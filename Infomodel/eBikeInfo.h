#ifndef EBIKEINFO_H
#define EBIKEINFO_H

#include <string>
#include <ctime>
#include "SharedInfo.h"
#include "../Widgets/WidgetClock.h"

class eBikeInfo
{
public:
	eBikeInfo() = default;

	explicit
	eBikeInfo(struct SharedModelData *info_ptr) : info(*info_ptr)
	{
		m_created = std::time(nullptr);
		m_name = std::string(info.name);
	}

	virtual const std::string& getName() const { return m_name; }

	bool operator==(const eBikeInfo& other) const
	{
		return m_name == other.m_name;
	}

	virtual std::string toString() const
	{
		char buffer[256];
		snprintf(buffer, sizeof(buffer),
				 "%s %s\n" \
				 "Mileage: %u km\n" \
				 "Battery: %u%%\n" \
				 "Cycles: %u\n%s",
				 m_name.c_str(),
				 info.state,
				 info.mileage_km,
				 info.battery_percent,
				 info.battery_cycles,
				 Clock::get_time(m_created).c_str());
		return std::string(buffer);
	}

	uint32_t getBatteryPercent() const { return info.battery_percent; }

protected:
	struct SharedModelData info;
	std::time_t m_created;
	std::string m_name;
};

class eBikeInfoDebug : public eBikeInfo
{
public:
	eBikeInfoDebug() = default;

	eBikeInfoDebug(const std::string &name, uint32_t batteryPercent = 100)
	{
		m_name = name;
		strcpy(info.name, name.c_str());
		strcpy(info.state, "Debug");
		info.mileage_km = 1234;
		info.battery_percent = batteryPercent;
		info.battery_cycles = 78;
		m_created = std::time(nullptr);
	}
};

#endif // EBIKEINFO_H
