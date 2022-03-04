#pragma once
#include <engine.h>
#include "engine/entities/bounding_box_bullet.h"

class zombie_enemy
{
	enum class state
	{
		idle,
		on_guard,
		chasing,
		attacking
	};
public:
	zombie_enemy(engine::game_object_properties object, engine::ref<engine::model> zombie_model, glm::vec3& position, glm::vec3& forward);
	~zombie_enemy();
	// update the enemy
	void on_update(const engine::timestep& time_step, const glm::vec3& player_position, engine::bounding_box& p_box);
	static engine::ref<zombie_enemy> create(engine::game_object_properties props, engine::ref<engine::model> zombie_model, glm::vec3& position, glm::vec3& forward);
	// methods controlling the enemy’s behaviour in a certain state
	void patrol(const engine::timestep& time_step);
	void on_render(const engine::ref<engine::shader> &shader);
	void attacking(const engine::timestep& time_step, const glm::vec3& player_position);
	void face_player(const engine::timestep& time_step, const glm::vec3& player_position);
	void chase_player(const engine::timestep& time_step, const glm::vec3& player_position);
	// game object bound to the enemy
	engine::ref<engine::game_object> object() const { return m_object; }
	float health() { return m_health; };
	void set_health(float Health) { m_health = Health; };
	engine::bounding_box box() { return m_box; };

private:
	// enemy's speed
	float m_speed{ 2.f };
	// timer controlling the direction switch and the reset value for this timer
	float m_default_time{ 6.f };
	float m_switch_direction_timer = m_default_time;
	// threshold distances
	float m_detection_radius{ 6.f };
	float m_trigger_radius{ 3.f };
	float m_health{10.f};
	engine::bounding_box m_box;
	// game object bound to the enemy
	engine::ref<engine::game_object> m_object;
	//current state of the enemy's state machine
	state m_state = state::idle;
};
