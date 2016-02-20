#!/usr/bin/nodejs

// libraries
var fs          =    require('fs'),
    moment      =    require('moment'),
    sys         =    require('sys'),
    exec        =    require('child_process').exec;

// environment stuff
var rf_gpio_pin = 2;
var light1 = {
  on: 341251,
  off: 341260
};
var terrarium_hotpoint = 88.0;
var terrarium_coolpoint = 80;

// globals
var temp_log = "/var/log/temperature_sensor.log";
var rf_bin = "/usr/bin/rf-comm";

if(fs.existsSync(temp_log)) {
    fs.readFile(temp_log, {encoding: 'utf-8'}, function(err, data) {
      if(!err) {

        var lines = data.trim().split('\n');
        var lastLine = lines.slice(-1)[0];

        var sensor1_temp = lastLine.split(',')[1];
        console.log('Sensor 1 temp is: ' + sensor1_temp + '.');

        var temp = parseFloat(sensor1_temp.slice(0, -1));
        if(temp > terrarium_hotpoint) {
          console.log('Turning OFF heat lamp!');
          exec('rf-comm ' + light1.off + ' -p ' + rf_gpio_pin);
        } else if(temp < terrarium_coolpoint) {
          console.log('Turning ON heat lamp!');
          exec('rf-comm ' + light1.on + ' -p ' + rf_gpio_pin);
        }

        console.log('Complete!');
      }
    });
}
