
// UDiskIconChangerDlg.h : 头文件
//

#pragma once


// CUDiskIconChangerDlg 对话框
class CUDiskIconChangerDlg : public CDialogEx
{
// 构造
public:
	CUDiskIconChangerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UDISKICONCHANGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedButtonPath();

	CString strPath;
	CString strDriverName;
	CStringArray m_arrayDriveNames;
	void GetMobileDrive(void);
	BOOL IsLogicalDriverExist(CString driverName);
	void ReloadDriver();
	afx_msg void OnBnClickedButtonReplace();
	afx_msg void OnBnClickedButtonRestore();
	afx_msg void OnEnChangeEditDrive();
	afx_msg void OnCbnSelchangeComboDrivers();
};
