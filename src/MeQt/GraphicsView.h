/*  	
 *@file   EventAdapter.h
 *@brief  brief  description  
 *@author louyk
 *@date   2015/05/17
 *@version 1.0.0
 *@note   ����QGraphicsView��ʽ����osgǶ��qt�Ļ���osg��
 */
#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <osgViewer/Viewer>
#include "EventAdapter.h"
#include "Export.h"

class MEQT_EXPORT GraphicsView : public EventAdapter
{
	Q_OBJECT

public:
	GraphicsView(QWidget* parent = 0);
	~GraphicsView();

	osgViewer::Viewer* getOSGViewer(){ return m_pViewer; }
	osg::Group* getRoot(){ return m_pSceneData; }

protected:
	virtual void drawBackground(QPainter *painter, const QRectF& rect);
	virtual void timerEvent(QTimerEvent *event);

private:
	void init();

private:
	osg::Group* m_pSceneData;
	osgViewer::Viewer* m_pViewer;
};

#endif // GRAPHICSVIEW_H
