#ifndef BUILDINGMODEL_H
#define BUILDINGMODEL_H

#include "ModelBase.h"

class RIGELMODEL_EXPORT StaticModel : public ModelBase
{
public:
	StaticModel();
	virtual ~StaticModel();

	virtual void create(Geo::ModelOption& data);

};

#endif//BUILDINGMODEL_H