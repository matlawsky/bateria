#include "cbattery.h"
#include "pch.h"


//copy constructor
CBattery::CBattery(const CBattery &battery)
{
	m_Capacity = battery.m_Capacity;
	m_ChargeLevel = battery.m_ChargeLevel;
	m_Voltage = battery.m_Voltage;
}

// default constructor creating object with default values
CBattery::CBattery()
{
	m_Capacity = 1000.0; //mAh
	m_Voltage = 3.7;
	m_ChargeLevel = 0.0;
}

//regular constructor
CBattery::CBattery(double m_capacity, double m_voltage, double m_chargelevel)
{
	if (m_chargelevel <= 0 || m_chargelevel >= m_capacity)
	{
		throw BatteryException();
	}
	else
	{
		m_Capacity = m_capacity;
		m_Voltage = m_chargelevel;
		m_ChargeLevel = m_voltage;
	}
}

// function that changes current load for a certain value(mAh)
void CBattery::Charge(double mAh)
{
	if (m_ChargeLevel + (Current*(Time / 60)) >= m_Capacity)
	{
		m_ChargeLevel = m_Capacity;
	}
	else
	{
		m_ChargeLevel += mAh;
	}
}

void CBattery::ChargeFor(double Current, double Time)
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

bool CBattery::Discharge(double mAh)
{
	// function disscharging
	// function returns type double if it fails to decrease the load by given value
	if (m_ChargeLevel - mAh <= 0)
	{
		return mAh;
	}
	else
	{
		m_ChargeLevel -= mAh;
		return true;
	}
}

void CBattery::DischargeFor(double Current, double Time)
// as in charging but decreasing the load 
{
	if (m_ChargeLevel - (Current*(Time / 60)) <= 0)
	{
		return (Current*(Time / 60));
	}
	else
	{
		m_ChargeLevel -= (Current*(Time / 60));
		return true;
	}
}

double CBattery::GetCapacity()
{
	//	returns capacity of accumulator
	return m_Capacity;
}

void CBattery::SetCapacity(double capacity)
{
	this->m_Capacity = capacity;
}

void CBattery::SetVoltage(double voltage)
{
	this->m_Voltage = voltage;
}

void CBattery::SetChargeLevel(double charge)
{
	this->m_ChargeLevel = charge;
}

double CBattery::GetChargeLevel()
{
	//	returns actual level of charging (from 0 to 1) *(maybye a better way is to show it in percentages)
	return (m_ChargeLevel / m_Capacity);
}

double CBattery::GetMaxDischargeTime(double Current)
{
	// returns maximal work time of the battery if burden would be of given value
	return (m_ChargeLevel / Current);
}


void CBattery::Info()
{
	// prints basic info like capacity(mA), chargeLevel(mA), voltage(V)
	cout << "Battery Capacity: " << m_Capacity << "   Voltage: " << m_Voltage << "   Battery Level Now: " << m_ChargeLevel << endl;
}
CBattery& CBattery::operator=(const CBattery &battery)
{
	if (this != battery)  // self-assignment check
	{
		this->m_Capacity = battery.m_Capacity;
		this->m_ChargeLevel = battery.m_ChargeLevel;
		this->m_Voltage = battery.m_Voltage;
	}

	// it needds testing
	return *this;
}

CBattery& CBattery::operator+=(const double amh)
{
	this->m_ChargeLevel += amh;
	// add exceptions when it's greater than capacity
	return *this;
}

CBattery& CBattery::operator-=(const double amh)
{
	this->m_ChargeLevel -= amh;
	// add exception when it's going to be lower than 0
	return *this;
}

CBattery& CBattery::operator+(const CBattery &battery)
{
	// in the task is written that we should add all the values that add up to eachother so
	// i think the good solution for in-series connection is to add-up voltages
	// choose the smaller capacitance and smaller battery level
	CBattery bat();
	if (this->m_Capacity >= battery.m_Capacity)
	{
		bat.SetCapacity(battery.m_Capacity);
	}
	else
	{
		bat.SetCapacity(this->m_Capacity);
	}

	if (this->m_ChargeLevel >= battery.m_ChargeLevel)
	{
		bat.SetChargeLevel(battery.m_ChargeLevel);
	}
	else
	{
		bat.SetChargeLevel(this->m_ChargeLevel);
	}

	bat.SetVoltage((battery.m_Voltage) + (this->m_Voltage));

	return *bat;
}

bool CBattery::operator==(const CBattery &battery)
{
	if ((this->m_Capacity == battery.m_Capacity) && (this->m_Voltage == battery.m_Voltage))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CBattery::operator!=(const CBattery &battery)
{
	if ((this->m_Capacity == battery.m_Capacity) && (this->m_Voltage == battery.m_Voltage))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CBattery::operator<(const CBattery &battery)
{
	if (this->m_ChargeLevel < battery.m_ChargeLevel)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CBattery::operator>(const CBattery &battery)
{
	if (this->m_ChargeLevel > battery.m_ChargeLevel)
	{
		return true;
	}
	else
	{
		return false;
	}
}

CBattery::~CBattery()
{
}


















