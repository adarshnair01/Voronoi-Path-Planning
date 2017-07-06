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

    // imshow("hoi",image);
    if ( !image.data )
        return -1;
    bw=image>70;



    Mat rect( bw.size(), CV_8UC1 );
    rect=Scalar(0,0,0);
    rectangle(rect,Point(0,0),Point(bw.cols,bw.rows), Scalar(255, 255, 255),+50,4);

    bitwise_or(bw,rect,bw);


    // namedWindow("hoi",WINDOW_AUTOSIZE);
    // imshow("hoi",bw);

     /// Find contours
     vector<vector<Point> > contours;
     vector<Vec4i> hierarchy;
     findContours( bw, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );


     /// Draw contours
        Mat drawing( bw.size(), CV_8UC1 );
        drawing=Scalar(25,25,25);
        for( int i = 1; i< contours.size(); i++ )
        {
            if(contourArea(contours[i])>100){
                // cout<<contourArea(contours[i])<<endl;
              for (size_t j = 50; j > 25; j--) {
                drawContours( drawing, contours, i, Scalar(j-25,j-25,j-25), j, 8, hierarchy, 0, Point() );
              }

                drawContours( drawing, contours, i, Scalar(0,0,0), CV_FILLED, 8, hierarchy, 0, Point() );

              // drawContours( drawing, contours, i, Scalar(0, 0, 0), -1, 8, hierarchy, 0, Point() );
            }
        }


        resize(rect,rect,cvSize(bw.cols-50,bw.rows-50));
        rect=Scalar(255,255,255);
        for(size_t i=25;i>0;i--){
          copyMakeBorder(rect,rect,1,1,1,1,BORDER_CONSTANT,i);
          // drawing=drawing&rect;
        }
        drawing=min(drawing,rect);
        imshow("out",rect);
        // imshow( "Result window", drawing );


        // rect=Scalar(255,255,255);
        // for (size_t i =25; i > 0; i--) {
        //   std::cout<<i<<std::endl;
        //   bitwise_and(drawing,rect,drawing);
        // }

  // imshow( "Result window", drawing );
        //
        // imshow( "EResult window", rect );
        // bitwise_or(drawing,bw,drawing);

        // drawing=drawingbw;
        // cout<<bw.rows<<" "<<bw.cols<<" "<<drawing.rows<<" "<<drawing.cols;
        imshow( "Result window", drawing );

    // scalex=0.25*image.cols;
    // scaley=0.25*image.rows;
    //
    // resize(image,image,cvSize(image.rows+scalex,image.cols+scaley));
    //
    // scalex/=2;
    // scaley/=2;
    //
    // Rect croprect(scalex,scaley,image.rows-scalex,image.cols-scaley);
    //
    // image=image(croprect);
    //
    // namedWindow("hi",WINDOW_AUTOSIZE);
    // imshow("hi",image);
    waitKey(0);
    return 0;
}
