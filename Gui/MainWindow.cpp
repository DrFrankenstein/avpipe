#include "MainWindow.hpp"

#include "AboutDialog.hpp"
#include "PropSheets/SourcePropSheet.hpp"
#include "ui_MainWindow.h"

#include <iterator>
#include <ranges>

#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QStringList>
#include <QWidget>

using std::back_inserter, std::ranges::transform;

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


void MainWindow::on_treeViewSources_customContextMenuRequested(const QPoint &pos)
{
    const auto index = ui->treeViewSources->indexAt(pos);
    if (!index.isValid())
        return;

    QMenu contextMenu;
	const auto propsAction = contextMenu.addAction(tr("&Properties..."));
	const auto selected = contextMenu.exec(ui->treeViewSources->viewport()->mapToGlobal(pos));

	if (selected == propsAction)
	{
		if (SourceViewModel::itemIsStream(index))
			qDebug() << "NYI stream properties";
		else
		{
			SourcePropSheet sourceprops { _sourcesModel.formatFromIndex(index), this };
			sourceprops.exec();
		}
	}
}
