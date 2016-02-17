#include "TemperatureControl.h"

#define HOT_SIDE_TEMPERATURE_SENSOR_PIN 10
#define COOL_SIDE_TEMPERATURE_SENSOR_PIN 11

TemperatureControl::TemperatureControl() {
		hotTempSensor = new DHT22(HOT_SIDE_TEMPERATURE_SENSOR_PIN);
		coolTempSensor = new DHT22(COOL_SIDE_TEMPERATURE_SENSOR_PIN);
}

void TemperatureControl::CheckEnvironment() {

	DHT22_SensorResponseModel* hotResponse = hotTempSensor->GetSensorData();
	DHT22_SensorResponseModel* coolResponse = coolTempSensor->GetSensorData();


}
