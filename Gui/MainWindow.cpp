#include "MainWindow.hpp"
#include "AboutDialog.hpp"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
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
