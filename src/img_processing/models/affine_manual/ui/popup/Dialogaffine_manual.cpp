#include "Dialogaffine_manual.h"
#include "ui_Dialogaffine_manual.h"

Dialogaffine_manual::Dialogaffine_manual(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialogaffine_manual)
{
  ui->setupUi(this);
}

Dialogaffine_manual::~Dialogaffine_manual()
{
  delete ui;
}

QJsonObject Dialogaffine_manual::saveState() {
  QJsonObject param_js_data;

  return param_js_data;
}

void Dialogaffine_manual::restoreState(QJsonObject param_js_data) {

}
