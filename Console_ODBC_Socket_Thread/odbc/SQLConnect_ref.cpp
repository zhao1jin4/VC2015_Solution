//�ֹ�����OK

// SQLConnect_ref.cpp
// compile with: odbc32.lib
#include <windows.h>
#include <sqlext.h>
namespace odbc_connnect_ref
{

int main(int argc,char* argv[] )
{
   SQLHENV henv;
   SQLHDBC hdbc;
   SQLHSTMT hstmt;
   SQLRETURN retcode;

   SQLCHAR * OutConnStr = (SQLCHAR * )malloc(255);
   SQLSMALLINT * OutConnStrLen = (SQLSMALLINT *)malloc(255);

   // Allocate environment handle
   retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

   // Set the ODBC version environment attribute
   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
      retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0); 

      // Allocate connection handle
      if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
         retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc); 

         // Set login timeout to 5 seconds
         if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

            // Connect to data source
            //retcode = SQLConnect(hdbc,L"myDataSource", SQL_NTS, (SQLWCHAR*) NULL, 0, NULL, 0);
			retcode = SQLConnect(hdbc, L"myDataSource", SQL_NTS,L"sa",  SQL_NTS,L"sa", SQL_NTS);//�û�DSN��������SQLServer�û���������,����ҲҪд�û���������

            // Allocate statement handle
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
               retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); 

               // Process data
               if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
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