#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/listbox.h>

#include <iostream>
#include "Widgets/WidgetClock.h"
#include "Widgets/WidgetBike.h"

class MainWindows : public Gtk::Window
{
public:
	MainWindows()
	{
		set_title("eBikeGTK Desktop App");

		m_grid.set_expand(true);
		m_grid.set_column_homogeneous(true);
		set_child(m_grid);

		m_grid.attach(m_clockLabel, 0, 0);
		m_grid.attach(m_listBox, 0, 1);

		m_listBox.set_selection_mode(Gtk::SelectionMode::NONE);
		m_listBox.prepend(*(new WidgetBike()));
		m_listBox.prepend(*(new WidgetBike()));
#ifdef TARGET_ARCH_ARM64
		set_decorated(false);
		set_deletable(false);
		fullscreen();
#else
		set_default_size(600, 800);
		set_resizable(false);
#endif
	}

	~MainWindows() override {}

protected:
	Gtk::Grid m_grid;
	Gtk::ListBox m_listBox;
	WidgetClock m_clockLabel;
};

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create("");

	return app->make_window_and_run<MainWindows>(argc, argv);
}