/*  	
 *@file   Export.h
 *@brief  brief  description  
 *@author fy
 *@date   2017/05/11
 *@version 0.1.0
 *@note  
 */
#ifndef MAPBASE_EXPORT_H
#define MAPBASE_EXPORT_H

#ifdef MAPBASE_EXPORTS
#	define MAPBASE_EXPORT __declspec(dllexport)
#else 
#	define MAPBASE_EXPORT __declspec(dllimport)
#endif 

#endif // MAPBASE_EXPORT_H
