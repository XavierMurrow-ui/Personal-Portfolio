#include "pch.h"
#include "diamond.h"
#include <engine.h>

engine::diamond::diamond(std::vector<glm::vec3> vertices) : m_vertices(vertices) {

	std::vector<glm::vec3> normals;

	// front normal
	normals.push_back(glm::cross(vertices.at(0) - vertices.at(1), vertices.at(0) - vertices.at(2)));
	// left normal
	normals.push_back(glm::cross(vertices.at(0) - vertices.at(2), vertices.at(0) - vertices.at(3)));
	// right normal
	normals.push_back(glm::cross(vertices.at(0) - vertices.at(3), vertices.at(0) - vertices.at(4)));

	normals.push_back(glm::cross(vertices.at(0) - vertices.at(4), vertices.at(0) - vertices.at(1)));

	//updown front normal
	normals.push_back(glm::cross(vertices.at(5) - vertices.at(1), vertices.at(5) - vertices.at(2)));
	//updown left normal
	normals.push_back(glm::cross(vertices.at(5) - vertices.at(2), vertices.at(5) - vertices.at(3)));
	//updown right normal
	normals.push_back(glm::cross(vertices.at(5) - vertices.at(3), vertices.at(5) - vertices.at(4)));

	normals.push_back(glm::cross(vertices.at(5) - vertices.at(4), vertices.at(5) - vertices.at(1)));

	std::vector<mesh::vertex> diamond_vertices{

		{ vertices.at(0),		normals.at(0),		{ 0.f,  0.f } },//0
		{ vertices.at(2),		normals.at(0),		{ 1.f,  0.f } },//1
		{ vertices.at(1),		normals.at(0),		{ 0.5f, 1.f } },//2

		{ vertices.at(0),		normals.at(1),		{ 0.f,  0.f } },//3
		{ vertices.at(3),		normals.at(1),		{ 1.f,  0.f } },//4
		{ vertices.at(2),		normals.at(1),		{ 0.5f, 1.f } },//5

		{ vertices.at(0),		normals.at(2),		{ 0.f,  0.f } },//9
		{ vertices.at(4),		normals.at(2),		{ 1.f,  0.f } },//10
		{ vertices.at(3),		normals.at(2),		{ 0.5f, 1.f } },//11

		{ vertices.at(0),		normals.at(3),		{ 0.f,  0.f } },//6
		{ vertices.at(1),		normals.at(3),		{ 1.f,  0.f } },//7
		{ vertices.at(4),		normals.at(3),		{ 0.5f, 1.f } },//8

		{ vertices.at(5),		normals.at(4),		{ 0.f,  0.f } },//12
		{ vertices.at(2),		normals.at(4),		{ 1.f,  0.f } },//13
		{ vertices.at(1),		normals.at(4),		{ 0.5f, 1.f } },//14

		{ vertices.at(5),		normals.at(5),		{ 0.f,  0.f } },//15
		{ vertices.at(3),		normals.at(5),		{ 1.f,  0.f } },//16
		{ vertices.at(2),		normals.at(5),		{ 0.5f, 1.f } },//17

		{ vertices.at(5),		normals.at(6),		{ 0.f,  0.f } },//21
		{ vertices.at(4),		normals.at(6),		{ 1.f,  0.f } },//22
		{ vertices.at(3),		normals.at(6),		{ 0.5f, 1.f } },//23

		{ vertices.at(5),		normals.at(7),		{ 0.f,  0.f } },//18
		{ vertices.at(1),		normals.at(7),		{ 1.f,  0.f } },//19
		{ vertices.at(4),		normals.at(7),		{ 0.5f, 1.f } },//20
	};

	std::vector<uint32_t> diamond_indices{
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		12, 14, 13,
		15, 17, 16,
		18, 20, 19,
		21, 23, 22
	};

	m_mesh = engine::mesh::create(diamond_vertices, diamond_indices);
}
engine::diamond::~diamond() {}

engine::ref<engine::diamond> engine::diamond::create(std::vector<glm::vec3> vertices) {
	return std::make_shared<engine::diamond>(vertices);
}
