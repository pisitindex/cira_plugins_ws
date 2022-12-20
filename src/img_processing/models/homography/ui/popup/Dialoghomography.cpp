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

  param_js_data["spinBox_point1_x"] = ui->spinBox_point1_x->value();
  param_js_data["spinBox_point1_y"] = ui->spinBox_point1_y->value();
  param_js_data["spinBox_point2_x"] = ui->spinBox_point2_x->value();
  param_js_data["spinBox_point2_y"] = ui->spinBox_point2_y->value();
  param_js_data["spinBox_point3_x"] = ui->spinBox_point3_x->value();
  param_js_data["spinBox_point3_y"] = ui->spinBox_point3_y->value();
  param_js_data["spinBox_point4_x"] = ui->spinBox_point4_x->value();
  param_js_data["spinBox_point4_y"] = ui->spinBox_point4_y->value();

  param_js_data["using_ai"] = ui->checkBox_usingAI->isChecked();


  return param_js_data;
}

void Dialoghomography::restoreState(QJsonObject param_js_data) {

  ui->spinBox_vertical->setValue(param_js_data["spinBox_horizontal"].toInt());
  ui->spinBox_horizontal->setValue(param_js_data["spinBox_vertical"].toInt());

  ui->spinBox_point1_x->setValue(param_js_data["spinBox_point1_x"].toInt());
  ui->spinBox_point1_y->setValue(param_js_data["spinBox_point1_y"].toInt());
  ui->spinBox_point2_x->setValue(param_js_data["spinBox_point2_x"].toInt());
  ui->spinBox_point2_y->setValue(param_js_data["spinBox_point2_y"].toInt());
  ui->spinBox_point3_x->setValue(param_js_data["spinBox_point3_x"].toInt());
  ui->spinBox_point3_y->setValue(param_js_data["spinBox_point3_y"].toInt());
  ui->spinBox_point4_x->setValue(param_js_data["spinBox_point4_x"].toInt());
  ui->spinBox_point4_y->setValue(param_js_data["spinBox_point4_y"].toInt());


}
