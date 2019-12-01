#include "Export.h"
#include "RigelLayer.h"

typedef std::map<std::string, RigelLayer*> LayersList;

class RIGELMODEL_EXPORT ModelFactory : public osg::Group
{
public:
	static ModelFactory* ins();
	static void destory();

	template<typename T>
	static T* create(Geo::ModelOption& data) 
	{
		T* model = new T();
		model->create(data);
		return model;
	};

	RigelLayer* addLayer(RigelLayer* layer);
	RigelLayer* addLayer(const std::string& name);
	RigelLayer* getLayer(const std::string& name);

	void addModel(RigelLayer* layer, ModelBase* model);
	ModelBase* getModel(RigelLayer* layer, const std::string& strID);

	void addModel(const std::string& layerName, ModelBase* model);

	ModelBase* getModel(const std::string& layerName, const std::string& strID);
	ModelBase* getModel(const std::string& strID);

	void removeModel(const std::string& layerName, ModelBase* model);

	void clearLayer(const std::string& layerName);

private:
	ModelFactory();
	~ModelFactory();

private:
	static ModelFactory* s_pSelf;
	LayersList m_listLayer;

};


