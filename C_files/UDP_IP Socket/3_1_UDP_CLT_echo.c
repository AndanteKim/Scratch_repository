/*set preprocessor*/
#pragma comment(lib,"ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>
#include<string.h>
#define BUFSIZE 1024

int main(){
	/*load dll*/	
	WSAData wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);

	SOCKET s;
	s= socket(AF_INET,SOCK_DGRAM,0);
	if(s == INVALID_SOCKET){
		return -1;
	}
	
	/*set port and ip address*/
	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = inet_addr("192.168.1.144");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(11111);
	
	/*set and send data*/
	char buf[1024]={0};
	printf("Input sending data : ");
	gets(buf);
	int size;
	
	size = sendto(s,buf,sizeof(buf),0,
		(sockaddr*)&addr,sizeof(addr));
	if(size == SOCKET_ERROR){
		return -1;
	}
	char buf_1[1024]={0};
	recvfrom(s,buf_1,sizeof(buf_1),0,0,0);
	
	/*show how much size of data sent*/
	printf("buf : %s\n\n",buf);
	printf("buf_1 : %s\n",buf_1);
	
	/*close socket and unload dll*/
	closesocket(s);
	WSACleanup();

	return 0;

}