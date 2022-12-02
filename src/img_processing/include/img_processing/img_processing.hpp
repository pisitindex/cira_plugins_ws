#ifndef img_processing_HPP
#define img_processing_HPP

#include <cira_lib_bernoulli/plugin/ciraloader_base.h>

class img_processing : public CiRALoader
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "teerawat.CiRACORE.CiRALoader")
  Q_INTERFACES(CiRALoader)

public:
  img_processing();

  virtual std::shared_ptr<DataModelRegistry> registerDataModels(std::shared_ptr<DataModelRegistry> ret) override;

  virtual void setTreeWidget() override;

  virtual const QString name() const override
  {
    return info()["name"].toString();
  }

  virtual const QJsonObject info() const override
  {
    QJsonObject jso;
    jso["name"] = "img_processing";
    jso["version"] = "0.0.0";
    jso["maintainer"] = "anonymous";
    jso["email"] = "";

    return jso;
  }

};

#endif // img_processing_HPP
