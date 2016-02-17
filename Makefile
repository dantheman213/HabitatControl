all: habitat-control

habitat-control: lib/DHT22.o lib/RCSwitch.o src/Daemon.o src/Logging.o src/main.o src/Overmind.o src/RFComm.o src/TemperatureControl.o
	$(CXX) $(CXXFLAGS) $(LDSFLAGS) $+ -pthread -o bin/$@ -lwiringPi

clean:
	$(RM) src/*.o bin/habitat-control

  
