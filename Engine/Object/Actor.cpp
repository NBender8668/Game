#include "pch.h"
#include "Actor.h"
#include <fstream>
namespace nc 
{
	bool nc::Actor::Load(const std::string& filename)
	{
		bool success = false;

		std::ifstream stream(filename);
		// open stream
	 // check if stream is open
		 // set success to true
		 // stream >> into transform
		if (stream.is_open())
		{
			success = true;

			stream >> m_transform;
		};


		while (!stream.eof())
		{
			std::string shapename;
			stream >> shapename;
			m_shape.Load(shapename);
		};

		return success;

	}

	void nc::Actor::Update(float dt)
	{

	}

	void nc::Actor::Draw(Core::Graphics& graphics)
	{
		m_shape.Draw(graphics, m_transform);
	}
}