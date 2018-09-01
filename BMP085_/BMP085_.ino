/*
* BMP085_.ino
*
* Created: 9/1/2018 10:44:37 PM
* Author: Mateusz Patyk
* Email: matpatyk@gmail.com
*/

#include <Wire.h>

#include "Headers/Status.h"
#include "Headers/I2C_Sensor.h"
#include "Headers/BMP085.h"

static long previousTime		= 0;
long actualTime					= 0;

void setup()
{
	Wire.begin();
	
	Status.begin();
	Status.checkStatus(Barometer);
	
	// Set Mode or use defaults from BMP085::init()
	//	Barometer.setMode(ULTRA_HIGH_RESOLUTION);
}

void loop()
{
	actualTime = millis();
	
	if((actualTime - previousTime) >= 10)
	{
		Barometer.read();
		// Data is valid after ~1000ms by default, check README!
		Status.printMessage("Pressure\t" + String(Barometer.getPressure()) + "\tAltitude\t" + String(Barometer.getAltitude()) + "\tTemperature\t" + String(Barometer.getTemperature()));
		
		previousTime = actualTime;
	}
}
