#include "playout.h"
#include <wx/log.h>
#include <iostream>
#include "audio.h"
#include "settings.h"

using namespace std;

Playback::Playback() :
    m_pManager(0),
    m_nDevice(0),
    m_pStream(0),
    m_nSampleRate(48000),
    m_nBufferSize(0),
    m_nOutputChannels(2),
    m_pBuffer(0)
{
    m_bDone = false;
    m_bOpen = false;
    m_bClose = false;

    // @todo make this multi channel
    m_vMixer.resize(2);
    m_vMixer[0] = 0;
    m_vMixer[1] = 1;

    m_nInputChannels = 2;
}

Playback::~Playback()
{
    Close();
}

void Playback::Close()
{
    if(m_pStream)
    {
        Pa_CloseStream(m_pStream);
        m_pStream = NULL;
    }
}


void Playback::Run()
{
    OpenStream(m_nDevice,m_nSampleRate,playbackCallback);

}


void Playback::ClosePlayback()
{
    Close();
    while(m_qBuffer.empty() == false)
    {
        m_qBuffer.pop();
    }
}

bool Playback::OpenPlayback(unsigned long nDevice, unsigned long nSampleRate, unsigned long nChannels, unsigned long nBufferSize)
{
    if(m_pStream)
    {
        ClosePlayback();
    }

    m_nDevice = nDevice;
    m_nSampleRate = nSampleRate;
    m_nOutputChannels = nChannels;
    m_nBufferSize = nBufferSize;

    if(m_nSampleRate == 0)
    {
        m_nSampleRate = 48000;
    }
    if(m_nOutputChannels == 0)
    {
        m_nOutputChannels = 2;
    }
    if(m_pBuffer)
    {
        delete[] m_pBuffer;
    }
    m_pBuffer = new float[m_nBufferSize*nChannels];

    return OpenStream(m_nDevice,m_nSampleRate,playbackCallback);
}

bool Playback::OpenStream(unsigned long nDevice, unsigned long nSampleRate, PaStreamCallback *streamCallback)
{
//    wxLogDebug(wxT("Playback::OpenStream"));

    PaStreamParameters outputParameters;
    outputParameters.channelCount = m_nOutputChannels;
    outputParameters.device = nDevice;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = 0;//Pa_GetDeviceInfo(m_nDevice)->defaultHighOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    PaError err = Pa_OpenStream(&m_pStream, 0, &outputParameters, nSampleRate, m_nBufferSize, paNoFlag, streamCallback, reinterpret_cast<void*>(this) );
    if(err == paNoError)
    {
        err = Pa_StartStream(m_pStream);
        if(err == paNoError)
        {

            m_bDone = true;
            m_bFirst = true;
            return true;
        }
        else
        {
            //wxLogDebug(wxT("Playback::OpenStream - Could not start stream %s"), wxString::FromAscii(Pa_GetErrorText(err)).c_str());
        }
    }
    else
    {
        const PaDeviceInfo* pInfo = Pa_GetDeviceInfo(nDevice);
        int nChannels = -1;
        if(pInfo)
        {
            nChannels = pInfo->maxInputChannels;
        }
    }
    return false;
}

pairTime_t Playback::ConvertDoubleToPairTime(double dTime)
{
    double dInt, dDec;
    dDec = modf(dTime, &dInt);
    return make_pair(static_cast<unsigned int>(dInt), static_cast<unsigned int>(dDec*1000000.0));
}

void Playback::Callback(float* pBuffer, size_t nFrameCount)
{

    wxMutexLocker ml(m_mutex);

    int nSamples = 0;

    if(m_bFirst)
    {
        pairTime_t tvNow;
        gettimeofday(tvNow, NULL);
        double dNow = ConvertPairTimeToDouble(tvNow);
        double dLatency = (dNow-m_qBuffer.front().dPresentation)*1000.0;
        while(dLatency < Settings::Get().Read(wxT("Playback"), wxT("Latency"), 0) && nSamples < nFrameCount*m_nOutputChannels)
        {
            for(int i = 0; i < m_nOutputChannels; i++)
            {
                pBuffer[nSamples] = 0.0;
                nSamples++;
            }
            dLatency += (1000.0/48000.0);
        }

        m_dLatency = dLatency;

        if(nSamples < nFrameCount*m_nOutputChannels)
        {
            m_bFirst = false;
        }
        m_nBuffer = m_qBuffer.size();
    }
    else if(m_qBuffer.size() != m_nBuffer)
    {
        pairTime_t tvNow;
        gettimeofday(tvNow, NULL);
        double dNow = ConvertPairTimeToDouble(tvNow);
        m_dLatency = (dNow-m_qBuffer.front().dPresentation)*1000.0;

        m_nBuffer = m_qBuffer.size();
    }

    timedSample tsBuffer;
    if(m_qBuffer.empty() == false)
    {
        tsBuffer = m_qBuffer.front();
    }


    for(size_t i = nSamples; i < nFrameCount*m_nOutputChannels; i++)
    {
        if(m_qBuffer.size() > 0)
        {
            float d(m_qBuffer.front().dSample);
            pBuffer[i] = m_qBuffer.front().dSample;
            m_qBuffer.pop();
        }
        else
        {
            pBuffer[i] = 0.0;
        }
    }



    //double dOffsetMicro = static_cast<double>(m_qBuffer.size()/m_nOutputChannels)/static_cast<double>(m_nSampleRate)*1000000.0;
    timedbuffer* pTimedBuffer = new timedbuffer(nFrameCount*m_nOutputChannels, ConvertDoubleToPairTime(tsBuffer.dPresentation), tsBuffer.nTimestamp);
    pTimedBuffer->SetTransmissionTime(ConvertDoubleToPairTime(tsBuffer.dTransmission));
    pTimedBuffer->SetBuffer(pBuffer);
    pTimedBuffer->SetPlaybackOffset(m_dLatency*1000.0);
    pTimedBuffer->SetBufferDepth(m_qBuffer.size()/m_nOutputChannels);



    wxCommandEvent event(wxEVT_DATA);
    event.SetId(1);
    event.SetClientData(reinterpret_cast<void*>(pTimedBuffer));
    event.SetInt(nFrameCount);
    event.SetExtraLong(m_nSampleRate);
    wxPostEvent(m_pManager, event);

}


double Playback::ConvertPairTimeToDouble(const pairTime_t& tv)
{
    return static_cast<double>(tv.second)/1000000.0 + static_cast<double>(tv.first);
}

void Playback::AddSamples(const timedbuffer* pTimedBuffer)
{
    wxMutexLocker ml(m_mutex);
    if(m_nInputChannels > 0)
    {
        double dModifier(0.0);
        double dTransmission(ConvertPairTimeToDouble(pTimedBuffer->GetTransmissionTime()));
        double dPresentation(ConvertPairTimeToDouble(pTimedBuffer->GetTimeVal()));

        for(unsigned int i =0; i < pTimedBuffer->GetBufferSize(); i+=m_nInputChannels)
        {
            int nSample = i/m_nInputChannels;
            dModifier = static_cast<double>(nSample)/static_cast<double>(m_nSampleRate);

            for(size_t j = 0; j < m_vMixer.size(); j++)
            {
                m_qBuffer.push(timedSample(dTransmission+dModifier, dPresentation+dModifier, pTimedBuffer->GetTimestamp()+nSample, pTimedBuffer->GetBuffer()[i+m_vMixer[j]]));
            }
        }
    }
}

bool Playback::IsStreamOpen()
{
    return (m_pStream && Pa_IsStreamActive(m_pStream));
}


int playbackCallback( const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData )
{
    if(userData && output)
    {
        //cout << statusFlags << endl;
        Playback* pPlayer = reinterpret_cast<Playback*>(userData);
        pPlayer->Callback(reinterpret_cast<float*>(output), frameCount);
    }
    return 0;
}


void Playback::FlushBuffer()
{
    while(m_qBuffer.empty() == false)
    {
        m_qBuffer.pop();
    }
}

void Playback::SetMixer(const vector<char>& vChannels, unsigned int nTotalChannels)
{
    m_vMixer = vChannels;
    m_nInputChannels = nTotalChannels;
    //m_vOutput.resize(nTotalChannels);
}

const std::vector<char>& Playback::GetOutputChannels()
{
    return m_vMixer;
}
