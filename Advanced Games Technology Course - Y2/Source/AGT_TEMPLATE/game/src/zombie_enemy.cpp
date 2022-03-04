#include "pch.h"
#include "zombie_enemy.h"

zombie_enemy::zombie_enemy(engine::game_object_properties object, engine::ref<engine::model> zombie_model, glm::vec3& position, glm::vec3& forward) {
	m_object = engine::game_object::create(object);
	m_object->set_offset(zombie_model->offset());
	m_object->set_forward(forward);
	m_object->set_position(position);
	m_box.set_box(m_object->bounding_shape().x * m_object->scale().x, m_object->bounding_shape().y * m_object->scale().x, m_object->bounding_shape().z * m_object->scale().x, m_object->position(), false);
}

zombie_enemy::~zombie_enemy() {}

engine::ref<zombie_enemy> zombie_enemy::create(engine::game_object_properties props, engine::ref<engine::model> zombie_model, glm::vec3& position, glm::vec3& forward) {
	return std::make_shared<zombie_enemy>(props,zombie_model,position,forward);
}

void zombie_enemy::on_update(const engine::timestep& time_step, const glm::vec3& player_position, engine::bounding_box &p_box)
{
	float distance_to_player = glm::distance(m_object->position(), player_position);
	m_box.on_update(m_object->position(),m_object->rotation_amount(), m_object->rotation_axis(),false);
	// check which state is the enemy in, then execute the matching behaviour
	if (m_state == state::idle)
	{
		patrol(time_step);
		// check whether the condition has been met to switch to the on_guard state
		if (distance_to_player < m_detection_radius)
			m_state = state::on_guard;
	}
	else if (m_state == state::on_guard)
	{
		face_player(time_step, player_position);
		// check whether the condition has been met to switch back to idle state
		if (distance_to_player > m_detection_radius)
			m_state = state::idle;
		// check whether the condition has been met to switch to the chasing state
		else if (distance_to_player < m_trigger_radius)
			m_state = state::chasing;
	}
	else if(m_state == state::chasing)
	{
		chase_player(time_step, player_position);
		// check whether the condition has been met to switch back to idle state
		if (distance_to_player > m_detection_radius)
			m_state = state::idle;
		if (m_box.collision(p_box))
			m_state = state::attacking;
	}
	else {
		if (distance_to_player > m_detection_radius)
			m_state = state::idle;
	}
}

void zombie_enemy::on_render(const engine::ref<engine::shader>& shader) {
	m_box.on_render(1.f,0.f,0.f,shader, false);
	glm::mat4 z_transform(1.f);
	z_transform = glm::translate(z_transform, m_object->position());
	z_transform = glm::rotate(z_transform, m_object->rotation_amount(), m_object->rotation_axis());
	z_transform = glm::scale(z_transform, m_object->scale());
	engine::renderer::submit(shader, z_transform, m_object);
}

// move forwards until the timer runs out, then switch direction to move the other way

void zombie_enemy::patrol(const engine::timestep& time_step)
{
	m_switch_direction_timer -= (float)time_step;
	if (m_switch_direction_timer < 0.f)
	{
		m_object->set_forward(m_object->forward() * -1.f);
		m_switch_direction_timer = m_default_time;
	}

	m_object->set_position(glm::vec3(m_object->position().x, 0.5f,m_object->position().z) + m_object->forward() * m_speed * (float)time_step);
	m_object->set_rotation_amount(atan2(m_object->forward().x, m_object->forward().z));
}
// stop and look at the player
void zombie_enemy::face_player(const engine::timestep& time_step, const glm::vec3& player_position)
{
	m_object->set_forward(player_position - m_object->position());
	m_object->set_rotation_amount(atan2(m_object->forward().x, m_object->forward().z));
	m_object->set_position(glm::vec3(m_object->position().x, 0.5f, m_object->position().z));
}
// move forwards in the direction of the player
void zombie_enemy::chase_player(const engine::timestep& time_step, const glm::vec3& player_position)
{
	m_object->set_forward(player_position - m_object->position());
	m_object->set_position(glm::vec3(m_object->position().x, 0.5f, m_object->position().z) + m_object->forward() * m_speed *(float)time_step);
	m_object->set_rotation_amount(atan2(m_object->forward().x, m_object->forward().z));
}

void zombie_enemy::attacking(const engine::timestep& time_step, const glm::vec3& player_position) {
	//move zombie from player so they are not constantly colliding
	m_object->set_forward(player_position - m_object->position());
	m_object->set_position(glm::vec3(m_object->position().x, 0.5f, m_object->position().z) - (m_object->forward() * m_speed * (float)time_step));
}
