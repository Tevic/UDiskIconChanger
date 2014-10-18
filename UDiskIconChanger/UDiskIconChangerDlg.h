
// UDiskIconChangerDlg.h : ͷ�ļ�
//

#pragma once


// CUDiskIconChangerDlg �Ի���
class CUDiskIconChangerDlg : public CDialogEx
{
// ����
public:
	CUDiskIconChangerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UDISKICONCHANGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
