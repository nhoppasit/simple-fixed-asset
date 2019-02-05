#ifndef __VHDLLLIB_H__
#define __VHDLLLIB_H__

//////////////////////////////////////////////////////////////////////////
#include <atlbase.h>
//////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

//////////////////////////////////////////////////////////////////////////
//用途:		取得系统的COM口
//函数名:	GetSystemPorts
//功能:		
//输入参数:	CComboBox 指针
//输出参数:	
//返回值:	无
//备注:		
//////////////////////////////////////////////////////////////////////////
void _stdcall GetSystemPorts(CComboBox *tempCombBox);


//打开USB设备,0--成功, 其它失败
int VM_OpenUsbDevice(HANDLE *hScanner);

//关闭USB设备,0--成功, 其它失败
BOOL VM_CloseUsbDevice(HANDLE hScanner);

//设备状态改变时的处理函数
BOOL VM_OnDeviceChange(UINT nEventType, DWORD dwData );

//初始化通知
void VM_iniDeviceNotification(HWND hWnd );

//释放通知
void VM_DeiniDeviceNotification(HWND hWnd );

//使能是否接收数据,bFlag 为真则接收，否则不接收
void VM_IsEnableRecvData(BOOL bFlag );

#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////
#endif	//end of 
