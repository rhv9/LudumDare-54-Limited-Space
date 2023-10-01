#pragma once
#include <Gonk.h>

using namespace Gonk;

struct AnimationComponent
{
	std::vector<std::vector<Ref<SubTexture2D>>> Animations;

	float AnimationTime = 1.0f;

	AnimationComponent() = default;
	AnimationComponent(const AnimationComponent&) = default;
	AnimationComponent(float animationTime, const std::vector<std::vector<Ref<SubTexture2D>>> animations)
		: Animations(animations), AnimationTime(animationTime) {}
};

struct SubTextureComponent
{
	Ref<SubTexture2D> SubTexture;

	float AnimationTime = 1.0f;

	SubTextureComponent() = default;
	SubTextureComponent(const SubTextureComponent&) = default;
	SubTextureComponent(Ref<SubTexture2D> subTexture)
		: SubTexture(subTexture) {}
};

struct HealthComponent
{
	float MaxHp = 1.0f;
	float Hp = 1.0f;

	HealthComponent() = default;
	HealthComponent(const HealthComponent&) = default;
	HealthComponent(float maxHp, float hp)
		: MaxHp(maxHp), Hp(hp) {}

	void AddHp(float hp) { Hp += hp; }
	void RemoveHp(float hp) { Hp -= hp; }

	bool IsDead() { Hp <= 0.0f; }
};