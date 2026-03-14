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
		char buffer[128];
		snprintf(buffer, sizeof(buffer),
				 "%s\n" \
				 "%u km\n" \
				 "%s",
				 info.state,
				 info.mileage_km,
				 Clock::get_time_diff(m_created).c_str());
		return std::string(buffer);
	}

	uint32_t getBatteryPercent() const { return info.battery_percent; }

	std::string getBatteryPercentStr() const
	{
		char buffer[16];
		snprintf(buffer, sizeof(buffer), "%u%%", info.battery_percent);
		return std::string(buffer);
	}

	std::string getAdditionalInfoStr() const
	{
		char buffer[64];
		snprintf(buffer, sizeof(buffer), "%s\n%.1f\u00B0C %uc",
				 info.battery,
				 info.temperature_x10 / 10.0,
				 info.battery_cycles);
		return std::string(buffer);
	}

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
		strcpy(info.battery, "LiFePO4");
		info.mileage_km = 1234;
		info.battery_percent = batteryPercent;
		info.battery_cycles = 78;
		info.temperature_x10 = 252;
		m_created = std::time(nullptr);
	}
};

#endif // EBIKEINFO_H
