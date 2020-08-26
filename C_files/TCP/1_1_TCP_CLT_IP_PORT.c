
#include<winsock2.h>
#include<stdio.h>
int main(){
	// load dll
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	//set socket
	SOCKET s;
	s = socket(AF_INET,SOCK_STREAM,0);
	if(s == INVALID_SOCKET){
		printf("socket_error!!!");
		return -1;
	}

	SOCKADDR_IN ser_addr;
	ser_addr.sin_addr.s_addr = inet_addr("192.168.139.134");
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(12345);

	int error=0;
	error = connect(s,(sockaddr*)&ser_addr,sizeof(ser_addr));
	if(error == SOCKET_ERROR){
		printf("connect_error!!!!");
		return -1;
	}
	//This is a method to get port number as command : netstat -an
	getchar();
	
	
	int len=0;
	char buf[100]="hello";
	len = send(s,buf,sizeof(buf),0);
	// close socket and unload dll
	closesocket(s);
	WSACleanup();


	return -1;
}