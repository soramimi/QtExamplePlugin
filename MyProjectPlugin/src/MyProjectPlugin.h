#ifndef MYPROJECTPLUGIN_H
#define MYPROJECTPLUGIN_H

#include <QtCore/qplugin.h>
#include "MyProjectInterface.h"

class MyProjectPlugin : public QObject, public MyProjectInterface {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "mynamespace.MyProjectPlugin" FILE "myprojectplugin.json")
	Q_INTERFACES(MyProjectInterface)
public:
	MyProject *create() override
	{
		return new MyProject();
	}
};

#endif // MYPROJECTPLUGIN_H
