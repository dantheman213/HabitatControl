#include <stdint.h>
#include "DHT22_SensorResponseModel.h"

class DHT22 {

public:
    DHT22(int);
    DHT22_SensorResponseModel* GetSensorData();
    float ConvertDegreesCelsiusToFahrenheit(float);

private:
    int GPIO_PIN_OUTPUT;
    uint8_t sizecvt(int);

};
