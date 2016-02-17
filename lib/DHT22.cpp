#include <stdio.h>
#include <cstdlib>
#include <wiringPi.h>

#include "DHT22.h"

#define MAXTIMINGS 85

DHT22::DHT22(int GPIO_PIN_OUTPUT) {
	this->GPIO_PIN_OUTPUT = GPIO_PIN_OUTPUT;
}

float DHT22::ConvertDegreesCelsiusToFahrenheit(float degreesCelsius) {
  return (degreesCelsius * (9/5) + 32);
}

uint8_t DHT22::sizecvt(int read)
{
  /* digitalRead() and friends from wiringpi are defined as returning a value
  < 256. However, they are returned as int() types. This is a safety function */

  if (read > 255 || read < 0)
  {
    printf("Invalid data from wiringPi library\n");
    exit(1);
  }
  return (uint8_t)read;
}

DHT22_SensorResponseModel* DHT22::GetSensorData() {
  DHT22_SensorResponseModel* responseModel = new DHT22_SensorResponseModel();

	int dht22_dat[5] = {0, 0, 0, 0, 0};
	uint8_t laststate = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0;
	uint8_t i = 0;

	// pull pin down for 18 milliseconds
  pinMode(this->GPIO_PIN_OUTPUT, OUTPUT);
  digitalWrite(GPIO_PIN_OUTPUT, HIGH);
  delay(10);
  digitalWrite(GPIO_PIN_OUTPUT, LOW);
  delay(18);

  // then pull it up for 40 microseconds
  digitalWrite(GPIO_PIN_OUTPUT, HIGH);
  delayMicroseconds(40);

  // prepare to read the pin
  pinMode(GPIO_PIN_OUTPUT, INPUT);

	// detect change and read data
  for ( i=0; i< MAXTIMINGS; i++) {
    counter = 0;

    while (sizecvt(digitalRead(GPIO_PIN_OUTPUT)) == laststate) {
      counter++;
      delayMicroseconds(1);
      if (counter == 255) {
        break;
      }
    }

    laststate = sizecvt(digitalRead(GPIO_PIN_OUTPUT));

    if (counter == 255) {
       break;
    }

    // ignore first 3 transitions
    if ((i >= 4) && (i%2 == 0)) {
      // shove each bit into the storage bytes

      dht22_dat[j/8] <<= 1;
      if (counter > 16)
        dht22_dat[j/8] |= 1;

      j++;
    }
  }

  // check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
  // print it out if data is good
  if ((j >= 40) &&
      (dht22_dat[4] == ((dht22_dat[0] + dht22_dat[1] + dht22_dat[2] + dht22_dat[3]) & 0xFF)) ) {
        float t, h;
        h = (float)dht22_dat[0] * 256 + (float)dht22_dat[1];
        h /= 10;
        t = (float)(dht22_dat[2] & 0x7F)* 256 + (float)dht22_dat[3];
        t /= 10.0;
        if ((dht22_dat[2] & 0x80) != 0)  t *= -1;

        // return results
        responseModel->status = true;
        responseModel->humidity = h;
        responseModel->temperatureC = t;
        responseModel->temperatureF = ConvertDegreesCelsiusToFahrenheit(t);

        printf("Humidity = %.2f %% Temperature = %.2f *C \n", h, t );
  }
  else
  {
    responseModel->status = false;
    printf("Data not good, skip...\n");
  }

  return responseModel;
}
