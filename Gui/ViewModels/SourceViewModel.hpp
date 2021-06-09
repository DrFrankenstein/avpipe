#pragma once

#include "../../libavxx/FormatContext.hpp"

#include <QAbstractItemModel>
#include <QList>
#include <QVariant>
#include <QWidget>
#include <unordered_map>
#include <vector>

// What indices mean:
// level 0 (null parent): sources (files, devices...)
//	id: (FormatContext*?) (is it needed?)
//	column 1: URL
// level 1: streams (audio, video, subtitles, data...)
//	id: AVStream*
//	column 1: type?
//	column 2: language?
// level 2..: invalid

class SourceViewModel : public QAbstractItemModel
{
	using FormatContext = AV::Format::FormatContext;

	Q_OBJECT

	public:
	explicit SourceViewModel(std::vector<FormatContext>& sources, QWidget* parent = nullptr);

	virtual int rowCount(const QModelIndex& parent = {}) const override;
	virtual int columnCount(const QModelIndex& parent = {}) const override;
	virtual bool hasChildren(const QModelIndex& parent = {}) const override;
	virtual QModelIndex index(int row, int column, const QModelIndex& parent = {}) const override;
	virtual QModelIndex parent(const QModelIndex& index) const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void addSourcesByUrls(const QStringList& urls);

	private:
	static bool itemIsStream(const QModelIndex& index);
	static QVariant formatData(FormatContext& format, int role);
	static QVariant streamData(const AVStream& stream, int role);

	FormatContext& formatFromIndex(const QModelIndex& index) const;
	AVStream& streamFromIndex(const QModelIndex& index) const;

	std::vector<FormatContext>& _sources;
	std::unordered_map<AVStream*, int> _streamParents;

	QWidget* _parent;
};
