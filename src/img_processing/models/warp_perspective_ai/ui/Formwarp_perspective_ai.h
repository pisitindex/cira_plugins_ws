#ifndef Formwarp_perspective_ai_H
#define Formwarp_perspective_ai_H

#include <QWidget>
#include <iostream>
#include <QMovie>
#include <QScreen>

#include "Threadwarp_perspective_ai.hpp"
#include <cira_lib_bernoulli/general/GlobalData.hpp>
#include "popup/Dialogwarp_perspective_ai.h"

namespace Ui {
class Formwarp_perspective_ai;
}

class Formwarp_perspective_ai : public QWidget
{
  Q_OBJECT

public:
  explicit Formwarp_perspective_ai(QWidget *parent = 0);
  ~Formwarp_perspective_ai();

  bool nodeStatus_enable = true;
  bool nodeStatus_ready = true;
  bool nodeStatus_complete = true;

  qint64 timestamp_base = 0;
  qint64 timestamp_input = -1;

  bool isHaveError = false;

  QString style_nodeDisable = "background-color: transparent; border-image: url(:/img_processing/icon/node_disable.png); background: none; border: none; background-repeat: none;";
  QString style_nodeEnable = "background-color: transparent; border-image: url(:/img_processing/icon/node_enable.png); background: none; border: none; background-repeat: none;";

  QMovie *mv_node_run;

  Threadwarp_perspective_ai *workerThread;
  Dialogwarp_perspective_ai *dialog;

public slots:
  void update_ui();

private slots:
  void stop_node_process();
  void on_pushButton_nodeEnable_clicked();
  void on_pushButton_prop_clicked();

private:
  Ui::Formwarp_perspective_ai *ui;
};

#endif // Formwarp_perspective_ai_H
