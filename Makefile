all: habitat-control

habitat-control: Logging.o RFComm.o TemperatureControl.o main.o Daemon.o
	$(CXX) $(CXXFLAGS) $(LDSFLAGS) $+ -o $@ -lwiringPi

clean:
	$(RM) *.o habitat-control
