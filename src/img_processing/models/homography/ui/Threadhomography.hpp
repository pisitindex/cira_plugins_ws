#ifndef Threadhomography_HPP
#define Threadhomography_HPP

#include <ros/ros.h>
#include <cira_lib_bernoulli/general/GlobalData.hpp>
#include <QThread>
#include <QJsonObject>
#include <QDebug>
#include <opencv2/opencv.hpp>

class Threadhomography : public QThread
{
  Q_OBJECT
public:

  QString name = "homography";

  QJsonObject payload_js_data;
  QJsonObject output_js_data;
  QJsonObject param_js_data;

  bool isUseImage = true;
  cv::Mat mat_im, mat_im1;

  bool isHaveError = false;

  Threadhomography() { }

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


    bool using_ai = param_js_data["using_ai"].toBool();

    int spinBox_horizontal = param_js_data["spinBox_horizontal"].toInt();
    int spinBox_vertical = param_js_data["spinBox_vertical"].toInt();


    cv::Point2f p_curr[4];


    if(using_ai){

    if(!payload_js_data.contains("DeepDetect")){
        jso["error"] = "No DeepDetect";
        isHaveError = true;
        return;
    }

    QJsonArray objects = payload_js_data["DeepDetect"].toObject()["objects"].toArray();

    bool is_found_a = false;
    bool is_found_b = false;
    bool is_found_c = false;
    bool is_found_d = false;

    for(int i = 0; i < objects.size(); i++) {
    QJsonObject obj = objects[i].toObject();
    QString name = obj["name"].toString();
    int x = obj["x"].toInt(); int y = obj["y"].toInt();
    cv::Point2f p(x, y);
    qDebug() << "--- " << name << x << y;
    if(name == "a") { is_found_a=true; p_curr[0] = p; }
    if(name == "b") { is_found_b=true; p_curr[1] = p; }
    if(name == "c") { is_found_c=true; p_curr[2] = p; }
    if(name == "d") { is_found_d=true; p_curr[3] = p; }
    }

    if(!is_found_a || !is_found_b || !is_found_c || !is_found_d) {
    isHaveError = true;
    return;
    }
    }

    else{
        int point1_x = param_js_data["spinBox_point1_x"].toInt();
        int point1_y = param_js_data["spinBox_point1_y"].toInt();
        int point2_x = param_js_data["spinBox_point2_x"].toInt();
        int point2_y = param_js_data["spinBox_point2_y"].toInt();
        int point3_x = param_js_data["spinBox_point3_x"].toInt();
        int point3_y = param_js_data["spinBox_point3_y"].toInt();
        int point4_x = param_js_data["spinBox_point4_x"].toInt();
        int point4_y = param_js_data["spinBox_point4_y"].toInt();

        int radious = 10;
        int thickness = 5;

        p_curr[0] = cv::Point2f(point1_x, point1_y);
        p_curr[1] = cv::Point2f(point2_x, point2_y);
        p_curr[2] = cv::Point2f(point3_x, point3_y);
        p_curr[3] = cv::Point2f(point4_x, point4_y);
        cv::circle(mat_im, p_curr[0], radious, cv::Scalar(0,0,255), thickness);
        cv::circle(mat_im, p_curr[1], radious, cv::Scalar(0,255,255), thickness);
        cv::circle(mat_im, p_curr[2], radious, cv::Scalar(255,0,255), thickness);
        cv::circle(mat_im, p_curr[3], radious, cv::Scalar(255,255,0), thickness);
    }

    //destination
    cv::Point2f p_dest[4];
    p_dest[0] = cv::Point2f(0, 0);
    p_dest[1] = cv::Point2f(spinBox_horizontal, 0);
    p_dest[2] = cv::Point2f(spinBox_horizontal, spinBox_vertical);
    p_dest[3] = cv::Point2f(0, spinBox_vertical);

    cv::Mat out(cv::Size(spinBox_horizontal, spinBox_vertical), CV_8UC3);
    cv::Mat M = cv::getPerspectiveTransform(p_curr, p_dest);
    cv::warpPerspective(mat_im, out, M, out.size());

    mat_im1 = out;


    payload_js_data[name] = jso;
  }


};

#endif // Threadhomography_HPP
