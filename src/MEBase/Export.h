/*  	
 *@file   Export.h
 *@brief  brief  description  
 *@author fy
 *@date   2017/05/11
 *@version 0.1.0
 *@note  
 */
#ifndef MEBASE_EXPORT_H
#define MEBASE_EXPORT_H

#ifdef MEBASE_EXPORTS
#	define MEBASE_EXPORT __declspec(dllexport)
#else 
#	define MEBASE_EXPORT __declspec(dllimport)
#endif 

#endif // MECORE_EXPORT_H
