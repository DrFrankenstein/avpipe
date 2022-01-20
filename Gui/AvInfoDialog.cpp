#include "AvInfoDialog.hpp"
#include "ui_avinfodialog.h"

#include <QString>

extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

AvInfoDialog::AvInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AvInfoDialog)
{
    ui->setupUi(this);
	populateFormats();
	populateCodecs();
}

AvInfoDialog::~AvInfoDialog()
{
    delete ui;
}

void AvInfoDialog::populateFormats()
{
	const auto version = avformat_version();
	const auto license = avformat_license();
	ui->formatsVersionLabel->setText(
		QString("libavformat version %1.%2.%3 (%4)")
			.arg(AV_VERSION_MAJOR(version))
			.arg(AV_VERSION_MINOR(version))
			.arg(AV_VERSION_MICRO(version))
			.arg(license)
	);

	const auto options = avformat_configuration();
	ui->formatsOptionsTextEdit->setPlainText(options);
}

void AvInfoDialog::populateCodecs()
{
	const auto version = avcodec_version();
	const auto license = avcodec_license();
	ui->codecsVersionLabel->setText(
		QString("libavcodec version %1.%2.%3 (%4)")
			.arg(AV_VERSION_MAJOR(version))
			.arg(AV_VERSION_MINOR(version))
			.arg(AV_VERSION_MICRO(version))
		.arg(license)
	);

	const auto options = avcodec_configuration();
	ui->codecsOptionsTextEdit->setPlainText(options);
}
