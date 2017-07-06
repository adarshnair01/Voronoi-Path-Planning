#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"

using namespace cv;
using namespace std;



int main(int argc, char** argv )
{
  Mat image,bw;
  image = imread("image.jpg",CV_LOAD_IMAGE_GRAYSCALE);
  int scalex,scaley;

  if ( !image.data )
      return -1;

  //applying threshold to get black and white image(Binary)
  bw=image>70;

  //Create a rectangle to remove border noise
  Mat rect( bw.size(), CV_8UC1 );
  rect=Scalar(0,0,0);
  rectangle(rect,Point(0,0),Point(bw.cols,bw.rows), Scalar(255, 255, 255),+50,4);
  bitwise_or(bw,rect,bw);

  //Get contours and apply contour border to get clearance value
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  findContours( bw, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  //Create a new matrix with same size and draw contour and fill its area
  Mat drawing( bw.size(), CV_8UC1 );
  drawing=Scalar(25,25,25);
  for( int i = 1; i< contours.size(); i++ )
  {
    if(contourArea(contours[i])>100){
      for (size_t j = 50; j > 25; j--) {
        drawContours( drawing, contours, i, Scalar(j-25,j-25,j-25), j, 8, hierarchy, 0, Point() );
      }
      drawContours( drawing, contours, i, Scalar(0,0,0), CV_FILLED, 8, hierarchy, 0, Point() );
    }
  }

  //Get the clearance value for border of image
  resize(rect,rect,cvSize(bw.cols-50,bw.rows-50));
  rect=Scalar(255,255,255);
  for(size_t i=25;i>0;i--){
    copyMakeBorder(rect,rect,1,1,1,1,BORDER_CONSTANT,i);
  }
  drawing=min(drawing,rect);
  imshow( "Result window", drawing );

  waitKey(0);
  return 0;
}
