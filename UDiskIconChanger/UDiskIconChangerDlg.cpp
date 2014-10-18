
// UDiskIconChangerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDiskIconChanger.h"
#include "UDiskIconChangerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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


// CUDiskIconChangerDlg 对话框




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


// CUDiskIconChangerDlg 消息处理程序

BOOL CUDiskIconChangerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, TRUE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	ReloadDriver();
	int nDriverCount=m_arrayDriveNames.GetSize();
	if (nDriverCount==0)
	{
		MessageBox(_T("未检测到U盘，程序将退出！"),_T("错误"),MB_OK | MB_ICONERROR);
		//ExitProcess(1);
		SendMessage(WM_CLOSE,NULL,NULL);
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUDiskIconChangerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUDiskIconChangerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUDiskIconChangerDlg::OnBnClickedAbout()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CUDiskIconChangerDlg::OnBnClickedButtonPath()
{
	// TODO: 在此添加控件通知处理程序代码
	//创建文件对话框
	CString strFilter = _T("图标文件(*.ico)|*.ico||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | 
		OFN_OVERWRITEPROMPT, strFilter);
	dlg.m_ofn.lpstrTitle = _T("请选择图标");

	if(dlg.DoModal() == IDOK)
	{
		//获得源文件路径
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

//判断当前盘符是否存在
BOOL CUDiskIconChangerDlg::IsLogicalDriverExist(CString driverName)
{
	return GetDriveType(driverName)!=DRIVE_NO_ROOT_DIR;
}

//重新载入盘符
void CUDiskIconChangerDlg::ReloadDriver()
{
	//获取并显示U盘盘符
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
		// TODO: 在此添加控件通知处理程序代码
		//step1:
		//复制图标到优盘,更名为UDisk.ico,设置属性为系统隐藏
		CString strIconPath,strIniFile;
		strIconPath=strDriverName+L"\\UDisk.ico";
		strIniFile=strDriverName+L"\\Autorun.inf";
		SetFileAttributes(strIconPath,FILE_ATTRIBUTE_NORMAL);
		CopyFile(strPath,strIconPath,FALSE);
		SetFileAttributes(strIconPath,FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);

		//step2:
		//创建文件Autorun.inf,并写入,属性为系统隐藏
		HANDLE hFile=CreateFile(strIniFile,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ,NULL,
			CREATE_ALWAYS,FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN,0);

		//step3:
		//写入Autorun.inf信息
		CHAR szWrite[]="[Autorun]\r\nIcon=UDisk.ico";
		DWORD dwWrite;
		WriteFile(hFile,szWrite,strlen(szWrite),&dwWrite,NULL);
		CloseHandle(hFile);//关闭句柄，保存文件

		//step4:
		//提示信息
		MessageBox(_T("U盘图标替换成功，拔下U盘重新插上即可看到！"),_T("替换成功"),MB_OK | MB_ICONINFORMATION);
	}
	else if(!IsLogicalDriverExist(strDriverName))
	{
		MessageBox(_T("检测到当前磁盘已移除，将重新载入盘符！"),_T("盘符错误！"),MB_OK | MB_ICONWARNING);
		ReloadDriver();
	}
	else if(_T("")==strPath)
		MessageBox(_T("未选择图标，请选择图标后再替换！"),_T("请选择图标！"),MB_OK | MB_ICONEXCLAMATION);
	else
		MessageBox(_T("请选择U盘后再执行替换！"),_T("请选择U盘！"),MB_OK | MB_ICONEXCLAMATION);
}



void CUDiskIconChangerDlg::OnBnClickedButtonRestore()
{
	// TODO: 在此添加控件通知处理程序代码
	if((strDriverName!=L"")&&(IsLogicalDriverExist(strDriverName)))
	{
		DeleteFile(strDriverName+"\\Autorun.inf");
		DeleteFile(strDriverName+"\\UDisk.ico");
		MessageBox(_T("U盘已恢复默认图标，拔下U盘重新插上即可！"),_T("提示信息"),MB_OK | MB_ICONINFORMATION);
	}
	else if(!IsLogicalDriverExist(strDriverName))
	{
		MessageBox(_T("检测到当前磁盘已移除，将重新载入盘符！"),_T("盘符错误！"),MB_OK | MB_ICONWARNING);
		ReloadDriver();
	}
	else
		MessageBox(_T("请选择U盘后在执行还原！"),_T("请选择U盘！"),MB_OK | MB_ICONEXCLAMATION);
}


void CUDiskIconChangerDlg::OnEnChangeEditDrive()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CUDiskIconChangerDlg::OnCbnSelchangeComboDrivers()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取当前选中盘符
	GetDlgItemText(IDC_COMBO_DRIVERS,strDriverName);
}
