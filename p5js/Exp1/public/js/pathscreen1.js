var weather;
var i=0;
var bg;

// var fr = 35; //starting FPS

function preload() {
  var url = 'paths/path80.json';
  weather = loadJSON(url);
}

function setup() {
  var myCanvas=createCanvas(1023,595);
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
    ellipse(weather.points[0].x, weather.points[0].y,30,30);


    stroke(124,252,2)
    ellipse(weather.points[99].x, weather.points[99].y,30,30);

    for(j=1;j<99;j++){
      stroke(196,43,51);
      fill(196,43,51)
      ellipse(weather.points[j].x, weather.points[j].y,5,5);
    }


    ellipse(weather.points[i].x, weather.points[i++].y,25,25);
    stroke(250);
    fill(176,23,31);
    if(i>100){
      i=0;
    }
}
