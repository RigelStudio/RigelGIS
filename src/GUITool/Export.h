/*************************************************
// Copyright(C)
// File name:    Export
// Author:       ����
// Version:      1.0
// Date:         2017/05/11
// Description:  dll�����궨��
//	History:
*************************************************/
#ifndef GUITOOL_EXPORT_H
#define GUITOOL_EXPORT_H

#if defined (GUITOOL_EXPORTS)
#	define GUITOOL_EXPORT __declspec(dllexport)
#else 
#	define GUITOOL_EXPORT __declspec(dllimport)
#endif 

#endif // GUITOOL_EXPORT_H
