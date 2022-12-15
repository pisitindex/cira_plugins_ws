#ifndef FormSobel_H
#define FormSobel_H

#include <QWidget>
#include <iostream>
#include <QMovie>
#include <QScreen>

#include "ThreadSobel.hpp"
#include <cira_lib_bernoulli/general/GlobalData.hpp>
#include "popup/DialogSobel.h"

namespace Ui {
class FormSobel;
}

class FormSobel : public QWidget
{
  Q_OBJECT

public:
  explicit FormSobel(QWidget *parent = 0);
  ~FormSobel();

  bool nodeStatus_enable = true;
  bool nodeStatus_ready = true;
  bool nodeStatus_complete = true;

  qint64 timestamp_base = 0;
  qint64 timestamp_input = -1;

  bool isHaveError = false;

  QString style_nodeDisable = "background-color: transparent; border-image: url(:/img_processing/icon/node_disable.png); background: none; border: none; background-repeat: none;";
  QString style_nodeEnable = "background-color: transparent; border-image: url(:/img_processing/icon/node_enable.png); background: none; border: none; background-repeat: none;";

  QMovie *mv_node_run;

  ThreadSobel *workerThread;
  DialogSobel *dialog;

public slots:
  void update_ui();

private slots:
  void stop_node_process();
  void on_pushButton_nodeEnable_clicked();
  void on_pushButton_prop_clicked();

private:
  Ui::FormSobel *ui;
};

#endif // FormSobel_H
