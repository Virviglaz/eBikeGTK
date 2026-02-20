#ifndef SHARED_MODEL_DATA_H
#define SHARED_MODEL_DATA_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
	struct SharedModelData
	{
		char name[32];
		uint32_t mileage_km;
		uint32_t battery_percent;
		uint32_t battery_cycles;
	};
#ifdef __cplusplus
}
#endif

#endif // SHARED_MODEL_DATA_H
