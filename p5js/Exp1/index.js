
// Using express: http://expressjs.com/
var express = require('express');
var bodyParser=require('body-parser');


// Create the app
var app = express();

const fs = require('fs');
const child_process = require('child_process');

// Set up the server
// process.env.PORT is related to deploying on heroku
var server = app.listen(process.env.PORT || 3000, listen);

// This call back just tells us that the server has started
function listen() {
  var host = server.address().address;
  var port = server.address().port;
  console.log('Example app listening at http://' + host + ':' + port);
}

app.use(express.static('public'));
app.use(bodyParser());
app.post('/',function(req,res){
  var sourcex=req.body.sourcex;
  var sourcey=req.body.sourcey;
  var endx=req.body.endx;
  var endy=req.body.endy;
  console.log(sourcex+sourcey+endx+endy);
  fun(sourcex,sourcey,endx,endy);
  setTimeout(function (){
    res.setHeader("Location", "http://172.16.21.113:3000");
    res.end();
  },10000);
});

// WebSocket Portion
// WebSockets work with the HTTP server
var io = require('socket.io')(server);

// Register a callback function to run when we have an individual connection
// This is run for each individual user that connects
io.sockets.on('connection',
  // We are given a websocket object in our function
  function (socket) {

    console.log("We have a new client: " + socket.id);

    socket.on('disconnect', function() {
      console.log("Client has disconnected");
    });
  }
);



function fun(x1,y1,x2,y2){
  console.log("hello");
  var workerProcess = child_process.spawn('./mocmaes', [x1, y1, x2, y2], {cwd:"../../project"});

   workerProcess.stdout.on('data', function (data) {
      console.log('stdout: ' + data);
   });

   workerProcess.stderr.on('data', function (data) {
      console.log('stderr: ' + data);
   });

   workerProcess.on('close', function (code) {
      console.log('child process exited with code ' + code);
   });
}

function autorefresh(){
  window.location.href="http://172.16.21.113:3000";
}

// if (pathfile== '/get.json'){
//   fs.writeFile("devices.txt", devices(daten), function(err) {
//       if(err) {console.log(err);} else {console.log("The file was saved!");}
//   });

  // fun();
// }
