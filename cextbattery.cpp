#include "pch.h"

#include "cextbattery.h"


CExtBattery::CExtBattery(double m_capacity, double m_voltage, double m_chargelevel)
{
	if (m_chargelevel <= 0.1*m_capacity || m_chargelevel >= m_capacity)
	{
		throw DischargeExtBatteryException();
	}
	else
	{
		m_EChargeSum = m_chargelevel;
		m_ECapacity = m_capacity;
		m_EVoltage = m_chargelevel;
		m_EChargeLevel = m_voltage;
	}
};
// change constructors so that there is no way battery will drop to 10% of capacitance

bool CExtBattery::Discharge(double mAh)
{
	// function disscharging
	// function returns type double if it fails to decrease the load by given value
	if (m_EChargeLevel - mAh <= 0.1*m_ECapacity)
	{
		throw DischargeExtBatteryException();
		return mAh;
	}
	else
	{
		m_EChargeLevel -= mAh;
		return true;
	}
}

void CExtBattery::DischargeFor(double Current, double Time)
// as in charging but decreasing the load 
{
	if (m_EChargeLevel - (Current*(Time / 60)) <= 0)
	{
		throw DischargeExtBatteryException();
		return (Current*(Time / 60));
	}
	else
	{
		m_EChargeLevel -= (Current*(Time / 60));
		return true;
	}
}

CExtBattery& CExtBattery::operator-=(const double amh)
{
	if (m_EChargeLevel - amh <= 0.1*m_ECapacity)
	{
		throw DischargeExtBatteryException;
	}
	else
	{
		this->m_EChargeLevel -= amh;

	}
	return *this;
}

int CExtBattery::GetChargeCycles()
{
	return m_CyclesCounter;
}

void CExtBattery::Charge(double mAh) // function that changes current load for a certain value(mAh)
{
	if (m_EChargeLevel + (Current*(Time / 60)) >= m_ECapacity)
	{
		m_EChargeSum =
			m_EChargeLevel = m_ECapacity;
	}
	else
	{

		m_EChargeLevel += mAh;
	}
}

void CExtBattery::ChargeFor(double Current, double Time)
{
	// variable Time is  equal to time in minutes
	// function  loading accumulator by current in mA in time expresed in minutes
	// the load charged is equal to time(hours)* current(mA)
	m_ChargeLevel += (Current*(Time / 60));
	if (m_ChargeLevel + (Current*(Time / 60)) >= m_Capacity)
	{
		m_ChargeLevel = m_Capacity;
		return (Current*(Time / 60));
	}
	else
	{
		m_ChargeLevel += (Current*(Time / 60));
		return true;
	}
}