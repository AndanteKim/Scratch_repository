
#include<winsock2.h>
#include<stdio.h>
int main(int argc,char * argv[]){
	// load dll
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	// create socket
	SOCKET s;
	s = socket(AF_INET,SOCK_STREAM,0);
	if(s == INVALID_SOCKET){
		printf("socket_error!!!");
		return -1;
	}
	// set port and ip address
	SOCKADDR_IN ser_addr;
	ser_addr.sin_addr.s_addr = inet_addr(argv[1]);
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(atoi(argv[2]));
	
	int error=0;
	error = connect(s,(sockaddr*)&ser_addr,sizeof(ser_addr));
	if(error == SOCKET_ERROR){
		printf("connect_error!!!!");
		return -1;
	}
	// send data to say "hello"
	int len=0;
	char buf[100]="hello";
	len = send(s,buf,sizeof(buf),0);

	// close socket and unload dll
	closesocket(s);
	WSACleanup();


	return -1;
}