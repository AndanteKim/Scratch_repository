#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main(){

	/*create winsocket*/
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	/*create socket*/
	SOCKET UDPs;
	UDPs = socket(AF_INET,SOCK_DGRAM,0);
	if(UDPs == INVALID_SOCKET){
		printf("SOCKET ERROR!!\n");
		return -1;
	}

	/*server struct*/
	SOCKADDR_IN SRVAddr;
	SRVAddr.sin_family = AF_INET;
	SRVAddr.sin_port = htons(22222);
	SRVAddr.sin_addr.s_addr = inet_addr("192.168.222.129");


	/*bind address*/
	int error=0;
	error=bind(UDPs,(sockaddr *)(&SRVAddr),sizeof(SRVAddr));
	if(error == SOCKET_ERROR){
		printf("BIND ERROR!!\n");
		return -1;
	}
	
	/*address struct of who communicates with*/
	SOCKADDR_IN recvAddr;
	int recvLen = sizeof(recvAddr);

	char path[256];
	memset(path,0,sizeof(path));
	recvfrom(UDPs,path,sizeof(path),0,(sockaddr*)(&recvAddr),&recvLen);
	printf("Path : %s\n",path);

	/*Sending data*/
	FILE * fp;
	fp = fopen(path,"rb");
	fseek(fp,0,SEEK_END);
	int	datasize=ftell(fp);
	fclose(fp);
	
sendto(UDPs,(char*)&datasize,sizeof(datasize),0,(sockaddr*)(&recvAddr),recvLen);

	char * sendBuf = (char*)malloc(datasize);
	memset(sendBuf,0,datasize);

	fp=fopen(path,"rb");
	fread(sendBuf,datasize,1,fp);
	fclose(fp);

	char udpbuf[1024];
	memset(udpbuf,0,sizeof(udpbuf));
	int sendsize =sizeof(udpbuf);
	int totalsize=0;
	printf("%d\n",datasize);
	int size=0;

while(1)
{

	memcpy(udpbuf,&sendBuf[totalsize],sendsize);
	size=sendto(UDPs,udpbuf,sendsize,0,(sockaddr*)(&recvAddr),recvLen);
	if(size==0)
		break;

	datasize-=size;

	if(datasize<size)
		sendsize = datasize;

	totalsize+=size;

	printf("sending data : %d\n",size);


}
	/*close socket*/
	closesocket(UDPs);

	/*unload dll*/
	WSACleanup();
	return 0;
}