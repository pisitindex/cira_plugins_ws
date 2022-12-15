#ifndef ThreadSobel_HPP
#define ThreadSobel_HPP

#include <ros/ros.h>
#include <cira_lib_bernoulli/general/GlobalData.hpp>
#include <QThread>
#include <QJsonObject>
#include <QDebug>
#include <opencv2/opencv.hpp>

class ThreadSobel : public QThread
{
  Q_OBJECT
public:

  QString name = "Sobel";

  QJsonObject payload_js_data;
  QJsonObject output_js_data;
  QJsonObject param_js_data;

  bool isUseImage = true;
  cv::Mat mat_im, concat;

  bool isHaveError = false;

  ThreadSobel() { }

  void run() {

    isHaveError = false;
    output_js_data = QJsonObject();
    QJsonObject jso;
    if(isUseImage) {
      if(mat_im.empty()) {
        jso["error"] = "No image";
        output_js_data[name] = jso;
        isHaveError = true;
        return;
      }
    }

    //********* run here **************


    QString mode = param_js_data["mode"].toString();

    // prepare image //
    cv::Mat original = mat_im.clone();
    cv::Mat tmp = mat_im.clone();

    // convert to graycsale
    cv::Mat img_gray, img_hsv;
    cv::cvtColor(tmp, img_gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(tmp, img_hsv, cv::COLOR_BGR2HSV);

    // blur the image for better edge detection
    cv::Mat img_blur;
    cv::GaussianBlur(img_gray, img_blur, cv::Size(3,3), 0);

    // select mode
    cv::Mat sobel;
    if(mode == "Horizontal"){
        cv::Sobel(img_blur, sobel, CV_16S, 0, 1, 5);
    }
    if(mode == "Vertical"){
        cv::Sobel(img_blur, sobel, CV_16S, 1, 0, 5);
    }
    if(mode == "Mixed"){
        cv::Mat sobelx, sobely;
        cv::Sobel(img_blur, sobelx, CV_64F, 0, 1, 5);
        cv::Sobel(img_blur, sobely, CV_64F, 1, 0, 5);
        sobel = sobelx + sobely;
    }

    cv::threshold(sobel, sobel, 140,255,cv::THRESH_TOZERO);
    cv::convertScaleAbs(sobel, mat_im);
    cv::cvtColor(mat_im, mat_im, cv::COLOR_GRAY2BGR);
    cv::hconcat(original, mat_im, concat);

    payload_js_data[name] = jso;
  }


};

#endif // ThreadSobel_HPP
