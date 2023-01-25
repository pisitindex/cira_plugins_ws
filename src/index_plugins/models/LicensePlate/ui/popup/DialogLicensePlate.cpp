#include "DialogLicensePlate.h"
#include "ui_DialogLicensePlate.h"

DialogLicensePlate::DialogLicensePlate(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogLicensePlate)
{
  ui->setupUi(this);
}

DialogLicensePlate::~DialogLicensePlate()
{
  delete ui;
}

QJsonObject DialogLicensePlate::saveState() {
  QJsonObject param_js_data;

  return param_js_data;
}

void DialogLicensePlate::restoreState(QJsonObject param_js_data) {

}
