/* ============================ [ INCLUDES  ] ====================================================== */
/* most of the code copy from https://github.com/linux-can/can-utils */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

/* virtual socket can
 * sudo modprobe vcan
 * sudo ip link add dev vcan0 type vcan
 * sudo ip link set up vcan0
 */
#ifndef CAN_MTU
#define CAN_MTU sizeof(struct can_frame)
#endif
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
int sCan0 = -1;
extern void cantp_rx_indication(uint32_t canid,uint8_t dlc,uint8_t * data);
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
int can_init(void)
{
	int s;
	int rv = 0;
	struct sockaddr_can addr;
	struct ifreq ifr;
	/* open socket */
	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("CAN socket : ");
		rv = -1;
	}

	if( 0 == rv )
	{
		snprintf(ifr.ifr_name,IFNAMSIZ - 1,"can%d", 0);
		ifr.ifr_name[IFNAMSIZ - 1] = '\0';
		ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
		if (!ifr.ifr_ifindex) {
			perror("CAN socket if_nametoindex");
			rv = -1;
		}
	}

	if( 0 == rv )
	{
		addr.can_family = AF_CAN;
		addr.can_ifindex = ifr.ifr_ifindex;

		/* disable default receive filter on this RAW socket */
		/* This is obsolete as we do not read from the socket at all, but for */
		/* this reason we can remove the receive list in the Kernel to save a */
		/* little (really a very little!) CPU usage.                          */
		/* setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0); */

		if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
			perror("CAN socket bind");
			rv = -1;
		}
		else
		{
			sCan0 = s;
		}
	}

	return rv;
}
int can_send(uint32_t canid, uint8_t dlc, uint8_t* data)
{
	int rv = 0;

	if(sCan0 != -1)
	{
		struct can_frame frame;
		frame.can_id = canid;
		frame.can_dlc = dlc;
		memcpy(frame.data,data,dlc);

		if (write(sCan0, &frame, CAN_MTU) != CAN_MTU)
		{
			perror("CAN socket write");
			rv = -1;
		}
	}
	else
	{
		rv = -1;
		printf("CAN Socket can0 is not on-line, not able to send message!\n");
	}

	return rv;
}


int can_rec(uint32_t *canid, uint8_t *dlc, uint8_t* data)
{
	int rv = -1;
	int nbytes,len;
	struct can_frame frame;
	nbytes = recv(sCan0, &frame, sizeof(frame), MSG_DONTWAIT);
	if( -1 == nbytes )
	{
		/* nothing to do */
	}
	else if (nbytes < 0) {
		perror("CAN socket read");
		rv = -1;
	}
	else
	{
		*canid = frame.can_id;
		*dlc = frame.can_dlc;
		memcpy(data,frame.data,frame.can_dlc);

		rv = 0;
	}

	return rv;
}

void can_main_rxisr(void)
{
	uint32_t canid;
	uint8_t dlc;
	uint8_t data[8];

	int rv;
	int i;

	rv = can_rec(&canid,&dlc,data);

	if(0 == rv)
	{
		cantp_rx_indication(canid,dlc,data);
	}

}
