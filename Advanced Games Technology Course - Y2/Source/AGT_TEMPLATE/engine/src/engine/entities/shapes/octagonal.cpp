#include "pch.h"
#include "octagonal.h"
#include <engine.h>

engine::octagonal::octagonal(std::vector<glm::vec3> vertices) : m_vertices(vertices) {

	std::vector<glm::vec3> normals;
	// tri 1 top
	/*0*/normals.push_back(glm::cross(vertices.at(0) - vertices.at(1), vertices.at(0) - vertices.at(2)));

	//tri 1 square 1
	/*8*/normals.push_back(glm::cross(vertices.at(2) - vertices.at(1), vertices.at(2) - vertices.at(10)));

	//tri 1 square 2
	/*9*/normals.push_back(glm::cross(vertices.at(3) - vertices.at(2), vertices.at(3) - vertices.at(11)));

	//tri 1 square 3
	/*11*/normals.push_back(glm::cross(vertices.at(4) - vertices.at(3), vertices.at(4) - vertices.at(12)));

	//tri 1 square 4
	/*14*/normals.push_back(glm::cross(vertices.at(5) - vertices.at(4), vertices.at(5) - vertices.at(13)));

	//tri 1 square 5
	/*16*/normals.push_back(glm::cross(vertices.at(6) - vertices.at(5), vertices.at(6) - vertices.at(14)));

	//tri 1 square 6
	/*18*/normals.push_back(glm::cross(vertices.at(7) - vertices.at(6), vertices.at(7) - vertices.at(15)));

	//tri 1 square 7
	/*20*/normals.push_back(glm::cross(vertices.at(8) - vertices.at(7), vertices.at(8) - vertices.at(16)));

	//tri 1 square 8
	/*22*/normals.push_back(glm::cross(vertices.at(1) - vertices.at(8), vertices.at(8) - vertices.at(17)));

	// tri 1 bottom
	/*24*/normals.push_back(glm::cross(vertices.at(9) - vertices.at(10), vertices.at(9) - vertices.at(11)));

	//MIGHT NOT WOT
	std::vector<mesh::vertex> octagonal_vertices{
		//TOP
		//  position			normal			      tex coord       
		{ vertices.at(0),		normals.at(0),		{ 0.f,  0.f } },//0
		{ vertices.at(1),		normals.at(0),		{ 1.f,  0.f } },//1
		{ vertices.at(2),		normals.at(0),		{ 0.5f, 1.f } },//2

		{ vertices.at(3),		normals.at(0),		{ 0.f, 0.f } },//3
		{ vertices.at(4),		normals.at(0),		{ 1.f, 0.f } },//4
		{ vertices.at(5),		normals.at(0),		{ 0.5f, 1.f } },//5

		{ vertices.at(6),		normals.at(0),		{ 0.f, 0.f } },//6
		{ vertices.at(7),		normals.at(0),		{ 1.f, 0.f } },//7
		{ vertices.at(8),		normals.at(0),		{ 0.5f, 1.f } },//8
		//TOP

		//Square 1
		{ vertices.at(1),		normals.at(1),		{ 0.f,  0.f } },//9
		{ vertices.at(2),		normals.at(1),		{ 1.f,  0.f } },//10
		{ vertices.at(10),		normals.at(1),		{ 1.f, 1.f } },//11
		{ vertices.at(11),		normals.at(1),		{ 0.f,  1.f } },//12

		//Square 2
		{ vertices.at(2),		normals.at(2),		{ 0.f,  0.f } },//13
		{ vertices.at(3),		normals.at(2),		{ 1.f,  0.f } },//14
		{ vertices.at(11),		normals.at(2),		{ 1.f, 1.f } },//15
		{ vertices.at(12),		normals.at(2),		{ 0.f,  1.f } },//16

		//Square 3
		{ vertices.at(3),		normals.at(3),		{ 0.f,  0.f } },//17
		{ vertices.at(4),		normals.at(3),		{ 1.f,  0.f } },//18
		{ vertices.at(12),		normals.at(3),		{ 1.f, 1.f } },//19
		{ vertices.at(13),		normals.at(3),		{ 0.f,  1.f } },//20

		//Square 4
		{ vertices.at(4),		normals.at(4),		{ 0.f,  0.f } },//21
		{ vertices.at(5),		normals.at(4),		{ 1.f,  0.f } },//22
		{ vertices.at(13),		normals.at(4),		{ 1.f, 1.f } },//23
		{ vertices.at(14),		normals.at(4),		{ 0.f,  1.f } },//24

		//Square 5
		{ vertices.at(5),		normals.at(5),		{ 0.f,  0.f } },//25
		{ vertices.at(6),		normals.at(5),		{ 1.f,  0.f } },//26
		{ vertices.at(14),		normals.at(5),		{ 1.f, 1.f } },//27
		{ vertices.at(15),		normals.at(5),		{ 0.f,  1.f } },//28

		//Square 6
		{ vertices.at(6),		normals.at(6),		{ 0.f,  0.f } },//29
		{ vertices.at(7),		normals.at(6),		{ 1.f,  0.f } },//30
		{ vertices.at(15),		normals.at(6),		{ 1.f, 1.f } },//31
		{ vertices.at(16),		normals.at(6),		{ 0.f,  1.f } },//32

		//Square 7
		{ vertices.at(7),		normals.at(7),		{ 0.f,  0.f } },//33
		{ vertices.at(8),		normals.at(7),		{ 1.f,  0.f } },//34
		{ vertices.at(16),		normals.at(7),		{ 1.f, 1.f } },//35
		{ vertices.at(17),		normals.at(7),		{ 0.f,  1.f } },//36

		//Square 8
		{ vertices.at(8),		normals.at(8),		{ 0.f,  0.f } },//37
		{ vertices.at(1),		normals.at(8),		{ 1.f,  0.f } },//38
		{ vertices.at(17),		normals.at(8),		{ 1.f, 1.f } },//39
		{ vertices.at(10),		normals.at(8),		{ 0.f,  1.f } },//40

		//BOTTOM
		//left
		{ vertices.at(9),		normals.at(9),		{ 0.f,  0.f } },//41
		{ vertices.at(10),		normals.at(9),		{ 1.f,  0.f } },//42
		{ vertices.at(11),		normals.at(9),		{ 0.5f, 1.f } },//43

		{ vertices.at(12),		normals.at(9),		{ 0.f, 0.f } },//44
		{ vertices.at(13),		normals.at(9),		{ 1.f, 0.f } },//45
		{ vertices.at(14),		normals.at(9),		{ 0.5f, 1.f } },//46

		{ vertices.at(15),		normals.at(9),		{ 0.f, 0.f } },//47
		{ vertices.at(16),		normals.at(9),		{ 1.f, 0.f } },//48
		{ vertices.at(17),		normals.at(9),		{ 0.5f, 1.f } },//49
		//BOTTOM
	};

	std::vector<uint32_t> octagonal_indices{
		0, 2, 1,  0, 3, 2,  0, 4, 3,  0, 5, 4,  0, 6, 5,  0, 7, 6,  0, 8, 7,  0, 1, 8, //top
		9, 10, 12,  9, 12, 11, //s1
		13, 14, 16,  13, 16, 15, //s2
		17, 18, 20,  17, 20, 19, //s3
		21, 22, 24,  21, 24, 23, //s4
		25, 26, 28,  25, 28, 27, //s5
		29, 30, 32,  29, 32, 31, //s6
		33, 34, 36,  33, 36, 35, //s7
		37, 38, 40,  37, 40, 39, //s8
		41, 42, 43,  41, 43, 44,  41, 44, 45,  41, 45, 46,  41, 46, 47,  41, 47, 48,  41, 48, 49,  41, 49, 42 //bottom
	};

	m_mesh = engine::mesh::create(octagonal_vertices, octagonal_indices);
}

engine::octagonal::~octagonal() {}

engine::ref<engine::octagonal> engine::octagonal::create(std::vector<glm::vec3> vertices)
{
	return std::make_shared<engine::octagonal>(vertices);
}
