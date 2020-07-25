#include "AboutDialog.hpp"

#include "../config.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget* parent):
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
	ui->setupUi(this);
	QString versionText = ui->labelVersion->text().arg(PROJECT_VERSION);
	ui->labelVersion->setText(versionText);
	QString buildText = ui->labelBuild->text().arg(PROJECT_BUILD);
	ui->labelBuild->setText(buildText);
}

AboutDialog::~AboutDialog()
{
	delete ui;
}
