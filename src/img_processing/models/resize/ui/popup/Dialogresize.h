#ifndef Dialogresize_H
#define Dialogresize_H

#include <QDialog>
#include <QJsonObject>
#include <QEvent>

#include <iostream>

namespace Ui {
class Dialogresize;
}

class Dialogresize : public QDialog
{
  Q_OBJECT

public:
  explicit Dialogresize(QWidget *parent = 0);
  ~Dialogresize();

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
  Ui::Dialogresize *ui;
};

#endif // Dialogresize_H
