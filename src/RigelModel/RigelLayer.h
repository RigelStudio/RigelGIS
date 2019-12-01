#ifndef RIGELLAYER_H
#define RIGELLAYER_H
#include <osg/Group>
#include "ModelBase.h"

typedef std::map<std::string, ModelBase*> ModelList;

class RigelLayer : public osg::Group
{
public:
	RigelLayer();
	~RigelLayer();

	void clear();

	void addModel(ModelBase* model);
	ModelBase* getModel(const std::string& strID);


private:
	ModelList m_listModel;
};

#endif//RIGELLAYER_H