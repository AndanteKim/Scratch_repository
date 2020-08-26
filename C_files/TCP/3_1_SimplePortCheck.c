/*set preprocessor*/
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
	/* unload dll */
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	/*create socket*/
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s == INVALID_SOCKET){
		printf("socket error!\n");
		return -1;
	}

	unsigned short start = atoi(argv[1]);
	unsigned short end = atoi(argv[2]);

	SOCKADDR_IN SRVAddr;
	memset(&SRVAddr, 0, sizeof(SRVAddr));

	/*Input server ip address and port*/
	SRVAddr.sin_addr.s_addr = inet_addr("192.168.91.132");
	SRVAddr.sin_family = AF_INET;

	int errch = 0;
	while(start <= end)
	{
		SRVAddr.sin_port = htons(start);
		errch = connect(s,(SOCKADDR *)&SRVAddr, sizeof(SRVAddr));
		if(errch == SOCKET_ERROR){
			printf("%d port close!\n", start);
		}else{
			printf("%d port open!\n", start);
		}

		start++;
	}

	/*close socket*/
	closesocket(s);

	/*unload dll */
	WSACleanup();

	return 0;
}
