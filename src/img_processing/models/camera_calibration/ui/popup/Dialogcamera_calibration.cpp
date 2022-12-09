#include "Dialogcamera_calibration.h"
#include "ui_Dialogcamera_calibration.h"
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <cira_lib_bernoulli/general/GlobalData.hpp>
#include <QPixmap>


Dialogcamera_calibration::Dialogcamera_calibration(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialogcamera_calibration)
{
  ui->setupUi(this);
}

Dialogcamera_calibration::~Dialogcamera_calibration()
{
  delete ui;
}

QJsonObject Dialogcamera_calibration::saveState() {
  QJsonObject param_js_data;
  param_js_data["label_folder_path"]  = ui->label_folder_path->text();
  param_js_data["spinBox_pattern_horizontal"] = ui->spinBox_pattern_horizontal->value();
  param_js_data["spinBox_pattern_vertical"] = ui->spinBox_pattern_vertical->value();
  param_js_data["spinBox_resolutions_horizontal"] = ui->spinBox_resolutions_horizontal->value();
  param_js_data["spinBox_resolutions_vertical"] = ui->spinBox_resolutions_vertical->value();
  return param_js_data;
}

void Dialogcamera_calibration::restoreState(QJsonObject param_js_data) {
    ui->label_folder_path->setText(param_js_data["label_folder_path"].toString());
    ui->spinBox_pattern_vertical->setValue(param_js_data["spinBox_pattern_vertical"].toInt());
    ui->spinBox_pattern_horizontal->setValue(param_js_data["spinBox_pattern_horizontal"].toInt());
    ui->spinBox_resolutions_vertical->setValue(param_js_data["spinBox_resolutions_vertical"].toInt());
    ui->spinBox_resolutions_horizontal->setValue(param_js_data["spinBox_resolutions_horizontal"].toInt());
}


QString Dialogcamera_calibration::open_folder_dialog(){
    QString select_folder = QFileDialog::getExistingDirectory(this, "Choose Folder", QDir::homePath());
        if(!select_folder.isEmpty()) {
          tmp_folder = select_folder;
          qDebug() << tmp_folder;
          return tmp_folder;
        }
        if(select_folder.isEmpty()) return "";
}

void Dialogcamera_calibration::on_pushButton_folder_path_clicked()
{
    ui->label_folder_path->setText(Dialogcamera_calibration::open_folder_dialog());
}


