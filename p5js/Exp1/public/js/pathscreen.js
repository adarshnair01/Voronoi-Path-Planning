var weather=[];
var i=0;
var bg;
var counter=0;
var color;

// var fr = 35; //starting FPS

function preload() {
  for (var k = 0; k < 6; k++) {
    color[k]=(Math.random()*255);
  }
  var url = 'paths/final/path0.json';
  weather[0] = loadJSON(url);
  var url1= 'paths/final/path1.json';
  weather[1] = loadJSON(url1);
  var url2= 'paths/final/path2.json';
  weather[2] = loadJSON(url2);
  var url3= 'paths/final/path3.json';
  weather[3] = loadJSON(url3);
  var url4= 'paths/final/path4.json';
  weather[4] = loadJSON(url4);
  var url5= 'paths/final/path5.json';
  weather[5] = loadJSON(url5);
}

function setup() {
  var myCanvas=createCanvas(720,480);
  myCanvas.parent("mainContainer");
  // frameRate(fr);
  bg = loadImage("image.jpg");
}

function draw() {
  background(bg);
  drawPath();
}

function drawPath(){


  stroke(100,3,31);
  fill(156,3,21);
  ellipse(weather[0].points[0].x, weather[0].points[0].y,30,30);


  stroke(124,252,2)
  ellipse(weather[0].points[100].x, weather[0].points[100].y,30,30);
  for (var k = 0; k < weather.length; k++) {
    for(j=1;j<100;j++){
      stroke(color[(k+2)%weather.length],color[k],color[(k+1)%weather.length]);
      fill(color[(k+2)%weather.length],color[k],color[(k+1)%weather.length]);
      ellipse(weather[k].points[j].x, weather[k].points[j].y,5,5);
    }
  }

  if(counter==6){
    counter=0;
  }

  stroke(color[(counter+2)%weather.length],color[counter],color[(counter+1)%weather.length]);
  fill(color[(counter+2)%weather.length],color[counter],color[(counter+1)%weather.length]);
  ellipse(weather[counter].points[i].x, weather[counter].points[i++].y,25,25);
  stroke(250);
  fill(176,23,31);
  if(i>100){
    i=0;
    counter++;
  }
}
