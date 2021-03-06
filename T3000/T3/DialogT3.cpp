// DialogT3.cpp : implementation file
//

#include "stdafx.h"
#include "DialogT3.h"
 #include "../globle_function.h"
#include "../T3000.h"
#include "../MainFrm.h"
#include "../ado/ADO.h"



#define   T3_MODEL   100
static BOOL ift3db = TRUE;
// CDialogT3
IMPLEMENT_DYNCREATE(CDialogT3, CFormView)

CDialogT3::CDialogT3()
	: CFormView(CDialogT3::IDD)
	, m_address(0)
	, m_firmware(0)
	, m_serial(0)
	, m_hardware(0)
	, m_model(_T(""))
	, m_picVersion(0)
{

}

CDialogT3::~CDialogT3()
{
}

void CDialogT3::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_T3ADDRESS, m_address);
	DDX_Text(pDX, IDC_EDIT_T3FIRMWARE, m_firmware);
	DDX_Text(pDX, IDC_EDIT_T3SERIAL, m_serial);
	DDX_Text(pDX, IDC_EDIT_T3HARDWARE, m_hardware);
	DDX_Text(pDX, IDC_EDIT_T3MODEL, m_model);
	DDX_Text(pDX, IDC_EDIT_T3PICVERSION, m_picVersion);
	DDX_Control(pDX, IDC_MSFLEXGRID_INPUT, m_msflexgrid_input);
	DDX_Control(pDX, IDC_MSFLEXGRID_OUTPUT, m_msflexgrid_output);
}

BEGIN_MESSAGE_MAP(CDialogT3, CFormView)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDialogT3 diagnostics

#ifdef _DEBUG
void CDialogT3::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDialogT3::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}


#endif
#endif //_DEBUG


// CDialogT3 message handlers

void CDialogT3::OnInitialUpdate()
{
	 CFormView::OnInitialUpdate();


	//============================================================================================================界面Input部份列表框


// 	//显示横标题
// 	m_msflexgrid_input.put_TextMatrix(0,1,_T("Input Name"));
// 	m_msflexgrid_input.put_TextMatrix(0,2,_T("Value"));
// 	//m_msflexgrid_input.put_TextMatrix(0,3,_T("Hand/Off/Auto"));
// 	m_msflexgrid_input.put_TextMatrix(0,3,_T("Input Filter"));
// 	m_msflexgrid_input.put_TextMatrix(0,4,_T("Range"));
// 	m_msflexgrid_input.put_TextMatrix(0,5,_T("Function"));
// 
// 
// 	//设置排/行数量
// 	m_msflexgrid_input.put_Cols(6);
// 	m_msflexgrid_input.put_Rows(9);
// 
// 	//设置列宽	
// 	m_msflexgrid_input.put_ColWidth(0,400);
// 	//m_msflexgrid_input.put_ColWidth(3,1500);
// 
// 	//居中显示
// 	for (int col=0;col<6;col++)
// 	{ 
// 		m_msflexgrid_input.put_ColAlignment(col,4);
// 	}
// 
// 	//彩色显示
// 	for(int i=1;i<9;i++)		//排数量
// 	{
// 
// 		for(int k=0;k<6;k++)	//列数量
// 		{
// 			if (i%2==1)
// 			{
// 				m_msflexgrid_input.put_Row(i);m_msflexgrid_input.put_Col(k);m_msflexgrid_input.put_CellBackColor(RGB(255,255,255));
// 			}
// 			else
// 			{
// 				m_msflexgrid_input.put_Row(i);m_msflexgrid_input.put_Col(k);m_msflexgrid_input.put_CellBackColor(COLOR_CELL);
// 			}
// 		}
// 	}
// 
// 
// 
// 
// 	//第3，4列11-26灰色显示
// 	for (int i=1;i<9;i++)
// 	{
// 
// 		m_msflexgrid_input.put_TextMatrix(i,4,_T("°C"));	  
// 		m_msflexgrid_input.put_Row(i);
// 		m_msflexgrid_input.put_Col(4);
// 		m_msflexgrid_input.put_CellBackColor(FLEXGRID_CELL_GRAY_COLOR);	   //灰色
// 	}
// 
// 
// 	//显示纵标题
// 	CString str;
// 	for(int i=1;i<=8;i++)
// 	{
// 
// 		str.Format(_T("%d"),i);
// 
// 		m_msflexgrid_input.put_TextMatrix(i,0,str);	 
// 
// 		str = _T("Input ")+str;
// 		m_msflexgrid_input.put_TextMatrix(i,1,str);
// 		m_msflexgrid_input.put_TextMatrix(i,5,_T("Default"));	
// 
// 	}
// 
// 	//显示纵标题
// 	str =_T("");
// 	for(int i=11;i<9;i++)
// 	{
// 
// 		str.Format(_T("%d"),i);
// 
// 		m_msflexgrid_input.put_TextMatrix(i,0,str);
// 		str = _T("Input ")+str;
// 		m_msflexgrid_input.put_TextMatrix(i,1,str);
// 
// 		m_msflexgrid_input.put_TextMatrix(i,3,_T("Auto"));
// 		m_msflexgrid_input.put_TextMatrix(i,4,_T("On/Off"));
// 		m_msflexgrid_input.put_TextMatrix(i,5,_T("Default"));	
// 
// 
// 	}
// 
// 
// 	//unsigned char writevalue[1];
// 	//writevalue[0] = 0;
// 	//int flg = Write_Multi(g_tstat_id,writevalue,144,10);
// 	//TRACE(_T("flg=%d\n"),flg);
// 	//ASSERT(flg>0);
// 
// 
// 	//============================================================================================================界面Output部份列表框
// 
// 	//设置行/列数量
// 	m_msflexgrid_output.put_Rows(14);
// 	m_msflexgrid_output.put_Cols(6);
// 	//设置列宽	
// 	m_msflexgrid_output.put_ColWidth(0,400);
// 	m_msflexgrid_output.put_ColWidth(3,1500);
// 
// 	//显示横标题
// 	m_msflexgrid_output.put_TextMatrix(0,1,_T("Input Name"));
// 	m_msflexgrid_output.put_TextMatrix(0,2,_T("Value"));
// 	m_msflexgrid_output.put_TextMatrix(0,3,_T("Auto/Manual"));
// 	m_msflexgrid_output.put_TextMatrix(0,4,_T("Range"));
// 	m_msflexgrid_output.put_TextMatrix(0,5,_T("Function"));
// 
// 
// 
// 	//居中显示
// 	for (int col=0;col<6;col++)
// 	{ 
// 		m_msflexgrid_output.put_ColAlignment(col,4);
// 	}
// 
// 	//彩色显示
// 	for(int i=1;i<14;i++)		//排数量
// 	{
// 
// 		for(int k=0;k<6;k++)	//列数量
// 		{
// 			if (i%2==1)
// 			{
// 				m_msflexgrid_output.put_Row(i);m_msflexgrid_output.put_Col(k);m_msflexgrid_output.put_CellBackColor(RGB(255,255,255));
// 			}
// 			else
// 			{
// 				m_msflexgrid_output.put_Row(i);m_msflexgrid_output.put_Col(k);m_msflexgrid_output.put_CellBackColor(COLOR_CELL);
// 			}
// 		}
// 	}
// 	//显示纵标题
// 	CString str_output;
// 	for(int i=1;i<=13;i++)
// 	{
// 
// 		str_output.Format(_T("%d"),i);
// 		m_msflexgrid_output.put_TextMatrix(i,0,str_output);	
// 		str_output = _T("Output ")+str_output;
// 		m_msflexgrid_output.put_TextMatrix(i,1,str_output);
// 
// 		//m_msflexgrid_output.put_TextMatrix(i,3,_T("Off"));
// 		m_msflexgrid_output.put_TextMatrix(i,4,_T("On/Off"));
// 		m_msflexgrid_output.put_TextMatrix(i,5,_T("Default"));
// 		m_msflexgrid_output.put_Row(i);
// 		m_msflexgrid_output.put_Col(4);
// 		m_msflexgrid_output.put_CellBackColor(FLEXGRID_CELL_GRAY_COLOR);
// 	}


	#if 1

	//显示横标题
	m_msflexgrid_input.put_TextMatrix(0,1,_T("Input Name"));
	m_msflexgrid_input.put_TextMatrix(0,2,_T("Value"));
	//m_msflexgrid_input.put_TextMatrix(0,3,_T("Auto/Manual"));
	m_msflexgrid_input.put_TextMatrix(0,3,_T("Range"));
	m_msflexgrid_input.put_TextMatrix(0,4,_T("Function"));


	//设置排/行数量
	m_msflexgrid_input.put_Cols(5);
	m_msflexgrid_input.put_Rows(11);//包括标题栏


	//设置列宽	
	m_msflexgrid_input.put_ColWidth(0,400);
	m_msflexgrid_input.put_ColWidth(3,1500);
	m_msflexgrid_input.put_ColWidth(4,1000);
	//居中显示
	for (int col=0;col<5;col++)
	{ 
		m_msflexgrid_input.put_ColAlignment(col,4);
	}

	//彩色显示
	for(int i=1;i<11;i++)		//排数量
	{

		for(int k=0;k<5;k++)	//列数量
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
	for(int i=1;i<11;i++)
	{

		str.Format(_T("%d"),i);

		m_msflexgrid_input.put_TextMatrix(i,0,str);	 

		// 		str = _T("Input ")+str;
		// 		m_msflexgridinput.put_TextMatrix(i,1,str);
		m_msflexgrid_input.put_TextMatrix(i,4,_T("Default"));	
		m_msflexgrid_input.put_TextMatrix(i,3,_T("Default"));

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
	m_msflexgrid_output.put_Rows(13);
	m_msflexgrid_output.put_Cols(6);
	//设置列宽	
	m_msflexgrid_output.put_ColWidth(0,400);
	m_msflexgrid_output.put_ColWidth(3,1500);

	//显示横标题
	m_msflexgrid_output.put_TextMatrix(0,1,_T("Input Name"));
	m_msflexgrid_output.put_TextMatrix(0,2,_T("Value"));
	m_msflexgrid_output.put_TextMatrix(0,3,_T("Auto/Manual"));
	m_msflexgrid_output.put_TextMatrix(0,4,_T("Range"));
	m_msflexgrid_output.put_TextMatrix(0,5,_T("Function"));



	//居中显示
	for (int col=0;col<6;col++)
	{ 
		m_msflexgrid_output.put_ColAlignment(col,4);
	}

	//彩色显示
	for(int i=1;i<13;i++)		//排数量
	{

		for(int k=0;k<6;k++)	//列数量
		{
			if (i%2==1)
			{
				m_msflexgrid_output.put_Row(i);m_msflexgrid_output.put_Col(k);m_msflexgrid_output.put_CellBackColor(RGB(255,255,255));
			}
			else
			{
				m_msflexgrid_output.put_Row(i);m_msflexgrid_output.put_Col(k);m_msflexgrid_output.put_CellBackColor(COLOR_CELL);
			}
		}
	}
	//显示纵标题
	CString str_output;
	for(int i=1;i<13;i++)
	{

		str_output.Format(_T("%d"),i);
		m_msflexgrid_output.put_TextMatrix(i,0,str_output);	
		// 		str_output = _T("Output ")+str_output;
		// 		m_msflexgridDO.put_TextMatrix(i,1,str_output);
		// 
		// 		//m_msflexgrid_output.put_TextMatrix(i,3,_T("Off"));
		// 		m_msflexgridDO.put_TextMatrix(i,4,_T("On/Off"));
		m_msflexgrid_output.put_TextMatrix(i,5,_T("Default"));
		m_msflexgrid_output.put_Row(i);
		m_msflexgrid_output.put_Col(4);
		m_msflexgrid_output.put_CellBackColor(FLEXGRID_CELL_GRAY_COLOR);
		m_msflexgrid_output.put_TextMatrix(i,3,_T("Default"));
	}




	#endif 


}

void CDialogT3::Fresh()
{
	SetTimer(T3_MODEL,1000,NULL);
	GetDatabase();
	ShowDialogData();
	//Updatedatabase();
	
}

void CDialogT3::ShowDialogData()
{

	m_model = _T("T3-4AO");
	m_address= multi_register_value[6];
	m_firmware= multi_register_value[5];
	m_serial= get_serialnumber(); //Address 0-3
	m_hardware= multi_register_value[4];
	//if (multi_register_value[7] == 20)
	//	m_model= _T("T3-8AI13O");
	m_picVersion= multi_register_value[9];




	//==================================================Input============================================================
	//T3-4AO
	//address: input 119~138  INPUT1-10 119(high word) 120(low word)
	//address:Switch 
	//Range Setting for each input  200
	CString strresult;

	for(int i = 1;i<=10;i++)
	{  
		// 		strresult.Format(_T("%d°C"),10);
		// 		m_msflexgridinput.put_TextMatrix(i,2,strresult);
		// 		m_msflexgridinput.put_TextMatrix(i,1,_T("west door"));
		// 		m_msflexgridinput.put_TextMatrix(i,3,_T("0-100%"));


		m_msflexgrid_input.put_TextMatrix(i,2,vect3model.at(119-1+i).CStvalue);
		m_msflexgrid_input.put_TextMatrix(i,1,vect3model.at(119-1+i).CStName);
		//m_msflexgrid_input.put_TextMatrix(i,3,vect3model.at(148-1+i).CStrange);
	}


	//====================================================Output============================================================	
	//T3-4AO OUTPUT
	//address: input 100~110   OUTPUT1-12
	//100~111

	CString CstresultDO;
	for(int i = 1;i<=12;i++)
	{  
		// 		CstresultDO.Format(_T("%d"),10);
		// 		m_msflexgridDO.put_TextMatrix(i,2,CstresultDO);
		// 		m_msflexgridDO.put_TextMatrix(i,1,_T("east door"));
		// 		m_msflexgridDO.put_TextMatrix(i,3,_T("AUTO"));
		
		
		m_msflexgrid_output.put_TextMatrix(i,2,vect3model.at(100-1+i).CStvalue);
		m_msflexgrid_output.put_TextMatrix(i,1,vect3model.at(100-1+i).CStName);
		//m_msflexgrid_output.put_TextMatrix(i,3,vect3model.at(124-1+i).CStautomannel);
		//m_msflexgrid_output.put_TextMatrix(i,4,vect3model.at(100-1+i).CStrange);


	}






	UpdateData(FALSE);





#if 0
		//183					1		Range Setting for each input.
		//184					1		183 correspond to input1,
		//185					1		184 correspond to input2, etc.
		//186					1		0 = raw data,
		//187					1		1 = 10K Celsius,
		//188					1		2 = 10K Fahrenheit,
		//189					1		3 = 0-100%
		//190					1		4 = ON/OFF,
		//								5 = OFF/ON
		//								6 = Pulse Input
		//								7 = Lighting Control
	for (int i = 183;i<=190;i++)
	{	
		int retRangSet =write_one(g_tstat_id,i,1);
		TRACE(_T("retRangSet=%d\n"),retRangSet);
	}
	


	CString strinput,stroutput,strfilter;
	//Input Register address 118-133  eg:input1-> 118 high word   119 low word
	int numrow = 1;
	for (int i = 1;i<=16;i++)
	{
		int temphigh = multi_register_value[i+117]<<16;
		i++;
		int templow = multi_register_value[i+117]&0x0000ffff;
		int temp = temphigh|templow;

		strinput.Format(_T("%d°C"),temp);
		m_msflexgrid_input.put_TextMatrix(numrow,2,strinput);
		//Input Filter address 191-198
		strfilter.Format(_T("%d"),multi_register_value[190+numrow]);
		m_msflexgrid_input.put_TextMatrix(numrow,3,strfilter);
		numrow++;
		
	

	}

	//Output Register address 100-112
	for (int i = 1;i<=13;i++)
	{
		if (multi_register_value[i+99] == 0)
		{
			m_msflexgrid_output.put_TextMatrix(i,2,_T("Off"));
		} 
		else if(multi_register_value[i+99] > 0)
		{
			m_msflexgrid_output.put_TextMatrix(i,2,_T("On"));
		}

	}

	//显示Auto/Manual
	//116	2	Switch Status, 1 Register output 1-8
	//117	2	Switch Status, 2 Register output 9-13
	//当output全按至HAND时，116 117的二进制值：
	//					 high 8 bit   |	  low 8 bit							
	//HAND INPUT		 1   2   3   4   5   6  7    8			  9  10  11  12  13
//register:116 117     0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1			0 1 0 1 0 1 0 1 0 1 0 0 0 0 0 0


    //当output全按至AUTO时，116 117的二进制值：
	//AUTO INPUT	   1   2   3   4   5   6   7   8			9  10  11  12  13
//register;116 117	   1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0			1 0 1 0 1 0 1 0 1 0 0 0 0 0 0 0

	int temp = 1; 

	for (int i = 8;i>=1;i--)
	{
		//Manual
		if((multi_register_value[116]&temp)!= 0)
			m_msflexgrid_output.put_TextMatrix(i,3,_T("Manual"));
			temp = temp<<1;
		if ((multi_register_value[116]&temp)!=0)
			m_msflexgrid_output.put_TextMatrix(i,3,_T("Auto"));
		temp = temp<<1;
	}

	temp = 1;
	temp = temp<<6;
	for (int i = 13;i>=9;i--)
	{
		
		//Manual
		if((multi_register_value[117]&temp)!= 0)
			m_msflexgrid_output.put_TextMatrix(i,3,_T("Manual"));	
		temp = temp<<1;
		if ((multi_register_value[117]&temp)!=0)
			m_msflexgrid_output.put_TextMatrix(i,3,_T("Auto"));
		temp = temp<<1;
	}

#endif
}

void CDialogT3::CreatDBTable()
{
	CADO m_ado;
	m_ado.OnInitADOConn();
//	CString sql = _T("CREATE TABLE tblCustomers(Fist TEXT(5) NOT NULL,Phone TEXT(10))");//创建表


	CString sql = _T("SELECT Count(*) AS Qty FROM MSysObjects WHERE ((MSysObjects.Name) Like 'NewTable')");
	//以下这两行代码表示，判断是否存在这个表 返回1为存在， 0为不存在 
//  CString sql= _T("SELECT Count(*) AS RTab FROM MSysObjects WHERE((MSysObjects.Name) Like 'NewTable')");//   


	

	
// 	由于Access数据库本身的“管理员”组没有访问隐含对象的权限，因此先要：工具 -> 选项 -> 视图 -> 隐藏对象、系统对象，前面的勾选上。  
// 	然后，工具 -> 安全 -> 用户与组的权限，在对象名称中选定 MSysObjects（我只用到这个对象，如果需要用到其它的，可以再选） ，然后权限中设置“读取数据”权限


// 
// 	　Access中判断表对象是否存在：
// 
// 		 　　其实，Access数据库也有系统表，存放有对象名
// 
// 		   　　Select Count(*) AS Qty FROM MSysObjects Where ((MSysObjects.Name) Like '表名');
// 
// 	 　　判断数据库和表是否存在
// 
// 		   　　if not exists(select 1 From master.dbo.sysdatabases where name=N'JZKStarCfg')

//	if exists (select * from sysobjects where objectproperty(object_id(''table_name''),''istable'')=1)

	//	drop table table_name








// 	CREATE TABLE tblCustomers (
// 		...CustomerID INTEGER NOT NULL,
// 		...[Last Name] TEXT(5) NOT NULL,
// 		...[First Name] TEXT(50) NOT NULL,
// 		...Phone TEXT(10),
// 		...Email TEXT(50))
	


	try 
	{
		//exists
	
 	m_ado.m_pRecordset = m_ado.OpenRecordset(sql);



// 	CString cstnum;
 
// 		saveADO.m_pRecordset->Move(num,vtMissing);
// 		saveADO.m_pRecordset->PutCollect("Name",(_bstr_t)str);
// 		saveADO.m_pRecordset->Update();
// 
	}
 	catch(...)
 	{
 		//SetPaneString(2,_T("'Input Name' Write dababase false!"));
 		//return ;

 	}
// 
// 
// 	vecminipanel.at(num).CStName = str;
// 	saveADO.CloseRecordset();
// 	saveADO.CloseConn(); 




}
void CDialogT3::OnTimer(UINT_PTR nIDEvent)
{
 	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CView* pNewView = pMain->m_pViews[5];
	CView* pActiveView = pMain->GetActiveView();

	if ( pNewView != pActiveView )    // current is minipanel dialog
	{
		KillTimer(T3_MODEL);
	}

#if 1
	static int nCount = 0,nCount2 = 0;

	nCount++;
	nCount2++;

	if (T3_MODEL == nIDEvent)
	{
		CTime now;
		now = CTime::GetCurrentTime();
		//m_datetime = now.Format(_T("%A,%B %d,%Y  %H:%M:%S"));		// "Saturday, April 12, 2012"		

		//UpdateData(FALSE);

		if (nCount% 30 == 0)
		{

			nCount = 0;
			BOOL flag=MiniUpdateData();

			if (flag)
			{
				ShowDialogData();
				SetPaneString(2,_T("Online!"));

			}

		}
		if (nCount2%60*10 == 0)
		{
			nCount2 = 0;
			Updatedatabase();

		}


	}

#endif

	CFormView::OnTimer(nIDEvent);
}

BOOL CDialogT3::GetDatabase()
{
	CADO m_ado;
	m_ado.OnInitADOConn();

	if(ift3db)
	{
#if 1

	//判断MiniPanel数据库是否存在,Auto/Manual text,Range text

	CString temptable = _T("T3_4AO");
	CString tempsql = _T("create table T3_4AO(Address Number Primary Key,Name text,Data text,AutoManual text,Range text)");//

	bool m_judge = m_ado.IsHaveTable(m_ado,temptable);

	if (!m_judge) 
	{	
		m_ado.m_pRecordset = m_ado.OpenRecordset(tempsql);
		//初始化表
		CString sql = _T("select * from T3_4AO");
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
	ift3db = FALSE;
#endif 
	}

#if 1
	CString SQL = _T("select * from T3_4AO");
	m_ado.m_pRecordset = m_ado.OpenRecordset(SQL);
	_variant_t vartemp;
	while(!m_ado.m_pRecordset->EndOfFile)
	{
		m_t3model.iaddress =m_ado.m_pRecordset->GetCollect(_T("Address"));
		vartemp =m_ado.m_pRecordset->GetCollect(_T("Name"));
		if (vartemp.vt==VT_NULL)
			m_t3model.CStName =_T("");
		else
			m_t3model.CStName =vartemp;


		vartemp =m_ado.m_pRecordset->GetCollect(_T("Data"));
		if (vartemp.vt==VT_NULL)
			m_t3model.CStvalue =_T("");
		else
			m_t3model.CStvalue =vartemp;


		vartemp =m_ado.m_pRecordset->GetCollect(_T("AutoManual"));
		if (vartemp.vt==VT_NULL)
			m_t3model.CStautomannel =_T("");
		else
			m_t3model.CStautomannel =vartemp;


		vartemp =m_ado.m_pRecordset->GetCollect(_T("Range"));
		if (vartemp.vt==VT_NULL)
			m_t3model.CStrange =_T("");
		else
			m_t3model.CStrange =vartemp;

		m_ado.m_pRecordset->MoveNext();

		vect3model.push_back(m_t3model);
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

	int ret = vect3model.size();
	if (ret<230)
	{
		for (int i=0;i<=230;i++)
		{
			m_t3model.CStName = _T("Unused");
			m_t3model.CStautomannel = _T("Auto");
			m_t3model.CStrange = _T("ON/OFF");
			vect3model.push_back(m_t3model);
		}

	}

#endif 


	return TRUE;

}

BOOL CDialogT3::MiniUpdateData()
{
	KillTimer(T3_MODEL);
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
		vect3model.at(i).CStvalue.Format(_T("%d"),shmPRegister[i]);	
		if (i>=124&&i<=147)
		{
			switch(shmPRegister[i])
			{
			case 0:
				vect3model.at(i).CStautomannel = _T("OFF");				
				break;
			case 1:
				vect3model.at(i).CStautomannel = _T("Manual");				
				break;
			case 2:
				vect3model.at(i).CStautomannel = _T("Auto");				
				break;
			default:
				break;
			}

		}

		if (i>=100&&i<=123)
		{

			if (shmPRegister[i]>512)
				vect3model.at(i).CStvalue = _T("ON"); 
			else
				vect3model.at(i).CStvalue = _T("OFF");

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


	SetTimer(T3_MODEL,1000,NULL);
#endif
	return flag;

}

void CDialogT3::Updatedatabase()
{
	TRACE(_T("Updatedatabase()start!\n"));
	KillTimer(T3_MODEL);
	//存入数据库中
	CADO saveADO;
	saveADO.OnInitADOConn();
	CString sql = _T("select * from T3_4AO");
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

				saveADO.m_pRecordset->PutCollect("Address",(_bstr_t)(i+1));
				saveADO.m_pRecordset->PutCollect("Name",(_bstr_t)vect3model.at(i).CStName);
				saveADO.m_pRecordset->PutCollect("Data",(_bstr_t)shmPRegister[i]);
				saveADO.m_pRecordset->PutCollect("Range",(_bstr_t)vect3model.at(i).CStrange);


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
				saveADO.m_pRecordset->PutCollect("Address",(_bstr_t)(i+1));
				saveADO.m_pRecordset->PutCollect("Name",(_bstr_t)vect3model.at(i).CStName);
				saveADO.m_pRecordset->PutCollect("Data",(_bstr_t)shmPRegister[i]);
				saveADO.m_pRecordset->PutCollect("Range",(_bstr_t)vect3model.at(i).CStrange);


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

	SetTimer(T3_MODEL,1000,NULL);

}