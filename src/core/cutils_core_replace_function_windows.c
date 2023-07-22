//
// repo:            cutils
// file:            cutils_core_replace_function_windows.c
// path:			src/core/windows/cutils_core_replace_function_windows.c
// created on:		2023 Mar 08
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/internal_header.h>

#ifdef _WIN32

#include <cutils/replace_function_sys.h>
#include <string.h>
#include <cinternal/disable_compiler_warnings.h>
#include <Psapi.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C


struct CPPUTILS_DLL_PRIVATE SReplaceDataInitial {
    LPBYTE                      pAddress;
    PIMAGE_DOS_HEADER           pIDH;
    PIMAGE_NT_HEADERS           pINH;
    PIMAGE_OPTIONAL_HEADER      pIOH;
    PIMAGE_IMPORT_DESCRIPTOR    pIID;
};

static void MakeHookForModule(LPBYTE a_pAddress, PIMAGE_IMPORT_DESCRIPTOR a_pIID, size_t a_count,struct SCInternalReplaceFunctionData* a_replaceData);


static inline void CInternalReplaceFunctionsForModulePrepareDataInline(HMODULE a_hModule, struct SReplaceDataInitial* CPPUTILS_ARG_NONULL a_pData,
                size_t a_count, struct SCInternalReplaceFunctionData* a_replaceData) {
    size_t ind;
    MODULEINFO modInfo = { 0 };
    // Find the base address
    GetModuleInformation(GetCurrentProcess(), a_hModule, &modInfo, sizeof(MODULEINFO));
    // Find Import Directory
    a_pData->pAddress = (LPBYTE)(modInfo.lpBaseOfDll);
    a_pData->pIDH = (PIMAGE_DOS_HEADER)(a_pData->pAddress);
    a_pData->pINH = (PIMAGE_NT_HEADERS)(a_pData->pAddress + a_pData->pIDH->e_lfanew);
    a_pData->pIOH = (PIMAGE_OPTIONAL_HEADER) & (a_pData->pINH->OptionalHeader);
    a_pData->pIID = (PIMAGE_IMPORT_DESCRIPTOR)(a_pData->pAddress + a_pData->pIOH->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

    for (ind = 0; ind < a_count; ++ind) {
        a_replaceData[ind].bFound = false;
    }
}


static inline void CInternalReplaceFunctionsForModuleInline(HMODULE a_hModule,size_t a_count, struct SCInternalReplaceFunctionData* a_replaceData) {
    struct SReplaceDataInitial moduleData;

    CInternalReplaceFunctionsForModulePrepareDataInline(a_hModule, &moduleData, a_count, a_replaceData);

    if ((moduleData.pIID->Name) != 0xffff) {
        for (; moduleData.pIID->Characteristics; ++(moduleData.pIID)) {
            // Find ntdll.dll
            //if (!strcmp("ntdll.dll", (char*)(pAddress + pIID->Name)))
            //    break;
            MakeHookForModule(moduleData.pAddress, moduleData.pIID, a_count, a_replaceData);
        }  //  for (; moduleData.pIID->Characteristics; ++(moduleData.pIID)) {
    }  // if ((moduleData.pIID->Name) != 0xffff) {
}


CUTILS_EXPORT void CInternalReplaceFunctionsForModule(HMODULE a_hModule, size_t a_count, struct SCInternalReplaceFunctionData* a_replaceData)
{
    CInternalReplaceFunctionsForModuleInline(a_hModule, a_count, a_replaceData);
}


CUTILS_EXPORT void CInternalReplaceFunctionsAllModules(size_t a_count, struct SCInternalReplaceFunctionData* a_replaceData)
{
    DWORD cbNeededIn, cbNeededOut;
    HMODULE hMod;
    HMODULE* pMods;
    DWORD dwFinalSize, i;
    const HANDLE curProcHeap = GetProcessHeap();
    const HANDLE curProcHandle = GetCurrentProcess();
    
    if (!EnumProcessModules(curProcHandle, &hMod, 0, &cbNeededIn)) {
        return;
    }

    pMods = (HMODULE*)HeapAlloc(curProcHeap, 0, (SIZE_T)cbNeededIn);
    if (!pMods) {
        return;
    }

    if (!EnumProcessModules(curProcHandle, pMods, cbNeededIn, &cbNeededOut)) {
        return;
    }

    dwFinalSize = (cbNeededIn < cbNeededOut) ? (cbNeededIn/ sizeof(HMODULE)) : (cbNeededOut / sizeof(HMODULE));

    for (i = 0; i < dwFinalSize; ++i) {
        CInternalReplaceFunctionsForModuleInline(pMods[i], a_count, a_replaceData);
    }

    HeapFree(curProcHeap, 0, pMods);
}


CUTILS_EXPORT void CInternalReplaceFunctions(size_t a_count, struct SCInternalReplaceFunctionData* a_replaceData) 
{
    HMODULE hModule = GetModuleHandleA(0);
    CInternalReplaceFunctionsForModuleInline(hModule, a_count, a_replaceData);
}


static void MakeHookForModule(LPBYTE a_pAddress, PIMAGE_IMPORT_DESCRIPTOR a_pIID, size_t a_count, struct SCInternalReplaceFunctionData* a_replaceData)
{
    DWORD dwOld, dwOldTmp;
    size_t ind;
    // Search for a_funcname
    PIMAGE_THUNK_DATA pITD;
    PIMAGE_THUNK_DATA pFirstThunkTest;
    PIMAGE_IMPORT_BY_NAME pIIBM;

    for (ind = 0; ind < a_count; ++ind) {
        pITD = (PIMAGE_THUNK_DATA)(a_pAddress + a_pIID->OriginalFirstThunk);
        pFirstThunkTest = (PIMAGE_THUNK_DATA)((a_pAddress + a_pIID->FirstThunk));

        for (; !(pITD->u1.Ordinal & IMAGE_ORDINAL_FLAG) && pITD->u1.AddressOfData; ++pITD) {
            pIIBM = (PIMAGE_IMPORT_BY_NAME)(a_pAddress + pITD->u1.AddressOfData);
            if (!strcmp(a_replaceData[ind].funcname, (const char*)(pIIBM->Name))) {
                VirtualProtect((LPVOID) & (pFirstThunkTest->u1.Function), sizeof(size_t), PAGE_READWRITE, &dwOld);
                if ((((const void*)(pFirstThunkTest->u1.Function)) == a_replaceData[ind].replaceIfAddressIs) || (!(a_replaceData[ind].replaceIfAddressIs))) {
                    a_replaceData[ind].replaceIfAddressIs = (const void*)pFirstThunkTest->u1.Function;
                    pFirstThunkTest->u1.Function = (size_t)a_replaceData[ind].newFuncAddress;
                    a_replaceData[ind].bFound = true;
                }
                VirtualProtect((LPVOID) & (pFirstThunkTest->u1.Function), sizeof(size_t), dwOld, &dwOldTmp);
                break; 
            }  //  if (!strcmp(a_replaceData->funcname, (const char*)(pIIBM->Name))) {
            pFirstThunkTest++;
        }  //  for (; !(pITD->u1.Ordinal & IMAGE_ORDINAL_FLAG) && pITD->u1.AddressOfData; pITD++) {
    }  //  for (ind = 0; ind < a_count; ++ind) {

}


CPPUTILS_END_C


#endif  //  #ifdef _WIN32
