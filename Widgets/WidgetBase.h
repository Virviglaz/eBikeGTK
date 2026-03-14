#ifndef WIDGETBASE_H
#define WIDGETBASE_H

#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>

#ifdef __x86_64__
#include <iostream>
#include <set>
#endif

static void setCssClass(Gtk::Widget& widget, const std::string& cssClass)
{
#ifdef GTKMM4
	widget.add_css_class(cssClass);
#else
	widget.get_style_context()->add_class(cssClass);
#endif
#ifdef __x86_64__
	static std::set<std::string> addedClasses {};
	if (addedClasses.count(cssClass))
		return;

	addedClasses.insert(cssClass);
	std::cout << "Added CSS class: " << cssClass << std::endl;
#endif
}

static void setExpand(Gtk::Widget& widget, bool expand = true)
{
#ifdef GTKMM4
		widget.set_expand(expand);
#else
		widget.set_hexpand(expand);
		widget.set_vexpand(expand);
#endif
}

class WidgetGridBase : public Gtk::Grid
{
public:
	WidgetGridBase() = default;

	WidgetGridBase(const std::string& cssClass, bool expand = true)
	{
		setCssClass(*this, cssClass + "Grid");
		setExpand(*this, expand);
	}
};

class WidgetLabelBase : public Gtk::Label
{
public:
	WidgetLabelBase() = default;

	WidgetLabelBase(const std::string& cssClass, bool expand = true)
	{
		setCssClass(*this, cssClass + "Label");
		setExpand(*this, expand);
	}
};

class WidgetImageBase : public Gtk::Image
{
public:
	WidgetImageBase() = default;

	WidgetImageBase(const std::string& cssClass)
	{
		setCssClass(*this, cssClass + "Image");
		setExpand(*this, false);
		set_halign(Gtk::Align::CENTER);
	}
};

#endif // WIDGETBASE_H
