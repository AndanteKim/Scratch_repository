#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main(){

	/*Create Window Socket*/
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);
	
	/*Create socket*/
	SOCKET s;
	s = socket(AF_INET,SOCK_DGRAM,0);
	if(s == INVALID_SOCKET){
		printf("socket error!!\n");
		return -1;
	}
	/*Create address struct*/
	/*Note : The ip address can be changed.*/
	SOCKADDR_IN SRVaddr;
	SRVaddr.sin_addr.s_addr = inet_addr("192.168.222.129");
	SRVaddr.sin_port = htons(22222);
	SRVaddr.sin_family = AF_INET;
	
	/*bind address*/
	int errch;
	errch = bind(s,(SOCKADDR *)&SRVaddr,sizeof(SRVaddr));
	if(errch == SOCKET_ERROR){
		printf("bind error!!\n");
		return -1;
	}

	/*receive data*/
	SOCKADDR_IN CLTaddr;
	char recvbuf[1024];
	int addlen = sizeof(CLTaddr);

	memset(recvbuf,0,sizeof(recvbuf));
	memset((char*)&CLTaddr,0,sizeof(CLTaddr));

	recvfrom(s,recvbuf,sizeof(recvbuf),0,(SOCKADDR*)&CLTaddr,&addlen);

	printf("Inward data : %s\n", recvbuf);

	/*Terminate socket*/
	closesocket(s);
	
	/*end Window socket*/
	WSACleanup();
	return 0;
}