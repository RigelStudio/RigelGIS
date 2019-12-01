/*
 *@file   Export.h
 *@brief  brief  description
 *@author fy
 *@date   2017/05/11
 *@version 0.1.0
 *@note
 */
#ifndef RIGELDB_EXPORT_H
#define RIGELDB_EXPORT_H

#ifdef RIGELDB_EXPORTS
#	define RIGELDB_EXPORT __declspec(dllexport)
#else
#	define RIGELDB_EXPORT __declspec(dllimport)
#endif

#endif // MAPBASE_EXPORT_H
