
// PIC32_EcatLinkStatus_LogFileProc.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "PIC32_EcatLinkStatus_LogFileProc.h"
#include "MainFrm.h"

#include "PIC32_EcatLinkStatus_LogFileProcDoc.h"
#include "PIC32_EcatLinkStatus_LogFileProcView.h"

#include <errno.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPIC32EcatLinkStatusLogFileProcApp

BEGIN_MESSAGE_MAP(CPIC32EcatLinkStatusLogFileProcApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CPIC32EcatLinkStatusLogFileProcApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_FILE_OPEN, &CPIC32EcatLinkStatusLogFileProcApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CPIC32EcatLinkStatusLogFileProcApp construction

CPIC32EcatLinkStatusLogFileProcApp::CPIC32EcatLinkStatusLogFileProcApp() noexcept
{
	m_bHiColorIcons = TRUE;

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("PIC32EcatLinkStatusLogFileProc.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	InputFile_m		= NULL;
	OutputFile_m	= NULL;
}

// The one and only CPIC32EcatLinkStatusLogFileProcApp object

CPIC32EcatLinkStatusLogFileProcApp theApp;


// CPIC32EcatLinkStatusLogFileProcApp initialization

BOOL CPIC32EcatLinkStatusLogFileProcApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPIC32EcatLinkStatusLogFileProcDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CPIC32EcatLinkStatusLogFileProcView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Get access to the Main Frame to reach the Output window
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();
	wndOutputPtr_m = (COutputWnd*)mainFrame->GetOutputWndPrt();

	return TRUE;
}

int CPIC32EcatLinkStatusLogFileProcApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CPIC32EcatLinkStatusLogFileProcApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CPIC32EcatLinkStatusLogFileProcApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CPIC32EcatLinkStatusLogFileProcApp customization load/save methods

void CPIC32EcatLinkStatusLogFileProcApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CPIC32EcatLinkStatusLogFileProcApp::LoadCustomState()
{
}

void CPIC32EcatLinkStatusLogFileProcApp::SaveCustomState()
{
}

// CPIC32EcatLinkStatusLogFileProcApp message handlers

void CPIC32EcatLinkStatusLogFileProcApp::OnFileOpen()
{
	char	inBuffer[256];
	char	outBuffer[256]	= "";
	char*	ret = NULL;

	CFileDialog dlgFile(TRUE);
	CFileDialog dlgFileSave(FALSE, _T("dr"), NULL, NULL, _T("Log File (*.log)|*.txt|") _T("All Files||"));

	INT_PTR retDlg;

	// 1. Get Input filename
	retDlg = dlgFile.DoModal();
	if (retDlg != IDOK)
		return;
	InputFile_filename_m = dlgFile.GetPathName();
	// 1.1 Open File
	errno_t err = 0;
	err = fopen_s(&InputFile_m, InputFile_filename_m.GetString(), "r");
	if (0 != err)
		return;

	// 2. Get Output filename
	retDlg = dlgFileSave.DoModal();
	if (retDlg != IDOK)
		return;
	OutputFile_filename_m = dlgFileSave.GetPathName();

	// 2.2 Open file
	err = 0;
	err = fopen_s(&OutputFile_m, OutputFile_filename_m.GetString(), "w");
	if (0 != err)
		return;

	// 3. Process file
	// Every 3 rows & 2 cols --> 1 row & 3 cols
	do {	
		int linesProc = 0;
		do
		{
			 ret = fgets(inBuffer, sizeof(inBuffer), InputFile_m);

			int posStart = 0;

			if ( NULL != ret )
			{
				while ((inBuffer[posStart] != ',') && (posStart < sizeof(inBuffer)))
				{
					posStart++;
				}
				posStart += 2; // jump over ','  and ' ' characters 
				int posEnd = posStart + 1;
				while ((inBuffer[posEnd] != ',') && (posEnd < sizeof(inBuffer)))
				{
					posEnd++;
				}
				char Value1[16] = { {} };
				memcpy(Value1, &inBuffer[posStart], posEnd - posStart);

				fwrite(Value1, 1, posEnd - posStart, OutputFile_m);
				if (linesProc < 2)
					fwrite("\t", 1, 1, OutputFile_m); // add tabulation
			}
			else
				break;

			linesProc++;
		}while (linesProc < 3);

		if( NULL != ret) // No extra file ending line
			fwrite("\n", 1, 1, OutputFile_m);

	} while( (NULL != ret) && (inBuffer != "") );

	// Close files
	fclose(InputFile_m);
	fclose(OutputFile_m);

	wndOutputPtr_m->InsertMsgBuildWindow(0, _T("File processing is done!"));
}
