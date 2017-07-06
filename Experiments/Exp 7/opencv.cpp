#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include <fstream>

using namespace cv;
using namespace std;




int main(int argc, char** argv )
{

  int edgeThresh = 1;
  int lowThreshold;
  int const max_lowThreshold = 80;
  int ratio = 3;
  int kernel_size = 3;

  Mat src, src_gray;
    Mat grad;
    // char* window_name = "Sobel Demo - Simple Edge Detector";
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    int c;

  Mat image,bw;
  image = imread("image.jpg",CV_LOAD_IMAGE_GRAYSCALE);
  Size size(720,480);
  resize(image,image,size);
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

  for (size_t j = 217; j > 0; j--) {
    for( int i = 0; i< contours.size(); i++ ){
      if(contourArea(contours[i])>100){
        drawContours( drawing, contours, i, Scalar(j,j,j), j*2, 8, hierarchy, 0, Point() );
        if(i!=0)
          drawContours( drawing, contours, i, Scalar(0,0,0), CV_FILLED, 8, hierarchy, 0, Point() );
      }
    }
  }


  //
  // //Get the clearance value for border of image
  // resize(rect,rect,cvSize(bw.cols-50,bw.rows-50));
  // rect=Scalar(255,255,255);
  // for(size_t i=25;i>0;i--){
  //   copyMakeBorder(rect,rect,1,1,1,1,BORDER_CONSTANT,i);
  // }
  // drawing=min(drawing,rect);

  // equalizeHist(drawing,drawing);

  rect=Scalar(255,255,255);
  subtract(rect,drawing,drawing);

  //
  //   std::ofstream outfile;
  //   outfile.open("points.txt");
  //   for (size_t i = 0; i < drawing.cols; i++) {
  //     for (size_t j = 0; j < drawing.rows; j++) {
  //     outfile<<static_cast<int>(drawing.at<uchar>(Point(i,j)))<<" ";
  //     }
  //     outfile<<"\n";
  //   }
  // Canny(drawing,drawing,0,217);
  // normalize(drawing, drawing, 0, 255);




      // imshow( "hello",drawing);
      adaptiveThreshold(drawing,drawing,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,11,2);
      // imshow("result",drawing);
      // blur(drawing,drawing,Size(3,3));
      //
      // double min,max;
      // cv::minMaxLoc(drawing, &min, &max);
      // cout<<min<<" "<<max;
      //
      //
      // drawing=drawing>180;
      // imshow("final",drawing);
      // imwrite("final.jpg",drawing);

      // assuming your matrix is CV_8U, and black is 0
      std::vector<cv::Point> pixelPoints;
      std::vector<int> pixelValues;
      bw=image>70;
      unsigned char const *p = drawing.ptr<unsigned char>();
      unsigned char const *q = bw.ptr<unsigned char>();
      for(int i = 0; i < drawing.rows * drawing.cols; ++i, ++p, ++q)
      {
        if(*q!=0)
        {
          int x = i % drawing.cols;
          int y = i / drawing.cols;
          pixelPoints.push_back(cv::Point(x, y));
          if(*p==0)
            pixelValues.push_back(10);
          else
            pixelValues.push_back(2);
        }
      }
      cout<<pixelPoints.size()<<" "<<pixelPoints[pixelPoints.size()-1]<<endl;
      cout<<pixelValues.size()<<" "<<pixelValues[pixelValues.size()-1]<<endl;
      // for (size_t i = 0; i < blackPixels.size(); i++) {
      //   cout<<blackPixels[i]<<" ";
      // }
    //
    //   equalizeHist( drawing, drawing );
    //           // imshow( "hel22lo", drawing);
    // /// Generate grad_x and grad_y
    // Mat grad_x, grad_y;
    // Mat abs_grad_x, abs_grad_y;
    //
    // /// Gradient X
    // //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    // Sobel( drawing, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    // convertScaleAbs( grad_x, abs_grad_x );
    //
    // /// Gradient Y
    // //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    // Sobel( drawing, grad_y, ddepth, 0, 1, 1, scale, delta, BORDER_DEFAULT );
    // convertScaleAbs( grad_y, abs_grad_y );
    //
    // /// Total Gradient (approximate)
    // addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );
    //
    //     imshow( "hel2lo", grad );



  // imshow( "Result window", bw );


  // imshow( "Result window", drawing );
  // imwrite( "window.jpg", drawing );

  waitKey(0);
  return 0;
}
