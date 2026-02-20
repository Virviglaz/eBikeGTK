#ifndef WIDGETBIKE_H
#define WIDGETBIKE_H

#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>

#include "../Infomodel/eBikeInfo.h"

class WidgetBike : public Gtk::Grid
{
public:
	WidgetBike() = default;

	explicit
	WidgetBike(eBikeInfo info) : m_info(info)
	{
		m_imageBike.set_pixel_size(50);
		m_imageBike.set("Resources/bike_icon.png");

		m_imageBattery.set_pixel_size(80);
		m_imageBattery.set(batteryIconPath());

		m_label.set_text(m_info.toString());

		attach(m_imageBike,		0, 0);
		attach(m_imageBattery,	1, 0);
		attach(m_label,			2, 0);
		set_expand(false);
		set_column_homogeneous(true);
	}

	bool operator==(const WidgetBike& other) const
	{
		return m_info == other.m_info;
	}

	eBikeInfo getInfo() const { return m_info; }
private:
	const std::string batteryIconPath() const
	{
		const uint32_t batteryPercent = m_info.getBatteryPercent();
		uint32_t imageIndex = 0;

		if (batteryPercent >= 90)
			imageIndex = 100;
		else if (batteryPercent >= 75)
			imageIndex = 75;
		else if (batteryPercent >= 50)
			imageIndex = 50;
		else if (batteryPercent >= 25)
			imageIndex = 25;

		char buffer[64];
		snprintf(buffer, sizeof(buffer), "Resources/battery_%u.png", imageIndex);
		return std::string(buffer);
	}

	Gtk::Image m_imageBike;
	Gtk::Image m_imageBattery;
	Gtk::Label m_label;
	eBikeInfo m_info;
};

#endif // WIDGETBIKE_H
