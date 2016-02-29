//#ifndef OPENCVWIDGET_H
//#define OPENCVWIDGET_H

//#include <QtOpenGL/QGLWidget>
//#include <opencv2/core/core.hpp>

//class OpenCVWidget : public QGLWidget
//{
//    Q_OBJECT

//public:
//    OpenCVWidget(QWidget *parent = 0);

//private:
//    bool sceneChanged;

//    QImage renderImage;
//    cv::Mat cvImage;

//    QColor bgColor;

//    int imgWidth;
//    int imgHeihgt;
//    float imgRatio;

//    int posX;
//    int posY;

//protected:
//    void initializeGL();
//    void paintGL();
//    void resizeGL(int width, int height);

//    void updateScene();
//    void renderImage();

//signals:
//    imageSizeChanges(int width, int height);

//public slots:
//    bool showImage(cv::Mat image);
//};

//#endif // OPENCVWIDGET_H
