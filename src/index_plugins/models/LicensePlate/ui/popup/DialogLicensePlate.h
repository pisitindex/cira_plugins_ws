#ifndef DialogLicensePlate_H
#define DialogLicensePlate_H

#include <QDialog>
#include <QJsonObject>
#include <QEvent>

#include <iostream>

namespace Ui {
class DialogLicensePlate;
}

class DialogLicensePlate : public QDialog
{
  Q_OBJECT

public:
  explicit DialogLicensePlate(QWidget *parent = 0);
  ~DialogLicensePlate();

  void changeEvent(QEvent *ev) {
    if (ev->type() == QEvent::ActivationChange)
    {
        if(this->isActiveWindow())
        {

        }
        else
        {
          if(!isPin) {
            this->close();
          }
        }
    }
  }

  bool isPin = true;

  QString style_unpin = "background-color: transparent; border-image: url(:/index_plugins/icon/unpin.png); background: none; border: none; background-repeat: none;";
  QString style_pin = "background-color: transparent; border-image: url(:/index_plugins/icon/pin.png); background: none; border: none; background-repeat: none;";

  QJsonObject saveState();
  void restoreState(QJsonObject param_js_data);

private:
  Ui::DialogLicensePlate *ui;
};

#endif // DialogLicensePlate_H
