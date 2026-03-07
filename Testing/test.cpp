#include "server.h"
#include "SharedInfo.h"
#include <cstring>

static const char IPAddress[] = "192.168.0.177";
static const uint16_t Port = 1785;

int main(int argc, char *argv[])
{
	Network::Client client(IPAddress, Port, Network::ServerBase::Protocol::UDP);
	SharedModelData data;
	data.magic_number = MAGIC_NUMBER;
	strcpy(data.name, argc == 2 ? argv[1] : "TestModel");
	strcpy(data.state, "Idle");
	data.mileage_km = 12345;
	data.battery_percent = 80;
	data.battery_cycles = 500;
	client.Send(reinterpret_cast<const char*>(&data), sizeof(data));
	return 0;
}