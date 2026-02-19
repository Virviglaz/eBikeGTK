#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>

class WidgetBike : public Gtk::Grid
{
public:
	WidgetBike() : Gtk::Grid()
	{
		m_imageBike.set_pixel_size(100);
		m_imageBike.set("Resources/bike_icon.png");

		m_imageBattery.set_pixel_size(20);
		m_imageBattery.set("Resources/battery_50.png");

		m_label.set_text("Bike");

		attach(m_imageBike,		0, 0);
		attach(m_imageBattery,	1, 0);
		attach(m_label,			2, 0);
		set_expand(true);
		set_column_homogeneous(true);
	}
private:
	Gtk::Image m_imageBike;
	Gtk::Image m_imageBattery;
	Gtk::Label m_label;
};