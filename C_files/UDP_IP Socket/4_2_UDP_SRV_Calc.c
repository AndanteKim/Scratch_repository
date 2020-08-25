#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>

int main()
{
	WSADATA wsa;
	
	/* load dll */ 
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
	//SRVaddr.sin_addr.S_un.S_addr = ("ip address");

	int errch = 0;
	errch = bind(s, (SOCKADDR*)&SRVaddr, sizeof(SRVaddr));
	if(errch == SOCKET_ERROR){
		printf("bind error!\n");
		return -1;
	}
	
	/*receive data*/
	char recvbuf[1024];
	memset(recvbuf, 0, sizeof(recvbuf));
	
	SOCKADDR_IN CLTaddr;
	int CLTlen = sizeof(CLTaddr);
	memset(&CLTaddr, 0, CLTlen);

	int recvlen=0;
	recvlen = recvfrom(s,recvbuf,sizeof(recvbuf),0,(SOCKADDR*)&CLTaddr, &CLTlen);
	printf("[%s:%d]", inet_ntoa(CLTaddr.sin_addr), ntohs(CLTaddr.sin_port) );
	printf(" %s\n", recvbuf);

	int totalsize = strlen(recvbuf);
	int i;
	for(i=0; i<totalsize;i++)
	{
		if(recvbuf[i] == '+'||recvbuf[i]=='-'||recvbuf[i]=='*'||recvbuf[i] == '/')
		break;
	}

	int j, n1=0;
	for(j=0; j<i; j++){
		n1 += recvbuf[j] - '0';
		if(j<i-1)
			n1*=10;
	}

	int n2=0;
	for(j=i+1; j<totalsize; j++)
	{
		n2 += recvbuf[j]-'0';
		if(j < totalsize-1)
			n2*=10;
	}

	int result=0;
	if(recvbuf[i] == '+')
	{
		result = n1+n2;
	}
	else if(recvbuf[i] == '-')
	{
		result = n1-n2;
	}
	else if(recvbuf[i] == '*')
	{
		result = n1*n2;
	}
	else if(recvbuf[i] == '/')
	{
		result = n1/n2;
	}

	sendto(s,(char*)&result,sizeof(result),0,(SOCKADDR*)&CLTaddr,CLTlen);

	/*terminate socket นื unload dll*/
	closesocket(s);
	WSACleanup();
	return 0;
}
