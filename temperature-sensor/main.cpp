#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "DHT22.h"

void printUsage(char *argv[]) {
    printf("Usage: %s <GPIO PIN Number>\n", argv[0]);
}

int main(int argc, char *argv[]) {
    if((argc-1) < 1) {
        printUsage(argv);
        return EXIT_SUCCESS;
    }

    char *gpioPin = argv[1];

    DHT22 *thermostat = new DHT22((int)gpioPin);
    DHT22_SensorResponseModel *sensorData = thermostat->GetSensorData();

    printf("Success! Temperature is %fF and %fC. The humidity is %f percent.\n", sensorData->temperatureF, sensorData->temperatureC, sensorData->humidity);

    return EXIT_SUCCESS;
}
