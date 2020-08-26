#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>
#include <time.h>

int main(){

	/*create winsocket*/
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	/*create socket*/
	SOCKET UDPs;
	UDPs = socket(AF_INET,SOCK_DGRAM,0);
	if(UDPs == INVALID_SOCKET){
		printf("SOCKET ERROR!!\n");
		return -1;
	}

	/* struct of server address*/
	SOCKADDR_IN SRVAddr;
	SRVAddr.sin_family = AF_INET;
	SRVAddr.sin_port = htons(22222);
	SRVAddr.sin_addr.s_addr = inet_addr("192.168.222.129");


	/*bind address*/
	int error=0;
	error=bind(UDPs,(sockaddr *)(&SRVAddr),sizeof(SRVAddr));
	if(error == SOCKET_ERROR){
		printf("BIND ERROR!!\n");
		return -1;
	}
	
	SOCKADDR_IN CLTaddr;
	int CLTlen = sizeof(CLTaddr);
	memset((char*)&CLTaddr,0,sizeof(CLTaddr));

	char msg[256];
	memset(msg,0,sizeof(msg));

	recvfrom(UDPs,msg,sizeof(msg),0,(SOCKADDR*)&CLTaddr, &CLTlen);

	time_t tm;
	time(&tm);
	struct tm * lt= localtime(&tm);
	char time[512];
	memset(time,0, sizeof(time));

	sprintf(time,"Today is %d(year)/%d(month)/%d(day). Current time is %d : %d. \n",
	lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday,lt->tm_hour, lt->tm_min);

	sendto(UDPs,time,strlen(time),0,(SOCKADDR*)&CLTaddr, CLTlen);



	/*close socket*/
	closesocket(UDPs);

	/*unload dll*/
	WSACleanup();
	return 0;
}