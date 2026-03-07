#include <gtkmm.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/listbox.h>
#include <gtkmm/cssprovider.h>
#include <list>
#include <queue>
#include <mutex>

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
		//m_grid.set_hexpand(false);
		//m_grid.set_vexpand(false);
		add(m_grid);
		get_style_context()->add_class("eBikeMainWindow");
		m_grid.get_style_context()->add_class("eBikeWidgetGrid");
		m_listBox.get_style_context()->add_class("eBikeMainWindowListBox");
		m_listBox.set_selection_mode(Gtk::SelectionMode::SELECTION_NONE);

		Gtk::StyleContext::add_provider_for_screen(Gdk::Screen::get_default(),
			m_refCssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
#endif
		std::string cssPath = getPath() + "Theme/style.css";
		m_refCssProvider->load_from_path(cssPath);

		set_resizable(false);
		set_decorated(false);
		set_deletable(false);
		set_size_request(480, 800);
#ifndef __x86_64__
		fullscreen();
#endif
		m_dispatcher.connect(sigc::mem_fun(*this, &MainWindows::on_notification_received));
		Glib::signal_timeout().connect(sigc::mem_fun(*this, &MainWindows::UpdateBikeWidgetTimeInfo), 1000);

		try {
			m_server.Start();
		} catch (const std::exception &e) {
			std::cerr << "Failed to start server: " << e.what() << std::endl;
		}
#ifdef __x86_64__
		RegisterBikeWidgetInternal(WidgetBike(eBikeInfoDebug("Test bike 1", 20)));
		RegisterBikeWidgetInternal(WidgetBike(eBikeInfoDebug("Test bike 2", 50)));
		RegisterBikeWidgetInternal(WidgetBike(eBikeInfoDebug("Test bike 3", 90)));
		RegisterBikeWidgetInternal(WidgetBike(eBikeInfoDebug("Test bike 1", 55)));
#endif
	}

	~MainWindows() override {
		m_server.Stop();
	}

	void RegisterBikeWidget(WidgetBike&& bike) override
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_data_queue.push(std::move(bike));
		m_dispatcher.emit();
	}
private:
	void RegisterBikeWidgetInternal(WidgetBike&& bike)
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
#ifndef GTKMM4
		m_listBox.show_all();
#endif
	}

	bool UpdateBikeWidgetTimeInfo()
	{
		for (auto& bike : m_bikes)
			bike.updateInfo();
		return true;
	}

	void on_notification_received()
	{
		// 4. Lock, Pop, and Update UI (Main Thread)
		std::lock_guard<std::mutex> lock(m_mutex);
		while (!m_data_queue.empty()) {
			RegisterBikeWidgetInternal(std::move(m_data_queue.front()));
			m_data_queue.pop();
		}
	}

	Gtk::Grid m_grid;
	Gtk::ListBox m_listBox;
	WidgetClock m_clockLabel;
	std::list<WidgetBike> m_bikes;
	eBikeUDPserver m_server = eBikeUDPserver(this);
	Glib::Dispatcher m_dispatcher;
	std::queue<WidgetBike> m_data_queue;
	std::mutex m_mutex;
};

int main(int argc, char *argv[])
{
	if (argc > 1)
		setPath(argv[1]);
#ifdef GTKMM4
	auto app = Gtk::Application::create("gtkmm.eBikeGTK.application");
	return app->make_window_and_run<MainWindows>(0, nullptr);
#else
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create("gtkmm.eBikeGTK.application");
	MainWindows window;
	window.show_all();
	return app->run(window);  
#endif
}