/*set preprocessor*/
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main(int agrc,char*argv[])
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

	/*Input server IP and port*/
	// Note : The information is changed depending on a device
	SRVAddr.sin_addr.s_addr = inet_addr("192.168.1.144");
	SRVAddr.sin_port = htons(12345);//"12345"
	SRVAddr.sin_family = AF_INET;
	// connect client
	int errch = 0;
	errch = connect(s,(SOCKADDR *)&SRVAddr, sizeof(SRVAddr));
	if(errch == SOCKET_ERROR){
		printf("connect error!\n");
		return -1;
	}
	
	/*send data*/
	char sendbuf[1024];
	memset(sendbuf, 0, sizeof(sendbuf));
	
	FILE * fp = fopen("c:\\test.txt","r");
	if(fp == NULL){
		printf("The file cannot open!");
		return -1;
	}
	fread(sendbuf,1,sizeof(sendbuf),fp);
	fclose(fp);
	
	// send data
	int size;
	size = send(s,sendbuf,sizeof(sendbuf),0);
	printf("The size of sending data : %d\n", size);

	/*close socket*/
	closesocket(s);

	/*unload dll*/
	WSACleanup();

	return 0;
}
