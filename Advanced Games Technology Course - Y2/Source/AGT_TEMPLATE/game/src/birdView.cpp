#include <engine.h>
#include "pch.h"
#include "birdView.h"

birdView::birdView() {
	;
}

birdView::~birdView() {}

void birdView::on_update(glm::vec3& pPos) {
	m_view_on = true;
	playPos = pPos;
}

void birdView::camera_update(engine::perspective_camera& camera) {
	camera.set_view_matrix(playPos + glm::vec3(0.f,40.f,0.f),playPos + (glm::vec3(0.f,-1.f,0.f)));
	//camera.set_view_matrix(playPos + glm::vec3(0.f,0.f,10.f), playPos + glm::vec3(0.f,0.f,-1.f));
}
