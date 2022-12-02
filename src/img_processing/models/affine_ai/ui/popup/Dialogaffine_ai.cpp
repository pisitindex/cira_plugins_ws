#include "Dialogaffine_ai.h"
#include "ui_Dialogaffine_ai.h"

Dialogaffine_ai::Dialogaffine_ai(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialogaffine_ai)
{
  ui->setupUi(this);
}

Dialogaffine_ai::~Dialogaffine_ai()
{
  delete ui;
}

QJsonObject Dialogaffine_ai::saveState() {
  QJsonObject param_js_data;

  return param_js_data;
}

void Dialogaffine_ai::restoreState(QJsonObject param_js_data) {

}
