#pragma once
#include <engine.h>

class birdView
{
public:
	birdView();
	~birdView();
	void on_update(glm::vec3& pPos);
	void camera_update(engine::perspective_camera& camera);
	bool view_on() { return m_view_on; };
	void set_view(const bool& viewNew) { m_view_on = viewNew; };

private:
	bool m_view_on = false;
	glm::vec3 playPos;
};
