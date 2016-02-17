#include <iostream>
#include <unistd.h>
#include "TemperatureControl.h"

using namespace std;

int main() {
  cout << "Hello, World!" << endl;

  TemperatureControl *thermostat = new TemperatureControl();
  while(true) {
    cout << "Checking...\n";

    thermostat->CheckEnvironment();
    sleep(1);
  }

  return 0;
}
