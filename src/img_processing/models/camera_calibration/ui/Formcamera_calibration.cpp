#include "Formcamera_calibration.h"
#include "ui_Formcamera_calibration.h"

Formcamera_calibration::Formcamera_calibration(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Formcamera_calibration)
{
  ui->setupUi(this);

  timestamp_base = GlobalData::timer.nsecsElapsed();
  nodeStatus_ready = true;

  workerThread = new Threadcamera_calibration();
  dialog = new Dialogcamera_calibration();

  mv_node_run = new QMovie(":/img_processing/icon/run_led.gif");
  update_ui();
  connect(GlobalData::GlobalDataObject, SIGNAL(stopAllScene()), this, SLOT(stop_node_process()));
}

Formcamera_calibration::~Formcamera_calibration()
{
  delete ui;
}

void Formcamera_calibration::on_pushButton_nodeEnable_clicked()
{
  if(nodeStatus_enable) {
    ui->pushButton_nodeEnable->setStyleSheet(style_nodeDisable);
    nodeStatus_enable = false;
  } else {
    ui->pushButton_nodeEnable->setStyleSheet(style_nodeEnable);
    timestamp_base = GlobalData::timer.nsecsElapsed();
    nodeStatus_enable = true;
  }
}

void Formcamera_calibration::on_pushButton_prop_clicked()
{
  dialog->setWindowModality(Qt::NonModal); dialog->setParent(GlobalData::parent);
  dialog->setWindowFlags( /*Qt::WindowTitleHint | Qt::FramelessWindowHint |*/
                                      Qt::Window |  Qt::WindowCloseButtonHint /* | Qt::Popup*/);

  if(ui->label->pixmap()) dialog->setWindowIcon(QIcon(   *ui->label->pixmap()   ));

  QSize size = qApp->screens()[0]->size();
  QPoint p = QCursor::pos();
  int w = size.width();
  int h = size.height();
  int x = p.x();
  int y = p.y();
  if(x + dialog->width() > w) {
    x -= x + dialog->width() - w;
  }
  if(y + dialog->height() > h) {
    y -= y + dialog->height() - h;
  }

  dialog->move(x, y);
  dialog->setVisible(true);
}
