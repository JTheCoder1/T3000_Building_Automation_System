// DialgMiniPanel.cpp : implementation file
//

#include "stdafx.h"
#include "DialgMiniPanel.h"
#include "../globle_function.h"
#include "../T3000.h"

static BOOL ifminidb = TRUE;

// CDialgMiniPanel

IMPLEMENT_DYNCREATE(CDialgMiniPanel, CFormView)


CDialgMiniPanel::CDialgMiniPanel()
	: CFormView(CDialgMiniPanel::IDD)
	, m_inaddress(0)
	, m_inSerialNum(0)
	, m_flFirmware(0)
	, m_inHardware(0)
	, m_CStrModel(_T(""))
	, m_inBaudrate(0)
	, m_datetime(_T(""))
{

}

CDialgMiniPanel::~CDialgMiniPanel()
{
}

void CDialgMiniPanel::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSFLEXGRID_INPUT, m_msflexgridinput);
	DDX_Control(pDX, IDC_MSFLEXGRID_OUTPUT_DO, m_msflexgridDO);
	DDX_Control(pDX, IDC_MSFLEXGRID_OUTPUT_AO, m_msflexgridAO);
	DDX_Text(pDX, IDC_EDIT1, m_inaddress);
	DDX_Text(pDX, IDC_EDIT3, m_inSerialNum);
	DDX_Text(pDX, IDC_EDIT2, m_flFirmware);
	DDX_Text(pDX, IDC_EDIT4, m_inHardware);
	DDX_Text(pDX, IDC_EDIT5, m_CStrModel);
	DDX_Text(pDX, IDC_EDIT6, m_inBaudrate);
	DDX_Text(pDX, IDC_STATIC1, m_datetime);
	DDX_Text(pDX, IDC_STATIC1, m_datetime);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_editinput);
	DDX_Control(pDX, IDC_EDITOUTPUTDO, m_editoutputdo);
	DDX_Control(pDX, IDC_EDIT_OUTPUTAO, m_editoutputao);
}

BEGIN_MESSAGE_MAP(CDialgMiniPanel, CFormView)
	ON_WM_TIMER()
	ON_EN_KILLFOCUS(IDC_EDIT_INPUT, &CDialgMiniPanel::OnEnKillfocusEditInput)
	ON_EN_KILLFOCUS(IDC_EDITOUTPUTDO, &CDialgMiniPanel::OnEnKillfocusEditoutputdo)
	ON_EN_KILLFOCUS(IDC_EDIT_OUTPUTAO, &CDialgMiniPanel::OnEnKillfocusEditOutputao)
END_MESSAGE_MAP()


// CDialgMiniPanel diagnostics

#ifdef _DEBUG
void CDialgMiniPanel::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDialgMiniPanel::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDialgMiniPanel message handlers

void CDialgMiniPanel::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
#if 1

	//显示横标题
	m_msflexgridinput.put_TextMatrix(0,1,_T("Input Name"));
	m_msflexgridinput.put_TextMatrix(0,2,_T("Value"));
	//m_msflexgridinput.put_TextMatrix(0,3,_T("Auto/Manual"));
	m_msflexgridinput.put_TextMatrix(0,3,_T("Range"));
	m_msflexgridinput.put_TextMatrix(0,4,_T("Function"));


	//设置排/行数量
	m_msflexgridinput.put_Cols(5);
	m_msflexgridinput.put_Rows(33);//包括标题栏


	//设置列宽	
	m_msflexgridinput.put_ColWidth(0,400);
	m_msflexgridinput.put_ColWidth(3,1500);
	m_msflexgridinput.put_ColWidth(4,1000);
	//居中显示
	for (int col=0;col<5;col++)
	{ 
		m_msflexgridinput.put_ColAlignment(col,4);
	}

	//彩色显示
	for(int i=1;i<33;i++)		//排数量
	{

		for(int k=0;k<5;k++)	//列数量
		{
			if (i%2==1)
			{
				m_msflexgridinput.put_Row(i);m_msflexgridinput.put_Col(k);m_msflexgridinput.put_CellBackColor(RGB(255,255,255));
			}
			else
			{
				m_msflexgridinput.put_Row(i);m_msflexgridinput.put_Col(k);m_msflexgridinput.put_CellBackColor(COLOR_CELL);
			}
		}
	}




	//第3，4列11-26灰色显示
// 	for (int i=1;i<33;i++)
// 	{
// 
// 		m_msflexgridinput.put_TextMatrix(i,4,_T("°C"));	  
// 		m_msflexgridinput.put_Row(i);
// 		m_msflexgridinput.put_Col(4);
// 		m_msflexgridinput.put_CellBackColor(FLEXGRID_CELL_GRAY_COLOR);	   //灰色
// 	}


	//显示纵标题
	CString str;
	for(int i=1;i<33;i++)
	{

		str.Format(_T("%d"),i);

		m_msflexgridinput.put_TextMatrix(i,0,str);	 

// 		str = _T("Input ")+str;
// 		m_msflexgridinput.put_TextMatrix(i,1,str);
		m_msflexgridinput.put_TextMatrix(i,4,_T("Default"));	

	}

	//显示结果值
//	str =_T("");
//	for(int i=1;i<33;i++)
//	{

// 		str.Format(_T("%d"),i);
// 
// 		m_msflexgridinput.put_TextMatrix(i,0,str);
// 		str = _T("Input ")+str;
// 		m_msflexgridinput.put_TextMatrix(i,1,str);
// 
// 		//m_msflexgridinput.put_TextMatrix(i,3,_T("Auto"));
// 		m_msflexgridinput.put_TextMatrix(i,3,_T("On/Off"));
//		m_msflexgridinput.put_TextMatrix(i,4,_T("Default"));	


//	}


	//unsigned char writevalue[1];
	//writevalue[0] = 0;
	//int flg = Write_Multi(g_tstat_id,writevalue,144,10);
	//TRACE(_T("flg=%d\n"),flg);
	//ASSERT(flg>0);


	//============================================================================================================界面Output DO部份列表框
 
	//设置行/列数量
	m_msflexgridDO.put_Rows(13);
	m_msflexgridDO.put_Cols(6);
	//设置列宽	
	m_msflexgridDO.put_ColWidth(0,400);
	m_msflexgridDO.put_ColWidth(3,1500);

	//显示横标题
	m_msflexgridDO.put_TextMatrix(0,1,_T("Input Name"));
	m_msflexgridDO.put_TextMatrix(0,2,_T("Value"));
	m_msflexgridDO.put_TextMatrix(0,3,_T("Auto/Manual"));
	m_msflexgridDO.put_TextMatrix(0,4,_T("Range"));
	m_msflexgridDO.put_TextMatrix(0,5,_T("Function"));



	//居中显示
	for (int col=0;col<6;col++)
	{ 
		m_msflexgridDO.put_ColAlignment(col,4);
	}

	//彩色显示
	for(int i=1;i<13;i++)		//排数量
	{

		for(int k=0;k<6;k++)	//列数量
		{
			if (i%2==1)
			{
				m_msflexgridDO.put_Row(i);m_msflexgridDO.put_Col(k);m_msflexgridDO.put_CellBackColor(RGB(255,255,255));
			}
			else
			{
				m_msflexgridDO.put_Row(i);m_msflexgridDO.put_Col(k);m_msflexgridDO.put_CellBackColor(COLOR_CELL);
			}
		}
	}
	//显示纵标题
	CString str_output;
	for(int i=1;i<13;i++)
	{

		str_output.Format(_T("%d"),i);
		m_msflexgridDO.put_TextMatrix(i,0,str_output);	
// 		str_output = _T("Output ")+str_output;
// 		m_msflexgridDO.put_TextMatrix(i,1,str_output);
// 
// 		//m_msflexgrid_output.put_TextMatrix(i,3,_T("Off"));
// 		m_msflexgridDO.put_TextMatrix(i,4,_T("On/Off"));
 		m_msflexgridDO.put_TextMatrix(i,5,_T("Default"));
		m_msflexgridDO.put_Row(i);
		m_msflexgridDO.put_Col(4);
		m_msflexgridDO.put_CellBackColor(FLEXGRID_CELL_GRAY_COLOR);
	}



	//============================================================================================================界面Output AO部份列表框

	//设置行/列数量
	m_msflexgridAO.put_Rows(13);
	m_msflexgridAO.put_Cols(6);
	//设置列宽	
	m_msflexgridAO.put_ColWidth(0,400);
	m_msflexgridAO.put_ColWidth(3,1500);

	//显示横标题
	m_msflexgridAO.put_TextMatrix(0,1,_T("Input Name"));
	m_msflexgridAO.put_TextMatrix(0,2,_T("Value"));
	m_msflexgridAO.put_TextMatrix(0,3,_T("Auto/Manual"));
	m_msflexgridAO.put_TextMatrix(0,4,_T("Range"));
	m_msflexgridAO.put_TextMatrix(0,5,_T("Function"));



	//居中显示
	for (int col=0;col<6;col++)
	{ 
		m_msflexgridAO.put_ColAlignment(col,4);
	}

	//彩色显示
	for(int i=1;i<13;i++)		//排数量
	{

		for(int k=0;k<6;k++)	//列数量
		{
			if (i%2==1)
			{
				m_msflexgridAO.put_Row(i);m_msflexgridAO.put_Col(k);m_msflexgridAO.put_CellBackColor(RGB(255,255,255));
			}
			else
			{
				m_msflexgridAO.put_Row(i);m_msflexgridAO.put_Col(k);m_msflexgridAO.put_CellBackColor(COLOR_CELL);
			}
		}
	}
	//显示纵标题
	CString str_outputAO;
	for(int i=1;i<13;i++)
	{

		str_outputAO.Format(_T("%d"),i);
		m_msflexgridAO.put_TextMatrix(i,0,str_outputAO);	
// 		str_outputAO = _T("Output ")+str_outputAO;
// 		m_msflexgridAO.put_TextMatrix(i,1,str_outputAO);
// 
// 		//m_msflexgrid_output.put_TextMatrix(i,3,_T("Off"));
// 		m_msflexgridAO.put_TextMatrix(i,4,_T("On/Off"));
		m_msflexgridAO.put_TextMatrix(i,5,_T("Default"));
		m_msflexgridAO.put_Row(i);
		m_msflexgridAO.put_Col(4);
		m_msflexgridAO.put_CellBackColor(FLEXGRID_CELL_GRAY_COLOR);
	}

#endif 
	

}

void CDialgMiniPanel::Fresh()
{
	SetTimer(MiniPanelTimer,1000,NULL);
  	GetDatabase();
  	ShowMinipDialog();
}

void CDialgMiniPanel::ShowMinipDialog()
{

#if 1

	//============================================================System Parameters===============================================================

	m_CStrModel = _T("Mini Panel");
	//6	1	Modbus device address
	m_inaddress = _wtoi(vecminipanel.at(6).CStvalue);

	UINT nSelectSerialNumber = _wtoi(vecminipanel.at(0).CStvalue)+_wtoi(vecminipanel.at(1).CStvalue)*256+_wtoi(vecminipanel.at(2).CStvalue)*256*256+_wtoi(vecminipanel.at(3).CStvalue)*256*256*256;
	m_inSerialNum=nSelectSerialNumber;

	m_flFirmware = ((float)(_wtoi(vecminipanel.at(5).CStvalue)*256+_wtoi(vecminipanel.at(4).CStvalue)))/10;

	m_inHardware = _wtoi(vecminipanel.at(8).CStvalue);
	m_inBaudrate = _wtoi(vecminipanel.at(9).CStvalue);



	//==================================================Input============================================================
	//address: input 148~179
	//address:Switch 124~147
	CString strresult;

	for(int i = 1;i<=32;i++)
	{  
// 		strresult.Format(_T("%d°C"),10);
// 		m_msflexgridinput.put_TextMatrix(i,2,strresult);
// 		m_msflexgridinput.put_TextMatrix(i,1,_T("west door"));
// 		m_msflexgridinput.put_TextMatrix(i,3,_T("0-100%"));


		m_msflexgridinput.put_TextMatrix(i,2,vecminipanel.at(148-1+i).CStvalue);
		m_msflexgridinput.put_TextMatrix(i,1,vecminipanel.at(148-1+i).CStName);
		m_msflexgridinput.put_TextMatrix(i,3,vecminipanel.at(148-1+i).CStrange);
	}


	//====================================================Output============================================================	
	//100~111

	CString CstresultDO;
	for(int i = 1;i<=12;i++)
	{  
// 		CstresultDO.Format(_T("%d"),10);
// 		m_msflexgridDO.put_TextMatrix(i,2,CstresultDO);
// 		m_msflexgridDO.put_TextMatrix(i,1,_T("east door"));
// 		m_msflexgridDO.put_TextMatrix(i,3,_T("AUTO"));

		m_msflexgridDO.put_TextMatrix(i,2,vecminipanel.at(100-1+i).CStvalue);
		m_msflexgridDO.put_TextMatrix(i,1,vecminipanel.at(100-1+i).CStName);
		m_msflexgridDO.put_TextMatrix(i,3,vecminipanel.at(124-1+i).CStautomannel);
		m_msflexgridDO.put_TextMatrix(i,4,vecminipanel.at(100-1+i).CStrange);


	}




	//112~123
	CString CstresultAO;
	for(int i = 1;i<=12;i++)
	{  
// 		CstresultAO.Format(_T("%d"),10);
// 		ms_msflexgridAO.put_TextMatrix(i,2,CstresultAO);
// 		ms_msflexgridAO.put_TextMatrix(i,1,_T("south door"));
// 		ms_msflexgridAO.put_TextMatrix(i,3,_T("AUTO"));

		m_msflexgridAO.put_TextMatrix(i,2,vecminipanel.at(112-1+i).CStvalue);
		m_msflexgridAO.put_TextMatrix(i,1,vecminipanel.at(112-1+i).CStName);
		m_msflexgridAO.put_TextMatrix(i,3,vecminipanel.at(136-1+i).CStautomannel);
		m_msflexgridAO.put_TextMatrix(i,4,vecminipanel.at(112-1+i).CStrange);
	}

	UpdateData(FALSE);
#endif

	}

BOOL CDialgMiniPanel::GetDatabase()
{ 
	CADO m_ado;
	m_ado.OnInitADOConn();

	if(ifminidb)
	{

	//判断MiniPanel数据库是否存在,Auto/Manual text,Range text

	CString temptable = _T("MiniPanel");
	CString tempsql = _T("create table MiniPanel(Address Number Primary Key,Name text,Data text,AutoManual text,Range text)");//
		
	bool m_judge = m_ado.IsHaveTable(m_ado,temptable);

	//不存在 创建数据库表
	if (!m_judge) 
	{	
 		m_ado.m_pRecordset = m_ado.OpenRecordset(tempsql);
		//初始化表
		CString sql = _T("select * from MiniPanel");
		m_ado.m_pRecordset = m_ado.OpenRecordset(sql);
		if (m_ado.m_pRecordset->EndOfFile)
		{

		for(int i = 0;i<230;i++)
		{
			try 
			{
				m_ado.m_pRecordset->AddNew();
				m_ado.m_pRecordset->PutCollect("Address",(_bstr_t)(i+1));
				m_ado.m_pRecordset->PutCollect("Name",(_bstr_t)_T("Unused"));
				m_ado.m_pRecordset->PutCollect("Data",(_bstr_t)"On");
				m_ado.m_pRecordset->PutCollect("Range",(_bstr_t)_T("On/Off"));
				m_ado.m_pRecordset->PutCollect("AutoManual",(_bstr_t)"Auto");

				m_ado.m_pRecordset->Update();

			}


			catch(...)
			{

			}
		}
		}
		

	}

	ifminidb = FALSE;
	}

#if 1
	vecminipanel.clear();
 	CString SQL = _T("select * from MiniPanel"); 
 	m_ado.m_pRecordset = m_ado.OpenRecordset(SQL);
	_variant_t vartemp;
	while(!m_ado.m_pRecordset->EndOfFile)
	{
		MINImini.iaddress =m_ado.m_pRecordset->GetCollect(_T("Address"));
		vartemp =m_ado.m_pRecordset->GetCollect(_T("Name"));
		if (vartemp.vt==VT_NULL)
			MINImini.CStName =_T("");
		else
			MINImini.CStName =vartemp;


		vartemp =m_ado.m_pRecordset->GetCollect(_T("Data"));
		if (vartemp.vt==VT_NULL)
			MINImini.CStvalue =_T("");
		else
			MINImini.CStvalue =vartemp;


		vartemp =m_ado.m_pRecordset->GetCollect(_T("AutoManual"));
		if (vartemp.vt==VT_NULL)
			MINImini.CStautomannel =_T("");
		else
			MINImini.CStautomannel =vartemp;


		vartemp =m_ado.m_pRecordset->GetCollect(_T("Range"));
		if (vartemp.vt==VT_NULL)
			MINImini.CStrange =_T("");
		else
			MINImini.CStrange =vartemp;

		m_ado.m_pRecordset->MoveNext();

		vecminipanel.push_back(MINImini);
	}

//读取本电脑当前正在使用的串口。
	CString CSTcompot;
	BOOL BOdefault;
	SQL = _T("select * from Building");
	m_ado.m_pRecordset = m_ado.OpenRecordset(SQL);
	while(!m_ado.m_pRecordset->EndOfFile)
	{
		CSTcompot =(_variant_t)m_ado.m_pRecordset->GetCollect(_T("Com_Port"));
		BOdefault =(_variant_t)m_ado.m_pRecordset->GetCollect(_T("Default_SubBuilding"));//TRUE = -1即非0，FALSE就是0
		m_ado.m_pRecordset->MoveNext();

		if (BOdefault)
		{
			comnum = _wtoi(CSTcompot.Mid(3));
		}

	}



	m_ado.CloseRecordset();
	m_ado.CloseConn();





#endif 



	return TRUE;



}

BOOL CDialgMiniPanel::MiniUpdateData()
{
	KillTimer(MiniPanelTimer);
#if 1
	//读取串口号，从数据库
	open_com(comnum);

	int sumret = 0;
	BOOL flag = FALSE;

	//读取miniPanel数据
	BOOL ret_bool = FALSE;
	long start = clock(),end(0); 		


	memset(&shmPRegister,0,sizeof(shmPRegister)); 
	for(int i=0;i<4;i++)
	{
		int ret = Read_Multi(g_tstat_id,&shmPRegister[i*64],i*64,64,2);
		sumret += ret;
		
		if (sumret<0)
		{
			TRACE(_T("write_multi ret sum = %d\n"),sumret);
			SetTimer(MiniPanelTimer,1000,NULL);
			return FALSE;
		}
			
	}



	for (int i = 0;i<230;i++)
	{
	//	vecminipanel.at(i).CStvalue = shmPRegister[i];		// error C2593: 'operator =' is ambiguous
		vecminipanel.at(i).CStvalue.Format(_T("%d"),shmPRegister[i]);	
		if (i>=124&&i<=147)
		{
			switch(shmPRegister[i])
			{
			case 0:
				vecminipanel.at(i).CStautomannel = _T("OFF");				
				break;
			case 1:
				vecminipanel.at(i).CStautomannel = _T("Manual");				
				break;
			case 2:
				vecminipanel.at(i).CStautomannel = _T("Auto");				
				break;
			default:
				break;
			}

		}

		if (i>=100&&i<=123)
		{

			if (shmPRegister[i]>512)
				vecminipanel.at(i).CStvalue = _T("ON"); 
			else
				vecminipanel.at(i).CStvalue = _T("OFF");

		}
	}

	if (sumret>200)
	{
		flag = TRUE;
	}
	TRACE(_T("write_multi ret sum = %d\n"),sumret);

	end = clock();
	long resultvalue = (end - start)/1000;
	TRACE(_T("GetData() usetime %d second\n"),resultvalue);

	
	SetTimer(MiniPanelTimer,1000,NULL);
#endif
	return flag;
}



void CDialgMiniPanel::OnTimer(UINT_PTR nIDEvent)
{

	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CView* pNewView = pMain->m_pViews[6];
	CView* pActiveView = pMain->GetActiveView();

	if ( pNewView != pActiveView )    // current is minipanel dialog
	{
		KillTimer(MiniPanelTimer);
	}

#if 1
	static int nCount = 0,nCount2 = 0;

	nCount++;
	nCount2++;

	if (MiniPanelTimer == nIDEvent)
	{
		CTime now;
		now = CTime::GetCurrentTime();
		m_datetime = now.Format(_T("%A,%B %d,%Y  %H:%M:%S"));		// "Saturday, April 12, 2012"		

		UpdateData(FALSE);

		if (nCount% 30 == 0)
		{
	
			nCount = 0;

			BOOL flag = MiniUpdateData();

			if (flag)
			{
				ShowMinipDialog();
				SetPaneString(2,_T("Online!"));
				
			}

		}
		if (nCount2%120 == 0)
		{
			nCount2 = 0;
			Updatedatabase();

		}


	}

#endif
	CFormView::OnTimer(nIDEvent);
}

void CDialgMiniPanel::Updatedatabase()
{
	TRACE(_T("Updatedatabase()start!\n"));
	KillTimer(MiniPanelTimer);
	//存入数据库中
	CADO saveADO;
	saveADO.OnInitADOConn();
	CString sql = _T("select * from MiniPanel");
	saveADO.m_pRecordset = saveADO.OpenRecordset(sql);
	if (!saveADO.m_pRecordset->EndOfFile)
	{
		saveADO.m_pRecordset->MoveFirst();

	for(int i = 0;i<230;i++)
	{
		try 
		{

			//saveADO.m_pRecordset->AddNew();
			//saveADO.m_pRecordset->Move(pos,vtMissing);
			// 			cstnum.Format(_T("%d"),i+1);
			// 			saveADO.m_pRecordset->PutCollect("Address",(_bstr_t)cstnum);
			// 			saveADO.m_pRecordset->PutCollect("Name",(_bstr_t)_T("output"));

			saveADO.m_pRecordset->PutCollect("Address",(_bstr_t)i);
			saveADO.m_pRecordset->PutCollect("Name",(_bstr_t)vecminipanel.at(i).CStName);
			saveADO.m_pRecordset->PutCollect("Data",(_bstr_t)shmPRegister[i]);
			saveADO.m_pRecordset->PutCollect("Range",(_bstr_t)vecminipanel.at(i).CStrange);
			

			if (i>=124&&i<=147)
			{
				switch ((int)(_variant_t)shmPRegister[i])
				{
				case 0:   //0- off 1 - mannel 2 - auto
					saveADO.m_pRecordset->PutCollect("AutoManual",(_bstr_t)"OFF");
					break;
				case 1:
					saveADO.m_pRecordset->PutCollect("AutoManual",(_bstr_t)"Manual");
					break;
				case 2:
					saveADO.m_pRecordset->PutCollect("AutoManual",(_bstr_t)"Auto");
					break;
				default:
					break;

				}
			}


			//  		saveADO.m_pRecordset->PutCollect("Auto/Manual",(_bstr_t)"auto");
			//  		saveADO.m_pRecordset->PutCollect("Range",(_bstr_t)"10%-100%");
			saveADO.m_pRecordset->Update();
			saveADO.m_pRecordset->MoveNext();
		}


		catch(...)
		{
			//MessageBox(_T("Write dababase false!"));
			
			SetPaneString(2,_T("Write dababase false!"));
			return ;
		}
	}
	}
	else
	{
		for(int i = 0;i<230;i++)
		{
			try 
			{

				//saveADO.m_pRecordset->AddNew();
				//saveADO.m_pRecordset->Move(pos,vtMissing);
				// 			cstnum.Format(_T("%d"),i+1);
				// 			saveADO.m_pRecordset->PutCollect("Address",(_bstr_t)cstnum);
				// 			saveADO.m_pRecordset->PutCollect("Name",(_bstr_t)_T("output"));
				saveADO.m_pRecordset->AddNew();
				saveADO.m_pRecordset->PutCollect("Address",(_bstr_t)i);
				saveADO.m_pRecordset->PutCollect("Name",(_bstr_t)vecminipanel.at(i).CStName);
				saveADO.m_pRecordset->PutCollect("Data",(_bstr_t)shmPRegister[i]);
				saveADO.m_pRecordset->PutCollect("Range",(_bstr_t)vecminipanel.at(i).CStrange);


				if (i>=124&&i<=147)
				{
					switch ((int)(_variant_t)shmPRegister[i])
					{
					case 0:   //0- off 1 - mannel 2 - auto
						saveADO.m_pRecordset->PutCollect("AutoManual",(_bstr_t)"OFF");
						break;
					case 1:
						saveADO.m_pRecordset->PutCollect("AutoManual",(_bstr_t)"Manual");
						break;
					case 2:
						saveADO.m_pRecordset->PutCollect("AutoManual",(_bstr_t)"Auto");
						break;
					default:
						break;

					}
				}


				//  		saveADO.m_pRecordset->PutCollect("Auto/Manual",(_bstr_t)"auto");
				//  		saveADO.m_pRecordset->PutCollect("Range",(_bstr_t)"10%-100%");
				saveADO.m_pRecordset->Update();

			}


			catch(...)
			{
				//MessageBox(_T("Write dababase false!"));

				SetPaneString(2,_T("Write dababase false!"));
				return ;
			}
		}

	}

	saveADO.CloseRecordset();
	saveADO.CloseConn(); 

	SetTimer(MiniPanelTimer,1000,NULL);

}
void CDialgMiniPanel::OnEnKillfocusEditInput()
{

	CString strText;
	m_editinput.GetWindowText(strText); 
	m_editinput.ShowWindow(SW_HIDE);  
	int lRow = m_msflexgridinput.get_RowSel();	
	int lCol = m_msflexgridinput.get_ColSel(); 

	m_msflexgridinput.put_TextMatrix(lRow,lCol,strText);
	CString strrow;
	strrow.Format(_T("%d"),lRow);
	CString stremp;
	stremp = _T("CM5_INPUT");
	int passvalue = lRow+147;
	writedbinputname(passvalue,strText);

	CRect rcCell(0,0,1,1);
	m_editinput.MoveWindow(&rcCell,1);
	SetTimer(MiniPanelTimer,1000,NULL);
	TRACE(_T("KillfocusEditInput()end!\nSetTimer()start\n"));

}
BEGIN_EVENTSINK_MAP(CDialgMiniPanel, CFormView)
	ON_EVENT(CDialgMiniPanel, IDC_MSFLEXGRID_INPUT, DISPID_CLICK, CDialgMiniPanel::ClickMsflexgridInput, VTS_NONE)
	ON_EVENT(CDialgMiniPanel, IDC_MSFLEXGRID_OUTPUT_DO, DISPID_CLICK, CDialgMiniPanel::ClickMsflexgridOutputDo, VTS_NONE)
	ON_EVENT(CDialgMiniPanel, IDC_MSFLEXGRID_OUTPUT_AO, DISPID_CLICK, CDialgMiniPanel::ClickMsflexgridOutputAo, VTS_NONE)
END_EVENTSINK_MAP()

void CDialgMiniPanel::ClickMsflexgridInput()
{

	//使用edition控件形式显示

	long lRow,lCol;
	lRow = m_msflexgridinput.get_RowSel();
	lCol = m_msflexgridinput.get_ColSel(); 

	if(lCol == 1)
	{
		CRect rect;
		m_msflexgridinput.GetWindowRect(rect); //
		ScreenToClient(rect); //
		CDC* pDC =GetDC();

		int nTwipsPerDotX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX) ;
		int nTwipsPerDotY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY) ;

		long y = m_msflexgridinput.get_RowPos(lRow)/nTwipsPerDotY;
		long x = m_msflexgridinput.get_ColPos(lCol)/nTwipsPerDotX;

		long width = m_msflexgridinput.get_ColWidth(lCol)/nTwipsPerDotX+1;
		long height = m_msflexgridinput.get_RowHeight(lRow)/nTwipsPerDotY+1;

		CRect rcCell(x,y,x+width,y+height);

		rcCell.OffsetRect(rect.left+1,rect.top+1);
		ReleaseDC(pDC);
		CString strValue = m_msflexgridinput.get_TextMatrix(lRow,lCol);

		if(1==lCol)		
		{	
			KillTimer(MiniPanelTimer);
			TRACE(_T("ClickMsflexgridInput()start!\nKillTimer()start\n"));
			m_editinput.MoveWindow(&rcCell,1);
			m_editinput.ShowWindow(SW_SHOW);	
			m_editinput.SetWindowText(strValue);	
			m_editinput.SetFocus();
			m_editinput.SetCapture();//使随后的鼠标输入都被发送到这个CWnd 
			int nLenth=strValue.GetLength();	
			m_editinput.SetSel(nLenth,nLenth); 

		}	

	}


}

void CDialgMiniPanel::OnEnKillfocusEditoutputdo()
{
	CString strText;
	m_editoutputdo.GetWindowText(strText); 
	m_editoutputdo.ShowWindow(SW_HIDE);  
	int lRow = m_msflexgridDO.get_RowSel();	
	int lCol = m_msflexgridDO.get_ColSel(); 

	m_msflexgridDO.put_TextMatrix(lRow,lCol,strText);
	CString strrow;
	strrow.Format(_T("%d"),lRow);
	CString stremp;
	stremp = _T("CM5_INPUT");
	int passvalue = lRow+99;
	writedbinputname(passvalue,strText);

	CRect rcCell(0,0,1,1);
	m_editoutputdo.MoveWindow(&rcCell,1);
	SetTimer(MiniPanelTimer,1000,NULL);
}

void CDialgMiniPanel::OnEnKillfocusEditOutputao()
{

	CString strText;
	m_editoutputao.GetWindowText(strText); 
	m_editoutputao.ShowWindow(SW_HIDE);  
	int lRow = m_msflexgridAO.get_RowSel();	
	int lCol = m_msflexgridAO.get_ColSel(); 

	m_msflexgridAO.put_TextMatrix(lRow,lCol,strText);
	CString strrow;
	strrow.Format(_T("%d"),lRow);
	CString stremp;
	stremp = _T("CM5_INPUT");
	int passvalue = lRow+111;
	writedbinputname(passvalue,strText);

	CRect rcCell(0,0,1,1);
	m_editoutputao.MoveWindow(&rcCell,1);
	SetTimer(MiniPanelTimer,1000,NULL);
}

void CDialgMiniPanel::ClickMsflexgridOutputDo()
{

	//使用edition控件形式显示

	long lRow,lCol;
	lRow = m_msflexgridDO.get_RowSel();
	lCol = m_msflexgridDO.get_ColSel(); 

	if(lCol == 1)
	{
		CRect rect;
		m_msflexgridDO.GetWindowRect(rect); //
		ScreenToClient(rect); //
		CDC* pDC =GetDC();

		int nTwipsPerDotX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX) ;
		int nTwipsPerDotY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY) ;

		long y = m_msflexgridDO.get_RowPos(lRow)/nTwipsPerDotY;
		long x = m_msflexgridDO.get_ColPos(lCol)/nTwipsPerDotX;

		long width = m_msflexgridDO.get_ColWidth(lCol)/nTwipsPerDotX+1;
		long height = m_msflexgridDO.get_RowHeight(lRow)/nTwipsPerDotY+1;

		CRect rcCell(x,y,x+width,y+height);

		rcCell.OffsetRect(rect.left+1,rect.top+1);
		ReleaseDC(pDC);
		CString strValue = m_msflexgridDO.get_TextMatrix(lRow,lCol);

		if(1==lCol)		
		{
			KillTimer(MiniPanelTimer);
			TRACE(_T("ClickMsflexgridInput()start!\nKillTimer()start\n"));
			m_editoutputdo.MoveWindow(&rcCell,1);
			m_editoutputdo.ShowWindow(SW_SHOW);	
			m_editoutputdo.SetWindowText(strValue);	
			m_editoutputdo.SetFocus();
			m_editoutputdo.SetCapture();//使随后的鼠标输入都被发送到这个CWnd 
			int nLenth=strValue.GetLength();	
			m_editoutputdo.SetSel(nLenth,nLenth); 

		}	

	}

}

void CDialgMiniPanel::ClickMsflexgridOutputAo()
{

	//使用edition控件形式显示

	long lRow,lCol;
	lRow = m_msflexgridAO.get_RowSel();
	lCol = m_msflexgridAO.get_ColSel(); 

	if(lCol == 1)
	{
		CRect rect;
		m_msflexgridAO.GetWindowRect(rect); //
		ScreenToClient(rect); //
		CDC* pDC =GetDC();

		int nTwipsPerDotX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX) ;
		int nTwipsPerDotY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY) ;

		long y = m_msflexgridAO.get_RowPos(lRow)/nTwipsPerDotY;
		long x = m_msflexgridAO.get_ColPos(lCol)/nTwipsPerDotX;

		long width = m_msflexgridAO.get_ColWidth(lCol)/nTwipsPerDotX+1;
		long height = m_msflexgridAO.get_RowHeight(lRow)/nTwipsPerDotY+1;

		CRect rcCell(x,y,x+width,y+height);

		rcCell.OffsetRect(rect.left+1,rect.top+1);
		ReleaseDC(pDC);
		CString strValue = m_msflexgridAO.get_TextMatrix(lRow,lCol);

		if(1==lCol)		
		{	
			KillTimer(MiniPanelTimer);
			TRACE(_T("ClickMsflexgridInput()start!\nKillTimer()start\n"));
			m_editoutputao.MoveWindow(&rcCell,1);
			m_editoutputao.ShowWindow(SW_SHOW);	
			m_editoutputao.SetWindowText(strValue);	
			m_editoutputao.SetFocus();
			m_editoutputao.SetCapture();//使随后的鼠标输入都被发送到这个CWnd 
			int nLenth=strValue.GetLength();	
			m_editoutputao.SetSel(nLenth,nLenth); 

		}	

	}

}

void CDialgMiniPanel::writedbinputname( int& num,CString& str )
{


	//存入数据库中
	CADO saveADO;
	saveADO.OnInitADOConn();
	CString sql = _T("select * from MiniPanel");
	saveADO.m_pRecordset = saveADO.OpenRecordset(sql);
	CString cstnum;
		try 
		{
			saveADO.m_pRecordset->Move(num,vtMissing);
			saveADO.m_pRecordset->PutCollect("Name",(_bstr_t)str);
			saveADO.m_pRecordset->Update();

		}
		catch(...)
		{
			SetPaneString(2,_T("'Input Name' Write dababase false!"));
			return ;
		}


	vecminipanel.at(num).CStName = str;
	saveADO.CloseRecordset();
	saveADO.CloseConn(); 


}