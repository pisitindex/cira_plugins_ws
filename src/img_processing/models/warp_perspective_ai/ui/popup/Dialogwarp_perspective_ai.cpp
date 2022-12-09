#include "Dialogwarp_perspective_ai.h"
#include "ui_Dialogwarp_perspective_ai.h"

Dialogwarp_perspective_ai::Dialogwarp_perspective_ai(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialogwarp_perspective_ai)
{
  ui->setupUi(this);
}

Dialogwarp_perspective_ai::~Dialogwarp_perspective_ai()
{
  delete ui;
}

QJsonObject Dialogwarp_perspective_ai::saveState() {
  QJsonObject param_js_data;

  return param_js_data;
}

void Dialogwarp_perspective_ai::restoreState(QJsonObject param_js_data) {

}
