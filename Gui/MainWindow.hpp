#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../libavxx/FormatContext.hpp"
#include "ViewModels/SourceViewModel.hpp"

#include <vector>
#include <QMainWindow>
#include <QStringList>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	using FormatContext = AV::Format::FormatContext;

	public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	private slots:
	void on_action_Quit_triggered();

	void on_action_About_triggered();

	void on_action_Add_source_triggered();

	private:
	Ui::MainWindow* ui;

	std::vector<FormatContext> _sources;	// ???: should the model own this?
	SourceViewModel _sourcesModel { _sources, this };
};

#endif  // MAINWINDOW_HPP
