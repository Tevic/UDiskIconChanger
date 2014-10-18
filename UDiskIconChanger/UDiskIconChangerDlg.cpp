
// UDiskIconChangerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDiskIconChanger.h"
#include "UDiskIconChangerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUDiskIconChangerDlg �Ի���




CUDiskIconChangerDlg::CUDiskIconChangerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDiskIconChangerDlg::IDD, pParent)
{
	strPath=L"";
	strDriverName=L"";
	m_arrayDriveNames.RemoveAll();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUDiskIconChangerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUDiskIconChangerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ABOUT, &CUDiskIconChangerDlg::OnBnClickedAbout)
	ON_BN_CLICKED(IDC_BUTTON_PATH, &CUDiskIconChangerDlg::OnBnClickedButtonPath)
	ON_BN_CLICKED(IDC_BUTTON_REPLACE, &CUDiskIconChangerDlg::OnBnClickedButtonReplace)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE, &CUDiskIconChangerDlg::OnBnClickedButtonRestore)
	ON_EN_CHANGE(IDC_EDIT_DRIVE, &CUDiskIconChangerDlg::OnEnChangeEditDrive)
	ON_CBN_SELCHANGE(IDC_COMBO_DRIVERS, &CUDiskIconChangerDlg::OnCbnSelchangeComboDrivers)
END_MESSAGE_MAP()


// CUDiskIconChangerDlg ��Ϣ�������

BOOL CUDiskIconChangerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, TRUE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	ReloadDriver();
	int nDriverCount=m_arrayDriveNames.GetSize();
	if (nDriverCount==0)
	{
		MessageBox(_T("δ��⵽U�̣������˳���"),_T("����"),MB_OK | MB_ICONERROR);
		//ExitProcess(1);
		SendMessage(WM_CLOSE,NULL,NULL);
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CUDiskIconChangerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUDiskIconChangerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CUDiskIconChangerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUDiskIconChangerDlg::OnBnClickedAbout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CUDiskIconChangerDlg::OnBnClickedButtonPath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�����ļ��Ի���
	CString strFilter = _T("ͼ���ļ�(*.ico)|*.ico||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | 
		OFN_OVERWRITEPROMPT, strFilter);
	dlg.m_ofn.lpstrTitle = _T("��ѡ��ͼ��");

	if(dlg.DoModal() == IDOK)
	{
		//���Դ�ļ�·��
		strPath = dlg.GetPathName();
		SetDlgItemText(IDC_EDIT_PATH, strPath);
	}
}


void CUDiskIconChangerDlg::GetMobileDrive()
{
	CStringArray arrayDriveNames;
	DWORD id = GetLogicalDrives();
	for (int i = 1; i < 26; i++)
	{  
		if ((id & (1 << i)) != 0)  
		{   
			CString strDrv = CString(char('A' + i)) + ":";  
			if (GetDriveType(strDrv) == DRIVE_REMOVABLE)    
			{
				m_arrayDriveNames.Add(strDrv);
			}  
		} 
	} 
}

//�жϵ�ǰ�̷��Ƿ����
BOOL CUDiskIconChangerDlg::IsLogicalDriverExist(CString driverName)
{
	return GetDriveType(driverName)!=DRIVE_NO_ROOT_DIR;
}

//���������̷�
void CUDiskIconChangerDlg::ReloadDriver()
{
	//��ȡ����ʾU���̷�
	m_arrayDriveNames.RemoveAll();
	GetMobileDrive();
	int nDriverCount=m_arrayDriveNames.GetSize();
	((CComboBox*)GetDlgItem(IDC_COMBO_DRIVERS))->ResetContent();
	for (int i = 0; i < nDriverCount; i++)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_DRIVERS))->AddString(m_arrayDriveNames.GetAt(i));
	}
}


void CUDiskIconChangerDlg::OnBnClickedButtonReplace()
{
	if((_T("")!=strPath)&&(_T("")!=strDriverName)&&(IsLogicalDriverExist(strDriverName)))
	{
		// TODO: �ڴ���ӿؼ�֪ͨ����������
		//step1:
		//����ͼ�굽����,����ΪUDisk.ico,��������Ϊϵͳ����
		CString strIconPath,strIniFile;
		strIconPath=strDriverName+L"\\UDisk.ico";
		strIniFile=strDriverName+L"\\Autorun.inf";
		SetFileAttributes(strIconPath,FILE_ATTRIBUTE_NORMAL);
		CopyFile(strPath,strIconPath,FALSE);
		SetFileAttributes(strIconPath,FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);

		//step2:
		//�����ļ�Autorun.inf,��д��,����Ϊϵͳ����
		HANDLE hFile=CreateFile(strIniFile,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ,NULL,
			CREATE_ALWAYS,FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN,0);

		//step3:
		//д��Autorun.inf��Ϣ
		CHAR szWrite[]="[Autorun]\r\nIcon=UDisk.ico";
		DWORD dwWrite;
		WriteFile(hFile,szWrite,strlen(szWrite),&dwWrite,NULL);
		CloseHandle(hFile);//�رվ���������ļ�

		//step4:
		//��ʾ��Ϣ
		MessageBox(_T("U��ͼ���滻�ɹ�������U�����²��ϼ��ɿ�����"),_T("�滻�ɹ�"),MB_OK | MB_ICONINFORMATION);
	}
	else if(!IsLogicalDriverExist(strDriverName))
	{
		MessageBox(_T("��⵽��ǰ�������Ƴ��������������̷���"),_T("�̷�����"),MB_OK | MB_ICONWARNING);
		ReloadDriver();
	}
	else if(_T("")==strPath)
		MessageBox(_T("δѡ��ͼ�꣬��ѡ��ͼ������滻��"),_T("��ѡ��ͼ�꣡"),MB_OK | MB_ICONEXCLAMATION);
	else
		MessageBox(_T("��ѡ��U�̺���ִ���滻��"),_T("��ѡ��U�̣�"),MB_OK | MB_ICONEXCLAMATION);
}



void CUDiskIconChangerDlg::OnBnClickedButtonRestore()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if((strDriverName!=L"")&&(IsLogicalDriverExist(strDriverName)))
	{
		DeleteFile(strDriverName+"\\Autorun.inf");
		DeleteFile(strDriverName+"\\UDisk.ico");
		MessageBox(_T("U���ѻָ�Ĭ��ͼ�꣬����U�����²��ϼ��ɣ�"),_T("��ʾ��Ϣ"),MB_OK | MB_ICONINFORMATION);
	}
	else if(!IsLogicalDriverExist(strDriverName))
	{
		MessageBox(_T("��⵽��ǰ�������Ƴ��������������̷���"),_T("�̷�����"),MB_OK | MB_ICONWARNING);
		ReloadDriver();
	}
	else
		MessageBox(_T("��ѡ��U�̺���ִ�л�ԭ��"),_T("��ѡ��U�̣�"),MB_OK | MB_ICONEXCLAMATION);
}


void CUDiskIconChangerDlg::OnEnChangeEditDrive()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CUDiskIconChangerDlg::OnCbnSelchangeComboDrivers()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ��ǰѡ���̷�
	GetDlgItemText(IDC_COMBO_DRIVERS,strDriverName);
}
