#if 1
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define RecvBuffer_SIZE 1024*3
#define SendBuffer_SIZE 1024*3

/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void send_file(int socket)
{
	char *SendBuffer=malloc(SendBuffer_SIZE);
	FILE *SendFile;
	int ReadLen=0,SendLen=0;
	SendFile=fopen("./eval2.c","rb");
	(SendFile != NULL)? printf("open file successful\n") : printf("open file failed\n");
	do{
		ReadLen=fread(SendBuffer,sizeof(char),SendBuffer_SIZE,SendFile);
		if(ReadLen>0)
		{
			printf("ReadLen=%d\n",ReadLen);
			SendLen=send(socket,SendBuffer,ReadLen,0);
			printf("SendLen=%d\n",SendLen);
		}

	}while(ReadLen>0);
	fclose(SendFile);
	free(SendBuffer);
}
void recv_file(int socket)
{
    char *RecvBuffer=malloc(RecvBuffer_SIZE);
    char *string="./server2.c";
    FILE *RecvFile;
    int RecvLen=0,WriteLen=0;
    send(socket,string,strlen(string),0);
    RecvFile = fopen("./server2.c", "w+");//浠ヤ簩杩涘埗鏂瑰紡鎵撳紑锛堝垱寤猴級鏂囦欢
	(RecvFile != NULL) ? printf("open file successful!\n") : printf("open file failed");
	do {
		RecvLen=recv(socket,RecvBuffer,RecvBuffer_SIZE,0);	/*recv()杩斿洖璇诲叆鐨勫瓧鑺傛暟*/
		if(RecvLen > 0)
		{
			RecvBuffer[RecvLen]='\0';
			printf("RecvLen=%d\n",RecvLen);
			WriteLen=fwrite(RecvBuffer,sizeof(char),RecvLen,RecvFile);
			printf("WriteLen=%d\n",WriteLen);
		}
	} while(RecvLen>0);
	fclose(RecvFile);
	free(RecvBuffer);
}
int SocketClient_init(char* IpAddr)
{
	int err;
	char recvBuf[100];
	char* str = "this is SocketClient";
	int SockClient=socket(AF_INET,SOCK_STREAM,0);	/*寤虹珛閫氳socket	*/
	struct sockaddr_in addrSrv;
	addrSrv.sin_addr.s_addr=inet_addr(IpAddr);	/*璁惧畾闇�瑕佽繛鎺ョ殑鏈嶅姟鍣ㄧ殑ip鍦板潃,鎶婂瓧绗︿覆褰㈠紡鐨処P鍦板潃杞垚IN_ADDR缁撴瀯闇�瑕佺殑褰㈠紡銆�*/
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(8989);	/*璁惧畾闇�瑕佽繛鎺ョ殑鏈嶅姟鍣ㄧ殑绔彛鍦板潃*/
	connect(SockClient,(struct sockaddr*)&addrSrv,sizeof(struct sockaddr));	/*涓庢湇鍔″櫒杩涜杩炴帴*/
	recv(SockClient,recvBuf,100,0);	/*鎺ュ彈鏉ヨ嚜server鐨勪俊鎭�*/
	printf("from server锛�%s\n",recvBuf);
	send(SockClient,str,strlen(str),0);	/*鍙戦�佷俊鎭�*/
	return SockClient;
}
void SocketClient_main(void)
{
	int SockClient;
	SockClient=SocketClient_init("192.168.1.101");
	//recv_file(SockClient);
	send_file(SockClient);

	close(SockClient);
}

#endif
