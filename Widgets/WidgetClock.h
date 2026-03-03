#ifndef WIDGETCLOCK_H
#define WIDGETCLOCK_H

#include <gtkmm/label.h>
#include <glibmm/main.h>
#include <chrono>
#include <ctime>
#include <locale>
#include <gtkmm/cssprovider.h>

class Clock {
    public:
	/**
	 * @brief Get the current time as a formatted string.
	 *
	 * @param time The time to format. If not provided, the current time will be used.
	 * @return A string representing the formatted time.
	 */
	static std::string get_time(std::time_t time = std::time(nullptr))
	{
		char timeString[20];
		std::strftime(timeString, sizeof(timeString), "%F %T", std::localtime(&time));

		return std::string(timeString);
	}
};

class WidgetClock : public Gtk::Label {
    public:
	WidgetClock() : Gtk::Label()
	{
		Glib::signal_timeout().connect(sigc::mem_fun(*this, &WidgetClock::update_time), 1000);
#ifdef GTKMM4
		add_css_class("eBikeDateTimeLabel");
#else
		get_style_context()->add_class("eBikeDateTimeLabel");
#endif
	}

    private:
	bool update_time()
	{
		set_text(Clock::get_time());

		return true;
	}
};

#endif // WIDGETCLOCK_H
