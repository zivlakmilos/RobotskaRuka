#ifndef HANDGESTURE_H
#define HANDGESTURE_H

#include <vector>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class QImage;

typedef struct
{
    float x;
    float y;
    float x2;
    float y2;
} Rect;

class HandGesture
{
public:
    HandGesture();

    bool pickColor(bool pick);
    bool trackHand(int *rot, int *seg1, int *seg2, int *seg3);
    QImage matToImg(int type);

    void setColorLow(int h, int s, int v);
    void setColorHigh(int h, int s, int v);

    enum { ImageOriginal = 0, ImageFilter };

private:
    enum { RectLeanght = 20, NumOfRects = 7 };

    cv::VideoCapture cap;
    cv::Mat original;
    cv::Mat filter;

    std::vector<Rect> colorPickerRect;

    int colorLow[3];
    int colorHigh[3];
};

#endif // HANDGESTURE_H
