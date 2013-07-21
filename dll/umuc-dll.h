#ifdef UMUC_DLL_EXPORT
#define UMUC_DLL extern "C" __declspec(dllexport)
#else
#define UMUC_DLL extern "C" __declspec(dllimport)
#endif

UMUC_DLL void showMessage ();

