/*
 *@file   Export.h
 *@brief  brief  description
 *@author fy
 *@date   2017/05/11
 *@version 0.1.0
 *@note
 */
#ifndef MEGA_EXPORT_H
#define MEGA_EXPORT_H

#ifdef MEGA_EXPORTS
#	define MEGA_EXPORT __declspec(dllexport)
#else
#	define MEGA_EXPORT __declspec(dllimport)
#endif

#endif // MEGA_EXPORT_H
