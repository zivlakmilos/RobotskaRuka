#ifndef HANDGESTURE_H
#define HANDGESTURE_H

#include <vector>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

typedef struct
{
    int x;
    int y;
    int w;
    int h;
} Rect;

class HandGesture
{
public:
    HandGesture();

    void pickColor();
    void trackHand(int *rot, int *seg1, int *seg2, int *seg3);

private:
    enum { RectLeanght = 20 };

    cv::VideoCapture cap;
    cv::Mat original;
    cv::Mat tresholded;

    int huleL;
    int huleH;
    int saturationL;
    int saturationH;
    int valueL;
    int valueH;
};

#endif // HANDGESTURE_H
