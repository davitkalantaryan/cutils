//
// file:            main_win_function_changer.cpp
// path:			src/tests/main_win_function_changer.cpp
// created on:		2023 Mar 08
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cinternal/export_symbols.h>
#include <stdio.h>
#include <cinternal/disable_compiler_warnings.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <Psapi.h>
#include <winternl.h>

#ifdef _WIN64
typedef ULONGLONG   CINT_TYPE_FNC;
#else
typedef DWORD   CINT_TYPE_FNC;
#endif


//#define FUNCTION_TO_HOOK  "HookedNtQuerySystemInformation"
#define FUNCTION_TO_HOOK  "malloc"

#ifdef _DEBUG
#define CRASH_INVEST_CRUN_LIB	"ucrtbased.dll"
#else
#define CRASH_INVEST_CRUN_LIB	"ucrtbase.dll"
#endif

typedef void* (*TypeMallocFnc)(size_t);

static TypeMallocFnc    s_originalMalloc;


void StartHook(const char* a_funcname, CINT_TYPE_FNC a_newFuncAddress);


static void* MyMalloc(size_t a_size)
{
    void* pRet = (*s_originalMalloc)(a_size);
    return pRet;
}


int main(void)
{
    HMODULE cranLib = LoadLibraryA(CRASH_INVEST_CRUN_LIB);
    if (!cranLib) {
        return 1;
    }
    
    s_originalMalloc = (TypeMallocFnc)GetProcAddress(cranLib, FUNCTION_TO_HOOK);
    if (!s_originalMalloc) {
        return 1;
    }

    StartHook(FUNCTION_TO_HOOK, (ULONGLONG)((size_t)&MyMalloc));

    void* pMem = malloc(100);
    printf("pMem = %p\n", pMem);
    free(pMem);

    FreeLibrary(cranLib);

	return 0;
}



bool MakeHookForModule(LPBYTE a_pAddress, PIMAGE_IMPORT_DESCRIPTOR a_pIID, const char* a_funcname, CINT_TYPE_FNC a_newFuncAddress)
{
    bool bNotFound = true;
    char szAddress[64];
    // Search for a_funcname
    PIMAGE_THUNK_DATA pITD = (PIMAGE_THUNK_DATA)(a_pAddress + a_pIID->OriginalFirstThunk);
    PIMAGE_THUNK_DATA pFirstThunkTest = (PIMAGE_THUNK_DATA)((a_pAddress + a_pIID->FirstThunk));
    PIMAGE_IMPORT_BY_NAME pIIBM = NULL;

    for (; !(pITD->u1.Ordinal & IMAGE_ORDINAL_FLAG) && pITD->u1.AddressOfData; pITD++) {
        pIIBM = (PIMAGE_IMPORT_BY_NAME)(a_pAddress + pITD->u1.AddressOfData);
        if (!strcmp(a_funcname, (char*)(pIIBM->Name))) {
            bNotFound = false;
            break;
        }
        pFirstThunkTest++;
    }

    if (bNotFound) {
        return false;
    }

    // Write over function pointer
    DWORD dwOld = NULL;
    VirtualProtect((LPVOID) & (pFirstThunkTest->u1.Function), sizeof(CINT_TYPE_FNC), PAGE_READWRITE, &dwOld);
    pFirstThunkTest->u1.Function = a_newFuncAddress;
    VirtualProtect((LPVOID) & (pFirstThunkTest->u1.Function), sizeof(CINT_TYPE_FNC), dwOld, NULL);

    sprintf_s(szAddress, 63, "%s 0x%zX", (char*)(pIIBM->Name), (size_t)pFirstThunkTest->u1.Function);

#if 0
    if (a_pIDH->e_magic == IMAGE_DOS_SIGNATURE)
        MessageBox(NULL, szAddress, "TEST", MB_OK);
    else
        MessageBox(NULL, "FAIL", "FAIL", MB_OK);
#endif

    //CloseHandle(hModule);

    return true;
}


void StartHook(const char* a_funcname, CINT_TYPE_FNC a_newFuncAddress) {
    MODULEINFO modInfo = { 0 };
    HMODULE hModule = GetModuleHandle(0);

    // Find the base address
    GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));

    // Find Import Directory
    LPBYTE pAddress = (LPBYTE)modInfo.lpBaseOfDll;
    PIMAGE_DOS_HEADER pIDH = (PIMAGE_DOS_HEADER)pAddress;

    PIMAGE_NT_HEADERS pINH = (PIMAGE_NT_HEADERS)(pAddress + pIDH->e_lfanew);
    PIMAGE_OPTIONAL_HEADER pIOH = (PIMAGE_OPTIONAL_HEADER) & (pINH->OptionalHeader);
    PIMAGE_IMPORT_DESCRIPTOR pIID = (PIMAGE_IMPORT_DESCRIPTOR)(pAddress + pIOH->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

    // Find ntdll.dll
    for (; pIID->Characteristics; pIID++) {
        //if (!strcmp("ntdll.dll", (char*)(pAddress + pIID->Name)))
        //    break;
        MakeHookForModule(pAddress, pIID, a_funcname, a_newFuncAddress);
    }

    //// Search for NtQuerySystemInformation
    //PIMAGE_THUNK_DATA pITD = (PIMAGE_THUNK_DATA)(pAddress + pIID->OriginalFirstThunk);
    //PIMAGE_THUNK_DATA pFirstThunkTest = (PIMAGE_THUNK_DATA)((pAddress + pIID->FirstThunk));
    //PIMAGE_IMPORT_BY_NAME pIIBM;
    //
    //for (; !(pITD->u1.Ordinal & IMAGE_ORDINAL_FLAG) && pITD->u1.AddressOfData; pITD++) {
    //    pIIBM = (PIMAGE_IMPORT_BY_NAME)(pAddress + pITD->u1.AddressOfData);
    //    if (!strcmp("NtQuerySystemInformation", (char*)(pIIBM->Name)))
    //        break;
    //    pFirstThunkTest++;
    //}
    //
    //// Write over function pointer
    //DWORD dwOld = NULL;
    //VirtualProtect((LPVOID) & (pFirstThunkTest->u1.Function), sizeof(DWORD), PAGE_READWRITE, &dwOld);
    //pFirstThunkTest->u1.Function = (DWORD)HookedNtQuerySystemInformation;
    //VirtualProtect((LPVOID) & (pFirstThunkTest->u1.Function), sizeof(DWORD), dwOld, NULL);
    //
    //sprintf(szAddress, "%s 0x%X", (char*)(pIIBM->Name), pFirstThunkTest->u1.Function);
    //
    //if (pIDH->e_magic == IMAGE_DOS_SIGNATURE)
    //    MessageBox(NULL, szAddress, "TEST", MB_OK);
    //else
    //    MessageBox(NULL, "FAIL", "FAIL", MB_OK);
    //
    ////CloseHandle(hModule);
}


NTSTATUS WINAPI HookedNtQuerySystemInformation(
    __in       SYSTEM_INFORMATION_CLASS SystemInformationClass,
    __inout    PVOID                    SystemInformation,
    __in       ULONG                    SystemInformationLength,
    __out_opt  PULONG                   ReturnLength) 
{
    (void)SystemInformationClass;
    (void)SystemInformation;
    (void)SystemInformationLength;
    (void)ReturnLength;
    return 0;
}


void StartHookForHookedNtQuerySystemInformation() {
    MODULEINFO modInfo = { 0 };
    HMODULE hModule = GetModuleHandle(0);
    PIMAGE_IMPORT_BY_NAME pIIBM = NULL;

    // Find the base address
    GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));

    char szAddress[64];

    // Find Import Directory
    LPBYTE pAddress = (LPBYTE)modInfo.lpBaseOfDll;
    PIMAGE_DOS_HEADER pIDH = (PIMAGE_DOS_HEADER)pAddress;

    PIMAGE_NT_HEADERS pINH = (PIMAGE_NT_HEADERS)(pAddress + pIDH->e_lfanew);
    PIMAGE_OPTIONAL_HEADER pIOH = (PIMAGE_OPTIONAL_HEADER) & (pINH->OptionalHeader);
    PIMAGE_IMPORT_DESCRIPTOR pIID = (PIMAGE_IMPORT_DESCRIPTOR)(pAddress + pIOH->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

    // Find ntdll.dll
    for (; pIID->Characteristics; pIID++) {
        if (!strcmp("ntdll.dll", (char*)(pAddress + pIID->Name)))
            break;
    }

    // Search for NtQuerySystemInformation
    PIMAGE_THUNK_DATA pITD = (PIMAGE_THUNK_DATA)(pAddress + pIID->OriginalFirstThunk);
    PIMAGE_THUNK_DATA pFirstThunkTest = (PIMAGE_THUNK_DATA)((pAddress + pIID->FirstThunk));

    for (; !(pITD->u1.Ordinal & IMAGE_ORDINAL_FLAG) && pITD->u1.AddressOfData; pITD++) {
        pIIBM = (PIMAGE_IMPORT_BY_NAME)(pAddress + pITD->u1.AddressOfData);
        if (!strcmp("NtQuerySystemInformation", (char*)(pIIBM->Name)))
            break;
        pFirstThunkTest++;
    }

    // Write over function pointer
    DWORD dwOld = NULL;
    VirtualProtect((LPVOID) & (pFirstThunkTest->u1.Function), sizeof(DWORD), PAGE_READWRITE, &dwOld);
    pFirstThunkTest->u1.Function = (ULONGLONG)((size_t)HookedNtQuerySystemInformation);
    VirtualProtect((LPVOID) & (pFirstThunkTest->u1.Function), sizeof(DWORD), dwOld, NULL);

    sprintf_s(szAddress, 63, "%s 0x%zX", (char*)(pIIBM->Name), (size_t)pFirstThunkTest->u1.Function);

#if 0
    if (pIDH->e_magic == IMAGE_DOS_SIGNATURE)
        MessageBox(NULL, szAddress, "TEST", MB_OK);
    else
        MessageBox(NULL, "FAIL", "FAIL", MB_OK);
#endif

    CloseHandle(hModule);
}

