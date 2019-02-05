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
//add by martrin 20140616增加ARM9的时间格式,原来是6字节，现在变成7字节
//#define					ENABLE_ARM9_MODEL

//#####################################################################


//////////////////////////////////////////////////////////////////////////
extern "C" int  WQ_Sum(int a, int b);//test

#if 1
//==============================数据类型定义==============================
typedef int apiReturn;   // 函数返回值类型
//////////////////////////////////////////////////////////////////////////
#define WM_ADDLIST (WM_USER+100)
//////////////////////////////////////////////////////////////////////////

//==============================常量定义==============================
#define	ID_MAX_SIZE_64BIT	8		//电子标签的ID号为64bit
#define	ID_ATA_MAX_SIZE		20		//ATA电子标签的ID号为20byte
#define ID_MAX_SIZE_96BIT	65		//电子标签的ID号
#define MAX_LABELS			255		// 一次读写操作最多不超过100个标签

//==============================API函数返回码==============================
#define	_OK					0x00	// 操作成功

//通信方面出错信息
#define _init_rs232_err		0x81	//  通信口初始化失败
#define _no_scanner			0x82	//  找不到读写器
#define _comm_error         0x83	//  收发通信数据出错
#define _baudrate_error     0x84	//  设置波特率出错
#define _init_net_error		0x85	//  网口初始化失败
#define _net_error          0x86	//  网口收发通信数据出错

// 读写器返回出错信息
#define _no_antenna			0x01   //天线连接失败
#define _no_label			0x02   //未检测到标签
#define _invalid_label		0x03   //非法标签
#define _less_power			0x04   //读写功率不够
#define _write_prot_error	0x05   //该区写保护
#define _check_sum_error	0x06   //校验和错误
#define _parameter_error	0x07   //参数错误
#define _memory_error		0x08   //数据区不存在
#define _password_error		0x09   //密码不正确
#define _killpassword_error	0x0a   //G2标签毁灭密码为全零
#define _nonlicet_command	0x0b   //非法命令
#define _nonlicet_user		0x0c   //密码不匹配的非法用户
#define _invalid_command	0x1e   //表示无效指令，如参数不正确的指令
#define _other_error		0x1f   //未知命令

//函数输入错误
#define _no_cardID_input   0x20   //其它错误

typedef struct tagReaderDate
{
	BYTE	Year;			//年
	#if defined (ENABLE_ARM9_MODEL)
	BYTE	Yeam;			//年
	#endif
	BYTE	Month;			//月
	BYTE	Day;			//日
	BYTE	Hour;			//时
	BYTE	Minute;			//分
	BYTE	Second;			//秒
}ReaderDate;

typedef struct tagReaderBasicParam
{
	BYTE	BaudRate;			//(1)串口的通信速率，取值：00H~08H，代表速率同"设定波特率"命令。
	BYTE	Power;				//(2)发射功率值，取值：20~30dBm。(0-63)
	BYTE	Min_Frequence;		//(3)发射微波信号频率的起始点，取值： 1~63。
	BYTE	Max_Frequence;		//(4)发射微波信号频率的终止点，取值： 1~63。
	BYTE	Reserve5;			//(5)保留,后来改为调制深度
	BYTE	WorkMode;			//(6)读写器工作方式：0-主动方式，1-命令方式
	BYTE	ReaderAddress;		//(7)RS485地址:0--255
	BYTE	NumofCard;			//(8)最多读卡数目。
	BYTE	TagType;			//(9)标签种类：01H－ISO18000-6B，02H－EPCC1，04H－EPCC1G2，08H－EM4442。
	BYTE	ReadDuration;		//(10)读卡持续时间：射频发射持续时间，只针对EM标签有效；0－10ms，1－20ms，2－30ms，3－40ms。
	BYTE	ReadTimes;			//(11)读卡次数M：收到上位机读卡命令，读写器执行M次此命令。
	BYTE	EnableBuzzer;		//(12)1:使能蜂鸣器0:不使能蜂鸣器
	BYTE	IP1;			    //(13)读写器IP地址
	BYTE	IP2;			    //(14)
	BYTE	IP3;			    //(15)
	BYTE	IP4;			    //(16)
	BYTE	Port1;				//(17)读写器端口高位
	BYTE	Port2;				//(18)
	BYTE	Mask1;				//(19)读写器掩码1
	BYTE	Mask2;				//(20)读写器掩码2
	BYTE	Mask3;				//(21)读写器掩码3
	BYTE	Mask4;				//(22)读写器掩码4
	BYTE	Gateway1;			//(23)读写器地址网关
	BYTE	Gateway2;			//(24)
	BYTE	Gateway3;			//(25)
	BYTE	Gateway4;			//(26)
	BYTE	MAC1;			    //(27)读写器MAC地址
	BYTE	MAC2;			    //(28)
	BYTE	MAC3;			    //(29)
	BYTE	MAC4;			    //(30)
	BYTE	MAC5;			    //(31)
	BYTE	MAC6;			    //(32)
	#if defined (ENABLE_ARM9_MODEL)
	BYTE	AutoParam[32];
	#endif

} ReaderBasicParam;

//读写器主动工作参数
typedef struct tagReaderAutoParam
{
	BYTE	AutoMode;			//(1)读标签模式：0-定时方式，1-触发方式。
	BYTE	TimeH;				//(2)标签保留时间：单位：秒s。缺省值为1。
	BYTE	TimeL;				//(3)
	BYTE	Interval;			//(4)0-10ms，1-20ms，2-30ms，3-50ms，4-100ms。缺省值为2。每隔设定时间主动读取一次标签。
	BYTE	NumH;				//(5)标签保留数目：缺省值为1。已读取的标签ID在读写器内存中保留的数目。
	BYTE	NumL;				//(6)
	BYTE	OutputManner;	    //(7)数据输出格式：0-简化格式，1-标准格式，2-XML格式。缺省值为0。
	BYTE	OutInterface;		//(8)输出接口：0－RS232口，1－RS485口，2－RJ45口。缺省值为0。 3- Wiegand26    4- Wiegand34
	BYTE	WiegandWidth;		//(9)Weigand脉冲宽度值。
	BYTE	WiegandInterval;	//(10)Weigand脉冲间隔值。
	BYTE	ID_Start;			//(11)输出卡号的起始位，取值0～4。
	BYTE    IDPosition;			//(12)卡号在电子标签上的存放地址。
	BYTE	Report_Interval;	//(13)通知间隔：单位秒s。缺省值为1。每隔设定时间主动通知上位机一次。
	BYTE	Report_Condition;	//(14)通知条件：缺省值为1。0-被动通知，1-定时通知，2-增加新标签，3-减少标签，4-标签数变化	
	BYTE	Report_Output;		//(15)通知输出端
	BYTE	Antenna;			//(16)天线选择。1-ant1,2-ant2,4-ant4,8-ant8
	BYTE	TriggerMode;	    //(17)触发方式(缺省值为0): 0-低电平 1-高电平
	BYTE	HostIP1;			//(18)被通知IP地址
	BYTE	HostIP2;			//(19)
	BYTE	HostIP3;			//(20)
	BYTE	HostIP4;			//(21)
	BYTE	Port1;				//(22)被通知端口
	BYTE	Port2;				//(23)
	BYTE	Reserve24;			//(24)被通知MAC,mofi by mqs 20121207 保留
	BYTE	ArgentinaSim;		//(25)//仿真模式(阿根廷),0--非仿真，1--仿真
	BYTE	CardTime1;			//(26)//读卡总超时1
	BYTE	CardTime2;			//(27)//读卡总超时2
	BYTE	ArgentinaMode;		//(28)//阿根的五种模式,0---Only ATA  只读ATA;1---Only EPC 只读EPC;2---Only EPC & TID 只读EPC+TID;3---ATA + EPC   读ATA+EPC;4---ATA + EPC & TID读ATA+EPC&TID
	BYTE	AnSleepTime;		//(29)//天线睡眠时间，单位：ms,(1-255)
	BYTE	Alarm;				//(30)0-不报警，1-报警。在定时和触发方式下是否检测报警。
	BYTE	Reserve31;		    //(31)标准输出时间间隔，缺省值为120秒，1～255。
	BYTE	EnableRelay;		//(32)自动工作模式是否控制继电器1:控制 0:不控制
} ReaderAutoParam;

typedef struct tagReaderDebugState
{
	BYTE	Test;				//0－工作状态；1－调试状态。
	BYTE	Reserve2;			//保留
	BYTE	Reserve3;			//保留
	BYTE	Reserve4;			//保留
} ReaderDebugState;


typedef struct _tagReaderFreq
{
	char *chFreq;		//国家频率字符串

	int	iGrade;			//级数 = 50;
	int iSkip;			//步进 = 500KHz;
	int dwFreq;			//起始频率 = 902750;
						//公式：902750 + 级数*步进
}tagReaderFreq;

//关于各个国家的频率
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

//关于各个国家的频率
static const tagReaderFreq stuctFreqCountryT[]=
{
	{"01---FCC(American)", 63, 400, 902600},							//(0),{"00---FCC(American)", 50, 500, 902750},
	{"02---ETSI", 11, 200, 865500},										//(1),{"01---ETSI EN 300-220(Europe300-220)", -1, -1, -1},
	{"03---CHN", 4, 600, 865700},										//(2)
	{"04---Custom", 10, 500, 920250},									//(3)
	
};

//接收扫描到的IP
typedef void (WINAPI *OnWqReceiveData)(LPCSTR ReaderIP1, LPCSTR ReaderIP2, LPCSTR ReaderIP3, LPCSTR ReaderIP4, LPCSTR Port);


//自动模式扫描的数据回传
//dwSize 为接收数据的字符的个数
typedef void (WINAPI *OnCallbackAutoReceiveData)(DWORD dwSize);

void _stdcall DeleteAppHwnd();
//////////////////////////////////////////////////////////////////////////
void _stdcall SetAppHwnd(HWND hWnd);

//==============================函数定义==============================

//连接读写器
apiReturn _stdcall ConnectScanner(HANDLE *hScanner, char *szPort, int *nBaudRate);

//断开连接
apiReturn _stdcall DisconnectScanner(HANDLE hScanner);

//==============================设备控制命令==============================
//设置波特率
apiReturn _stdcall SetBaudRate(HANDLE hScanner, int nBaudRate,int Address);

//读取版本号
apiReturn _stdcall GetReaderVersion(HANDLE hScanner, WORD *wHardVer, WORD  *wSoftVer,int Address);

//设置读写器继电器状态
apiReturn _stdcall SetRelay(HANDLE hScanner, int Relay,int Address);

//设定输出功率
apiReturn _stdcall SetOutputPower(HANDLE hScanner, int nPower1,int Address);

//设定工作频率
apiReturn _stdcall SetFrequency(HANDLE hScanner, int Min_Frequency, int Max_Frequency,int Address);

//获得读写器工作频率范围
apiReturn _stdcall GetFrequencyRange(HANDLE hScanner, BYTE *Frequency,int Address);

//设定工作频率(针对R2000模块专有)
apiReturn _stdcall SetFrequencyEx(HANDLE hScanner, BYTE *Frequency,int Address);

//////////////////////////////////////////////////////////////////////////
//用途:		设定工作频率(针对5F模块专有)	
//函数名:	SetFrequencyEx5F
//功能:		hScanner 为句柄;Address 为RS485地址(1-254)，0则为RS232
//输入参数:	Frequency 为取得数据,
//输出参数:	无
//返回值:	返回AK_TRUE为初始化成功，否则AK_FALSE为初始化失败
//备注:
//例如:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall SetFrequencyEx5F(HANDLE hScanner, BYTE *Frequency,int Address);

//获得读写器工作频率范围(针对R2000模块专有)
apiReturn _stdcall GetFrequencyRangeEx(HANDLE hScanner, BYTE *Frequency,int Address);

//获取读写器基本工作参数
apiReturn _stdcall ReadBasicParam(HANDLE hScanner, ReaderBasicParam * pParam,int Address);

//设置读写器基本工作参数
apiReturn _stdcall WriteBasicParam(HANDLE hScanner, ReaderBasicParam * pParam,int Address);

//获取读写器自动工作参数
apiReturn _stdcall ReadAutoParam(HANDLE hScanner, ReaderAutoParam * pParam,int Address);

//设置读写器自动工作参数
apiReturn _stdcall WriteAutoParam(HANDLE hScanner, ReaderAutoParam * pParam,int Address);

//设置调制度
apiReturn _stdcall SetModDepth(HANDLE hScanner, int ModDepth,int Address);

//获得调制度
apiReturn _stdcall GetModDepth(HANDLE hScanner, int *ModDepth,int Address);

//恢复读写器出厂参数
apiReturn _stdcall ReadFactoryParameter(HANDLE hScanner,int Address);

//选择天线
apiReturn _stdcall SetAntenna(HANDLE hScanner, int Antenna,int Address);

//复位读写器
apiReturn _stdcall Reboot(HANDLE hScanner,int Address);

//启动/停止读写器自动模式
apiReturn _stdcall AutoMode(HANDLE hScanner,int Mode,int Address);

//ATA检测读取ID标签
apiReturn _stdcall ATA_ListTagID(HANDLE hScanner, BYTE *btID, int *nCounter,int Address);

//清除内存
apiReturn _stdcall ClearTagMemory(HANDLE hScanner,int Address);

//设置时间
apiReturn _stdcall SetReaderTime(HANDLE hScanner, ReaderDate *time,int Address);

//获得时间
apiReturn _stdcall GetReaderTime(HANDLE hScanner, ReaderDate *time,int Address);

//设置标签过滤器
apiReturn _stdcall SetReportFilter(HANDLE hScanner, int ptr, int len, BYTE *mask,int Address);

//获得标签过滤器
apiReturn _stdcall GetReportFilter(HANDLE hScanner, int *ptr, int *len, BYTE *mask,int Address);

//增加名单
apiReturn _stdcall AddLableID(HANDLE hScanner, int listlen, int datalen, BYTE * data);

//删除名单
apiReturn _stdcall DelLableID(HANDLE hScanner, int listlen, int datalen, BYTE * data);

//获得名单
apiReturn _stdcall GetLableID(HANDLE hScanner, int startaddr, int listlen, int *relistlen, int *taglen, BYTE * data);

//获得记录
apiReturn _stdcall GetRecord(HANDLE hScanner, ReaderDate *stime, ReaderDate *etime, int startaddr, int listlen, int *relistlen, int *taglen, BYTE * data);

//删除全部记录
apiReturn _stdcall DeleteAllRecord(HANDLE hScanner);

//立即通知
apiReturn _stdcall ReportNow(HANDLE hScanner,int Address);

//获得标签记录
apiReturn _stdcall GetTagInfo(HANDLE hScanner, int straddr, BYTE Counter, BYTE* len, BYTE* Data,int Address);

//获得读写器ID
apiReturn _stdcall SetReaderID(HANDLE hScanner, BYTE *ReaderID,int Address);

//获得读写器ID
apiReturn _stdcall GetReaderID(HANDLE hScanner, BYTE *ReaderID,int Address);

//获得读写器内部模块的版本,add by mqs 20130320
apiReturn _stdcall GetModuleVer(HANDLE hScanner, BYTE *bModuleVer,int Address);

//==============================网络命令==============================
//设置读写器IP地址
apiReturn _stdcall SetReaderNetwork(HANDLE hScanner, BYTE IP_Address[4], int Port, BYTE Mask[4], BYTE Gateway[4],int Address);

//获得读写器IP地址
apiReturn _stdcall GetReaderNetwork(HANDLE hScanner, BYTE *IP_Address, int *Port, BYTE *Mask, BYTE *Gateway,int Address);

//设置读写器MAC地址
apiReturn _stdcall SetReaderMAC(HANDLE hScanner, BYTE MAC[6],int Address);

//获得读写器MAC地址
apiReturn _stdcall GetReaderMAC(HANDLE hScanner, BYTE *MAC,int Address);
//==============================IO命令==============================
//设置读写器继电器状态
apiReturn _stdcall SetRelay(HANDLE hScanner, int relay,int Address);

//获得读写器继电器状态
apiReturn _stdcall GetRelay(HANDLE hScanner, int *relay,int Address);

//==============================ISO-6B数据读写命令==============================
//检测标签存在
apiReturn _stdcall ISO6B_LabelPresent(HANDLE hScanner, int *nCounter,int Address);

//读取ISO6B标签ID号
apiReturn _stdcall ISO6B_ReadLabelID(HANDLE hScanner, BYTE *IDBuffer, int *nCounter,int Address);

//列出选定标签
apiReturn _stdcall ISO6B_ListSelectedID(HANDLE hScanner, int Cmd, int ptr, BYTE Mask, BYTE *Data, BYTE *IDBuffer, int *nCounter,int Address);

//读一块数据
apiReturn _stdcall ISO6B_ReadByteBlock(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE len,BYTE *Data,int Address);

//一次写4字节数据
apiReturn _stdcall ISO6B_WriteByteBlock(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE len, BYTE *Data,int Address);

//一次写一字节数据
apiReturn _stdcall ISO6B_WriteAByte(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE len, BYTE *Data,int Address);

//写大块数据，字节数超过16
apiReturn _stdcall ISO6B_WriteLongBlock(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE len, BYTE *Data,int Address);

//置写保护状态
apiReturn _stdcall ISO6B_WriteProtect(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr,int Address);

//读写保护状态
apiReturn _stdcall ISO6B_ReadWriteProtect(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE *Protected,int Address);

//全部清除
apiReturn _stdcall ISO6B_ClearMemory(HANDLE hScanner, BYTE CardType, BYTE *IDBuffer,int Address);

//==============================EPC C1G2数据读写命令==============================
//读取EPC1G2标签ID号
apiReturn _stdcall EPC1G2_ReadLabelID(HANDLE hScanner, BYTE mem, int ptr, BYTE len, BYTE *mask, BYTE *IDBuffer, int *nCounter,int Address);

//读一块数据
apiReturn _stdcall EPC1G2_ReadWordBlock(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len, BYTE *Data, BYTE *AccessPassword,int Address);

//写一块数据
apiReturn _stdcall EPC1G2_WriteWordBlock(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len, BYTE *Data, BYTE *AccessPassword,int Address);

//设置读写保护状态
apiReturn _stdcall EPC1G2_SetLock(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE Lock, BYTE *AccessPassword,int Address);

//擦除标签数据
apiReturn _stdcall EPC1G2_EraseBlock(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len,int Address);

//永久休眠标签
apiReturn _stdcall EPC1G2_KillTag(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE *KillPassword,int Address);

//写EPC
apiReturn _stdcall EPC1G2_WriteEPC(HANDLE hScanner, BYTE len, BYTE *Data, BYTE *AccessPassword,int Address);

//块锁命令
apiReturn _stdcall EPC1G2_BlockLock(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE ptr, BYTE *AccessPassword,int Address);

//EAS状态操作命令
apiReturn _stdcall EPC1G2_ChangeEas(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE State, BYTE *AccessPassword,int Address);

//EAS报警命令
apiReturn _stdcall EPC1G2_EasAlarm(HANDLE hScanner,int Address);

//读保护设置
apiReturn _stdcall EPC1G2_ReadProtect(HANDLE hScanner,BYTE *AccessPassword, BYTE EPC_WORD, BYTE *IDBuffer,int Address);

//复位读保护设置
apiReturn _stdcall EPC1G2_RStreadProtect(HANDLE hScanner, BYTE *AccessPassword,int Address);

//设置用户区数据块读保护
apiReturn _stdcall EPC1G2_BlockReadLock(HANDLE hScanner, BYTE EPC_WORD, BYTE *IDBuffer, BYTE Lock, BYTE *AccessPassword,int Address);

//识别EPC同时读数据
apiReturn _stdcall EPC1G2_ReadEPCandData(HANDLE hScanner, BYTE *EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len, BYTE *Data, int Address);

//频谱校验
apiReturn _stdcall EPC1G2_Calibrate(HANDLE hScanner, BYTE *AccessPassword, BYTE Kword);

//侦测标签
apiReturn _stdcall EPC1G2_DetectTag(HANDLE hScanner,int Address);
//==============================TK900数据读写命令==============================
//读取TK900标签ID号
apiReturn _stdcall TK900_ReadLabelID(HANDLE hScanner, BYTE *IDBuffer, int *nCounter,int Address);

//读一块数据
apiReturn _stdcall TK900_ReadPageBlock(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE len,BYTE *Data,int Address);

//写一块数据
apiReturn _stdcall TK900_WritePageBlock(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE *Data,int Address);

//置写保护状态
apiReturn _stdcall TK900_SetProtect(HANDLE hScanner, BYTE *IDBuffer, BYTE ptr, BYTE len,int Address);

//读写保护状态
apiReturn _stdcall TK900_GetProtect(HANDLE hScanner, BYTE *IDBuffer ,BYTE *state,int Address);

//设置标签进入TTO状态
apiReturn _stdcall TK900_SetTTO(HANDLE hScanner, BYTE *IDBuffer ,BYTE ptr, BYTE len,int Address);

//读取TTO标签
apiReturn _stdcall TK900_ListTagPage(HANDLE hScanner, BYTE *IDBuffer ,BYTE *Data,int Address);

//得到TTO标签的开始地址和长度
apiReturn _stdcall TK900_GetTTOStartAdd(HANDLE hScanner, BYTE *IDBuffer ,BYTE *len,int Address);

//==============================网口函数定义==============================
//连接读写器
apiReturn _stdcall Net_ConnectScanner(SOCKET *hSocket,char *nTargetAddress,UINT nTargetPort,char *nHostAddress,UINT nHostPort);

//断开连接
apiReturn _stdcall Net_DisconnectScanner();
apiReturn _stdcall Net_DisconnectScannerEx(SOCKET sSocket);

//==============================设备控制命令==============================
//设置波特率
apiReturn _stdcall Net_SetBaudRate(SOCKET hSocket, int nBaudRate);

//读取版本号
apiReturn _stdcall Net_GetReaderVersion(SOCKET hSocket, WORD *wHardVer, WORD  *wSoftVer);

//设定输出功率
apiReturn _stdcall Net_SetOutputPower(SOCKET hSocket, int nPower);

//设定工作频率
apiReturn _stdcall Net_SetFrequency(SOCKET hSocket, int Min_Frequency, int Max_Frequency);

//获得读写器工作频率范围
apiReturn _stdcall Net_GetFrequencyRange(SOCKET hSocket, BYTE *Frequency);

//设定工作频率(针对R2000模块专有)
apiReturn _stdcall Net_SetFrequencyEx(SOCKET hSocket, BYTE *Frequency);

//获得读写器工作频率范围(针对R2000模块专有)
apiReturn _stdcall Net_GetFrequencyRangeEx(SOCKET hSocket, BYTE *Frequency);

//读取读写器基本工作参数
apiReturn _stdcall Net_ReadBasicParam(SOCKET hSocket, ReaderBasicParam *pParam);

//设置读写器基本工作参数
apiReturn _stdcall Net_WriteBasicParam(SOCKET hSocket, ReaderBasicParam *pParam);

//读取读写器自动工作参数
apiReturn _stdcall Net_ReadAutoParam(SOCKET hSocket, ReaderAutoParam *pParam);

//设置读写器自动工作参数
apiReturn _stdcall Net_WriteAutoParam(SOCKET hSocket, ReaderAutoParam *pParam);

//设置调制度
apiReturn _stdcall Net_SetModDepth(SOCKET hSocket, int ModDepth);

//获得调制度
apiReturn _stdcall Net_GetModDepth(SOCKET hSocket, int *ModDepth);

//选择天线
apiReturn _stdcall Net_SetAntenna(SOCKET hSocket, int Antenna);

//恢复读写器出厂参数
apiReturn _stdcall Net_ReadFactoryParameter(SOCKET hSocket);

//复位读写器
apiReturn _stdcall Net_Reboot(SOCKET hSocket);

//停止/启动读写器自动模式
apiReturn _stdcall Net_AutoMode(SOCKET hSocket,int Mode);

//ATA检测读取ID标签
apiReturn _stdcall Net_ATA_ListTagID(SOCKET hSocket, BYTE *btID, int *nCounter);

//清除内存
apiReturn _stdcall Net_ClearTagMemory(SOCKET hSocket);

//设置时间
apiReturn _stdcall Net_SetReaderTime(SOCKET hSocket, ReaderDate *time);

//获得时间
apiReturn _stdcall Net_GetReaderTime(SOCKET hSocket, ReaderDate *time);

//设置标签过滤器
apiReturn _stdcall Net_SetReportFilter(SOCKET hSocket, int ptr, int len, BYTE *mask);

//获得标签过滤器
apiReturn _stdcall Net_GetReportFilter(SOCKET hSocket, int *ptr, int *len, BYTE *mask);

//增加名单
apiReturn _stdcall Net_AddLableID(SOCKET hSocket, int listlen, int datalen, BYTE * data);

//删除名单
apiReturn _stdcall Net_DelLableID(SOCKET hSocket, int listlen, int datalen, BYTE * data);

//获得名单
apiReturn _stdcall Net_GetLableID(SOCKET hSocket, int startaddr, int listlen, int *relistlen, int *taglen, BYTE * data);

//获得记录
apiReturn _stdcall Net_GetRecord(SOCKET hSocket, ReaderDate *stime, ReaderDate *etime, int startaddr, int listlen, int *relistlen, int *taglen, BYTE * data);

//删除全部记录
apiReturn _stdcall Net_DeleteAllRecord(SOCKET hSocket);

//立即通知
apiReturn _stdcall Net_ReportNow(SOCKET hSocket);

//获得标签记录
apiReturn _stdcall Net_GetTagInfo(SOCKET hSocket, int straddr, BYTE Counter, BYTE* len, BYTE* Data);

//设置读写器ID
apiReturn _stdcall Net_SetReaderID(SOCKET hSocket, BYTE *ReaderID);

//获得读写器ID
apiReturn _stdcall Net_GetReaderID(SOCKET hSocket, BYTE *ReaderID);

//获得读写器内部模块的版本,add by mqs 20130320
apiReturn _stdcall Net_GetModuleVer(SOCKET hSocket, BYTE *bModuleVer);

//==============================网络命令==============================
//设置读写器IP地址
apiReturn _stdcall Net_SetReaderNetwork(SOCKET hSocket, BYTE IP_Address[4], int Port, BYTE Mask[4], BYTE Gateway[4]);

//获得读写器IP地址
apiReturn _stdcall Net_GetReaderNetwork(SOCKET hSocket, BYTE *IP_Address, int *Port, BYTE *Mask, BYTE *Gateway);

//设置读写器MAC地址
apiReturn _stdcall Net_SetReaderMAC(SOCKET hSocket, BYTE MAC[6]);

//获得读写器MAC地址
apiReturn _stdcall Net_GetReaderMAC(SOCKET hSocket, BYTE *MAC);

//==============================IO命令==============================
//设置读写器继电器状态
apiReturn _stdcall Net_SetRelay(SOCKET hSocket, int relay);

//获得读写器继电器状态
apiReturn _stdcall Net_GetRelay(SOCKET hSocket, int *relay);

//==============================ISO-6B数据读写命令==============================
//检测标签存在
apiReturn _stdcall Net_ISO6B_LabelPresent(SOCKET hSocket, int *nCounter);

//读取ISO6B标签ID号
apiReturn _stdcall Net_ISO6B_ReadLabelID(SOCKET hSocket, BYTE *IDBuffer, int *nCounter);

//列出选定标签
apiReturn _stdcall Net_ISO6B_ListSelectedID(SOCKET hSocket, int Cmd, int ptr, BYTE Mask, BYTE *Data, BYTE *IDBuffer, int *nCounter);

//读一块数据
apiReturn _stdcall Net_ISO6B_ReadByteBlock(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr, BYTE len,BYTE *Data);

//一次写4字节数据
apiReturn _stdcall Net_ISO6B_WriteByteBlock(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr, BYTE len, BYTE *Data);

//一次写一字节数据
apiReturn _stdcall Net_ISO6B_WriteAByte(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr, BYTE len, BYTE *Data);

//置写保护状态
apiReturn _stdcall Net_ISO6B_WriteProtect(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr);

//读写保护状态
apiReturn _stdcall Net_ISO6B_ReadWriteProtect(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr, BYTE *Protected);

//==============================EPC C1G2数据读写命令==============================
//读取EPC1G2标签ID号
apiReturn _stdcall Net_EPC1G2_ReadLabelID(SOCKET hSocket, BYTE mem, int ptr, BYTE len, BYTE *mask, BYTE *IDBuffer, int *nCounter);

//读一块数据
apiReturn _stdcall Net_EPC1G2_ReadWordBlock(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len, BYTE *Data, BYTE *AccessPassword);

//写一块数据
apiReturn _stdcall Net_EPC1G2_WriteWordBlock(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len, BYTE *Data, BYTE *AccessPassword);

//设置读写保护状态
apiReturn _stdcall Net_EPC1G2_SetLock(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE Lock, BYTE *AccessPassword);

//擦除标签数据
apiReturn _stdcall Net_EPC1G2_EraseBlock(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len);

//永久休眠标签
apiReturn _stdcall Net_EPC1G2_KillTag(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE *KillPassword);

//写EPC
apiReturn _stdcall Net_EPC1G2_WriteEPC(SOCKET hSocket,BYTE len, BYTE *Data, BYTE *AccessPassword);

//块锁命令
apiReturn _stdcall Net_EPC1G2_BlockLock(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE ptr, BYTE *AccessPassword);

//EAS状态操作命令
apiReturn _stdcall Net_EPC1G2_ChangeEas(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE State, BYTE *AccessPassword);

//EAS报警命令
apiReturn _stdcall Net_EPC1G2_EasAlarm(SOCKET hSocket);

//读保护设置
apiReturn _stdcall Net_EPC1G2_ReadProtect(SOCKET hSocket,BYTE *AccessPassword, BYTE EPC_WORD, BYTE *IDBuffer);

//复位读保护设置
apiReturn _stdcall Net_EPC1G2_RStreadProtect(SOCKET hSocket, BYTE *AccessPassword);

//识别EPC同时读数据
apiReturn _stdcall Net_EPC1G2_ReadEPCandData(SOCKET hSocket, BYTE *EPC_WORD, BYTE *IDBuffer, BYTE mem, BYTE ptr, BYTE len, BYTE *Data, int Address);

//设置用户区数据块读保护
apiReturn _stdcall Net_EPC1G2_BlockReadLock(SOCKET hSocket, BYTE EPC_WORD, BYTE *IDBuffer, BYTE Lock, BYTE *AccessPassword);

//侦测标签
apiReturn _stdcall Net_EPC1G2_DetectTag(SOCKET hSocket);

//==============================TK900数据读写命令==============================
//读取TK900标签ID号
apiReturn _stdcall Net_TK900_ReadLabelID(SOCKET hSocket, BYTE *IDBuffer, int *nCounter);

//读一块数据
apiReturn _stdcall Net_TK900_ReadPageBlock(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr, BYTE len,BYTE *Data);

//写一块数据
apiReturn _stdcall Net_TK900_WritePageBlock(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr, BYTE *Data);

//置写保护状态
apiReturn _stdcall Net_TK900_SetProtect(SOCKET hSocket, BYTE *IDBuffer, BYTE ptr, BYTE len);

//读写保护状态
apiReturn _stdcall Net_TK900_GetProtect(SOCKET hSocket, BYTE *IDBuffer ,BYTE *state);

//设置标签进入TTO状态
apiReturn _stdcall Net_TK900_SetTTO(SOCKET hSocket, BYTE *IDBuffer ,BYTE ptr, BYTE len);

//读取TTO标签
apiReturn _stdcall Net_TK900_ListTagPage(SOCKET hSocket, BYTE *IDBuffer ,BYTE *Data);

//得到TTO标签的开始地址和长度
apiReturn _stdcall Net_TK900_GetTTOStartAdd(SOCKET hSocket, BYTE *IDBuffer ,BYTE *len);


////////////////////////////////////////////////////////////////////////////////

//修改读写器频率范围
apiReturn _stdcall ChangeFrequency(HANDLE hScanner, BYTE fre,int Address);

//修改读写器频率范围
apiReturn _stdcall Net_ChangeFrequency(SOCKET hSocket, BYTE fre);

//设置硬件版本
apiReturn _stdcall SetHardVersion(HANDLE hScanner, int wHardVer,int wHardVer2,int Address);

//修改读写器硬件版本号
apiReturn _stdcall Net_SetHardVersion(SOCKET hSocket, int wHardVer,int wHardVer2);

//设置读写器出厂基本工作参数
apiReturn _stdcall WriteFactoryBasicParam(HANDLE hScanner, ReaderBasicParam * pParam,int Address);

//设置读写器出厂自动工作参数
apiReturn _stdcall WriteFactoryAutoParam(HANDLE hScanner, ReaderAutoParam * pParam,int Address);

//设置读写器基本工作参数
apiReturn _stdcall Net_WriteFactoryBasicParam(SOCKET hSocket, ReaderBasicParam *pParam);

//设置读写器自动工作参数
apiReturn _stdcall Net_WriteFactoryAutoParam(SOCKET hSocket, ReaderAutoParam *pParam);

//连接读写器
apiReturn _stdcall ConnectScanner485(HANDLE *hScanner, char *szPort, int nBaudRate,int Address);

//读取读写器的系统状态,dwData可能如:0x00000200值
apiReturn _stdcall GetSystemState(HANDLE hScanner, DWORD *dwData, int Address);

//读取读写器的系统状态,dwData可能如:0x00000200值
apiReturn _stdcall Net_GetSystemState(SOCKET hSocket, DWORD *dwData);

//读取读写器的打印模式,dwData可能如:0x00000200值
apiReturn _stdcall GetPrintInfo(HANDLE hScanner, DWORD *dwData, int Address);

//读取读写器的打印模式,dwData可能如:0x00000200值
apiReturn _stdcall Net_GetPrintInfo(SOCKET hSocket, DWORD *dwData);

//设置读写器的打印模式,dwData可能如:0x00000200值
apiReturn _stdcall SetPrintInfo(HANDLE hScanner, DWORD dwData, int Address);

//设置读写器的打印模式,dwData可能如:0x00000200值
apiReturn _stdcall Net_SetPrintInfo(SOCKET hSocket, DWORD dwData);

//dwTimeout 为发命令后没反映的超时时间
typedef void (WINAPI *OnCallbackTimeOutFunc)(DWORD dwTimeout);
//设置超时时间
apiReturn _stdcall WE_SetCommunicationTimeout(DWORD dwTimeout, OnCallbackTimeOutFunc fFunc);

//////////////////////////////////////////////////////////////////////////
//用途:		取得扫描到的IP
//函数名:	WE_GetScanReaderIP
//功能:		将读写器IP读出来
//输入参数:	无
//输出参数:	ReaderIP1 为读写器IP1, ReaderIP2 为读写器IP2, ReaderIP3 为读写器IP3, ReaderIP4 为读写器IP4
//			Port 指端口 如"192","168","0","100","1969"--->IP:192.168.0.100 1969
//返回值:	返回 0 为成功，其它失败
//备注:		外部接口
//////////////////////////////////////////////////////////////////////////
BOOL _stdcall WE_GetScanReaderIP(LPSTR ReaderIP1, LPSTR ReaderIP2, LPSTR ReaderIP3, LPSTR ReaderIP4, LPSTR Port);

//////////////////////////////////////////////////////////////////////////
//用途:		设IP和端口
//函数名:	WE_SetAddrIpPort
//功能:		读写器自动工作时所用的IP和端口
//输入参数:	lpAddr 为IP地址，如：192.168.0.71 dwPort 为其端口:如5001
//输出参数:	
//返回值:	返回 0 为成功，否则失败
//备注:
//例如:		
//////////////////////////////////////////////////////////////////////////
BOOL _stdcall WE_SetAddrIpPort(LPSTR lpAddr, DWORD dwPort);

//////////////////////////////////////////////////////////////////////////
//用途:		主动模式扫描记录初始化	
//函数名:	WE_StartScanAutoRecord
//功能:		读写器自动工作时读取记录开始初始化
//输入参数:	lpData 为通信句柄, dwOpt 指哪种类型通信(1-网口,2-串口,3-RS485) fFunc 为函数指针
//输出参数:	
//返回值:	返回 0 为成功，否则失败
//备注:
//例如:		如函数指针类型:typedef void (WINAPI *OnCallbackAutoReceiveData)(DWORD dwSize)
//////////////////////////////////////////////////////////////////////////
BOOL _stdcall WE_StartScanAutoRecord(LPVOID lpData, DWORD dwOpt, OnCallbackAutoReceiveData fFunc);

//////////////////////////////////////////////////////////////////////////
//用途:		主动模式扫描记录销毁	
//函数名:	WE_StopScanAutoRecord
//功能:		读写器自动工作时读取记录最后清理工作
//输入参数:	无
//输出参数:	无
//返回值:	返回 0 为成功，否则失败
//备注:
//////////////////////////////////////////////////////////////////////////
BOOL _stdcall WE_StopScanAutoRecord();

//////////////////////////////////////////////////////////////////////////
//用途:		取记录	
//函数名:	WE_GetScanAutoRecord
//功能:		读写器自动工作时读取记录
//输入参数:	dwSize 指其大小
//输出参数:	lpGetBuf 存读录的记录
//返回值:	返回 0 为成功，否则失败
//备注:
//////////////////////////////////////////////////////////////////////////
BOOL _stdcall WE_GetScanAutoRecord(LPSTR lpGetBuf, DWORD dwSize);




//////////////////////////////////////////////////////////////////////////
//用途:		组轮询指令	
//函数名:	GetReaderGroupPolling
//功能:		用组轮询
//输入参数:	hScanner 为BPA的句柄,
//输出参数:	lpBuf 为收到的指针，lpSize 为其长度
//返回值:	返回 0 为成功，否则失败
//备注:
//例如:		轮询发指令，见BPA-9-proctol.pdf
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall GetReaderGroupPolling(HANDLE hScanner, BYTE *lpBuf, int *lpSize);


//////////////////////////////////////////////////////////////////////////
//用途:		发轮询指令	
//函数名:	GetReaderBPAEpc
//功能:		取读写器BPA的EPC
//输入参数:	hScanner 为BPA的句柄,
//输出参数:	lpBuf 为收到的指针，lpSize 为其长度
//返回值:	返回 0 为成功，否则失败
//备注:
//例如:		轮询发指令，见BPA-9-proctol.pdf
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall GetReaderBPAEpc(HANDLE hScanner, BYTE *lpBuf, int *lpSize);


//////////////////////////////////////////////////////////////////////////
//用途:		发轮询指令接受	
//函数名:	GetReaderBPAGranted
//功能:		向读写器发接受
//输入参数:	hScanner 为BPA的句柄,
//输出参数:	lpBuf 为收到的指针，lpSize 为其长度
//返回值:	返回 0 为成功，否则失败
//备注:
//例如:		轮询发指令，见BPA-9-proctol.pdf
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall GetReaderBPAGranted(HANDLE hScanner, BYTE *lpBuf, int *lpSize);


//////////////////////////////////////////////////////////////////////////
//用途:		发轮询指令拒绝
//函数名:	GetReaderBPADenied
//功能:		向读写器发拒绝
//输入参数:	hScanner 为BPA的句柄,
//输出参数:	lpBuf 为收到的指针，lpSize 为其长度
//返回值:	返回 0 为成功，否则失败
//备注:
//例如:		轮询发指令，见BPA-9-proctol.pdf
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall GetReaderBPADenied(HANDLE hScanner, BYTE *lpBuf, int *lpSize);


//////////////////////////////////////////////////////////////////////////
//用途:		发时间指令
//函数名:	SetReaderTimeStamp
//功能:		向读写器发时间信息
//输入参数:	hScanner 为BPA的句柄,
//输出参数:	lpBuf 为收到的指针，lpSize 为其长度
//返回值:	返回 0 为成功，否则失败
//备注:
//例如:		轮询发指令，见BPA-9-proctol.pdf
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall SetReaderTimeStamp(HANDLE hScanner, BYTE *lpBuf, int *lpSize);


//////////////////////////////////////////////////////////////////////////
//用途:		连接BPA读写器
//函数名:	ConnectScannerBPA
//功能:		连接读写器
//输入参数:	szPort 指哪个COM口, nBaudRate 为通信速率，因为要求定为9600,暂不起作用
//			Address 为哪个端口，如41 41
//输出参数:	hScanner 为BPA的句柄
//返回值:	返回 0 为成功，否则失败
//备注:
//例如:		详见BPA-9-proctol.pdf
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall ConnectScannerBPA(HANDLE *hScanner, char *szPort, int nBaudRate,int Address);



//////////////////////////////////////////////////////////////////////////
//用途:		取小模块参数
//函数名:	GetReaderSmallModeParam
//功能:		将小模块的参数读出来
//输入参数:	hScanner 为通信句柄,
//输出参数:	lpBuf 为收到的指针，lpSize 为其长度
//返回值:	返回 0 为成功，否则失败
//备注:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall GetReaderSmallModeParam(HANDLE hScanner, BYTE *lpBuf, int *lpSize);


//////////////////////////////////////////////////////////////////////////
//用途:		设置小模块参数
//函数名:	SetReaderSmallModeParam
//功能:		将小模块的参数写入其中
//输入参数:	hScanner 为通信句柄,lpBuf 为发送的指针，lpSize 为其长度
//输出参数:	
//返回值:	返回 0 为成功，否则失败
//备注:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall SetReaderSmallModeParam(HANDLE hScanner, BYTE *lpBuf, int lpSize);







//////////////////////////////////////////////////////////////////////////
//有关垃圾厂处理的非标--Rubbish//////---START/////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//用途:		设置读写器ID参数
//函数名:	RU_SetReaderID
//功能:		将参数写入其中
//输入参数:	hScanner 为通信句柄,ReaderID 为发送的首地址(内容1字节)，Address 为其RS485地址
//输出参数:	
//返回值:	返回 0 为成功，否则失败
//备注:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_SetReaderID(HANDLE hScanner, BYTE *ReaderID, int Address);

//////////////////////////////////////////////////////////////////////////
//用途:		设置读写器ID参数
//函数名:	RU_SetReaderIDNet
//功能:		将参数写入其中
//输入参数:	hSocket 为通信句柄,ReaderID 为发送的首地址(内容1字节)，Address 为其RS485地址
//输出参数:	
//返回值:	返回 0 为成功，否则失败
//备注:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_SetReaderIDNet(SOCKET hSocket, BYTE *ReaderID);

//////////////////////////////////////////////////////////////////////////
//用途:		获取读写器ID参数
//函数名:	RU_GetReaderID
//功能:		取出读写器ID出来
//输入参数:	hScanner 为通信句柄,ReaderID 为发送的首地址(内容1字节)，Address 为其RS485地址
//输出参数:	
//返回值:	返回 0 为成功，否则失败
//备注:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_GetReaderID(HANDLE hScanner, BYTE *ReaderID, int Address);

//////////////////////////////////////////////////////////////////////////
//用途:		获取读写器ID参数
//函数名:	RU_GetReaderIDNet
//功能:		取出读写器ID出来
//输入参数:	hSocket 为通信句柄,ReaderID 为发送的地址指向(1字节)
//输出参数:	
//返回值:	返回 0 为成功，否则失败
//备注:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_GetReaderIDNet(SOCKET hSocket, BYTE *ReaderID);

//////////////////////////////////////////////////////////////////////////
//用途:		设置读写器记录
//函数名:	RU_SetReaderRecord
//功能:		将记录写入其中
//输入参数:	hScanner 为通信句柄,lpSetBuf 为发送的地址指向(1字节ID+6字节时间年月日时分秒)
//			Address 为其RS485地址
//输出参数:	
//返回值:	返回 0 为成功，否则失败
//备注:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_SetReaderRecord(HANDLE hScanner, BYTE *lpSetBuf, int Address);

//////////////////////////////////////////////////////////////////////////
//用途:		设置读写器记录
//函数名:	RU_SetReaderRecordNet
//功能:		将记录写入其中
//输入参数:	hSocket 为通信句柄,lpSetBuf 为发送的地址指向(1字节ID+6字节时间年月日时分秒)
//输出参数:	
//返回值:	返回 0 为成功，否则失败
//备注:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_SetReaderRecordNet(SOCKET hSocket, BYTE *lpSetBuf);

//////////////////////////////////////////////////////////////////////////
//用途:		获取读写器全部信息
//函数名:	RU_GetExportRecord
//功能:		
//输入参数:	hScanner 为通信句柄,lpGetBuf 为发送的地址指向(28字节)，Address 为其RS485地址
//输出参数:	
//返回值:	返回 0 为成功，否则失败
//备注:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_GetExportRecord(HANDLE hScanner, BYTE *lpGetBuf, int Address);

//////////////////////////////////////////////////////////////////////////
//用途:		获取读写器全部信息
//函数名:	RU_GetExportRecordNet
//功能:		
//输入参数:	hSocket 为通信句柄,lpGetBuf 为发送的地址指向(28字节)
//输出参数:	
//返回值:	返回 0 为成功，否则失败
//备注:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_GetExportRecordNet(SOCKET hSocket, BYTE *lpGetBuf);

//////////////////////////////////////////////////////////////////////////
//用途:		删除读写器全部信息
//函数名:	RU_DeleteAllRecord
//功能:		
//输入参数:	hScanner 为通信句柄,Address 为其RS485地址
//输出参数:	
//返回值:	返回 0 为成功，否则失败
//备注:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_DeleteAllRecord(HANDLE hScanner, int Address);

//////////////////////////////////////////////////////////////////////////
//用途:		删除读写器全部信息
//函数名:	RU_DeleteAllRecordNet
//功能:		
//输入参数:	hSocket 为通信句柄
//输出参数:	
//返回值:	返回 0 为成功，否则失败
//备注:
//////////////////////////////////////////////////////////////////////////
apiReturn _stdcall RU_DeleteAllRecordNet(SOCKET hSocket);

//////////////////////////////////////////////////////////////////////////
//有关垃圾厂处理的非标--Rubbish//////---END///////////////////////////////
//////////////////////////////////////////////////////////////////////////












//显示信息
apiReturn _stdcall ShowInfo(char *chStr);

apiReturn _stdcall WriteAppLogFile(char* FileName, int Line, char* fmt, ...);
//////////////////////////////////////////////////////////////////////////
//用途:		16进制转ASC码	
//函数名:	Hex2Asc
//功能:		16进制转ASC码
//输入参数:	inHex 为16进制数
//输出参数:	pOutStr 为ASC码
//返回值:	返回无
//备注:
//例如:		0x12===>'12';
//////////////////////////////////////////////////////////////////////////
void _stdcall Hex2Asc(unsigned char inHex, unsigned char *pOutStr);
void _stdcall Asc2Bcd(char *bcd, char *asc, int len);
void _stdcall Bcd2Asc(char *asc, char *bcd, int len);


//////////////////////////////////////////////////////////////////////////
//用途:		Bcd码转成ASC码并补空格
//函数名:	Bcd2AscEx
//功能:		将BCD码转成ASC码,即16进制转成字符串
//输入参数:	bcd 指16进制的指针
//			len 指其长度
//输出参数:	bcd 指转后输出的指针
//返回值:	无
//备注:		与Bcd2Asc不同的是多出空格，如0x40 0x03==>40 03 ,而不是4003
//////////////////////////////////////////////////////////////////////////
void _stdcall Bcd2AscEx(char *asc, char *bcd, int len);


//////////////////////////////////////////////////////////////////////////
//用途:		设置编辑控件句柄
//函数名:	Debug_SetEditHwnd
//功能:		
//输入参数:	HWND hEdit
//输出参数:	无
//返回值:	无
//备注:
//////////////////////////////////////////////////////////////////////////
void PASCAL  Debug_SetEditHwnd(HWND hEdit);

//////////////////////////////////////////////////////////////////////////
//用途:		输出信息	
//函数名:	Debug_Printf
//功能:		向辑框中输出信息
//输入参数:	fmt为输出格式
//输出参数:	无
//返回值:	返回AK_TRUE为初始化成功，否则AK_FALSE为初始化失败
//备注:
//例如:
//////////////////////////////////////////////////////////////////////////
int PASCAL	Debug_Printf(const char *fmt, ...);

//////////////////////////////////////////////////////////////////////////
//用途:		输出信息	
//函数名:	DebugOutput
//功能:		向文件中输出信息
//输入参数:	fmt为输出格式
//输出参数:	无
//返回值:	返回AK_TRUE为初始化成功，否则AK_FALSE为初始化失败
//备注:
//例如:
//////////////////////////////////////////////////////////////////////////
BOOL PASCAL	DebugOutput(char	*FileName, char *s, ...);
#ifdef __cplusplus
}
#endif



#endif

#endif
