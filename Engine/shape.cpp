#include "pch.h"
#include "shape.h"
#include "Math/Color (2).h"
#include <fstream>
#include <string>
bool nc::Shape::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);


	if (stream.is_open())
	{
		success = true;
		//get color
		stream >> m_color;
		//get number of points
		std::string line;
		std::getline(stream, line);
		size_t size;
		size = stoi(line);

		for (size_t i = 0; i < size; i++)
		{
			Vector2 v;
			stream >> v;
			m_points.push_back(v);
		}

		//read points

		stream.close();
	}

	return success;
};

void nc::Shape::Draw(Core::Graphics& graphics, nc::Vector2 position, float scale , float angle)
{

	graphics.SetColor(m_color);


	for (size_t i = 0; i < m_points.size() - 1; i++)
	{
		// local / object space points

		nc::Vector2 p1 = m_points[i];
		nc::Vector2 p2 = m_points[i + 1];

		// transform points

		//scale
		p1 = p1 * scale;
		p2 = p2 * scale;

		//rotate
		p1 = nc::Vector2::Rotate(p1, angle);
		p2 = nc::Vector2::Rotate(p2, angle);


		//translate
		p1 = p1 + position;
		p2 = p2 + position;

		// draw points
		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	};
}
void nc::Shape::Draw(Core::Graphics& graphics, const Transform& transform)
{
	Draw(graphics, transform.position, transform.scale, transform.angle);
}
;
