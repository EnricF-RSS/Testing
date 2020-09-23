
// PIC32_EcatLinkStatus_LogFileProc.h : main header file for the PIC32_EcatLinkStatus_LogFileProc application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "OutputWnd.h"

// CPIC32EcatLinkStatusLogFileProcApp:
// See PIC32_EcatLinkStatus_LogFileProc.cpp for the implementation of this class
//

class CPIC32EcatLinkStatusLogFileProcApp : public CWinAppEx
{
private:
	FILE*	InputFile_m;
	FILE*	OutputFile_m;

	CString InputFile_filename_m;
	CString OutputFile_filename_m;

protected:
	COutputWnd* wndOutputPtr_m;
	//CMainFrame*	m_mainFramePtr;

public:
	void SetOutputWndPtr(COutputWnd* Ptr) { wndOutputPtr_m = Ptr; };

public:
	CPIC32EcatLinkStatusLogFileProcApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOpen();
};

extern CPIC32EcatLinkStatusLogFileProcApp theApp;
