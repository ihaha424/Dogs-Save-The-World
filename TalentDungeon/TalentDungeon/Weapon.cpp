#include "Weapon.h"

Weapon::Weapon(float _damage, float _delayTime) :damage(_damage), delayTime(_delayTime), MaxShot(1) {}

Weapon::~Weapon()
{
}

void Weapon::FixedUpdate()
{
}

