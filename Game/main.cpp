
#include <iostream>
#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"

#include "Math/Color (2).h"
#include "Math/Transform.h"
#include "shape.h"
#include <vector>
#include <string>


//std::vector<nc::Vector2> points = { { 4, 0 },{0,3},{-4,0},{0,-3},{4,0} };

//nc::Color color{ 1,5,7 };



nc::Shape ship;
//nc::Shape ship{points,color};

nc::Transform transform{ {400,300},4,0 };


const size_t NUM_POINTS = 40;
float speed = 300.0f;

float t{ 0 };

float frametime;
float roundTime{ 0 };
bool gameover{ false };

DWORD prevTime;
DWORD deltaTime;

bool Update(float dt) //delta time (1/60 = 0.16)
{
	//dt = current frame time - previous frame time
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	t = t + dt;

	frametime = dt;
	roundTime += dt;

	if (roundTime >= 60.0f) gameover = true;

	if(gameover) dt = 0;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x;
	int y;
	Core::Input::GetMousePos(x,y);

	//nc::Vector2 target = nc::Vector2{ x,y };
	//nc::Vector2 direction = target - position; // (head <- tail)
	//direction.Normalize();
	
	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::foward * speed * dt; }
	nc::Vector2 direction = force;
	direction = nc::Vector2::Rotate(direction, transform.angle);
	transform.position = transform.position + (direction * 2.0f);

	//rotate
	if (Core::Input::IsPressed('A')) { transform.angle = transform.angle - (dt * nc::DegreesToRadians(360.0f)); };
	if (Core::Input::IsPressed('D')) { transform.angle = transform.angle + (dt * nc::DegreesToRadians(360.0f)); };

	//transform.position = nc::Clamp(transform.position, { 0,0 }, { 800,600 });

	transform.position.x = nc::Clamp(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Clamp(transform.position.y, 0.0f, 600.0f);
	//if (Core::Input::IsPressed('A')) { position += nc::Vector2::left * speed * dt; }
	//if (Core::Input::IsPressed('D')) { position += nc::Vector2::right * speed * dt; }
	//if (Core::Input::IsPressed('W')) { position += nc::Vector2::up * speed * dt; }
	//if (Core::Input::IsPressed('S')) { position += nc::Vector2::down * speed * dt; }
	

	
	return quit;
}



void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime /1000.0f).c_str());

	float v = (std::sin(t)+1.0f)* 0.5f; //0 - 2

	nc::Color c = nc::Lerp(nc::Color{ 0,0,1 }, nc::Color{ 1,0,0 }, t);
	graphics.SetColor(c);

	nc::Vector2 p = nc::Lerp(nc::Vector2{ 400,300 }, nc::Vector2{ 400,100 }, v);
	graphics.DrawString(p.x, p.y, "Some Game");

	if (gameover) graphics.DrawString(400, 300, "Game Over");

	ship.Draw(graphics, transform);


	
};

int main()
{
	DWORD ticks = GetTickCount(); //how many tick per second (1000)
	std::cout << ticks / 1000 << std::endl;
	prevTime = GetTickCount();

	ship.Load("Diamond_Ship.txt");
	//ship.SetColor(nc::Color{ 1,1,1 });

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
};

