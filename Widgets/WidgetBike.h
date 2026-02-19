#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>

class WidgetBike : public Gtk::Grid
{
public:
	WidgetBike() : Gtk::Grid()
	{
		m_image.set_pixel_size(100);
		m_image.set("Resources/bike_icon.png");

		m_label.set_text("Bike");

		attach(m_image, 0, 0);
		attach(m_label, 1, 0);
		set_expand(true);
		set_column_homogeneous(true);
	}
private:
	Gtk::Image m_image;
	Gtk::Label m_label;
};