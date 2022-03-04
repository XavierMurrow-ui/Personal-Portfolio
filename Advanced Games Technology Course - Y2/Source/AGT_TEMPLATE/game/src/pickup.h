#pragma once
#include <engine.h>
#include "engine/entities/bounding_box_bullet.h"

class pickup {
public:
	enum class pick {
		slow = 0,
		damage,
		rock
	};

	pickup();
	~pickup();
	void init(const engine::game_object_properties &props, const engine::game_object_properties text, pick pow);
	void update(const engine::timestep& time_step, pick pow);
	void on_render(const engine::ref<engine::shader> shader, pick pow);
	engine::bounding_box s_box() { return m_slow_box; };
	engine::bounding_box d_box() { return m_dam_box; };
	engine::bounding_box r_box() { return m_rock_box; };
	engine::ref<engine::game_object> slow_object() { return m_slow_object; };
	engine::ref<engine::game_object> dam_object() { return m_dam_object; };
	engine::ref<engine::game_object> rock_object() { return m_rock_object; };
private:
	engine::bounding_box m_slow_box;
	engine::bounding_box m_dam_box;
	engine::bounding_box m_rock_box;
	engine::ref< engine::game_object> m_slow_object;
	engine::ref< engine::game_object> m_dam_object;
	engine::ref< engine::game_object> m_rock_object;
	engine::ref< engine::game_object> m_text;
};
