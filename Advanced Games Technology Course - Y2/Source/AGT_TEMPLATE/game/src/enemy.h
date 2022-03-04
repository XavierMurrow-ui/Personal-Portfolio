#pragma once
#include <engine.h>
#include "engine/entities/bounding_box_bullet.h"

class enemy
{
	enum class state
	{
		idle,
		jumping,
		chasing,
		retreat
	};
public:
	enemy();
	~enemy();
	// set the parameters for the enemy
	void initialise(engine::ref<engine::game_object> object, glm::vec3 position, glm::vec3 forward);
	// update the enemy
	void on_update(const engine::timestep& time_step, const glm::vec3& player_position, const glm::vec3& zombie_position);
	// methods controlling the enemy’s behaviour in a certain state
	void on_render(const engine::ref<engine::shader> shader);
	void patrol(const engine::timestep& time_step, const glm::vec3& zombie_position);

	void jumpToPlayer(const engine::timestep& time_step);
	void face_player(const engine::timestep& time_step, const glm::vec3& player_position);
	void face_away_player(const engine::timestep& time_step, const glm::vec3& player_position);
	void chase_player(const engine::timestep& time_step, const glm::vec3& player_position);
	// game object bound to the enemy
	engine::ref<engine::game_object> object() const { return m_object; }
	float health() { return m_health; };
	void set_health(float Health) { m_health = Health; };
	engine::bounding_box box() { return m_box; };

private:
	// enemy's speed
	float m_speed{ 1.f };
	float m_timer = 0.f;
	// timer controlling the direction switch and the reset value for this timer
	float m_default_time{ 6.f };
	float m_switch_direction_timer = m_default_time;
	// threshold distances
	float m_detection_radius{ 25.f };
	float m_trigger_radius{ 5.f };
	float m_zombie_trigger_radius{ 0.5f };
	float m_health{ 100.f };
	engine::bounding_box m_box;
	glm::vec3 m_instantaneous_acceleration{ 0.f };
	glm::vec3 m_instantaneous_angular_acceleration{ 0.f };
	float m_contact_time = 0.0f;
	float m_rotational_inertia = 0.f;
	float m_phi, m_theta;
	glm::vec3 m_last_position{ 0.f };
	// game object bound to the enemy
	engine::ref< engine::game_object> m_object;
	//current state of the enemy's state machine
	state m_state = state::idle;
};
