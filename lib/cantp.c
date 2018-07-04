#if 0
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
/* ============================ [ MACROS    ] ====================================================== */
#define N_PCItype0_SF 0x00
#define N_PCItype1_FF 0x10
#define N_PCItype2_CF 0x20
#define N_PCItype3_FC 0x30
#define TX_SF_STATUS 0
#define TX_FF_STATUS 1
#define TX_CF_STATUS 2
#define TX_FC_WAIT_STATUS 3
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
extern int can_send(uint32_t canid, uint8_t dlc, uint8_t* data);
extern void dcm_rx_indication(uint8_t *buffer,uint16_t count);
/* ============================ [ DATAS     ] ====================================================== */
static uint32_t tp_rxid;
static uint32_t tp_txid;
uint8_t TXflowControl[3]={0x30,5,10};
uint8_t RXflowControl[3];
uint8_t RXbuffer[4095],TXtempBuffer[4095];
uint16_t DL,TXlength=0,RXcount=0,TXcount=0,TX_CFcount=0,RX_CFcount=0;
uint8_t SN,TXstatus=8,flag=0;

/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */

int cantp_init(uint32_t rxid,uint32_t txid)
{
	tp_rxid = rxid;
	tp_txid = txid;

	return 0;
}

int cantp_transmit(uint8_t *data, uint32_t length)
{
	if(length > 4095)
	{
		printf("length must less than 4095!");
	}
	else
	{
		if((length > 7) && (length <4095))
		{
			TXstatus=TX_FF_STATUS;
		}
		else
		{
			TXstatus=TX_SF_STATUS;
		}
		TXlength=length;
		memcpy(TXtempBuffer,data,length);
	}
	return 0;
}

void cantp_rx_indication(uint32_t canid,uint8_t dlc,uint8_t * data)
{	/* event task when any can message received */
	int count;
	if(canid == tp_rxid)
	{
		// do handle of Frame
		if((data[0] & 0xf0) == N_PCItype0_SF)	/*SingleFrame (SF) N_PCItype = 0*/
		{
			DL=data[0] & 0x0f;
			memcpy(RXbuffer,data+1,DL);
		}
		else if((data[0] & 0xf0) == N_PCItype1_FF)	/*FirstFrame (FF) N_PCItype = 1*/
		{
			can_send(tp_txid,3,TXflowControl);
			DL=((data[0] << 4) << 8) | data[1];
			memcpy(RXbuffer,data+2,6);
			RXcount=6;
		}
		else if((data[0] & 0xf0) == N_PCItype2_CF)	/*ConsecutiveFrame (CF) N_PCItype = 2*/
		{
			RX_CFcount++;
			if((RX_CFcount % 5) == 0)
			{
				can_send(tp_txid,3,TXflowControl);
			}
			count=((DL-RXcount) > 7) ? 7:(DL-RXcount);
			memcpy(RXbuffer+RXcount,data+1,count);
			RXcount+=count;
		}
		else if((data[0] & 0xf0) == N_PCItype3_FC)	/*  FlowControl (FC) N_PCItype = 3*/
		{
			memcpy(RXflowControl,data,dlc);
			flag=1;
		}
		if(RXcount == DL)
		{
			dcm_rx_indication(RXbuffer,RXcount);
			RXcount = 0;
		}
	}
}

void cantp_main_function(void)
{	/* 1ms periodic task */

	if((TXlength-TXcount)>0)
	{
		uint8_t TXbuffer[8];
		int count;
		switch(TXstatus)
		{
			case TX_SF_STATUS:	/*SingleFrame (SF) N_PCItype = 0*/
				TXbuffer[0]=N_PCItype0_SF | TXlength;
				memcpy(TXbuffer+1,TXtempBuffer,TXlength);
				can_send(tp_txid,8,TXbuffer);
				break;
			case TX_FF_STATUS:	/*FirstFrame (FF) N_PCItype = 1*/
				TXbuffer[0]=N_PCItype1_FF | (TXlength >> 8);
				TXbuffer[1]=TXlength;
				memcpy(TXbuffer+2,TXtempBuffer,6);
				can_send(tp_txid,8,TXbuffer);
				TXcount=6;
				SN=0;
				TXstatus=TX_FC_WAIT_STATUS;
				break;
			case TX_CF_STATUS:	/*ConsecutiveFrame (CF) N_PCItype = 2*/
				SN++;
				if(SN >15)
				{
					SN=0;
				}
				TXbuffer[0]=N_PCItype2_CF | SN;
				count=((TXlength-TXcount) > 7) ? 7 : (TXlength-TXcount);
				memcpy(TXbuffer+1,TXtempBuffer+TXcount,count);
				can_send(tp_txid,count+1,TXbuffer);
				TXcount+=count;
				if(TXcount == TXlength)
				{
					TXlength=0;
					TXcount=0;
				}
				TX_CFcount++;
				if((TX_CFcount % RXflowControl[1]) == 0)
				{
					TXstatus=TX_FC_WAIT_STATUS;
				}
				break;
			case TX_FC_WAIT_STATUS:	/*FlowControl (FC) N_PCItype = 3*/
				if(flag == 1)
				{
					TXstatus=TX_CF_STATUS;
					flag=0;
				}
				break;
			default:
				break;
		}
	}
}
#endif
