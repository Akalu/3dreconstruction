// ImageDlg.cpp : implementation file
// 

#include "stdafx.h"
#include "Image.h"
#include "ImageDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageDlg dialog

CImageDlg::CImageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageDlg)
	m_ePath1 = _T("");
	m_ePath2 = _T("");
	m_sbase = 0.0f;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageDlg)
	DDX_Control(pDX, IDC_SFOCAL, m_sf);
	DDX_Control(pDX, IDC_EBASE, m_eBase);
	DDX_Control(pDX, IDC_SNAME2, m_sname2);
	DDX_Control(pDX, IDC_SNAME1, m_sname1);
	DDX_Control(pDX, IDOK, m_bOk);
	DDX_Text(pDX, IDC_EFULLPATH1, m_ePath1);
	DDX_Text(pDX, IDC_EFULLPATH2, m_ePath2);
	DDX_Text(pDX, IDC_EBASE, m_sbase);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImageDlg, CDialog)
	//{{AFX_MSG_MAP(CImageDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnStart)
	ON_BN_CLICKED(IDC_OPENBTN1, OnOpenbtn1)
	ON_BN_CLICKED(IDC_OPENBTN2, OnOpenbtn2)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageDlg message handlers

BOOL CImageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//INIT Paths Vars
	m_bOk.EnableWindow(FALSE);
	m_bPath1=FALSE;
	m_bPath2=FALSE;
	m_ePath1="c:\\";
	m_ePath2="c:\\";
	pi=3.1415927;
	gamma=135*pi/180;
	f=0;	base=0;
	fi=0;	theta=0;
	fi_max=90;theta_max=90;
	dplane=600;
	bCashisempty=TRUE;
	m_eBase.EnableWindow(FALSE);
	
	CWnd* p_Canvas=GetDlgItem(IDC_VWINDOW); 

	p_Canvas->GetWindowRect(&m_Vwindow); 

	ScreenToClient(&m_Vwindow); 

	m_Vwindow.DeflateRect(2,2,1,1); 
	
	CClientDC dc(this); 

	dc.SelectStockObject(NULL_PEN); 

	dc.Rectangle(m_Vwindow); 

	XMIN=m_Vwindow.left;
	XMAX=m_Vwindow.Width()-2;
	YMIN=m_Vwindow.top;
	YMAX=m_Vwindow.Height()-2;

	lastrender.CreateCompatibleBitmap( &dc, XMAX, YMAX );

	UpdateData(FALSE);
	 return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.



// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CImageDlg::OnStart() 
{
	CClientDC dc( this );
	CDC dc2;

	int wd1=infohead1.biWidth;
	int ht1=infohead1.biHeight;
	int wd2=infohead2.biWidth;
	int ht2=infohead2.biHeight;
	if ((wd1!=wd2) || (ht1!=ht2)){
		AfxMessageBox("The size of images must be equal!",
			        MB_ICONEXCLAMATION);
		return;
	}

	m_bOk.SetWindowText("Processing...");
	dc2.CreateCompatibleDC(&dc);
	dc2.SelectObject( &lastrender );

	width=min(wd1,wd2)-1;
	height=min(ht1,ht2)-1;
	halfheight=height/2;
	halfwidth=width/2;

	int loffset1=mod(3*wd1,4)==0?3*wd1:(3*wd1/4+1)*4;
	int loffset2=mod(3*wd2,4)==0?3*wd2:(3*wd2/4+1)*4;
	
	for (int i=0;i<infohead1.biHeight;i++)
		pRow1[i]=(RGBTRIAD*)(Bits1+i*loffset1);
	for (i=0;i<infohead2.biHeight;i++)
		pRow2[i]=(RGBTRIAD*)(Bits2+i*loffset2);
		

	float d=width,f=d/2,gamma_min,ftg,a[2][2],detofa,v[2],t;
	base=width*1.8;m_sbase=base*sin(gamma/2);dplane=m_sbase;
	int l2distance,dist;
	int u1,w1,u2,w2,u_near,w_near;
	CFVector r01,a1,r02,a2,r1,center;
	cash3d =(CIVector*)malloc(height*width*sizeof(CIVector));
	int count=0;
	CString s;
	s.Format("f = %4.2f",f);
	m_sf.SetWindowText(s);
	UpdateData(FALSE);

	ftg=f*sin(gamma/2)/cos(gamma/2);

	r01.x=width/2;
	r01.y=0;	
	r01.z=height/2;
	a1.x=0;				
	a1.y=1;		
	a1.z=0;
	r02.x=(width+base)/2-(base/2)*cos(gamma);
	r02.y=(base/2)*cos(gamma-pi/2);
	r02.z=height/2;
	a2.x=-f*cos(gamma-pi/2);
	a2.y=f*sin(gamma-pi/2);
	a2.z=0;
	a[0][0]=a1*a2; a[0][1]=-(a1*a1);
	a[1][0]=a2*a2; a[1][1]=-(a1*a2);
	v[0]=a1*(r01-r02);
	v[1]=a2*(r01-r02);
	detofa=a[0][0]*a[1][1]-a[0][1]*a[1][0];
	t=(a[0][0]*v[1]-a[1][0]*v[0])/detofa;
	center=r01+t*a1;


	for (w1=(height-1)/2;w1>(-height+1)/2;w1--)
		for (u1=(-width+1)/2;u1<(width-1)/2;u1++){
			l2distance=10000;
			for ( u2=(-width+1)/2;u2<(width-1)/2;u2++){
			w2=w1*(ftg-u2)/(ftg+u1);
			if (w2>(-height+1)/2 && w2<(height-1)/2){
				dist=CulcL2distance(u1+halfwidth,w1+halfheight,
									u2+halfwidth,w2+halfheight);
				if (dist<l2distance){
					l2distance=dist;
					u_near=u2;
					w_near=w2;
				}
			}
		}
		if (l2distance!=100){
			r01.x=halfwidth+u1;
			r01.y=0;
			r01.z=halfheight+w1;
			a1.x=-u1;
			a1.y=f;
			a1.z=-w1;
			r02.x=(width+base)/2-(base/2+u_near)*cos(gamma);
			r02.y=(base/2+u_near)*sin(gamma);
			r02.z=height/2+w_near;
			a2.x=u_near*cos(gamma)-f*sin(gamma);
			a2.y=-f*cos(gamma)-u_near*sin(gamma);
			a2.z=-w_near;
			a[0][0]=a1*a2; a[0][1]=-(a1*a1);
			a[1][0]=a2*a2; a[1][1]=-(a1*a2);
			v[0]=a1*(r01-r02);
			v[1]=a2*(r01-r02);
			detofa=a[0][0]*a[1][1]-a[0][1]*a[1][0];
			t=(a[0][0]*v[1]-a[1][0]*v[0])/detofa;
			r1=r01+t*a1-center;
			cash3d[count].x=int(r1.x);
			cash3d[count].y=int(r1.y);
			cash3d[count++].z=int(r1.z);
		}
		else{
			cash3d[count].x=0;
			cash3d[count].y=0;
			cash3d[count++].z=0;
		}
		}
		bCashisempty=FALSE;

	RenderCash3d(&dc2,0,0);
	dc.BitBlt( XMIN, YMIN , XMAX, YMAX , &dc2, 0,0, SRCCOPY );
	m_bOk.SetWindowText("Generate");
}

void CImageDlg::OnOpenbtn1() 
{
	// TODO: Add your control notification handler code here
	CFileDialog DlgOpen(TRUE,(LPCSTR)"bmp",NULL,
  		OFN_HIDEREADONLY,(LPCSTR)"Graphic Files (*.bmp) |*.bmp||");  
 
	if(DlgOpen.DoModal()==IDOK){ 

		m_ePath1=DlgOpen.GetPathName();
		if (m_ePath1.Compare((LPCTSTR)m_ePath2)==0)
			AfxMessageBox("This file have chose yet",MB_ICONEXCLAMATION);
		else{
			CStdioFile File1(m_ePath1,CFile::modeRead|CFile::typeBinary);  
			CString tmp;

			if (LoadBMPFileInfo(File1,filehead1,infohead1) ){
				tmp.Format("Left Image: %4d x %4d", infohead1.biWidth,
											infohead1.biHeight);
				m_sname1.SetWindowText(tmp);

				// allocating memory

				Bits1=
				(BYTE*)malloc(infohead1.biSizeImage);
				if (Bits1 == NULL)
					AfxMessageBox("Allocation memory error",MB_ICONEXCLAMATION);

				// load bits
				File1.Read(Bits1,infohead1.biSizeImage);
				File1.Close();
				m_bPath1=TRUE;
			}
		}
		m_bOk.EnableWindow(m_bPath1 & m_bPath2);
		UpdateData(FALSE);
		} 
}

void CImageDlg::OnOpenbtn2() 
{
	// TODO: Add your control notification handler code here
	CFileDialog DlgOpen(TRUE,(LPCSTR)"bmp",NULL,
  		OFN_HIDEREADONLY,(LPCSTR)"Graphic Files (*.bmp) |*.bmp||");  

	if(DlgOpen.DoModal()==IDOK){ 
		m_ePath2=DlgOpen.GetPathName();
		if (m_ePath2.Compare((LPCTSTR)m_ePath1)==0)
			AfxMessageBox("This file have chose yet, choose another image",
			  MB_ICONEXCLAMATION);
		else{
				CStdioFile File2(m_ePath2,CFile::modeRead|CFile::typeBinary);  
				CString tmp;

			if (LoadBMPFileInfo(File2,filehead2,infohead2)){
				tmp.Format("Right Image: %4d x %4d", infohead2.biWidth,
											infohead2.biHeight);
				m_sname2.SetWindowText(tmp);
			
				Bits2=
				(BYTE*)malloc(infohead2.biSizeImage);
				if (Bits2 == NULL)
					AfxMessageBox("Allocation memory error",MB_ICONEXCLAMATION);
			// load bits

				File2.Read(Bits2,infohead2.biSizeImage);				
				File2.Close();
		
				m_bPath2=TRUE;
			}
		}
		m_bOk.EnableWindow(m_bPath1 & m_bPath2);
		UpdateData(FALSE);
		
	}
}

BOOL CImageDlg::LoadBMPFileInfo(CStdioFile &fl, BITMAPFILEHEADER &fh, BITMAPINFOHEADER &ih)
{
	fl.Read(&fh,sizeof(fh));

	if ( fh.bfOffBits != 54 )
	{
		AfxMessageBox("File header not accepted!",
			  MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	fl.Read(&ih,sizeof(ih));
	
	if (ih.biSize != 40
		 || ih.biHeight < 0 
		 || ih.biPlanes != 1
	     || ih.biBitCount != 24
		 || ih.biCompression != 0 /* not compressed */ ){
			AfxMessageBox("Format is not 24bit uncompressed bitmap with orig at left-bottom corner!",
			  MB_ICONEXCLAMATION);
		 return FALSE;
	}
	return TRUE;
}



int inline CImageDlg::CulcL2distance(int x1, int y1, int x2, int y2)
{
	BYTE TP1[15];
	BYTE TP2[15];

	memcpy(TP1,&(pRow1[y1][x1].B),3);
	memcpy(TP1+3,&(pRow1[y1-1][x1].B),3);
	memcpy(TP1+6,&(pRow1[y1+1][x1].B),3);
	memcpy(TP1+9,&(pRow1[y1][x1-1].B),3);
	memcpy(TP1+12,&(pRow1[y1][x1+1].B),3);

	memcpy(TP2,&(pRow2[y2][x2].B),3);
	memcpy(TP2+3,&(pRow2[y2-1][x2].B),3);
	memcpy(TP2+6,&(pRow2[y2+1][x2].B),3);
	memcpy(TP2+9,&(pRow2[y2][x2-1].B),3);
	memcpy(TP2+12,&(pRow2[y2][x2+1].B),3);
	int a=0;
	for (int i=0;i<15;i++) a+=sqr((int)TP1[i]-(int)TP2[i]);

	return a;
}


int inline CImageDlg::sqr(int b)
{
	return(b*b);

}

void CImageDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if(m_Vwindow.PtInRect(point) && !bCashisempty){

	m_ClickStart= point;
	m_ClickEnd=point; 
	}

	
	CDialog::OnLButtonDown(nFlags, point);
}

void CImageDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	float fi_tmp,theta_tmp;

	if( (nFlags & MK_LBUTTON) && m_Vwindow.PtInRect(point) 
		&& !bCashisempty){


	CClientDC dc(this); 
	CDC dc2;
	dc2.CreateCompatibleDC(&dc);
	dc2.SelectObject( &lastrender );

	m_ClickEnd= point; 

	fi_tmp=fi+(m_ClickEnd.x-m_ClickStart.x);
	theta_tmp=theta+(m_ClickEnd.y-m_ClickStart.y);
	if ((abs(fi_tmp)<fi_max) && (abs(theta_tmp)<theta_max)){
		fi=fi_tmp;
		theta=theta_tmp;
		RenderCash3d(&dc2,theta,fi);
		dc.BitBlt( XMIN, YMIN , XMAX, YMAX , &dc2, 0,0, SRCCOPY );
		m_ClickStart=m_ClickEnd;
	} 
	}
	
	CDialog::OnMouseMove(nFlags, point);
}

void CImageDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnLButtonUp(nFlags, point);
}

int CImageDlg::mod(int a, int b)
{
	return(a-b*(a/b));
}

BOOL CImageDlg::RenderCash3d(CDC* dc2, float th, float fi)
{
	int ut,wt;
	float cs_fi=cos(fi*pi/180),sn_fi=sin(fi*pi/180);
	float cs_theta=cos(th*pi/180),sn_theta=sin(th*pi/180);
	float uscale=0.2; float wscale=0.2;
	int count=0;
	int x,y,z,yt,xt2,yt2,zt2;
	BYTE R,G,B;

    dc2->FillSolidRect( 0, 0, XMAX, YMAX, RGB( 0,0,0) );

	for (int w1=(height-1)/2;w1>(-height+1)/2;w1--)
		for (int u1=(-width+1)/2;u1<(width-1)/2;u1++){
			R=pRow1[w1+halfheight][u1+halfwidth].R;
			G=pRow1[w1+halfheight][u1+halfwidth].G;
			B=pRow1[w1+halfheight][u1+halfwidth].B;
			x=-cash3d[count].x;
			y=cash3d[count].y;
			z=cash3d[count++].z;
			
			xt2=x*cs_fi-y*sn_fi;
			yt=x*sn_fi+y*cs_fi;
			yt2=yt*cs_theta+z*sn_theta;
			zt2=-yt*sn_theta+z*cs_theta;

			ut=int(uscale*dplane*(xt2)/(dplane+yt2))+XMAX/2;
			wt=int(wscale*dplane*(zt2)/(dplane+yt2))+YMAX/2;

			dc2->SetPixel(ut,wt,RGB(R,G,B));
		}
		return(TRUE);
}


void CImageDlg::OnPaint() 
{
	
	// TODO: Add your message handler code here
		if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	CDialog::OnPaint();
	CClientDC dc( this );
		if (!bCashisempty){
	CDC dc2;
	dc2.CreateCompatibleDC(&dc);
	dc2.SelectObject( &lastrender );
	dc.BitBlt( XMIN, YMIN , XMAX, YMAX , &dc2, 0,0, SRCCOPY );
		}
	}
	// Do not call CDialog::OnPaint() for painting messages
}


