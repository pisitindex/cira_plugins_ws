#include <img_processing/img_processing.hpp>
#include <cira_lib_bernoulli/CiraBernoulliWidget.h>
#include <models/camera_calibration/camera_calibrationModel.hpp>
#include <models/undistort/undistortModel.hpp>
#include <models/homography/homographyModel.hpp>

img_processing::img_processing() {

}

std::shared_ptr<DataModelRegistry> img_processing::registerDataModels(std::shared_ptr<DataModelRegistry> ret) {

  ret->registerModel<camera_calibrationModel>();
  ret->registerModel<undistortModel>();
  ret->registerModel<homographyModel>();

  setTreeWidget();
  return ret;

}

void img_processing::setTreeWidget() {

  QStringList strListNodeDataModels;
  QString category;

  category = "img_processing";
  strListNodeDataModels << category + ",camera_calibration"+ ",null";
  strListNodeDataModels << category + ",undistort"+ ",null";
  strListNodeDataModels << category + ",homography"+ ",null";
  CiraBernoulliWidget::pluginTreeWidget->addNodeDataModels(strListNodeDataModels);
}
