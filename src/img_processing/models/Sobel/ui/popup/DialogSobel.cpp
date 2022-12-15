#include "DialogSobel.h"
#include "ui_DialogSobel.h"

DialogSobel::DialogSobel(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogSobel)
{
  ui->setupUi(this);
}

DialogSobel::~DialogSobel()
{
  delete ui;
}

QJsonObject DialogSobel::saveState() {
  QJsonObject param_js_data;

  param_js_data["mode"] = ui->comboBox_mode->currentText();

  return param_js_data;
}

void DialogSobel::restoreState(QJsonObject param_js_data) {
  ui->comboBox_mode->setCurrentText(param_js_data["mode"].toString());
}
