#ifndef WIDGETCLOCK_H
#define WIDGETCLOCK_H

#include <gtkmm/label.h>
#include <glibmm/main.h>
#include <chrono>
#include <ctime>
#include <locale>
#include <gtkmm/cssprovider.h>

class Clock
{
public:
	static const std::string get_time(std::time_t time = std::time(nullptr))
	{
		char timeString[std::size("yyyy-mm-ddThh:mm:ssZ")];
		std::strftime(std::data(timeString), std::size(timeString),
				  "%F %T", std::gmtime(&time));

		return timeString;
	}
};

class WidgetClock : public Gtk::Label
{
public:
	WidgetClock() : Gtk::Label()
	{
		Glib::signal_timeout().connect(sigc::mem_fun(*this, &WidgetClock::update_time), 1000);
		add_css_class("eBikeDateTimeLabel");
	}
private:
	bool update_time()
	{
		set_text(Clock::get_time());

		return true;
	}
};

#endif // WIDGETCLOCK_H
