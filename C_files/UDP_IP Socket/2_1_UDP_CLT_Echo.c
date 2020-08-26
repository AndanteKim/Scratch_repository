/*set preprocess*/
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

	/*sending data*/
	SOCKADDR_IN SRVaddr;
	memset(&SRVaddr, 0, sizeof(SRVaddr));

	SRVaddr.sin_addr.s_addr = inet_addr("192.168.91.132");
	SRVaddr.sin_port = htons(12345);
	SRVaddr.sin_family = AF_INET;

	FILE * fp;
	fp = fopen("c:\\Data.txt", "rb");
	fseek(fp,0,SEEK_END);
	int fsize = ftell(fp);

	char * sendbuf = (char*)malloc(fsize);
	memset(sendbuf, 0, fsize);

	fseek(fp, 0 , SEEK_SET);
	fread(sendbuf,1,fsize,fp);
	fclose(fp);

	int sendsize=0;
	sendsize = sendto(s,sendbuf,fsize,0,
		(SOCKADDR*)&SRVaddr,sizeof(SRVaddr));
	printf("Size of sending data : %d\n", sendsize);

	char recvbuf[1024];
	memset(recvbuf,0,sizeof(recvbuf));

	recvfrom(s,recvbuf,sizeof(recvbuf),0,NULL,0);
	printf("Inward data : %s\n", recvbuf);

	/*close socket*/
	closesocket(s);

	/*unload dll */
	WSACleanup();

	return 0;
}
