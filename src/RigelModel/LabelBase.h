#ifndef LABELBASE_H
#define LABELBASE_H
#include "Export.h"
#include <osgText/Text>
#include <osgText/TextBase>
#include <osg/AutoTransform>
#include <osg/Lod>

using namespace osgText;

class RIGELMODEL_EXPORT LabelBase : public osg::LOD
{
public:
	LabelBase(void);
	~LabelBase(void);

	enum AlignType
	{
		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT
	};

	enum HaloType
	{
		NONE_HALO,
		HALO,
		SHADOW
	};

	enum BackType
	{
		NONE_BACK,
		LINE_BOX,
		FILL_BOX
	};
	
	//���ñ�ע��Ϣ;
	void setText(const std::string text);
	void setText(const std::wstring wtext);
	std::string getText(){return m_strText;}
	std::wstring getWText(){return m_wstrText;}
	
	//����������ɫ;
	void setTextColor(const osg::Vec4 color);
	osg::Vec4 getTextColor(){return m_vecTextColor;}

	//��������;
	void setFont(const std::string font);
	std::string getFont(){return m_strFont;}

	//�������ִ�С;
	void setFontSize(const float size);
	float getFontSize(){return m_numTextSize;}

	
	void setPosition(osg::Vec3& postion);

	//���ù��ο��(ȡֵ��Χ��0~1֮��);
	void setHaloSize(const float size);
	float getHaloSize(){return m_numHaloSize*10.0f;}

	//���ù���ģʽ;
	void setHaloMode(const HaloType type);
	int	getHaloMode(){return m_enumHalo;}

	//���ù�����ɫ;
	void setHaloColor(const osg::Vec4 color);
	osg::Vec4 getHaloColor(){return m_vecHaloColor;}


	//���ö��뷽ʽ;
	void setAlignment(const AlignType type);
	int	getAlignment(){return m_enumAlign;}

	//���ñ���ģʽ;
	void setBackMode(const BackType type);
	int	getBackMode(){return m_enumBack;}

	//���ñ�����ɫ;
	void setBackColor(const osg::Vec4 color);
	osg::Vec4 getBackColor(){return m_vecBackColor;}


	//���osgText::Text�ڵ�;
	osgText::Text* getTextNode() { return m_pTextNode;}

	//���ð󶨵Ľڵ�;
	void setBindNode(osg::Node* node);

private:
	virtual void update() = 0;

protected:
	float m_numHaloSize;
	float m_numTextSize;
	std::string m_strText;
	std::string m_strFont;
	std::wstring m_wstrText;
	osg::Vec4 m_vecTextColor;
	osg::Vec4 m_vecBackColor;
	osg::Vec4 m_vecHaloColor;
	osg::Vec3 m_vecPosition;
	size_t m_enumBack;
	Text::BackdropType m_enumHalo;
	Text::AlignmentType m_enumAlign;
	osg::AutoTransform* m_pAutoGroup;
	osg::ref_ptr<osgText::Text> m_pTextNode;
	osg::ref_ptr < osg::Geode> m_pGeodeNode;
};

#endif//LABELBASE_H