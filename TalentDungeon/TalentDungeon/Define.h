#pragma once

#define DebugModeFlag 0

namespace game
{
#define FixedUpdateTime 0.02 //0.02√ 
#define ScreenWidth 2560
#define ScreenHeight 1080

	enum class OBJECT_TYPE
	{
		DEFAULT,
		BACKGROUND,
		FACTORY,
		MONSTER,
		ITEM,
		WEAPON,
		PLAYER,
		UI,
		EventManager,

		END//√÷¥Î 32
	};

	enum class SCENE_TYPE
	{
		START,
		STAGE_01,

		FINISH_LOSE,
		FINISH_WIN,
		END
	};

	enum Status
	{
		DeActive,
		Active,
		UnVisible,
		Destroy
	};

	enum class eSoundChannel
	{
		BGM,
		Effect_Shot,
		Effect_Dash,
		Effect_Collision,
		End
	};

	enum class eSoundList
	{
		StartBGM,
		MainBGM,
		BossBGM,

		DashEffect,
		ShotEffect,
		CollisionEffect,

		End
	};
}
