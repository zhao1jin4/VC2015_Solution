
//#include <Windows.h>
#include <WinSock2.h> //在links设置中加Ws2_32.lib
#include <stdio.h>
namespace socket_tcp_server
{
	int main(int argc,char* argv[] )
	{
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;
 
		wVersionRequested = MAKEWORD( 1, 1 );//使用1.1版本
 
		err = WSAStartup( wVersionRequested, &wsaData );
		if ( err != 0 ) {
			return 1;
		}
		if ( LOBYTE( wsaData.wVersion ) != 1 ||
				HIBYTE( wsaData.wVersion ) != 1 ) {
			WSACleanup( );
			return 1; 
		}
		//--------windows
		SOCKET socketSer=socket(AF_INET,SOCK_STREAM,0);//windows的SOCKET,linux用int,TCP
		sockaddr_in addr;//windows也可以使用大写SOCKADDR_IN
		addr.sin_port=htons(8000);
		addr.sin_family=AF_INET;
		addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//本机的所有网卡的IP都可以收到

		bind(socketSer,(sockaddr*)&addr,sizeof(addr));
		
		listen(socketSer,5);//队列中最多5个
		
		sockaddr_in clientAddr;
		int len=sizeof(clientAddr);
		printf("waiting ...\n");
		while(1)
		{
			SOCKET socketClient;
			socketClient=accept(socketSer,(sockaddr*)&clientAddr,&len);
			char resp[50];
			sprintf(resp,"welcome %s !",inet_ntoa(clientAddr.sin_addr));
			send(socketClient,resp,strlen(resp)+1,0);//+1 为\0 ,MSG_OOB

			recv(socketClient,resp,50,0);
			printf("tcp server receive from client :%s\n",resp);

			closesocket(socketClient);

		}

		//--------可移植代码
		/*
		int socketSer=socket(AF_INET,SOCK_STREAM,0);

		sockaddr_in addr;
		addr.sin_port=htons(8000);
		addr.sin_family=AF_INET;
		*/



		return 1;
	}

}