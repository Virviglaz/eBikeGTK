#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/listbox.h>
#include <gtkmm/cssprovider.h>
#include <list>

#include "Widgets/WidgetClock.h"
#include "Widgets/WidgetBike.h"
#include "Server/eBikeUDPserver.h"
#include "Infomodel/Settings.h"

class MainWindows : public MainWindowsInt
{
public:
	MainWindows()
	{
		m_grid.set_column_homogeneous(true);
		m_grid.attach(m_clockLabel, 0, 0);
		m_grid.attach(m_listBox, 0, 1);

		auto m_refCssProvider = Gtk::CssProvider::create();
#ifdef GTKMM4
		m_grid.set_expand(true);
		set_child(m_grid);
		add_css_class("eBikeMainWindow");
		m_listBox.add_css_class("eBikeMainWindowListBox");
		m_listBox.set_selection_mode(Gtk::SelectionMode::NONE);

		Gtk::StyleProvider::add_provider_for_display(get_display(),
			m_refCssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
#else
		//set_position(Gtk::WIN_POS_CENTER);
		m_grid.set_hexpand(false);
		m_grid.set_vexpand(false);
		add(m_grid);
		get_style_context()->add_class("eBikeMainWindow");
		m_grid.get_style_context()->add_class("eBikeWidgetGrid");
		m_listBox.get_style_context()->add_class("eBikeMainWindowListBox");
		m_listBox.set_selection_mode(Gtk::SelectionMode::SELECTION_NONE);

		Gtk::StyleContext::add_provider_for_screen(Gdk::Screen::get_default(),
			m_refCssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
#endif
		m_refCssProvider->load_from_path(getPath() + "Theme/style.css");

		set_resizable(false);
		set_decorated(false);
		set_deletable(false);
		set_default_size(480, 800);
		set_size_request(480, 800);
		fullscreen();

		m_server.Start();
#if 1
		RegisterBikeWidget(WidgetBike(eBikeInfoDebug("Test bike 1", 20)));
		RegisterBikeWidget(WidgetBike(eBikeInfoDebug("Test bike 2", 50)));
		RegisterBikeWidget(WidgetBike(eBikeInfoDebug("Test bike 3", 90)));
		RegisterBikeWidget(WidgetBike(eBikeInfoDebug("Test bike 1", 55)));
#endif
	}

	~MainWindows() override {
		m_server.Stop();
	}

	void RegisterBikeWidget(WidgetBike&& bike) override
	{
		auto existingBikeIt = std::find(m_bikes.begin(), m_bikes.end(), bike);
		if (existingBikeIt != m_bikes.end())
		{
			m_listBox.remove(*(existingBikeIt->get_parent()));
			m_bikes.remove(*existingBikeIt);
		}

		/* Move actual item to container */
		m_bikes.push_back(std::forward<WidgetBike>(bike));

		/* Use reference to it */
		m_listBox.prepend(m_bikes.back());
	}
private:
	Gtk::Grid m_grid;
	Gtk::ListBox m_listBox;
	WidgetClock m_clockLabel;
	std::list<WidgetBike> m_bikes;
	eBikeUDPserver m_server = eBikeUDPserver(this);
};

int main(int argc, char *argv[])
{
	if (argc > 1)
		setPath(argv[1]);
#ifdef GTKMM4
	auto app = Gtk::Application::create("");
	return app->make_window_and_run<MainWindows>(++argc, ++argv);
#else
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create("");
	MainWindows window;
	window.show_all();
	return app->run(window);  
#endif
}