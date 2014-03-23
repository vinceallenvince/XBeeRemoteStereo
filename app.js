var connect = require('connect'),
    io = require('socket.io').listen(1337),
    EventEmitter = require('events').EventEmitter,
    serialport = require("serialport");

var emitter = new EventEmitter();

var SerialPort = serialport.SerialPort; // localize object constructor

//var mySerialPort = '/dev/tty.usbmodem1411'; // Arduino connected via usb
var mySerialPort = '/dev/tty.usbserial-A702LCUI'; // XBee

var sp = new SerialPort(mySerialPort, {
	baudrate: 57600,
	parser: serialport.parsers.readline('\n')
});

sp.on('open', function () {
	// when we receive data, publish it via the emitter
  sp.on('data', function(data) {
  	emitter.emit('data', data);
  });
});

// host a single page
connect(connect.static(__dirname + '/public')).listen(8000);

// start web sockets
io.sockets.on('connection', function(socket) {

  socket.emit('connected');

  // when we receive data, send it to the web sockets client
  emitter.on('data', function(data) {
    socket.emit('data', data);
  });

});
