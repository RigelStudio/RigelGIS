#ifndef RIGELMODEL_EXPORT_H
#define RIGELMODEL_EXPORT_H

#ifdef RIGELMODEL_EXPORTS
#	define RIGELMODEL_EXPORT __declspec(dllexport)
#else 
#	define RIGELMODEL_EXPORT __declspec(dllimport)
#endif 

#endif // MECORE_EXPORT_H
