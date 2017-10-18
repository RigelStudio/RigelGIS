#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <osg/Vec4>
#include <osg/Vec3>

namespace Geo
{
	struct Option
	{
		virtual void clear()
		{
			strID = "";
			strName = "";
			strType = "";
			strPath = "";
		}

	public:
		std::string strID;
		std::string strName;
		std::string strType;
		std::string strPath;
	};

	struct ShpOption : public Option
	{
		float numWidth;
		float numMinRange;
		float numMaxRange;
		osg::Vec4 vColor;
		std::string strResource;
	};

	struct ImageOption : public Option
	{

	};
}

#endif//OPTION_H