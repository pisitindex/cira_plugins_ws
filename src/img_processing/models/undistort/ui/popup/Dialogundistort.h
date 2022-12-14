#ifndef Dialogundistort_H
#define Dialogundistort_H

#include <QDialog>
#include <QJsonObject>
#include <QEvent>

#include <iostream>

namespace Ui {
class Dialogundistort;
}

class Dialogundistort : public QDialog
{
  Q_OBJECT

public:
  explicit Dialogundistort(QWidget *parent = 0);
  ~Dialogundistort();

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

private slots:
  void on_pushButton_path_to_file_clicked();

private:
  Ui::Dialogundistort *ui;
  QString browse_camera_calibration_matrix();

};

#endif // Dialogundistort_H
