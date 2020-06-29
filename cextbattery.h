//#pragma once

#ifndef CEXTBATTERY_H
#define CEXTBATTERY_H

#include "pch.h"

#include <cstring>
#include <iostream>
#include <string>
#include "cbattery.h"

using namespace std;

class CExtBattery : public CBattery
{
private:
	double m_ECapacity;
	double m_EVoltage;
	double m_EChargeLevel;	// current capacity level in mAh == 0 < m_c_lvl 
	double m_EChargeSum;
	int m_CyclesCounter;
public:

	CExtBattery(double m_capacity, double m_voltage, double m_chargelevel); // change constructors so that there is no way battery will drop to 10% of capacitance

	bool Discharge(double mAh);

	void DischargeFor(double Current, double Time);

	CExtBattery& operator-=(const double amh);

	CExtBattery& operator+=(const double amh); // assignment that loads by a given load

	CExtBattery& operator+(const CExtBattery &battery); // sum of accumulators connected in series

	bool Charge(double mAh); // function that changes current load for a certain value

	bool ChargeFor(double Current, double Time); // function  loading accumulator 

	int GetChargeCycles();
};


#endif // CBATTERY_H

