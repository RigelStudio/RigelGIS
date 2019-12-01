#ifndef BONEANIMENODE_H
#define BONEANIMENODE_H

#include "BoneAnimeVisitor.h"
#include <osg/MatrixTransform>

typedef std::vector<std::string> NameList;

class BoneAnimeNode : public osg::MatrixTransform
{
public:
	BoneAnimeNode(osg::Node* node);
	virtual ~BoneAnimeNode();

	void play(const std::string& animName);

	void stop();

	bool isPlaying(const std::string& animName);

	const NameList getAnimationNameList() { return m_nameList; };


private:
	void init(osg::Node* node);

private:
	NameList m_nameList;
	osgAnimation::BasicAnimationManager* m_pManager;
	osgAnimation::AnimationMap  m_animationMap;
};

#endif//BONEANIMENODE_H