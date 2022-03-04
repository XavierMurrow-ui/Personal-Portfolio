#include "pch.h"
#include "enemy.h"

enemy::enemy() {}

enemy::~enemy() {}

void enemy::initialise(engine::ref<engine::game_object> object, glm::vec3 position, glm::vec3 forward)
{
	m_object = object;
	m_box.set_box(m_object->bounding_shape().x * m_object->scale().x, m_object->bounding_shape().y * m_object->scale().x, m_object->bounding_shape().z * m_object->scale().x, m_object->position(), false);
	m_object->set_forward(forward);
	m_object->set_position(position);

	m_object->set_velocity(glm::vec3(0.f));
	m_object->set_acceleration(glm::vec3(0.f));
	m_contact_time = 0.05f;

	glm::vec3 directVec = glm::normalize(m_object->forward());
	directVec.y += 1.f;
	glm::vec3 force = directVec * 5000.f;
	m_instantaneous_acceleration = force / m_object->mass();
}

void enemy::on_update(const engine::timestep& time_step, const glm::vec3& player_position, const glm::vec3& zombie_position)
{
	float distance_to_player = glm::distance(m_object->position(), player_position);
	m_box.on_update(m_object->position(),m_object->rotation_amount(),m_object->rotation_axis(), false);
	m_timer += time_step;
	// check which state is the enemy in, then execute the matching behaviour
	if (m_state == state::idle)
	{
		patrol(time_step, zombie_position);
		// check whether the condition has been met to switch to the on_guard state
		if (distance_to_player < m_detection_radius)
			m_state = state::jumping;
	}
	else if (m_state == state::jumping)
	{
		face_player(time_step, player_position);
		// check whether the condition has been met to switch back to idle state
		jumpToPlayer(time_step);
		if (distance_to_player > m_detection_radius)
			m_state = state::idle;
		// check whether the condition has been met to switch to the chasing state
		else if (distance_to_player < m_trigger_radius)
			m_state = state::chasing;
	}
	else if(m_state == state::chasing)
	{
		if (m_timer >= 0.5f) {
			chase_player(time_step, player_position);
			m_timer = 0.f;
		}
		// check whether the condition has been met to switch back to idle state
		if (distance_to_player > m_detection_radius)
			m_state = state::idle;
		else if (((int)m_health % 10 == 0 && m_health < 100)) {
			m_health -= 1.f;
			m_state = state::retreat;
		}
	}
	else {
		m_object->set_position(glm::vec3(20.f, 1.f, 35.f));
		m_state = state::idle;
	}
}

void enemy::on_render(const engine::ref<engine::shader> shader) {
	m_box.on_render(1.f,0.f,0.f, shader,false);
	glm::mat4 z_transform(1.f);
	z_transform = glm::translate(z_transform, m_object->position()); //- glm::vec3(m_object->offset().x, 0.f, m_object->offset().z) * m_object->scale().x);
	z_transform = glm::rotate(z_transform, m_object->rotation_amount(), m_object->rotation_axis());
	z_transform = glm::scale(z_transform, m_object->scale());
	engine::renderer::submit(shader, z_transform, m_object);
}

// move forwards until the timer runs out, then switch direction to move the other way
void enemy::patrol(const engine::timestep& time_step, const glm::vec3& zombie_position)
{
	float distance_to_zombie = glm::distance(m_object->position(), zombie_position);
	m_switch_direction_timer -= (float)time_step;
	if (m_switch_direction_timer < 0.f)
	{
		m_object->set_forward(m_object->forward() * -1.f);
		m_switch_direction_timer = m_default_time;
	}

	if (distance_to_zombie < m_zombie_trigger_radius)
		chase_player(time_step, zombie_position);

	m_object->set_position(m_object->position() + m_object->forward() * m_speed * (float)time_step);
	m_object->set_rotation_amount(atan2(m_object->forward().x, m_object->forward().z));
}

// stop and look at the player
void enemy::face_player(const engine::timestep& time_step, const glm::vec3&
	player_position)
{
	m_object->set_forward(player_position - m_object->position());
	m_object->set_rotation_amount(atan2(m_object->forward().x, m_object->forward().z));
}

// stop and look at the player
void enemy::face_away_player(const engine::timestep& time_step, const glm::vec3& player_position)
{
	m_object->set_forward(player_position + m_object->position());
	m_object->set_rotation_amount(atan2(m_object->forward().x, m_object->forward().z));
}

// move forwards in the direction of the player
void enemy::chase_player(const engine::timestep& time_step, const glm::vec3& player_position)
{
	m_object->set_forward(player_position - m_object->position());
	m_object->set_position(m_object->position() + m_object->forward() * m_speed * (float)time_step);
	m_object->set_rotation_amount(atan2(m_object->forward().x, m_object->forward().z));
}

void enemy::jumpToPlayer(const engine::timestep& time_step) {

	//Update acceleration to compensate for gravity
	m_object->set_acceleration(glm::vec3(0.f, -9.81f, 0.f));
	// Update physical quanitities
	m_last_position = m_object->position();
	m_object->set_velocity(m_object->velocity() + (m_object->acceleration() + m_instantaneous_acceleration) * (float)time_step);
	m_object->set_position(m_object->position() + m_object->velocity() * (float)time_step);

	// Turn off instantaneous forces if contact time is surpassed
	if (glm::length(m_instantaneous_acceleration) > 0 && m_contact_time > 0.05) {
		m_instantaneous_acceleration = glm::vec3(0.f);
		m_instantaneous_angular_acceleration = glm::vec3(0.f);
		m_contact_time = 0.f;
	}
	if (m_object->position().y <= 0.f) {
		m_state = state::chasing;
	}
	m_contact_time += time_step;
}
