#include <engine.h>
#include "pch.h"
#include "player.h"

player::player() : m_speed(SPEED) {}

player::~player(){}

void player::initialise(engine::ref<engine::game_object> object, engine::perspective_camera &camera)
{
	m_object = object;
	m_object->set_forward(glm::vec3(camera.front_vector()));
	m_object->set_position(glm::vec3(0.f, 0.f, -40.f));
	m_player_box.set_box(0.5f, 1.f, 0.5f, glm::vec3(m_object->position().x, m_object->position().y - 0.5f, m_object->position().z) ,false);
}
void player::on_update(const engine::timestep& time_step, engine::perspective_camera& camera)
{
	//how my movement works
	m_object->set_position( glm::vec3(m_object->position().x,glm::clamp(m_object->position().y, 1.5f, 1.5f), m_object->position().z) + m_speed * normalize(camera.front_vector()));
	m_player_box.on_update(glm::vec3(m_object->position().x, m_object->position().y - 0.5f, m_object->position().z),m_object->rotation_amount(),m_object->rotation_axis(), false);
}

void player::on_render(engine::ref<engine::shader> shader) {

	//render all 
	m_player_box.on_render(1.f,0.f,0.f, shader, false);
	glm::mat4 p_transform(1.0f);
	p_transform = glm::translate(p_transform, m_object->position());
	engine::renderer::submit(shader, m_object->meshes().at(0), p_transform);
}

void player::update_camera(engine::perspective_camera& camera)
{
	//update cam to object pos
	glm::vec3 cam_pos = m_object->position();
	camera.set_position(cam_pos);
}

void player::birdStop() {
	//save last speed for pause birdsview
	m_last_speed = m_speed;
	m_speed = 0;
}

void player::birdStart() {
	m_speed = m_last_speed;
}
