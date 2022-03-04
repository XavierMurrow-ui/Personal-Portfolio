#include "pickup.h"

pickup::pickup(){}

pickup::~pickup() {}

void pickup::init(const engine::game_object_properties &props, const engine::game_object_properties text, pick pow) {

//create each object and bounding box for each powerup type
	if (pow == pick::slow) {
		m_slow_object = engine::game_object::create(props);
		m_slow_box.set_box(1.f, 1.f, 1.f, m_slow_object->position(), true);
	}
	else if (pow == pick::damage) {
		m_dam_object = engine::game_object::create(props);
		m_dam_box.set_box(1.f, 1.f, 1.f, m_dam_object->position(), true);
	}
	else {
		m_rock_object = engine::game_object::create(props);
		m_rock_box.set_box(1.f, 1.f, 1.f, m_rock_object->position(), true);
	}
}

void pickup::update(const engine::timestep& time_step, pick pow)
{
	//update for each type of type
	if (pow == pick::slow) {
		m_slow_box.on_update(m_slow_object->position(),m_slow_object->rotation_amount(),m_slow_object->rotation_axis(),true);
	}
	else if (pow == pick::damage) {
		m_dam_box.on_update(m_dam_object->position(), m_dam_object->rotation_amount(), m_dam_object->rotation_axis(), true);
	}
	else {
		m_rock_box.on_update(m_rock_object->position(), m_rock_object->rotation_amount(), m_rock_object->rotation_axis(), true);
	}
}

void pickup::on_render(const engine::ref<engine::shader> shader, pick pow) {
	//render for each type
	if (pow == pick::slow) {
		m_slow_box.on_render(1.f,0.f,0.f,shader,true);

		glm::mat4 dia_transform(1.f);
		dia_transform = glm::translate(dia_transform, glm::vec3(glm::vec3(m_slow_object->position().x, m_slow_object->position().y, m_slow_object->position().z)));
		dia_transform = glm::rotate(dia_transform, m_slow_object->rotation_amount(), glm::vec3(0.f, 1.f, 0.f));//So each render also rotates around the y axis
		dia_transform = glm::scale(dia_transform, m_slow_object->scale());
		engine::renderer::submit(shader, dia_transform, m_slow_object);
	}
	else if (pow == pick::damage) {
		m_dam_box.on_render(1.f, 0.f, 0.f, shader, true);

		glm::mat4 dia_transform(1.f);
		dia_transform = glm::translate(dia_transform, glm::vec3(glm::vec3(m_dam_object->position().x, m_dam_object->position().y, m_dam_object->position().z)));
		dia_transform = glm::rotate(dia_transform, m_dam_object->rotation_amount(), glm::vec3(0.f, 1.f, 0.f));//So each render also rotates around the y axis
		dia_transform = glm::scale(dia_transform, m_dam_object->scale());
		engine::renderer::submit(shader, dia_transform, m_dam_object);
	}
	else if (pow == pick::rock){
		m_rock_box.on_render(1.f, 0.f, 0.f, shader, true);

		glm::mat4 dia_transform(1.f);
		dia_transform = glm::translate(dia_transform, glm::vec3(glm::vec3(m_rock_object->position().x, m_rock_object->position().y, m_rock_object->position().z)));
		dia_transform = glm::rotate(dia_transform, m_rock_object->rotation_amount(), glm::vec3(0.f, 1.f, 0.f));//So each render also rotates around the y axis
		dia_transform = glm::scale(dia_transform, m_rock_object->scale());
		engine::renderer::submit(shader, dia_transform, m_rock_object);
	}
}
