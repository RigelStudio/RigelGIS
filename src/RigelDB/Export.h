/*
 *@file   Export.h
 *@brief  brief  description
 *@author fy
 *@date   2017/05/11
 *@version 0.1.0
 *@note
 */
#ifndef MEDB_EXPORT_H
#define MEDB_EXPORT_H

#ifdef MEDB_EXPORTS
#	define MEDB_EXPORT __declspec(dllexport)
#else
#	define MEDB_EXPORT __declspec(dllimport)
#endif

#endif // MAPBASE_EXPORT_H
