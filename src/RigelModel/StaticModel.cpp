#include "StaticModel.h"


StaticModel::StaticModel()
{
	setNodeMask(Geo::NM_Building);
}


StaticModel::~StaticModel()
{
}

void StaticModel::create(Geo::ModelOption& data)
{
	m_modelData = data;
	if (m_modelData.pModeNode == nullptr)
	{
		osg::notify(osg::FATAL) << "创建模型失败，请检查路径！" << std::endl;
	}
	else
	{
		setPosLLH(data.llhPos);
		setScale(data.scale);
		setAngle(data.rotation);
		m_pNodeMT->addChild(m_modelData.pModeNode);
	}
	getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

// 	m_pLogo = new PlaceNode;
// 	m_pLogo->setText(data.strName);
// 	m_pLogo->setFontSize(0.5);
// 	m_pLogo->setImage(data.strIcon);
// 	m_pLogo->setTextColor(osg::Vec4(1, 1, 0, 1));
// 	m_pLogo->setPosition(osg::Vec3(0, 0, 2.0));
// 	m_pLogo->setImageLod(100, 500000.0);
// 	m_pModelMT->addChild(m_pLogo);
}

