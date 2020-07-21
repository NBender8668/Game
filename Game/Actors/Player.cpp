#include "Player.h"
#include "Math/Math.h"
#include "projectile.h"
#include"Object/Scene.h"
#include <fstream>
bool Player::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		// load the base actor members
		Actor::Load(stream);
		stream >> m_thrust;
		stream >> m_rotation;
		// stream into thrust
		// stream into rotation rate

		stream.close();
	}

	return success;

}

void Player::Update(float dt)
{
	m_fireTimer += dt;

	if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
	{
		m_fireTimer = 0;

		Projectile* projectile = new  Projectile;
		projectile->Load("projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;
		m_scene->AddActor(projectile);
	}


	float thrust = 300.0f;
	nc::Vector2 velocity;

	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::foward * m_thrust; }
	force = nc::Vector2::Rotate(force, m_transform.angle);

	//force = force + nc::Vector2{ 0,100 };

	m_velocity = m_velocity + force * dt;
	m_velocity = m_velocity * 0.99f;


	nc::Vector2 direction = force;
	m_transform.position = m_transform.position + m_velocity * dt;
	//transform.position = transform.position + (direction * 2.0f);

	//rotate
	if (Core::Input::IsPressed('A')) { m_transform.angle = m_transform.angle - (dt * nc::DegreesToRadians(m_rotation)); };
	if (Core::Input::IsPressed('D')) { m_transform.angle = m_transform.angle + (dt * nc::DegreesToRadians(m_rotation)); };

	//transform.position = nc::Clamp(transform.position, { 0,0 }, { 800,600 });

	if (m_transform.position.x > 800) m_transform.position.x = 0;	
	if (m_transform.position.x < 0) m_transform.position.x = 800;	

	if (m_transform.position.y > 600) m_transform.position.y = 0;	
	if (m_transform.position.y < 0) m_transform.position.y = 600;

	m_transform.Update();

//player.GetTransform().position.x = nc::Clamp(player.GetTransform().position.x, 0.0f, 800.0f);
//player.GetTransform().position.y = nc::Clamp(player.GetTransform().position.y, 0.0f, 600.0f);
//if (Core::Input::IsPressed('A')) { position += nc::Vector2::left * speed * dt; }
//if (Core::Input::IsPressed('D')) { position += nc::Vector2::right * speed * dt; }
//if (Core::Input::IsPressed('W')) { position += nc::Vector2::up * speed * dt; }
//if (Core::Input::IsPressed('S')) { position += nc::Vector2::down * speed * dt; }
}


