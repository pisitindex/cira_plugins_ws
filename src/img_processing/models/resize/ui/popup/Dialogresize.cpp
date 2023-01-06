#include "Dialogresize.h"
#include "ui_Dialogresize.h"

Dialogresize::Dialogresize(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialogresize)
{
  ui->setupUi(this);
}

Dialogresize::~Dialogresize()
{
  delete ui;
}

QJsonObject Dialogresize::saveState() {
  QJsonObject param_js_data;

  return param_js_data;
}

void Dialogresize::restoreState(QJsonObject param_js_data) {

}
