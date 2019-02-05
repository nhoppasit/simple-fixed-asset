#ifndef _READER626API_H 
#define _READER626API_H

#include "WINSOCK2.h"
//#include "WINSOCK.h"

#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")

#ifdef __cplusplus
extern "C"
{
#endif

//#####################################################################
//add by martrin 20140616����ARM9��ʱ���ʽ,ԭ����6�ֽڣ����ڱ��7�ֽ�
//#define					ENABLE_ARM9_MODEL

//#####################################################################


//////////////////////////////////////////////////////////////////////////
extern "C" int  WQ_Sum(int a, int b);//test

#if 1
//==============================�������Ͷ���==============================
typedef int apiReturn;   // ��������ֵ����
//////////////////////////////////////////////////////////////////////////
#define WM_ADDLIST (WM_USER+100)
//////////////////////////////////////////////////////////////////////////

//==============================��������==============================
#define	ID_MAX_SIZE_64BIT	8		//���ӱ�ǩ��ID��Ϊ64bit
#define	ID_ATA_MAX_SIZE		20		//ATA���ӱ�ǩ��ID��Ϊ20byte
#define ID_MAX_SIZE_96BIT	65		//���ӱ�ǩ��ID��
#define MAX_LABELS			255		// һ�ζ�д������಻����100����ǩ

//==============================API����������==============================
#define	_OK					0x00	// �����ɹ�

//ͨ�ŷ��������Ϣ
#define _init_rs232_err		0x81	//  ͨ�ſڳ�ʼ��ʧ��
#define _no_scanner			0x82	//  �Ҳ�����д��
#define _comm_error         0x83	//  �շ�ͨ�����ݳ���
#define _baudrate_error     0x84	//  ���ò����ʳ���
#define _init_net_error		0x85	//  ���ڳ�ʼ��ʧ��
#define _net_error          0x86	//  �����շ�ͨ�����ݳ���

// ��д�����س�����Ϣ
#define _no_antenna			0x01   //��������ʧ��
#define _no_label			0x02   //δ��⵽��ǩ
#define _invalid_label		0x03   //�Ƿ���ǩ
#define _less_power			0x04   //��д���ʲ���
#define _write_prot_error	0x05   //����д����
#define _check_sum_error	0x06   //У��ʹ���
#define _parameter_error	0x07   //��������
#define _memory_error		0x08   //������������
#define _password_error		0x09   //���벻��ȷ
#define _killpassword_error	0x0a   //G2��ǩ��������Ϊȫ��
#define _nonlicet_command	0x0b   //�Ƿ�����
#define _nonlicet_user		0x0c   //���벻ƥ��ķǷ��û�
#define _invalid_command	0x1e   //��ʾ��Чָ����������ȷ��ָ��
#define _other_error		0x1f   //δ֪����

//�����������
#define _no_cardID_input   0x20   //��������

typedef struct tagReaderDate
{
	BYTE	Year;			//��
	#if defined (ENABLE_ARM9_MODEL)
	BYTE	Yeam;			//��
	#endif
	BYTE	Month;			//��
	BYTE	Day;			//��
	BYTE	Hour;			//ʱ
	BYTE	Minute;			//��
	BYTE	Second;			//��
}ReaderDate;

typedef struct tagReaderBasicParam
{
	BYTE	BaudRate;			//(1)���ڵ�ͨ�����ʣ�ȡֵ��00H~08H����������ͬ"�趨������"���
	BYTE	Power;				//(2)���书��ֵ��ȡֵ��20~30dBm��(0-63)
	BYTE	Min_Frequence;		//(3)����΢���ź�Ƶ�ʵ���ʼ�㣬ȡֵ�� 1~63��
	BYTE	Max_Frequence;		//(4)����΢���ź�Ƶ�ʵ���ֹ�㣬ȡֵ�� 1~63��
	BYTE	Reserve5;			//(5)����,������Ϊ�������
	BYTE	WorkMode;			//(6)��д��������ʽ��0-������ʽ��1-���ʽ
	BYTE	ReaderAddress;		//(7)RS485��ַ:0--255
	BYTE	NumofCard;			//(8)��������Ŀ��
	BYTE	TagType;			//(9)��ǩ���ࣺ01H��ISO18000-6B��02H��EPCC1��04H��EPCC1G2��08H��EM4442��
	BYTE	ReadDuration;		//(10)��������ʱ�䣺��Ƶ�������ʱ�䣬ֻ���EM��ǩ��Ч��0��10ms��1��20ms��2��30ms��3��40ms��
	BYTE	ReadTimes;			//(11)��������M���յ���λ�����������д��ִ��M�δ����
	BYTE	EnableBuzzer;		//(12)1:ʹ�ܷ�����0:��ʹ�ܷ�����
	BYTE	IP1;			    //(13)��д��IP��ַ
	BYTE	IP2;			    //(14)
	BYTE	IP3;			    //(15)
	BYTE	IP4;			    //(16)
	BYTE	Port1;				//(17)��д���˿ڸ�λ
	BYTE	Port2;				//(18)
	BYTE	Mask1;				//(19)��д������1
	BYTE	Mask2;				//(20)��д������2
	BYTE	Mask3;				//(21)��д������3
	BYTE	Mask4;				//(22)��д������4
	BYTE	Gateway1;			//(23)��д����ַ����
	BYTE	Gateway2;			//(24)
	BYTE	Gateway3;			//(25)
	BYTE	Gateway4;			//(26)
	BYTE	MAC1;			    //(27)��д��MAC��ַ
	BYTE	MAC2;			    //(28)
	BYTE	MAC3;			    //(29)
	BYTE	MAC4;			    //(30)
	BYTE	MAC5;			    //(31)
	BYTE	MAC6;			    //(32)
	#if defined (ENABLE_ARM9_MODEL)
	BYTE	AutoParam[32];
	#endif

} ReaderBasicParam;

//��д��������������
typedef struct tagReaderAutoParam
{
	BYTE	AutoMode;			//(1)����ǩģʽ��0-��ʱ��ʽ��1-������ʽ��
	BYTE	TimeH;				//(2)��ǩ����ʱ�䣺��λ����s��ȱʡֵΪ1��
	BYTE	TimeL;				//(3)
	BYTE	Interval;			//(4)0-10ms��1-20ms��2-30ms��3-50ms��4-100ms��ȱʡֵΪ2��ÿ���趨ʱ��������ȡһ�α�ǩ��
	BYTE	NumH;				//(5)��ǩ������Ŀ��ȱʡֵΪ1���Ѷ�ȡ�ı�ǩID�ڶ�д���ڴ��б�������Ŀ��
	BYTE	NumL;				//(6)
	BYTE	OutputManner;	    //(7)���������ʽ��0-�򻯸�ʽ��1-��׼��ʽ��2-XML��ʽ��ȱʡֵΪ0��
	BYTE	OutInterface;		//(8)����ӿڣ�0��RS232�ڣ�1��RS485�ڣ�2��RJ45�ڡ�ȱʡֵΪ0�� 3- Wiegand26    4- Wiegand34
	BYTE	WiegandWidth;		//(9)Weigand������ֵ��
	BYTE	WiegandInterval;	//(10)Weigand������ֵ��
	BYTE	ID_Start;			//(11)������ŵ���ʼλ��ȡֵ0��4��
	BYTE    IDPosition;			//(12)�����ڵ��ӱ�ǩ�ϵĴ�ŵ�ַ��
	BYTE	Report_Interval;	//(13)֪ͨ�������λ��s��ȱʡֵΪ1��ÿ���趨ʱ������֪ͨ��λ��һ�Ρ�
	BYTE	Report_Condition;	//(14)֪ͨ������ȱʡֵΪ1��0-����֪ͨ��1-��ʱ֪ͨ��2-�����±�ǩ��3-���ٱ�ǩ��4-��ǩ���仯	
	BYTE	Report_Output;		//(15)֪ͨ�����
	BYTE	Antenna;			//(16)����ѡ��1-ant1,2-ant2,4-ant4,8-ant8
	BYTE	TriggerMode;	    //(17)������ʽ(ȱʡֵΪ0): 0-�͵�ƽ 1-�ߵ�ƽ
	BYTE	HostIP1;			//(18)��֪ͨIP��ַ
	BYTE	HostIP2;			//(19)
	BYTE	HostIP3;			//(20)
	BYTE	HostIP4;			//(21)
	BYTE	Port1;				//(22)��֪ͨ�˿�
	BYTE	Port2;				//(23)
	BYTE	Reserve24;			//(24)��֪ͨMAC,mofi by mqs 20121207 ����
	BYTE	ArgentinaSim;		//(25)//����ģʽ(����͢),0--�Ƿ��棬1--����
	BYTE	CardTime1;			//(26)//�����ܳ�ʱ1
	BYTE	CardTime2;			//(27)//�����ܳ�ʱ2
	BYTE	ArgentinaMode;		//(28)//����������ģʽ,0---Only ATA  ֻ��ATA;1---Only EPC ֻ��EPC;2---Only EPC & TID ֻ��EPC+TID;3---ATA + EPC   ��ATA+EPC;4---ATA + EPC & TID��ATA+EPC&TID
	BYTE	AnSleepTime;		//(29)//����˯��ʱ�䣬��λ��ms,(1-255)
	BYTE	Alarm;				//(30)0-��������1-�������ڶ�ʱ�ʹ�����ʽ���Ƿ��ⱨ����
	BYTE	Reserve31;		    //(31)��׼���ʱ������ȱʡֵΪ120�룬1��255��
	BYTE	EnableRelay;		//(32)�Զ�����ģʽ�Ƿ���Ƽ̵���1:���� 0:������
} ReaderAutoParam;

typedef struct tagReaderDebugState
{
	BYTE	Test;				//0������״̬��1������״̬��
	BYTE	Reserve2;			//����
	BYTE	Reserve3;			//����
	BYTE	Reserve4;			//����
} ReaderDebugState;


typedef struct _tagReaderFreq
{
	char *chFreq;		//����Ƶ���ַ���

	int	iGrade;			//���� = 50;
	int iSkip;			//���� = 500KHz;
	int dwFreq;			//��ʼƵ�� = 902750;
						//��ʽ��902750 + ����*����
}tagReaderFreq;

//���ڸ������ҵ�Ƶ��
static const tagReaderFreq stuctFreqCountry[]=
{
	{"00---FCC(American)", 63, 400, 902600},							//(0),{"00---FCC(American)", 50, 500, 902750},
	{"01---ETSI EN 300-220(Europe300-220)", 11, 200, 865500},			//(1),{"01---ETSI EN 300-220(Europe300-220)", -1, -1, -1},
	{"02---ETSI EN 302-208(Europe302-208)", 4, 600, 865700},			//(2)
	{"03---HK920-925(Hong Kong)", 10, 500, 920250},						//(3)
	{"04---TaiWan 922-928(Taiwan)", 12, 500, 922250},					//(4)
	{"05---Japan 952-954(Japan)", 0, 0, 0},								//(5)
	{"06---Japan 952-955(Japan)", 14,200, 952200},						//(6)
	{"07---ETSI EN 302-208(Europe)", 4, 600, 865700},					//(7)
	{"08---Korea 917-921(Korea)", 6, 600, 917300},						//(8)
	{"09---Malaysia 919-923(Malaysia)", 8, 500, 919250},				//(9)
	{"10--China 920-925(China)", 16, 250, 920625},						//(10)
	{"11--Japan 952-956(Japan)", 4, 1200, 952400},						//(11)
	{"12--South Africa 915-919(Poncho)", 17, 200, 915600},				//(12)
	{"13--Brazil 902-907/915-928(Brazil)", 35, 500, 902750},			//(13)
	{"14--Thailand 920-925(Thailand)", -1, -1, -1},						//(14)
	{"15--Singapore 920-925(Singapore)", 10, 500, 920250},				//(15)
	{"16--Australia 920-926(Australia)", 12, 500, 920250},				//(16)
	{"17--India 865-867(India)", 4, 600, 865100},						//(17)
	{"18--Uruguay 916-928(Uruguay)", 23, 500, 916250},					//(18)
	{"19--Vietnam 920-925(Vietnam)", 10, 500, 920250},					//(19)
	{"20--Israel 915-917", 1, 0, 916250},								//(20)
	{"21--Philippines 918-920(Philippines)", 4, 500, 918250},			//(21)
	{"22--Canada 902-928(Canada)", 42, 500, 902750},					//(22)
	{"23--Indonesia 923-925(Indonesia)", 4, 500, 923250},				//(23)
	{"24--New Zealand 921.5-928(New Zealand)", 11, 500, 922250},		//(24)
};

//���ڸ������ҵ�Ƶ��
static const tagReaderFreq stuctFreqCountryT[]=
{
	{"01---FCC(American)", 63, 400, 902600},							//(0),{"00---FCC(American)", 50, 500, 902750},
	{"02---ETSI", 11, 200, 865500},										//(1),{"01---ETSI EN 300-220(Europe300-220)", -1, -1, -1},
	{"03---CHN", 4, 600, 865700},										//(2)
	{"04---Custom", 10, 500, 920250},									//(3)
	
};

//����ɨ�赽��IP
typedef void (WINAPI *OnWqReceiveData)(LPCSTR ReaderIP1, LPCSTR ReaderIP2, LPCSTR ReaderIP3, LPCSTR ReaderIP4, LPCSTR Port);


//�Զ�ģʽɨ������ݻش�
//dwSize Ϊ�������ݵ��ַ��ĸ���
typedef void (WINAPI *OnCallbackAutoReceiveData)(DWORD dwSize);

void _stdcall DeleteAppHwnd();
//////////////////////////////////////////////////////////////////////////
void _stdcall SetAppHwnd(HWND hWnd);

//==============================��������==============================

//���Ӷ�д��
apiReturn _stdcall ConnectScanner(HANDLE *hScanner, char *szPort, int *nBaudRate);

//�Ͽ�����
apiReturn _stdcall DisconnectScanner(HANDLE hScanner);

//==============================�豸��������==============================
//���ò�����
apiReturn _stdcall SetBaudRate(HANDLE hScanner, int nBaudRate,int Address);

//��ȡ�汾��
apiReturn _stdcall GetReaderVersion(HANDLE hScanner, WORD *wHardVer, WORD  *wSoftVer,int Address);

//���ö�д���̵���״̬
apiReturn _stdcall SetRelay(HANDLE hScanner, int Relay,int Address);

//�趨�������
apiReturn _stdcall SetOutputPower(HANDLE hScanner, int nPower1,int Address);

//�趨����Ƶ��
apiReturn _stdcall SetFrequency(HANDLE hScanner, int Min_Frequency, int Max_Frequency,int Address);

//��ö�д������Ƶ�ʷ�Χ
apiReturn _stdcall GetFrequencyRange(HANDLE hScanner, BYTE *Frequency,int Address);

//�趨����Ƶ��(���R2000ģ��ר��)
apiReturn _stdcall SetFrequencyEx(HANDLE hScanner, BYTE *Frequency,int Address);

//////////////////////////////////////////////////////////////////////////
//��;:		�趨����Ƶ��(���5Fģ��ר��)	
//������:	SetFrequencyEx5F
//����:		hScanner Ϊ���;Address ΪRS485��ַ(1-254)��0��ΪRS232
//�������:	Frequency Ϊȡ������,
//�������:	��
//����ֵ:	����AK_TRUEΪ��ʼ���ɹ�������AK_FALSEΪ��ʼ��ʧ��
//��ע:
//����:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall SetFrequencyEx5F(HANDLE hScanner, BYTE *Frequency,int Address);

//��ö�д������Ƶ�ʷ�Χ(���R2000ģ��ר��)
apiReturn _stdcall GetFrequencyRangeEx(HANDLE hScanner, BYTE *Frequency,int Address);

//��ȡ��д��������������
apiReturn _stdcall ReadBasicParam(HANDLE hScanner, ReaderBasicParam * pParam,int Address);

//���ö�д��������������
apiReturn _stdcall WriteBasicParam(HANDLE hScanner, ReaderBasicParam * pParam,int Address);

//��ȡ��д���Զ���������
apiReturn _stdcall ReadAutoParam(HANDLE hScanner, ReaderAutoParam * pParam,int Address);

//���ö�д���Զ���������
apiReturn _stdcall WriteAutoParam(HANDLE hScanner, ReaderAutoParam * pParam,int Address);

//���õ��ƶ�
apiReturn _stdcall SetModDepth(HANDLE hScanner, int ModDepth,int Address);

//��õ��ƶ�
apiReturn _stdcall GetModDepth(HANDLE hScanner, int *ModDepth,int Address);

//�ָ���д����������
apiReturn _stdcall ReadFactoryParameter(HANDLE hScanner,int Address);

//ѡ������
apiReturn _stdcall SetAntenna(HANDLE hScanner, int Antenna,int Address);

//��λ��д��
apiReturn _stdcall Reboot(HANDLE hScanner,int Address);

//����/ֹͣ��д���Զ�ģʽ
apiReturn _stdcall AutoMode(HANDLE hScanner,int Mode,int Address);

//ATA����ȡID��ǩ
apiReturn _stdcall ATA_ListTagID(HANDLE hScanner, BYTE *btID, int *nCounter,int Address);

//����ڴ�
apiReturn _stdcall ClearTagMemory(HANDLE hScanner,int Address);

//����ʱ��
apiReturn _stdcall SetReaderTime(HANDLE hScanner, ReaderDate *time,int Address);

//���ʱ��
apiReturn _stdcall GetReaderTime(HANDLE hScanner, ReaderDate *time,int Address);

//���ñ�ǩ������
apiReturn _stdcall SetReportFilter(HANDLE hScanner, int ptr, int len, BYTE *mask,int Address);

//��ñ�ǩ������
apiReturn _stdcall GetReportFilter(HANDLE hScanner, int *ptr, int *len, BYTE *mask,int Address);

//��������
apiReturn _stdcall AddLableID(HANDLE hScanner, int listlen, int datalen, BYTE * data);

//ɾ������
apiReturn _stdcall DelLableID(HANDLE hScanner, int listlen, int datalen, BYTE * data);

//�������
apiReturn _stdcall GetLableID(HANDLE hScanner, int startaddr, int listlen, int *relistlen, int *taglen, BYTE * data);

//��ü�¼
apiReturn _stdcall GetRecord(HANDLE hScanner, ReaderDate *stime, ReaderDate *etime, int startaddr, int listlen, int *relistlen, int *taglen, BYTE * data);

//ɾ��ȫ����¼
apiReturn _stdcall DeleteAllRecord(HANDLE hScanner);

//����֪ͨ
apiReturn _stdcall ReportNow(HANDLE hScanner,int Address);

//��ñ�ǩ��¼
apiReturn _stdcall GetTagInfo(HANDLE hScanner, int straddr, BYTE Counter, BYTE* len, BYTE* Data,int Address);

//��ö�д��ID
apiReturn _stdcall SetReaderID(HANDLE hScanner, BYTE *ReaderID,int Address);

//��ö�д��ID
apiReturn _stdcall GetReaderID(HANDLE hScanner, BYTE *ReaderID,int Address);

//��ö�д���ڲ�ģ��İ汾,add by mqs 20130320
apiReturn _stdcall GetModuleVer(HANDLE hScanner, BYTE *bModuleVer,int Address);

//==============================��������==============================
//���ö�д��IP��ַ
apiReturn _stdcall SetReaderNetwork(HANDLE hScanner, BYTE IP_Address[4], int Port, BYTE Mask[4], BYTE Gateway[4],int Address);

//��ö�д��IP��ַ
apiReturn _stdcall GetReaderNetwork(HANDLE hScanner, BYTE *IP_Address, int *Port, BYTE *Mask, BYTE *Gateway,int Address);

//���ö�д��MAC��ַ
apiReturn _stdcall SetReaderMAC(HANDLE hScanner, BYTE MAC[6],int Address);

//��ö�д��MAC��ַ
apiReturn _stdcall GetReaderMAC(HANDLE hScanner, BYTE *MAC,int Address);
//==============================IO����==============================
//���ö�д���̵���״̬
apiReturn _stdcall SetRelay(HANDLE hScanner, int relay,int Address);

//��ö�д���̵���״̬
apiReturn _stdcall GetRelay(HANDLE hScanner, int *relay,int Address);

//==============================ISO-6B���ݶ�д����==============================
//����ǩ����
apiReturn _stdcall ISO6B_LabelPresent(HANDLE hScanner, int *nCounter,int Address);

//��ȡISO6B��ǩID��
apiReturn _stdcall ISO6B_ReadLabelID(HANDLE hScanner, BYTE *IDBuffer, int *nCounter,int Address);

//�г�ѡ����ǩ
apiReturn _stdcall ISO6B_ListSelectedID(HANDLE hScanner, int Cmd, int ptr, BYTE Mask, BYTE *Data, BYTE *IDBuffer, int *nCounter,int Address);

//��һ������
apiReturn _stdcall ISO6B_ReadByteBlock(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE len,BYTE *Data,int Address);

//һ��д4�ֽ�����
apiReturn _stdcall ISO6B_WriteByteBlock(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE len, BYTE *Data,int Address);

//һ��дһ�ֽ�����
apiReturn _stdcall ISO6B_WriteAByte(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE len, BYTE *Data,int Address);

//д������ݣ��ֽ�������16
apiReturn _stdcall ISO6B_WriteLongBlock(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE len, BYTE *Data,int Address);

//��д����״̬
apiReturn _stdcall ISO6B_WriteProtect(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr,int Address);

//��д����״̬
apiReturn _stdcall ISO6B_ReadWriteProtect(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE *Protected,int Address);

//ȫ�����
apiReturn _stdcall ISO6B_ClearMemory(HANDLE hScanner, BYTE CardType, BYTE *IDBuffer,int Address);

//==============================EPC C1G2���ݶ�д����==============================
//��ȡEPC1G2��ǩID��
apiReturn _stdcall EPC1G2_ReadLabelID(HANDLE hScanner, BYTE mem, int ptr, BYTE len, BYTE *mask, BYTE *IDBuffer, int *nCounter,int Address);

//��һ������
apiReturn _stdcall EPC1G2_ReadWordBlock(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len, BYTE *Data, BYTE *AccessPassword,int Address);

//дһ������
apiReturn _stdcall EPC1G2_WriteWordBlock(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len, BYTE *Data, BYTE *AccessPassword,int Address);

//���ö�д����״̬
apiReturn _stdcall EPC1G2_SetLock(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE Lock, BYTE *AccessPassword,int Address);

//������ǩ����
apiReturn _stdcall EPC1G2_EraseBlock(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len,int Address);

//�������߱�ǩ
apiReturn _stdcall EPC1G2_KillTag(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE *KillPassword,int Address);

//дEPC
apiReturn _stdcall EPC1G2_WriteEPC(HANDLE hScanner, BYTE len, BYTE *Data, BYTE *AccessPassword,int Address);

//��������
apiReturn _stdcall EPC1G2_BlockLock(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE ptr, BYTE *AccessPassword,int Address);

//EAS״̬��������
apiReturn _stdcall EPC1G2_ChangeEas(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE State, BYTE *AccessPassword,int Address);

//EAS��������
apiReturn _stdcall EPC1G2_EasAlarm(HANDLE hScanner,int Address);

//����������
apiReturn _stdcall EPC1G2_ReadProtect(HANDLE hScanner,BYTE *AccessPassword, BYTE EPC_WORD, BYTE *IDBuffer,int Address);

//��λ����������
apiReturn _stdcall EPC1G2_RStreadProtect(HANDLE hScanner, BYTE *AccessPassword,int Address);

//�����û������ݿ������
apiReturn _stdcall EPC1G2_BlockReadLock(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE Lock, BYTE *AccessPassword,int Address);

//ʶ��EPCͬʱ������
apiReturn _stdcall EPC1G2_ReadEPCandData(HANDLE hScanner, BYTE *EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len, BYTE *Data, int Address);

//Ƶ��У��
apiReturn _stdcall EPC1G2_Calibrate(HANDLE hScanner, BYTE *AccessPassword, BYTE Kword);

//����ǩ
apiReturn _stdcall EPC1G2_DetectTag(HANDLE hScanner,int Address);
//==============================TK900���ݶ�д����==============================
//��ȡTK900��ǩID��
apiReturn _stdcall TK900_ReadLabelID(HANDLE hScanner, BYTE *IDBuffer, int *nCounter,int Address);

//��һ������
apiReturn _stdcall TK900_ReadPageBlock(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE len,BYTE *Data,int Address);

//дһ������
apiReturn _stdcall TK900_WritePageBlock(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE *Data,int Address);

//��д����״̬
apiReturn _stdcall TK900_SetProtect(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE len,int Address);

//��д����״̬
apiReturn _stdcall TK900_GetProtect(HANDLE hScanner, BYTE *IDBuffer ,BYTE *state,int Address);

//���ñ�ǩ����TTO״̬
apiReturn _stdcall TK900_SetTTO(HANDLE hScanner, BYTE *IDBuffer ,BYTE ptr, BYTE len,int Address);

//��ȡTTO��ǩ
apiReturn _stdcall TK900_ListTagPage(HANDLE hScanner, BYTE *IDBuffer ,BYTE *Data,int Address);

//�õ�TTO��ǩ�Ŀ�ʼ��ַ�ͳ���
apiReturn _stdcall TK900_GetTTOStartAdd(HANDLE hScanner, BYTE *IDBuffer ,BYTE *len,int Address);

//==============================���ں�������==============================
//���Ӷ�д��
apiReturn _stdcall Net_ConnectScanner(SOCKET *hSocket,char *nTargetAddress,UINT nTargetPort,char *nHostAddress,UINT nHostPort);

//�Ͽ�����
apiReturn _stdcall Net_DisconnectScanner();
apiReturn _stdcall Net_DisconnectScannerEx(SOCKET sSocket);

//==============================�豸��������==============================
//���ò�����
apiReturn _stdcall Net_SetBaudRate(SOCKET hSocket, int nBaudRate);

//��ȡ�汾��
apiReturn _stdcall Net_GetReaderVersion(SOCKET hSocket, WORD *wHardVer, WORD  *wSoftVer);

//�趨�������
apiReturn _stdcall Net_SetOutputPower(SOCKET hSocket, int nPower);

//�趨����Ƶ��
apiReturn _stdcall Net_SetFrequency(SOCKET hSocket, int Min_Frequency, int Max_Frequency);

//��ö�д������Ƶ�ʷ�Χ
apiReturn _stdcall Net_GetFrequencyRange(SOCKET hSocket, BYTE *Frequency);

//�趨����Ƶ��(���R2000ģ��ר��)
apiReturn _stdcall Net_SetFrequencyEx(SOCKET hSocket, BYTE *Frequency);

//��ö�д������Ƶ�ʷ�Χ(���R2000ģ��ר��)
apiReturn _stdcall Net_GetFrequencyRangeEx(SOCKET hSocket, BYTE *Frequency);

//��ȡ��д��������������
apiReturn _stdcall Net_ReadBasicParam(SOCKET hSocket, ReaderBasicParam *pParam);

//���ö�д��������������
apiReturn _stdcall Net_WriteBasicParam(SOCKET hSocket, ReaderBasicParam *pParam);

//��ȡ��д���Զ���������
apiReturn _stdcall Net_ReadAutoParam(SOCKET hSocket, ReaderAutoParam *pParam);

//���ö�д���Զ���������
apiReturn _stdcall Net_WriteAutoParam(SOCKET hSocket, ReaderAutoParam *pParam);

//���õ��ƶ�
apiReturn _stdcall Net_SetModDepth(SOCKET hSocket, int ModDepth);

//��õ��ƶ�
apiReturn _stdcall Net_GetModDepth(SOCKET hSocket, int *ModDepth);

//ѡ������
apiReturn _stdcall Net_SetAntenna(SOCKET hSocket, int Antenna);

//�ָ���д����������
apiReturn _stdcall Net_ReadFactoryParameter(SOCKET hSocket);

//��λ��д��
apiReturn _stdcall Net_Reboot(SOCKET hSocket);

//ֹͣ/������д���Զ�ģʽ
apiReturn _stdcall Net_AutoMode(SOCKET hSocket,int Mode);

//ATA����ȡID��ǩ
apiReturn _stdcall Net_ATA_ListTagID(SOCKET hSocket, BYTE *btID, int *nCounter);

//����ڴ�
apiReturn _stdcall Net_ClearTagMemory(SOCKET hSocket);

//����ʱ��
apiReturn _stdcall Net_SetReaderTime(SOCKET hSocket, ReaderDate *time);

//���ʱ��
apiReturn _stdcall Net_GetReaderTime(SOCKET hSocket, ReaderDate *time);

//���ñ�ǩ������
apiReturn _stdcall Net_SetReportFilter(SOCKET hSocket, int ptr, int len, BYTE *mask);

//��ñ�ǩ������
apiReturn _stdcall Net_GetReportFilter(SOCKET hSocket, int *ptr, int *len, BYTE *mask);

//��������
apiReturn _stdcall Net_AddLableID(SOCKET hSocket, int listlen, int datalen, BYTE * data);

//ɾ������
apiReturn _stdcall Net_DelLableID(SOCKET hSocket, int listlen, int datalen, BYTE * data);

//�������
apiReturn _stdcall Net_GetLableID(SOCKET hSocket, int startaddr, int listlen, int *relistlen, int *taglen, BYTE * data);

//��ü�¼
apiReturn _stdcall Net_GetRecord(SOCKET hSocket, ReaderDate *stime, ReaderDate *etime, int startaddr, int listlen, int *relistlen, int *taglen, BYTE * data);

//ɾ��ȫ����¼
apiReturn _stdcall Net_DeleteAllRecord(SOCKET hSocket);

//����֪ͨ
apiReturn _stdcall Net_ReportNow(SOCKET hSocket);

//��ñ�ǩ��¼
apiReturn _stdcall Net_GetTagInfo(SOCKET hSocket, int straddr, BYTE Counter, BYTE* len, BYTE* Data);

//���ö�д��ID
apiReturn _stdcall Net_SetReaderID(SOCKET hSocket, BYTE *ReaderID);

//��ö�д��ID
apiReturn _stdcall Net_GetReaderID(SOCKET hSocket, BYTE *ReaderID);

//��ö�д���ڲ�ģ��İ汾,add by mqs 20130320
apiReturn _stdcall Net_GetModuleVer(SOCKET hSocket, BYTE *bModuleVer);

//==============================��������==============================
//���ö�д��IP��ַ
apiReturn _stdcall Net_SetReaderNetwork(SOCKET hSocket, BYTE IP_Address[4], int Port, BYTE Mask[4], BYTE Gateway[4]);

//��ö�д��IP��ַ
apiReturn _stdcall Net_GetReaderNetwork(SOCKET hSocket, BYTE *IP_Address, int *Port, BYTE *Mask, BYTE *Gateway);

//���ö�д��MAC��ַ
apiReturn _stdcall Net_SetReaderMAC(SOCKET hSocket, BYTE MAC[6]);

//��ö�д��MAC��ַ
apiReturn _stdcall Net_GetReaderMAC(SOCKET hSocket, BYTE *MAC);

//==============================IO����==============================
//���ö�д���̵���״̬
apiReturn _stdcall Net_SetRelay(SOCKET hSocket, int relay);

//��ö�д���̵���״̬
apiReturn _stdcall Net_GetRelay(SOCKET hSocket, int *relay);

//==============================ISO-6B���ݶ�д����==============================
//����ǩ����
apiReturn _stdcall Net_ISO6B_LabelPresent(SOCKET hSocket, int *nCounter);

//��ȡISO6B��ǩID��
apiReturn _stdcall Net_ISO6B_ReadLabelID(SOCKET hSocket, BYTE *IDBuffer, int *nCounter);

//�г�ѡ����ǩ
apiReturn _stdcall Net_ISO6B_ListSelectedID(SOCKET hSocket, int Cmd, int ptr, BYTE Mask, BYTE *Data, BYTE *IDBuffer, int *nCounter);

//��һ������
apiReturn _stdcall Net_ISO6B_ReadByteBlock(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr, BYTE len,BYTE *Data);

//һ��д4�ֽ�����
apiReturn _stdcall Net_ISO6B_WriteByteBlock(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr, BYTE len, BYTE *Data);

//һ��дһ�ֽ�����
apiReturn _stdcall Net_ISO6B_WriteAByte(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr, BYTE len, BYTE *Data);

//��д����״̬
apiReturn _stdcall Net_ISO6B_WriteProtect(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr);

//��д����״̬
apiReturn _stdcall Net_ISO6B_ReadWriteProtect(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr, BYTE *Protected);

//==============================EPC C1G2���ݶ�д����==============================
//��ȡEPC1G2��ǩID��
apiReturn _stdcall Net_EPC1G2_ReadLabelID(SOCKET hSocket, BYTE mem, int ptr, BYTE len, BYTE *mask, BYTE *IDBuffer, int *nCounter);

//��һ������
apiReturn _stdcall Net_EPC1G2_ReadWordBlock(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len, BYTE *Data, BYTE *AccessPassword);

//дһ������
apiReturn _stdcall Net_EPC1G2_WriteWordBlock(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len, BYTE *Data, BYTE *AccessPassword);

//���ö�д����״̬
apiReturn _stdcall Net_EPC1G2_SetLock(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE Lock, BYTE *AccessPassword);

//������ǩ����
apiReturn _stdcall Net_EPC1G2_EraseBlock(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len);

//�������߱�ǩ
apiReturn _stdcall Net_EPC1G2_KillTag(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE *KillPassword);

//дEPC
apiReturn _stdcall Net_EPC1G2_WriteEPC(SOCKET hSocket,BYTE len, BYTE *Data, BYTE *AccessPassword);

//��������
apiReturn _stdcall Net_EPC1G2_BlockLock(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE ptr, BYTE *AccessPassword);

//EAS״̬��������
apiReturn _stdcall Net_EPC1G2_ChangeEas(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE State, BYTE *AccessPassword);

//EAS��������
apiReturn _stdcall Net_EPC1G2_EasAlarm(SOCKET hSocket);

//����������
apiReturn _stdcall Net_EPC1G2_ReadProtect(SOCKET hSocket,BYTE *AccessPassword, BYTE EPC_WORD, BYTE *IDBuffer);

//��λ����������
apiReturn _stdcall Net_EPC1G2_RStreadProtect(SOCKET hSocket, BYTE *AccessPassword);

//ʶ��EPCͬʱ������
apiReturn _stdcall Net_EPC1G2_ReadEPCandData(SOCKET hSocket, BYTE *EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len, BYTE *Data, int Address);

//�����û������ݿ������
apiReturn _stdcall Net_EPC1G2_BlockReadLock(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE Lock, BYTE *AccessPassword);

//����ǩ
apiReturn _stdcall Net_EPC1G2_DetectTag(SOCKET hSocket);

//==============================TK900���ݶ�д����==============================
//��ȡTK900��ǩID��
apiReturn _stdcall Net_TK900_ReadLabelID(SOCKET hSocket, BYTE *IDBuffer, int *nCounter);

//��һ������
apiReturn _stdcall Net_TK900_ReadPageBlock(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr, BYTE len,BYTE *Data);

//дһ������
apiReturn _stdcall Net_TK900_WritePageBlock(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr, BYTE *Data);

//��д����״̬
apiReturn _stdcall Net_TK900_SetProtect(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr, BYTE len);

//��д����״̬
apiReturn _stdcall Net_TK900_GetProtect(SOCKET hSocket, BYTE *IDBuffer ,BYTE *state);

//���ñ�ǩ����TTO״̬
apiReturn _stdcall Net_TK900_SetTTO(SOCKET hSocket, BYTE *IDBuffer ,BYTE ptr, BYTE len);

//��ȡTTO��ǩ
apiReturn _stdcall Net_TK900_ListTagPage(SOCKET hSocket, BYTE *IDBuffer ,BYTE *Data);

//�õ�TTO��ǩ�Ŀ�ʼ��ַ�ͳ���
apiReturn _stdcall Net_TK900_GetTTOStartAdd(SOCKET hSocket, BYTE *IDBuffer ,BYTE *len);


////////////////////////////////////////////////////////////////////////////////

//�޸Ķ�д��Ƶ�ʷ�Χ
apiReturn _stdcall ChangeFrequency(HANDLE hScanner, BYTE fre,int Address);

//�޸Ķ�д��Ƶ�ʷ�Χ
apiReturn _stdcall Net_ChangeFrequency(SOCKET hSocket, BYTE fre);

//����Ӳ���汾
apiReturn _stdcall SetHardVersion(HANDLE hScanner, int wHardVer,int wHardVer2,int Address);

//�޸Ķ�д��Ӳ���汾��
apiReturn _stdcall Net_SetHardVersion(SOCKET hSocket, int wHardVer,int wHardVer2);

//���ö�д������������������
apiReturn _stdcall WriteFactoryBasicParam(HANDLE hScanner, ReaderBasicParam * pParam,int Address);

//���ö�д�������Զ���������
apiReturn _stdcall WriteFactoryAutoParam(HANDLE hScanner, ReaderAutoParam * pParam,int Address);

//���ö�д��������������
apiReturn _stdcall Net_WriteFactoryBasicParam(SOCKET hSocket, ReaderBasicParam *pParam);

//���ö�д���Զ���������
apiReturn _stdcall Net_WriteFactoryAutoParam(SOCKET hSocket, ReaderAutoParam *pParam);

//���Ӷ�д��
apiReturn _stdcall ConnectScanner485(HANDLE *hScanner, char *szPort, int nBaudRate,int Address);

//��ȡ��д����ϵͳ״̬,dwData������:0x00000200ֵ
apiReturn _stdcall GetSystemState(HANDLE hScanner, DWORD *dwData, int Address);

//��ȡ��д����ϵͳ״̬,dwData������:0x00000200ֵ
apiReturn _stdcall Net_GetSystemState(SOCKET hSocket, DWORD *dwData);

//��ȡ��д���Ĵ�ӡģʽ,dwData������:0x00000200ֵ
apiReturn _stdcall GetPrintInfo(HANDLE hScanner, DWORD *dwData, int Address);

//��ȡ��д���Ĵ�ӡģʽ,dwData������:0x00000200ֵ
apiReturn _stdcall Net_GetPrintInfo(SOCKET hSocket, DWORD *dwData);

//���ö�д���Ĵ�ӡģʽ,dwData������:0x00000200ֵ
apiReturn _stdcall SetPrintInfo(HANDLE hScanner, DWORD dwData, int Address);

//���ö�д���Ĵ�ӡģʽ,dwData������:0x00000200ֵ
apiReturn _stdcall Net_SetPrintInfo(SOCKET hSocket, DWORD dwData);

//dwTimeout Ϊ�������û��ӳ�ĳ�ʱʱ��
typedef void (WINAPI *OnCallbackTimeOutFunc)(DWORD dwTimeout);
//���ó�ʱʱ��
apiReturn _stdcall WE_SetCommunicationTimeout(DWORD dwTimeout, OnCallbackTimeOutFunc fFunc);

//////////////////////////////////////////////////////////////////////////
//��;:		ȡ��ɨ�赽��IP
//������:	WE_GetScanReaderIP
//����:		����д��IP������
//�������:	��
//�������:	ReaderIP1 Ϊ��д��IP1, ReaderIP2 Ϊ��д��IP2, ReaderIP3 Ϊ��д��IP3, ReaderIP4 Ϊ��д��IP4
//			Port ָ�˿� ��"192","168","0","100","1969"--->IP:192.168.0.100 1969
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:		�ⲿ�ӿ�
//////////////////////////////////////////////////////////////////////////
BOOL _stdcall WE_GetScanReaderIP(LPSTR ReaderIP1, LPSTR ReaderIP2, LPSTR ReaderIP3, LPSTR ReaderIP4, LPSTR Port);

//////////////////////////////////////////////////////////////////////////
//��;:		��IP�Ͷ˿�
//������:	WE_SetAddrIpPort
//����:		��д���Զ�����ʱ���õ�IP�Ͷ˿�
//�������:	lpAddr ΪIP��ַ���磺192.168.0.71 dwPort Ϊ��˿�:��5001
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//����:		
//////////////////////////////////////////////////////////////////////////
BOOL _stdcall WE_SetAddrIpPort(LPSTR lpAddr, DWORD dwPort);

//////////////////////////////////////////////////////////////////////////
//��;:		����ģʽɨ���¼��ʼ��	
//������:	WE_StartScanAutoRecord
//����:		��д���Զ�����ʱ��ȡ��¼��ʼ��ʼ��
//�������:	lpData Ϊͨ�ž��, dwOpt ָ��������ͨ��(1-����,2-����,3-RS485) fFunc Ϊ����ָ��
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//����:		�纯��ָ������:typedef void (WINAPI *OnCallbackAutoReceiveData)(DWORD dwSize)
//////////////////////////////////////////////////////////////////////////
BOOL _stdcall WE_StartScanAutoRecord(LPVOID lpData, DWORD dwOpt, OnCallbackAutoReceiveData fFunc);

//////////////////////////////////////////////////////////////////////////
//��;:		����ģʽɨ���¼����	
//������:	WE_StopScanAutoRecord
//����:		��д���Զ�����ʱ��ȡ��¼���������
//�������:	��
//�������:	��
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
BOOL _stdcall WE_StopScanAutoRecord();

//////////////////////////////////////////////////////////////////////////
//��;:		ȡ��¼	
//������:	WE_GetScanAutoRecord
//����:		��д���Զ�����ʱ��ȡ��¼
//�������:	dwSize ָ���С
//�������:	lpGetBuf ���¼�ļ�¼
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
BOOL _stdcall WE_GetScanAutoRecord(LPSTR lpGetBuf, DWORD dwSize);




//////////////////////////////////////////////////////////////////////////
//��;:		����ѯָ��	
//������:	GetReaderGroupPolling
//����:		������ѯ
//�������:	hScanner ΪBPA�ľ��,
//�������:	lpBuf Ϊ�յ���ָ�룬lpSize Ϊ�䳤��
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//����:		��ѯ��ָ���BPA-9-proctol.pdf
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall GetReaderGroupPolling(HANDLE hScanner, BYTE *lpBuf, int *lpSize);


//////////////////////////////////////////////////////////////////////////
//��;:		����ѯָ��	
//������:	GetReaderBPAEpc
//����:		ȡ��д��BPA��EPC
//�������:	hScanner ΪBPA�ľ��,
//�������:	lpBuf Ϊ�յ���ָ�룬lpSize Ϊ�䳤��
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//����:		��ѯ��ָ���BPA-9-proctol.pdf
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall GetReaderBPAEpc(HANDLE hScanner, BYTE *lpBuf, int *lpSize);


//////////////////////////////////////////////////////////////////////////
//��;:		����ѯָ�����	
//������:	GetReaderBPAGranted
//����:		���д��������
//�������:	hScanner ΪBPA�ľ��,
//�������:	lpBuf Ϊ�յ���ָ�룬lpSize Ϊ�䳤��
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//����:		��ѯ��ָ���BPA-9-proctol.pdf
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall GetReaderBPAGranted(HANDLE hScanner, BYTE *lpBuf, int *lpSize);


//////////////////////////////////////////////////////////////////////////
//��;:		����ѯָ��ܾ�
//������:	GetReaderBPADenied
//����:		���д�����ܾ�
//�������:	hScanner ΪBPA�ľ��,
//�������:	lpBuf Ϊ�յ���ָ�룬lpSize Ϊ�䳤��
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//����:		��ѯ��ָ���BPA-9-proctol.pdf
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall GetReaderBPADenied(HANDLE hScanner, BYTE *lpBuf, int *lpSize);


//////////////////////////////////////////////////////////////////////////
//��;:		��ʱ��ָ��
//������:	SetReaderTimeStamp
//����:		���д����ʱ����Ϣ
//�������:	hScanner ΪBPA�ľ��,
//�������:	lpBuf Ϊ�յ���ָ�룬lpSize Ϊ�䳤��
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//����:		��ѯ��ָ���BPA-9-proctol.pdf
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall SetReaderTimeStamp(HANDLE hScanner, BYTE *lpBuf, int *lpSize);


//////////////////////////////////////////////////////////////////////////
//��;:		����BPA��д��
//������:	ConnectScannerBPA
//����:		���Ӷ�д��
//�������:	szPort ָ�ĸ�COM��, nBaudRate Ϊͨ�����ʣ���ΪҪ��Ϊ9600,�ݲ�������
//			Address Ϊ�ĸ��˿ڣ���41 41
//�������:	hScanner ΪBPA�ľ��
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//����:		���BPA-9-proctol.pdf
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall ConnectScannerBPA(HANDLE *hScanner, char *szPort, int nBaudRate,int Address);



//////////////////////////////////////////////////////////////////////////
//��;:		ȡСģ�����
//������:	GetReaderSmallModeParam
//����:		��Сģ��Ĳ���������
//�������:	hScanner Ϊͨ�ž��,
//�������:	lpBuf Ϊ�յ���ָ�룬lpSize Ϊ�䳤��
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall GetReaderSmallModeParam(HANDLE hScanner, BYTE *lpBuf, int *lpSize);


//////////////////////////////////////////////////////////////////////////
//��;:		����Сģ�����
//������:	SetReaderSmallModeParam
//����:		��Сģ��Ĳ���д������
//�������:	hScanner Ϊͨ�ž��,lpBuf Ϊ���͵�ָ�룬lpSize Ϊ�䳤��
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall SetReaderSmallModeParam(HANDLE hScanner, BYTE *lpBuf, int lpSize);







//////////////////////////////////////////////////////////////////////////
//�й�����������ķǱ�--Rubbish//////---START/////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//��;:		���ö�д��ID����
//������:	RU_SetReaderID
//����:		������д������
//�������:	hScanner Ϊͨ�ž��,ReaderID Ϊ���͵��׵�ַ(����1�ֽ�)��Address Ϊ��RS485��ַ
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_SetReaderID(HANDLE hScanner, BYTE *ReaderID, int Address);

//////////////////////////////////////////////////////////////////////////
//��;:		���ö�д��ID����
//������:	RU_SetReaderIDNet
//����:		������д������
//�������:	hSocket Ϊͨ�ž��,ReaderID Ϊ���͵��׵�ַ(����1�ֽ�)��Address Ϊ��RS485��ַ
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_SetReaderIDNet(SOCKET hSocket, BYTE *ReaderID);

//////////////////////////////////////////////////////////////////////////
//��;:		��ȡ��д��ID����
//������:	RU_GetReaderID
//����:		ȡ����д��ID����
//�������:	hScanner Ϊͨ�ž��,ReaderID Ϊ���͵��׵�ַ(����1�ֽ�)��Address Ϊ��RS485��ַ
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_GetReaderID(HANDLE hScanner, BYTE *ReaderID, int Address);

//////////////////////////////////////////////////////////////////////////
//��;:		��ȡ��д��ID����
//������:	RU_GetReaderIDNet
//����:		ȡ����д��ID����
//�������:	hSocket Ϊͨ�ž��,ReaderID Ϊ���͵ĵ�ַָ��(1�ֽ�)
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_GetReaderIDNet(SOCKET hSocket, BYTE *ReaderID);

//////////////////////////////////////////////////////////////////////////
//��;:		���ö�д����¼
//������:	RU_SetReaderRecord
//����:		����¼д������
//�������:	hScanner Ϊͨ�ž��,lpSetBuf Ϊ���͵ĵ�ַָ��(1�ֽ�ID+6�ֽ�ʱ��������ʱ����)
//			Address Ϊ��RS485��ַ
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_SetReaderRecord(HANDLE hScanner, BYTE *lpSetBuf, int Address);

//////////////////////////////////////////////////////////////////////////
//��;:		���ö�д����¼
//������:	RU_SetReaderRecordNet
//����:		����¼д������
//�������:	hSocket Ϊͨ�ž��,lpSetBuf Ϊ���͵ĵ�ַָ��(1�ֽ�ID+6�ֽ�ʱ��������ʱ����)
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_SetReaderRecordNet(SOCKET hSocket, BYTE *lpSetBuf);

//////////////////////////////////////////////////////////////////////////
//��;:		��ȡ��д��ȫ����Ϣ
//������:	RU_GetExportRecord
//����:		
//�������:	hScanner Ϊͨ�ž��,lpGetBuf Ϊ���͵ĵ�ַָ��(28�ֽ�)��Address Ϊ��RS485��ַ
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_GetExportRecord(HANDLE hScanner, BYTE *lpGetBuf, int Address);

//////////////////////////////////////////////////////////////////////////
//��;:		��ȡ��д��ȫ����Ϣ
//������:	RU_GetExportRecordNet
//����:		
//�������:	hSocket Ϊͨ�ž��,lpGetBuf Ϊ���͵ĵ�ַָ��(28�ֽ�)
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_GetExportRecordNet(SOCKET hSocket, BYTE *lpGetBuf);

//////////////////////////////////////////////////////////////////////////
//��;:		ɾ����д��ȫ����Ϣ
//������:	RU_DeleteAllRecord
//����:		
//�������:	hScanner Ϊͨ�ž��,Address Ϊ��RS485��ַ
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_DeleteAllRecord(HANDLE hScanner, int Address);

//////////////////////////////////////////////////////////////////////////
//��;:		ɾ����д��ȫ����Ϣ
//������:	RU_DeleteAllRecordNet
//����:		
//�������:	hSocket Ϊͨ�ž��
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_DeleteAllRecordNet(SOCKET hSocket);

//////////////////////////////////////////////////////////////////////////
//�й�����������ķǱ�--Rubbish//////---END///////////////////////////////
//////////////////////////////////////////////////////////////////////////












//��ʾ��Ϣ
apiReturn _stdcall ShowInfo(char *chStr);

apiReturn _stdcall WriteAppLogFile(char* FileName, int Line, char* fmt, ...);
//////////////////////////////////////////////////////////////////////////
//��;:		16����תASC��	
//������:	Hex2Asc
//����:		16����תASC��
//�������:	inHex Ϊ16������
//�������:	pOutStr ΪASC��
//����ֵ:	������
//��ע:
//����:		0x12===>'12';
//////////////////////////////////////////////////////////////////////////
void _stdcall Hex2Asc(unsigned char inHex, unsigned char *pOutStr);
void _stdcall Asc2Bcd(char *bcd, char *asc, int len);
void _stdcall Bcd2Asc(char *asc, char *bcd, int len);


//////////////////////////////////////////////////////////////////////////
//��;:		Bcd��ת��ASC�벢���ո�
//������:	Bcd2AscEx
//����:		��BCD��ת��ASC��,��16����ת���ַ���
//�������:	bcd ָ16���Ƶ�ָ��
//			len ָ�䳤��
//�������:	bcd ָת�������ָ��
//����ֵ:	��
//��ע:		��Bcd2Asc��ͬ���Ƕ���ո���0x40 0x03==>40 03 ,������4003
//////////////////////////////////////////////////////////////////////////
void _stdcall Bcd2AscEx(char *asc, char *bcd, int len);


//////////////////////////////////////////////////////////////////////////
//��;:		���ñ༭�ؼ����
//������:	Debug_SetEditHwnd
//����:		
//�������:	HWND hEdit
//�������:	��
//����ֵ:	��
//��ע:
//////////////////////////////////////////////////////////////////////////
void PASCAL  Debug_SetEditHwnd(HWND hEdit);

//////////////////////////////////////////////////////////////////////////
//��;:		�����Ϣ	
//������:	Debug_Printf
//����:		�򼭿��������Ϣ
//�������:	fmtΪ�����ʽ
//�������:	��
//����ֵ:	����AK_TRUEΪ��ʼ���ɹ�������AK_FALSEΪ��ʼ��ʧ��
//��ע:
//����:
//////////////////////////////////////////////////////////////////////////
int PASCAL	Debug_Printf(const char *fmt, ...);

//////////////////////////////////////////////////////////////////////////
//��;:		�����Ϣ	
//������:	DebugOutput
//����:		���ļ��������Ϣ
//�������:	fmtΪ�����ʽ
//�������:	��
//����ֵ:	����AK_TRUEΪ��ʼ���ɹ�������AK_FALSEΪ��ʼ��ʧ��
//��ע:
//����:
//////////////////////////////////////////////////////////////////////////
BOOL PASCAL	DebugOutput(char	*FileName, char *s, ...);
#ifdef __cplusplus
}
#endif



#endif

#endif
