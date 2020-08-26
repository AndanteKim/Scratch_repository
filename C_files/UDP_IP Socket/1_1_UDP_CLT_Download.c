#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main()
{
	/*create window socket*/
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);

	/*create socket*/
	SOCKET UDPc;
	UDPc=socket(AF_INET, SOCK_DGRAM,0);
	if(UDPc == INVALID_SOCKET){
		printf("SOCKET ERROR!!\n");
		return -1;
	}
	/*address struct of server*/
	SOCKADDR_IN sendAddr;
	sendAddr.sin_addr.s_addr = inet_addr("192.168.222.129");
	sendAddr.sin_port = htons(22222);
	sendAddr.sin_family = AF_INET;
	
	char path[256];
	memset(path,0,sizeof(path));
	printf("input path : ");
	scanf("%s",path);
sendto(UDPc,path,sizeof(path),0,(sockaddr*)(&sendAddr),sizeof(sendAddr));

	SOCKADDR_IN recvAddr;
	memset((char*)&recvAddr,0,sizeof(recvAddr));
	int recvLen = sizeof(recvAddr);

	/*receive data*/
	int datasize=0;
	recvfrom(UDPc,(char*)&datasize,sizeof(datasize),0,(sockaddr*)(&recvAddr),&recvLen);
	printf("datasize : %d\n",datasize);
	char * recvBuf= (char*)malloc(datasize);
	memset(recvBuf,0,datasize);

/* make nested loops since there is large size of file*/
	char buf[1024];
	memset(buf,0,sizeof(buf));
	int totalbuf=0;
	int recvSize=0;

	while(1){
recvSize = recvfrom(UDPc,buf,sizeof(buf),0,(sockaddr*)(&recvAddr),&recvLen);
		if(recvSize==0)
			break;
		printf("Receiving : %d\n", recvSize);
		memcpy(&recvBuf[totalbuf],buf,recvSize);
			totalbuf+=recvSize;
	}

	FILE *fp;
	fp=fopen("C:\\download.jpg", "wb");
	fwrite(recvBuf,datasize,1,fp);
	fclose(fp);
	


	/*close socket*/
	closesocket(UDPc);

	/*unload dll*/
	WSACleanup();

	return 0;
}