#include "Mapper.h"
#include "Mapper000.h"

std::shared_ptr<Mapper> getMapperByID(uint8_t ID, uint8_t PRGBanks, uint8_t CHRBanks)
{
	switch (ID)
	{
		case 0: return std::make_shared<Mapper000>(PRGBanks, CHRBanks);
		default: return nullptr; //need to die here
	}
}