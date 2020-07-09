#include "pch.h"
#include "Actor.h"
 
namespace nc 
{
	bool nc::Actor::Load(const std::string& filename)
	{
		bool success = false;

		// open stream
	 // check if stream is open
		

		 // set success to true
		 // stream >> into transform

		std::string shapename;
		stream >> shapename;
		m_shape.Load(shapename);

		return success;

	}

	void nc::Actor::Update(float dt)
	{
	}

	void nc::Actor::Draw(Core::Graphics& graphics)
	{
	}
}