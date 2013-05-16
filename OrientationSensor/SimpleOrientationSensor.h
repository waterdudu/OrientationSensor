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

#pragma once
#include "stdafx.h"
#include <initguid.h>
#include <SensorsApi.h>
#include <sensors.h>
#include "OrientationEvents.h"
using namespace ATL;

class CSFSimpleOrientationSensor;

class SimpleOrientationSensor
{
public:
	SimpleOrientationSensor(CSFSimpleOrientationSensor *pSFSimpleOrientationSensor = NULL);
	~SimpleOrientationSensor();
	void SetSFSimpleOrietationSensorPtr(CSFSimpleOrientationSensor *pSFSimpleOrientationSensor);
	int GetOrientation();
	void SetSFSimpleOrientationSensorPtr(CSFSimpleOrientationSensor *pSFSimpleOrientationSensor)
	{
		m_pSFSimpleOrientationSensor = pSFSimpleOrientationSensor;
	}
	
public:
	CSFSimpleOrientationSensor * m_pSFSimpleOrientationSensor;
	CComPtr<ISensor> m_pOrientationSensor;
	CComPtr<ISensorEvents> m_pMyEvents;
	COrientationEvents *m_pEventClass;
};