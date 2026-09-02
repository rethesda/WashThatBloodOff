#pragma once

#include "Settings.h"
#include "Util.h"

namespace Rain
{
	struct Precipitation
	{
	public:
		static void Install();

		static bool IsRaining() { return _raining; }
		static void SetRaining(const bool a_isRaining) { _raining = a_isRaining; }

		template <std::size_t N>
		struct UpdatePrecipitation
		{
			static void thunk(RE::Precipitation* a_precip)
			{
				func(a_precip);

				const auto sky = RE::Sky::GetSingleton();

				if (bool isRaining = sky->IsRaining(); IsRaining() != isRaining) {
					SetRaining(isRaining);

					if (IsRaining()) {
						util::clear_decals(RE::PlayerCharacter::GetSingleton());
						if (Settings::GetSingleton()->GetAllowRainingNPC()) {
							util::clear_decals_all();
						}
					}
				}
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		template <std::size_t N>
		struct SetInterior
		{
			static void thunk(bool a_isInterior)
			{
				func(a_isInterior);

				if (a_isInterior) {
					SetRaining(false);
				} else if (const auto sky = RE::Sky::GetSingleton(); sky && sky->IsRaining()) {
					util::clear_decals(RE::PlayerCharacter::GetSingleton());
					if (Settings::GetSingleton()->GetAllowRainingNPC()) {
						util::clear_decals_all();
					}
				}
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

	private:
		static inline std::atomic_bool _raining{ false };
	};

	namespace Decal::Actor
	{
		struct AddDecal
		{
			static void thunk(RE::TESObjectCELL* a_cell, RE::DECAL_CREATION_DATA& a_data, bool a_forceAdd)
			{
				if (Precipitation::IsRaining()) {
					return;
				}

				return func(a_cell, a_data, a_forceAdd);
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		struct GetScreenSplatterCount
		{
			static std::int32_t thunk(float a_damage)
			{
				auto count = func(a_damage);
				if (Precipitation::IsRaining()) {
					count = 0;
				}
				return count;
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		void Install();
	}

	namespace Decal::Weapon
	{
		struct GetUnk317
		{
			static bool thunk(RE::AIProcess* a_process)
			{
				auto result = func(a_process);
				if (result) {
					result = Precipitation::IsRaining();
				}
				return result;
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		void Install();
	}

	void Install();
}
