#ifndef HABITATCONTROL_TEMPERATURECONTROL_H
#define HABITATCONTROL_TEMPERATURECONTROL_H

#include "../lib/DHT22.h"

class TemperatureControl {
public:
	TemperatureControl();
	void CheckEnvironment();

private:
	DHT22* hotTempSensor;
	DHT22* coolTempSensor;
};


#endif //HABITATCONTROL_TEMPERATURECONTROL_H
