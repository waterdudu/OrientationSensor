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
embedded in Materials by Intel or Intel’s suppliers or licensors in any way.?
*/

#include "stdafx.h"
#include "SimpleOrientationSensor.h"

SimpleOrientationSensor::SimpleOrientationSensor(CSFSimpleOrientationSensor *pSFSimpleOrientationSensor)
{
 	// CoInitialize(NULL);
	m_pSFSimpleOrientationSensor = pSFSimpleOrientationSensor;
	m_pEventClass = NULL;
	m_pOrientationSensor = NULL;

	CComPtr<ISensorManager> pSensorManager;
	HRESULT hr = ::CoCreateInstance(CLSID_SensorManager, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pSensorManager));
	if (FAILED(hr))
		return;

	CComPtr<ISensorCollection> pSensorCollection;
	hr = pSensorManager->GetSensorsByType(SENSOR_TYPE_AGGREGATED_SIMPLE_DEVICE_ORIENTATION, &pSensorCollection);
	if (FAILED(hr))
	{
		::MessageBox(NULL, L"No Orientation Sensor", NULL, MB_OK);
		return;
	}
	ULONG ulCount = 0;
	hr = pSensorCollection->GetCount(&ulCount);
	if (FAILED(hr))
	{
		::MessageBox(NULL, L"No Orientation Sensor", NULL, MB_OK);
		return;
	}
	for (UINT i = 0; i < ulCount; i++)
	{
		CComPtr<ISensor> pSensor;
		hr = pSensorCollection->GetAt(i, &pSensor);
		if (SUCCEEDED(hr))
		{
			VARIANT_BOOL bSupported = VARIANT_FALSE;
			hr = pSensor->SupportsDataField(SENSOR_DATA_TYPE_SIMPLE_DEVICE_ORIENTATION, &bSupported);
			if (SUCCEEDED(hr) && bSupported == VARIANT_TRUE)
				m_pOrientationSensor = pSensor;
		}
	}

	if (m_pOrientationSensor == NULL)
	{
		::MessageBox(NULL, L"No Orientation Sensor", NULL, MB_OK);
		return;
	}

	m_pEventClass = new(std::nothrow) COrientationEvents(this);
	hr = m_pEventClass->QueryInterface(IID_PPV_ARGS(&m_pMyEvents));
	if(SUCCEEDED(hr))
	{
		// Start receiving events.
		hr = m_pOrientationSensor->SetEventSink(m_pMyEvents);
	} 
};

SimpleOrientationSensor::~SimpleOrientationSensor()
{
};

int SimpleOrientationSensor::GetOrientation()
{
	int res = -1;
	if (m_pOrientationSensor != NULL)
	{
		CComPtr<ISensorDataReport> pData;
		if (SUCCEEDED(m_pOrientationSensor->GetData(&pData)))
		{
			PROPVARIANT pv = {};
			if (SUCCEEDED(pData->GetSensorValue(SENSOR_DATA_TYPE_SIMPLE_DEVICE_ORIENTATION, &pv)))
			{
				if (pv.vt == VT_UI4)
				{
					res = pv.uiVal;
				}
			}
		}
	}

	return res;
};

void SimpleOrientationSensor::SetSFSimpleOrietationSensorPtr( CSFSimpleOrientationSensor *pSFSimpleOrientationSensor )
{
	m_pSFSimpleOrientationSensor = pSFSimpleOrientationSensor;
}

