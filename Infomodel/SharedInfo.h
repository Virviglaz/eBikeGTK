#ifndef SHARED_MODEL_DATA_H
#define SHARED_MODEL_DATA_H

#include <stdint.h>

#define MAGIC_NUMBER 0xEB1F3DA2

#ifdef __cplusplus
extern "C"
{
#endif
	struct SharedModelData
	{
		uint32_t magic_number;
		char name[32];
		char state[32];
		char battery[32];
		uint32_t mileage_km;
		uint32_t battery_percent;
		uint32_t battery_cycles;
		uint32_t temperature_x10;
	};
#ifdef __cplusplus
}
#endif

#endif // SHARED_MODEL_DATA_H
