#!/usr/bin/nodejs

// libraries
var fs          =    require('fs'),
    moment      =    require('moment'),
    sys         =    require('sys'),
    exec        =    require('child_process').exec;

// globals
var log_dir = "/var/log/tempeature_sensor.log";
var temperature_bin = "/usr/bin/temperature-sensor.py";


// start the show

if(!fs.existsSync(log_dir)) {

  fs.writeFile(log_dir, 'datetime,sensor1_temperature,sensor1_humidity,sensor2_temperature,sensor2_humidity\n', { flags: 'wx' }, function (err) {
      if (err) throw err;
      console.log("Created new log file at " + log_dir);
  });

}

var reading1 = null;
var reading2 = null;

console.log('Reading sensor data...');

var child_proc1 = exec(temperature_bin + ' 4', function(error, stdout, stderr) {reading1 = stdout});
var child_proc2 = exec(temperature_bin + ' 17', function(error, stdout, stderr) {reading2 = stdout});

console.log('Waiting for responses...');

var thread = setInterval(function() {

  if(reading1 != null && reading2 != null) {
    reading1 = reading1.trim();
    reading2 = reading2.trim();

    var sh_command = 'echo "' + moment().format() + ',' + reading1 + ',' + reading2 + '" >> ' + log_dir;
    console.log(sh_command);
    var child_proc3 = exec(sh_command, function (error, stdout, stderr) {});

    console.log('Complete!');
    clearTimeout(thread);
  }

}, 2000);
