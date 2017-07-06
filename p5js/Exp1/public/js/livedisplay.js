var capture;

function setup() {
  var live=createCanvas(390, 240);
  capture = createCapture(VIDEO);
  capture.size(320, 240);
  live.parent("right");
  capture.hide();
}

function draw() {
  background(255);
  image(capture, 0, 0, 320, 240);
  filter('THRESHOLD');
}
