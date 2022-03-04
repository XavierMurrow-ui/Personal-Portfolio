#pragma once
#include <engine.h>
#include "player.h"
#include "birdView.h"
#include "ballistic.h"
#include "cross_fade.h"
#include "HUD.h"
#include "engine/entities/bounding_box_bullet.h"
#include "zombie_enemy.h"
#include "enemy.h"
#include "pickup.h"

class pickup;

class example_layer : public engine::layer
{
public:
    example_layer();
	~example_layer();

    void on_update(const engine::timestep& time_step) override;
    void on_render() override; 
    void on_event(engine::event& event) override;
	engine::perspective_camera getCamera();
	void gunRender(const engine::ref<engine::shader> &shader);
	void touchRender(const engine::ref<engine::shader> &shader);
	void mapRender(const engine::ref<engine::shader> &shader);
	float RandomFloat(float a, float b);

private:

	engine::ref<engine::skybox>			m_skybox{};
	engine::ref<engine::game_object>	m_terrain{};
	engine::ref<engine::game_object>	m_mannequin{};
	engine::ref<engine::game_object>	m_road{};//Mesh road
	engine::ref<engine::game_object>	m_road_turn{};//Mesh road
	engine::ref<engine::game_object>	m_house{};//Mesh house
	std::vector<engine::bounding_box>		m_house_box{15};
	engine::ref<engine::game_object>	m_house2{};//Mesh modern house
	std::vector<engine::bounding_box>		m_house2_box{15};
	engine::ref<engine::game_object>	m_tetrahedron{};//Primitive game object
	engine::ref<engine::game_object>	m_octagonal{};//Primitive game object
	engine::ref<engine::game_object>	m_diamond{};//Primitive game object
	engine::ref<engine::game_object>	m_gun{};//gun object
	engine::ref<engine::game_object>	m_ball{};//ball object (might not be used)
	std::vector<pickup>					m_pick{3};//pickup/powerup object
	engine::ref<engine::game_object>	m_shrek{};//main enemy
	engine::game_object_properties		m_sphere_props{};//bullets
	player m_player{};//player object
	enemy m_enemy;//enemy for shrek
	std::vector<engine::ref<zombie_enemy>> m_zombies{};//vector of zombies

	birdView m_birdview{};//birdview class
	std::vector<engine::ref<ballistic>> m_bullets{};//bullets class

	engine::ref<engine::material>		m_material{};
	engine::ref<engine::material>		m_mannequin_material{};
	engine::ref<engine::material>		m_ballistic_material{};
	engine::ref<engine::material>		m_octagonal_material{};
	engine::ref<engine::material>		m_lightsource_material{};

	engine::DirectionalLight            m_directionalLight;

	engine::PointLight					m_pointLight;
	uint32_t							num_point_lights = 1;

	engine::SpotLight					m_touchLight;
	uint32_t							num_spot_lights = 1;

	std::vector<engine::ref<engine::game_object>>     m_game_objects{};

	engine::ref<engine::bullet_manager> m_physics_manager{};
	float								m_prev_sphere_y_vel = 0.f;
	engine::ref<engine::text_manager>	m_text_manager{};
	engine::ref<engine::audio_manager>  m_audio_manager{};

    engine::orthographic_camera       m_2d_camera; 
    engine::perspective_camera        m_3d_camera;

	engine::ref<cross_fade>							m_cross_fade{};
	engine::ref<cross_fade>							m_blood{};
	engine::ref<HUD>								m_HUD{};

	float m_timer = 0.f;
	float m_fire_rate = 0.f;
	float m_game_timer = 180.f;
	bool							  m_start_game = false;//Bool for intro and outro screen
	bool							  m_lose_game = false;
	bool							  m_win_game = false;
	const engine::ref<engine::shader> m_text_shader = engine::renderer::shaders_library()->get("text_2D");//global text renderer for powerups
	bool dam, slow, rock = false;//for powerups
};
