#include <wchar.h>
#include "libpointcloud_toolbox.hxx"
extern "C"
{
#include "libpointcloud_toolbox.h"
#include "addfunction.h"
}

#define MODULE_NAME L"libpointcloud_toolbox"

int libpointcloud_toolbox(wchar_t* _pwstFuncName)
{
    if(wcscmp(_pwstFuncName, L"writepc") == 0){ addCFunction(L"writepc", &sci_writepc, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"viewpc") == 0){ addCFunction(L"viewpc", &sci_viewpc, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"readpc") == 0){ addCFunction(L"readpc", &sci_readpc, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"concatpc") == 0){ addCFunction(L"concatpc", &sci_concatpc, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"pc2png") == 0){ addCFunction(L"pc2png", &sci_pc2png, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"viewmonopc") == 0){ addCFunction(L"viewmonopc", &sci_viewmonopc, MODULE_NAME); }

    return 1;
}
