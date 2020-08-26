#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main()
{
	/*load dll*/
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);

	/*create socket*/
	SOCKET UDPc;
	UDPc=socket(AF_INET, SOCK_DGRAM,0);
	if(UDPc == INVALID_SOCKET){
		printf("SOCKET ERROR!!\n");
		return -1;
	}
	/*address struct of who communicates with*/
	SOCKADDR_IN sendAddr;
	sendAddr.sin_addr.s_addr = inet_addr("192.168.222.129");
	sendAddr.sin_port = htons(22222);
	sendAddr.sin_family = AF_INET;

	char msg[256]="Give me a moment!!";
	sendto(UDPc, msg, strlen(msg),0,(SOCKADDR*)&sendAddr,sizeof(sendAddr));

	char time[512];
	memset(time,0,sizeof(time));
	
	SOCKADDR_IN recvAddr;
	int recvLen = sizeof(recvAddr);
	memset((char*)&recvAddr, 0, recvLen);

	recvfrom(UDPc,time,sizeof(time),0,(SOCKADDR*)&recvAddr,&recvLen);

	printf("%s\n", time);

	/*close socket*/
	closesocket(UDPc);

	/*unload dll*/
	WSACleanup();

	return 0;
}