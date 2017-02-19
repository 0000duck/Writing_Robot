
// FontsViewDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FontsView.h"
#include "FontsViewDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
int BITSTABLE[] = { 2,5,17,65 };
POINT Points[500];

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFontsViewDlg �Ի���



CFontsViewDlg::CFontsViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_FONTSVIEW_DIALOG, pParent)
	, m_strEntered(_T(""))
	, m_intBold(0)
	//, m_bCheckItalic(false)
	, m_intAngle(0)
	, m_intHeight(0)
	//, m_bCheckReverse(false)
	//, m_intBits(0)
	, m_strFontName(_T(""))
	//, pBuf(0)
	, m_strStatus(_T(""))
	, m_intPixX(0)
	, m_intPixY(0)
	//, m_intScrollHPos(0)
	//, m_intScrollVPos(0)
	, m_ctrlRadio1(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFontsViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EENTERED, m_strEntered);
	DDX_Control(pDX, IDC_SLIDER_BOLD, m_slider_bold);
	DDX_Text(pDX, IDC_EDIT_BOLD, m_intBold);
	DDV_MinMaxInt(pDX, m_intBold, 0, 900);
	DDX_Control(pDX, IDC_CHECK_ITALIC, m_ctlCheckItalic);
	DDX_Control(pDX, IDC_SLIDER_ANGLE, m_slider_angle);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_intAngle);
	DDV_MinMaxInt(pDX, m_intAngle, 0, 3599);
	DDX_Control(pDX, IDC_SLIDER_HEIGHT, m_slider_height);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_intHeight);
	DDV_MinMaxInt(pDX, m_intHeight, 0, 30000);
	DDX_Control(pDX, IDC_CHECK_REVERSE, m_ctlBtnReverse);
	DDX_Control(pDX, IDC_COMBO_NBITS, m_ctlComboNbits);
	DDX_Control(pDX, IDC_LFONTS, m_ctlFontList);
	DDX_LBString(pDX, IDC_LFONTS, m_strFontName);
	DDX_Control(pDX, IDC_STATIC_PIC, m_ctlDisplay);
	//DDX_Text(pDX, IDC_STATIC_STATUS, m_strStatus);
	DDX_Text(pDX, IDC_EDIT_PIXX, m_intPixX);
	DDX_Text(pDX, IDC_EDIT_PIXY, m_intPixY);
	DDX_Control(pDX, IDC_SCROLLBAR_H, m_ctlScrollH);
	DDX_Control(pDX, IDC_SCROLLBAR_V, m_ctlScrollV);
	DDX_Radio(pDX, IDC_RADIO1, m_ctrlRadio1);
}

BEGIN_MESSAGE_MAP(CFontsViewDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BEXIT, &CFontsViewDlg::OnBnClickedBexit)
	ON_EN_CHANGE(IDC_EENTERED, &CFontsViewDlg::OnEnChangeEentered)
	ON_LBN_SELCHANGE(IDC_LFONTS, &CFontsViewDlg::OnLbnSelchangeLfonts)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BOLD, &CFontsViewDlg::OnNMReleasedcaptureSliderBold)
	ON_BN_CLICKED(IDC_CHECK_ITALIC, &CFontsViewDlg::OnBnClickedCheckItalic)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_ANGLE, &CFontsViewDlg::OnNMReleasedcaptureSliderAngle)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_HEIGHT, &CFontsViewDlg::OnNMReleasedcaptureSliderHeight)
	ON_BN_CLICKED(IDC_CHECK_REVERSE, &CFontsViewDlg::OnBnClickedCheckReverse)
	ON_CBN_SELCHANGE(IDC_COMBO_NBITS, &CFontsViewDlg::OnCbnSelchangeComboNbits)
	ON_EN_CHANGE(IDC_EDIT_HEIGHT, &CFontsViewDlg::OnEnChangeEditHeight)
	ON_EN_CHANGE(IDC_EDIT_BOLD, &CFontsViewDlg::OnEnChangeEditBold)
	ON_EN_CHANGE(IDC_EDIT_ANGLE, &CFontsViewDlg::OnEnChangeEditAngle)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CFontsViewDlg::OnBnClickedButtonSave)
	ON_EN_CHANGE(IDC_EDIT_PIXX, &CFontsViewDlg::OnEnChangeEditPixx)
	ON_BN_CLICKED(IDC_BUTTON1, &CFontsViewDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CFontsViewDlg ��Ϣ�������

BOOL CFontsViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	FillFontList();
	m_strEntered = "��";
	this->SetWindowText("·����ȡ_��ƻҳ�Ʒ");
	this->m_slider_height.SetRange(0, 30000);
	this->m_slider_angle.SetTicFreq(1);
	this->m_intHeight = 100;
	this->m_slider_height.SetPos(this->m_intHeight);
	this->m_slider_angle.SetRange(0, 3600 - 1);
	this->m_slider_angle.SetTicFreq(1);
	this->m_intAngle = 0;
	this->m_slider_angle.SetPos(this->m_intAngle);
	this->m_slider_bold.SetRange(0, 900);
	this->m_slider_bold.SetTicFreq(100);
	this->m_intBold = 100;
	this->m_slider_bold.SetPos(this->m_intBold);
	this->m_bCheckItalic = false;
	this->m_bCheckReverse = false;
	this->m_ctlBtnReverse.SetCheck(this->m_bCheckReverse);
	this->m_ctlCheckItalic.SetCheck(this->m_bCheckItalic);
	this->charLineW = 0;
	this->pbmpinfo = NULL;
	this->pfileinfo = NULL;
	this->pBuf = NULL;
	this->m_intBits = 1;
	this->m_ctlComboNbits.SetCurSel(this->m_intBits - 1);
	this->GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(0);
	this->m_ctlScrollH.ShowWindow(SW_HIDE);
	this->m_ctlScrollV.ShowWindow(SW_HIDE);
	this->m_intScrollHPos = 0;
	this->m_intScrollVPos = 0;
	//this->m_strStatus = "״ָ̬ʾ��";

	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFontsViewDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFontsViewDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFontsViewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFontsViewDlg::OnBnClickedBexit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}


void CFontsViewDlg::OnEnChangeEentered()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}



void CFontsViewDlg::OnLbnSelchangeLfonts()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (m_ctrlRadio1==0)
		Paint();
	if (m_ctrlRadio1==1)
		SetMyFont();
}





void CFontsViewDlg::OnNMReleasedcaptureSliderBold(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->m_intBold =this->m_slider_bold.GetPos();
	this->UpdateData(0);
	this->OnLbnSelchangeLfonts();
	*pResult = 0;
}




void CFontsViewDlg::OnBnClickedCheckItalic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->m_bCheckItalic = this->m_ctlCheckItalic.GetCheck();

	this->OnLbnSelchangeLfonts();
}



void CFontsViewDlg::OnNMReleasedcaptureSliderAngle(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->m_intAngle = this->m_slider_angle.GetPos();
	this->UpdateData(0);
	this->OnLbnSelchangeLfonts();
	*pResult = 0;
}


void CFontsViewDlg::OnNMReleasedcaptureSliderHeight(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->m_intHeight = this->m_slider_height.GetPos();
	this->UpdateData(0);
	this->OnLbnSelchangeLfonts();
	*pResult = 0;
}


void CFontsViewDlg::OnBnClickedCheckReverse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->m_bCheckReverse = (bool)this->m_ctlBtnReverse.GetCheck();
	this->OnLbnSelchangeLfonts();
}



void CFontsViewDlg::OnCbnSelchangeComboNbits()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = this->m_ctlComboNbits.GetCurSel();
	if (i != CB_ERR)
		this->m_intBits = i + 1;
	this->OnLbnSelchangeLfonts();
}


void CFontsViewDlg::OnEnChangeEditHeight()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(1);
	this->m_slider_height.SetPos(this->m_intHeight);
	this->OnLbnSelchangeLfonts();
}


void CFontsViewDlg::OnEnChangeEditBold()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(1);
	this->m_slider_bold.SetPos(this->m_intBold);
	this->OnLbnSelchangeLfonts();
}


void CFontsViewDlg::OnEnChangeEditAngle()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(1);
	this->m_slider_angle.SetPos(this->m_intAngle);
	this->OnLbnSelchangeLfonts();
}

int CALLBACK MyEnumFontProc(ENUMLOGFONTEX* lpelf, NEWTEXTMETRICEX* lpntm, DWORD nFontType, long lParam)
{
	CFontsViewDlg* pWnd = (CFontsViewDlg*)lParam;
	if (pWnd)
	{
		pWnd->m_ctlFontList.AddString(lpelf->elfLogFont.lfFaceName);
		return 1;
	}
	return 0;
}

void CFontsViewDlg::FillFontList(void)
{
	int iCurCount;
	CString strCurFont;
	CString strPrevFont = "";
	LOGFONT lf;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfFaceName[0] = NULL;
	lf.lfPitchAndFamily = 0;
	m_ctlFontList.ResetContent();
	CClientDC dc(this);
	::EnumFontFamiliesEx((HDC)dc, &lf, (FONTENUMPROC)MyEnumFontProc, (LPARAM) this, 0);
	for (iCurCount = m_ctlFontList.GetCount();iCurCount >0;iCurCount--)
	{
		m_ctlFontList.GetText((iCurCount - 1), strCurFont);
		if (strCurFont == strPrevFont)
		{
			m_ctlFontList.DeleteString((iCurCount - 1));
		}
		else
		{
			strPrevFont = strCurFont;
		}
	}
	this->m_ctlFontList.SetCurSel(0);
	TRACE("the total is %d\n", this->m_ctlFontList.GetCount());
	this->m_ctlFontList.GetText(this->m_ctlFontList.GetCurSel(), this->m_strFontName);
}

void CFontsViewDlg::SetMyFont(void)
{


	if (m_strFontName.GetLength()>0)
	{
		CFont newfont;
		newfont.CreateFont(this->m_intHeight, 0, this->m_intAngle, 0, this->m_intBold, this->m_bCheckItalic, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, m_strFontName);
		CDC* pdc = this->m_ctlDisplay.GetDC();
		CFont *poldfont = pdc->SelectObject(&newfont);
		MAT2 mmat2 = { 0,1,0,0,0,0,0,1 };
		GLYPHMETRICS glpm;
		DWORD nLen;
		UINT chartemp;
		BYTE temp;
		temp = this->m_strEntered.GetAt(0);
		if (temp >= 128)
		{
			chartemp = ((UINT)temp) << 8;
			temp = this->m_strEntered.GetAt(1);
			chartemp += temp;
		}
		else
			chartemp = temp;

		TRACE("chartemp is %d, sizeof(uint) is %d\n", chartemp, sizeof(UINT));
		if (this->m_intBits == 1)
			nLen = ::GetGlyphOutline(pdc->GetSafeHdc(), chartemp, this->m_intBits, &glpm, 0, NULL, &mmat2);
		else
			nLen = ::GetGlyphOutline(pdc->GetSafeHdc(), chartemp, this->m_intBits + 2, &glpm, 0, NULL, &mmat2);

		//GGO_BITMAP 1 
		// GGO_GRAY2_BITMAP   4
		// GGO_GRAY4_BITMAP   5
		//GGO_GRAY8_BITMAP   6
		if ((signed)nLen>0)
		{
			if (this->pBuf != NULL)
				delete[]this->pBuf;
			this->pBuf = new BYTE[nLen];
			int nLentemp;
			if (this->m_intBits == 1)
			{
				nLentemp = ::GetGlyphOutline(pdc->GetSafeHdc(), chartemp, this->m_intBits, &glpm, nLen, pBuf, &mmat2);


				this->charLineW = (glpm.gmBlackBoxX / 32 + (glpm.gmBlackBoxX % 32 == 0 ? 0 : 1)) * 4;
				this->FormBitmapInfo(glpm.gmBlackBoxX, glpm.gmBlackBoxY, this->m_intBits);
				if (nLentemp != nLen)
				{
					this->m_strStatus = "������󣡲�֧�֣�";
				}
				else
				{
					this->m_strStatus = "������";
				}
			}
			else
			{
				nLentemp = ::GetGlyphOutline(pdc->GetSafeHdc(), chartemp, this->m_intBits + 2, &glpm, nLen, pBuf, &mmat2);

				this->charLineW = (glpm.gmBlackBoxX / 4 + (glpm.gmBlackBoxX % 4 == 0 ? 0 : 1)) * 4;
				this->FormBitmapInfo(glpm.gmBlackBoxX, glpm.gmBlackBoxY, this->m_intBits);
				if (nLentemp != nLen)
				{
					this->m_strStatus = "������󣡲�֧�֣�";
				}
				else
				{
					this->m_strStatus = "������";
				}

			}

			this->m_intPixX = glpm.gmBlackBoxX;
			this->m_intPixY = glpm.gmBlackBoxY;
			//TRACE("x is %d,y is %d\n",glpm.gmBlackBoxX,glpm.gmBlackBoxY);
			this->UpdateData(FALSE);

			this->ShowFontChar(pdc);
			this->m_intScrollHPos = 0;
			this->m_intScrollVPos = 0;
			this->ShowVHScrollBar();




			pdc->SelectObject(poldfont);
			newfont.DeleteObject();
			this->GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(1);


		}
		else
		{
			this->m_strStatus = "������󣡲�֧�֣�";
			this->UpdateData(0);
		}
	}
}

void CFontsViewDlg::FormBitmapInfo(int nWidth, int nHeight, int nBits)
{
	if (this->pbmpinfo != NULL)
		delete[]this->pbmpinfo;
	this->pbmpinfo = (LPBITMAPINFO)(new BYTE[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*BITSTABLE[nBits - 1]]);
	this->pbmpinfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	this->pbmpinfo->bmiHeader.biWidth = nWidth;
	this->pbmpinfo->bmiHeader.biHeight = -nHeight;
	this->pbmpinfo->bmiHeader.biPlanes = 1;
	this->pbmpinfo->bmiHeader.biBitCount = nBits == 1 ? 1 : 8;
	this->pbmpinfo->bmiHeader.biCompression = BI_RGB;
	this->pbmpinfo->bmiHeader.biSizeImage = 0;
	this->pbmpinfo->bmiHeader.biXPelsPerMeter = 0;
	this->pbmpinfo->bmiHeader.biYPelsPerMeter = 0;
	this->pbmpinfo->bmiHeader.biClrUsed = BITSTABLE[nBits - 1];
	this->pbmpinfo->bmiHeader.biClrImportant = BITSTABLE[nBits - 1];
	RGBQUAD* pquad = (new RGBQUAD[BITSTABLE[nBits - 1]]);
	if (nBits == 1)
	{
		if (this->m_bCheckReverse == false)
		{
			(*pquad).rgbRed = 255;
			(*pquad).rgbGreen = 255;
			(*pquad).rgbBlue = 255;
			(*pquad).rgbReserved = 0;
			(*(pquad + 1)).rgbRed = 0;
			(*(pquad + 1)).rgbGreen = 0;
			(*(pquad + 1)).rgbBlue = 0;
			(*(pquad + 1)).rgbReserved = 0;
		}
		else
		{
			(*pquad).rgbRed = 0;
			(*pquad).rgbGreen = 0;
			(*pquad).rgbBlue = 0;
			(*pquad).rgbReserved = 0;
			(*(pquad + 1)).rgbRed = 255;
			(*(pquad + 1)).rgbGreen = 255;
			(*(pquad + 1)).rgbBlue = 255;
			(*(pquad + 1)).rgbReserved = 0;

		}
	}
	else
	{
		if (this->m_bCheckReverse == false)
		{
			for (int i = 0;i<BITSTABLE[nBits - 1];i++)
			{
				(*(pquad + i)).rgbRed = (*(pquad + i)).rgbGreen = (*(pquad + i)).rgbBlue = 255 - 255 * i / (BITSTABLE[nBits - 1] - 1);
				(*(pquad + i)).rgbReserved = 0;

			}
		}
		else
		{
			for (int i = 0;i<BITSTABLE[nBits - 1];i++)
			{
				(*(pquad + i)).rgbRed = (*(pquad + i)).rgbGreen = (*(pquad + i)).rgbBlue = 255 * i / (BITSTABLE[nBits - 1] - 1);

				(*(pquad + i)).rgbReserved = 0;

			}

		}
	}
	memcpy(&this->pbmpinfo->bmiColors, pquad, sizeof(RGBQUAD)*BITSTABLE[nBits - 1]);
	delete[]pquad;
}

void CFontsViewDlg::ShowFontChar(CDC* pdc)
{
	if (this->pBuf != NULL)
	{
		CRect rect;
		this->GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(&rect);
		CDC memdc;
		memdc.CreateCompatibleDC(pdc);
		CBitmap nbitmap, *poldbitmap;
		nbitmap.CreateCompatibleBitmap(pdc, rect.Width(), rect.Height());
		poldbitmap = memdc.SelectObject(&nbitmap);
		if (this->m_bCheckReverse == false)
			memdc.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));
		::StretchDIBits(memdc.m_hDC, -this->m_intScrollHPos, -this->m_intScrollVPos, this->m_intPixX, this->m_intPixY, 0, 0, this->m_intPixX, this->m_intPixY, this->pBuf, this->pbmpinfo, DIB_RGB_COLORS, SRCCOPY);

		pdc->BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);
		memdc.DeleteDC();

	}
}

void CFontsViewDlg::ShowVHScrollBar(void)
{
	CRect rect;
	GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(&rect);
	if (rect.Width()<this->m_intPixX)
	{
		SCROLLINFO info;
		info.cbSize = sizeof(SCROLLINFO);
		info.fMask = SIF_ALL;
		info.nMin = 0;
		info.nMax = this->m_intPixX - rect.Width() + 50;
		info.nPage = 50;
		info.nPos = 0;
		info.nTrackPos = 10;



		this->m_ctlScrollH.SetScrollInfo(&info);
		this->m_ctlScrollH.SetScrollPos(this->m_intScrollHPos);
		this->m_ctlScrollH.EnableScrollBar(ESB_ENABLE_BOTH);
		this->m_ctlScrollH.ShowWindow(SW_SHOW);
	}
	else
		this->m_ctlScrollH.ShowWindow(SW_HIDE);
	if (rect.Height()<this->m_intPixY)
	{
		SCROLLINFO info;
		info.cbSize = sizeof(SCROLLINFO);
		info.fMask = SIF_ALL;
		info.nMin = 0;
		info.nMax = this->m_intPixY - rect.Height() + 50;
		info.nPage = 50;
		info.nPos = 0;
		info.nTrackPos = 10;
		this->m_ctlScrollV.SetScrollInfo(&info);
		this->m_ctlScrollV.SetScrollPos(this->m_intScrollHPos);
		this->m_ctlScrollV.EnableScrollBar(ESB_ENABLE_BOTH);
		this->m_ctlScrollV.ShowWindow(SW_SHOW);
	}
	else
		this->m_ctlScrollV.ShowWindow(SW_HIDE);

}

void CFontsViewDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (this->pbmpinfo != NULL)
		delete[]this->pbmpinfo;
	if (this->pfileinfo != NULL)
		delete[]this->pfileinfo;
	if (this->pBuf != NULL)
		delete[]this->pBuf;

	CDialog::OnClose();
}

void CFontsViewDlg::FormFileHeader(int nWidth, int nHeight, int nBits)
{


	if (this->pfileinfo != NULL)
		delete[]this->pfileinfo;
	this->pfileinfo = (LPBITMAPFILEHEADER)new BYTE[sizeof(BITMAPFILEHEADER)];
	this->pfileinfo->bfType = *(WORD*)(&"BM");
	this->pfileinfo->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*BITSTABLE[nBits - 1];
	this->pfileinfo->bfSize = this->pfileinfo->bfOffBits + this->charLineW*nHeight;


}

void CFontsViewDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (pScrollBar == &this->m_ctlScrollH)
	{

		int minpos;
		int maxpos;
		pScrollBar->GetScrollRange(&minpos, &maxpos);
		maxpos = pScrollBar->GetScrollLimit();

		// Get the current position of scroll box.
		int curpos = pScrollBar->GetScrollPos();

		// Determine the new position of scroll box.
		switch (nSBCode)
		{
		case SB_LEFT:      // Scroll to far left.
			curpos = minpos;
			break;

		case SB_RIGHT:      // Scroll to far right.
			curpos = maxpos;
			break;

		case SB_ENDSCROLL:   // End scroll.
			break;

		case SB_LINELEFT:      // Scroll left.
			if (curpos > minpos)
				curpos--;
			break;

		case SB_LINERIGHT:   // Scroll right.
			if (curpos < maxpos)
				curpos++;
			break;

		case SB_PAGELEFT:    // Scroll one page left.
		{
			// Get the page size. 
			SCROLLINFO   info;
			pScrollBar->GetScrollInfo(&info, SIF_ALL);

			if (curpos > minpos)
				curpos = max(minpos, curpos - (int)info.nPage);
		}
		break;

		case SB_PAGERIGHT:      // Scroll one page right.
		{
			// Get the page size. 
			SCROLLINFO   info;
			pScrollBar->GetScrollInfo(&info, SIF_ALL);

			if (curpos < maxpos)
				curpos = min(maxpos, curpos + (int)info.nPage);
		}
		break;

		case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
			curpos = nPos;      // of the scroll box at the end of the drag operation.
			break;

		case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
			curpos = nPos;     // position that the scroll box has been dragged to.
			break;
		}

		// Set the new position of the thumb (scroll box).
		pScrollBar->SetScrollPos(curpos);
		this->m_intScrollHPos = curpos;
		this->OnPaint();

	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CFontsViewDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (pScrollBar == &this->m_ctlScrollV)
	{

		int minpos;
		int maxpos;
		pScrollBar->GetScrollRange(&minpos, &maxpos);
		maxpos = pScrollBar->GetScrollLimit();

		// Get the current position of scroll box.
		int curpos = pScrollBar->GetScrollPos();

		// Determine the new position of scroll box.
		switch (nSBCode)
		{
		case SB_LEFT:      // Scroll to far left.
			curpos = minpos;
			break;

		case SB_RIGHT:      // Scroll to far right.
			curpos = maxpos;
			break;

		case SB_ENDSCROLL:   // End scroll.
			break;

		case SB_LINELEFT:      // Scroll left.
			if (curpos > minpos)
				curpos--;
			break;

		case SB_LINERIGHT:   // Scroll right.
			if (curpos < maxpos)
				curpos++;
			break;

		case SB_PAGELEFT:    // Scroll one page left.
		{
			// Get the page size. 
			SCROLLINFO   info;
			pScrollBar->GetScrollInfo(&info, SIF_ALL);

			if (curpos > minpos)
				curpos = max(minpos, curpos - (int)info.nPage);
		}
		break;

		case SB_PAGERIGHT:      // Scroll one page right.
		{
			// Get the page size. 
			SCROLLINFO   info;
			pScrollBar->GetScrollInfo(&info, SIF_ALL);

			if (curpos < maxpos)
				curpos = min(maxpos, curpos + (int)info.nPage);
		}
		break;

		case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
			curpos = nPos;      // of the scroll box at the end of the drag operation.
			break;

		case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
			curpos = nPos;     // position that the scroll box has been dragged to.
			break;
		}

		// Set the new position of the thumb (scroll box).
		pScrollBar->SetScrollPos(curpos);
		this->m_intScrollVPos = curpos;

		this->OnPaint();

	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CFontsViewDlg::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strfile;
	CFileDialog cfd(FALSE, ".bmp", "δ����.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "BMP files(*.bmp)|*.bmp|All files(*.*)|*.*||", this);
	if (cfd.DoModal() == IDOK)
	{
		strfile = cfd.GetPathName();

	}
	if (strfile.IsEmpty())
	{
		::AfxMessageBox("��������Ҫ������ļ�����");
		return;
	}
	CFile cf;
	cf.Open(strfile, CFile::modeCreate | CFile::modeWrite);
	this->FormFileHeader(this->m_intPixX, this->m_intPixY, this->m_intBits);
	cf.Write(this->pfileinfo, sizeof(BITMAPFILEHEADER));
	cf.Write(this->pbmpinfo, sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*BITSTABLE[this->m_intBits - 1]);
	cf.Write(this->pBuf, this->charLineW*this->m_intPixY);
	cf.Close();

}

HBRUSH CFontsViewDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_STATUS)
	{
		if (this->m_strStatus.Compare("������") != 0)
			pDC->SetTextColor(RGB(255, 0, 0));

	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CFontsViewDlg::OnEnChangeEditPixx()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
void CFontsViewDlg::Paint()
{
	CDC* pDC = this->m_ctlDisplay.GetDC();
	CFont curFont;
	curFont.CreateFont(300, 0, this->m_intAngle, 0, this->m_intBold, this->m_bCheckItalic, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, m_strFontName);
	CFont* pOldFont = (CFont*)pDC->SelectObject(&curFont);

	TEXTMETRIC tm;
	int x = 0, y = 0;
	RedrawWindow();
	pDC->GetTextMetrics(&tm);
	CDC::FromHandle((HDC)pDC)->DeleteDC();
	DrawTTFOutline(pDC, '��', 0, 100, tm.tmAscent);
	//DrawTTFOutline(pDC, '��', 120, 100, tm.tmAscent);
	//DrawTTFOutline(pDC, '��', 240, 100, tm.tmAscent);
	//DrawTTFOutline(pDC, '', 360, 100, tm.tmAscent);

	pDC->SelectObject(pOldFont);
}

void CFontsViewDlg::DrawTTFOutline(CDC* pDC, UINT uChar, int x, int y, int ascent)
{
	UINT chartemp;
	BYTE temp;
	GLYPHMETRICS gm;
	MAT2 mat;
	memset(&mat, 0, sizeof(mat));
	mat.eM11.value = 1;
	mat.eM22.value = 1;
	DWORD dwMemSize; //�����ڴ�ռ��С 
	HGLOBAL hMem; //�ڴ��� 
	LPSTR pdwMemBits; //������ڴ� ����������Ϣ�ͱ���������ڴ���
	temp = this->m_strEntered.GetAt(0);
	if (temp >= 128)
	{
		chartemp = ((UINT)temp) << 8;
		temp = this->m_strEntered.GetAt(1);
		chartemp += temp;
	}
	else
		chartemp = temp;
					  //�����ڴ�մ� 
	dwMemSize = pDC->GetGlyphOutline(chartemp, GGO_NATIVE, &gm, 0, NULL, &mat);
	hMem = GlobalAlloc(GHND, dwMemSize);
	if (hMem == NULL)
	{
		TRACE("�����ڴ�ʧ��!\n");
		return;
	}
	//�����ڴ� ��Ϊ����Ҫ��ȡ����ڴ��е����� 
	pdwMemBits = (LPSTR)GlobalLock(hMem);
	if (pdwMemBits == NULL)
	{
		TRACE("�����ڴ�ʧ��!\n");
		return;
	}
	//��ȡ����������Ϣ 
	if (pDC->GetGlyphOutline(chartemp, GGO_NATIVE, &gm, dwMemSize, pdwMemBits, &mat) != dwMemSize)
	{
		TRACE("��ȡ����������Ϣʧ�ܣ�\n");
		return;
	}

	//����pDC����׼������uChar 
	CBrush curBrush(RGB(0, 0, 0));
	CBrush* pOldBrush = pDC->SelectObject(&curBrush);
	CPoint oldOrg = pDC->GetViewportOrg();
	pDC->OffsetViewportOrg(x , y + ascent/1.5);

	//���������ȡ���������εĴ��� 
	LPTTPOLYGONHEADER lpHeader;
	LPTTPOLYGONHEADER lpStart;
	LPTTPOLYCURVE lpCurve;
	int nOutlinePt[50]; //ÿ��������տ��е�ת�۵��� 
	int nTotal = 0; //ת�۵�Ĺ���. 
	int nInOutline; //��ǰ��������е�ת�۵��� 
	int nOutline = 0; //���������ж����ķ�տ����Ŀ 
	int nFirstOutline; //��һ���ߵ���ʼλ�� 
	int i;
	float yB = 0, xB = 0, yA = 0, xA = 0, yC = 0, xC = 0;
	POINTFX spline[3];

	lpHeader = (LPTTPOLYGONHEADER)pdwMemBits;
	lpStart = lpHeader;
	while ((DWORD)lpHeader < (DWORD)(((LPSTR)lpStart) + dwMemSize))//ѭ��ֱ�������ڴ��е���������,�����ַ���Ϣ
	{
		if (lpHeader->dwType == TT_POLYGON_TYPE)
		{
			nInOutline = 0;
			//�õ���һ��������ߵĵ�ַ 
			lpCurve = (LPTTPOLYCURVE)(lpHeader + 1);
			nFirstOutline = nTotal;

			while ((DWORD)lpCurve<(DWORD)(((LPSTR)lpHeader) + lpHeader->cb))//ѭ��ֱ��ȡ�굱ǰ����еĵ�
			{
				//ֱ�� 
				if (lpCurve->wType == TT_PRIM_LINE)
				{
					for (i = 0; i<lpCurve->cpfx; i++)
					{
						Points[nTotal].x = FixedToInt(lpCurve->apfx[i].x);
						Points[nTotal].y = FixedToInt(lpCurve->apfx[i].y);
						nTotal++;
						nInOutline++;
					}
				}
				//���� (������һ������B������ 
				else if (lpCurve->wType == TT_PRIM_QSPLINE)
				{

						spline[0] = *(LPPOINTFX)((LPSTR)lpCurve - sizeof(POINTFX));

						for (i = 0; i<lpCurve->cpfx;)
						{
							spline[1] = lpCurve->apfx[i++];
						if (i == (lpCurve->cpfx - 1))
						{
					
							spline[2] = lpCurve->apfx[i++];
						}
						else
						{
							spline[2].x = fxDiv2(lpCurve->apfx[i - 1].x, lpCurve->apfx[i].x);
							spline[2].y = fxDiv2(lpCurve->apfx[i - 1].y, lpCurve->apfx[i].y);
						}
						const float Chord = 0.5;//��Ϊ�趨�ҳ�ֵ 
						float t = 0;//�� A �㿪ʼɨ�� 
						xA= FixedToInt(spline[0].x);
						yA= FixedToInt(spline[0].y);
						yB= FixedToInt(spline[1].y);
						xB= FixedToInt(spline[1].x);
						yC= FixedToInt(spline[2].y);
						xC= FixedToInt(spline[2].x);
						while (t<1)
						{
							//����ǰ����뼯���� contour[k]�� 
							Points[nTotal].x =  (xA - 2 * xB + xC)*t*t + 2 * (xB - xA)*t + xA;
							Points[nTotal].y =  (yA - 2 * yB + yC)*t*t + 2 * (yB - yA)*t + yA;
							//contour[k].Add(pMyPoint);
							//��  
							t += 0.5*Chord / sqrt(pow(t*(xA + xC - 2 * xB) + xB - xA, 2) + pow(t*(yA + yC - 2 * yB) + yB - yA, 2));
						}
						nTotal++;
						nInOutline += 1;

						spline[0] = spline[2];
					}
				}
				else
					; //����ֱ�ߺ����߻���ʲô���أ�����

					  //ָ����һ���� 
				lpCurve = (LPTTPOLYCURVE)&(lpCurve->apfx[i]);
			}

			//����һ�����յ�ǰ���. 
			Points[nTotal].x = FixedToInt(lpHeader->pfxStart.x);
			Points[nTotal].y = FixedToInt(lpHeader->pfxStart.y);
			nInOutline++;
			nTotal++;
			Points[nTotal].x = Points[nFirstOutline].x;
			Points[nTotal].y = Points[nFirstOutline].y;
			nInOutline++;
			nTotal++;
			nOutlinePt[nOutline++] = nInOutline;

			//ָ����һ�����. 
			lpHeader = (LPTTPOLYGONHEADER)(((LPSTR)lpHeader) + lpHeader->cb);
		}
		else
			; //���� 
	}

	for (i = 0; i < nTotal; i++)
		Points[i].y = 0 - Points[i].y;

	//���� ��ȫ���Ѿ����浽Points���� ���ڸ������ǡ��� 
	i = 0;
	pDC->SelectStockObject(BLACK_PEN);
	for (int a = 0; a<nOutline; a++)
	{
		pDC->MoveTo(Points[i]);
		for (int b = 0; b<nOutlinePt[a]; b++)
		{
			pDC->LineTo(Points[i]);
			i++;
		}
	}


	pDC->SetViewportOrg(oldOrg.x, oldOrg.y);
	pDC->SelectObject(pOldBrush);
	GlobalUnlock(hMem);
	GlobalFree(hMem);
}

int CFontsViewDlg::FixedToInt(FIXED f)
{
	if (f.fract >= 0x8000)
		return(f.value + 1);
	else
		return(f.value);
	//return value;
}

FIXED CFontsViewDlg::fxDiv2(FIXED fxVal1, FIXED fxVal2)
{
	//long l;

	//l = (*((long far *)&(fxVal1)) + *((long far *)&(fxVal2))) / 2;
	//return(*(FIXED *)&l);
	long l;
	l = (*((long far *)&(fxVal1)) + *((long far *)&(fxVal2))) / 2;
	return(*(FIXED *)&l);
}


void CFontsViewDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}
