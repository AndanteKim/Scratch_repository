#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main()
{
	WSADATA wsa;
	
	/* load winsocket dll*/ 
	WSAStartup( MAKEWORD(2,2) ,&wsa);

	/* create socket*/
	SOCKET s;
	s = socket(AF_INET, SOCK_DGRAM,0);
	if(s == INVALID_SOCKET){
		printf("socket error!\n");
		return -1;
	}
	
	/*bind address*/
	//struct sockaddr_in
	SOCKADDR_IN SRVaddr;
	memset(&SRVaddr, 0, sizeof(SRVaddr));

	SRVaddr.sin_family = AF_INET;
	SRVaddr.sin_port = htons(12345);
	SRVaddr.sin_addr.s_addr = inet_addr("192.168.91.132");
	//SRVaddr.sin_addr.S_un.S_addr = "ip address";

	int errch = 0;
	errch = bind(s, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr));
	if(errch == SOCKET_ERROR){
		printf("bind error!\n");
		return -1;
	}
	
	/*receive data*/
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	
	SOCKADDR_IN CLTaddr;
	int CLTlen = sizeof(CLTaddr);
	memset(&CLTaddr, 0, CLTlen);

	int fsize=0;
	recvfrom(s,(char*)&fsize,sizeof(fsize),0,NULL,0);

	char * recvbuf = (char*)malloc(fsize);
	memset(recvbuf,0, fsize);

	int recvlen=0;
	int size =0;

	while(1)
	{
		recvlen = recvfrom(s,buf,sizeof(buf),0,
				   (SOCKADDR*)&CLTaddr, &CLTlen);
		printf("Size of receiving data : %d\n", recvlen);
			if(recvlen == 0)
				break;

			memcpy(&recvbuf[size],buf,recvlen);
			size += recvlen;

	}

	/*This is an example of image.*/
	FILE* fp;
	fp = fopen("C:\\image.jpg", "wb");
	fwrite(recvbuf,1, fsize,fp);
	fclose(fp);

	/*close socket นื unload dll*/
	closesocket(s);
	WSACleanup();
	return 0;
}
