#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main()
{
	WSADATA wsa;
	
	/* load winsocket dll*/ 
	WSAStartup( MAKEWORD(2,2) ,&wsa);

	/* create socket*/
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM,0);
	if(s == INVALID_SOCKET){
		printf("socket error!\n");
		return -1;
	}
	
	/*bind address*/
	//struct sockaddr_in
	SOCKADDR_IN SRVaddr;
	memset(&SRVaddr, 0, sizeof(SRVaddr));

	SRVaddr.sin_family = AF_INET;
	SRVaddr.sin_port = htons(12345);
	SRVaddr.sin_addr.s_addr = inet_addr("192.168.1.144");
	//SRVaddr.sin_addr.S_un.S_addr = "IP address";

	int errch = 0;
	errch = bind(s, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr));
	if(errch == SOCKET_ERROR){
		printf("bind error!\n");
		return -1;
	}
	
	/*Open port*/
	errch = listen(s,SOMAXCONN);
	if(errch == SOCKET_ERROR){
		printf("listen error!\n");
		return -1;
	}

	/*Permit connection from client*/
	SOCKET CLTs;
	SOCKADDR_IN CLTaddr;
	memset(&CLTaddr, 0, sizeof(CLTaddr));
	int size = sizeof(CLTaddr);

	CLTs = accept(s, (SOCKADDR * )&CLTaddr, &size);
	if(CLTs == INVALID_SOCKET){
		printf("accept error!\n");
		return -1;
	}
	
	/*Receive data*/
	char recvbuf[1024];
	memset(recvbuf, 0, sizeof(recvbuf));

	recv(CLTs, recvbuf, sizeof(recvbuf), 0);
	
	FILE * fp = fopen("c:\\data.txt","w");
	fwrite(recvbuf,1,sizeof(recvbuf),fp);

	fclose(fp);

	/*close socket and unload dll*/
	closesocket(CLTs);
	closesocket(s);
	// close socket and unload dll
	WSACleanup();
	return 0;
}
