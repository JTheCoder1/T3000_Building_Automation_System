// DialogCM5.cpp : implementation file
//

#include "stdafx.h"
#include "../T3000.h"
#include "DialogCM5.h"


//#ifndef _CM5DB

int timer = 3;
static BOOL  ifcreatedb = TRUE,initparam = TRUE; 

//#endif




// CDialogCM5

IMPLEMENT_DYNCREATE(CDialogCM5, CFormView)

CDialogCM5::CDialogCM5()
	: CFormView(CDialogCM5::IDD)
	, m_IDaddressCM5(0)
	, m_nSerialNumCM5(0)
	, m_firmwareVersionCM5(0)
	, m_hardware_versionCM5(0)
	, m_strDateCM5(_T(""))
	, m_strTime(_T(""))
	, m_heating(_T(""))
	, m_cooling(_T(""))
	, m_coating(_T(""))
	, m_result(_T(""))
	, m_priorityinterval(0)
	, m_countprioritytime(_T(""))
	, m_static_datetime(_T(""))
	, m_combo2_cstring(_T(""))

	,m_cellrow(1)
	,m_cellcol(1)
	,m_cellcolout(1)
	,m_cellrowout(1)
	,num(0)		
	,m_switch(0)

{

}

CDialogCM5::~CDialogCM5()
{

}

void CDialogCM5::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_IDaddressCM5);
	DDX_Text(pDX, IDC_EDIT_SERIAL, m_nSerialNumCM5);
	DDX_Text(pDX, IDC_EDIT_FIRMWARE, m_firmwareVersionCM5);
	DDX_Text(pDX, IDC_EDIT_HARDWARE, m_hardware_versionCM5);
	DDX_Text(pDX, IDC_EDIT_DATE, m_strDateCM5);
	DDX_Text(pDX, IDC_EDIT_TIME, m_strTime);
	DDX_Text(pDX, IDC_EDIT_HEAT, m_heating);
	DDX_Text(pDX, IDC_EDIT_COOL, m_cooling);
	DDX_Text(pDX, IDC_EDIT_COAST, m_coating);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_result);
	DDX_Control(pDX, IDC_COMBO_MODE, m_combo_prioritymode);
	DDX_Text(pDX, IDC_EDIT_DURATION, m_priorityinterval);
	DDX_Text(pDX, IDC_EDIT_TIMELEFT, m_countprioritytime);
	DDX_Control(pDX, IDC_ADDBUILDING_MSFLEXGRID, m_Output_GridCM5_);
	DDX_Control(pDX, IDC_INPUT_MSFLEXGRID, m_msflexgrid_input);
	DDX_Control(pDX, IDC_OUTPUT_MSFLEXGRID, m_msflexgridoutput);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_edit_input);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_edit_output);
	DDX_Control(pDX, IDC_COMBO_INPUTOUTPUT, m_combobox2_input);
	DDX_Text(pDX, IDC_STATIC_DATETIME, m_static_datetime);
	DDX_CBString(pDX, IDC_COMBO_INPUTOUTPUT, m_combo2_cstring);
}

BEGIN_MESSAGE_MAP(CDialogCM5, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogCM5::OnBnClickedButtonSyncwithpc)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogCM5::OnBnClickedButtonweeklyschedule)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialogCM5::OnBnClickedButtonannualschedule)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialogCM5::OnBnClickedButtonidschedule)
	ON_BN_CLICKED(IDC_BUTTON5, &CDialogCM5::OnBnClickedButtoninputtype)
	ON_EN_KILLFOCUS(IDC_EDIT_INPUT, &CDialogCM5::OnEnKillfocusEditInput)
	ON_EN_KILLFOCUS(IDC_EDIT_OUTPUT, &CDialogCM5::OnEnKillfocusEditoutput)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDialogCM5 diagnostics

#ifdef _DEBUG
void CDialogCM5::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDialogCM5::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}


#endif
#endif //_DEBUG

void CDialogCM5::Fresh()
{
	int start,end(0);
	start = clock();

	if (ifcreatedb)
	{	
		int star,en(0);
		star = clock();
		//检测CM5_INPUT数据库中的这个表是否存在
		CString temptable = _T("CM5_INPUT");
		CString tempsql = _T("create table CM5_INPUT(num TEXT,name TEXT)");
		JudgeTableExist(temptable,tempsql);

		temptable = _T("CM5_OUTPUT");
		tempsql = _T("create table CM5_OUTPUT(num TEXT,name TEXT)");
		JudgeTableExist(temptable,tempsql);
		ifcreatedb = FALSE;
		en = clock();
		int tem = en - star;//110
		TRACE(_T("create db = %d\n"),tem);


#if 1
		//CM5_INPUT显示纵标题
		CString str;	
		CString strdata;
		strdata = _T("CM5_INPUT");
		for(int i=1;i<=10;i++)
		{

			str.Format(_T("%d"),i);

			m_msflexgrid_input.put_TextMatrix(i,0,str);	 
			CString strtemp;
	//		strtemp = ReadDatabase(strdata,str);
			if (strtemp.IsEmpty())
			{	
				str = _T("Input ")+str;
				m_msflexgrid_input.put_TextMatrix(i,1,str);	
			}else
			{
				m_msflexgrid_input.put_TextMatrix(i,1,strtemp);	
			}

			m_msflexgrid_input.put_TextMatrix(i,5,_T("Default"));	 

		}

	
		str =_T("");
		for(int i=11;i<27;i++)																
		{

			str.Format(_T("%d"),i);
			m_msflexgrid_input.put_TextMatrix(i,0,str);
			CString strtemp;
//			strtemp = ReadDatabase(strdata,str);
			if (strtemp.IsEmpty())
			{	
				str = _T("Input ")+str;
				m_msflexgrid_input.put_TextMatrix(i,1,str);	
			}else
			{
				m_msflexgrid_input.put_TextMatrix(i,1,strtemp);	
			}
			
			//m_msflexgrid_input.put_TextMatrix(i,3,_T("Auto"));
			m_msflexgrid_input.put_TextMatrix(i,4,_T("On/Off"));
			m_msflexgrid_input.put_TextMatrix(i,5,_T("Default"));	




		}
#endif

#if 1
		//CM5_OUTPUT显示纵标题
		CString str_output;	
		CString m_cmouput;
		m_cmouput = _T("CM5_OUTPUT");
		for(int i=1;i<=10;i++)
		{

			str_output.Format(_T("%d"),i);
			m_msflexgridoutput.put_TextMatrix(i,0,str_output);	
			CString strtemp;
//			strtemp = ReadDatabase(m_cmouput,str_output);
			if (strtemp.IsEmpty())
			{	
				str_output = _T("OUTPUT ")+str_output;
				m_msflexgridoutput.put_TextMatrix(i,1,str_output);	
			}else
			{
				m_msflexgridoutput.put_TextMatrix(i,1,strtemp);	
			}

			//m_msflexgridoutput.put_TextMatrix(i,3,_T("Auto"));
			m_msflexgridoutput.put_TextMatrix(i,4,_T("On/Off"));
			m_msflexgridoutput.put_TextMatrix(i,5,_T("Default"));
			m_msflexgridoutput.put_Row(i);
			m_msflexgridoutput.put_Col(4);
			m_msflexgridoutput.put_CellBackColor(FLEXGRID_CELL_GRAY_COLOR);
		}
#endif






	}

	end = clock();
	int spendtime = (end - start);//1797
	TRACE(_T("Fresh()spend time=%d\n"),spendtime);
	
	SetTimer(DATATIME_TIMER,1000,NULL);

	start = clock();end = 0;
	ShowDialogData();
	end = clock();

	spendtime = (end - start);//0
	TRACE(_T("showDialogData()spend time=%d\n"),spendtime);
	

}


// CDialogCM5 message handlers

void CDialogCM5::OnBnClickedButtonSyncwithpc()
{
	// 		200	1	second
	// 		201	1	minute
	// 		202	1	hour
	// 		203	1	day
	// 		204	1	week, 0=Sunday; 1=Monday; and so on.
	// 		205	1	month
	// 		206	1	lower byte of the year, for example, here should be 98 in year 1998
	// 		207	1	higher byte of the year, for example, here should be 19 in the year 1998

	KillTimer(DATATIME_TIMER);
	//179 180 181 182
	CString tempyear,tempmonth,tempday,temptime,tempminute;
	CTime now;
	now = CTime::GetCurrentTime();
	tempyear = now.Format(_T("%Y"));
	tempmonth = now.Format(_T("%m"));
	tempday   = now.Format(_T("%d"));
	temptime  = now.Format(_T("%H"));
	tempminute= now.Format(_T("%M"));

	int year,month,day,time,minute;

	year  = atoi((char*)LPCTSTR(tempyear));
	month = atoi((char*)LPCTSTR(tempmonth));
	day   = atoi((char*)LPCTSTR(tempday));
	time  = atoi((char*)LPCTSTR(temptime));
	minute = atoi((char*)LPCTSTR(tempminute));


	year = _ttoi(tempyear);
	month = _ttoi(tempmonth);
	day   = _ttoi(tempday);
	time  = _ttoi(temptime);
	minute = _ttoi(tempminute);

	int yearh,yearl;
	yearl = year&0x00FF;
	int tempy = year&0xFF00;
	tempy = tempy>>16;
	yearh = tempy;

	write_one(g_tstat_id,207,yearh);
	write_one(g_tstat_id,206,yearl);
	write_one(g_tstat_id,205,month);
	write_one(g_tstat_id,203,day);

	write_one(g_tstat_id,202,time);
	write_one(g_tstat_id,201,minute);

	SetTimer(DATATIME_TIMER,1000,NULL);
}

void CDialogCM5::OnBnClickedButtonweeklyschedule()
{
	KillTimer(DATATIME_TIMER);
	if(g_NetWorkLevel==1)
		return;

	g_bPauseMultiRead=TRUE;
	Weekly_Routines dlg;
	dlg.DoModal();

	g_bPauseMultiRead=FALSE;
	SetTimer(DATATIME_TIMER,1000,NULL);


}

void CDialogCM5::OnBnClickedButtonannualschedule()
{
	KillTimer(DATATIME_TIMER);
	if(g_NetWorkLevel==1)
		return;
	g_bPauseMultiRead=TRUE;
	Annual_Routines dlg;
	dlg.DoModal();
	g_bPauseMultiRead=FALSE;
	SetTimer(DATATIME_TIMER,1000,NULL);


}

void CDialogCM5::OnBnClickedButtonidschedule()
{
	KillTimer(DATATIME_TIMER);
	if(g_NetWorkLevel==1)
		return;

	g_bPauseMultiRead=TRUE;
	CConfig_Routines dlg;
	dlg.DoModal();
	g_bPauseMultiRead=FALSE;
	SetTimer(DATATIME_TIMER,1000,NULL);
}

void CDialogCM5::OnBnClickedButtoninputtype()
{
	// TODO: Add your control notification handler code here
}

void CDialogCM5::OnEnKillfocusEditInput()
{
	KillTimer(DATATIME_TIMER);
	CString strText;
	m_edit_input.GetWindowText(strText); 
	m_edit_input.ShowWindow(SW_HIDE);  
	int lRow = m_msflexgrid_input.get_RowSel();	
	int lCol = m_msflexgrid_input.get_ColSel(); 

	m_msflexgrid_input.put_TextMatrix(lRow,lCol,strText);
	CString strrow;
	strrow.Format(_T("%d"),lRow);
	CString stremp;
	stremp = _T("CM5_INPUT");
	//AddDatabase(stremp,strrow,strText);
	UpdateDatabase(stremp,strrow,strText);

	CRect rcCell(0,0,1,1);
	m_edit_input.MoveWindow(&rcCell,1);



	SetTimer(DATATIME_TIMER,1000,NULL);
}

void CDialogCM5::OnEnKillfocusEditoutput()
{
	KillTimer(DATATIME_TIMER);
	// TODO: Add your control notification handler code here
	CString strText;
	m_edit_output.GetWindowText(strText);
	m_edit_output.ShowWindow(SW_HIDE);  
	int lRow = m_msflexgridoutput.get_RowSel();	
	int lCol = m_msflexgridoutput.get_ColSel(); 

	m_msflexgridoutput.put_TextMatrix(lRow,lCol,strText);

	CString strrow,m_database;
	strrow.Format(_T("%d"),lRow);
	
	m_database = _T("CM5_OUTPUT");
//	AddDatabase(m_database,strrow,strText);
	UpdateDatabase(m_database,strrow,strText);
	SetTimer(DATATIME_TIMER,1000,NULL);

	CRect rcCell(0,0,1,1);
	m_edit_output.MoveWindow(&rcCell,1);
}

void CDialogCM5::OnTimer(UINT_PTR nIDEvent)
{
	
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CView* pNewView = pMain->m_pViews[4];
	CView* pActiveView = pMain->GetActiveView();

	if ( pNewView != pActiveView )    // current is CM5 dialog
	{
		KillTimer(MiniPanelTimer);
	}



	static int nCount1 = 0;

	nCount1++;
//	TRACE(_T("nCount1 = %d\n"),nCount1);


	if (DATATIME_TIMER == nIDEvent)
	{
		CTime now;
		now = CTime::GetCurrentTime();
		m_static_datetime = now.Format(_T("%A,%B %d,%Y  %H:%M:%S"));		// "Saturday, April 12, 2012"		

		UpdateData(FALSE);
// 		if (!theApp.cm5_timer)
// 		{
// 			KillTimer(DATATIME_TIMER);
// 		}
			if (nCount1% timer == 0)
			{
				nCount1 = 0;
//				TRACE(_T("start GetData\n"));
				BOOL flag = GetData();
					ShowDialogData();
				if (flag)
				{
//					TRACE(_T("start ShowDialogData\n"));
				
				}
				timer = 60*2;

			}
	

	} 
	CFormView::OnTimer(nIDEvent);
	
}

void CDialogCM5::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();





	//============================================================================================列表框设置（界面中间部份列表框）
	m_Output_GridCM5_.put_Rows(9); //行
	//set row high
	m_Output_GridCM5_.put_WordWrap(TRUE);
	m_Output_GridCM5_.put_RowHeight(0,500);
	//title middle show
	for (int n=0;n<=9;n++)
	{
		m_Output_GridCM5_.put_ColAlignment(n,4);
	}
	//设置列宽
	m_Output_GridCM5_.put_ColWidth(0,400);
	m_Output_GridCM5_.put_ColWidth(1,800);
	m_Output_GridCM5_.put_ColWidth(2,800);
	m_Output_GridCM5_.put_ColWidth(3,1000);
	m_Output_GridCM5_.put_ColWidth(4,1000);
	m_Output_GridCM5_.put_ColWidth(5,1000);
	m_Output_GridCM5_.put_ColWidth(6,1000);
	m_Output_GridCM5_.put_ColWidth(7,1000);
	m_Output_GridCM5_.put_ColWidth(8,1200);
	m_Output_GridCM5_.put_ColWidth(9,1200);

	m_Output_GridCM5_.put_TextMatrix(0,0,_T("No"));
	m_Output_GridCM5_.put_TextMatrix(0,1,_T("Device"));
	m_Output_GridCM5_.put_TextMatrix(0,2,_T("Address"));
	m_Output_GridCM5_.put_TextMatrix(0,3,_T("Cooling\nSetpoint"));
	m_Output_GridCM5_.put_TextMatrix(0,4,_T("Heating\nSetpoint"));
	m_Output_GridCM5_.put_TextMatrix(0,5,_T("Setpoint"));
	m_Output_GridCM5_.put_TextMatrix(0,6,_T("Room\nTemperture"));
	m_Output_GridCM5_.put_TextMatrix(0,7,_T("Mode"));
	m_Output_GridCM5_.put_TextMatrix(0,8,_T("Night Heating\nSetpoint"));
	m_Output_GridCM5_.put_TextMatrix(0,9,_T("Night Cooling\nSetpoint"));

	//彩色显示
	for(int i=1;i<9;i++)
	{

		//		for(int k=0;k<=12;k++)
		for(int k=0;k<=9;k++)
		{
			if (i%2==1)
			{
				m_Output_GridCM5_.put_Row(i);m_Output_GridCM5_.put_Col(k);m_Output_GridCM5_.put_CellBackColor(RGB(255,255,255));
			}
			else
			{
				m_Output_GridCM5_.put_Row(i);m_Output_GridCM5_.put_Col(k);m_Output_GridCM5_.put_CellBackColor(COLOR_CELL);
			}
		}
	}



	//============================================================================================================界面Input部份列表框


	//显示横标题
	m_msflexgrid_input.put_TextMatrix(0,1,_T("Input Name"));
	m_msflexgrid_input.put_TextMatrix(0,2,_T("Value"));
	m_msflexgrid_input.put_TextMatrix(0,3,_T("Auto/Man"));
	m_msflexgrid_input.put_TextMatrix(0,4,_T("Range"));
	m_msflexgrid_input.put_TextMatrix(0,5,_T("Function"));


	//设置排/行数量
	m_msflexgrid_input.put_Cols(6);
	m_msflexgrid_input.put_Rows(27);

	//设置列宽	
	m_msflexgrid_input.put_ColWidth(0,400);
	m_msflexgrid_input.put_ColWidth(5,1500);

	//居中显示
	for (int col=0;col<6;col++)
	{ 
		m_msflexgrid_input.put_ColAlignment(col,4);
	}

	//彩色显示
	for(int i=1;i<27;i++)		//排数量
	{

		for(int k=0;k<6;k++)	//列数量
		{
			if (i%2==1)
			{
				m_msflexgrid_input.put_Row(i);m_msflexgrid_input.put_Col(k);m_msflexgrid_input.put_CellBackColor(RGB(255,255,255));
			}
			else
			{
				m_msflexgrid_input.put_Row(i);m_msflexgrid_input.put_Col(k);m_msflexgrid_input.put_CellBackColor(COLOR_CELL);
			}
		}
	}

//第3，4列11-26灰色显示
	for (int i=1;i<27;i++)
	{
		if (i<=10)
		{
			m_msflexgrid_input.put_TextMatrix(i,4,_T("°C"));	  
		}else
		{
			m_msflexgrid_input.put_TextMatrix(i,4,_T("On/Off"));
		}

		m_msflexgrid_input.put_Row(i);
		m_msflexgrid_input.put_Col(4);
		m_msflexgrid_input.put_CellBackColor(FLEXGRID_CELL_GRAY_COLOR);	   //灰色

	}

#if 0
	//显示纵标题
	CString str;	
	CString strdata;
	strdata = _T("CM5_INPUT");
	for(int i=1;i<=10;i++)
	{

		str.Format(_T("%d"),i);

		m_msflexgrid_input.put_TextMatrix(i,0,str);	 
		CString strtemp = ReadDatabase(strdata,str);
		if (strtemp.IsEmpty())
		{	
			str = _T("Input ")+str;
			m_msflexgrid_input.put_TextMatrix(i,1,str);	
		}else
		{
			m_msflexgrid_input.put_TextMatrix(i,1,strtemp);	
		}

		m_msflexgrid_input.put_TextMatrix(i,5,_T("Default"));	 

	}

	//显示纵标题
	str =_T("");
	for(int i=11;i<27;i++)																
	{

		str.Format(_T("%d"),i);
		CString strtemp = ReadDatabase(strdata,str);
		if (strtemp.IsEmpty())
		{	
			str = _T("Input ")+str;
			m_msflexgrid_input.put_TextMatrix(i,1,str);	
		}else
		{
			m_msflexgrid_input.put_TextMatrix(i,1,strtemp);	
		}
		m_msflexgrid_input.put_TextMatrix(i,0,str);
		//m_msflexgrid_input.put_TextMatrix(i,3,_T("Auto"));
		m_msflexgrid_input.put_TextMatrix(i,4,_T("On/Off"));
		m_msflexgrid_input.put_TextMatrix(i,5,_T("Default"));	

		


	}
#endif

	//============================================================================================================界面Output部份列表框

	//设置行/列数量
	m_msflexgridoutput.put_Rows(11);
	m_msflexgridoutput.put_Cols(6);
	//设置列宽	
	m_msflexgridoutput.put_ColWidth(0,400);
	m_msflexgridoutput.put_ColWidth(5,1500);

	//显示横标题
	m_msflexgridoutput.put_TextMatrix(0,1,_T("Input Name"));
	m_msflexgridoutput.put_TextMatrix(0,2,_T("Value"));
	m_msflexgridoutput.put_TextMatrix(0,3,_T("Auto/Man"));
	m_msflexgridoutput.put_TextMatrix(0,4,_T("Range"));
	m_msflexgridoutput.put_TextMatrix(0,5,_T("Function"));



	//居中显示
	for (int col=0;col<6;col++)
	{ 
		m_msflexgridoutput.put_ColAlignment(col,4);
	}

	//彩色显示
	for(int i=1;i<11;i++)		//排数量
	{

		for(int k=0;k<6;k++)	//列数量
		{
			if (i%2==1)
			{
				m_msflexgridoutput.put_Row(i);m_msflexgridoutput.put_Col(k);m_msflexgridoutput.put_CellBackColor(RGB(255,255,255));
			}
			else
			{
				m_msflexgridoutput.put_Row(i);m_msflexgridoutput.put_Col(k);m_msflexgridoutput.put_CellBackColor(COLOR_CELL);
			}
		}
	}



#if 0
	//显示纵标题
	CString str_output;	
	CString m_cmouput;
	m_cmouput = _T("CM5_OUTPUT");
	for(int i=1;i<=10;i++)
	{

		str_output.Format(_T("%d"),i);
		m_msflexgridoutput.put_TextMatrix(i,0,str_output);	

 		CString strtemp = ReadDatabase(m_cmouput,str_output);
	 	if (strtemp.IsEmpty())
			{	
		 		str_output = _T("OUTPUT ")+str_output;
	 			m_msflexgridoutput.put_TextMatrix(i,1,str_output);	
			}else
			{
				m_msflexgridoutput.put_TextMatrix(i,1,strtemp);	
			}

		//m_msflexgridoutput.put_TextMatrix(i,3,_T("Auto"));
		m_msflexgridoutput.put_TextMatrix(i,4,_T("On/Off"));
		m_msflexgridoutput.put_TextMatrix(i,5,_T("Default"));
		m_msflexgridoutput.put_Row(i);
		m_msflexgridoutput.put_Col(4);
		m_msflexgridoutput.put_CellBackColor(FLEXGRID_CELL_GRAY_COLOR);
	}
#endif
	UpdateData(FALSE);

	m_combobox2_input.ShowWindow(SW_HIDE);
 	m_edit_input.ShowWindow(SW_HIDE); 
 	m_edit_output.ShowWindow(SW_HIDE);	
}

BOOL CDialogCM5::PreTranslateMessage(MSG* pMsg)
{
	
	if(pMsg->wParam == VK_RETURN )			 
	{ 
		

		//	GetDlgItem(IDC_SERIALSTATIC)->SetFocus();
		num++;	  //Enter按下弹起都会进入此。
		if (num == 2)
		{
			num =0;
			return true;
		}
		if (m_switch == 1)
		{
			KillTimer(DATATIME_TIMER);
			int lRow = m_msflexgrid_input.get_RowSel();//获取点击的行号
			int lCol = m_msflexgrid_input.get_ColSel(); //获取点击的列号
			if (lCol == 3)
			{
				m_combobox2_input.ShowWindow(SW_SHOW);


				long lRow = m_msflexgrid_input.get_RowSel();//获取点击的行号	
				long lCol = m_msflexgrid_input.get_ColSel(); //获取点击的列号		
				CRect rect;	
				m_msflexgrid_input.GetWindowRect(rect); //获取表格控件的窗口矩形
				ScreenToClient(rect); //转换为客户区矩形
				// MSFlexGrid控件的函数的长度单位是"缇(twips)"，
				//需要将其转化为像素，1440缇= 1英寸
				CDC* pDC =GetDC();
				//计算象素点和缇的转换比例
				int nTwipsPerDotX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX) ;
				int nTwipsPerDotY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY) ;
				//计算选中格的左上角的坐标(象素为单位)
				long y = m_msflexgrid_input.get_RowPos(lRow)/nTwipsPerDotY;
				long x = m_msflexgrid_input.get_ColPos(lCol)/nTwipsPerDotX;
				//计算选中格的尺寸(象素为单位)。加1是实际调试中，发现加1后效果更好
				long width = m_msflexgrid_input.get_ColWidth(lCol)/nTwipsPerDotX+1;
				long height = m_msflexgrid_input.get_RowHeight(lRow)/nTwipsPerDotY+1;
				//形成选中个所在的矩形区域
				CRect rc(x,y,x+width,y+height);
				//转换成相对对话框的坐标	
				rc.OffsetRect(rect.left+1,rect.top+1);	
				//获取选中格的文本信息	
				//获取选中格的文本信息	
				CString strValue = m_msflexgrid_input.get_TextMatrix(lRow,lCol);
				m_combobox2_input.ResetContent();

				m_combobox2_input.AddString(_T("Manual"));
				m_combobox2_input.AddString(_T("Auto"));

				m_combobox2_input.MoveWindow(&rc,1); //移动到选中格的位置
				m_combobox2_input.BringWindowToTop();	
				m_combobox2_input.SelectString(-1,strValue);
				m_combobox2_input.ShowWindow(SW_SHOW);//显示控件



				CString strTemp;
				int nindext = m_combobox2_input.GetCurSel();//GetEditSel();	 GetCurSel
				if (nindext<0||nindext>3)
				{	   
					nindext = 1;			
				}	
				m_combobox2_input.GetLBText(nindext,strTemp);

				CString m_strmanual = _T("Manual");
				int addr;
				int ret = strTemp.Collate(m_strmanual);
				if (ret == 0)
				{
					m_combo2_cstring = _T("Auto");
					TRACE(_T("Auto%d"),num);

				}else
				{
					m_combo2_cstring = _T("Manual");  
					TRACE(_T("Manual%d"),num);


				}	

				UpdateData(FALSE);
				if (lCol == 3)
				{ 
					m_msflexgrid_input.put_TextMatrix(lRow,lCol,m_combo2_cstring);

				}
			}else if (lCol == 2&lRow>10)
			{
				CString value_lCol = m_msflexgrid_input.get_TextMatrix(lRow,lCol+1);
				CString m_strmanual = _T("Manual");
				int ret = value_lCol.Collate(m_strmanual);
				if (ret == 0)
				{

					m_combobox2_input.ShowWindow(SW_SHOW);


					long lRow = m_msflexgrid_input.get_RowSel();//获取点击的行号	
					long lCol = m_msflexgrid_input.get_ColSel(); //获取点击的列号		
					CRect rect;	
					m_msflexgrid_input.GetWindowRect(rect); //获取表格控件的窗口矩形
					ScreenToClient(rect); //转换为客户区矩形
					// MSFlexGrid控件的函数的长度单位是"缇(twips)"，
					//需要将其转化为像素，1440缇= 1英寸
					CDC* pDC =GetDC();
					//计算象素点和缇的转换比例
					int nTwipsPerDotX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX) ;
					int nTwipsPerDotY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY) ;
					//计算选中格的左上角的坐标(象素为单位)
					long y = m_msflexgrid_input.get_RowPos(lRow)/nTwipsPerDotY;
					long x = m_msflexgrid_input.get_ColPos(lCol)/nTwipsPerDotX;
					//计算选中格的尺寸(象素为单位)。加1是实际调试中，发现加1后效果更好
					long width = m_msflexgrid_input.get_ColWidth(lCol)/nTwipsPerDotX+1;
					long height = m_msflexgrid_input.get_RowHeight(lRow)/nTwipsPerDotY+1;
					//形成选中个所在的矩形区域
					CRect rc(x,y,x+width,y+height);
					//转换成相对对话框的坐标	
					rc.OffsetRect(rect.left+1,rect.top+1);	
					//获取选中格的文本信息	
					//获取选中格的文本信息	
					CString strValue = m_msflexgrid_input.get_TextMatrix(lRow,lCol);
					m_combobox2_input.ResetContent();

					m_combobox2_input.AddString(_T("On"));
					m_combobox2_input.AddString(_T("Off"));

					m_combobox2_input.MoveWindow(&rc,1); //移动到选中格的位置
					m_combobox2_input.BringWindowToTop();	
					m_combobox2_input.SelectString(-1,strValue);
					m_combobox2_input.ShowWindow(SW_SHOW);//显示控件

					CString strTemp;
					int nindext = m_combobox2_input.GetCurSel();//GetEditSel();	 GetCurSel
					if (nindext<0||nindext>3)
					{	   
						nindext = 1;			
					}	
					m_combobox2_input.GetLBText(nindext,strTemp);

					CString m_strmanual = _T("On");
					int addr;
					int ret = strTemp.Collate(m_strmanual);
					if (ret == 0)
					{
						m_combo2_cstring = _T("Off");
					
						TRACE(_T("Auto%d"),num);

					}else
					{
						m_combo2_cstring = _T("On");  
				
						TRACE(_T("Manual%d"),num);


					}	

					UpdateData(FALSE);
					if (lCol == 2)
					{ 
						m_msflexgrid_input.put_TextMatrix(lRow,lCol,m_combo2_cstring);
					}
				}

			}else if(lCol == 1)			
			{
				//使用edition控件形式显示

				long lRow,lCol;
				lRow = m_msflexgrid_input.get_RowSel();
				lCol = m_msflexgrid_input.get_ColSel(); 

				CRect rect;
				m_msflexgrid_input.GetWindowRect(rect); //
				ScreenToClient(rect); //
				CDC* pDC =GetDC();

				int nTwipsPerDotX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX) ;
				int nTwipsPerDotY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY) ;

				long y = m_msflexgrid_input.get_RowPos(lRow)/nTwipsPerDotY;
				long x = m_msflexgrid_input.get_ColPos(lCol)/nTwipsPerDotX;

				long width = m_msflexgrid_input.get_ColWidth(lCol)/nTwipsPerDotX+1;
				long height = m_msflexgrid_input.get_RowHeight(lRow)/nTwipsPerDotY+1;

				CRect rcCell(x,y,x+width,y+height);

				rcCell.OffsetRect(rect.left+1,rect.top+1);
				ReleaseDC(pDC);
				CString strValue = m_msflexgrid_input.get_TextMatrix(lRow,lCol);

				if(1==lCol)		
				{		
					m_edit_input.MoveWindow(&rcCell,1);
					m_edit_input.ShowWindow(SW_SHOW);	
					m_edit_input.SetWindowText(strValue);	
					m_edit_input.SetFocus();
					int nLenth=strValue.GetLength();	
					m_edit_input.SetSel(nLenth,nLenth); 

				}	

			}
			SetTimer(DATATIME_TIMER,1000,NULL);


		}else if (m_switch == 2)
		{
			KillTimer(DATATIME_TIMER);

			int lRow = m_msflexgridoutput.get_RowSel();//获取点击的行号
			int lCol = m_msflexgridoutput.get_ColSel(); //获取点击的列号
			if (lCol == 3)
			{
				m_msflexgridoutput.ShowWindow(SW_SHOW);

				long lRow = m_msflexgridoutput.get_RowSel();//获取点击的行号	
				long lCol = m_msflexgridoutput.get_ColSel(); //获取点击的列号		
				CRect rect;	
				m_msflexgridoutput.GetWindowRect(rect); //获取表格控件的窗口矩形
				ScreenToClient(rect); //转换为客户区矩形
				// MSFlexGrid控件的函数的长度单位是"缇(twips)"，
				//需要将其转化为像素，1440缇= 1英寸
				CDC* pDC =GetDC();
				//计算象素点和缇的转换比例
				int nTwipsPerDotX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX) ;
				int nTwipsPerDotY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY) ;
				//计算选中格的左上角的坐标(象素为单位)
				long y = m_msflexgridoutput.get_RowPos(lRow)/nTwipsPerDotY;
				long x = m_msflexgridoutput.get_ColPos(lCol)/nTwipsPerDotX;
				//计算选中格的尺寸(象素为单位)。加1是实际调试中，发现加1后效果更好
				long width = m_msflexgridoutput.get_ColWidth(lCol)/nTwipsPerDotX+1;
				long height = m_msflexgridoutput.get_RowHeight(lRow)/nTwipsPerDotY+1;
				//形成选中个所在的矩形区域
				CRect rc(x,y,x+width,y+height);
				//转换成相对对话框的坐标	
				rc.OffsetRect(rect.left+1,rect.top+1);	
				//获取选中格的文本信息	
				//获取选中格的文本信息	
				CString strValue = m_msflexgridoutput.get_TextMatrix(lRow,lCol);
				m_combobox2_input.ResetContent();

				m_combobox2_input.AddString(_T("Manual"));
				m_combobox2_input.AddString(_T("Auto"));

				m_combobox2_input.MoveWindow(&rc,1); //移动到选中格的位置
				m_combobox2_input.BringWindowToTop();	
				m_combobox2_input.SelectString(-1,strValue);
				m_combobox2_input.ShowWindow(SW_SHOW);//显示控件

				CString strTemp;
				int nindext = m_combobox2_input.GetCurSel();//GetEditSel();	 GetCurSel
				if (nindext<0||nindext>3)
				{	   
					nindext = 1;			
				}	
				m_combobox2_input.GetLBText(nindext,strTemp);

				CString m_strmanual = _T("Manual");
				int addr;
				int ret = strTemp.Collate(m_strmanual);
				if (ret == 0)
				{
					m_combo2_cstring = _T("Auto");
		
					TRACE(_T("Auto%d"),num);

				}else
				{
					m_combo2_cstring = _T("Manual");  
			
					TRACE(_T("Manual%d"),num);


				}	

				UpdateData(FALSE);
				if (lCol == 3)
				{ 
					m_msflexgridoutput.put_TextMatrix(lRow,lCol,m_combo2_cstring);

					CString m_strmanual = _T("Auto");
					int ret = m_combo2_cstring.Collate(m_strmanual);
					if (ret == 0)
					{
						m_msflexgridoutput.put_TextMatrix(lRow,lCol+1,_T("On/Off"));
					}

				}
			}else if (lCol == 2)
			{

				CString value_lCol = m_msflexgridoutput.get_TextMatrix(lRow,lCol+1);
				CString m_strmanual = _T("Manual");
				int ret = value_lCol.Collate(m_strmanual);
				if (ret == 0)
				{

					m_msflexgridoutput.ShowWindow(SW_SHOW);


					long lRow = m_msflexgridoutput.get_RowSel();//获取点击的行号	
					long lCol = m_msflexgridoutput.get_ColSel(); //获取点击的列号		
					CRect rect;	
					m_msflexgridoutput.GetWindowRect(rect); //获取表格控件的窗口矩形
					ScreenToClient(rect); //转换为客户区矩形
					// MSFlexGrid控件的函数的长度单位是"缇(twips)"，
					//需要将其转化为像素，1440缇= 1英寸
					CDC* pDC =GetDC();
					//计算象素点和缇的转换比例
					int nTwipsPerDotX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX) ;
					int nTwipsPerDotY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY) ;
					//计算选中格的左上角的坐标(象素为单位)
					long y = m_msflexgridoutput.get_RowPos(lRow)/nTwipsPerDotY;
					long x = m_msflexgridoutput.get_ColPos(lCol)/nTwipsPerDotX;
					//计算选中格的尺寸(象素为单位)。加1是实际调试中，发现加1后效果更好
					long width = m_msflexgridoutput.get_ColWidth(lCol)/nTwipsPerDotX+1;
					long height = m_msflexgridoutput.get_RowHeight(lRow)/nTwipsPerDotY+1;
					//形成选中个所在的矩形区域
					CRect rc(x,y,x+width,y+height);
					//转换成相对对话框的坐标	
					rc.OffsetRect(rect.left+1,rect.top+1);	
					//获取选中格的文本信息	
					//获取选中格的文本信息	
					CString strValue = m_msflexgridoutput.get_TextMatrix(lRow,lCol);
					m_combobox2_input.ResetContent();

					m_combobox2_input.AddString(_T("On"));
					m_combobox2_input.AddString(_T("Off"));

					m_combobox2_input.MoveWindow(&rc,1); //移动到选中格的位置
					m_combobox2_input.BringWindowToTop();	
					m_combobox2_input.SelectString(-1,strValue);
					m_combobox2_input.ShowWindow(SW_SHOW);//显示控件


					CString strTemp;
					int nindext = m_combobox2_input.GetCurSel();//GetEditSel();	 GetCurSel
					if (nindext<0||nindext>3)
					{	   
						nindext = 1;			
					}	
					m_combobox2_input.GetLBText(nindext,strTemp);

					CString m_strmanual = _T("On");
					int addr;
					int ret = strTemp.Collate(m_strmanual);
					if (ret == 0)
					{
						m_combo2_cstring = _T("Off");
						TRACE(_T("Auto%d"),num);

					}else
					{
						m_combo2_cstring = _T("On");  
						TRACE(_T("Manual%d"),num);


					}	

					UpdateData(FALSE);
					if (lCol == 2)
					{ 
						m_msflexgridoutput.put_TextMatrix(lRow,lCol,m_combo2_cstring);

					}
				}

			}else if (lCol == 1)
			{
				//使用edition控件形式显示

				long lRow,lCol;
				lRow = m_msflexgridoutput.get_RowSel();
				lCol = m_msflexgridoutput.get_ColSel(); 

				CRect rect;
				m_msflexgridoutput.GetWindowRect(rect); 
				ScreenToClient(rect); 
				CDC* pDC =GetDC();

				int nTwipsPerDotX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX) ;
				int nTwipsPerDotY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY) ;

				long y = m_msflexgridoutput.get_RowPos(lRow)/nTwipsPerDotY;
				long x = m_msflexgridoutput.get_ColPos(lCol)/nTwipsPerDotX;

				long width = m_msflexgridoutput.get_ColWidth(lCol)/nTwipsPerDotX+1;
				long height = m_msflexgridoutput.get_RowHeight(lRow)/nTwipsPerDotY+1;

				CRect rcCell(x,y,x+width,y+height);

				rcCell.OffsetRect(rect.left+1,rect.top+1);
				ReleaseDC(pDC);
				CString strValue = m_msflexgridoutput.get_TextMatrix(lRow,lCol);


				if(1==lCol)		
				{		
					m_edit_output.MoveWindow(&rcCell,1);
					m_edit_output.ShowWindow(SW_SHOW);	
					m_edit_output.SetWindowText(strValue);	
					m_edit_output.SetFocus();	
					int nLenth=strValue.GetLength();	
					m_edit_output.SetSel(nLenth,nLenth); 	

				}		

			}
			SetTimer(DATATIME_TIMER,1000,NULL);

		}else
		{

			return true; 
		}

	}


	if(pMsg->wParam == VK_LEFT||pMsg->wParam == VK_RIGHT||pMsg->wParam == VK_UP||pMsg->wParam == VK_DOWN)			 
	{ 


		m_combobox2_input.ShowWindow(SW_HIDE);
		if (m_switch == 1)			  
		{
			KillTimer(DATATIME_TIMER);
			int lCol = m_msflexgrid_input.get_ColSel(); //获取点击的列号
			if (lCol ==1)
			{
				m_edit_input.EnableWindow(FALSE);
				m_msflexgrid_input.SetFocus();
				
				
				m_edit_input.EnableWindow();

			}else
			{
				m_msflexgrid_input.SetFocus();
			}

			m_msflexgrid_input.SetFocus();
			SetTimer(DATATIME_TIMER,1000,NULL);

		} 
		else if (m_switch == 2)
		{
			KillTimer(DATATIME_TIMER);
			int lCol = m_msflexgridoutput.get_ColSel(); //获取点击的列号
			if (lCol ==1)
			{
				m_edit_output.EnableWindow(FALSE);
				m_msflexgridoutput.SetFocus();
				m_edit_output.EnableWindow();

			}else
			{
				m_msflexgridoutput.SetFocus();
			}

		}
		SetTimer(DATATIME_TIMER,1000,NULL);

	} 


	
	return CFormView::PreTranslateMessage(pMsg);
}

void CDialogCM5::ShowDialogData()
{


	//=======================================================initialization====================================================================
	int cooling_temp;
	int coasting_temp;
	int heating_temp;



	//============================================================System Parameters===============================================================
	// 		200	1	second
	// 		201	1	minute
	// 		202	1	hour
	// 		203	1	day
	// 		204	1	week, 0=Sunday; 1=Monday; and so on.
	// 		205	1	month
	// 		206	1	lower byte of the year, for example, here should be 98 in year 1998
	// 		207	1	higher byte of the year, for example, here should be 19 in the year 1998

	//	m_strDate.Format(_T("%d%d-%d-%d"),cm5_register_value[207],cm5_register_value[206],cm5_register_value[205],cm5_register_value[203]);
	if (initparam)
	{
		m_IDaddressCM5 = 254;
		m_nSerialNumCM5 = 4294967063;
		m_firmwareVersionCM5 = 0.7;
		m_hardware_versionCM5 =4;
		initparam = FALSE;




	}
	else
	{


		m_strDateCM5.Format(_T("%d%d-%d-%d"),20,11,cm5_register_value[205],cm5_register_value[203]);//临时演示



		m_strTime.Format(_T("%02d:%02d"),cm5_register_value[202],cm5_register_value[201]);
		m_IDaddressCM5=cm5_register_value[6];	

		UINT nSelectSerialNumber = cm5_register_value[0]+cm5_register_value[1]*256+cm5_register_value[2]*256*256+cm5_register_value[3]*256*256*256;
		m_nSerialNumCM5=nSelectSerialNumber;
		m_firmwareVersionCM5 =get_curtstat_version();
		m_hardware_versionCM5=cm5_register_value[8];
	}
	//================================================Parameter=========================================================

	// 	176	1	priority mode. 0--OFF  1--TIMER   2--ON
	// 	177	1	priority period . Range is 1 - 99min
	// 	178	1	priority time left
	if (cm5_register_value[176]!=0||cm5_register_value[176]!=1||cm5_register_value[176]!=2)
		m_combo_prioritymode.SetCurSel(0);
	else
		m_combo_prioritymode.SetCurSel(cm5_register_value[176]);
	m_priorityinterval = cm5_register_value[177];
	m_countprioritytime.Format(_T("%d"),cm5_register_value[178]);
	



	//==========================================显示界面中间列表框中的数据==============================================

	//	    5671 to 5678	8	cooling setpoint value of Sub Tstats(register380)
	//		5679 to 5686	8	heating setpoint value of Sub Tstats(register136)
	//		5687 to 5694	8	setpoint value of Sub Tstats(register135)
	//		5695 to 5702	8	room temperture value of Sub Tstats(register101)
	//		5703 to 5710	8	mode of Sub Tstats(register107)
	//		5711 to 5718	8	output state of Sub Tstats(register108)

	//		5735 to 5742	8	night heatting setpoint value of Sub Tstats(register182)
	//		5743 to 5750	8	night cooling setpoint value of Sub Tstats(register183)
	//		5751 to 5758	8	tstat product model of Sub Tstats(register7)

	_subnetwork.clear();
	for (int i = 0;i<8;i++)
	{


		m_subetwork.m_coolingSet.Format(_T("%.1f°C"),(float)m_buffer[i]/10);
		m_subetwork.m_heatingSet.Format(_T("%.1f°C"),(float)m_buffer[i+8]/10);
		m_subetwork.m_setpoint.Format(_T("%.1f°C"),(float)m_buffer[i+16]/10); 
		m_subetwork.m_roomTemper.Format(_T("%.1f°C"),(float)m_buffer[i+24]/10); 
		m_subetwork.m_mode = m_buffer[i+32];     
		m_subetwork.m_outputState.Format(_T("%.1f"),(float)m_buffer[i+40]/10); 
		m_subetwork.m_nightHeating.Format(_T("%.1f°C"),(float)m_buffer[i+48]/10);
		m_subetwork.m_nightCooling.Format(_T("%.1f°C"),(float)m_buffer[i+56]/10); 
		m_subetwork.m_tstatProduct = m_buffer[i+64]; 
		m_subetwork.m_modbusaddr.Format(_T("%d"),cm5_register_value[185+i]);
		_subnetwork.push_back(m_subetwork);

	}


	CString m_num,strtemp1,strtemp2;
	coasting_temp = 0;
	heating_temp = 0;
	cooling_temp = 0;


	for (int i=1;i<9;i++)
	{
		int ret = _subnetwork.at(i-1).m_modbusaddr.Compare(_T("0"));
		if(ret == 0)
			continue;
		m_num.Format(_T("%d"),i);
		m_Output_GridCM5_.put_TextMatrix(i,0,m_num);//第一列：序号

		switch(_subnetwork.at(i-1).m_tstatProduct)
		{
		case 1:strtemp1=g_strTstat5b;break;
		case 2:strtemp1=g_strTstat5a;break;
		case 3:strtemp1=g_strTstat5b;break;
		case 4:strtemp1=g_strTstat5c;break;
		case 12:			strtemp1=g_strTstat5d;break;
		case 100:		strtemp1=g_strnetWork;break;
		case NET_WORK_OR485_PRODUCT_MODEL:strtemp1=g_strOR485;break;
		case 17:strtemp1=g_strTstat5f;break;
		case 18:strtemp1=g_strTstat5g;break;
		case 16:strtemp1=g_strTstat5e;break;
		case 19:strtemp1=g_strTstat5h;break;

		case 26:strtemp1=g_strTstat6;break;
		case 27:strtemp1=g_strTstat7;break;
		case 13:
		case 14:break;
		default:strtemp1=g_strTstat5a;break;
		}
		m_Output_GridCM5_.put_TextMatrix(i,1,strtemp1);

		m_Output_GridCM5_.put_TextMatrix(i,2,_subnetwork.at(i-1).m_modbusaddr);
		m_Output_GridCM5_.put_TextMatrix(i,3,_subnetwork.at(i-1).m_coolingSet);
		m_Output_GridCM5_.put_TextMatrix(i,4,_subnetwork.at(i-1).m_heatingSet);
		m_Output_GridCM5_.put_TextMatrix(i,5,_subnetwork.at(i-1).m_setpoint);
		m_Output_GridCM5_.put_TextMatrix(i,6,_subnetwork.at(i-1).m_roomTemper);

		switch (_subnetwork.at(i-1).m_tstatProduct)		 
		{
		case 0:
			strtemp2.Format(_T("%s"),_T("COASTING"));
			coasting_temp++;
			break;
		case 1:
			strtemp2.Format(_T("%s"),_T("COOLING1"));
			cooling_temp++;
			break;
		case 2:
			strtemp2.Format(_T("%s"),_T("COOLING2"));	
			cooling_temp++;
			break;
		case 3:
			strtemp2.Format(_T("%s"),_T("COOLING3"));
			cooling_temp++;
			break;
		case 4:
			strtemp2.Format(_T("%s"),_T("HEATING1"));
			heating_temp++;
			break;
		case 5:
			strtemp2.Format(_T("%s"),_T("HEATING2"));
			heating_temp++;
			break;
		case 6:
			strtemp2.Format(_T("%s"),_T("HEATING3"));
			heating_temp++;
			break;

		default:
			strtemp2.Format(_T("%s"),_T("COASTING"));
			coasting_temp++;
			break;
		}
		m_Output_GridCM5_.put_TextMatrix(i,7,strtemp2);


		m_Output_GridCM5_.put_TextMatrix(i,8,_subnetwork.at(i-1).m_nightHeating);
		m_Output_GridCM5_.put_TextMatrix(i,9,_subnetwork.at(i-1).m_nightCooling);
	}


	//================================================Tstat Status======================================================
	//     	193	1	number of tstats
	// 		194	1	number of tstats calling for heat
	// 		195	1	number of tstats calling for cool

	int rettemp = coasting_temp+heating_temp+cooling_temp;
	if (cm5_register_value[193] == rettemp)
		m_result.Format(_T("%d"),cm5_register_value[193]);
	else
		m_result.Format(_T("%d"),rettemp);
	m_coating.Format(_T("%d"),coasting_temp);
	m_heating.Format(_T("%d"),heating_temp);
	m_cooling.Format(_T("%d"),cooling_temp);	


	//==================================================Input============================================================
	//	  134 to 143	10	value of Input1 - input10 
	CString str;
	int  row_num = 1;
	CString strresult;
	float m_tempf;
	int m_tempi;
	int num=1;	 
	for(int i = 134;i<=143;i++)
	{  
		//strresult.Format(_T("%d°C"),cm5_register_value[i]);
		strresult.Format(_T("%d"),cm5_register_value[i]);
		m_msflexgrid_input.put_TextMatrix(num,2,strresult);
		num++;
	}

	//	172	1	value of DI1-DI8, tstat status for mechanical stats
	//	173	1	value of DI9-DI16, valve endswitches

	int row_max = 19;
	int startnum =11;
	for (int addr = 172;addr<=173;addr++)
	{
		int temp = 1;
		if (cm5_register_value[addr]>=0)
		{

			for (startnum;startnum<=row_max;startnum++)
			{
				if ((cm5_register_value[addr]&temp)==0)
				{																						
					m_msflexgrid_input.put_TextMatrix(startnum,2,_T("Off"));	  //0-Off   0-代表OFF
				}else
				{
					m_msflexgrid_input.put_TextMatrix(startnum,2,_T("On"));	  //1- ON   1-代表ON
				}
				temp=temp<<1;

			}	 
		}
		row_max = 26;

	}



	//	182	2	auto/manual feature of analog input 1 - 10  (2代表的是，高8位，和低8位都用上，1代表中用低8位。)

	int tempAI = 1;

	for (int i = 1;i<=10;i++)
	{
		if ((cm5_register_value[182]&tempAI)==0)
		{																						
			m_msflexgrid_input.put_TextMatrix(i,3,_T("Auto"));	          //0-Auto	 0代表自动Auto
		}else
		{
			m_msflexgrid_input.put_TextMatrix(i,3,_T("Manual"));		  //1-Manual   1-代表手动Manual
		}
		tempAI=tempAI<<1;

	}																				





	//	180	2	auto/manual feature of digital input 1 - 16
	int tempAM = 1;
	for (int i = 11;i<=26;i++)
	{
		if ((cm5_register_value[180]&tempAM)==0)																						
			m_msflexgrid_input.put_TextMatrix(i,3,_T("Auto"));	   //0-Auto	
		else
			m_msflexgrid_input.put_TextMatrix(i,3,_T("Manual"));  //1-Manual
		tempAM=tempAM<<1;

	}	


	//====================================================Output============================================================	
	//   174	1	Digital output1 - 8, valves/pumps
	//   175	1	Digital output9,10: boiler , manifold pump
	int row_max_output = 8;
	int i = 1;
	for (int addr = 174;addr<=175;addr++)	  
	{
		int temp = 1;

		if (cm5_register_value[addr]>=0)
		{
			for (i;i<=row_max_output;i++)
			{

				if ((cm5_register_value[addr]&temp)==0)
				{
					m_msflexgridoutput.put_TextMatrix(i,2,_T("Off"));	   //0-OFF
				}else
				{
					m_msflexgridoutput.put_TextMatrix(i,2,_T("On"));	   //1-On
				}
				temp=temp<<1;

			}	
		}

		row_max_output = 10;

	}


	//   181	2	auto/manual feature of output 1 - 10

	int tempDO = 1;


	for (int i = 1;i<=10;i++)
	{
		if ((cm5_register_value[181]&tempDO)==0)
		{																						
			m_msflexgridoutput.put_TextMatrix(i,3,_T("Auto"));	//0-Auto
		}else
		{
			m_msflexgridoutput.put_TextMatrix(i,3,_T("Manual"));//1-Manual
		}
		tempDO=tempDO<<1;

	}																				




	UpdateData(FALSE);


}

BOOL& CDialogCM5::GetData()
{
	open_com(2);
	BOOL ret_bool = FALSE;
	long start = clock(),end(0); 		

	memset(&cm5_register_value,0,sizeof(cm5_register_value));
	int i;
	for(i=0;i<7;i++)
	{
// 		if (theApp.cm5_timer)
// 		{
			int ret0 = Read_Multi(g_tstat_id,&cm5_register_value[i*64],i*64,64);
//			if(ret0 == -2)
//				return ret_bool;
//		}

// 		else 
// 			return ret_bool;

	}



	//	    5671 to 5678	8	cooling setpoint value of Sub Tstats(register380)
	//		5679 to 5686	8	heating setpoint value of Sub Tstats(register136)
	//		5687 to 5694	8	setpoint value of Sub Tstats(register135)
	//		5695 to 5702	8	room temperture value of Sub Tstats(register101)
	//		5703 to 5710	8	mode of Sub Tstats(register107)
	//		5711 to 5718	8	output state of Sub Tstats(register108)

	//		5719 to 5726	8	night heatting deadband of Sub Tstats(register123)
	//		5727 to 5734	8	night cooling deadband  of Sub Tstats(register124)

	//		5735 to 5742	8	night heatting setpoint value of Sub Tstats(register182)
	//		5743 to 5750	8	night cooling setpoint value of Sub Tstats(register183)
	//		5751 to 5758	8	tstat product model of Sub Tstats(register7)
	int ret1,ret2,ret3;
	memset(&m_buffer,0,sizeof(m_buffer));
//	if (theApp.cm5_timer)
		ret1 = Read_Multi(g_tstat_id,&m_buffer[0],5671,48);
//	else
//		return ret_bool;
	TRACE(_T("ret1 = %d\n"),ret1);

//	if (theApp.cm5_timer)
 		ret2 = Read_Multi(g_tstat_id,&m_buffer[48],5735,24);
//	else
//		return ret_bool;

	TRACE(_T("ret2 = %d\n"),ret2);



	end = clock();
	long resultvalue = (end - start)/1000;
	TRACE(_T("GetData() usetime %d minute\n"),resultvalue);
	BOOL getdata_bool;

	if (ret1==-2||ret2==-2)
	{
		getdata_bool = FALSE;
	}else
	{
		getdata_bool = TRUE;
	}

	return getdata_bool;


}

BEGIN_EVENTSINK_MAP(CDialogCM5, CFormView)
ON_EVENT(CDialogCM5, IDC_INPUT_MSFLEXGRID, DISPID_CLICK, CDialogCM5::ClickInputMsflexgrid, VTS_NONE)
ON_EVENT(CDialogCM5, IDC_INPUT_MSFLEXGRID, DISPID_DBLCLICK, CDialogCM5::DblClickInputMsflexgrid, VTS_NONE)
ON_EVENT(CDialogCM5, IDC_OUTPUT_MSFLEXGRID, DISPID_CLICK, CDialogCM5::ClickOutputMsflexgrid, VTS_NONE)
ON_EVENT(CDialogCM5, IDC_OUTPUT_MSFLEXGRID, DISPID_DBLCLICK, CDialogCM5::DblClickOutputMsflexgrid, VTS_NONE)
END_EVENTSINK_MAP()

void CDialogCM5::ClickInputMsflexgrid()
{
	KillTimer(DATATIME_TIMER);
	m_combobox2_input.ShowWindow(SW_HIDE);
	UpdateData(FALSE);

	m_switch = 1;
	// TODO: Add your message handler code here
	//get_RowSel();这是获取总的行数
	long row = m_msflexgrid_input.get_RowSel();
	long col = m_msflexgrid_input.get_ColSel();
	if ((col==2&&row>10)||col==3)
	{
		if ((m_cellcol == 2&&m_cellrow>10)||m_cellcol == 3)//原来是否有标志背景单元格
		{
			if (m_cellrow%2 == 1)
			{
				m_msflexgrid_input.put_Row(m_cellrow);m_msflexgrid_input.put_Col(m_cellcol);m_msflexgrid_input.put_CellBackColor(RGB(255,255,255));//单数行
			}else
			{
				m_msflexgrid_input.put_Row(m_cellrow);m_msflexgrid_input.put_Col(m_cellcol);m_msflexgrid_input.put_CellBackColor(COLOR_CELL);//双数行
			}
		}

		m_msflexgrid_input.put_Row(row);m_msflexgrid_input.put_Col(col);m_msflexgrid_input.put_CellBackColor(RGB(100,100,150));


	}
	else
	{
		if ((m_cellcol == 2&&m_cellrow>10)||m_cellcol == 3)
		{

			if (m_cellrow%2 == 1)
			{
				m_msflexgrid_input.put_Row(m_cellrow);m_msflexgrid_input.put_Col(m_cellcol);m_msflexgrid_input.put_CellBackColor(RGB(255,255,255));
			}else
			{
				m_msflexgrid_input.put_Row(m_cellrow);m_msflexgrid_input.put_Col(m_cellcol);m_msflexgrid_input.put_CellBackColor(COLOR_CELL);
			}
		}
		if (col == 4)
		{
			m_msflexgrid_input.put_Row(row);m_msflexgrid_input.put_Col(col);m_msflexgrid_input.put_CellBackColor(FLEXGRID_CELL_GRAY_COLOR);//第5列灰色显示

		}else if (row%2 == 1)
		{
			m_msflexgrid_input.put_Row(row);m_msflexgrid_input.put_Col(col);m_msflexgrid_input.put_CellBackColor(RGB(255,255,255));
		}else
		{
			m_msflexgrid_input.put_Row(row);m_msflexgrid_input.put_Col(col);m_msflexgrid_input.put_CellBackColor(COLOR_CELL);
		}


	}
	m_cellrow = row;
	m_cellcol = col;																	 

	//使用edition控件形式显示

	long lRow,lCol;
	lRow = m_msflexgrid_input.get_RowSel();
	lCol = m_msflexgrid_input.get_ColSel(); 

	if(lCol == 1)
	{
		CRect rect;
		m_msflexgrid_input.GetWindowRect(rect); //
		ScreenToClient(rect); //
		CDC* pDC =GetDC();

		int nTwipsPerDotX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX) ;
		int nTwipsPerDotY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY) ;
		
		long y = m_msflexgrid_input.get_RowPos(lRow)/nTwipsPerDotY;
		long x = m_msflexgrid_input.get_ColPos(lCol)/nTwipsPerDotX;
		
		long width = m_msflexgrid_input.get_ColWidth(lCol)/nTwipsPerDotX+1;
		long height = m_msflexgrid_input.get_RowHeight(lRow)/nTwipsPerDotY+1;
		
		CRect rcCell(x,y,x+width,y+height);
		
		rcCell.OffsetRect(rect.left+1,rect.top+1);
		ReleaseDC(pDC);
		CString strValue = m_msflexgrid_input.get_TextMatrix(lRow,lCol);

			if(1==lCol)		
			{		
				m_edit_input.MoveWindow(&rcCell,1);
				m_edit_input.ShowWindow(SW_SHOW);	
				m_edit_input.SetWindowText(strValue);	
				m_edit_input.SetFocus();
				m_edit_input.SetCapture();//使随后的鼠标输入都被发送到这个CWnd 
				int nLenth=strValue.GetLength();	
				m_edit_input.SetSel(nLenth,nLenth); 

			}	
	
	}


	SetTimer(DATATIME_TIMER,1000,NULL);
}

void CDialogCM5::DblClickInputMsflexgrid()
{
#if 0
	KillTimer(DATATIME_TIMER);
	m_combobox2_input.ShowWindow(SW_HIDE);
	UpdateData(FALSE);

	long lRow = m_msflexgrid_input.get_RowSel();//获取点击的行号	
	long lCol = m_msflexgrid_input.get_ColSel(); //获取点击的列号

	if (lCol == 2&&lRow>10)
	{

		CString strgrid = m_msflexgrid_input.get_TextMatrix(lRow,lCol+1);
		CString m_strauto = _T("Manual");
		int retauto = m_strauto.Collate(strgrid);

		if (retauto == 0)
		{
			CString strValue = m_msflexgrid_input.get_TextMatrix(lRow,lCol);
			CString m_stron = _T("On");
			int ret = m_stron.Collate(strValue);
			if (ret == 0)
			{
				m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Off"));

			}else
			{
				//参数写入设备
				//1-代表ON            0-代表OFF
				//1-代表手动Manual    0-代表自动Auto
				m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("On"));

			}
		}


	}else if (lCol == 3)
	{
		CString strgrid = m_msflexgrid_input.get_TextMatrix(lRow,lCol);
		CString m_strauto = _T("Auto");
		int retauto = m_strauto.Collate(strgrid);
		if (retauto == 0)
		{
			m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Manual"));
		}else
		{
			m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Auto"));
		}
	}

	SetTimer(DATATIME_TIMER,1000,NULL);
#endif

#if 1
	KillTimer(DATATIME_TIMER);
	m_combobox2_input.ShowWindow(SW_HIDE);
	UpdateData(FALSE);

	long lRow = m_msflexgrid_input.get_RowSel();//获取点击的行号	
	long lCol = m_msflexgrid_input.get_ColSel(); //获取点击的列号

	if (lCol == 2&&lRow>10)
	{

		CString strgrid = m_msflexgrid_input.get_TextMatrix(lRow,lCol+1);
		CString m_strauto = _T("Manual");
		int retauto = m_strauto.Collate(strgrid);


		if (retauto == 0)
		{
			unsigned short temp =1;				
			CString strValue = m_msflexgrid_input.get_TextMatrix(lRow,lCol);
			CString m_stron = _T("Off");
			int ret = m_stron.Collate(strValue);



			if (lRow<=18)
			{

				//参数写入设备
				//1-代表ON            0-代表OFF
				//1-代表手动Manual    0-代表自动Auto

				//172	1	value of DI1-DI8, tstat status for mechanical stats

				int m_lRow= lRow-11;
				temp = temp<<m_lRow;				
				if (ret == 0)
				{

					temp =temp|cm5_register_value[172];

					int ww = write_one(g_tstat_id,172,temp,1);
					TRACE(_T("No:%d = write_one(on/off) is %d\n"),lRow,ww);
					if (ww>0)
					{
						m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("On"));
						cm5_register_value[172]=temp;
					}else
					{
						m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Off"));
					}
				}
				else
				{

					temp = ~temp;
					temp =temp&cm5_register_value[172];

					int ww = write_one(g_tstat_id,172,temp,1);
					TRACE(_T("No:%d = write_one(on/off) is %d\n"),lRow,temp);
					if (ww>0)
					{
						m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Off"));
						cm5_register_value[172]=temp;
					}
					else
					{
						m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("On"));
					}
				}

			}else   //lRow19~26
			{
				//173	1	value of DI9-DI16, valve endswitches

				int m_lRow= lRow-19;
				temp = temp<<m_lRow;	
				if (ret == 0)
				{
					temp =temp|cm5_register_value[173];
					int ww = write_one(g_tstat_id,173,temp,1);
					TRACE(_T("No:%d = write_one(on/off) is %d\n"),lRow,ww);
					if (ww>0)
					{
						m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("On"));
						cm5_register_value[173]=temp;
					}else
					{
						m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Off"));
					}
				}
				else
				{
					temp = ~temp;
					temp =temp&cm5_register_value[173];
					int ww = write_one(g_tstat_id,173,temp,1);
					TRACE(_T("No:%d = write_one(on/off) is %d\n"),lRow,temp);
					if (ww>0)
					{
						m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Off"));
						cm5_register_value[173]=temp;
					}
					else
					{
						m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("On"));
					}
				}




			}

		}

	}else if (lCol == 3)
	{
		CString strgrid = m_msflexgrid_input.get_TextMatrix(lRow,lCol);
		CString m_strauto = _T("Auto");
		int retauto = m_strauto.Collate(strgrid);
		if (retauto == 0)
		{
			unsigned short temp =1;
			if (lRow<=10)
			{
				//	182	2	auto/manual feature of analog input 1 - 10
				temp = temp<<lRow-1;
				temp =temp|cm5_register_value[182];

				int ww = write_one(g_tstat_id,182,temp,1);
				TRACE(_T("No:%d = write_one is %d\n"),lRow,ww);
				if (ww>0)
				{
					m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Manual"));
					cm5_register_value[182]=temp;
				}
				else
					m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Auto"));
			}else
			{
				//	180	2	auto/manual feature of digital input 1 - 16
				int m_lRow= lRow-11;
				temp = temp<<m_lRow;
				temp =temp|cm5_register_value[180];

				int ww = write_one(g_tstat_id,180,temp,1);
				TRACE(_T("No:%d = Manual is %d\n"),lRow,temp);
				if (ww>0)
				{
					m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Manual"));
					cm5_register_value[180]=temp;
				}
				else
					m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Auto"));
			}



		}else
		{
			unsigned short temp =1;

			if (lRow<=10)
			{
				//	182	2	auto/manual feature of analog input 1 - 10
				temp = temp<<lRow-1;
				temp = ~temp;
				temp =temp&cm5_register_value[182];

				int ww = write_one(g_tstat_id,182,temp,1);
				TRACE(_T("No:%d = write_one is %d\n"),lRow,ww);
				if (ww>0)
				{
					m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Auto"));
					cm5_register_value[182]=temp;
				}
				else
					m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Manual"));
			}else
			{
				//	180	2	auto/manual feature of digital input 1 - 16
				int m_lRow= lRow-11;
				temp = temp<<m_lRow;
				temp = ~temp;
				temp =temp&cm5_register_value[180];

				int ww = write_one(g_tstat_id,180,temp,1);
				TRACE(_T("No:%d = Manual is %d\n"),lRow,temp);
				if (ww>0)
				{
					m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Auto"));
					cm5_register_value[180]=temp;
				}
				else
					m_msflexgrid_input.put_TextMatrix(lRow,lCol,_T("Manual"));
			}
		}
	}

	SetTimer(DATATIME_TIMER,1000,NULL);
#endif
}

void CDialogCM5::ClickOutputMsflexgrid()
{
	KillTimer(DATATIME_TIMER);
	m_combobox2_input.ShowWindow(SW_HIDE);
	UpdateData(FALSE);

	m_switch = 2;

	long row = m_msflexgridoutput.get_RowSel();
	long col = m_msflexgridoutput.get_ColSel();
	if (col==2||col==3)
	{
		if (m_cellcolout==2||m_cellcolout==3)
		{
			if (m_cellrowout%2 == 1)
			{
				m_msflexgridoutput.put_Row(m_cellrowout);m_msflexgridoutput.put_Col(m_cellcolout);m_msflexgridoutput.put_CellBackColor(RGB(255,255,255));//单数行
			}else
			{
				m_msflexgridoutput.put_Row(m_cellrowout);m_msflexgridoutput.put_Col(m_cellcolout);m_msflexgridoutput.put_CellBackColor(COLOR_CELL);//双数行
			}


		}

		m_msflexgridoutput.put_Row(row);m_msflexgridoutput.put_Col(col);m_msflexgridoutput.put_CellBackColor(RGB(100,100,150));

	}
	else
	{
		if (m_cellcolout==2||m_cellcolout==3)
		{
			if (m_cellrowout%2 == 1)
			{
				m_msflexgridoutput.put_Row(m_cellrowout);m_msflexgridoutput.put_Col(m_cellcolout);m_msflexgridoutput.put_CellBackColor(RGB(255,255,255));
			}else
			{
				m_msflexgridoutput.put_Row(m_cellrowout);m_msflexgridoutput.put_Col(m_cellcolout);m_msflexgridoutput.put_CellBackColor(COLOR_CELL);
			}
		}
		if (col == 4)
		{
			m_msflexgridoutput.put_Row(row);m_msflexgridoutput.put_Col(col);m_msflexgridoutput.put_CellBackColor(FLEXGRID_CELL_GRAY_COLOR);//第5列灰色显示
		}else if (row%2 == 1)
		{
			m_msflexgridoutput.put_Row(row);m_msflexgridoutput.put_Col(col);m_msflexgridoutput.put_CellBackColor(RGB(255,255,255));
		}else
		{
			m_msflexgridoutput.put_Row(row);m_msflexgridoutput.put_Col(col);m_msflexgridoutput.put_CellBackColor(COLOR_CELL);
		}

	}

	m_cellrowout = row;
	m_cellcolout = col;



	//使用edition控件形式显示

	long lRow,lCol;
	lRow = m_msflexgridoutput.get_RowSel();
	lCol = m_msflexgridoutput.get_ColSel(); 

	if(lCol == 1)
	{
		CRect rect;
		m_msflexgridoutput.GetWindowRect(rect); 
		ScreenToClient(rect); 
		CDC* pDC =GetDC();

		int nTwipsPerDotX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX) ;
		int nTwipsPerDotY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY) ;
		
		long y = m_msflexgridoutput.get_RowPos(lRow)/nTwipsPerDotY;
		long x = m_msflexgridoutput.get_ColPos(lCol)/nTwipsPerDotX;
		
		long width = m_msflexgridoutput.get_ColWidth(lCol)/nTwipsPerDotX+1;
		long height = m_msflexgridoutput.get_RowHeight(lRow)/nTwipsPerDotY+1;
		
		CRect rcCell(x,y,x+width,y+height);
		
		rcCell.OffsetRect(rect.left+1,rect.top+1);
		ReleaseDC(pDC);
		CString strValue = m_msflexgridoutput.get_TextMatrix(lRow,lCol);


		if(1==lCol)		
		{		
			m_edit_output.MoveWindow(&rcCell,1);
			m_edit_output.ShowWindow(SW_SHOW);	
			m_edit_output.SetWindowText(strValue);	
			m_edit_output.SetFocus();	
			m_edit_output.SetCapture();
			int nLenth=strValue.GetLength();	
			m_edit_output.SetSel(nLenth,nLenth); 	

		}		
	}


	SetTimer(DATATIME_TIMER,1000,NULL);

}

void CDialogCM5::DblClickOutputMsflexgrid()
{
#if 0
	KillTimer(DATATIME_TIMER);
	m_combobox2_input.ShowWindow(SW_HIDE);
	UpdateData(FALSE);

	long lRow = m_msflexgridoutput.get_RowSel();//获取点击的行号	
	long lCol = m_msflexgridoutput.get_ColSel(); //获取点击的列号

	if (lCol == 2)
	{

		CString strgrid = m_msflexgridoutput.get_TextMatrix(lRow,lCol+1);
		CString m_strauto = _T("Manual");
		int retauto = m_strauto.Collate(strgrid);

		if (retauto == 0)
		{
			CString strValue = m_msflexgridoutput.get_TextMatrix(lRow,lCol);
			CString m_stron = _T("On");
			int ret = m_stron.Collate(strValue);
			if (ret == 0)
			{
				m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("Off"));

			}else
			{
				m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("On"));
			}
		}


	}else if (lCol == 3)
	{
		CString strgrid = m_msflexgridoutput.get_TextMatrix(lRow,lCol);
		CString m_strauto = _T("Auto");
		int retauto = m_strauto.Collate(strgrid);
		if (retauto == 0)
		{
			m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("Manual"));
		}else
		{
			m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("Auto"));
		}
	}

	SetTimer(DATATIME_TIMER,1000,NULL);
#endif

	KillTimer(DATATIME_TIMER);
	m_combobox2_input.ShowWindow(SW_HIDE);
	UpdateData(FALSE);

	long lRow = m_msflexgridoutput.get_RowSel();//获取点击的行号	
	long lCol = m_msflexgridoutput.get_ColSel(); //获取点击的列号

	if (lCol == 2)
	{

		CString strgrid = m_msflexgridoutput.get_TextMatrix(lRow,lCol+1);
		CString m_strauto = _T("Manual");
		int retauto = m_strauto.Collate(strgrid);


		if (retauto == 0)
		{
			unsigned short temp =1;				
			CString strValue = m_msflexgridoutput.get_TextMatrix(lRow,lCol);
			CString m_stron = _T("Off");
			int ret = m_stron.Collate(strValue);



			if (lRow<=8)
			{

				//参数写入设备
				//1-代表ON            0-代表OFF
				//1-代表手动Manual    0-代表自动Auto

				//174	1	Digital output1 - 8, valves/pumps

				int m_lRow= lRow;
				temp = temp<<m_lRow;				
				if (ret == 0)
				{

					temp =temp|cm5_register_value[174];

					int ww = write_one(g_tstat_id,174,temp,1);
					TRACE(_T("No:%d = write_one(on/off) is %d\n"),lRow,ww);
					if (ww>0)
					{
						m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("On"));
						cm5_register_value[174]=temp;
					}else
					{
						m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("Off"));
					}
				}
				else
				{

					temp = ~temp;
					temp =temp&cm5_register_value[174];

					int ww = write_one(g_tstat_id,174,temp,1);
					TRACE(_T("No:%d = write_one(on/off) is %d\n"),lRow,temp);
					if (ww>0)
					{
						m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("Off"));
						cm5_register_value[174]=temp;
					}
					else
					{
						m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("On"));
					}
				}

			}else   //lRow9~10
			{
				//175	1	Digital output9,10: boiler , manifold pump
				int m_lRow= lRow-9;
				temp = temp<<m_lRow;	
				if (ret == 0)
				{
					temp =temp|cm5_register_value[175];
					int ww = write_one(g_tstat_id,175,temp,1);
					TRACE(_T("No:%d = write_one(on/off) is %d\n"),lRow,ww);
					if (ww>0)
					{
						m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("On"));
						cm5_register_value[175]=temp;
					}else
					{
						m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("Off"));
					}
				}
				else
				{
					temp = ~temp;
					temp =temp&cm5_register_value[175];
					int ww = write_one(g_tstat_id,175,temp,1);
					TRACE(_T("No:%d = write_one(on/off) is %d\n"),lRow,temp);
					if (ww>0)
					{
						m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("Off"));
						cm5_register_value[175]=temp;
					}
					else
					{
						m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("On"));
					}
				}




			}

		}
	}else if (lCol == 3)
	{
		CString strgrid = m_msflexgridoutput.get_TextMatrix(lRow,lCol);
		CString m_strauto = _T("Auto");
		int retauto = m_strauto.Collate(strgrid);
		if (retauto == 0)
		{
			unsigned short temp =1;


			//   181	2	auto/manual feature of output 1 - 10

			temp = temp<<lRow-1;
			temp =temp|cm5_register_value[181];

			int ww = write_one(g_tstat_id,181,temp,1);
			TRACE(_T("No:%d = write_one is %d\n"),lRow,ww);
			if (ww>0)
			{
				m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("Manual"));
				cm5_register_value[181]=temp;
			}
			else
				m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("Auto"));





		}else
		{
			unsigned short temp =1;

			//   181	2	auto/manual feature of output 1 - 10
			temp = temp<<lRow-1;
			temp = ~temp;
			temp =temp&cm5_register_value[181];

			int ww = write_one(g_tstat_id,181,temp,1);
			TRACE(_T("No:%d = write_one is %d\n"),lRow,ww);
			if (ww>0)
			{
				m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("Auto"));
				cm5_register_value[181]=temp;
			}
			else
				m_msflexgridoutput.put_TextMatrix(lRow,lCol,_T("Manual"));

		}
	}

	SetTimer(DATATIME_TIMER,1000,NULL);
}

void CDialogCM5::AddDatabase( CString m_database,CString m_no,CString m_name )
{
 	_ConnectionPtr t_pCon;//for ado connection
	t_pCon.CreateInstance(_T("ADODB.Connection"));
	t_pCon->Open(g_strDatabasefilepath.GetString(),_T(""),_T(""),adModeUnknown);	

	CString strSql;
	strSql.Format(_T("insert into %s(num,name) values ('"+m_no+"','"+m_name+"')"),m_database);


	
	try
	{
		t_pCon->Execute(strSql.GetString(),NULL,adCmdText);

	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}

	if(t_pCon->State)
		t_pCon->Close();

}

CString CDialogCM5::ReadDatabase( CString m_database,CString m_no )
{	
	_ConnectionPtr t_pCon;//for ado connection
	_RecordsetPtr t_pRs;//for ado 
	CString ret_str;

	t_pCon.CreateInstance("ADODB.Connection");		
	t_pCon->Open(g_strDatabasefilepath.GetString(),"","",adModeUnknown);		   
	t_pRs.CreateInstance("ADODB.Recordset");

	_variant_t temp_variant;
	CString strTemp;

	CString temp_str;

	try
	 {
		temp_str.Format(_T("select * from %s where num ='%s'"),m_database,m_no);
		t_pRs->Open(_variant_t(temp_str),_variant_t((IDispatch *)t_pCon,true),adOpenStatic,adLockOptimistic,adCmdText);	 
	 }
	 catch(_com_error e)
	 {
		AfxMessageBox(e.Description()); 
	 }
		   

	int nTemp=-1;
	while(VARIANT_FALSE==t_pRs->EndOfFile)							
	{  
		ret_str = t_pRs->GetCollect("name");

		t_pRs->MoveNext();

	}

	if(t_pRs->State)
		t_pRs->Close(); 
	return ret_str;
}

void CDialogCM5::UpdateDatabase( CString m_database,CString m_num,CString m_name )
{
	_ConnectionPtr t_pCon;

	t_pCon.CreateInstance(_T("ADODB.Connection"));
	t_pCon->Open(g_strDatabasefilepath.GetString(),_T(""),_T(""),adModeUnknown);	

	CString strtemp;
	
	strtemp.Format(_T("update %s set name='%s' where num='%s'"),m_database,m_name,m_num);
	try
	{
		t_pCon->Execute(strtemp.GetString(),NULL,adCmdText);	
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}

	if(t_pCon->State)
		t_pCon->Close();

}

void CDialogCM5::JudgeTableExist( CString strtable,CString strsql )
{
	CADO m_cado;     
	m_cado.OnInitADOConn();
	//CString strTableName = _T("CM5_INPUT"); 		
	bool ret = m_cado.IsHaveTable(m_cado,strtable);
	
	//不存在 创建数据库表
	if (!ret) 
	{	
		//CString strsql = _T("create table CM5_INPUT(num text,name text)");
		//m_cado.Createtable(strsql);
		m_cado.m_pRecordset = m_cado.OpenRecordset(strsql);
		//初始化表
		//如果不初始化，则会有很多问题
		CString sql;
		sql.Format(_T("select * from %s"),strtable);
		m_cado.m_pRecordset = m_cado.OpenRecordset(sql);
		if (m_cado.m_pRecordset->EndOfFile)
		{
			int inend = 27;
			if(strtable.CompareNoCase(_T("CM5_OUTPUT")) == 0)
				inend = 10;

			for(int i = 0;i<inend;i++)
			{
				try 
				{
					m_cado.m_pRecordset->AddNew();
					m_cado.m_pRecordset->PutCollect("num",(_bstr_t)(i+1));
					m_cado.m_pRecordset->PutCollect("name",(_bstr_t)_T("Unused"));
// 					m_cado.m_pRecordset->PutCollect("Data",(_bstr_t)"On");
// 					m_cado.m_pRecordset->PutCollect("Range",(_bstr_t)_T("On/Off"));
// 					m_cado.m_pRecordset->PutCollect("AutoManual",(_bstr_t)"Auto");

					m_cado.m_pRecordset->Update();

				}


				catch(...)
				{

				}
			}
		}




	}
	m_cado.CloseConn();

}