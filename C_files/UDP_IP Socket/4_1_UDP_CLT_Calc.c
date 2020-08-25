/*set preprocessor*/
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main(){
	/* load dll */
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	/*create socket*/
	SOCKET s;
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if(s == INVALID_SOCKET){
		printf("socket error!\n");
		return -1;
	}

	/*send data*/
	SOCKADDR_IN SRVaddr;
	memset(&SRVaddr, 0, sizeof(SRVaddr));

	SRVaddr.sin_addr.s_addr = inet_addr("192.168.91.132");
	SRVaddr.sin_port = htons(12345);
	SRVaddr.sin_family = AF_INET;

	char sendbuf[1024];
	memset(sendbuf, 0, sizeof(sendbuf) );

	printf("input data : ");
	scanf("%s", sendbuf);

	int sendsize=0;
	sendsize = sendto(s,sendbuf,strlen(sendbuf),0,
		(SOCKADDR*)&SRVaddr,sizeof(SRVaddr));
	printf("The size of sending data : %d\n", sendsize);

	int result=0;
	recvfrom(s,(char*)&result,sizeof(result),0,NULL,0);
	printf("result : %d\n", result);

	/*close socket*/
	closesocket(s);

	/*unload dll */
	WSACleanup();

	return 0;
}
