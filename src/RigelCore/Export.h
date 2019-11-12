/*
 *@file   Export.h
 *@brief  brief  description
 *@author fy
 *@date   2017/05/11
 *@version 0.1.0
 *@note
 */
#ifndef RIGELCORE_EXPORT_H
#define RIGELCORE_EXPORT_H

#ifdef RIGELCORE_EXPORTS
#	define RIGELCORE_EXPORT __declspec(dllexport)
#else
#	define RIGELCORE_EXPORT __declspec(dllimport)
#endif

#endif // RIGELCORE_EXPORT_H
