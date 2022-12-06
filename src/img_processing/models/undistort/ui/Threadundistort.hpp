#ifndef Threadundistort_HPP
#define Threadundistort_HPP

#include <ros/ros.h>
#include <cira_lib_bernoulli/general/GlobalData.hpp>
#include <QThread>
#include <QJsonObject>
#include <QDebug>
#include <iostream>

#include <opencv2/opencv.hpp>

class Threadundistort : public QThread
{
  Q_OBJECT
public:

  QString name = "undistort";

  QJsonObject payload_js_data;
  QJsonObject output_js_data;
  QJsonObject param_js_data;

  bool isUseImage = true;
  cv::Mat mat_im;

  bool isHaveError = false;

  Threadundistort() { }

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

    jso["msg"] = "Hello World";

    QString path_to_file = param_js_data["path_to_file"].toString();
    qDebug() << path_to_file;
    cv::FileStorage fs(path_to_file.toStdString(), cv::FileStorage::READ);
    qDebug() << "testttttttttttttt";
    cv::Matx33f K(cv::Matx33f::eye());  // intrinsic camera matrix
    cv::Vec<float, 5> k(0, 0, 0, 0, 0); // distortion coefficients
    fs["cameraMatrix"] >> K;
    fs["distCoeffs"] >> k;
    std::cout <<"cameraMatrix"<< K;
    std::cout <<"distCoeffs"<< k;
    fs.release();
    cv::Mat undist;
    cv::undistort(mat_im,undist,K,k);
    mat_im = undist;

    payload_js_data[name] = jso;
  }


};

#endif // Threadundistort_HPP
