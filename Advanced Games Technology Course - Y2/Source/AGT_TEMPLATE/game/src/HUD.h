#pragma once
#include <engine.h>

class quad;

class HUD
{

public:
	enum e_power {
		slow = 0,
		more,
		rock,
		t_slow,
		t_more,
		t_rock
	};

	HUD(const std::string& path, const std::string& path2, const std::string& path3);
	~HUD();

	void on_update(e_power power);
	void on_render(engine::ref<engine::shader> shader, glm::vec3 &pos1, glm::vec3& pos2, glm::vec3& pos3);

	static engine::ref<HUD> create(const std::string &path1, const std::string &path2, const std::string &path3);

private:

	engine::ref<engine::texture_2d> m_left_icon_tex;
	engine::ref<quad> m_left_icon_quad;
	float m_transparency_left = 0.1f;
	engine::ref<engine::texture_2d> m_mid_icon_tex;
	engine::ref<quad> m_mid_icon_quad;
	float m_transparency_mid = 0.1f;
	engine::ref<engine::texture_2d> m_right_icon_tex;
	engine::ref<quad> m_right_icon_quad;
	float m_transparency_right = 0.1f;
};
