//#pragma once

#ifndef CBATTERY_H
#define CBATTERY_H

#include "pch.h"

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

class CBattery
{
private:
	double m_Capacity;		// maximal capacity value in mAh
	double m_ChargeLevel;	// current capacity level in mAh == 0 < m_c_lvl 
	double m_Voltage;		// working voltage in V

public:
	CBattery();

	CBattery(double m_capacity, double m_chargelevel);

	CBattery(double m_capacity, double m_voltage, double m_chargelevel); // wanted

	void SetVoltage(double m_voltage);

	void SetChargeLevel(double m_chargelevel);

	void SetCapacity(double m_capacity);

	bool Charge(double mAh); // function that changes current load for a certain value

	bool ChargeFor(double Current, double Time); // function  loading accumulator by current in mA in time expresed in minutes
	// the load charged is equal to time(hours)* current(mA)

	void Discharge(double Current); // function disscharging  
	// function returns type double if it fails to decrease the load by given value

	void DischargeFor(double Current, double Time);
	// as in charging but decreasing the load 

	double GetCapacity();
	//	returns capacity of accumulator

	double GetChargeLevel();
	//	returns actual level of charging (from 0 to 1) *(maybye a better way is to show it in percentages)

	double GetMaxDischargeTime(double Current);
	// returns maximal work time of the battery if burden would be of given value

	void Info(); // prints basic info like capacity(mA), chargeLevel(mA), voltage(V)

	virtual ~CBattery();

	/*   ########### Operators ############		*/

	CBattery& operator=(const CBattery &battery); // copy assignment operator

	CBattery& operator+=(const double amh); // assignment that loads by a given load

	CBattery& operator-=(const double amh); // assignment that unloads by a given load

	CBattery& operator+(const CBattery &battery); // sum of accumulators connected in series that will create new accumulator tht will have qualities of the 2 

	bool operator==(const CBattery &battery);

	bool operator!=(const CBattery &battery);

	bool operator<(const CBattery &battery);

	bool operator>(const CBattery &battery);

protected:

};

#endif // CBATTERY_H
