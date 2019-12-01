#include "BoneAnimeVisitor.h"

BoneAnimeVisitor::BoneAnimeVisitor()
	:osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ACTIVE_CHILDREN)
{
}


BoneAnimeVisitor::~BoneAnimeVisitor()
{
}

void BoneAnimeVisitor::apply(osg::Node& node)
{
	osg::ref_ptr<osgAnimation::AnimationManagerBase> amb =
		dynamic_cast<osgAnimation::AnimationManagerBase*>(node.getUpdateCallback());
	if (amb.valid())
	{
		m_pManager = new osgAnimation::BasicAnimationManager(*amb);
		amb.release();
		return;
	}
	traverse(node);
}
