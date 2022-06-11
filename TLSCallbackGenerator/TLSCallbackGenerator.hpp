#pragma once
#include <Windows.h>


#ifdef _WIN64

/* Create the first TLS Callback. */
#define CREATE_TLS_CALLBACK(func)	\
	_Pragma("comment (linker, \"/INCLUDE:_tls_used\")")	\
	_Pragma("comment (linker, \"/INCLUDE:tls_callback_func\")")	\
	_Pragma("const_seg(\".CRT$XLB\")")	\
	EXTERN_C const PIMAGE_TLS_CALLBACK tls_callback_func = (PIMAGE_TLS_CALLBACK)func; \
	_Pragma("const_seg()")	\

#else

/* Create the first TLS Callback. */
#define CREATE_TLS_CALLBACK(func) \
	_Pragma("comment (linker, \"/INCLUDE:__tls_used\")")	\
	_Pragma("comment (linker, \"/INCLUDE:_tls_callback_func\")"); \
	_Pragma("data_seg(\".CRT$XLB\")"); \
	EXTERN_C PIMAGE_TLS_CALLBACK tls_callback_func = (PIMAGE_TLS_CALLBACK)func; \
	_Pragma("data_seg()"); \

#endif

/*
	Insert another function in runtime to the TLS Callback table of the current Module at index.
*/
#define ADD_SECRET_TLS_CALLBACK(func, index)	\
	if (true)	\
	{	\
		DWORD TLSCALLBACK_dwOldProtection;	\
		char* TLSCALLBACK_hBase = (char*)GetModuleHandle(NULL);	\
		PIMAGE_DOS_HEADER TLSCALLBACK_hImageDosHeader = (PIMAGE_DOS_HEADER)TLSCALLBACK_hBase;	\
		PIMAGE_NT_HEADERS TLSCALLBACK_hImageNtHeaders = (PIMAGE_NT_HEADERS)(TLSCALLBACK_hBase + TLSCALLBACK_hImageDosHeader->e_lfanew);	\
		DWORD TLSCALLBACK_TlsDataDirectoryVirtualAddress = TLSCALLBACK_hImageNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress;	\
		PIMAGE_TLS_DIRECTORY TLSCALLBACK_hTlsDirectory = (PIMAGE_TLS_DIRECTORY)(TLSCALLBACK_hBase + TLSCALLBACK_TlsDataDirectoryVirtualAddress);	\
		UINT_PTR* TLSCALLBACK_hCallbackArray = (UINT_PTR*)TLSCALLBACK_hTlsDirectory->AddressOfCallBacks;	\
		VirtualProtect((LPVOID)(&TLSCALLBACK_hCallbackArray[index]), sizeof(UINT_PTR), PAGE_READWRITE, &TLSCALLBACK_dwOldProtection);	\
		TLSCALLBACK_hCallbackArray[index] = (UINT_PTR)func;	\
		VirtualProtect((LPVOID)(&TLSCALLBACK_hCallbackArray[index]), sizeof(UINT_PTR), TLSCALLBACK_dwOldProtection, &TLSCALLBACK_dwOldProtection);	\
	}	

/*
	Remove function in runtime from the TLS Callback table of the current Module at index.
*/
#define REMOVE_SECRET_TLS_CALLBACK_BY_INDEX(index)	\
	if (true)	\
	{	\
		DWORD TLSCALLBACK_dwOldProtection;	\
		char* TLSCALLBACK_hBase = (char*)GetModuleHandle(NULL);	\
		PIMAGE_DOS_HEADER TLSCALLBACK_hImageDosHeader = (PIMAGE_DOS_HEADER)TLSCALLBACK_hBase;	\
		PIMAGE_NT_HEADERS TLSCALLBACK_hImageNtHeaders = (PIMAGE_NT_HEADERS)(TLSCALLBACK_hBase + TLSCALLBACK_hImageDosHeader->e_lfanew);	\
		DWORD TLSCALLBACK_TlsDataDirectoryVirtualAddress = TLSCALLBACK_hImageNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress;	\
		PIMAGE_TLS_DIRECTORY TLSCALLBACK_hTlsDirectory = (PIMAGE_TLS_DIRECTORY)(TLSCALLBACK_hBase + TLSCALLBACK_TlsDataDirectoryVirtualAddress);	\
		UINT_PTR* TLSCALLBACK_hCallbackArray = (UINT_PTR*)TLSCALLBACK_hTlsDirectory->AddressOfCallBacks;	\
		VirtualProtect((LPVOID)(&TLSCALLBACK_hCallbackArray[index]), sizeof(UINT_PTR), PAGE_READWRITE, &TLSCALLBACK_dwOldProtection);	\
		TLSCALLBACK_hCallbackArray[index] = (UINT_PTR)0;	\
		VirtualProtect((LPVOID)(&TLSCALLBACK_hCallbackArray[index]), sizeof(UINT_PTR), TLSCALLBACK_dwOldProtection, &TLSCALLBACK_dwOldProtection);	\
	}
