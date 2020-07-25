extern "C"
{
#include <libavutil/error.h>
}

#include "Error.hpp"

namespace AV
{
char Error::whatBuf[AV_ERROR_MAX_STRING_SIZE];
}
