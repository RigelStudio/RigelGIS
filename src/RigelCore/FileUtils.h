/*  	
 *@file   FileUtils.h
 *@brief  brief  description  
 *@author fengya
 *@date   2017/10/18
 *@version 1.0.0
 *@note  
 */
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include "Export.h"
#include <string>

class RIGELCORE_EXPORT FileUtils
{
public:
	
	static FileUtils* ins();

	
	static void des();

	
	void init(const std::string& dir);

	std::string getPath(const std::string& name);

private:
	FileUtils();
	~FileUtils();

private:
	static FileUtils* m_pIns;
	std::string m_strRoot;
};

#endif // FILEUTILS_H
