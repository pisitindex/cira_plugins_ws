#ifndef Formaffine_manual_H
#define Formaffine_manual_H

#include <QWidget>
#include <iostream>
#include <QMovie>
#include <QScreen>

#include "Threadaffine_manual.hpp"
#include <cira_lib_bernoulli/general/GlobalData.hpp>
#include "popup/Dialogaffine_manual.h"

namespace Ui {
class Formaffine_manual;
}

class Formaffine_manual : public QWidget
{
  Q_OBJECT

public:
  explicit Formaffine_manual(QWidget *parent = 0);
  ~Formaffine_manual();

  bool nodeStatus_enable = true;
  bool nodeStatus_ready = true;
  bool nodeStatus_complete = true;

  qint64 timestamp_base = 0;
  qint64 timestamp_input = -1;

  bool isHaveError = false;

  QString style_nodeDisable = "background-color: transparent; border-image: url(:/img_processing/icon/node_disable.png); background: none; border: none; background-repeat: none;";
  QString style_nodeEnable = "background-color: transparent; border-image: url(:/img_processing/icon/node_enable.png); background: none; border: none; background-repeat: none;";

  QMovie *mv_node_run;

  Threadaffine_manual *workerThread;
  Dialogaffine_manual *dialog;

public slots:
  void update_ui();

private slots:
  void stop_node_process();
  void on_pushButton_nodeEnable_clicked();
  void on_pushButton_prop_clicked();

private:
  Ui::Formaffine_manual *ui;
};

#endif // Formaffine_manual_H
