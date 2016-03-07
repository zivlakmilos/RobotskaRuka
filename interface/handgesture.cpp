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
//        vector<Scalar> colors;
//        for(int i = 0; i < NumOfRects; i++)
//        {
//            Mat roi = this->filter(cv::Rect(Point(colorPickerRect[i].x, colorPickerRect[i].y),
//                                            Point(colorPickerRect[i].x2, colorPickerRect[i].y2)));
//            colors.push_back(mean(roi, Mat1b(roi.rows, roi.cols)));
//            for(int j = 0; j < 3; j++)
//        }
//        int sum;
//        for(int i = 0; i < colors.size(); i++)
//            for(int j = 0; j < 3; j++)
//            {
//                if(colors[i].val[j] < this->colorLow[j])
//                    this->colorLow[j] = colors[i].val[j];
//                else if(colors[i].val[j] > this->colorHigh[j])
//                    this->colorHigh[j] = colors[i].val[j];
//            }

//        for(int i = 0; i < NumOfRects; i++)
//        {
//            Mat roi = this->filter(cv::Rect(Point(colorPickerRect[i].x, colorPickerRect[i].y),
//                                            Point(colorPickerRect[i].x2, colorPickerRect[i].y2)));
//            vector<int> h;
//            vector<int> s;
//            vector<int> v;

//            for(int y = 2; y < roi.rows - 2; y++)
//                for(int x = 2; x < roi.cols - 2; x++)
//                {
//                    h.push_back(roi.data[roi.channels()*(roi.cols * y + x) + 0]);
//                    s.push_back(roi.data[roi.channels()*(roi.cols * y + x) + 1]);
//                    v.push_back(roi.data[roi.channels()*(roi.cols * y + x) + 2]);
//                }

//            sort(h.begin(), h.end());
//            sort(s.begin(), s.end());
//            sort(v.begin(), v.end());

//            if(h.size() % 2 == 0)
//            {
//                this->colorAverate[0] = h[h.size() / 2 - 1];
//                this->colorAverate[1] = s[h.size() / 2 - 1];
//                this->colorAverate[2] = v[h.size() / 2 - 1];
//            } else
//            {
//                this->colorAverate[0] = h[h.size() / 2];
//                this->colorAverate[1] = s[h.size() / 2];
//                this->colorAverate[2] = v[h.size() / 2];
//            }

//            this->colorLow[0] = this->colorAverate[0] - 12;
//            this->colorHigh[0] = this->colorAverate[0] + 7;
//            this->colorLow[1] = this->colorAverate[1] - 30;
//            this->colorLow[1] = this->colorAverate[1] + 40;
//            this->colorLow[2] = this->colorAverate[2] - 80;
//            this->colorHigh[2] = this->colorAverate[2] + 80;
//        }

//        this->colorLow[0] = this->colorAverate[0] - 12;
//        this->colorHigh[0] = this->colorAverate[0] + 7;
//        this->colorLow[1] = this->colorAverate[1] - 30;
//        this->colorLow[1] = this->colorAverate[1] + 40;
//        this->colorLow[2] = this->colorAverate[2] - 80;
//        this->colorHigh[2] = this->colorAverate[2] + 80;

//        qDebug("%d\t%d\t%d", colorLow[0], colorLow[1], colorLow[2]);
//        qDebug("%d\t%d\t%d\n", colorHigh[0], colorHigh[1], colorHigh[2]);
    }

    return true;
}

bool HandGesture::trackHand(int *rot, int *seg1, int *seg2, int *seg3)
{

    if(!this->cap.isOpened())
        return false;
    if(!cap.read(this->original))
        return false;

    cvtColor(this->original, this->filter, CV_BGR2HSV);

//    inRange(this->original, Scalar(this->colorLow[0], this->colorLow[1], this->colorLow[2]),
//                            Scalar(this->colorHigh[0], this->colorHigh[1], this->colorHigh[2]),
//            this->filter);

    inRange(this->original, Scalar(this->colorLow[0], this->colorLow[1], this->colorLow[2]),
                            Scalar(this->colorHigh[0], this->colorHigh[1], this->colorHigh[2]),
            this->filter);
//    GaussianBlur(this->filter, this->filter, cv::Size(9, 9), 2, 2);
    medianBlur(this->filter, this->filter, 7);

    Mat tmpFilter = this->filter.clone();
    vector<vector<Point> > contures;
    vector<Vec4i> hierarchy;
    findContours(tmpFilter, contures, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    int largest[2] = { 0, 0 };
    cv::Rect bounding_rect;
    for(int i = 0; i < contures.size(); i++)
    {
        double a = contourArea(contures[i], false);
        if(a > largest[1])
        {
            largest[0] = i;
            largest[1] = a;
            bounding_rect = boundingRect(contures[i]);
        }
    }

    drawContours(this->original, contures, largest[0], Scalar(255, 0, 0), CV_FILLED, 8, hierarchy);
    rectangle(this->original, bounding_rect, Scalar(0, 0, 255), 1, 8, 0);

    flip(this->original, this->original, 1);
    flip(this->filter, this->filter, 1);

    int x = this->original.cols - (bounding_rect.x + bounding_rect.width / 2);
    int y = this->original.rows - (bounding_rect.y + bounding_rect.height / 2);

    qDebug("x: %d\ty: %d", x, y);

    *rot = (x * 180) / this->original.cols;

    return true;
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

void HandGesture::setColorLow(int h, int s, int v)
{
    this->colorLow[0] = h;
    this->colorLow[1] = s;
    this->colorLow[2] = v;
}

void HandGesture::setColorHigh(int h, int s, int v)
{
    this->colorHigh[0] = h;
    this->colorHigh[1] = s;
    this->colorHigh[2] = v;
}
