/*
copyright (2013) Intel Corporation All Rights Reserved.

The source code, information and material ("Material") contained herein is owned by Intel Corporation or 
its suppliers or licensors, and title to such Material remains with Intel Corporation or its suppliers or 
licensors. The Material contains proprietary information of Intel or its suppliers and licensors. 
The Material is protected by worldwide copyright laws and treaty provisions. No part of the Material may 
be used, copied, reproduced, modified, published, uploaded, posted, transmitted, distributed or disclosed 
in any way without Intel's prior express written permission. No license under any patent, copyright or 
other intellectual property rights in the Material is granted to or conferred upon you, either expressly, 
by implication, inducement, estoppel or otherwise. Any license under such intellectual property rights must
be express and approved by Intel in writing.

Unless otherwise agreed by Intel in writing, you may not remove or alter this notice or any other notice 
embedded in Materials by Intel or Intel suppliers or licensors in any way.?
*/

#include "stdafx.h"
#include "OrientationEvents.h"

#include "SFSimpleOrientationSensor.h"
extern void NotifyOrientationChange();

COrientationEvents::COrientationEvents(SimpleOrientationSensor * pSimpleOrientationSensor)
{
	m_pSimpleOrientationSensor = pSimpleOrientationSensor;
}


COrientationEvents::~COrientationEvents(void)
{
}

STDMETHODIMP COrientationEvents::QueryInterface(REFIID iid, void** ppv)
{
	if (ppv == NULL)
	{
		return E_POINTER;
	}
	if (iid == __uuidof(IUnknown))
	{
		*ppv = static_cast<IUnknown*>(this);
	}
	else if (iid == __uuidof(ISensorEvents))
	{
		*ppv = static_cast<ISensorEvents*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}


STDMETHODIMP_(ULONG) COrientationEvents::AddRef()
{
	return InterlockedIncrement(&m_cRef); 
}

STDMETHODIMP_(ULONG) COrientationEvents::Release()
{
	ULONG count = InterlockedDecrement(&m_cRef);
	if (count == 0)
	{
		delete this;
		return 0;
	}
	return count;
}


//
// ISensorEvents methods.
//

STDMETHODIMP COrientationEvents::OnEvent(
	ISensor *pSensor,
	REFGUID eventID,
	IPortableDeviceValues *pEventData)
{
	HRESULT hr = S_OK;

	// Handle custom events here.

	return hr;
}


STDMETHODIMP COrientationEvents::OnDataUpdated(
	ISensor *pSensor,
	ISensorDataReport *pNewData)
{
	DL_ENTER_FUNC_I();
	DL_T(_T(" [x] on data update"));

	HRESULT hr = S_OK;

	if(NULL == pNewData ||
		NULL == pSensor)
	{
		return E_INVALIDARG;
	}

	// NotifyOrientationChange();
	// call CSFSimpleOrientationSensor's method

	CSFSimpleOrientationSensor * p = (CSFSimpleOrientationSensor *)m_pSimpleOrientationSensor->m_pSFSimpleOrientationSensor;
	p->DoOrientationSensor();

	return hr;
}

STDMETHODIMP COrientationEvents::OnLeave(
	REFSENSOR_ID sensorID)
{
	HRESULT hr = S_OK;

	return hr;
}


STDMETHODIMP COrientationEvents::OnStateChanged(
	ISensor* pSensor,
	SensorState state)
{
	HRESULT hr = S_OK;

	if(NULL == pSensor)
	{
		return E_INVALIDARG;
	}


	if(state == SENSOR_STATE_READY)
	{
		wprintf_s(L"\nOrientation sensor is now ready.");
	}
	else if(state == SENSOR_STATE_ACCESS_DENIED)
	{
		wprintf_s(L"\nNo permission for the orientation sensor.\n");
		wprintf_s(L"Enable the sensor in the control panel.\n");
	}


	return hr;
}