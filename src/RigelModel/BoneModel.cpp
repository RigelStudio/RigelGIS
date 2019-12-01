#include "BoneModel.h"
#include "RigelCore/MEMath.h"

BoneModel::BoneModel()
{
	m_pBone = nullptr;
	setNodeMask(Geo::NM_Bone);
}

BoneModel::~BoneModel()
{
}

void BoneModel::create(Geo::ModelOption& data)
{
	m_modelData = data;
	if (m_modelData.pModeNode == nullptr)
	{
		osg::notify(osg::FATAL) << "创建模型失败，请检查路径！" << std::endl;
	}
	else
	{
		m_pBone = new BoneAnimeNode(m_modelData.pModeNode);
		setPosLLH(data.llhPos);
		setScale(data.scale);
		setAngle(data.rotation);
		m_pNodeMT->addChild(m_pBone);
	}
	getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	m_pLogo = new PlaceNode;
	m_pLogo->setText(data.strName);
	m_pLogo->setFontSize(0.5);
	m_pLogo->setImage(data.strIcon);
	m_pLogo->setTextColor(osg::Vec4(1, 1, 0, 1));
	m_pLogo->setPosition(osg::Vec3(0, 0, 2.5));
	m_pLogo->setImageLod(100, 500000.0);
	m_pModelMT->addChild(m_pLogo);
}


void BoneModel::setModelText(const std::string& strName)
{
	m_pLogo->setText(strName);
}

void BoneModel::play(const std::string& animName)
{
	if (m_pBone != nullptr)
	{
		m_pBone->play(animName);
	}
}

void BoneModel::play(const size_t index/*= 0*/)
{
	if (m_pBone != nullptr)
	{
		auto listanime = m_pBone->getAnimationNameList();
		if (!listanime.empty())
		{
			m_pBone->play(listanime.at(index));
		}
	}
}

void BoneModel::stop()
{
	if (m_pBone != nullptr)
	{
		m_pBone->stop();
	}
}

osg::MatrixTransform* BoneModel::getModelMT()
{
	return m_pModelMT;
}
