#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "joinpath.h"
#include <QDebug>
#include <QDirIterator>
#include <QFileDialog>
#include <sys/stat.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_browse_destination_clicked()
{
	QString dir = QDir::current().dirName();
	dir = QFileDialog::getExistingDirectory(this, tr("Destination Directory"), dir);
	if (!dir.isEmpty()) {
		ui->lineEdit_destination_dir->setText(dir);
	}
}

void MainWindow::on_pushButton_generate_clicked()
{
	generate();
}

void MainWindow::on_pushButton_close_clicked()
{
	close();
}

void MainWindow::generate()
{
	QString template_dir = "/var/lib/soramimi.jp/MyProjectPlugin";
	QString project_name = ui->lineEdit_project_name->text();
	QString dstdir = ui->lineEdit_destination_dir->text();
	if (!QFileInfo(dstdir).isDir()) return;
	if (QFileInfo(dstdir / project_name).exists()) return;
	if (project_name.isEmpty()) return;
	QFileInfo info(template_dir);
	if (info.isDir()) {
		struct FileItem {
			QString name;
			QString path;
			QString rpath;
		};

		QList<FileItem> files;
		QList<FileItem> dirs;
		FileItem item;
		item.path = template_dir;
		dirs.push_back(item);
		while (!dirs.empty()) {
			FileItem diritem = dirs.front();
			dirs.pop_front();
			QDirIterator it(diritem.path);
			while (it.hasNext()) {
				it.next();
				ushort c = it.fileInfo().fileName().utf16()[0];
				if (c == '.' || c == '_') continue;
				QString path = it.filePath();
				if (it.fileInfo().isDir()) {
					FileItem item;
					item.name = it.fileInfo().fileName();
					item.path = path;
					item.rpath = diritem.rpath + it.fileName();
					dirs.push_back(item);
				} else if (it.fileInfo().isFile()) {
					FileItem item;
					item.name = it.fileInfo().fileName();
					item.path = path;
					item.rpath = diritem.rpath;
					files.push_back(item);
				}
			}
		}
		for (FileItem const &file : files) {
			auto Copy = [](QString const &src, QString const &dst, QString const &filename, QString const &project_name){
				auto Convert = [](QByteArray const &source, QString const &project_name){
					const std::string oldname = "MyProject";
					const std::string newname = project_name.toStdString();
					QByteArray result;
					int pos = 0;
					while (pos < source.size()) {
						if (int(pos + oldname.size()) <= source.size()) {
							auto memicmp = [](char const *a, char const *b, int n){
								for (int i = 0; i < n; i++) {
									int c = toupper((unsigned char)*a);
									int d = toupper((unsigned char)*b);
									if (c < d) return -1;
									if (c > d) return 1;
									a++;
									b++;
								}
								return 0;
							};
							if (memicmp(source.data() + pos, oldname.c_str(), oldname.size()) == 0) {
								bool lower = true;
								bool upper = true;
								for (size_t i = 0; i < oldname.size(); i++) {
									int c = (unsigned char)source.data()[pos + i];
									if (isupper(c)) lower = false;
									if (islower(c)) upper = false;
								}
								for (size_t i = 0; i < newname.size(); i++) {
									int c = (unsigned char)newname.c_str()[i];
									if (lower) {
										c = tolower(c);
									} else if (upper) {
										c = toupper(c);
									}
									result.push_back(c);
								}
								pos += oldname.size();
								continue;
							}
						}
						result.push_back(source.data()[pos]);
						pos++;
					}
					return result;
				};
				QString spath = src / filename;
				QFile sfile(spath);
				if (sfile.open(QFile::ReadOnly)) {
					QByteArray ba = sfile.readAll();
					QString dname = QString::fromUtf8(Convert(filename.toUtf8(), project_name));
					QDir().mkpath(dst);
					QString dpath = dst / dname;
					QFile dfile(dpath);
					if (dfile.open(QFile::WriteOnly)) {
						ba = Convert(ba, project_name);
						dfile.write(ba);
						dfile.close();
						{
							struct stat st;
							if (stat(spath.toStdString().c_str(), &st) == 0) {
								chmod(dpath.toStdString().c_str(), st.st_mode);
							}
						}
					}
				}
			};
			Copy(template_dir / file.rpath, dstdir / (project_name + "Plugin") / file.rpath, file.name, project_name);
		}
	}
}
