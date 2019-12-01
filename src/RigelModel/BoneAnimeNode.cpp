#include "BoneAnimeNode.h"
BoneAnimeNode::BoneAnimeNode(osg::Node* node)
{
	m_pManager = nullptr;
	init(node);
	addChild(node);
}


BoneAnimeNode::~BoneAnimeNode()
{
}

void BoneAnimeNode::play(const std::string& animName)
{
	if (isPlaying(animName))
	{
		return;
	}
	stop();
	if (m_pManager != NULL)
	{
		m_pManager->playAnimation(m_animationMap[animName]);
	}
}

void BoneAnimeNode::stop()
{
	if (m_pManager != NULL)
	{
		m_pManager->stopAll();
	}
}

bool BoneAnimeNode::isPlaying(const std::string& animName)
{
	if (m_pManager == nullptr)
	{
		return false;
	}
	return m_pManager->isPlaying(animName);
}

void BoneAnimeNode::init(osg::Node* node)
{
	m_nameList.clear();
	m_animationMap.clear();

	BoneAnimeVisitor finder;
	node->accept(finder);
	m_pManager = finder.getAnimeManager();
	if (m_pManager != NULL)
	{
		node->setUpdateCallback(m_pManager);

		auto iter = m_pManager->getAnimationList().begin();
		for (; iter != m_pManager->getAnimationList().end(); iter++)
		{
			std::string strTemp = (*iter)->getName();
			m_nameList.push_back(strTemp);
			m_animationMap[strTemp] = *iter;
		}
	}
	else
	{
		std::cout << "FBX模型初始化失败;" << std::endl;
	}
}
