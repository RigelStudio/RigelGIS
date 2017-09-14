/************************************************************ 
  Copyright (C), 2014-2017, SSIT Tech. Co., Ltd. 
  �ļ���: FileUtils.h
  ����: lyk
  �汾: V1.0.0
  ����: 2016/09/23
  ģ������:��ȡ·���ӿ�
  ��Ҫ�������书��:
  ��ʷ�޸ļ�¼:
***********************************************************/
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>
#include "Export.h"

/* ����Ĺ��ܣ��������·����ȡ�ļ��ľ���·��
 *   
 * ������һ������
 * �ڳ�������Ҫ����ģ�ͣ�ͼƬ�ļ����ҵĵط�ʹ��
 */ 
class MEBASE_EXPORT FileUtils
{
public:
	/*
	 * @return FileUtils*:������ʵ��
	 * @see    des()
	 * @note   ��ȡΨһʵ��:FileUtils::ins()->init("D:/project/");
	 */
	static FileUtils* ins();

	/*
	* @see    ins()
	* @note   ����Ψһʵ��
	*/
	static void des();

	/*
	* @param name:��Ŀ¼����
	* @see   getPath()
	* @note  ��ʼ����Ŀ¼
	*/
	void init(const QString& name);

	/*
	* @param name:�ļ����ƻ������·��
	* @return �ļ��ľ���·��
	* @see   init()
	* @note  ���ݸ������ļ����ƣ����߾����ļ�·��
	* QString strImagePath = FileUtils::ins()->getPath("image.png");
	*/
	QString getPath(const QString& name);

	std::string getPath(const std::string& name);

private:
	FileUtils();
	~FileUtils();

private:
	static FileUtils* m_pIns;
	QString m_strRoot;
};

#endif // FILEUTILS_H
