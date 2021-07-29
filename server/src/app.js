const path = require('path')
var http = require('http')
const https = require('https');
const express = require('express')
var SerialPort = require('serialport')
const Readline = SerialPort.parsers.Readline;


const app =express()
const server = http.createServer(app)

const port2 = process.env.PORT || 3000
const publicDirectoryPath=  path.join(__dirname, '../public')
app.use(express.static(publicDirectoryPath))

var port = new SerialPort("COM5", {
    baudRate: 9600,
});

const parser = new Readline();
port.pipe(parser);


function tryParseJson (str) {
    try {
        JSON.parse(str);
    } catch (e) {
        return false;
    }
    return JSON.parse(str);
}

console.log('Initialising...');
console.log('Opened port ....');
parser.on('data', function(data) {
    console.log(data);
    const sensorData = tryParseJson(data);
    if(sensorData){
        console.log(sensorData);
    
    
    let baseurl = 'https://api.thingspeak.com/update?api_key=4772VX96H8HICDU7&field1='+sensorData.temperature+'&field2='+sensorData.latitude+'&field3='+sensorData.longitude+'&field4='+sensorData.Heartbeat+'&field5='+sensorData.Spotwo+'&field6='+sensorData.humidity;

        https.get(baseurl, (res) => {  }); }    
		});

 server.listen(port2, () => {
    console.log(`Server is up on port ${port2}`)
})        
       
   
