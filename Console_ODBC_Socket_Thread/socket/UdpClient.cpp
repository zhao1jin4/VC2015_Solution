
//#include <Windows.h>
#include <WinSock2.h> //��links�����м�Ws2_32.lib
#include <stdio.h>
namespace socket_udp_client
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
		addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//�����IP

		int len =sizeof(addr);
		char* data="this from udp client.";
		sendto(socketSer,data,strlen(data)+1,0,(sockaddr*)&addr,len);
		printf("udp client send to server :%s \n",data);
		
		closesocket(socketSer);
		WSACleanup( );
		getchar();//��ͣ
		return 1;
	}
}