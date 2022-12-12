#include "Dialoghomography.h"
#include "ui_Dialoghomography.h"

Dialoghomography::Dialoghomography(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialoghomography)
{
  ui->setupUi(this);
}

Dialoghomography::~Dialoghomography()
{
  delete ui;
}

QJsonObject Dialoghomography::saveState() {
  QJsonObject param_js_data;

  param_js_data["spinBox_horizontal"] = ui->spinBox_horizontal->value();
  param_js_data["spinBox_vertical"] = ui->spinBox_vertical->value();

  return param_js_data;
}

void Dialoghomography::restoreState(QJsonObject param_js_data) {

  ui->spinBox_vertical->setValue(param_js_data["spinBox_horizontal"].toInt());
  ui->spinBox_horizontal->setValue(param_js_data["spinBox_vertical"].toInt());

}
