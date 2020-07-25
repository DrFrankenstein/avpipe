#include "MainWindow.hpp"

#include "AboutDialog.hpp"
#include "ui_MainWindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QStringList>

using AV::Format::FormatContext;

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

	addSourcesByUrls(dialog.selectedFiles());
}

void MainWindow::addSourcesByUrls(const QStringList& urls)
{
	_sources.append(urls);
	_sourcesModel.setStringList(_sources);  // there might be a more efficient way of doing this

	for (const auto& url : urls)
		_sourcesNew << FormatContext::fromUrl(url.toStdString());
}
