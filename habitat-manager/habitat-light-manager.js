#!/usr/bin/nodejs

// libraries
var fs          =    require('fs'),
    moment      =    require('moment'),
    sys         =    require('sys'),
    exec        =    require('child_process').exec;

// environment stuff
var rf_gpio_pin = 2;
var heatLampRF = {
  on: 341251,
  off: 341260
};
var ambientLampRF = {
  on: 335107,
  off: 335116
};
var nightLampRF = {
  on: 333107,
  off: 333116
};
var terrarium_hotpoint = 88;
var terrarium_coolpoint = 86;

var environmentTimeData = {
  dayTime: moment('7:00 AM', 'h:mm A'),
  nightTime: moment('7:30 PM', 'h:mm A')
};

// globals
var temp_log = "/var/log/temperature_sensor.log";
var rf_bin = "/usr/bin/rf-comm";

var DayNightEnum = {
  NONE: 0,
  DAY: 1,
  NIGHT: 2
};

function checkEnvironmentHeat() {

  if(fs.existsSync(temp_log)) {
      fs.readFile(temp_log, {encoding: 'utf-8'}, function(err, data) {
        if(!err) {

          var lines = data.trim().split('\n');
          var lastLine = lines.slice(-1)[0];

          var sensor1_temp = lastLine.split(',')[1];
          console.log('Checking at ' + moment().format());
          console.log('Sensor 1 temp is: ' + sensor1_temp + '.');

          var temp = parseFloat(sensor1_temp.slice(0, -1));
          if(temp > terrarium_hotpoint) {
            heatLampControl(false);
          } else if(temp < terrarium_coolpoint) {
            heatLampControl(true);
          }

          console.log('Complete!');
        }
      });
  }

}

function ambientLampControl(isOn) {
  if(isOn) {
    console.log('Turning ON ambient lamp!');
    exec('rf-comm ' + ambientLampRF.on + ' -p ' + rf_gpio_pin);
  } else {
    console.log('Turning OFF ambient lamp!');
    exec('rf-comm ' + ambientLampRF.off + ' -p ' + rf_gpio_pin);
  }
}

function nightLampControl(isOn) {
  if(isOn) {
    console.log('Turning ON night lamp!');
    exec('rf-comm ' + nightLampRF.on + ' -p ' + rf_gpio_pin);
  } else {
    console.log('Turning OFF night lamp!');
    exec('rf-comm ' + nightLampRF.off + ' -p ' + rf_gpio_pin);
  }
}

function heatLampControl(isOn) {
  if(isOn) {
    console.log('Turning ON heat lamp!');
    exec('rf-comm ' + heatLampRF.on + ' -p ' + rf_gpio_pin);
  } else {
    console.log('Turning OFF heat lamp!');
    exec('rf-comm ' + heatLampRF.off + ' -p ' + rf_gpio_pin);
  }
}

function checkDayOrNight() {
  var now = moment();

  if(now > environmentTimeData.dayTime && environmentTimeData.nightTime > now) {

        return DayNightEnum.DAY;
  } else {

    return DayNightEnum.NIGHT;
  }

  return DayNightEnum.NONE;
}

function main() {
  console.log('Checking is day or night...');

  if(moment() < environmentTimeData.dayTime) {
    //environmentTimeData.nightTime = environmentTimeData.nightTime.substract(1, 'days');
  }

  var timeMode = checkDayOrNight();

  if(timeMode == DayNightEnum.DAY) {
    console.log('day mode initiated');
    setTimeout(function(){ ambientLampControl(true); }, 500);
    setTimeout(function(){ nightLampControl(false); }, 2500);
    setTimeout(function(){ checkEnvironmentHeat(); }, 4500);
  } else if(timeMode == DayNightEnum.NIGHT) {
    console.log('night mode initiated');
    setTimeout(function(){ ambientLampControl(false); }, 500);
    setTimeout(function(){ heatLampControl(false); }, 2500);
    setTimeout(function(){ nightLampControl(true); }, 4500);
  }
}


main();
