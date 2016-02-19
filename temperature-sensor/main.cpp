#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "DHT22.h"

void printUsage(char *argv[]) {
    printf("Usage: %s -p <GPIO PIN Number>\n", argv[0]);
}

int main(int argc, char *argv[]) {
    char *gpioPin = NULL;

    int c;
    while ((c = getopt(argc, argv, "p:")) != -1) {
        switch (c) {
            case 'p':
                gpioPin = optarg;
                break;

            case '?':
            default:
                printUsage(argv);
                break;
            }
    }

    DHT22 *thermostat = new DHT22((int)gpioPin);
    DHT22_SensorResponseModel *sensorData = thermostat->GetSensorData();

    printf("Success! Temperature is %fF and %fC. The humidity is %f.\n", sensorData->temperatureF, sensorData->temperatureC, sensorData->humidity);

    return EXIT_SUCCESS;
}
