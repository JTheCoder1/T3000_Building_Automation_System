#pragma once
#include "afxwin.h"

#include "../msflexgrid1.h"
#include "../globle_function.h"
#include "../Weekly_Routines.h"
#include "../Annual_Routines.h"
#include "../Config_Routines.h"
#include "../global_variable_extern.h"

#include "../MainFrm.h"



#define FLEXGRID_CELL_COLOR						13421772
#define FLEXGRID_CELL_GRAY_COLOR				13421772	

#define  DATATIME_TIMER 1

typedef struct Subnetwork						
{						
	CString	m_coolingSet;				
	CString	m_heatingSet;				
	CString	m_setpoint; 				
	CString	m_roomTemper;				
	int	    m_mode;				
	CString	m_outputState;				
	CString	m_nightHeating;				
	CString	m_nightCooling;				
	int	m_tstatProduct;				
	CString m_modbusaddr;					
}subnetwork;



// CDialogCM5 form view

class CDialogCM5 : public CFormView
{
	DECLARE_DYNCREATE(CDialogCM5)

protected:
public:
	CDialogCM5();           // protected constructor used by dynamic creation
	virtual ~CDialogCM5();

public:
	enum { IDD = IDD_DIALOG_CM5 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


public:
	int m_IDaddressCM5;
	UINT m_nSerialNumCM5;
	float m_firmwareVersionCM5;
	int m_hardware_versionCM5;
	CString m_strDateCM5;
	CString m_strTime;
	CString m_heating;
	CString m_cooling;
	CString m_coating;
	CString m_result;
	CComboBox m_combo_prioritymode;
	int m_priorityinterval;
	CString m_countprioritytime;
	CMsflexgrid m_Output_GridCM5_;
	CMsflexgrid m_msflexgrid_input;
	CMsflexgrid m_msflexgridoutput;
	CEdit m_edit_input;
	CEdit m_edit_output;
	CComboBox m_combobox2_input;
	CString m_static_datetime;
	CString m_combo2_cstring;

public://events
	afx_msg void OnBnClickedButtonSyncwithpc();
	afx_msg void OnBnClickedButtonweeklyschedule();
	afx_msg void OnBnClickedButtonannualschedule();
	afx_msg void OnBnClickedButtonidschedule();
	afx_msg void OnBnClickedButtoninputtype();
	afx_msg void OnEnKillfocusEditInput();
	afx_msg void OnEnKillfocusEditoutput();
public://messages override
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);


public:
	void Fresh();
	void ShowDialogData();
	BOOL& GetData();

public:

	vector<subnetwork>_subnetwork;
	subnetwork m_subetwork;
private:
	int m_switch;
	int m_cellrow;
	int m_cellcol;
	int m_cellrowout;
	int m_cellcolout;
	int num;
	
	DECLARE_EVENTSINK_MAP()
	void ClickInputMsflexgrid();
	void DblClickInputMsflexgrid();
	void ClickOutputMsflexgrid();
	void DblClickOutputMsflexgrid();
	void AddDatabase(CString m_database,CString m_no,CString m_name);
	CString ReadDatabase(CString m_database,CString m_no);
	void UpdateDatabase(CString m_database,CString m_num,CString m_name);

	void JudgeTableExist(CString strtable,CString strsql);
	
};


