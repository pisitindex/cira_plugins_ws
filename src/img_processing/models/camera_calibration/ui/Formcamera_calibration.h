#ifndef Formcamera_calibration_H
#define Formcamera_calibration_H

#include <QWidget>
#include <iostream>
#include <QMovie>
#include <QScreen>

#include "Threadcamera_calibration.hpp"
#include <cira_lib_bernoulli/general/GlobalData.hpp>
#include "popup/Dialogcamera_calibration.h"

namespace Ui {
class Formcamera_calibration;
}

class Formcamera_calibration : public QWidget
{
  Q_OBJECT

public:
  explicit Formcamera_calibration(QWidget *parent = 0);
  ~Formcamera_calibration();

  bool nodeStatus_enable = true;
  bool nodeStatus_ready = true;
  bool nodeStatus_complete = true;

  qint64 timestamp_base = 0;
  qint64 timestamp_input = -1;

  bool isHaveError = false;

  QString style_nodeDisable = "background-color: transparent; border-image: url(:/img_processing/icon/node_disable.png); background: none; border: none; background-repeat: none;";
  QString style_nodeEnable = "background-color: transparent; border-image: url(:/img_processing/icon/node_enable.png); background: none; border: none; background-repeat: none;";

  QMovie *mv_node_run;

  Threadcamera_calibration *workerThread;
  Dialogcamera_calibration *dialog;

public slots:
  void update_ui();

private slots:
  void stop_node_process();
  void on_pushButton_nodeEnable_clicked();
  void on_pushButton_prop_clicked();

private:
  Ui::Formcamera_calibration *ui;
};

#endif // Formcamera_calibration_H
