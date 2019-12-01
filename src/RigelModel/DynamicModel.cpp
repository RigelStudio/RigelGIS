#include "DynamicModel.h"
#include "RigelCore/MEMath.h"

DynamicModel::DynamicModel()
{
	setNodeMask(Geo::NM_Dynamic);
	setDataVariance(Object::DYNAMIC);
	m_pPathCallback = nullptr;
	m_pAnimaPath = nullptr;
	m_pPathArray = nullptr;
}

DynamicModel::~DynamicModel()
{
	m_pPathArray = nullptr;
}

void DynamicModel::create(Geo::ModelOption& data)
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

	m_pLogo = new PlaceNode;
	m_pLogo->setText(data.strName);
	m_pLogo->setFontSize(5.0);
	m_pLogo->setImage(data.strIcon);
	m_pLogo->setTextColor(osg::Vec4(1, 1, 0, 1));
	m_pLogo->setPosition(osg::Vec3(0, 0, 2.0));
	m_pLogo->setImageLod(100, 500000.0);
	m_pModelMT->addChild(m_pLogo);

	getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
}
float DynamicModel::totalLength(osg::Vec3dArray* path)
{
	if (path->size() < 2)return 0;
	if (path->size() == 2)return (path->at(1) - path->at(0)).length();
	float length = 0;
	for (int i = 1; i < path->size(); i++)
	{
		osg::Vec3 m_vector = path->at(i) - path->at(i - 1);
		length += m_vector.length();
	}
	return length;
}
void DynamicModel::setRunPath(osg::Vec3dArray* path, float speed/* = 5.0*/)
{
	//获取逆矩阵，用来转变世界坐标系
	osg::Matrix mat = getInverseMatrix();
	static float x = path->at(0).x();
	static float y = path->at(0).y();
	static float z = path->at(0).z();
	if (path != nullptr)
	{
		m_pPathArray = MEMath::GCSToWCS(path);
		m_pPathArray = MEMath::transform(mat, m_pPathArray);
		float totalLength = this->totalLength(m_pPathArray);

		speed = 5;
		if (m_modelData.strType == "ZhiShengJi")
		{
			speed = 50;
		}
		else if (m_modelData.strType == "TeJingChe" || m_modelData.strType == "TeXunChe" ||
			m_modelData.strType == "XiaoFangChe" || m_modelData.strType == "KeChe" ||
			m_modelData.strType == "DaBa" || m_modelData.strType == "JiPu")
		{
			speed = 18.0;
		}
		float _dltaTime = 0;
		float totalTime= totalLength / speed;
		m_pAnimaPath = new osg::AnimationPath;
		m_pAnimaPath->setLoopMode(osg::AnimationPath::NO_LOOPING);
		size_t count = path->size();
		osg::Quat quat;
		osg::Vec3d dirA, dirB, voffset, currPos;
		for (int i = 0; i < count; i++)
		{
			if (m_modelData.strType == "ZhiShengJi")
			{
				voffset = osg::Vec3d(0, 0, 200);
				m_pPathArray->at(0).z() = m_pPathArray->at(1).z();
			}
			
			if (i == 0)
			{
				dirA = m_pPathArray->at(i + 1) - m_pPathArray->at(0);
				//dirA.normalize();
				float angle = MEMath::getAngleByVector(dirA);
				quat = osg::Quat(angle, osg::Z_AXIS);
				osg::Matrix modelMat = m_pModelMT->getMatrix();
				m_pModelMT->setMatrix(modelMat * osg::Matrix::rotate(quat));
				currPos = m_pPathArray->at(i) + voffset;
				m_pAnimaPath->insert(0.0, osg::AnimationPath::ControlPoint(currPos,quat) );
			}
			
			else if (i == count - 1)
			{
				dirA = m_pPathArray->at(i) - m_pPathArray->at(i - 1);
				//float _length = dirA.length();
				//_dltaTime = totalLength / speed;
				float angle = MEMath::getAngleByVector(dirA);
				quat = osg::Quat(angle, osg::Z_AXIS);
				currPos = m_pPathArray->at(i) + voffset;
				m_pAnimaPath->insert(totalTime, osg::AnimationPath::ControlPoint(currPos,quat));
			}
			else
			{
				dirA = m_pPathArray->at(i) - m_pPathArray->at(i-1);
				dirB = m_pPathArray->at(i+1) - m_pPathArray->at(i);
				float _length = dirA.length();
				_dltaTime  +=_length*totalTime / totalLength;
				
				float angleA = MEMath::getAngleByVector(dirA);
				float angleB = MEMath::getAngleByVector(dirB);

				currPos = m_pPathArray->at(i) + voffset;
				quat = osg::Quat(angleA, osg::Z_AXIS);
				m_pAnimaPath->insert(_dltaTime-.0001, osg::AnimationPath::ControlPoint(
					currPos, quat));
				quat = osg::Quat(angleB, osg::Z_AXIS);
				m_pAnimaPath->insert(_dltaTime, osg::AnimationPath::ControlPoint(
					currPos, quat)  );
			}
		}
		m_pPathCallback = new osg::AnimationPathCallback(m_pAnimaPath);
		m_pPathCallback->setPause(true);
		m_pModelMT->setUpdateCallback(m_pPathCallback);
	}
}

void DynamicModel::runPath()
{
	if (m_pPathCallback != nullptr)
	{
		m_pPathCallback->setPause(false);
	}
}

void DynamicModel::pausePath()
{
	if (m_pPathCallback != nullptr)
	{
		m_pPathCallback->setPause(true);
	}
}

void DynamicModel::stopPath()
{
	if (m_pPathCallback != nullptr)
	{
		m_pPathCallback->reset();
	}
}

void DynamicModel::setLoop(bool isLoop)
{
	if (m_pAnimaPath != nullptr)
	{
		if (isLoop)
		{
			m_pAnimaPath->setLoopMode(osg::AnimationPath::LOOP);
		}
		else
		{
			m_pAnimaPath->setLoopMode(osg::AnimationPath::NO_LOOPING);
		}
	}
}
