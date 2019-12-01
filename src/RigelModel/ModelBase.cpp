#include "ModelBase.h"
#include "RigelCore/MEMath.h"
#include "RigelCore/OECore.h"

#include <osgEarth\GeoData>

ModelBase::ModelBase()
{
	m_pModelMT = new osg::MatrixTransform;
	m_pNodeMT = new osg::MatrixTransform;
	m_pModelMT->addChild(m_pNodeMT);
	addChild(m_pModelMT);
	m_pLogo = nullptr;
}


ModelBase::~ModelBase()
{
}


void ModelBase::setScale(float scale)
{
	//ÉèÖÃËõ·Å
	osg::Matrix sMat = osg::Matrix::scale(scale, scale, scale);
	osg::Matrix mat = m_pNodeMT->getMatrix();
	m_pNodeMT->setMatrix(sMat * mat);

}

void ModelBase::setAngle(float angleX, float angleY, float angleZ)
{
	//
}

void ModelBase::setAngle(osg::Vec3& rotate)
{
	float radianX = osg::DegreesToRadians(rotate.x());
	float radianY = osg::DegreesToRadians(rotate.y());
	float radianZ = osg::DegreesToRadians(rotate.z());

	osg::Quat quatX, quatY, quatZ;
	quatX = osg::Quat(radianX, osg::X_AXIS);
	quatY = osg::Quat(radianY, osg::Y_AXIS);
	quatZ = osg::Quat(radianZ, osg::Z_AXIS);

	auto quat = quatX * quatY * quatZ;
	osg::Matrixd matS = m_pNodeMT->getMatrix();
	osg::Matrixd matR = osg::Matrixd::rotate(quat);
	m_pNodeMT->setMatrix(matS * matR);
}

Geo::ModelOption& ModelBase::getData()
{
	return m_modelData;
}

void ModelBase::setSelected(bool isSelect)
{
	//none
}

void ModelBase::setPosLLH(osg::Vec3d& llhPos)
{
	GeoPoint point = GeoPoint(OECore::ins()->getMapSRS(), llhPos);
	setPosition(point);
}

void ModelBase::setPosLL(double x, double y)
{
	auto geoPos = osgEarth::GeoPoint(OECore::ins()->getMapSRS(), x, y);
	setPosition(geoPos);
}

void ModelBase::setFont(std::string& strFont)
{
	if (m_pLogo != nullptr)
	{
		m_pLogo->setFont(strFont);
	}
}
