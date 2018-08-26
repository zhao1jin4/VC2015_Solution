
//#include <Windows.h>
#include <WinSock2.h> //��links�����м�Ws2_32.lib
#include <stdio.h>
namespace socket_udp_server
{
	int main(int argc,char* argv[] )
	{
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;
 
		wVersionRequested = MAKEWORD( 1, 1 );//ʹ��1.1�汾
 
		err = WSAStartup( wVersionRequested, &wsaData );
		if ( err != 0 ) {
			return 1;
		}
		if ( LOBYTE( wsaData.wVersion ) != 1 ||
				HIBYTE( wsaData.wVersion ) != 1 ) {
			WSACleanup( );
			return 1; 
		}

		SOCKET socketSer=socket(AF_INET,SOCK_DGRAM,0);//windows��SOCKET,linux��int,UDP
		
		sockaddr_in addr;//windowsҲ����ʹ�ô�дSOCKADDR_IN
		addr.sin_port=htons(8000);
		addr.sin_family=AF_INET;
		addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//����������������IP�������յ�
		 
		bind(socketSer, (sockaddr *) &addr, sizeof(addr));//UDPֻbind ,����listen,accept

		int len=sizeof(addr);
		char data[50];
		
		printf("waiting ... \n");
		recvfrom(socketSer,data,50,0,(sockaddr*)&addr,&len);

		printf("udp server receive from client:%s \n",data);
		closesocket(socketSer);
		WSACleanup( );
		getchar();//��ͣ
		return 1;
	}
}