#ifndef BONEMODEL_H
#define BONEMODEL_H

#include "Export.h"
#include "DynamicModel.h"
#include "BoneAnimeNode.h"

class RIGELMODEL_EXPORT BoneModel : public DynamicModel
{
public:
	BoneModel();
	virtual ~BoneModel();

	virtual void create(Geo::ModelOption& data);

	void setModelText(const std::string& strName);

	void play(const std::string& animName);

	void play(const size_t index = 0);

	void stop();

	osg::MatrixTransform* getModelMT();

protected:
	BoneAnimeNode* m_pBone;
};

#endif//BONEMODEL_H