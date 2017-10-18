/*
 *@file   Export.h
 *@brief  brief  description
 *@author fy
 *@date   2017/10/17
 *@version 0.1.0
 *@note
 */
#ifndef MEQT_EXPORT_H
#define MEQT_EXPORT_H

#ifdef MEQT_EXPORTS
#	define MEQT_EXPORT __declspec(dllexport)
#else
#	define MEQT_EXPORT __declspec(dllimport)
#endif

#endif // MEQT_EXPORT_H
