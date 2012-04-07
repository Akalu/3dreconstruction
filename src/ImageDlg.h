// ImageDlg.h : header file
//

#if !defined(AFX_IMAGEDLG_H__53EABC9A_DE6B_4FBB_8591_E326D15AA683__INCLUDED_)
#define AFX_IMAGEDLG_H__53EABC9A_DE6B_4FBB_8591_E326D15AA683__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TRGB.h"
#include "CVector.h"

/////////////////////////////////////////////////////////////////////////////
// CImageDlg dialog

class CImageDlg : public CDialog
{
// Construction
public:
//	CString m_ePath2;
//	CString m_ePath1;
	CRect m_Vwindow;
	CImageDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CImageDlg)
	enum { IDD = IDD_IMAGE_DIALOG };
	CButton	m_sf;
	CEdit	m_eBase;
	CButton	m_sname2;
	CButton	m_sname1;
	CButton	m_bOk;
	CString	m_ePath1;
	CString	m_ePath2;
	float	m_sbase;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CImageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnOpenbtn1();
	afx_msg void OnOpenbtn2();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL RenderCash3d(CDC* dc2, float th, float fi);
	float base;
	int mod(int a,int b);
	int halfwidth;
	int halfheight;
	float f;
	CBitmap lastrender;
	BOOL bCashisempty;
	CIVector* cash3d;
	int YMAX;
	int YMIN;
	int XMAX;
	int XMIN;
	int dplane;
	CPoint m_ClickEnd;
	CPoint m_ClickStart;
	float theta_max;
	float fi_max;
	float theta;
	float fi;
	int sqr(int );
	int CulcL2distance(int x1,int y1,int x2, int y2);
	RGBTRIAD* pRow2[1024];
	RGBTRIAD* pRow1[1024];
	float pi;
	float gamma;
	int height;
	int width;
	BYTE* Bits2;
	BYTE* Bits1;
	BOOL LoadBMPFileInfo(CStdioFile& fl,BITMAPFILEHEADER& fh, BITMAPINFOHEADER& ih);
	BITMAPINFOHEADER infohead2;
	BITMAPINFOHEADER infohead1;
	BITMAPFILEHEADER filehead2;
	BITMAPFILEHEADER filehead1;
	BOOL m_bPath2;
	BOOL m_bPath1;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEDLG_H__53EABC9A_DE6B_4FBB_8591_E326D15AA683__INCLUDED_)
