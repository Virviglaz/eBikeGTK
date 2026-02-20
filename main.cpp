#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/listbox.h>
#include <gtkmm/cssprovider.h>
#include <list>

#include <iostream>
#include "Widgets/WidgetClock.h"
#include "Widgets/WidgetBike.h"
#include "Server/eBikeUDPserver.h"

class MainWindows : public Gtk::Window
{
public:
	MainWindows()
	{
		m_grid.set_expand(true);
		m_grid.set_column_homogeneous(true);
		m_grid.attach(m_listBox, 0, 0);

		set_child(m_grid);
		set_titlebar(m_clockLabel);

		m_listBox.add_css_class("eBikeMainWindowListBox");
		m_listBox.set_selection_mode(Gtk::SelectionMode::NONE);

		auto m_refCssProvider = Gtk::CssProvider::create();
		Gtk::StyleProvider::add_provider_for_display(get_display(), m_refCssProvider,
			GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		m_refCssProvider->load_from_path("Theme/style.css");

#ifdef TARGET_ARCH_ARM64
		set_decorated(false);
		set_deletable(false);
		fullscreen();
#else
		set_default_size(600, 800);
		add_css_class("eBikeMainWindow");
		set_resizable(false);
#endif
		m_server.Start();
#if 1
		registerBikeWidget(WidgetBike(eBikeInfoDebug("Test bike 1", 20)));
		registerBikeWidget(WidgetBike(eBikeInfoDebug("Test bike 2", 50)));
		registerBikeWidget(WidgetBike(eBikeInfoDebug("Test bike 3", 90)));
		registerBikeWidget(WidgetBike(eBikeInfoDebug("Test bike 1", 55)));
#endif
	}

	~MainWindows() override {
		m_server.Stop();
	}

private:
	void registerBikeWidget(WidgetBike&& bike)
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

	Gtk::Grid m_grid;
	Gtk::ListBox m_listBox;
	WidgetClock m_clockLabel;
	std::list<WidgetBike> m_bikes;
	eBikeUDPserver m_server = eBikeUDPserver(sigc::mem_fun(*this, &MainWindows::registerBikeWidget));
};

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create("");

	return app->make_window_and_run<MainWindows>(argc, argv);
}