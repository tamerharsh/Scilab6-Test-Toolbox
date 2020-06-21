#ifndef __POINTCLOUD_TOOLBOX_GW_HXX__
#define __POINTCLOUD_TOOLBOX_GW_HXX__

#ifdef _MSC_VER
#ifdef POINTCLOUD_TOOLBOX_GW_EXPORTS
#define POINTCLOUD_TOOLBOX_GW_IMPEXP __declspec(dllexport)
#else
#define POINTCLOUD_TOOLBOX_GW_IMPEXP __declspec(dllimport)
#endif
#else
#define POINTCLOUD_TOOLBOX_GW_IMPEXP
#endif

extern "C" POINTCLOUD_TOOLBOX_GW_IMPEXP int POINTCLOUD_toolbox(wchar_t* _pwstFuncName);



#endif /* __POINTCLOUD_TOOLBOX_GW_HXX__ */
