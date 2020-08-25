/*set preprocessor*/
#pragma comment(lib,"ws2_32.lib")
#include<stdio.h>
#include<winsock2.h>
int main(){
	/*load dll*/
	WSAData wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	
	/*set server socket*/
	SOCKET s;
	s = socket(AF_INET,SOCK_DGRAM,0);
	if(s == INVALID_SOCKET){
		return -1;
	}
	
	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = inet_addr("192.168.1.144");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(11111);

	/*If there exists binding error, return error*/
	int error;
	error = bind(s,(sockaddr*)&addr,sizeof(addr));
	if(error == SOCKET_ERROR){
		return -1;
	}

	/*After binding success, allocate the maximum size of data how much server could receive.*/
	char buf[1024]={0};
	SOCKADDR_IN clt_addr={0};
	int len = sizeof(clt_addr);
	int size=0;
	size = recvfrom(s,buf,sizeof(buf),0,(sockaddr*)&clt_addr,&len);
	if(size == SOCKET_ERROR){
		return -1;
	}
	
	/*receive inward data from client*/
	printf("clt_ip : %s\n",inet_ntoa(clt_addr.sin_addr));
	printf("clt_port : %d\n",ntohs(clt_addr.sin_port));
	
	/*close socket*/
	closesocket(s);
	WSACleanup();
	return 0;
}
