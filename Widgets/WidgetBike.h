#ifndef WIDGETBIKE_H
#define WIDGETBIKE_H

#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gdkmm/pixbuf.h>
#include "../Infomodel/Settings.h"
#include "../Infomodel/eBikeInfo.h"

class WidgetBike : public Gtk::Grid
{
public:
	WidgetBike() = default;

	explicit
	WidgetBike(eBikeInfo info) : m_info(info)
	{
#ifdef GTKMM4
		add_css_class("eBikeWidgetGrid");
		m_label.add_css_class("eBikeWidgetBikeLabel");
		set_expand(false);
#else
		get_style_context()->add_class("eBikeWidgetGrid");
		m_label.get_style_context()->add_class("eBikeWidgetBikeLabel");
		set_hexpand(false);
#endif

		{
			m_imageBike.get_style_context()->add_class("eBikeWidgetImage");
			m_imageBike.set(getPath() + "Resources/bike_icon.png");
			//auto pixbuf = Gdk::Pixbuf::create_from_file(getPath() + "Resources/bike_icon.png");
			//auto scaled_pixbuf = pixbuf->scale_simple(100, 100, Gdk::INTERP_BILINEAR);
			//m_imageBike.set(scaled_pixbuf);
		}

		{
			m_imageBattery.set(getPath() + batteryIconPath());
			//auto pixbuf = Gdk::Pixbuf::create_from_file(getPath() + batteryIconPath());
			//auto scaled_pixbuf = pixbuf->scale_simple(120, 80, Gdk::INTERP_BILINEAR);
			//m_imageBattery.set(scaled_pixbuf);
		}

		m_label.set_text(m_info.toString());

		attach(m_imageBike,		0, 0);
		attach(m_imageBattery,	1, 0);
		attach(m_label,			2, 0);
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
