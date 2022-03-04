#include "pch.h"
#include "tetrahedron.h"
#include <engine.h>		

engine::tetrahedron::tetrahedron(std::vector<glm::vec3> vertices) : m_vertices(vertices)
{
	std::vector<glm::vec3> normals;
	// front normal
	normals.push_back(glm::cross(vertices.at(0) - vertices.at(2), vertices.at(0) - vertices.at(1)));
	// left normal
	normals.push_back(glm::cross(vertices.at(0) - vertices.at(3), vertices.at(0) - vertices.at(2)));
	// right normal
	normals.push_back(glm::cross(vertices.at(0) - vertices.at(1), vertices.at(0) - vertices.at(3)));
	//updown front normal
	normals.push_back(glm::cross(vertices.at(4) - vertices.at(2), vertices.at(4) - vertices.at(1)));
	//updown left normal
	normals.push_back(glm::cross(vertices.at(4) - vertices.at(3), vertices.at(4) - vertices.at(2)));
	//updown right normal
	normals.push_back(glm::cross(vertices.at(4) - vertices.at(1), vertices.at(4) - vertices.at(3)));

	std::vector<mesh::vertex> tetrahedron_vertices
	{
		//front
		//  position			normal			      tex coord       
		{ vertices.at(0),		normals.at(0),		{ 0.f,  0.f } },
		{ vertices.at(2),		normals.at(0),		{ 1.f,  0.f } },
		{ vertices.at(1),		normals.at(0),		{ 0.5f, 1.f } },

		//left
		{ vertices.at(0),		normals.at(1),		{ 0.f,  0.f } },
		{ vertices.at(3),		normals.at(1),		{ 1.f,  0.f } },
		{ vertices.at(2),		normals.at(1),		{ 0.5f, 1.f } },

		//right
		{ vertices.at(0),		normals.at(2),		{ 0.f,  0.f } },
		{ vertices.at(1),		normals.at(2),		{ 1.f,  0.f } },
		{ vertices.at(3),		normals.at(2),		{ 0.5f, 1.f } },

		//updown front
		{ vertices.at(4),		normals.at(4),		{ 0.f,  0.f } },
		{ vertices.at(2),		normals.at(4),		{ 1.f,  0.f } },
		{ vertices.at(1),		normals.at(4),		{ 0.5f, 1.f } },

		//updown left
		{ vertices.at(4),		normals.at(5),		{ 0.f,  0.f } },
		{ vertices.at(3),		normals.at(5),		{ 1.f,  0.f } },
		{ vertices.at(2),		normals.at(5),		{ 0.5f, 1.f } },

		//updown right
		{ vertices.at(4),		normals.at(3),		{ 0.f,  0.f } },
		{ vertices.at(1),		normals.at(3),		{ 1.f,  0.f } },
		{ vertices.at(3),		normals.at(3),		{ 0.5f, 1.f } },
	};

	const std::vector<uint32_t> tetrahedron_indices
	{
		0,  1,  2,	//front
		3,  4,  5,	//left
		6,	7,	8,	//Right
		9, 11, 10,  //updown front
		12, 14, 13, //updown left
		15, 17, 16	//updown right
	};

	m_mesh = engine::mesh::create(tetrahedron_vertices, tetrahedron_indices);
}

engine::tetrahedron::~tetrahedron() {}

engine::ref<engine::tetrahedron> engine::tetrahedron::create(std::vector<glm::vec3> vertices)
{
	return std::make_shared<engine::tetrahedron>(vertices);
}
