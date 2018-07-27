#if 1

#ifdef _WIN32
#include <Winsock2.h>
#else
//#include <netinet/in.h>
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
#ifdef _WIN32
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
    /* AF_INET(Ipv4),SOCK_STREAM(有序、可靠、双向的面向连接字节流（TCP）),0(按照前面的参数选择默认的传输协议) */
    int SockServ=socket(AF_INET,SOCK_STREAM,0);   /* 创建一个网络套接字 */

    struct sockaddr_in addrSrv;
    addrSrv.sin_addr.s_addr=htonl(INADDR_ANY);    /* IP地址：htonl(主机数转换成无符号长整形的网络字节顺序), INADDR_ANY(系统会自动填入本机的IP地址) */
    addrSrv.sin_family=AF_INET;                   /* sin_family一般固定写 AF_INET */
    addrSrv.sin_port=htons(8989);                 /* 端口号：htons(将整型变量从主机字节顺序转变成网络字节顺序) */

    bind(SockServ,(struct sockaddr*)&addrSrv,sizeof(struct sockaddr));/* 将套接字与计算机上的一个端口号相绑定 */
    listen(SockServ,5);/* 鏈�澶氬悓鏃舵帴鍙楋紩涓繛鎺ヨ姹�*/

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

#endif
