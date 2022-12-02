#ifndef Threadcamera_calibration_HPP
#define Threadcamera_calibration_HPP

#include <ros/ros.h>
#include <cira_lib_bernoulli/general/GlobalData.hpp>
#include <QThread>
#include <QJsonObject>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QDebug>


class Threadcamera_calibration : public QThread
{
  Q_OBJECT
public:

  QString name = "camera_calibration";

  QJsonObject payload_js_data;
  QJsonObject output_js_data;
  QJsonObject param_js_data;

  bool isUseImage = false;
  cv::Mat mat_im;

  bool isHaveError = false;

  Threadcamera_calibration() { }

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


    QString label_folder_path, test;
    label_folder_path = param_js_data["label_folder_path"].toString();
    qDebug() << "folder: " << label_folder_path;

    std::vector<cv::String> fileNames;
      cv::glob(label_folder_path.toStdString()+"/*.png", fileNames, false);
      cv::Size patternSize(25 - 1, 18 - 1);
      std::vector<std::vector<cv::Point2f>> q(fileNames.size());

      std::vector<std::vector<cv::Point3f>> Q;
      // 1. Generate checkerboard (world) coordinates Q. The board has 25 x 18
      // fields with a size of 15x15mm

      int checkerBoard[2] = {25,18};
      // Defining the world coordinates for 3D points
        std::vector<cv::Point3f> objp;
        for(int i = 1; i<checkerBoard[1]; i++){
          for(int j = 1; j<checkerBoard[0]; j++){
            objp.push_back(cv::Point3f(j,i,0));
          }
        }

      std::vector<cv::Point2f> imgPoint;
      // Detect feature points
      std::size_t i = 0;
      for (auto const &f : fileNames) {
        std::cout << std::string(f) << std::endl;

        // 2. Read in the image an call cv::findChessboardCorners()
        cv::Mat img = cv::imread(fileNames[i]);
        cv::Mat gray;

        cv::cvtColor(img, gray, cv::COLOR_RGB2GRAY);

        bool patternFound = cv::findChessboardCorners(gray, patternSize, q[i], cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);

        // 2. Use cv::cornerSubPix() to refine the found corner detections
        if(patternFound){
            cv::cornerSubPix(gray, q[i],cv::Size(11,11), cv::Size(-1,-1), cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.1));
            Q.push_back(objp);
        }

        // Display
        cv::drawChessboardCorners(img, patternSize, q[i], patternFound);
        cv::imshow("chessboard detection", img);
        //cv::waitKey(0);

        i++;
      }


      cv::Matx33f K(cv::Matx33f::eye());  // intrinsic camera matrix
      cv::Vec<float, 5> k(0, 0, 0, 0, 0); // distortion coefficients

      std::vector<cv::Mat> rvecs, tvecs;
      std::vector<double> stdIntrinsics, stdExtrinsics, perViewErrors;
      int flags = cv::CALIB_FIX_ASPECT_RATIO + cv::CALIB_FIX_K3 +
                  cv::CALIB_ZERO_TANGENT_DIST + cv::CALIB_FIX_PRINCIPAL_POINT;
      cv::Size frameSize(1440, 1080);

      std::cout << "Calibrating..." << std::endl;
      // 4. Call "float error = cv::calibrateCamera()" with the input coordinates
      // and output parameters as declared above...

      float error = cv::calibrateCamera(Q, q, frameSize, K, k, rvecs, tvecs, flags);



//      qDebug() << "cameraMatrix: " << K;
      std::cout << "Reprojection error = " << error << "\nK =\n"
                << K << "\nk=\n"
                << k << std::endl;

      QJsonObject distortMatrix;
//      distortMatrix["cameraMatrix"] = K;
//      distortMatrix["distCoeffs"] = k;


//      // Precompute lens correction interpolation
//      cv::Mat mapX, mapY;
//      cv::initUndistortRectifyMap(K, k, cv::Matx33f::eye(), K, frameSize, CV_32FC1,
//                                  mapX, mapY);

//      // Show lens corrected images
//      for (auto const &f : fileNames) {
//        std::cout << std::string(f) << std::endl;

//        cv::Mat img = cv::imread(f, cv::IMREAD_COLOR);

//        cv::Mat imgUndistorted;
//        // 5. Remap the image using the precomputed interpolation maps.
//        cv::remap(img, imgUndistorted, mapX, mapY, cv::INTER_LINEAR);

//        // Display
//        cv::imshow("undistorted image", imgUndistorted);
//        cv::waitKey(0);



    payload_js_data[name] = jso;
//  }
}

};

#endif // Threadcamera_calibration_HPP
