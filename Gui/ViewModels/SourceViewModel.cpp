#include "SourceViewModel.hpp"

#include <QAbstractItemModel>
#include <QApplication>
#include <QStyle>
#include <algorithm>
#include <boost/cast.hpp>
#include <iterator>

using AV::Format::FormatContext;
using boost::numeric_cast;
using std::back_inserter, std::begin, std::end, std::transform, std::vector;

SourceViewModel::SourceViewModel(vector<FormatContext>& sources, QObject* parent):
    QAbstractItemModel { parent }, _sources { sources }
{
}

int SourceViewModel::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid())
		return numeric_cast<int>(_sources[parent.row()].streams().size());

	return numeric_cast<int>(_sources.size());
}

int SourceViewModel::columnCount([[maybe_unused]] const QModelIndex& parent) const
{
	return 1;
}

bool SourceViewModel::hasChildren(const QModelIndex& parent) const
{  // only the first-level items, aka sources, have children (streams)
	return !itemIsStream(parent);
}

QModelIndex SourceViewModel::index(int row, int column, const QModelIndex& parent) const
{
	if (parent.isValid())
		return createIndex(row, column, _sources[parent.row()].streams()[row]);

	return createIndex(row, column, nullptr);
}

QModelIndex SourceViewModel::parent(const QModelIndex& index) const
{
	if (index.internalPointer() != nullptr)
	{
		const auto stream    = static_cast<AVStream* const>(index.internalPointer());
		const auto parentRow = _streamParents.at(stream);
		return createIndex(parentRow, 0, nullptr);
	}

	return {};
}

QVariant SourceViewModel::data(const QModelIndex& index, int role) const
{
	if (itemIsStream(index.parent()))
		return {};  // trying to access a stream's non-existent child

	if (itemIsStream(index))
	{
		const auto& source = _sources[index.parent().row()];
		const auto& stream = *source.streams()[index.row()];
		return streamData(stream, role);
	}

	FormatContext& source = _sources[index.row()];
	return formatData(source, role);
}

bool SourceViewModel::itemIsStream(const QModelIndex& index)
{
	return index.internalPointer() != nullptr;
}

QVariant SourceViewModel::formatData(FormatContext& format, int role)
{
	switch (role)
	{
	case Qt::DisplayRole:
		return format.data()->url;

	case Qt::DecorationRole:
		return QApplication::style()->standardIcon(QStyle::SP_FileIcon);

	default:
		return {};
	}
}

QVariant SourceViewModel::streamData(const AVStream& stream, int role)
{
	switch (role)
	{
	case Qt::DisplayRole:
		return QString("Stream %0").arg(stream.index);  // TODO: generate a string descriptor for a stream

	case Qt::DecorationRole:
		return QApplication::style()->standardIcon(QStyle::SP_MediaPlay);  // TODO: get better icons for this

	default:
		return {};
	}
}

FormatContext& SourceViewModel::formatFromIndex(const QModelIndex& index) const
{
	return _sources[index.row()];
}

AVStream& SourceViewModel::streamFromIndex(const QModelIndex& index) const
{
	return *_sources[index.parent().row()].streams()[index.row()];
}

void SourceViewModel::addSourcesByUrls(const QStringList& urls)
{
	auto idx = numeric_cast<int>(_sources.size());
	beginInsertRows({}, idx, idx + urls.size());

	for (const auto& url : urls)
	{
		_sources.push_back(FormatContext::fromUrl(url.toStdString()));
		const auto& format = _sources.back();
		for (const auto stream : format.streams())
			_streamParents.insert({ stream, idx });

		++idx;
	}

	transform(begin(urls), end(urls), back_inserter(_sources),
	    [](const auto& url) { return FormatContext::fromUrl(url.toStdString()); });

	endInsertRows();
}
