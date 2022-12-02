#include "Dialogundistort.h"
#include "ui_Dialogundistort.h"

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

  return param_js_data;
}

void Dialogundistort::restoreState(QJsonObject param_js_data) {

}
