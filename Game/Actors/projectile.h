#pragma once
#pragma once
#include "Object/Actor.h"

class Projectile : public nc::Actor
{
public:
	Projectile() = default;
	virtual ~Projectile() {};

	virtual eType GetType() { return eType::PROJECTILE; }

	virtual bool Load(const std::string& filename) override;

	virtual void Update(float dt) override;

	void SetThurst(float thrust) { m_thrust = thrust; }

protected:
	float m_thrust;

};


