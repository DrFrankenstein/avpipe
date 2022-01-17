#ifndef SOURCEPROPSHEET_HPP
#define SOURCEPROPSHEET_HPP

#include "../../libavxx/FormatContext.hpp"

#include <QDialog>

namespace Ui
{
class SourcePropSheet;
}

class SourcePropSheet : public QDialog
{
	Q_OBJECT

	public:
	explicit SourcePropSheet(const AV::Format::FormatContext& source, QWidget* parent = nullptr, Qt::WindowFlags flags = {});
	~SourcePropSheet();

	private:
	void populate();

	Ui::SourcePropSheet* ui;
	const AV::Format::FormatContext& _source;
};

#endif  // SOURCEPROPSHEET_HPP
