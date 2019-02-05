#ifndef __VHHandsetAPI_H__
#define __VHHandsetAPI_H__
#include "WINSOCK2.h"
//#include "WINSOCK.h"

#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")
//==============================��������==============================
#define	ID_MAX_SIZE_64BIT	8		//���ӱ�ǩ��ID��Ϊ64bit
#define ID_MAX_SIZE_96BIT	65		//���ӱ�ǩ��ID��
#define MAX_LABELS			100		// һ�ζ�д������಻����100����ǩ

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

#define Success					"��ȷ"
#define TransportError			"ͨѶʧ��"
#define SendBufferError			"����ʧ��"
#define ReceiveBufferError		"����ʧ��"
#define CheckSumError			"У��ʹ���"
#define CommandError			"���ƥ��"
#define ReturnPacketError		"���ذ�����"
#define ReturnPacketheadError	"���ذ���ͷ����"

//�����������
#define _no_cardID_input   0x20   //��������

//==============================�������Ͷ���==============================
typedef USHORT apiReturn;   // ��������ֵ����
//typedef DWORD apiReturn;   // ��������ֵ����
//typedef long apiReturn;   // ��������ֵ����

typedef struct tagReaderDate
{
	BYTE	Year;			//��
	BYTE	Month;			//��
	BYTE	Day;			//��
	BYTE	Hour;			//ʱ
	BYTE	Minute;			//��
	BYTE	Second;			//��
}ReaderDate;

typedef struct tagHandsetParam
{
	BYTE	TagType;		//��ǩ���ࣺ01H��ISO18000-6B��02H��EPCC1��04H��EPCC1G2��08H��EM4442��	(0)
	BYTE	Alarm;			//bit0-bit7 bit0:0-��������1-���� bit1 0-��ʹ�ð����� 1-ʹ�ð�������	(1)
	BYTE	OutputMode;	    //�������ģʽ��0-���沢ֱ�����,1-���浫��ֱ�����,2-�����浫ֱ�����  (2)
	BYTE	USBBaudRate;	//USB�ӿڲ����� 04-9600 05-19200  06-38400  07-57600 08-115200			(3)
	BYTE	BtBaudRate;		//��������ͨѶ������													(4)
	BYTE	Min_Frequence;	//����΢���ź�Ƶ�ʵ���ʼ�㣬ȡֵ�� 1~63��								(5)
	BYTE	Max_Frequence;	//����΢���ź�Ƶ�ʵ���ʼ�㣬ȡֵ�� 1~63��								(6)
	BYTE	Power;			//���书��ֵ��ȡֵ��0~160��												(7)
	BYTE	RFhrdVer1;		//RFģ��Ӳ�����汾														(8)
	BYTE	RFhrdVer2;		//RFģ��Ӳ���ΰ汾														(9)
	BYTE	RFSoftVer1;		//RFģ��������汾														(10)
	BYTE	RFSoftVer2;		//RFģ������ΰ汾														(11)
	BYTE	ISTID;		    //�Ƿ��TID��															(12)
	BYTE	TIDAddr;		//TID��ȡ��ʼλ��														(13)
	BYTE	TIDLen;		    //TID��ȡ����															(14)
	BYTE	ISUSER;		    //�Ƿ��USER															(15)
	BYTE	USERAddr;		//USER��ȡ��ʼλ��														(16)
	BYTE	USERLen;		//USER��ȡ����															(17)
	BYTE	ISVibrate;		//�����,0-����1-��													(18)
	BYTE	Modutype;		//ģ������,0---R2000, 1---VM5E											(19)
	BYTE	Reserve21;		//����																	(20)
	BYTE	Reserve22;		//����																	(21)
	BYTE	Reserve23;		//����																	(22)
	BYTE	Reserve24;		//����																	(23)
	BYTE	Reserve25;		//����																	(24)
	BYTE	Reserve26;		//����																	(25)
	BYTE	Reserve27;		//����																	(26)
	BYTE	Reserve28;		//����																	(27)
	BYTE	Reserve29;		//����																	(28)
	BYTE	Reserve30;		//����																	(29)
	BYTE	Reserve31;		//����																	(30)
	BYTE	Reserve32;		//����																	(31)
}HandsetParam;

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
	
}ReaderBasicParam;

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
	BYTE    IDPosition;			//(12)�����ڵ��ӱ�ǩ�ϵĴ�ŵ�ַ��EPC��--0, USER��--1��TID��--2
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
}ReaderAutoParam;



#define			PERFIXLEN			20   //ǰ׺ֵ�ĳ���
//��д��������̲���
typedef struct tagSimParam
{
	BYTE	DataFormat;				//(0)���ݸ�ʽ���֣�16����--0, 10����--1									
	//BYTE	DataBank;				//(1)EPC��--0, USER��--1��TID��--2
	BYTE	IsPerfix;				//(2)�Ƿ�ǰ׺��1--��,0--����												
	BYTE	PerfixCode[PERFIXLEN];	//(3-22)ǰ׺ֵ,����0x00���													
	BYTE	IsEnter;				//(23)�Ƿ�س�����, 1--��,0--����											
	BYTE    StartAddress;			//(24)������ʼ��ַ															
	BYTE	DataLen;				//(25)���ݳ���
	BYTE	OutputInterval;	//(26)��׼������(0-255)(0--���ID֮���޼��)

}SimParam;

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

//==============================��д��Ӧ�ú�������==============================

//���Ӷ�д��
apiReturn _stdcall ConnectScanner(HANDLE *hScanner, char *szPort, int nBaudRate);

//�Ͽ�����
apiReturn _stdcall DisconnectScanner(HANDLE hScanner);

//���Ӷ�д��VH73B
apiReturn _stdcall ConnectScannerVH73B(HANDLE *hScanner, char *szPort, int nBaudRate);

//ͨ��USB���Ӷ�д��
apiReturn _stdcall VH_ConnectScannerUsb(HANDLE *hScanner);

//�Ͽ�����
apiReturn _stdcall VH_DisconnectScannerUsb(HANDLE hScanner);

//���USB����,bDech---1Ϊ���ߣ���������
typedef int (_stdcall *VH_fDechUsb)(BOOL bDech);

//��ʼ��USB���ɼ�⣬���뺯����ַ
apiReturn _stdcall VH_InitUsb(VH_fDechUsb fFunc);

//�ر�USB,�ͷ���Դ
apiReturn _stdcall VH_CloseUsb();


//////////////////////////////////////////////////////////////////////////
//��;:		����ͨ�ŷ�ʽ
//������:	Mux_SetCommunicationOpt
//����:		���ֳֻ���ͨ��ģʽ��������
//�������:	lOpt Ϊ���ַ�ʽͨ��(0--TCP/IP, 1--RS232,2--RS485, 3--USB)
//			lpRHand Ϊ��д���ľ��
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:		�ⲿ�ӿ�
//////////////////////////////////////////////////////////////////////////
//apiReturn _stdcall VH_SetCommunicationOpt(long lOpt, void *lpRWHand);
apiReturn _stdcall VH_SetCommunicationOpt(int lOpt, int lpRWHand);

//�ַ�ʱ��תʮ����
int StrtimetoDecimal(CString Command,BYTE *CmdBuffer);

int strtodecimal(CString Command,BYTE *CmdBuffer);

//�Ƚ�ǰ��������¼�Ƿ����
int compare(BYTE *olddata, BYTE *data, int len);
//==============================���ؿ�������==============================

//��ȡ�汾��
apiReturn _stdcall VH_GetVersion(HANDLE hScanner, WORD *wHardVer, WORD  *wSoftVer);
//��������Ŀ�ĸ�ԭ������һ��
apiReturn _stdcall GetVersion(HANDLE hScanner, WORD *wHardVer, WORD  *wSoftVer);

//����/ֹͣ�Զ�ģʽ,0--stop, 1--start
apiReturn _stdcall VH_AutoMode(HANDLE hScanner,int Mode);

//����/ֹͣ�Զ�ģʽ,0--stop, 1--start
apiReturn _stdcall AutoMode(HANDLE hScanner,int Mode);

//��������
apiReturn _stdcall AddLableID(HANDLE hScanner, int Count, int Len, BYTE * data);

//ɾ������
apiReturn _stdcall DelLableID(HANDLE hScanner);

//���ӵ�����������
apiReturn _stdcall DelSingleLableID(HANDLE hScanner, int Count, int Len, BYTE * data);

//�������
apiReturn _stdcall GetLableID(HANDLE hScanner, int startaddr, int listlen, int *nTotal, int *DataLen, BYTE * data);

//�ύ����
apiReturn _stdcall SaveLableID(HANDLE hScanner);

//��ȡ��д��������������
apiReturn _stdcall ReadHanderParam(HANDLE hScanner, HandsetParam * pParam);

//���ö�д��������������
apiReturn _stdcall WriteHanderParam(HANDLE hScanner, HandsetParam * pParam);

//////////////////////////////////////////////////////////////////////////
//��;:		ȡ�������Сģ�����
//������:	ReadSimParam
//����:		��Сģ��Ĳ���������
//�������:	hScanner Ϊͨ�ž��,
//�������:	pParam Ϊ�ṹ��ָ��
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall ReadSimParam(HANDLE hScanner, SimParam * pParam);

//////////////////////////////////////////////////////////////////////////
//��;:		���÷������Сģ�����
//������:	WriteSimParam
//����:		��Сģ��Ĳ���д������
//�������:	hScanner Ϊͨ�ž��,pParam Ϊ�ṹ��ָ��
//�������:	
//����ֵ:	���� 0 Ϊ�ɹ�������ʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall WriteSimParam(HANDLE hScanner, SimParam * pParam);

//��ȡ��д��������������
apiReturn _stdcall ReadBasicParam(HANDLE hScanner, ReaderBasicParam * pParam);

//���ö�д��������������
apiReturn _stdcall WriteBasicParam(HANDLE hScanner, ReaderBasicParam * pParam);

//��ȡ��д���Զ���������
apiReturn _stdcall ReadAutoParam(HANDLE hScanner, ReaderAutoParam * pParam);

//���ö�д���Զ���������
apiReturn _stdcall WriteAutoParam(HANDLE hScanner, ReaderAutoParam * pParam);

//���ó���������
apiReturn _stdcall WriteFactoryParam(HANDLE hScanner, SimParam * pParam);

//�ָ���д����������
apiReturn _stdcall ReadFactoryParameter(HANDLE hScanner);

//��ö�д������Ƶ�ʷ�Χ
apiReturn _stdcall GetFrequencyRange(HANDLE hScanner, BYTE *Frequency);

//��ö�д��ID
apiReturn _stdcall GetReaderID(HANDLE hScanner, BYTE *ReaderID);

//����ʱ��
apiReturn _stdcall SetReaderTime(HANDLE hScanner, ReaderDate time);

//���ʱ��
apiReturn _stdcall GetReaderTime(HANDLE hScanner, ReaderDate *time);

//���ñ�ǩ������
apiReturn _stdcall SetReportFilter(HANDLE hScanner, int ptr, int len, BYTE *mask);

//��ñ�ǩ������
apiReturn _stdcall GetReportFilter(HANDLE hScanner, int *ptr, int *len, BYTE *mask);

//////////////////////////////////////////////////////////////////////////
//��;:		��ȡʱ��εļ�¼����
//������:	VH_GetRecordNum
//����:		ȡ��¼����
//�������:	hScanner ͨ�ž��
//			stime Ϊ��ʼʱ�䣬etime Ϊ����ʱ��
//�������:	nTotal Ϊ��¼����
//����ֵ:	0--�ɹ�������ʧ��
//��ע:		ע�⣺�����ʼʱ��ͽ���ʱ�䶼Ϊ0,��ȡ������ȫ����¼��
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall VH_GetRecordNum(HANDLE hScanner, ReaderDate *stime, ReaderDate *etime, int *nTotal);

//////////////////////////////////////////////////////////////////////////
//��;:		��ȡʱ��εļ�¼
//������:	VH_GetRecord
//����:		ȡ��¼
//�������:	hScanner ͨ�ž��
//			stime Ϊ��ʼʱ�䣬etime Ϊ����ʱ��
//�������:	nTotal Ϊ��¼����, nDiNum Ϊ�ڼ�������0��ʼ��, data ָ��¼ָ��
//����ֵ:	0--�ɹ�������ʧ��
//��ע:		ע�⣺�����ʼʱ��ͽ���ʱ�䶼Ϊ0,��ȡ������ȫ����¼��
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall VH_GetRecord(HANDLE hScanner, ReaderDate *stime, ReaderDate *etime, int *nTotal, int *nDiNum, BYTE * data);

//��ü�¼
apiReturn _stdcall GetRecord(HANDLE hScanner, ReaderDate *stime, ReaderDate *etime, int *nTotal, int *taglen, BYTE * data);

//ɾ��ȫ����¼
apiReturn _stdcall DeleteAllRecord(HANDLE hScanner);

//���ö�д��ID
apiReturn _stdcall SetHandsetID(HANDLE hScanner, BYTE *HandsetID);

//��ö�д��ID
apiReturn _stdcall GetHandsetID(HANDLE hScanner, BYTE *HandsetID);

//����Ӳ���汾
apiReturn _stdcall SetHardVersion(HANDLE hScanner, int wHardVer,int wHardVer2);

//��������������
apiReturn _stdcall SetBtBaudRate(HANDLE hScanner, BYTE nBaudRate);

//��ȡ����������
apiReturn _stdcall GetBtBaudRate(HANDLE hScanner, BYTE *nBaudRate);

//�����������
apiReturn _stdcall SetBluetoothName(HANDLE hScanner,int nLen, BYTE *BluetoothName);

//������������
apiReturn _stdcall GetBluetoothName(HANDLE hScanner, BYTE *BluetoothName);

//�����ֻ������д��ģʽ����ģ���Դ�򿪣�1--�򿪣�0--�ر�
apiReturn _stdcall SetReaderMode(HANDLE hScanner, BYTE nMode);

//��ʾ��Ϣ
CString _stdcall ShowInfo();






//==============================���ں�������==============================
//���Ӷ�д��
apiReturn _stdcall Net_ConnectScanner(SOCKET *hSocket,char *nTargetAddress,UINT nTargetPort,char *nHostAddress,UINT nHostPort);

//�Ͽ�����
apiReturn _stdcall Net_DisconnectScanner();


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

//����������,0--stop, 1--start
apiReturn _stdcall BuzzerAlarm(HANDLE hScanner,int iAlarm);

//����ͨ�ŷ���������,0--stop, 1--start
apiReturn _stdcall Net_BuzzerAlarm(SOCKET hSocket, int iAlarm);

//////////////////////////////////////////////////////////////////////////
//��;:		���������־�ļ�
//������:	VH_SetLogFile
//����:		����־����д�뵽ָ���ļ���
//�������:	FileName ָȫ·����
//�������:	��
//����ֵ:	����0Ϊ�ɹ�������-1Ϊʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
BOOL _stdcall VH_SetLogFile(char* FileName);


//////////////////////////////////////////////////////////////////////////
//��;:		д��־
//������:	VH_WriteAppLogFile
//����:		����־����д�뵽ָ���ļ���
//�������:	FileName ָȫ·����
//			Line ָ��ǰ�кţ������ݲ�ʹ��
//			fmt ָ��ʽ�����㶮��
//�������:	��
//����ֵ:	����0Ϊ�ɹ�������-1Ϊʧ��
//��ע:
//////////////////////////////////////////////////////////////////////////
int _stdcall VH_WriteAppLogFile(char* FileName, int Line, char* fmt, ...);


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

//AscתBcd
void _stdcall Asc2Bcd(char *bcd, char *asc, int len);
//////////////////////////////////////////////////////////////////////////
#endif	//end of 
