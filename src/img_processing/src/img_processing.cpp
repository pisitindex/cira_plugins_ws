#include <img_processing/img_processing.hpp>
#include <cira_lib_bernoulli/CiraBernoulliWidget.h>
#include <models/affine_ai/affine_aiModel.hpp>
#include <models/camera_calibration/camera_calibrationModel.hpp>

img_processing::img_processing() {

}

std::shared_ptr<DataModelRegistry> img_processing::registerDataModels(std::shared_ptr<DataModelRegistry> ret) {

  ret->registerModel<affine_aiModel>();
  ret->registerModel<camera_calibrationModel>();


  setTreeWidget();
  return ret;

}

void img_processing::setTreeWidget() {

  QStringList strListNodeDataModels;
  QString category;

  category = "img_processing";
  strListNodeDataModels << category + ",affine_ai"+ ",null";
  strListNodeDataModels << category + ",camera_calibration"+ ",null";
  CiraBernoulliWidget::pluginTreeWidget->addNodeDataModels(strListNodeDataModels);
}
