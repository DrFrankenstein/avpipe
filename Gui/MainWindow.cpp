#include "MainWindow.hpp"

#include "AboutDialog.hpp"
#include "ui_MainWindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QMainWindow>
#include <QStringList>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->treeViewSources->setModel(&_sourcesModel);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_action_Quit_triggered()
{
	QApplication::quit();
}

void MainWindow::on_action_About_triggered()
{
	AboutDialog about;
	about.exec();
}

void MainWindow::on_action_Add_source_triggered()
{
	QFileDialog dialog { this };
	dialog.setFileMode(QFileDialog::FileMode::ExistingFiles);
	dialog.exec();
	auto files = dialog.selectedFiles();

	for (auto& path : files)
	{	// FIXME: what if we get a SMB path? or an actual URL?
		path.prepend("file:");
	}

	_sourcesModel.addSourcesByUrls(files);
}

