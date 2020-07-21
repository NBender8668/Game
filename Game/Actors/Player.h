#pragma once
#include "Object/Actor.h"

class Player : public nc::Actor
{
public:
	Player() {};
	virtual ~Player() {};

	virtual eType GetType() { return eType::PlAYER; }
	virtual bool Load(const std::string& filename) override;

	virtual void Update(float dt) override;
	

protected:
	float m_thrust;
	nc::Vector2 m_velocity;
	float m_rotation;
	float m_fireRate{ 0.5f };
	float m_fireTimer{ 0.0f };
	
};