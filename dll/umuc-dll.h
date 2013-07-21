#ifdef UMUC_DLL_EXPORT
#define UMUC_DLL extern "C" __declspec(dllexport)
#else
#define UMUC_DLL extern "C" __declspec(dllimport)
#endif

UMUC_DLL void showMessage ();

//#ifdef EXPORT_API
//#define BASICDLL extern "C" __declspec(dllexport)
//#else
//#define BASICDLL extern "C" __declspec(dllimport)
//#endif
//
////
//// Function Declarations
////
//
//BASICDLL void ExecuteTarget();