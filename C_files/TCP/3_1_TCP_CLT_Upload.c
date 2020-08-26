/*set preprocessor*/
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main()
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

	/*Input server ip address and port*/
	SRVAddr.sin_addr.s_addr = inet_addr("192.168.91.132");
	SRVAddr.sin_port = htons(12345);
	SRVAddr.sin_family = AF_INET;

	int errch = 0;
	errch = connect(s,(SOCKADDR *)&SRVAddr, sizeof(SRVAddr));
	if(errch == SOCKET_ERROR){
		printf("connect error!\n");
		return -1;
	}
	
	/*Send the size of data*/
	FILE * fp;
	fp = fopen("C:\\winter.jpg", "rb");
	fseek(fp,0,SEEK_END);
	int fsize = ftell(fp);
	fclose(fp);

	send(s,(char*)&fsize, sizeof(fsize),0);

	/*send data*/
	fp = fopen("C:\\winter.jpg", "rb");
	char * sendbuf = (char*)malloc(fsize);
	memset(sendbuf,0, fsize);
	fread(sendbuf,1,fsize,fp);
	fclose(fp);

	int size;
	size = send(s,sendbuf,fsize,0);
	printf("The size of sending data : %d\n", size);

	/*close socket*/
	closesocket(s);

	/*unload dll*/
	WSACleanup();

	return 0;
}
