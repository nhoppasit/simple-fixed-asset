// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__57BD4D71_259A_4B9A_8C80_A7349D284048__INCLUDED_)
#define AFX_STDAFX_H__57BD4D71_259A_4B9A_8C80_A7349D284048__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//#include <afxsock.h>		// MFC socket extensions

//#include "./Reader1000API.h"
//#pragma comment(lib, "Reader1000DLL.lib")//动态连接库

//#pragma comment(lib, "./Lib626/Reader626StaticLib.lib")//静态连接库


#include "./Lib626/Reader626API.h"
//#pragma comment(lib, "./Lib626/Reader626StaticLib.lib")//静态连接库
#pragma comment(lib, "ReaderDynamicLib.lib")//动态连接库

//**************************************************************************/
//特述的485输出,以前修正，后来 add by mqs 20130711  合成一个DEMO
//RS485口协议
//采用RS485口输出数据时，需要事先设置RS485口的通信速率。RS485口输出数据的格式是:
//BODY	CHECK
//STX	DATA	ETX	BCC
//02	天线编号(2个字节ASCII码)	ID号或自定义编号(8字节ASCII码)	03	校验码/
//说明:
//数据开始标志STX = 02H ，数据结束标志ETX = 03H；
//DATA为天线编号(2Byte)+标签ID号(8Bytes)，长度为10个字节ASCII码。把十六进制数据转换为ASCII表示的方法是:
//把数据按从高到低的顺序每4位一组进行分割，再把4位二进制数的取值用ASCII码表示。由于4位二进制数的取值范围是0H～FH，因此转换后的ASCII码为30H～39H，41H～46H。例如:32位编号号数据为6A90F103H，转化为8个字节的ASCII码后为『36H 41H 39H 30H 46H 31H 30H 33H』。天线1编号(ASCII码)为『30H  31H』，天线2编号(ASCII码)为『30H 32H』。
#define					ENABLE485TXOUTPUT
//**************************************************************************/

//EPC读写16进制
#define					EPCREADWRITEHEX


//非标单的BPA，详见BPA-9-proctol.pdf, 接口有变化，用宏控制,add by mqs 20130118
//#define					ENABLEBPA9PROCTOL


//最终用户有需求，是否屏掉参数设置界面，编译ENABLEREADERPARAM 则有参数界面，否则无，用宏控制,add by mqs 20130222
#define					ENABLEREADERPARAM

//周工的要求，add by mqs 20130327 要求：1.在标题栏显示“读写器”,硬件版本：1000; 软件版本：1000; ID号：读写器1000,
//#define					ENABLETXVERCHANGE


//小模块参数设置界面，编译 ENABLEREADERMODES 则有小模块参数界面，否则无，用宏控制,add by mqs 20130514
//#define					ENABLEREADERMODES


//垃圾厂处理功能,编译 ENABLErubbish 则有垃圾厂处理参数界面，否则无，用宏控制,add by mqs 20130614
//#define					ENABLErubbish


//218为了提高读标签速度，不用切换天线，加一个命令，下面自动切换天线，编译 ENABLE218TXNOAntenna  否则无，用宏控制,add by mqs 20130910
//#define					ENABLE218TXNOAntenna

//#####################################################################
//add by martrin 20140110增加华为斯迈尔以前用Reader2600,现在换成四口的
//R2000的，所以要改用R2000协议, 开启用R2000, 否则用以前的
//#define					ENABLE_R2000_protocol

//#####################################################################

#define					WM_MYMESSAGE				(WM_USER+1)
#define					WM_MYDATAMSG				(WM_USER+2)
#define					WM_LISTUSERDATA				(WM_USER+3)	//主界面页子
#define					WM_CONNECTDATACUSTOM		(WM_USER+4)	//连接读写器
#define					WM_READERPARMDATAMSG		(WM_USER+5)	//参数页
#define					WM_EPC6CTRANDATAMSG			(WM_USER+6)	//6C
#define					WM_USERTIMERDATATRan		(WM_USER+7)	//6B
#define					WM_OUTPUTTESTDATAMSG		(WM_USER+8)	//(WM_USER+300)//output test
#define					WM_DLGBPA9DATAMSG			(WM_USER+9)	//BPA9的窗体
#define					WM_DLGSMALLMODEDATAMSG		(WM_USER+10)	//小模块的窗体


//RS485的Delay时间(ms)
#define					ReadRS485SleepTime				(60)//(300)

extern CString			g_szCurPath;		//当前可执行文件的路径名
//////////////////////////////////////////////////////////////////////////
extern HWND				gMainHwnd;			//主界面页子
extern HWND				gConnectReaderHwnd;	//连接的窗体的句柄
extern HWND				gReaderParamHwnd;	//读写器参数窗体句柄
extern HWND				gReaderDParaHwnd;	//218参数界面句柄
extern HWND				gEcpISO6C;			//6c窗体的句柄
extern HWND				gEcpISO6B;			//6B窗体的句柄
extern HWND				gOutputHwnd;		//输出测试的窗体的句柄
extern HWND				gDlgBpa9;			//Bpa9窗体的句柄



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__57BD4D71_259A_4B9A_8C80_A7349D284048__INCLUDED_)
