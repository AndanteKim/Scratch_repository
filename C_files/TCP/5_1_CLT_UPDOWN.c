//#pragma comment(lib,"ws2_32")
#include<winsock2.h>
#include<stdio.h>
typedef struct u{
	int num;
	char str[1024];
}ST;
int main(){
	// load dll
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	SOCKET s;
	// create socket
	s = socket(AF_INET,SOCK_STREAM,0);
	if(s == INVALID_SOCKET){
		printf("socket_error!!!!");
		return -1;
	}
	// set ip address and port
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = inet_addr("192.168.1.144");

	int error = connect(s,(sockaddr*)&addr,sizeof(addr));
	if(error == SOCKET_ERROR){
		printf("connect_error!!!!");
		return -1;
	}
	// send data
	char buf[500];
	int user;
	ST st;
	while(1){
		memset(&st,0,sizeof(st));
		printf("Input sending data : ");
		scanf("%d",&user);
		int len = send(s,(char*)&user,sizeof(user),0);
		recv(s,(char*)&st,sizeof(st),0);		
		printf("%s\n",st.str);
		if(st.num == 1)
			break;
		
	}
	// close socket and unload dll
	closesocket(s);
	WSACleanup();
	return 0;
}