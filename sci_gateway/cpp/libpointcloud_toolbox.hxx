#ifndef __LIBPOINTCLOUD_TOOLBOX_GW_HXX__
#define __LIBPOINTCLOUD_TOOLBOX_GW_HXX__

#ifdef _MSC_VER
#ifdef LIBPOINTCLOUD_TOOLBOX_GW_EXPORTS
#define LIBPOINTCLOUD_TOOLBOX_GW_IMPEXP __declspec(dllexport)
#else
#define LIBPOINTCLOUD_TOOLBOX_GW_IMPEXP __declspec(dllimport)
#endif
#else
#define LIBPOINTCLOUD_TOOLBOX_GW_IMPEXP
#endif

extern "C" LIBPOINTCLOUD_TOOLBOX_GW_IMPEXP int libpointcloud_toolbox(wchar_t* _pwstFuncName);








#endif /* __LIBPOINTCLOUD_TOOLBOX_GW_HXX__ */
