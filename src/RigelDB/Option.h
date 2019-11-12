#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <osg/Vec4>
#include <osg/Vec3>

namespace Geo
{
	class Option
	{
    public:
        Option() {}
        virtual ~Option() {}

		void clear()
		{
			strID = "";
			strName = "";
			strType = "";
			strPath = "";
		}
	
		std::string strID;
		std::string strName;
		std::string strType;
		std::string strPath;
	};

    class ShpOption : public Option
	{
    public:
		float numWidth;
		float numMinRange;
		float numMaxRange;
		osg::Vec4 vColor;
		std::string strResource;
	};

    class ImageOption : public Option
	{
    public:

	};
}

#endif//OPTION_H