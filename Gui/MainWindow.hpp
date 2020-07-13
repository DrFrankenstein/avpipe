#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:
    void on_action_Quit_triggered();

    void on_action_About_triggered();

private:
	Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_HPP
