#include "Dialogundistort.h"
#include "ui_Dialogundistort.h"
#include <QDebug>
#include <QFileDialog>

Dialogundistort::Dialogundistort(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialogundistort)
{
  ui->setupUi(this);
}

Dialogundistort::~Dialogundistort()
{
  delete ui;
}

QJsonObject Dialogundistort::saveState() {
  QJsonObject param_js_data;
  param_js_data["path_to_file"] = ui->label_path_to_file->text();

  return param_js_data;
}

void Dialogundistort::restoreState(QJsonObject param_js_data) {
  ui->label_path_to_file->setText(param_js_data["path_to_file"].toString());
}

QString Dialogundistort::browse_camera_calibration_matrix(){
    QString tmp_config;
    QString select_config = QFileDialog::getOpenFileName(
                    nullptr,
                    tr("Open calibration matrix"),
                    tmp_config,
                    tr("*.yml"),0,QFileDialog::DontUseNativeDialog);

    if(!select_config.isEmpty()) {
      tmp_config = select_config;
      qDebug() << tmp_config;
      return tmp_config;
    }
    if(select_config.isEmpty()) return "";
}

void Dialogundistort::on_pushButton_path_to_file_clicked()
{
   ui->label_path_to_file->setText(Dialogundistort::browse_camera_calibration_matrix());
}
