// set preprocessor
#pragma comment(lib,"ws2_32")
#include<winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
int up(int user);
int rand_();
void check();

typedef struct u{
	int num;
	char str[1024];
}ST;
int ran,cnt;
int main(){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);//load DLL 
	
	SOCKET s;
	s = socket(AF_INET,SOCK_STREAM,0);//create socket
	if(s == INVALID_SOCKET){		//check error
		printf("socket_error!!!!");
		return -1;
	}
	
	SOCKADDR_IN addr;	//struct of address 
	addr.sin_family = AF_INET;	// save ipv4 address
	addr.sin_port = htons(12345);// saveport number
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.1.144");// save server_ip
	//addr.sin_addr.s_addr = 
	int error;
	error = bind(s,(sockaddr*)&addr,sizeof(addr));// bind address in the operating system
	if(error == SOCKET_ERROR){
		printf("bind_error!!!!");
		return -1;
	}
	
	error = listen(s,SOMAXCONN); //port waiting(listening)
	if(error == SOCKET_ERROR){
		printf("listen_error!!!!");
		return -1;
	}
	SOCKET clt_s;
	SOCKADDR_IN clt_addr;
	int size = sizeof(clt_addr);
	
	clt_s = accept(s,(sockaddr*)&clt_addr,&size);//awaiting connection
	if(clt_s == INVALID_SOCKET){
		printf("accept_error!!!!");
		return -1;
	}
	char buf[1024];
	int len;
	int user;
	int result;
	ST st;
	while(1){
		len = recv(clt_s,(char*)&user,sizeof(user),0);
		if(len == SOCKET_ERROR){
			printf("recv_error!!!!");
			return -1;
		}
		result = up(user);
		if(result == 1){
			printf("==== UP ====\n");
			sprintf(st.str,"==== UP ====\n");
			send(clt_s,(char*)&st,sizeof(st),0);
		}
		else if(result == -1){
			printf("==== DOWN ====\n");
			sprintf(st.str,"==== DOWN ====\n");
			send(clt_s,(char*)&st,sizeof(st),0);
		}
		else{
			printf("The answer of number %d is\n",cnt);
			sprintf(st.str,"\n\n== !! Congratulations!! ==\n",cnt);
			st.num=1;
			send(clt_s,(char*)&st,sizeof(st),0);
			break;
		}
	}
	closesocket(s);
	WSACleanup();//unload DLL
	return 0;
}

///////////////////////
// This is updown game function as below

int rand_(){
	srand(time(NULL));
	return rand() %99 +1;
}
int check(int user){

	printf("input : %d\n",user);
	printf("com : %d\n",ran);
	if(user >ran){
		cnt++;
		return 1;
	}
	else if(user<ran){
		cnt++;
		return -1;
	}
	else{
		cnt++;
		return 0;
	}	
	system("pause");system("cls");
}
int up(int user){
	int result;
	printf("updown game start~!\n");
	if(!ran)
		ran = rand_();
	result = check(user);
	return result;
}