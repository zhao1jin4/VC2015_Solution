#pragma once //VC特殊的

//#ifndef MAIN_H
//#define MAIN_H

	//-----ODBC
	namespace odbc_bind_ref{
		int main(int argc,char* argv[] );
	}
	namespace odbc_bind_param{
		int main(int argc,char* argv[] );
	}
	namespace odbc_table{
		int main(int argc,char* argv[] );
	}
	namespace odbc_connnect_ref{
		int main(int argc,char* argv[] );
	}
	namespace odbc_put_data{
		int main(int argc,char* argv[] );
	}
	namespace odbc_table{
		int main(int argc,char* argv[] );
	}
	
	//-----Socket
	namespace socket_tcp_server{
		int main(int argc,char* argv[] );
	}
	namespace socket_tcp_client{
		int main(int argc,char* argv[] );
	}
	namespace socket_udp_server{
		int main(int argc,char* argv[] );
	}
	namespace socket_udp_client{
		int main(int argc,char* argv[] );
	}
	//-----线程
	namespace thread_mutex{
		int main(int argc,char* argv[] );
	}
	namespace thread_event{
		int main(int argc,char* argv[] );
	}
	namespace thread_critical{
		int main(int argc,char* argv[] );
	}
	namespace thread_critical_die{
		int main(int argc,char* argv[] );
	}
	
	//-----
	namespace other_chinese{
		int main(int argc,char* argv[] );
	}
	namespace other_judge{
		int main(int argc,char* argv[] );
	}
	

//#endif

