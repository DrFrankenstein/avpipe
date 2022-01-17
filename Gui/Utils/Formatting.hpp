#pragma once

#include <chrono>
#include <concepts>
#include <cstdint>
#include <type_traits>
#include <QString>

namespace Formatting
{
// TODO: this could probably be moved elsewhere for dat reuse goodness
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <Number Seconds>
QString duration(const Seconds s)
{
	using Duration = std::chrono::duration<Seconds>;

	Duration d { s };
	std::chrono::hh_mm_ss<Duration> hms { d };

	auto value = QString("%1:%2:%3")
	    .arg(hms.hours().count())
	    .arg(hms.minutes().count(), 2, 10, QLatin1Char { '0' })
	    .arg(hms.seconds().count(), 2, 10, QLatin1Char { '0' });

	if constexpr (std::is_floating_point<Seconds>::value)
		if (hms.subseconds() != Duration::zero())
		{	// HACK: kinda ugly, but there's no way to get Qt to stringify a float without a leading 0 before the dot.
			auto fractional = QString("%1").arg(hms.subseconds().count(), 'f');
			fractional.remove(0, fractional.indexOf('.'));
			value.append(fractional);
		}

	return value;
}

QString byteSize(std::int64_t size);
QString bitrate(std::int64_t size);

}
