// batter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "cbattery.h"
#include "cextbattery.h"

#include <iostream>

using namespace std;

struct DischargeBatteryException : public exception
{
	const char * what() const throw ()
	{
		return "Battery Charge Level shouldn't be greater than capacitance and lower than 0";
	}
};

struct BadCapacityCreateBatteryException : public exception
{
	const char * what() const throw ()
	{
		return "Capacity given is wrong.";
	}
};

struct BadVoltageCreateBatteryException : public exception
{
	const char * what() const throw ()
	{
		return "Battery you tried o create must have positive voltage flowing.";
	}
};

struct BatteryException : public exception
{
	const char * what() const throw ()
	{
		return "Battery error";
	}
};


struct BadCapacityCreateExtBatteryException : public exception
{
	const char * what() const throw ()
	{
		return "Capacity of EXT battery that was given was wrong.";
	}
};

struct DischargeExtBatteryException : public exception
{
	const char * what() const throw ()
	{
		return "Charge level can't decrease below 10% of capacitance.";
	}
};


int main()
{
	try {
		CBattery bat1;
		bat1.ChargeFor(1000, 30);
		bat1.DischargeFor(250, 60);

		CBattery bat2(2000, 3.7, 1000);
		bat2.ChargeFor(1000, 30);
		bat2.DischargeFor(1000, 60);
		bat2.DischargeFor(1000, 60);
		bat2 += 500;
		bat2 += 100;

		CBattery bat3;
		bat3 = bat1 + bat2;
		bat1.Info(); cout << bat1.GetChargeLevel() * 100 << "%. " << bat1.GetMaxDischargeTime(50) << " mins" << endl;
		bat2.Info(); cout << bat2.GetChargeLevel() * 100 << "%. " << bat2.GetMaxDischargeTime(50) << " mins" << endl;
		bat3.Info(); cout << bat3.GetChargeLevel() * 100 << "%. " << bat3.GetMaxDischargeTime(50) << " mins" << endl;

		CExtBattery ebat1(1000, 5, 500);
		ebat1.ChargeFor(2000, 30);
		ebat1.DischargeFor(2000, 30);
		ebat1.ChargeFor(2000, 30);
		ebat1.DischargeFor(2000, 30);
		ebat1.Info();
		cout << "Charge cycles: " << ebat1.GetChargeCycles() << endl;
	}
	catch (BadCapacityCreateExtBatteryException) {}
	catch (BadCapacityCreateBatteryException) {}
	catch (BadVoltageCreateBatteryException) {}
	catch (DischargeExtBatteryException) {}
	catch (DischargeBatteryException) {}
	catch (BatteryException) {}
	return 0;
}
