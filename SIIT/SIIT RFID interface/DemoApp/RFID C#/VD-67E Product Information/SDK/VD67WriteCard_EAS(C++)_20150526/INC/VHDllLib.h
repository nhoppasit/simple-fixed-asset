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
//��;:		ȡ��ϵͳ��COM��
//������:	GetSystemPorts
//����:		
//�������:	CComboBox ָ��
//�������:	
//����ֵ:	��
//��ע:		
//////////////////////////////////////////////////////////////////////////
void _stdcall GetSystemPorts(CComboBox *tempCombBox);


//��USB�豸,0--�ɹ�, ����ʧ��
int VM_OpenUsbDevice(HANDLE *hScanner);

//�ر�USB�豸,0--�ɹ�, ����ʧ��
BOOL VM_CloseUsbDevice(HANDLE hScanner);

//�豸״̬�ı�ʱ�Ĵ�����
BOOL VM_OnDeviceChange(UINT nEventType, DWORD dwData );

//��ʼ��֪ͨ
void VM_iniDeviceNotification(HWND hWnd );

//�ͷ�֪ͨ
void VM_DeiniDeviceNotification(HWND hWnd );

//ʹ���Ƿ��������,bFlag Ϊ������գ����򲻽���
void VM_IsEnableRecvData(BOOL bFlag );

#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////
#endif	//end of 
