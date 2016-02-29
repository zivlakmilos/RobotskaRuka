//#include "opencvwidget.h"

//OpenCVWidget::OpenCVWidget(QWidget *parent)
//    : QGLWidget(parent)
//{
//    sceneChangede = false;
//    bgColor = QColor::fromRgb(150, 150, 150);

//    imgHeihgt = 0;
//    imgWidth = 0;
//    imgRatio = 4.0f / 3.0f;     // Default ratio

//    posX = 0;
//    posY = 0;
//}

//void OpenCVWidget::initializeGL()
//{
//    makeCurrent();
//    qglClearColor(bgColor.darker());
//}

//void OpenCVWidget::resize(int width, int height)
//{
//    makeCurrent();
//    glViewport(0, 0, (GLint)width, (GLint)heihgt);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();

//    glOrtho(0, width, 0, height, 1);

//    glMatrixMode(GL_MODELVIEW);

//    imgWidth = height / imgRatio;
//    imgHeight = height;

//    if(imgHeight > height)
//    {
//        imgWidth = imgHeight * imgRatio;
//        imgWidth = height;
//    }

//    emit imageSizeChanges(width, height);

//    imgX = (width - imgWidth) / 2;
//    imgY = (height - imgHeight) / 2;

//    sceneChanged = true;

//    updateScene();
//}

//void OpenCVWidget::updateScene()
//{
//    if(sceneChanged && this->isVisible())
//        updateGL();
//}

//void OpenCVWidget::paintGL()
//{
//    makeCurrent();

//    if(!sceneChanged)
//        return;

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    renderImage();

//    sceneChanged = false;
//}

//void OpenCVWidget::renderImage()
//{
//    makeCurrent();

//    glClear(GL_COLOR_BUFFER_BIT);

//    if(!renderImage.isNull())
//    {
//        glLoadIdentity();

//        QImage image;

//        glPushMatrix();
//        {
//            int imgW = renderImage.width();
//            int imgH = renderImage.height();

//            if(imgW != this->size().width() &&
//                    imgH != this->size().height())
//            {
//                image = renderImage.scaled(
//                                            QSize(imgW, imgH),
//                                            Qt::IgnoreAspectRatio,
//                                            Qt::SmoothTransformation
//                                           );
//            } else
//                image = renderImage;

//            glRasterPos2i(posX, posY);

//            imgW = image.width();
//            imgH = image.height();

//            glDrawPixels(imgW, imgH, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
//        }
//        glPopMatrix();

//        glFlush();
//    }
//}

//bool OpenCVWidget::showImage(cv::Mat image)
//{
//    image.copyTo(cvImage);

//    imgRatio = (float)image.cols / (float)image.rows;

//    if(cvImage.channels() == 3)
//        renderImage = QImage((const unsigned char *)(cvImage.data),
//                             cvImage.cols, cvImage.rows,
//                             cvImage.step, QImage::Format_RGB888).rgbSwapped();
//    else if(cvImage.channels() == 1)
//        renderImage = QImage((const unsigned char *)(cvImage.data),
//                             cvImage.cols, cvImage.rows,
//                             cvImage.step, QImage::Format_Indexed8);
//    else
//        return false;

//    renderImage = QGLWidget::convertToGLFormat(renderImage);

//    sceneChanged = true;

//    updateScene();

//    return true;
//}
