#ifndef SYMBOLMODEL_H
#define SYMBOLMODEL_H

#include "Export.h"
#include "ModelBase.h"
#include "PlaceNode.h"

class RIGELMODEL_EXPORT SymbolModel : public ModelBase
{
public:
	SymbolModel();
	~SymbolModel();

	virtual void create(Geo::ModelOption& data);

	void setTextPosition(osg::Vec3& pos);

	void setTextVisiable(bool isShow);

	virtual Geo::GPSOption& getData();

private:
	Geo::GPSOption m_gpsData;
};

#endif//SYMBOLMODEL_H