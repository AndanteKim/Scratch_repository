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
	SRVaddr.sin_addr.s_addr = inet_addr("192.168.91.132");
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

	/*Permit connection*/
	SOCKET CLTs;
	SOCKADDR_IN CLTaddr;
	memset(&CLTaddr, 0, sizeof(CLTaddr));
	int size = sizeof(CLTaddr);

	CLTs = accept(s, (SOCKADDR * )&CLTaddr, &size);
	if(CLTs == INVALID_SOCKET){
		printf("accept error!\n");
		return -1;
	}
	
	/*Receive data size*/
	int fsize=0;
	recv(CLTs,(char*)&fsize, sizeof(fsize),0);

	/*Receive data*/
	char * recvbuf = (char*)malloc(fsize);
	memset(recvbuf,0, fsize);
	
	int recvsize = 0;
	recvsize = recv(CLTs, recvbuf, fsize, 0);
	printf("The size of receiving data: %d\n", recvsize);

	FILE * fp;
	fp=fopen("C:\\winter.jpg", "wb");
	fwrite(recvbuf,1,fsize,fp);
	fclose(fp);

	/*close socket and unload dll*/
	closesocket(CLTs);
	closesocket(s);
	WSACleanup();
	return 0;
}
