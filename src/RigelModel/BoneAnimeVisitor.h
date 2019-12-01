#ifndef BONEANIMEMANAGER_H
#define BONEANIMEMANAGER_H

#include <osg/NodeVisitor>
#include <osgAnimation/BasicAnimationManager>

class BoneAnimeVisitor : public osg::NodeVisitor
{
public:
	BoneAnimeVisitor();
	virtual ~BoneAnimeVisitor();

	osgAnimation::BasicAnimationManager* getAnimeManager() { return m_pManager; };

protected:
	void apply(osg::Node& node);

private:
	osg::ref_ptr<osgAnimation::BasicAnimationManager> m_pManager;
};

#endif//BONEANIMEMANAGER_H