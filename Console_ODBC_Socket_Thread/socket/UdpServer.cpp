
//#include <Windows.h>
#include <WinSock2.h> //在links设置中加Ws2_32.lib
#include <stdio.h>
namespace socket_udp_server
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

		SOCKET socketSer=socket(AF_INET,SOCK_DGRAM,0);//windows的SOCKET,linux用int,UDP
		
		sockaddr_in addr;//windows也可以使用大写SOCKADDR_IN
		addr.sin_port=htons(8000);
		addr.sin_family=AF_INET;
		addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//本机的所有网卡的IP都可以收到
		 
		bind(socketSer, (sockaddr *) &addr, sizeof(addr));//UDP只bind ,不用listen,accept

		int len=sizeof(addr);
		char data[50];
		
		printf("waiting ... \n");
		recvfrom(socketSer,data,50,0,(sockaddr*)&addr,&len);

		printf("udp server receive from client:%s \n",data);
		closesocket(socketSer);
		WSACleanup( );
		getchar();//暂停
		return 1;
	}
}