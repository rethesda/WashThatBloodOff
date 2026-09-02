#include "SwimManager.h"
#include "RainManager.h"

namespace Swim
{
	void detail::clear_blood(const RE::Character* a_actor, const RE::hkpCollidable* a_collidable)
	{
		if (Rain::Precipitation::IsRaining() && Settings::GetSingleton()->GetAllowRainingNoBlood()) {
			return;
		}

		if (const auto colLayer = a_collidable->broadPhaseHandle.collisionFilterInfo.GetCollisionLayer(); colLayer == RE::COL_LAYER::kCharController) {
			if (a_actor->IsSwimming() && util::can_show_blood(a_actor)) {
				util::clear_decals(a_actor);
			}
		}
	}

	void Install()
	{
		stl::write_vfunc<RE::PlayerCharacter, ProcessInWater::Player>();

		if (Settings::GetSingleton()->GetAllowSwimmingNPC()) {
			stl::write_vfunc<RE::Character, ProcessInWater::NPC>();
		}

		REX::INFO("Installed swim manager");
	}
}
