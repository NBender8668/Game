
#include <iostream>
#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include"Object/Actor.h"
#include "Math/Color (2).h"
#include "Math/Transform.h"
#include "shape.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Object/Scene.h"
#include <vector>
#include <string>
#include <list>



nc::Scene scene;

float frametime;
float spawntimer{0};
float t{ 0 };


DWORD prevTime;
DWORD deltaTime;

bool Update(float dt) //delta time (1/60 = 0.16)
{
	//dt = current frame time - previous frame time
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	frametime = dt;

	spawntimer += dt;


	if (spawntimer >= 3.0f)
	{
		spawntimer = 0.0f;

		nc::Actor* enemy = new  Enemy;
		enemy->Load("enemy.txt");
		dynamic_cast<Enemy*>(enemy)->SetTarget(scene.GetActor<Player>());
		dynamic_cast<Enemy*>(enemy)->SetThurst(nc::random(50, 100));
		enemy->GetTransform().position = nc::Vector2{ nc::random(0,800),nc::random(0,600) };

		scene.AddActor(enemy);

	};

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	int x;
	int y;
	
	scene.Update(dt);


	
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

	

	
	scene.Draw(graphics);

	
};

int main()
{
	scene.Startup();

	DWORD ticks = GetTickCount(); //how many tick per second (1000)
	std::cout << ticks / 1000 << std::endl;
	prevTime = GetTickCount();

	nc::Actor* player = new Player;
	player->Load("player.txt");
	scene.AddActor(player);

	for (int i = 0; i < 10; i++)
	{
		nc::Actor* enemy = new  Enemy;
		enemy->Load("enemy.txt");
		dynamic_cast<Enemy*>(enemy)->SetTarget(scene.GetActor<Player>());
		dynamic_cast<Enemy*>(enemy)->SetThurst(nc::random(50, 100));
		enemy->GetTransform().position = nc::Vector2{ nc::random(0,800),nc::random(0,600) };
		
		scene.AddActor(enemy);
	}

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	scene.Shutdown();
};

