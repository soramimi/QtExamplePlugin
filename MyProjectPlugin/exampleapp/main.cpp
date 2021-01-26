#include "../src/MyProject.h"
#include "../src/MyProjectInterface.h"
#include <QCoreApplication>
#include <QDebug>
#include <QPluginLoader>
#include <memory>


int main(int argc, char **argv)
{
	QCoreApplication a(argc, argv);

	QPluginLoader loader("myprojectplugin");
	MyProjectInterface *plugin = dynamic_cast<MyProjectInterface *>(loader.instance());
	if (plugin) {
		auto p = std::shared_ptr<MyProject>(plugin->create());
		QString s = p->func("Hello,", " world");
		qDebug() << s;
	} else {
		qDebug() << "failed to load the plugin";
	}

	return 0;
}



