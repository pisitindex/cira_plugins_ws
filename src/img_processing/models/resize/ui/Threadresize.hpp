#ifndef Threadresize_HPP
#define Threadresize_HPP

#include <ros/ros.h>
#include <cira_lib_bernoulli/general/GlobalData.hpp>
#include <QThread>
#include <QJsonObject>

#include <opencv2/opencv.hpp>

class Threadresize : public QThread
{
  Q_OBJECT
public:

  QString name = "resize";

  QJsonObject payload_js_data;
  QJsonObject output_js_data;
  QJsonObject param_js_data;

  bool isUseImage = true;
  cv::Mat mat_im;

  bool isHaveError = false;

  Threadresize() { }

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

    int new_size_width = 1920;
    int new_size_height = 1080;

    cv::resize(mat_im, mat_im, cv::Size(new_size_width, new_size_height));

    payload_js_data[name] = jso;
  }


};

#endif // Threadresize_HPP
