/*set preprocessor*/
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main(int argc, char * argv[] )
{
	/* load dll */
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	/*create socket*/
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s == INVALID_SOCKET){
		printf("socket error!\n");
		return -1;
	}

	SOCKADDR_IN SRVAddr;
	memset(&SRVAddr, 0, sizeof(SRVAddr));

	/*input server ip, port address */
	SRVAddr.sin_addr.s_addr = inet_addr(argv[1]);
	SRVAddr.sin_port = htons( atoi(argv[2]) );
	SRVAddr.sin_family = AF_INET;

	int errch = 0;
	errch = connect(s,(SOCKADDR *)&SRVAddr, sizeof(SRVAddr));
	if(errch == SOCKET_ERROR){
		printf("connect error!\n");
		return -1;
	}
	
	/*send data*/
	char sendbuf[1024];
	memset(sendbuf, 0, sizeof(sendbuf));

	printf("data input : ");
	scanf("%s", sendbuf);

	int size;
	size = send(s,sendbuf,strlen(sendbuf),0);
	printf("The size of sending data : %d\n", size);

	char recvbuf[1024];
	memset(recvbuf, 0, sizeof(recvbuf));
	recv(s,recvbuf, sizeof(recvbuf),0);
	printf("Receiving data :%s\n", recvbuf);

	/*Close socket*/
	closesocket(s);

	/*unload dll */
	WSACleanup();

	return 0;
}
