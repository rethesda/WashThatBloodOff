#pragma once

namespace Swim
{
	struct detail
	{
		static void clear_blood(const RE::Character* a_actor, const RE::hkpCollidable* a_collidable);
	};

	template <class T>
	struct ProcessInWater
	{
		static bool thunk(T* a_actor, RE::hkpCollidable* a_collidable, float a_waterHeight, float a_deltaTime)
		{
			detail::clear_blood(a_actor, a_collidable);
			return func(a_actor, a_collidable, a_waterHeight, a_deltaTime);
		}
		static inline REL::Relocation<decltype(thunk)> func;
		static inline constexpr std::size_t            idx{ 0x9C };
	};

	void Install();
}
