#include "pch.h"
#include "ballistic.h"

ballistic::ballistic(engine::game_object_properties object)
{
	m_object = engine::game_object::create(object);
	m_box.set_box(m_object->bounding_shape().x * m_object->scale().x, m_object->bounding_shape().y * m_object->scale().x, m_object->bounding_shape().z * m_object->scale().x, m_object->position(), false);
}

ballistic::~ballistic()
{}

engine::ref<ballistic> ballistic::create(engine::game_object_properties props) {
	return std::make_shared<ballistic>(props);
}

void ballistic::fire(glm::vec3& pos, glm::vec3& front, float speed){
	//shoot from correct place
	m_object->set_position(pos);
	m_object->set_forward(front);
	m_speed = speed;
}

void ballistic::on_update(const engine::timestep& time_step, glm::vec3& front)
{
	//update correctly
	m_object->set_position(m_object->position() + m_object->forward() * (float)time_step * m_speed);
	//m_object->set_forward(front);
	m_time_alive += (float)time_step;
	m_box.on_update(m_object->position(),m_object->rotation_amount(),m_object->rotation_axis(), false);
}

void ballistic::on_render(const engine::ref<engine::shader>& shader)
{
	//render
	engine::renderer::submit(shader, m_object);
	m_box.on_render(1.f,0.f,0.f,shader, false);
}
