#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main()
{
	/*Create Window socket*/
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);
	
	/*Socket create */
	SOCKET s;
	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s == INVALID_SOCKET){
		printf("socket error!!\n");
		return -1;
	}

	/*create struct of address*/
	/*Note : IP address can be changed depending on any device.*/
	SOCKADDR_IN sendaddr;
	sendaddr.sin_addr.s_addr = inet_addr("192.168.222.129");
	sendaddr.sin_port = htons(22222);
	sendaddr.sin_family = AF_INET;

	/*send data*/
	char sendbuf[512];
	memset(sendbuf,0,sizeof(sendbuf));
	memcpy(sendbuf,"HELLO SOCKET!!",15);

	sendto(s,sendbuf,strlen(sendbuf),0,(SOCKADDR*)&sendaddr,sizeof(sendaddr));

	/*terminate socket*/
	closesocket(s);

	/*end window socket*/
	WSACleanup();
	return 0;
}