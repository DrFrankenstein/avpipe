#pragma once

#include <span>
#include <stdexcept>
#include <string>
#include <vector>
extern "C"
{
#include <libavformat/avformat.h>
}

#include "Dictionary.hpp"
#include "Error.hpp"

namespace
{
}

namespace AV::Format
{
class FormatContext
{
	public:
	FormatContext():
	    _data { ::avformat_alloc_context() }
	{ }

	explicit FormatContext(AVFormatContext* context):
	    _data { context }
	{ }

	~FormatContext()
	{
		if (_data && _data->pb)
			::avformat_close_input(&_data);

		if (_data)
			::avformat_free_context(_data);
	}

	AVFormatContext* data()
	{
		return _data;
	}

	operator AVFormatContext*()
	{
		return data();
	}

	std::span<AVStream*> streams()
	{
		return { _data->streams, _data->nb_streams };
	}

	std::span<AVChapter*> chapters()
	{
		return { _data->chapters, _data->nb_chapters };
	}

	std::span<AVProgram*> programs()
	{
		return { _data->programs, _data->nb_programs };
	}

	void open(const char* url, AVInputFormat* fmt = nullptr, AVDictionary** options = nullptr)
	{
		const auto status = ::avformat_open_input(&_data, url, fmt, options);
		if (status < 0)
			throw Error { status };
	}

	void findStreamInfo(std::vector<Dictionary> options = {})
	{
		if (options.size() < _data->nb_streams)
			throw std::invalid_argument { "Not enough options for number of streams" };

		static_assert(sizeof(Dictionary) == sizeof(AVDictionary**));
		const auto dicts  = reinterpret_cast<AVDictionary**>(options.data());
		const auto status = ::avformat_find_stream_info(_data, dicts);
		if (status < 0)
			throw Error { status };
	}

	int findBestStream(AVMediaType type, int wanted_stream_nb = -1, int related_stream = -1, AVCodec** decoder = nullptr)
	{
		const auto idx = ::av_find_best_stream(_data, type, wanted_stream_nb, related_stream, decoder, 0);
		if (idx < 0)
			throw Error { idx };

		return idx;
	}

	// Packet readFrame(); // Packet NYI

	// void seekFrame(int stream_index, int64_t timestamp, int flags);

	// void seekFile(int stream_index, int64_t min_ts, int64_t ts, int64_t max_ts, int flags); // unstable in libavformat as of FFmpeg 4.1

	void flush()
	{
		const auto status = ::avformat_flush(_data);
		if (status < 0)
			throw Error { status };
	}

	static FormatContext fromUrl(const std::string& url, AVInputFormat* fmt = nullptr, AVDictionary** options = nullptr)
	{
		AVFormatContext* context;
		const int status = ::avformat_open_input(&context, url.c_str(), fmt, options);
		if (status < 0)
			throw Error { status };

		return FormatContext { context };
	}

	private:
	AVFormatContext* _data;
};
}
