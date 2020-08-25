#pragma comment(lib,"ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>

int main(){
	/*dll load*/
	WSAData wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	
	/*create socket*/
	SOCKET s;
	s= socket(AF_INET,SOCK_DGRAM,0);
	if(s == INVALID_SOCKET){
		return -1;
	}
	
	/*set socket port and address*/
	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = inet_addr("192.168.1.144");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(11111);
	
	/*set sending method*/
	int size;
	char buf[1024]={0};
	size = sendto(s,buf,sizeof(buf),0,(sockaddr*)&addr,sizeof(addr));
	if(size == SOCKET_ERROR){
		return -1;
	}
	
	/*After sending data, clean remained data*/
	closesocket(s);
	WSACleanup();

	return 0;

}