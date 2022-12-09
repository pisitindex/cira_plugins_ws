#include <img_processing/img_processing.hpp>
#include <cira_lib_bernoulli/CiraBernoulliWidget.h>
#include <models/warp_perspective_ai/warp_perspective_aiModel.hpp>
#include <models/camera_calibration/camera_calibrationModel.hpp>
#include <models/undistort/undistortModel.hpp>

img_processing::img_processing() {

}

std::shared_ptr<DataModelRegistry> img_processing::registerDataModels(std::shared_ptr<DataModelRegistry> ret) {

  ret->registerModel<camera_calibrationModel>();
  ret->registerModel<undistortModel>();
  ret->registerModel<warp_perspective_aiModel>();

  setTreeWidget();
  return ret;

}

void img_processing::setTreeWidget() {

  QStringList strListNodeDataModels;
  QString category;

  category = "img_processing";
  strListNodeDataModels << category + ",camera_calibration"+ ",null";
  strListNodeDataModels << category + ",undistort"+ ",null";
  strListNodeDataModels << category + ",warp_perspective_ai"+ ",null";
  CiraBernoulliWidget::pluginTreeWidget->addNodeDataModels(strListNodeDataModels);
}
