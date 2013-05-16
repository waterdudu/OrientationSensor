// SFSimpleOrientationSensor.cpp : Implementation of CSFSimpleOrientationSensor

#include "stdafx.h"
#include "SFSimpleOrientationSensor.h"

// CSFSimpleOrientationSensor



STDMETHODIMP CSFSimpleOrientationSensor::TestEnableOrientationSensor(BOOL bEnable )
{
	DL_ENTER_FUNC_I();

	// TODO: Add your implementation code here
	if (bEnable)
	{
		OrientationState state = Orientation_Portrait;

		Fire_OrientationChanged(state);
	}
	return S_OK;
}

CSFSimpleOrientationSensor::~CSFSimpleOrientationSensor()
{
	DL_ENTER_FUNC_I();
}

CSFSimpleOrientationSensor::CSFSimpleOrientationSensor() 
{
	DL_ENTER_FUNC_I();

	m_SimpleOrientationSensor.SetSFSimpleOrientationSensorPtr(this);
}

void CSFSimpleOrientationSensor::DoOrientationSensor()
{
	DL_ENTER_FUNC_I();

	// The other alternative is to use WM_DISPLAYCHANGE notification, but it won't work when it's running in new Windows 8 UI mode.
	int iOrientation = m_SimpleOrientationSensor.GetOrientation();
	DL_T(_T(" [x] --------  iOrientation : %d"), iOrientation);

	AR_STATE autoRotationState;
	::GetAutoRotationState(&autoRotationState);
	// if auto rotation is disabled, use the current orientation instead of sensor value
	if (autoRotationState != AR_ENABLED)
	{
		DEVMODE devMode;
		ZeroMemory(&devMode, sizeof(devMode));
		devMode.dmSize = sizeof(devMode);
		if (0 != EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode))
		{
			switch (devMode.dmDisplayOrientation)
			{
			case 0:
				iOrientation = 0;
				break;
			case 1:
				iOrientation = 3;
				break;
			case 2:
				iOrientation = 2;
				break;
			case 3:
				iOrientation = 1;
				break;
			default:
				iOrientation = -1;
			}
		}
	}

	if (m_iOrientation != iOrientation && iOrientation >= 0 && iOrientation < 4)
	{ 
		m_iOrientation = iOrientation;
	}

	OrientationState state = GetOrientationState(iOrientation);

	Fire_OrientationChanged(state);

}

OrientationState CSFSimpleOrientationSensor::GetOrientationState( int i )
{
	OrientationState state = Orientation_Landscape;
	switch (i)
	{
	case 0:
		state = Orientation_Landscape;
		break;
	case 1:
		state = Orientation_Portrait;
		break;
	case 2:
		state = ORIENTATION_Landscape_Flip;  
		break;
	case 3:
		state = ORIENTATION_Portrait_Flip;
		break;
	default:
		break;
	}

	return state;
}

 