/*set preprocessor*/
#pragma comment(lib,"ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>
int main(){
	/*load dll*/
	WSAData wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	
	SOCKET s;
	s = socket(AF_INET,SOCK_DGRAM,0);
	if(s == INVALID_SOCKET){
		return -1;
	}
	
	/*set ip address and port*/
	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = inet_addr("192.168.1.144");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(11111);
	
	/*If there is a bind error, show the error*/
	int error;
	error = bind(s,(sockaddr*)&addr,sizeof(addr));
	if(error == SOCKET_ERROR){
		return -1;
	}
	
	/*Receive data*/
	char buf[1024]={0};
	SOCKADDR_IN clt_addr={0};
	int len = sizeof(clt_addr);
	int size=0;
	size = recvfrom(s,buf,sizeof(buf),0,
		(sockaddr*)&clt_addr,&len);
	if(size == SOCKET_ERROR){
		return -1;
	}
	sendto(s,buf,sizeof(buf),0,
	(sockaddr*)&clt_addr,sizeof(clt_addr));
	
	/*unload dll and end socket*/
	closesocket(s);
	WSACleanup();
	return 0;
}
