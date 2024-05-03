#pragma once
#include "UI.h"
class FireBoneSkillUI :
    public game::UI
{
public:
	FireBoneSkillUI();
	~FireBoneSkillUI();

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);

};

