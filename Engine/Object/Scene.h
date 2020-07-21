#pragma once
#include "core.h"
#include "Actor.h"
#include <vector>
#include <List>
namespace nc
{
	class Scene
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void AddActor(class Actor* actor);
		void RemoveActor(class Actor* object);

		template <typename T>
		T* GetActor() {
			T* actor = { nullptr };
			for(Actor* a : m_actors)
			{
				actor = dynamic_cast<T*>(a);
				if (actor)break;
			}
			return actor;
	
		}


		template <typename T>
		std::vector<T*> GetActors() 
		{
			std::vector<nc::Actor*> results;

			for (nc::Actor* actor : m_actors)
			{
				T* result = dynamic_cast<T*>(actor);
				if (result)
				{
					results.push_back(result);
				}
			}

			return results;

			
		}

	private:
		std::list<class Actor*> m_actors;
	};
}
