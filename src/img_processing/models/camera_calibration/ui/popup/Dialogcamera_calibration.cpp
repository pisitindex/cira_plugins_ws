#include "Dialogcamera_calibration.h"
#include "ui_Dialogcamera_calibration.h"
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <cira_lib_bernoulli/general/GlobalData.hpp>



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
  qDebug() << ui->label_folder_path->text();
  return param_js_data;
}

void Dialogcamera_calibration::restoreState(QJsonObject param_js_data) {
    ui->label_folder_path->setText(param_js_data["label_folder_path"].toString());
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


