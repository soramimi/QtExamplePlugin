#ifndef MYPROJECT_H
#define MYPROJECT_H

#include <QObject>

class MyProject : public QObject {
	Q_OBJECT
public:
	MyProject();
	~MyProject();

	virtual QString func(QString const &a, QString const &b);
};

#endif // MYPROJECT_H
