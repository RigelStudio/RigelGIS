#ifndef LABELNODE_H
#define LABELNODE_H

#include "Export.h"
#include "LabelBase.h"

class RIGELMODEL_EXPORT LabelNode : public LabelBase
{
public:
	LabelNode(void);
	~LabelNode(void);

private:

	void init();

	void update();


};

#endif//LABELNODE_H