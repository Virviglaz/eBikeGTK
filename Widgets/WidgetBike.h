#ifndef WIDGETBIKE_H
#define WIDGETBIKE_H

#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gdkmm/pixbuf.h>
#include "../Infomodel/Settings.h"
#include "../Infomodel/eBikeInfo.h"
#include <iostream>

class PicAndLabel : public Gtk::Grid
{
public:
	PicAndLabel() = default;

	PicAndLabel(const std::string& imagePath, const std::string& labelText, const std::string& cssClass)
	{
#ifdef GTKMM4
		add_css_class("eBikeWidgetGrid");
		m_label.add_css_class(cssClass + "Label");
		set_expand(false);
#else
		get_style_context()->add_class("eBikeWidgetGrid");
		m_label.get_style_context()->add_class(cssClass + "Label");
		set_hexpand(false);
#endif
		attach(m_label,	0, 0);
		attach(m_image,	0, 1);

		set_column_homogeneous(true);

		m_image.set(getPath() + imagePath);
		updateLabel(labelText);
#ifdef GTKMM4
		m_image.set_pixel_size(96);
#endif
	}

	void updateLabel(const std::string& labelText)
	{
		m_label.set_text(labelText);
	}
private:
	Gtk::Image m_image;
	Gtk::Label m_label;
};

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
		m_BikePicAndName = PicAndLabel("Resources/bike_icon.png", m_info.getName(), "eBikeWidgetBikeName");
		m_BatteryPicAndPercent = PicAndLabel(batteryIconPath(), std::to_string(m_info.getBatteryPercent()) + "%", "eBikeWidgetBattery");

		m_label.set_text(m_info.toString());

		attach(m_BikePicAndName,	0, 0);
		attach(m_BatteryPicAndPercent,	1, 0);
		attach(m_label,			2, 0);
		set_column_homogeneous(true);
	}

	bool operator==(const WidgetBike& other) const
	{
		return m_info == other.m_info;
	}

	eBikeInfo getInfo() const { return m_info; }

	void updateInfo()
	{
		m_label.set_text(m_info.toString());
		m_BatteryPicAndPercent = PicAndLabel(batteryIconPath(), std::to_string(m_info.getBatteryPercent()) + "%", "eBikeWidgetBattery");
	}
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

	PicAndLabel m_BikePicAndName;
	PicAndLabel m_BatteryPicAndPercent;
	Gtk::Image m_imageBattery;
	Gtk::Label m_label;
	eBikeInfo m_info;
};

#endif // WIDGETBIKE_H
