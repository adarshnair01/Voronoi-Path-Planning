#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

class start
{

  public:
    static int startx;
    static int starty;
    static int endx;
    static int endy;
    static Mat image;
    static void processIt()
    {
      imshow("Working",image);
    }
};
