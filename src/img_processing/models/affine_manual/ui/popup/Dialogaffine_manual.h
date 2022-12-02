#ifndef Dialogaffine_manual_H
#define Dialogaffine_manual_H

#include <QDialog>
#include <QJsonObject>
#include <QEvent>

#include <iostream>

namespace Ui {
class Dialogaffine_manual;
}

class Dialogaffine_manual : public QDialog
{
  Q_OBJECT

public:
  explicit Dialogaffine_manual(QWidget *parent = 0);
  ~Dialogaffine_manual();

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

  QString style_unpin = "background-color: transparent; border-image: url(:/img_processing/icon/unpin.png); background: none; border: none; background-repeat: none;";
  QString style_pin = "background-color: transparent; border-image: url(:/img_processing/icon/pin.png); background: none; border: none; background-repeat: none;";

  QJsonObject saveState();
  void restoreState(QJsonObject param_js_data);

private:
  Ui::Dialogaffine_manual *ui;
};

#endif // Dialogaffine_manual_H
