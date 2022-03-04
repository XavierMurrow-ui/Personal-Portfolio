#pragma once
#include <engine.h>
#include "glm/gtx/rotate_vector.hpp"
#include "engine/entities/bounding_box_bullet.h"
class player
{
const float SPEED = 0.005f;

public:
	player();
	~player();
	void initialise(engine::ref<engine::game_object> object, engine::perspective_camera& camera);//kinda constructor but not
	void on_update(const engine::timestep& time_step, engine::perspective_camera& camera);//On update
	engine::ref<engine::game_object> object() const { return m_object; }//object getter
	void update_camera(engine::perspective_camera& camera);//update player camera
	void on_render(engine::ref<engine::shader> shader);//on render, renders player object
	void birdStop();//saves last known speed for birdcam
	void birdStart();//restarts previous speed
	int Health() { return m_health; };//health getter
	float Speed() { return m_speed; };//speed getter
	float Dam() { return m_damage; };//zombie damage getter
	float sDam() { return m_sdamage; };//shrek damage getter
	void up_health(int health) { m_health = health; };//health setter
	void up_speed(float speed) {//speed setter with lower limit
		m_speed = speed;
		if (m_speed < 0.f)
			m_speed = 0.001f;
	};
	void up_damage(float dam) { m_damage = dam; };//zombie damage setter
	void up_sdamage(float dam) { m_sdamage = dam; };//shrek damage setter
	engine::bounding_box p_box() { return m_player_box; };//bounding box getter

private:
	float m_speed{ 0.001f };
	float m_last_speed;
	int m_health = 100;
	float m_damage = 0.5f;
	float m_sdamage = 0.3f;
	engine::ref< engine::game_object> m_object;
	engine::bounding_box m_player_box;
};
