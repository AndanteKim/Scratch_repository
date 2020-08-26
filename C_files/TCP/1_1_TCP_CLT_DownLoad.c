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

	/* input server ip address and port */
	SRVAddr.sin_addr.s_addr = inet_addr("192.168.91.132");
	SRVAddr.sin_port = htons(12345);
	SRVAddr.sin_family = AF_INET;

	int errch = 0;
	errch = connect(s,(SOCKADDR *)&SRVAddr, sizeof(SRVAddr));
	if(errch == SOCKET_ERROR){
		printf("connect error!\n");
		return -1;
	}

	/*send download file path*/
	char path[256];
	memset(path,0,sizeof(path));
	printf("input path : ");
	scanf("%s", path);

	send(s,path,strlen(path),0);

	/* receive the size of data*/
	int fsize=0;
	recv(s,(char*)&fsize,sizeof(fsize),0);
	char * recvbuf = (char*)malloc(fsize);
	memset(recvbuf, 0, fsize);

	/*receive data*/
	recv(s,recvbuf,fsize,0);

	FILE * fp;
	fp=fopen("c:\\downdData.jpg", "wb");
	fwrite(recvbuf,1,fsize,fp);
	fclose(fp);

	/*close socket*/
	closesocket(s);

	/*unload dll */
	WSACleanup();

	return 0;
}
