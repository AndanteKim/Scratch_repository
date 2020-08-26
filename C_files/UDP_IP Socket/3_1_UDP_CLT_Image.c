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

	/*receive data*/
	SOCKADDR_IN SRVaddr;
	memset(&SRVaddr, 0, sizeof(SRVaddr));

	SRVaddr.sin_addr.s_addr = inet_addr("192.168.91.132");
	SRVaddr.sin_port = htons(12345);
	SRVaddr.sin_family = AF_INET;
	
	/*This is an example I want to open a file.*/
	FILE * fp;
	fp = fopen("c:\\winter.jpg", "rb");
	fseek(fp,0,SEEK_END);
	int fsize = ftell(fp);

	sendto(s,(char*)&fsize,sizeof(fsize),0,
		(SOCKADDR*)&SRVaddr,sizeof(SRVaddr));

	char * sendbuf = (char*)malloc(fsize);
	memset(sendbuf,0, fsize);

	fseek(fp,0,SEEK_SET);
	fread(sendbuf,1,fsize,fp);
	fclose(fp);

	char buf[1024];
	memset(buf,0,sizeof(buf));

	int size=0;
	int sendsize=1024;
	int totalsize = fsize;

	while(1)
	{
		memcpy(buf, &sendbuf[size] ,sendsize);
		sendsize = sendto(s,buf, sendsize ,0,
				(SOCKADDR*)&SRVaddr,sizeof(SRVaddr));
		printf("The size of sending data : %d\n", sendsize);

		if(sendsize == 0)
			break;

		totalsize -= sendsize;
		size += sendsize;

		if(totalsize < sendsize )
			sendsize = totalsize;

	}
	/*close socket*/
	closesocket(s);

	/*unload dll*/
	WSACleanup();

	return 0;
}
