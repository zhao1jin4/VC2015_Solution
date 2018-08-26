
// SQLBindCol_ref.cpp
// compile with: odbc32.lib
#include <windows.h>
#include <stdio.h>

#include <sqlext.h>

namespace odbc_bind_ref
{
	//手工测试OK,修改所有了WCHAR到CHAR...


	#define NAME_LEN 50
	#define PHONE_LEN 20

	void show_error() {
	   printf("error\n");
	}

	int main(int argc,char* argv[] )
	{
	   SQLHENV henv;
	   SQLHDBC hdbc;
	   SQLHSTMT hstmt = 0;
	   SQLRETURN retcode;
	   SQLCHAR szName[NAME_LEN], szPhone[PHONE_LEN], sCustID[NAME_LEN];
	   SQLLEN cbName = 0, cbCustID = 0, cbPhone = 0;

	   // Allocate environment handle
	   retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

	   // Set the ODBC version environment attribute
	   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		  retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0); 

		  // Allocate connection handle
		  if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			 retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

			 // Set login timeout to 5 seconds
			 if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

				// Connect to data source
				//retcode = SQLConnect(hdbc, (SQLWCHAR*) L"NorthWind", SQL_NTS, (SQLWCHAR*) NULL, 0, NULL, 0);
				retcode = SQLConnect(hdbc, L"myDataSource", SQL_NTS, L"sa",  SQL_NTS, L"sa", SQL_NTS);
				// Allocate statement handle
				if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) { 
				   retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); 

				   retcode = SQLExecDirect(hstmt, L"SELECT CustomerID, ContactName, Phone FROM CUSTOMERS ORDER BY 2, 1, 3", SQL_NTS);
				   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

					  // Bind columns 1, 2, and 3
					  retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, &sCustID, 100, &cbCustID);
					  retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, szName, NAME_LEN, &cbName);
					  retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, szPhone, PHONE_LEN, &cbPhone); 

					  // Fetch and print each row of data. On an error, display a message and exit.
					  for (int i=0; ; i++) {
						 retcode = SQLFetch(hstmt);
						 if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
							show_error();
						 if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
							printf("%d: %s %s %s\n", i + 1, sCustID, szName, szPhone);
						 else
							break;
					  }
				   }

				   // Process data
				   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
					  SQLCancel(hstmt);
					  SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
				   }

				   SQLDisconnect(hdbc);
				}

				SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
			 }
		  }
		  SQLFreeHandle(SQL_HANDLE_ENV, henv);
	   }
	   return 1;
	}
}