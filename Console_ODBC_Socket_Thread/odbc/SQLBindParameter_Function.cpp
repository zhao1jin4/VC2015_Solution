//≤‚ ‘OK

// SQLBindParameter_Function.cpp
// compile with: ODBC32.lib
#include <windows.h>
#include <sqltypes.h>
#include <sqlext.h>

namespace odbc_bind_param
{

#define EMPLOYEE_ID_LEN 10

SQLHENV henv = NULL;
SQLHDBC hdbc = NULL;
SQLRETURN retcode;
SQLHSTMT hstmt = NULL;
SQLSMALLINT sCustID;

SQLCHAR szEmployeeID[EMPLOYEE_ID_LEN];
SQL_DATE_STRUCT dsOrderDate;
SQLINTEGER cbCustID = 0, cbOrderDate = 0, cbEmployeeID = SQL_NTS;

int main(int argc,char* argv[] ) {
   retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
   retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0); 

   retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc); 
   retcode = SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

  // retcode = SQLConnect(hdbc,L"Northwind", SQL_NTS, (SQLWCHAR*) NULL, 0, NULL, 0);
   retcode = SQLConnect(hdbc,L"myDataSource", SQL_NTS, L"sa",  SQL_NTS, L"sa", SQL_NTS);
   retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

   retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, EMPLOYEE_ID_LEN, 0, szEmployeeID, 0, &cbEmployeeID);
   retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sCustID, 0, &cbCustID);
   retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_TYPE_DATE, SQL_TIMESTAMP, sizeof(dsOrderDate), 0, &dsOrderDate, 0, &cbOrderDate);

   retcode = SQLPrepare(hstmt, L"INSERT INTO Orders(CustomerID, EmployeeID, OrderDate) VALUES (?, ?, ?)", SQL_NTS);

   strcpy_s((char*)szEmployeeID, _countof(szEmployeeID), "BERGS");
   sCustID = 5;
   dsOrderDate.year = 2006;
   dsOrderDate.month = 3;
   dsOrderDate.day = 17;

   retcode = SQLExecute(hstmt);
   //select * from orders where CustomerID='BERGS' and EmployeeID=5

  
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	}

	SQLDisconnect(hdbc);
          
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);

	return 1;
}

}