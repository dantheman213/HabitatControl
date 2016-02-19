all: rf-comm temperature-sensor

rf-comm: rf-comm/RCSwitch.o rf-comm/main.o
	@mkdir -p bin/
	$(CXX) $(CXXFLAGS) $(LDSFLAGS) $+ -pthread -o bin/$@ -lwiringPi

temperature-sensor: temperature-sensor/DHT22.o temperature-sensor/main.o
	$(CXX) $(CXXFLAGS) $(LDSFLAGS) $+ -pthread -o bin/$@ -lwiringPi

clean:
	$(RM) rf-comm/*.o temperature-sensor/*.o bin/
