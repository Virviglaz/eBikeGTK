#include <gtkmm/label.h>
#include <glibmm/main.h>
#include <ctime>
#include <locale>

class Clock
{
public:
	static const std::string get_time()
	{
		std::time_t time = std::time({});
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
	}
private:
	bool update_time()
	{
		set_text(Clock::get_time());

		return true;
	}
};
