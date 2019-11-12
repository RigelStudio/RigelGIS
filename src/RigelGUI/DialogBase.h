/*************************************************
 // Copyright(C)  
 // File name:    DialogBase
 // Author:       ����       
 // Version:      1.0     
 // Date:         2017/04/28
 // Description:  ������ק�ƶ�����ק���Ŵ�С��dialogbase����
 //	History:
 *************************************************/
#ifndef DIALOGBASE_H
#define DIALOGBASE_H

#include "Export.h"
#include <QDialog>
#include <QMouseEvent>
#include <QLayout>
#include <QGridLayout>

#define PADDING 4

class GUITOOL_EXPORT DialogBase : public QDialog
{
	Q_OBJECT

public:
	DialogBase( QWidget *parent=0);
	~DialogBase();

	enum Direction 
	{ 
		UP = 0, 
		DOWN = 1, 
		LEFT, 
		RIGHT, 
		LEFTTOP, 
		LEFTBOTTOM, 
		RIGHTBOTTOM, 
		RIGHTTOP, 
		NONE
	};

	void setMoveEanable(bool isMove = true);

protected:
	virtual void mousePressEvent(QMouseEvent* e);
	virtual void mouseMoveEvent(QMouseEvent* e);
	virtual void mouseReleaseEvent(QMouseEvent* e);

private:
	void region(const QPoint &cursorGlobalPoint);

	virtual void leaveEvent(QEvent *);

	void initTitle();

private:
	bool m_isMove;	//��¼��굱ǰ״̬�Ƿ�Ϊ�ƶ�
	bool m_isMoveAble;	//���ô����Ƿ�����ƶ�����
	bool m_isResizeAble;	//������С����
	QPoint m_dragPoint;
	QPoint m_dragPosition;   
	Direction m_dir;
	QWidget* m_pTitleWid;

};

#endif // DIALOGBASE_H
