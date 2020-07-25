#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../libavxx/FormatContext.hpp"

#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>

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

	void on_action_Add_source_triggered();

	private:
	Ui::MainWindow* ui;

	QStringList _sources;
	QStringListModel _sourcesModel { _sources, this };
};

#endif  // MAINWINDOW_HPP
