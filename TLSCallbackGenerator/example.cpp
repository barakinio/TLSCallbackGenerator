#include <Windows.h>
#include "TLSCallbackGenerator.hpp"


void tls_callback(PVOID hModule, DWORD dwReason, PVOID pContext);
void secret_tls_callback(PVOID hModule, DWORD dwReason, PVOID pContext);

CREATE_TLS_CALLBACK(tls_callback);



void tls_callback(PVOID hModule, DWORD dwReason, PVOID pContext)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		MessageBox(0, L"First TLS Callback", L"TLS", 0);

		ADD_SECRET_TLS_CALLBACK(secret_tls_callback, 1);

	}
}


void secret_tls_callback(PVOID hModule, DWORD dwReason, PVOID pContext)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		MessageBox(0, L"Secret TLS Callback", L"TLS", 0);

	}
}



int main()
{
	MessageBox(0, L"Main", L"Main", 0);


	return 0;
}