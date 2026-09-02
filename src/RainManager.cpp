#include "RainManager.h"

namespace Rain
{
	void Precipitation::Install()
	{
		REL::Relocation<std::uintptr_t> target_0{ RELOCATION_ID(25682, 26229), OFFSET(0x463, 0x766) }; //Sky::Update
		stl::write_thunk_call<UpdatePrecipitation<0>>(target_0.address());

		REL::Relocation<std::uintptr_t> target_1{ RELOCATION_ID(25679, 26222), OFFSET(0xAA, 0x128) }; //Sky::SetMode
		stl::write_thunk_call<UpdatePrecipitation<1>>(target_1.address());

		REL::Relocation<std::uintptr_t> load_interior{ RELOCATION_ID(13171, 13316), OFFSET(0x2E6, 0x46D) };
		stl::write_thunk_call<SetInterior<0>>(load_interior.address());

		REL::Relocation<std::uintptr_t> leave_interior{ RELOCATION_ID(13172, 13317), OFFSET(0x2A, 0x1E) };
		stl::write_thunk_call<SetInterior<1>>(leave_interior.address());
	}

	void Decal::Actor::Install()
	{
		REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(36682, 37690) };  // Actor::CreateBlood
		stl::write_thunk_call<GetScreenSplatterCount>(target.address() + OFFSET(0x13A, 0x127));

	    stl::write_thunk_call<AddDecal>(target.address() + OFFSET_VERSIONED(0x925, 0x9B5, 0x9C5));  // Player

		if (Settings::GetSingleton()->GetAllowRainingNPC()) {
			stl::write_thunk_call<AddDecal>(target.address() + OFFSET_VERSIONED(0x10D5, 0x1194, 0x11A4));  // NPC
		}
	}

	void Decal::Weapon::Install()
	{
		REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(36683, 37691), OFFSET(0x89,0x88) }; // CreateBloodOnWeapon
		stl::write_thunk_call<GetUnk317>(target.address());
	}

	void Install()
	{
		Precipitation::Install();

		if (Settings::GetSingleton()->GetAllowRainingNoBlood()) {
			Decal::Actor::Install();
			Decal::Weapon::Install();
		}

		REX::INFO("Installed rain manager");
	}
}
