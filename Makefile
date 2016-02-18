all: rf-comm temperature-sensor

rf-comm: RCSwitch.o main.o
	@mkdir -p ../bin
	$(CXX) $(CXXFLAGS) $(LDSFLAGS) $+ -pthread -o ../bin/$@ -lwiringPi

temperature-sensor: DHT22.o main.o
	@mkdir -p ../bin
	$(CXX) $(CXXFLAGS) $(LDSFLAGS) $+ -pthread -o ../bin/$@ -lwiringPi

clean:
	$(RM) rf-comm/*.o temperature-sensor/*.o bin/
