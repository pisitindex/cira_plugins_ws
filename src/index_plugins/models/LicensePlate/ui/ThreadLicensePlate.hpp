﻿#ifndef ThreadLicensePlate_HPP
#define ThreadLicensePlate_HPP

#include <ros/ros.h>
#include <cira_lib_bernoulli/general/GlobalData.hpp>
#include <QThread>
#include <QJsonObject>
#include <cira_std_lib/cira_std_lib.hpp>
#include <cira_std_lib/cira_std_lib_deepdetect.h>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <string>


class ThreadLicensePlate : public QThread
{
  Q_OBJECT
public:

  QString name = "LicensePlate";

  QJsonObject payload_js_data;
  QJsonObject output_js_data;
  QJsonObject param_js_data;

  bool isUseImage = true;
  cv::Mat mat_im;

  bool isHaveError = false;

  ThreadLicensePlate() { }

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

    cv::Mat tmp_img = mat_im.clone();

    //********* run here **************

    DeepDetectParam param;
    param.drawing.is_draw_result = false;
    DeepDetectResult license = cira_std::deepDetectRun("license", tmp_img, param);

    for(int each_license = 0; each_license < license.objects.size(); each_license++){
        int each_license_x = license.objects[each_license].x;
        int each_license_y = license.objects[each_license].y;
        int each_license_w = license.objects[each_license].w;
        int each_license_h = license.objects[each_license].h;
        cv::Rect rect(each_license_x-each_license_w/2, each_license_y-each_license_h/2, each_license_w, each_license_h);
        cv::Mat crop = cira_std::getROI(tmp_img, rect);

        DeepDetectResult corner = cira_std::deepDetectRun("corner", crop, param);
        cv::Point2f p_curr[4];

        bool is_found_a = false;
        bool is_found_b = false;
        bool is_found_c = false;
        bool is_found_d = false;

        for(int i = 0; i < corner.objects.size(); i++) {
        QString name = corner.objects[i].name;
        int x = corner.objects[i].x; int y = corner.objects[i].y;
        cv::Point2f p(x, y);


        if(name == "a") { is_found_a=true; p_curr[0] = p; }
        if(name == "b") { is_found_b=true; p_curr[1] = p; }
        if(name == "c") { is_found_c=true; p_curr[2] = p; }
        if(name == "d") { is_found_d=true; p_curr[3] = p; }
        }

        if(!is_found_a || !is_found_b || !is_found_c || !is_found_d) {
        isHaveError = true;
        return;
        }

        //destination
        cv::Point2f p_dest[4];
        p_dest[0] = cv::Point2f(0, 0);
        p_dest[1] = cv::Point2f(1280, 0);
        p_dest[2] = cv::Point2f(1280, 720);
        p_dest[3] = cv::Point2f(0, 720);

        cv::Mat out(cv::Size(1280, 720), CV_8UC3);
        cv::Mat M = cv::getPerspectiveTransform(p_curr, p_dest);
        cv::warpPerspective(crop, out, M, out.size());

        DeepDetectResult details = cira_std::deepDetectRun("details", out, param);



    }


    jso["msg"] = "Hello World";



    payload_js_data[name] = jso;
  }


};

#endif // ThreadLicensePlate_HPP
