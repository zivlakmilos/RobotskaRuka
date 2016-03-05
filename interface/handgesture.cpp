#include "handgesture.h"

#include <QImage>

using namespace std;
using namespace cv;

HandGesture::HandGesture()
{
    this->cap = VideoCapture(0);
}

bool HandGesture::pickColor(bool pick = false)
{
    if(!this->cap.isOpened())
        return false;
    if(!this->cap.read(this->original))
        return false;

    cvtColor(this->original, this->filter, CV_BGR2HSV);

    if(this->colorPickerRect.empty())
    {
        colorPickerRect.push_back({this->original.cols / 3,
                                   this->original.rows / 6,
                                   this->original.cols / 3 + this->RectLeanght,
                                   this->original.rows / 6 + this->RectLeanght});
        colorPickerRect.push_back({this->original.cols / 4,
                                   this->original.rows / 2,
                                   this->original.cols / 4 + this->RectLeanght,
                                   this->original.rows / 2 + this->RectLeanght});
        colorPickerRect.push_back({this->original.cols / 3,
                                   this->original.rows / 1.5,
                                   this->original.cols / 3 + this->RectLeanght,
                                   this->original.rows / 1.5 + this->RectLeanght});
        colorPickerRect.push_back({this->original.cols / 2,
                                   this->original.rows / 2,
                                   this->original.cols / 2 + this->RectLeanght,
                                   this->original.rows / 2 + this->RectLeanght});
        colorPickerRect.push_back({this->original.cols / 2.5,
                                   this->original.rows / 2.5,
                                   this->original.cols / 2.5 + this->RectLeanght,
                                   this->original.rows / 2.5 + this->RectLeanght});
        colorPickerRect.push_back({this->original.cols / 2,
                                   this->original.rows / 1.5,
                                   this->original.cols / 2 + this->RectLeanght,
                                   this->original.rows / 1.5 + this->RectLeanght});
        colorPickerRect.push_back({this->original.cols / 2.5,
                                   this->original.rows / 1.8,
                                   this->original.cols / 2.5 + this->RectLeanght,
                                   this->original.rows / 1.8 + this->RectLeanght});
    }

    flip(this->original, this->original, 1);
    flip(this->filter, this->filter, 1);
    for(int i = 0; i < NumOfRects; i++)
    {
        rectangle(this->original, Point(colorPickerRect[i].x, colorPickerRect[i].y),
                                  Point(colorPickerRect[i].x2, colorPickerRect[i].y2),
                  Scalar(0, 255, 0), 2);
        rectangle(this->filter, Point(colorPickerRect[i].x, colorPickerRect[i].y),
                                  Point(colorPickerRect[i].x2, colorPickerRect[i].y2),
                  Scalar(0, 255, 0), 2);
    }

    if(pick)
    {
        vector<Scalar> colors;
        for(int i = 0; i < NumOfRects; i++)
        {
            Mat roi = this->filter(cv::Rect(Point(colorPickerRect[i].x, colorPickerRect[i].y),
                                            Point(colorPickerRect[i].x2, colorPickerRect[i].y2)));
            colors.push_back(mean(roi));
        }
        for(int i = 0; i < colors.size(); i++)
            for(int j = 0; j < 3; j++)
            {
                if(colors[i].val[j] < this->colorLow[i])
                    this->colorLow[i] = colors[i].val[j];
                else if(colors[i].val[j] > this->colorHight[i])
                    this->colorHight[i] = colors[i].val[j];
            }
    }

    return true;
}

void HandGesture::trackHand(int *rot, int *seg1, int *seg2, int *seg3)
{

    if(!this->cap.isOpened())
        return;
    if(!cap.read(this->original))
        return;

    cvtColor(this->original, this->filter, CV_BGR2HSV);
}

QImage HandGesture::matToImg(int type = ImageOriginal)
{
    if(type == ImageOriginal)
    {
        if(!this->original.empty())
        {
            QImage tmp;
            switch(original.type())
            {
                case CV_8UC4:
                    tmp =  QImage(original.data, original.cols, original.rows, original.step, QImage::Format_RGB32);
                    break;
                case CV_8UC3:
                    tmp = QImage(original.data, original.cols, original.rows, original.step, QImage::Format_RGB888);
                    tmp.rgbSwapped();
                    break;
                case CV_8UC1:
                    static QVector<QRgb> colorTable;
                        for(int i = 0; i < 256; i++)
                            colorTable.push_back(qRgb(i, i, i));
                    tmp = QImage(original.data, original.cols, original.rows, original.step, QImage::Format_Indexed8);
                    tmp.setColorTable(colorTable);
                    break;
            }
            return tmp;
        }
    } else if(type == ImageFilter)
    {
        if(!this->filter.empty())
        {
            QImage tmp;
            switch(filter.type())
            {
                case CV_8UC4:
                    tmp = QImage(filter.data, filter.cols, filter.rows, filter.step, QImage::Format_RGB32);
                    break;
                case CV_8UC3:
                    tmp = QImage(filter.data, filter.cols, filter.rows, filter.step, QImage::Format_RGB888);
                    tmp.rgbSwapped();
                    break;
                case CV_8UC1:
                    static QVector<QRgb> colorTable;
                        for(int i = 0; i < 256; i++)
                            colorTable.push_back(qRgb(i, i, i));
                    tmp = QImage(filter.data, filter.cols, filter.rows, filter.step, QImage::Format_Indexed8);
                    tmp.setColorTable(colorTable);
                    break;
            }
            return tmp;
        }
    }
}
