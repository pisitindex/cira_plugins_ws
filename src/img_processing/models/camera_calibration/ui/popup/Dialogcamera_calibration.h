#ifndef Dialogcamera_calibration_H
#define Dialogcamera_calibration_H

#include <QDialog>
#include <QJsonObject>
#include <QEvent>

#include <iostream>

namespace Ui {
class Dialogcamera_calibration;
}

class Dialogcamera_calibration : public QDialog
{
  Q_OBJECT

public:
  explicit Dialogcamera_calibration(QWidget *parent = 0);
  ~Dialogcamera_calibration();

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
  QString select_folder;
  QString tmp_folder;

  QString style_unpin = "background-color: transparent; border-image: url(:/img_processing/icon/unpin.png); background: none; border: none; background-repeat: none;";
  QString style_pin = "background-color: transparent; border-image: url(:/img_processing/icon/pin.png); background: none; border: none; background-repeat: none;";

  QJsonObject saveState();
  void restoreState(QJsonObject param_js_data);

private slots:
  void on_pushButton_folder_path_clicked();
  QString open_folder_dialog();

private:
  Ui::Dialogcamera_calibration *ui;
};

#endif // Dialogcamera_calibration_H
