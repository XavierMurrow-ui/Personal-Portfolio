#include "pch.h"
#include "HUD.h"
#include "quad.h"

HUD::HUD(const std::string& path1, const std::string& path2, const std::string& path3) {

	//declare for each powerup render
	m_left_icon_tex = engine::texture_2d::create(path1,true);
	m_left_icon_quad = quad::create(glm::vec2(0.2f,0.15f));

	m_mid_icon_tex = engine::texture_2d::create(path2, true);
	m_mid_icon_quad = quad::create(glm::vec2(0.3f, 0.15f));

	m_right_icon_tex = engine::texture_2d::create(path3, true);
	m_right_icon_quad = quad::create(glm::vec2(0.2f, 0.15f));
}

HUD::~HUD() {}

void HUD::on_update(e_power power) {

	//to deal with transparency
	if (power == slow) m_transparency_left = 1.f;
	else if (power == more) m_transparency_mid = 1.f;
	else if (power == rock) m_transparency_right = 1.f;
	else if (power == t_slow) m_transparency_left = 0.1f;
	else if (power == t_more) m_transparency_mid = 0.1f;
	else if (power == t_rock) m_transparency_right = 0.1f;
}

void HUD::on_render(engine::ref<engine::shader> shader, glm::vec3 &pos1,  glm::vec3& pos2, glm::vec3& pos3) {
	//rendering
	glm::mat4 left_transform(1.f);
	left_transform = glm::translate(left_transform,pos1);
	std::dynamic_pointer_cast<engine::gl_shader>(shader)->set_uniform("transparency", m_transparency_left);
	std::dynamic_pointer_cast<engine::gl_shader>(shader)->set_uniform("has_texture", true);
	m_left_icon_tex->bind();
	engine::renderer::submit(shader,m_left_icon_quad->mesh(),left_transform);

	glm::mat4 mid_transform(1.f);
	mid_transform = glm::translate(mid_transform, pos2);
	std::dynamic_pointer_cast<engine::gl_shader>(shader)->set_uniform("transparency", m_transparency_mid);
	std::dynamic_pointer_cast<engine::gl_shader>(shader)->set_uniform("has_texture", true);
	m_mid_icon_tex->bind();
	engine::renderer::submit(shader, m_mid_icon_quad->mesh(), mid_transform);

	glm::mat4 right_transform(1.f);
	right_transform = glm::translate(right_transform, pos3);
	std::dynamic_pointer_cast<engine::gl_shader>(shader)->set_uniform("transparency", m_transparency_right);
	std::dynamic_pointer_cast<engine::gl_shader>(shader)->set_uniform("has_texture", true);
	m_right_icon_tex->bind();
	engine::renderer::submit(shader, m_right_icon_quad->mesh(), right_transform);

	std::dynamic_pointer_cast<engine::gl_shader>(shader)->set_uniform("transparency", 1.f);
}

engine::ref<HUD> HUD::create(const std::string& path1, const std::string& path2, const std::string& path3) {
	return std::make_shared<HUD>(path1,path2,path3);
}
