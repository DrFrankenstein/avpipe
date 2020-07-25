#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../libavxx/FormatContext.hpp"

#include <QList>
#include <QMainWindow>
#include <QString>
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
	void addSourcesByUrls(const QStringList& urls);

	Ui::MainWindow* ui;

	QList<AV::Format::FormatContext> _sourcesNew;
	QStringList _sources;
	QStringListModel _sourcesModel { _sources, this };
};

#endif  // MAINWINDOW_HPP
