#include "MainWindow.hpp"

#include "AboutDialog.hpp"
#include "ui_MainWindow.h"

#include <iterator>

#include <nanorange.hpp>

#include <QApplication>
#include <QFileDialog>
#include <QMainWindow>
#include <QStringList>
#include <QWidget>

using std::back_inserter;
using nano::ranges::transform;

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

	QStringList urls;
	// ffmpeg understands file:<path> but not file:///<path>.
	// TODO: make sure it works on *nix paths too
	transform(dialog.selectedUrls(), back_inserter(urls), [](const auto& url) { 
		return url.toString().replace("file:///", "file:"); 
	});

	_sourcesModel.addSourcesByUrls(urls);
}

