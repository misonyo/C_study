

void can_main(void)
{
	can_init();
	cantp_init(0x731,0x732);

	do {
		can_main_rxisr();
		cantp_main_function();
		usleep(1000);
	} while(1);

}