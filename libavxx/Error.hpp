#pragma once

#include <exception>
extern "C"
{
#include <libavutil/error.h>
}

namespace AV
{
class Error : public std::exception
{
	public:
	Error(int errorcode):
	    _error { errorcode }
	{ }

	virtual const char* what() const noexcept
	{
		return ::av_make_error_string(whatBuf, AV_ERROR_MAX_STRING_SIZE, _error);
	}

	private:
	int _error;
	static char whatBuf[AV_ERROR_MAX_STRING_SIZE];
};
}
