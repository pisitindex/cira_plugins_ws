#include <index_plugins/index_plugins.hpp>
#include <cira_lib_bernoulli/CiraBernoulliWidget.h>
#include <models/LicensePlate/LicensePlateModel.hpp>

index_plugins::index_plugins() {

}

std::shared_ptr<DataModelRegistry> index_plugins::registerDataModels(std::shared_ptr<DataModelRegistry> ret) {

  ret->registerModel<LicensePlateModel>();


  setTreeWidget();
  return ret;

}

void index_plugins::setTreeWidget() {

  QStringList strListNodeDataModels;
  QString category;


  category = "IndexLivingmall";
  strListNodeDataModels << category + ",LicensePlate"      + ",null";
  CiraBernoulliWidget::pluginTreeWidget->addNodeDataModels(strListNodeDataModels);


}
