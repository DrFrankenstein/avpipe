#include "SourcePropSheet.hpp"

#include "../../libavxx/FormatContext.hpp"
#include "../Utils/Formatting.hpp"
#include "ui_SourcePropSheet.h"

using AV::Format::FormatContext;

SourcePropSheet::SourcePropSheet(const FormatContext& source, QWidget* parent, Qt::WindowFlags flags):
    QDialog { parent, flags }, ui { new Ui::SourcePropSheet }, _source { source }
{
	ui->setupUi(this);
	populate();
}

SourcePropSheet::~SourcePropSheet()
{
	delete ui;
}

void SourcePropSheet::populate()
{
	const auto sourcedata = _source.data();
	ui->urlLabel->setText(sourcedata->url);

	QString formatName { sourcedata->iformat->long_name };
	if (sourcedata->probe_score < AVPROBE_SCORE_MAX)
		formatName.append(tr(" (%1% confidence)").arg(sourcedata->probe_score / static_cast<double>(AVPROBE_SCORE_MAX)));
	ui->formatNameLabel->setText(formatName);

	ui->seekableLabel->setText((sourcedata->ctx_flags & AVFMTCTX_UNSEEKABLE) ? tr("No") : tr("Yes"));

	if (sourcedata->start_time == AV_NOPTS_VALUE)	// ???: move this to the formatting function?
	{
		ui->startTimeLabel->setText(tr("N/A"));
	}
	else
	{
		const auto startTimeSecs = static_cast<double>(sourcedata->start_time) / AV_TIME_BASE;
		ui->startTimeLabel->setText(Formatting::duration(startTimeSecs));
	}

	if (sourcedata->duration == AV_NOPTS_VALUE)
	{
		ui->durationLabel->setText(tr("N/A"));
	}
	else
	{
		const auto durationSecs = static_cast<double>(sourcedata->duration) / AV_TIME_BASE;
		QString duration = Formatting::duration(durationSecs);
		if (sourcedata->duration_estimation_method == AVFMT_DURATION_FROM_BITRATE)
			duration.append(tr(" (estimated from bitrate)"));
		ui->durationLabel->setText(duration);
	}

	ui->bitrateLabel->setText(Formatting::bitrate(sourcedata->bit_rate));
	ui->pktsizeLabel->setText(Formatting::byteSize(sourcedata->packet_size));
	ui->maxdelayLabel->setText(QString::number(sourcedata->max_delay));
}
