#pragma once
#include "Object/Actor.h"

class Enemy : public nc::Actor
{
public:
	Enemy() = default;
	virtual ~Enemy() {};

	virtual eType GetType() { return eType::ENEMY; }

	virtual bool Load(const std::string& filename) override;

	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* actor);

	void SetTarget(Actor* actor) { m_target = actor; }

	void SetThurst(float thrust) { m_thrust = thrust; }

protected:
	float m_thrust;
	Actor* m_target;
};