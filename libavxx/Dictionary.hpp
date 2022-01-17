#pragma once

#include <cstdint>
#include <initializer_list>
#include <string>
#include <utility>
extern "C"
{
#include <libavutil/dict.h>
}

#include "Error.hpp"

#include <boost/iterator/iterator_facade.hpp>

namespace AV
{
class Dictionary
{
	public:
	using Initializer = std::initializer_list<std::pair<const char*, const char*>>;

	class Iterator
	    : public boost::iterator_facade<Iterator, const AVDictionaryEntry, boost::forward_traversal_tag>
	{
		public:
		Iterator(Dictionary& dict, AVDictionaryEntry* entry = nullptr):
		    _dict { dict }, _entry { entry }
		{ }

		private:
		friend class boost::iterator_core_access;

		void increment()
		{
			_entry = _dict.getEntry("", _entry, AV_DICT_IGNORE_SUFFIX);
		}

		bool equal(const Iterator& right)
		{
			return _entry == right._entry;
		}

		const AVDictionaryEntry& dereference() const
		{
			return *_entry;
		}

		Dictionary& _dict;
		const AVDictionaryEntry* _entry;
	};

	Dictionary()
	{ }

	Dictionary(Initializer list)
	{
		for (const auto& item : list)
			set(item.first, item.second);
	}

	Dictionary(const Dictionary& other)
	{
		const auto status = ::av_dict_copy(&_data, other._data, 0);
		if (status < 0)
		{
			::av_dict_free(&_data);
			throw Error(status);
		}
	}

	Dictionary(Dictionary&& other) noexcept:
	    _data { std::exchange(other._data, nullptr) }
	{ }

	~Dictionary()
	{
		::av_dict_free(&_data);
	}

	Dictionary& operator=(const Dictionary& right)
	{
		return *this = Dictionary(right);
	}

	Dictionary& operator=(Dictionary&& right)
	{
		std::swap(_data, right._data);
		return *this;
	}

	// TODO: if we need it, we could create some sort of proxy object that
	// calls set(key, value) on operator=, but that seems superfluous right
	// now
	const char* operator[](const char* key)
	{
		return get(key).value;
	}

	operator AVDictionary*()
	{
		return _data;
	}

	// some FFmpeg functions mutate the dict and thus take in a **
	operator AVDictionary* *()
	{
		return &_data;
	}

	const AVDictionaryEntry& get(const char* key, const AVDictionaryEntry* prev = nullptr, int flags = 0)
	{
		return *getEntry(key, prev, flags);
	}

	int count() const
	{
		return ::av_dict_count(_data);
	}

	void set(const char* key, const char* value, int flags = 0)
	{
		const auto status = ::av_dict_set(&_data, key, value, flags);
		if (status < 0)
			throw Error(status);
	}

	void set(const char* key, int64_t value, int flags = 0)
	{
		const auto status = ::av_dict_set_int(&_data, key, value, flags);
		if (status < 0)
			throw Error(status);
	}

	void remove(const char* key)
	{
		const auto status = ::av_dict_set(&_data, key, nullptr, 0);
		if (status < 0)
			throw Error(status);
	}

	void parseString(const char* str, const char* key_val_sep, const char* pairs_sep, int flags = 0)
	{
		const auto status = ::av_dict_parse_string(&_data, str, key_val_sep, pairs_sep, flags);
		if (status < 0)
			throw Error(status);
	}

	std::string toString(const char key_val_sep, const char pairs_sep)
	{
		char* buffer;
		const auto status = ::av_dict_get_string(_data, &buffer, key_val_sep, pairs_sep);
		if (status < 0)
			throw Error(status);

		std::string out { buffer };
		::av_free(buffer);
		return out;
	}

	Iterator begin()
	{
		return { *this, ::av_dict_get(_data, "", nullptr, AV_DICT_IGNORE_SUFFIX) };
	}

	Iterator end()
	{
		return { *this };
	}

	private:
	const AVDictionaryEntry* getEntry(const char* key, const AVDictionaryEntry* prev, int flags)
	{
		return ::av_dict_get(_data, key, prev, flags);
	}

	AVDictionary* _data { nullptr };
};
}
