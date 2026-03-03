#ifndef EBIKEUDP_SERVER_H
#define EBIKEUDP_SERVER_H

#define SERVER_PORT		1785


#include "server.h"
#include "../Widgets/WidgetBike.h"
#include "../Infomodel/SharedInfo.h"
#include <gtkmm/window.h>
#include <gtkmm/applicationwindow.h>
#include <iostream>

class MainWindowsInt : public Gtk::ApplicationWindow
{
public:
	virtual void RegisterBikeWidget(WidgetBike&& bike) = 0;
};

class eBikeUDPserver : public Network::ServerBase
{
public:
	eBikeUDPserver() = delete;

	eBikeUDPserver(MainWindowsInt *parent) :
		Network::ServerBase(SERVER_PORT, sizeof(struct SharedModelData), 32, Network::ServerBase::Protocol::UDP),
		parent_(parent) {};

	void OnReceive(Network::MessageBase &msg) override
	{
		if (msg.GetSize() != sizeof(struct SharedModelData)) {
			std::cerr << "Received message with invalid size: " << msg.GetSize() << std::endl;
			return;
		}

		struct SharedModelData *info = reinterpret_cast<struct SharedModelData *>(msg.GetData());

		if (info->magic_number != MAGIC_NUMBER) {
			std::cerr << "Received message with invalid magic number: " << std::hex << info->magic_number << std::dec << std::endl;
			return;
		}

		eBikeInfo bikeInfo(info);

		parent_->RegisterBikeWidget(WidgetBike(bikeInfo));
	}
private:
	MainWindowsInt *parent_;
};

#endif // EBIKEUDP_SERVER_H
