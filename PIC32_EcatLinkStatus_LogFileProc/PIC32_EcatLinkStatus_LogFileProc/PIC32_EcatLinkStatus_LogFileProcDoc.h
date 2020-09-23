
// PIC32_EcatLinkStatus_LogFileProcDoc.h : interface of the CPIC32EcatLinkStatusLogFileProcDoc class
//


#pragma once


class CPIC32EcatLinkStatusLogFileProcDoc : public CDocument
{
protected: // create from serialization only
	CPIC32EcatLinkStatusLogFileProcDoc() noexcept;
	DECLARE_DYNCREATE(CPIC32EcatLinkStatusLogFileProcDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CPIC32EcatLinkStatusLogFileProcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
