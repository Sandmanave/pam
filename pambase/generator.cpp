#include "generator.h"
#include "timedbuffer.h"
#include "audio.h"
#include <wx/log.h>
#include <iterator>

using namespace std;

Sequence::Sequence(int nChannels) : m_nChannels(nChannels)
{
    m_itPosition = m_lstSequence.end();
}
void Sequence::AppendGenFreq(double dFrequency, double ddBFS, int nCycles, int nType)
{

    double dAmplitude(0.0);
    if(ddBFS > -80.0)
    {
        dAmplitude = pow(10.0, ddBFS/20.0);
    }

    m_lstSequence.push_back(genfreq(dFrequency, dAmplitude, nCycles,nType));
    if(m_itPosition == m_lstSequence.end())
    {
        m_itPosition = m_lstSequence.begin();
    }
}

list<genfreq>::iterator Sequence::GetSequenceBegin()
{
    return m_lstSequence.begin();
}

list<genfreq>::iterator Sequence::GetSequenceEnd()
{
    m_lstSequence.end();
}

const std::list<genfreq>::iterator& Sequence::GetSequencePosition()
{
    return m_itPosition;
}

void Sequence::AdvanceSequence()
{
    (*m_itPosition).dCycleCount = 0.0;
    (*m_itPosition).dPhase = 0.0;
    ++m_itPosition;
    if(m_itPosition == m_lstSequence.end())
    {
        m_itPosition = m_lstSequence.begin();
    }
}


Generator::Generator(wxEvtHandler* pHandler) :
    m_pHandler(pHandler),
    m_dSampleRate(48000),
    m_nPhase(0)
{

}

Generator::~Generator()
{
    ClearSequences();
}

void Generator::SetSampleRate(unsigned int nSampleRate)
{
    m_dSampleRate = nSampleRate;
    m_nPhase = 0;
}


void Generator::Generate(unsigned int nSize)
{

    float* pBuffer = new float[nSize];
    for(int i = 0; i < nSize; i++)
    {
        pBuffer[i] = 0.0;
    }

    timedbuffer* pData = new timedbuffer(nSize);
    double dSize(m_mSequences.size());

    if(m_mSequences.empty() == false)
    {
        for(map<wxString, Sequence*>::iterator itSequence = m_mSequences.begin(); itSequence != m_mSequences.end(); ++itSequence)
        {
            GenerateSequence(itSequence->second, pBuffer, nSize);
        }
    }
    else if(m_queueFreq.empty() == false)
    {
        GenerateFrequency(pBuffer, nSize);
    }


    m_nPhase += nSize/2;//(m_nPhase+nSize)%static_cast<int>(m_dSampleRate);

    pData->SetBuffer(pBuffer);

    pData->SetDuration(pData->GetBufferSize()*3);
    wxCommandEvent event(wxEVT_DATA);
    event.SetId(timedbuffer::GENERATOR);
    event.SetClientData(reinterpret_cast<void*>(pData));
    event.SetInt(pData->GetBufferSize()/2);
    event.SetExtraLong(m_dSampleRate);
    wxPostEvent(m_pHandler, event);
}

void Generator::GenerateSequence(Sequence* pSeq, float* pBuffer, unsigned int nSize)
{

    for(int i = 0; i < nSize; i+=2)
    {
        double dAmplitude(0.0);
        switch(pSeq->GetSequencePosition()->nType)
        {
            case SINE:
                dAmplitude = GenerateSin((*pSeq->GetSequencePosition()), pSeq->GetSequencePosition()->dPhase);
                break;
            case SQUARE:
                dAmplitude = GenerateSquare((*pSeq->GetSequencePosition()), pSeq->GetSequencePosition()->dPhase);
                break;
            case SAW:
                dAmplitude = GenerateSaw((*pSeq->GetSequencePosition()), pSeq->GetSequencePosition()->dPhase);
                break;
            case TRIANGLE:
                dAmplitude = GenerateTriangle((*pSeq->GetSequencePosition()), pSeq->GetSequencePosition()->dPhase);
                break;
        }
        if((pSeq->GetChannels() & Sequence::LEFT))
        {
            pBuffer[i] += dAmplitude;
        }
        if((pSeq->GetChannels() & Sequence::RIGHT))
        {
            pBuffer[i+1] += dAmplitude;
        }

        if(pSeq->GetSequencePosition()->nCycles > 0)
        {
            pSeq->GetSequencePosition()->dCycleCount+= (pSeq->GetSequencePosition()->dFrequency/m_dSampleRate);
            if(pSeq->GetSequencePosition()->dCycleCount >= pSeq->GetSequencePosition()->nCycles)
            {
                pSeq->AdvanceSequence();
            }
        }
        pSeq->GetSequencePosition()->dPhase++;
    }
}

void Generator::GenerateFrequency(float* pBuffer, unsigned int nSize)
{

    for(int i = 0; i < nSize; i+=2)
    {
        double dAmplitude(0.0);
        switch(m_queueFreq.front().nType)
        {
            case SINE:
                dAmplitude = GenerateSin(m_queueFreq.front(), m_queueFreq.front().dPhase);
                break;
            case SQUARE:
                dAmplitude = GenerateSquare(m_queueFreq.front(), m_queueFreq.front().dPhase);
                break;
            case SAW:
                dAmplitude = GenerateSaw(m_queueFreq.front(), m_queueFreq.front().dPhase);
                break;
            case TRIANGLE:
                dAmplitude = GenerateTriangle(m_queueFreq.front(), m_queueFreq.front().dPhase);
                break;
        }
        pBuffer[i] += dAmplitude;
        pBuffer[i+1] += dAmplitude;

        m_queueFreq.front().dPhase++;

        m_queueFreq.front().dCycleCount+= (m_queueFreq.front().dFrequency/m_dSampleRate);
        if(m_queueFreq.front().dCycleCount >= 1.0)
        {
            m_queueFreq.front().dCycleCount -= 1.0;
            if(m_queueFreq.size() > 1)
            {
                m_queueFreq.pop();
            }
        }

    }
}

float Generator::GenerateSin(const genfreq& gfreq, double dPhase)
{
    return sin(2 * M_PI * gfreq.dFrequency*(dPhase/m_dSampleRate)) * gfreq.dAmplitude;
}

float Generator::GenerateSquare(const genfreq& gfreq, double dPhase)
{
    double dAmp(sin(2 * M_PI * gfreq.dFrequency*(dPhase/m_dSampleRate)));
    if(dAmp >0 )
    {
        return gfreq.dAmplitude ;
    }
    else if(dAmp < 0)
    {
        return -gfreq.dAmplitude ;
    }
    return 0;
}

float Generator::GenerateSaw(const genfreq& gfreq, double dPhase)
{
    return - (2.0*gfreq.dAmplitude*atan(tan(M_PI_2 - (M_PI * gfreq.dFrequency*(dPhase/m_dSampleRate)) )))/M_PI;
}

float Generator::GenerateTriangle(const genfreq& gfreq, double dPhase)
{
    return (2.0*gfreq.dAmplitude*asin(sin(2 * M_PI * gfreq.dFrequency*(dPhase/m_dSampleRate))))/M_PI;
}


void Generator::AddSequence(const wxString& sName, Sequence* pSeq)
{
    m_mSequences.insert(make_pair(sName, pSeq));
}

void Generator::ClearSequences()
{
    for(map<wxString, Sequence*>::iterator itSeq = m_mSequences.begin(); itSeq != m_mSequences.end(); ++itSeq)
    {
        delete itSeq->second;
    }
    m_mSequences.clear();
}

void Generator::DeleteSequence(const wxString& sName)
{
    map<wxString, Sequence*>::iterator itSeq = m_mSequences.find(sName);
    if(itSeq != m_mSequences.end())
    {
        delete itSeq->second;
        m_mSequences.erase(sName);
    }
}


void Generator::SetFrequency(double dFrequency, double ddBFS, int nType)
{
    ClearSequences();
    double dAmplitude = 0.0;
    if(ddBFS > -80.0)
    {
        dAmplitude = pow(10.0, ddBFS/20.0);
    }

    m_queueFreq.push(genfreq(dFrequency, dAmplitude, 1, nType));
}
