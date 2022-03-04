#pragma once
#include <engine.h>
#include "engine/entities/bounding_box_bullet.h"

class ballistic
{
public:
	ballistic(engine::game_object_properties object);
	~ballistic();

	static engine::ref<ballistic> create(engine::game_object_properties props);
	void fire(glm::vec3& pos, glm::vec3& front, float speed);
	void on_update(const engine::timestep& time_step, glm::vec3& front);
	void on_render(const engine::ref<engine::shader>& shader);

	engine::ref<engine::game_object> object() const { return m_object; }
	float time_alive() { return m_time_alive; };
	engine::bounding_box bull_box() { return m_box; };

private:
	engine::ref<engine::game_object> m_object;
	float m_speed = 0.0f;
	float m_time_alive = 0.f;
	engine::bounding_box m_box;
};
