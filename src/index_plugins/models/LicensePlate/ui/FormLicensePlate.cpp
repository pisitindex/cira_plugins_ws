#include "FormLicensePlate.h"
#include "ui_FormLicensePlate.h"

FormLicensePlate::FormLicensePlate(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormLicensePlate)
{
  ui->setupUi(this);

  timestamp_base = GlobalData::timer.nsecsElapsed();
  nodeStatus_ready = true;

  workerThread = new ThreadLicensePlate();
  dialog = new DialogLicensePlate();

  mv_node_run = new QMovie(":/index_plugins/icon/run_led.gif");
  update_ui();
  connect(GlobalData::GlobalDataObject, SIGNAL(stopAllScene()), this, SLOT(stop_node_process()));
}

FormLicensePlate::~FormLicensePlate()
{
  delete ui;
}

void FormLicensePlate::on_pushButton_nodeEnable_clicked()
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

void FormLicensePlate::on_pushButton_prop_clicked()
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
