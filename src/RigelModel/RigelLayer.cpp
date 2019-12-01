#include "RigelLayer.h"



RigelLayer::RigelLayer()
{
}


RigelLayer::~RigelLayer()
{
}

void RigelLayer::clear()
{
	this->removeChildren(0, this->getNumChildren());
	m_listModel.clear();
}

void RigelLayer::addModel(ModelBase* model)
{
	if (model != nullptr)
	{
		addChild(model);
		auto theID = model->getData().strID;
		m_listModel[theID] = model;
	}
	else
	{
		osg::notify(osg::FATAL) << "RigelLayer::addModel Ìí¼ÓÄ£ÐÍÊ§°Ü" << std::endl;
	}
}

ModelBase* RigelLayer::getModel(const std::string& strID)
{
	auto model = m_listModel[strID];

	return model;
}

