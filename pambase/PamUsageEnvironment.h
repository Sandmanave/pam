#pragma once
#include "BasicUsageEnvironment0.hh"
#include <wx/string.h>
#include <wx/event.h>
#include "dlldefine.h"
#include "log.h"
class PAMBASE_IMPEXPORT PamUsageEnvironment: public BasicUsageEnvironment0 {
public:
  static PamUsageEnvironment* createNew(TaskScheduler& taskScheduler, wxEvtHandler* pHandler);

  // redefined virtual functions:
  virtual int getErrno() const;

  virtual UsageEnvironment& operator<<(char const* str);
  virtual UsageEnvironment& operator<<(int i);
  virtual UsageEnvironment& operator<<(unsigned u);
  virtual UsageEnvironment& operator<<(double d);
  virtual UsageEnvironment& operator<<(void* p);

protected:
  PamUsageEnvironment(TaskScheduler& taskScheduler, wxEvtHandler* pHandler);
      // called only by "createNew()" (or subclass constructors)
  virtual ~PamUsageEnvironment();

  wxEvtHandler* m_pHandler;
  wxString m_sLog;
    pml::LogStream m_ls;
};


