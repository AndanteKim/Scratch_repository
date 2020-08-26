#include<winsock2.h>
#include<stdio.h>
int main(){
	//load dll
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	//set socket
	SOCKET s;
	s = socket(AF_INET,SOCK_STREAM,0);
	if(s == INVALID_SOCKET){
		printf("socket_error!!!");
		return -1;
	}
	//set IP address and port
	SOCKADDR_IN ser_addr;
	ser_addr.sin_addr.s_addr = inet_addr("192.168.139.134");
	ser_addr.sin_port = htons(12345);
	ser_addr.sin_family = AF_INET;
	// check whether bind and port_listen works or not 
	int error =0;
	error = bind(s,(sockaddr*)&ser_addr,sizeof(ser_addr));
	if(error == SOCKET_ERROR){
		printf("bind_error!!");
		return -1;
	}
	error = listen(s,SOMAXCONN);
	if(error == SOCKET_ERROR){
		printf("listen_error!!");
		return -1;
	}
	
	// connect a client
	SOCKET clt_s;
	SOCKADDR_IN clt_addr;
	int size = sizeof(clt_addr);
	clt_s = accept(s,(sockaddr*)&clt_addr,&size);
	if(clt_s ==INVALID_SOCKET){
		printf("clt_socket_error!!!");
		return -1;
	}
	// receive message
	int len;
	char buf[512];
	len = recv(clt_s,buf,sizeof(buf),0);
	// get client's information
	printf("client_port : %d\n",ntohs(clt_addr.sin_port));
	printf("client_ip   : %s\n",inet_ntoa(clt_addr.sin_addr));
	// close socket and unload dll
	closesocket(s);
	WSACleanup();
	return -1;
	
}