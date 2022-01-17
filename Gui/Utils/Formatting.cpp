#include "Formatting.hpp"

#include <array>
#include <cstdint>
#include <ranges>
#include <utility>

#include <QString>

using std::array, std::ranges::find_if, std::ranges::input_range, std::int64_t, std::pair;

constexpr auto pwr(int64_t base, int64_t power)
{
	int64_t result = 1;
	while (power-- > 0)
		result *= base;

	return result;
}

constexpr auto sizesIEC = array {
	pair { pwr(1024, 4), "TiB" },
	pair { pwr(1024, 3), "GiB" },
	pair { pwr(1024, 2), "MiB" },
	pair { pwr(1024, 1), "kiB" },
	pair { int64_t { 0 }, "bytes" }
};

constexpr auto bitrates = array {
	pair { pwr(1000, 2), "Mbits/s" },
	pair { pwr(1000, 1), "kbits/s" },
	pair { int64_t { 0 }, "bits/s" }
};

namespace Formatting
{

QString formatMeasurement(input_range auto& magnitudes, int64_t size)
{
	const auto [factor, unit] = *find_if(magnitudes, [size](const auto mag) {
		return size >= mag.first;
	});

	double quotient = factor == 0? size : size / static_cast<double>(factor);
	//: A number followed by a unit (e.g.: 123 bytes)
	return QString("%1 %2").arg(quotient, 0, ' ', factor == 0? 0 : 2).arg(unit);
}

QString byteSize(int64_t size)
{
	return formatMeasurement(sizesIEC, size);
}

QString bitrate(int64_t rate)
{
	return formatMeasurement(bitrates, rate);
}

}
