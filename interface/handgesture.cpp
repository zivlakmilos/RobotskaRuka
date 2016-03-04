#include "handgesture.h"

using namespace std;
using namespace cv;

HandGesture::HandGesture()
{
    this->cap = VideoCapture(0);
}

void HandGesture::pickColor()
{
}

void HandGesture::trackHand(int *rot, int *seg1, int *seg2, int *seg3)
{
}
