#ifndef Dialoghomography_H
#define Dialoghomography_H

#include <QDialog>
#include <QJsonObject>
#include <QEvent>

#include <iostream>

namespace Ui {
class Dialoghomography;
}

class Dialoghomography : public QDialog
{
  Q_OBJECT

public:
  explicit Dialoghomography(QWidget *parent = 0);
  ~Dialoghomography();

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
  Ui::Dialoghomography *ui;
};

#endif // Dialoghomography_H
