// SFSimpleOrientationSensor.h : Declaration of the CSFSimpleOrientationSensor

#pragma once
#include "resource.h"       // main symbols



#include "OrientationSensor_i.h"
#include "_ISFSimpleOrientationSensorEvents_CP.h"
#include "SimpleOrientationSensor.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CSFSimpleOrientationSensor

class ATL_NO_VTABLE CSFSimpleOrientationSensor :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSFSimpleOrientationSensor, &CLSID_SFSimpleOrientationSensor>,
	public IConnectionPointContainerImpl<CSFSimpleOrientationSensor>,
	public CProxy_ISFSimpleOrientationSensorEvents<CSFSimpleOrientationSensor>,
	public IDispatchImpl<ISFSimpleOrientationSensor, &IID_ISFSimpleOrientationSensor, &LIBID_OrientationSensorLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSFSimpleOrientationSensor();
	
	~CSFSimpleOrientationSensor();

DECLARE_REGISTRY_RESOURCEID(IDR_SFSIMPLEORIENTATIONSENSOR)


BEGIN_COM_MAP(CSFSimpleOrientationSensor)
	COM_INTERFACE_ENTRY(ISFSimpleOrientationSensor)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSFSimpleOrientationSensor)
	CONNECTION_POINT_ENTRY(__uuidof(_ISFSimpleOrientationSensorEvents))
END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	void DoOrientationSensor();
	OrientationState GetOrientationState(int i);
public:


//	STDMETHOD(OrientationChanged)(OrientationState* orientationState);
	//	STDMETHOD(TestEnableOrientationSensor)(BOOL bEnable, OrientationState* orientationState);
	STDMETHOD(TestEnableOrientationSensor)(BOOL bEnable);
public:
	SimpleOrientationSensor m_SimpleOrientationSensor;
	int m_iOrientation;
};

OBJECT_ENTRY_AUTO(__uuidof(SFSimpleOrientationSensor), CSFSimpleOrientationSensor)
