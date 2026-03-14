#ifndef WIDGETBIKE_H
#define WIDGETBIKE_H

#include "../Infomodel/Settings.h"
#include "../Infomodel/eBikeInfo.h"
#include "WidgetBase.h"

class BikeIconAndNameWidget : public WidgetGridBase
{
public:
	BikeIconAndNameWidget() = default;

	BikeIconAndNameWidget(const std::string &name,
						  const std::string &cssClass) : WidgetGridBase(cssClass)
	{
		m_BikeName = WidgetLabelBase(cssClass + "Name");
		m_BikeIcon = WidgetImageBase(cssClass + "Icon");

		attach(m_BikeName, 0, 0);
		attach(m_BikeIcon, 0, 1);

		m_BikeName.set_text(name);
		m_BikeName.set_valign(Gtk::Align::END);
	}

private:
	WidgetLabelBase m_BikeName;
	WidgetImageBase m_BikeIcon;
};

class BatteryWidget : public WidgetGridBase
{
public:
	BatteryWidget() = default;

	BatteryWidget(const std::string& imagePath,
				  const std::string& batteryPercentStr,
				  const std::string& additionalInfoStr,
				  const std::string& cssClass) : WidgetGridBase(cssClass)
	{
		m_batteryPercentLabel = WidgetLabelBase(cssClass + "Percent");
		m_batteryExtraLabel = WidgetLabelBase(cssClass + "Extra");
		m_batteryImage = WidgetImageBase(cssClass + "Icon");

		attach(m_batteryPercentLabel,	0, 0);
		attach(m_batteryExtraLabel,		0, 1);
		attach(m_batteryImage,			0, 2);

		//m_batteryPercentLabel.set_valign(Gtk::Align::END);
		//m_batteryExtraLabel.set_valign(Gtk::Align::START);
	}

	void set_battery_icon(const std::string& imagePath)
	{
		m_batteryImage.set(imagePath);
	}

	void update_charge(const std::string& batteryPercentStr)
	{
		m_batteryPercentLabel.set_text(batteryPercentStr);
	}

	void update_extra_info(const std::string& additionalInfoStr)
	{
		m_batteryExtraLabel.set_text(additionalInfoStr);
	}
protected:
	WidgetLabelBase m_batteryPercentLabel;
	WidgetLabelBase m_batteryExtraLabel;
	WidgetImageBase m_batteryImage;
};

class WidgetBike : public Gtk::Grid
{
public:
	WidgetBike() = default;

	explicit
	WidgetBike(const eBikeInfo& info) : m_info(info)
	{
		m_BikeNameAndIcon = BikeIconAndNameWidget(m_info.getName(),
												  "eBikeWidgetBikeIcon");

		m_BatteryWidget = BatteryWidget(batteryIconPath(),
										m_info.getBatteryPercentStr(),
										m_info.getAdditionalInfoStr(),
										"eBikeWidgetBattery");

		m_AdditionalInfoLabel = WidgetLabelBase("eBikeWidgetAdditionalInfo");

		updateInfoText();

		attach(m_BikeNameAndIcon,		0, 0);
		attach(m_BatteryWidget,			1, 0);
		attach(m_AdditionalInfoLabel,	2, 0);
	}

	bool operator==(const WidgetBike& other) const
	{
		return m_info == other.m_info;
	}

	eBikeInfo getInfo() const { return m_info; }

	void updateInfoText()
	{
		m_BatteryWidget.update_charge(m_info.getBatteryPercentStr());
		m_BatteryWidget.update_extra_info(m_info.getAdditionalInfoStr());
		m_BatteryWidget.set_battery_icon(batteryIconPath());
		m_AdditionalInfoLabel.set_text(m_info.toString());
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

	BikeIconAndNameWidget m_BikeNameAndIcon;
	BatteryWidget m_BatteryWidget;
	WidgetLabelBase m_AdditionalInfoLabel;

	eBikeInfo m_info;
};

#endif // WIDGETBIKE_H
