#ifdef _windows_
#include <Winsock2.h>
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 1024*3

void sr_file(int socket)
{
 	FILE* SendFile;
 	char *buffer = malloc(BUF_SIZE);
 	int RecvLen=0,ReadLen=0,SendLen=0;
 	RecvLen=recv(socket,buffer,100,0);
 	if(RecvLen > 0)
 	{
 		buffer[RecvLen]='\0';
 		printf("RecvLen is:%d\n",RecvLen);
 	}
 	SendFile=fopen(buffer,"rb");
 	(SendFile != NULL) ? printf("open file successful!\n") : printf("open file failed!\n");
 	do {
		ReadLen=fread(buffer,sizeof(char),BUF_SIZE,SendFile);
		if(ReadLen > 0)
		{
			printf("ReadLen is:%d\n",ReadLen);
			SendLen=send(socket,buffer,ReadLen,0);
			printf("SendLen is:%d\n",SendLen);
		}
 	} while(ReadLen>0);
 	fclose(SendFile);
	free(buffer);
}

void SocketServer_main()
{
#ifdef _windows_
	/* code that under windows environment needed*/
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;   
    wVersionRequested = MAKEWORD( 1, 1 ); 
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 ) {
        return;
    }
    if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) {
        WSACleanup( );
        return; 
    }
#endif
    /*the socket part*/
    int SockServ=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addrSrv;
    addrSrv.sin_addr.s_addr=htonl(INADDR_ANY);	/* */
    addrSrv.sin_family=AF_INET;
    addrSrv.sin_port=htons(8989);	/*transfer port to char*/
    bind(SockServ,(struct sockaddr*)&addrSrv,sizeof(struct sockaddr));/* socket 绑定到相应的端口和地址*/
    listen(SockServ,5);/* 最多同时接受５个连接请求*/
    struct sockaddr_in addrClient;
    int len=sizeof(struct sockaddr);

    while(1)
    {
        int sockConn=accept(SockServ,(struct sockaddr*)&addrClient,&len);
        char sendBuf[100];
        sprintf(sendBuf,"Server IP is:%s",inet_ntoa(addrClient.sin_addr));
        send(sockConn,sendBuf,strlen(sendBuf)+1,0);
        char recvBuf[100];
        int len = recv(sockConn,recvBuf,100,0);
        recvBuf[len] = 0;
        printf("%s\n",recvBuf);
        
        sr_file(sockConn);
        
        close(sockConn);
    }
}
