#!/usr/bin/python

import sys
import Adafruit_DHT

# Parse command line parameters.
sensor_args = { '2302': Adafruit_DHT.AM2302 }

if len(sys.argv) == 2:
	sensor = sensor_args['2302']
	pin = sys.argv[1]
else:
	print 'usage: sudo ./temperature-sensor.py <GPIO Pin #>'
	sys.exit(1)

# Try to grab a sensor reading.  Use the read_retry method which will retry up
# to 15 times to get a sensor reading (waiting 2 seconds between each retry).
humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)

# Convert from C to F
temperature = temperature * 9/5.0 + 32

# Note that sometimes you won't get a reading and
# the results will be null (because Linux can't
# guarantee the timing of calls to read the sensor).
# If this happens try again!
if humidity is not None and temperature is not None:
	# Output in CSV format
	print "{0:0.1f}F".format(temperature) + ",{0:0.1f}%".format(humidity)

	#print 'Temperature={0:0.1f}* F'.format(temperature)
    #print 'Humidity={0:0.1f}%'.format(humidity)

else:
	print 'FAILED!'
	sys.exit(1)
