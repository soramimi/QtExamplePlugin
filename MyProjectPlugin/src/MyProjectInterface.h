#ifndef MYPROJECTINTERFACE_H
#define MYPROJECTINTERFACE_H

#include <QtPlugin>
#include "MyProject.h"

class MyProjectInterface {
public:
	MyProjectInterface();
	virtual ~MyProjectInterface() {}
	virtual MyProject *create() = 0;
};

Q_DECLARE_INTERFACE(MyProjectInterface, "mynamespace.MyProjectPlugin/1.0")

#endif // MYPROJECTINTERFACE_H
