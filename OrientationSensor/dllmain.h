// dllmain.h : Declaration of module class.

class COrientationSensorModule : public ATL::CAtlDllModuleT< COrientationSensorModule >
{
public :
	DECLARE_LIBID(LIBID_OrientationSensorLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ORIENTATIONSENSOR, "{15544C4B-D32D-4BAB-B262-7302EA64C602}")
};

extern class COrientationSensorModule _AtlModule;
