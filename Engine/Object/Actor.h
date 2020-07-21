#pragma once
#include "graphics.h"
#include "core.h"
#include"../Math/Transform.h"
#include "../shape.h"

namespace nc
{
	class Scene;

	struct Actor
	{
	public:
		enum class eType
		{
			PlAYER,
			ENEMY,
			PROJECTILE
		};

	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) : m_transform{ transform }, m_shape{ shape } {};  // make sure to initialize m_transform and m_shape
		virtual	~Actor() {}

		virtual eType GetType() = 0;

		virtual bool Load(const std::string& filename);
		virtual void Load(std::istream& stream);

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor){}

		void SetScene(Scene* scene) { m_scene = scene; }

		Transform& GetTransform() { return m_transform; } // return the transform
		Shape& GetShape() { return m_shape; } // return the shape
		void setDestory(bool destory = true) { m_destory = true; }
		bool isDestory() { return m_destory; }

	protected:
		bool m_destory{ false };
		Transform m_transform;
		Shape m_shape;
		class Scene* m_scene{ nullptr };
	};
}