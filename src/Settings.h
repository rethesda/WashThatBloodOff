#pragma once

class Settings : public REX::TSingleton<Settings>
{
public:
	struct WashData
	{
		WashData(std::string_view a_section) :
			enable(a_section, "bEnable"sv, true),
			affectNPC(a_section, "bAffectNPCs"sv, true)
		{}

		// members
		REX::TIniSetting<bool> enable;
		REX::TIniSetting<bool> affectNPC;
	};

	void LoadSettings();

	[[nodiscard]] bool GetAllowSwimming() const { return swimming.enable; }
	[[nodiscard]] bool GetAllowSwimmingNPC() const { return swimming.affectNPC; }
	[[nodiscard]] bool GetAllowRaining() const { return raining.enable; }
	[[nodiscard]] bool GetAllowRainingNPC() const { return raining.affectNPC; }
	[[nodiscard]] bool GetAllowRainingNoBlood() const { return preventBlood; }

private:
	static constexpr auto path = R"(Data\SKSE\Plugins\po3_WashThatBloodOff.ini)"sv;

	// members
	WashData swimming{ "Swim"sv };
	WashData raining{ "Rain"sv };

	REX::TIniSetting<bool> preventBlood{ "Rain"sv, "bNoBloodSplatter"sv, true };
};
