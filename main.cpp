#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

float ds_factor = 0.75;

static void help()
{
    cout <<
            "\nDense optical flow algorithm by Gunnar Farneback\n"
            "Usage:\n"
            "$ ./main\n"
            "This reads input from the webcam\n" << endl;
}

static void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step,
                    double, const Scalar& color)
{
    for(int y = 0; y < cflowmap.rows; y += step)
        for(int x = 0; x < cflowmap.cols; x += step)
        {
            const Point2f& fxy = flow.at<Point2f>(y, x);
            line(cflowmap, Point(x,y), Point(cvRound(x+fxy.x), cvRound(y+fxy.y)),
                 color);
            circle(cflowmap, Point(x,y), 2, color, -1);
        }
}

int main(int, char**)
{
    VideoCapture cap(0);
    help();
    if( !cap.isOpened() )
        return -1;

    Mat prevgray, gray, flow, cflow, frame;
    namedWindow("flow", 1);

    for(;;)
    {
        cap >> frame;
        resize(frame, frame, Size(), ds_factor, ds_factor, INTER_NEAREST);
        cvtColor(frame, gray, CV_BGR2GRAY);

        if( prevgray.data )
        {
            calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
            cvtColor(prevgray, cflow, CV_GRAY2BGR);
            drawOptFlowMap(flow, cflow, 16, 1.5, CV_RGB(0, 255, 0));
            imshow("flow", cflow);
        }
        if(waitKey(30)>=0)
            break;
        std::swap(prevgray, gray);
    }
    return 0;
}
