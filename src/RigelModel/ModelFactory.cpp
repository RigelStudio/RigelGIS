#include "ModelFactory.h"

ModelFactory* ModelFactory::s_pSelf = nullptr;

ModelFactory* ModelFactory::ins()
{
	if (s_pSelf == nullptr)
	{
		s_pSelf = new ModelFactory;
	}
	return s_pSelf;
}

void ModelFactory::destory()
{
	if (s_pSelf == nullptr)
	{
		delete s_pSelf;
		s_pSelf = nullptr;
	}
}


RigelLayer* ModelFactory::addLayer(const std::string& name)
{
	RigelLayer* layer = getLayer(name);
	if (layer == nullptr)
	{
		layer = new RigelLayer;
		layer->setName(name);
		m_listLayer[name] = layer;
		addChild(layer);
	}
	return layer;
}

RigelLayer* ModelFactory::addLayer(RigelLayer* layer)
{
	m_listLayer[layer->getName()] = layer;
	addChild(layer);
	return layer;
}

RigelLayer* ModelFactory::getLayer(const std::string& name)
{
	auto layer = m_listLayer[name];
	return layer;
}

ModelBase* ModelFactory::getModel(RigelLayer* layer, const std::string& strID)
{
	if (layer != nullptr)
	{
		auto model = layer->getModel(strID);
		return model;
	}
	else
	{
		return nullptr;
	}
}

ModelBase* ModelFactory::getModel(const std::string& layerName, const std::string& strID)
{
	auto layer = getLayer(layerName);

	if (layer != nullptr)
	{
		auto model = layer->getModel(strID);
		return model;
	}
	else
	{
		return nullptr;
	}
}

ModelBase* ModelFactory::getModel(const std::string& strID)
{
	LayersList::iterator iter = m_listLayer.begin();
	ModelBase* model = nullptr;
	for (; iter != m_listLayer.end(); iter++)
	{
		model = iter->second->getModel(strID);
		if (model != nullptr)
		{
			break;
		}
	}
	return model;
}

void ModelFactory::addModel(RigelLayer* layer, ModelBase* model)
{
	if (layer != nullptr)
	{
		layer->addModel(model);
	}
}

void ModelFactory::addModel(const std::string& layerName, ModelBase* model)
{
	RigelLayer* layer = nullptr;
	layer = getLayer(layerName);
	if (layer == nullptr)
	{
		layer = addLayer(layerName);
	}
	if (layer != nullptr)
	{
		layer->addModel(model);
	}
}

ModelFactory::ModelFactory()
{
}


ModelFactory::~ModelFactory()
{
}

void ModelFactory::clearLayer(const std::string& layerName)
{
	RigelLayer* layer = getLayer(layerName);
	if (layer != nullptr)
	{
		layer->clear();
	}
}

void ModelFactory::removeModel(const std::string& layerName, ModelBase* model)
{
	RigelLayer* layer = nullptr;
	layer = getLayer(layerName);
	if (layer != nullptr)
	{
		layer->removeChild(model);
	}
}
