#include "projectile.h"
#include <fstream>
bool Projectile::Load(const std::string& filename)
{
    bool success = false;

    std::ifstream stream(filename);
    if (stream.is_open())
    {
        success = true;

        // load the base actor members
        Actor::Load(stream);

        // stream into thrust
        stream >> m_thrust;

        stream.close();
    }

    return success; 
	
}

void Projectile::Update(float dt)
{
	nc::Vector2 direction = nc::Vector2::Rotate(nc::Vector2::foward, m_transform.angle);

		nc::Vector2 velocity = direction * m_thrust;
	m_transform.position = m_transform.position + velocity * dt;


	m_transform.Update();
}
