#ifndef EBIKEUDP_SERVER_H
#define EBIKEUDP_SERVER_H

#define SERVER_PORT		1785

#include <sigc++/sigc++.h>
#include <iostream>

#include "server.h"
#include "../Widgets/WidgetBike.h"
#include "../Infomodel/SharedInfo.h"

using infoModelCallback = sigc::slot<void(WidgetBike &&)>;

class eBikeUDPserver : public Network::ServerBase
{
public:
	eBikeUDPserver() = delete;

	eBikeUDPserver(infoModelCallback cb) :
		Network::ServerBase(SERVER_PORT, 128, 32, Network::ServerBase::Protocol::UDP),
		m_registerBikeFunc(cb) {};

	void OnReceive(Network::MessageBase &msg) override
	{
		if (msg.GetSize() != sizeof(struct SharedModelData)) {
			std::cerr << "Received message with invalid size: " << msg.GetSize() << std::endl;
			return;
		}

		struct SharedModelData *info = reinterpret_cast<struct SharedModelData *>(msg.GetData());

		eBikeInfo bikeInfo(info);

		m_registerBikeFunc(WidgetBike(bikeInfo));
	}
private:
	infoModelCallback m_registerBikeFunc;
};

#endif // EBIKEUDP_SERVER_H
