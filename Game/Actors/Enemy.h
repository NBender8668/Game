
#pragma once
#include "Object/Actor.h"

class Enemy : public nc::Actor
{
public:
	virtual bool Load(const std::string& filename) override;

	virtual void Update(float dt) override;

	void SetTarget(Actor* actor) { m_target = actor; }

protected:
	float m_thrust;
	Actor* m_target;
};