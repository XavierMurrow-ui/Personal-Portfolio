#include "example_layer.h"
#include "platform/opengl/gl_shader.h"

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include "engine/events/key_event.h"
#include "engine/utils/track.h"
#include "pickup.h"
#include <engine/entities/shapes/diamond.h>

example_layer::example_layer() 
    :m_2d_camera(-1.6f, 1.6f, -0.9f, 0.9f), 
    m_3d_camera((float)engine::application::window().width(), (float)engine::application::window().height())
{

	// Initialise audio and play background music
	m_audio_manager = engine::audio_manager::instance();
	m_audio_manager->init();
	m_audio_manager->load_sound("assets/audio/menu.wav", engine::sound_type::track, "menu music");  // Royalty free sound from freesound.org
	m_audio_manager->load_sound("assets/audio/game_music.wav", engine::sound_type::track, "game music");  // Royalty free sound from freesound.org
	m_audio_manager->load_sound("assets/audio/rock_music.mp3", engine::sound_type::track, "rock music");  // Royalty free sound from freesound.org
	m_audio_manager->load_sound("assets/audio/shotgun.mp3", engine::sound_type::spatialised, "shotgun"); // Royalty free sound from freesound.org
	m_audio_manager->load_sound("assets/audio/reload.wav", engine::sound_type::spatialised, "reload"); // Royalty free sound from freesound.org
	m_audio_manager->load_sound("assets/audio/Shrek.mp3", engine::sound_type::spatialised, "shrek"); // Royalty free sound from freesound.org
	m_audio_manager->play("menu music");

	// Initialise the shaders, materials and lights
	auto mesh_shader = engine::renderer::shaders_library()->get("mesh");
	auto text_shader = engine::renderer::shaders_library()->get("text_2D");

	engine::ref<engine::cuboid> player_shape = engine::cuboid::create(glm::vec3(0.1f, 0.5f, 0.1f), false);
	engine::game_object_properties player_props;
	player_props.position = { 5.f, 0.f, 5.f };
	player_props.meshes = { player_shape->mesh() };
	m_player.initialise(engine::game_object::create(player_props), m_3d_camera);

	m_directionalLight.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	m_directionalLight.AmbientIntensity = 0.01f;
	m_directionalLight.DiffuseIntensity = 0.01f;
	m_directionalLight.Direction = glm::normalize(glm::vec3(0.0f, -1.0f, -0.2f));

	m_pointLight.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	m_pointLight.AmbientIntensity = 0.25f;
	m_pointLight.DiffuseIntensity = 0.6f;

	m_touchLight.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	m_touchLight.AmbientIntensity = 0.15f;
	m_touchLight.DiffuseIntensity = 0.05f;
	m_touchLight.Cutoff = 0.002f;
	m_touchLight.Attenuation.Constant = 1.0f;
	m_touchLight.Attenuation.Linear = 0.01f;
	m_touchLight.Attenuation.Exp = 0.01f;

	// set color texture unit
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->bind();
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("lighting_on", true);
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gColorMap", 0);
	m_directionalLight.submit(mesh_shader);
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gMatSpecularIntensity", 1.f);
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gSpecularPower", 10.f);
	std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("transparency", 1.0f);

	std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->bind();
	std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->set_uniform("projection",
		glm::ortho(0.f, (float)engine::application::window().width(), 0.f,
		(float)engine::application::window().height()));
	m_material = engine::material::create(1.0f, glm::vec3(1.0f, 0.1f, 0.07f),
		glm::vec3(1.0f, 0.1f, 0.07f), glm::vec3(0.5f, 0.5f, 0.5f), 1.0f);

	m_lightsource_material = engine::material::create(1.0f, m_pointLight.Color,
		m_pointLight.Color, m_pointLight.Color, 1.0f);

	m_mannequin_material = engine::material::create(1.0f, glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 1.0f);

	m_ballistic_material = engine::material::create(1.f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 1.0f);

	m_octagonal_material = engine::material::create(1.f, glm::vec3(1.f,0.f,0.f),glm::vec3(1.f,0.f,0.f),glm::vec3(0.5f,0.5f,0.5f),1.f);

	// Skybox texture from https://opengameart.org/content/rusted-metal-texture-pack
	m_skybox = engine::skybox::create(50.f,
		{ engine::texture_2d::create("assets/textures/skybox/posz.jpg", true),
		  engine::texture_2d::create("assets/textures/skybox/posx.jpg", true),
		  engine::texture_2d::create("assets/textures/skybox/negz.jpg", true),
		  engine::texture_2d::create("assets/textures/skybox/negx.jpg", true),
		  engine::texture_2d::create("assets/textures/skybox/posy.jpg", true),
		  engine::texture_2d::create("assets/textures/skybox/negy.jpg", true)
		});

	engine::ref<engine::model> shrek_model = engine::model::create("assets/models/animated/ShrekTex/ShrekTpose.dae");
	engine::game_object_properties shrek_props{};
	shrek_props.meshes = shrek_model->meshes();
	shrek_props.textures = shrek_model->textures();
	shrek_props.position = glm::vec3(4.f, 1.f, 0.f);
	float shrek_scale = 1.f / glm::max(shrek_model->size().x, glm::max(shrek_model->size().y, shrek_model->size().z));
	shrek_props.scale = glm::vec3(shrek_scale);
	shrek_props.mass = 1.f;
	shrek_props.bounding_shape = shrek_model->size();
	m_shrek = engine::game_object::create(shrek_props);
	m_enemy.initialise(m_shrek,glm::vec3(20.f,1.f,35.f),glm::vec3(0.f,0.f,-1.f));

	// Load the terrain texture and create a terrain mesh. Create a terrain object. Set its properties
	std::vector<engine::ref<engine::texture_2d>> terrain_textures = { engine::texture_2d::create("assets/textures/grass.png", false) };//Same terrain code, different image
	engine::ref<engine::terrain> terrain_shape = engine::terrain::create(100.f, 0.5f, 100.f);
	engine::game_object_properties terrain_props;
	terrain_props.meshes = { terrain_shape->mesh() };
	terrain_props.textures = terrain_textures;
	terrain_props.is_static = true;
	terrain_props.type = 0;
	terrain_props.bounding_shape = glm::vec3(100.f, 0.5f, 100.f);
	terrain_props.restitution = 0.92f;
	m_terrain = engine::game_object::create(terrain_props);

	//load the road model, Create a road object, Set its properties
	engine::ref<engine::model> road_model = engine::model::create("assets/models/static/road-straight-house-2-low.obj");
	engine::game_object_properties road_props;
	road_props.meshes = road_model->meshes();
	road_props.textures = road_model->textures();
	m_road = engine::game_object::create(road_props);

	//load the road model, Create a road object, Set its properties
	engine::ref<engine::model> road2_model = engine::model::create("assets/models/static/singleturnroad.obj");
	engine::game_object_properties road2_props;
	road2_props.meshes = road2_model->meshes();
	road2_props.textures = road2_model->textures();
	m_road_turn = engine::game_object::create(road2_props);

	//load the house model, Create a road object, Set its properties
	engine::ref<engine::model> house_model = engine::model::create("assets/models/static/house-small-garage.obj");
	engine::game_object_properties house_props;
	house_props.meshes = house_model->meshes();
	house_props.textures = house_model->textures();
	house_props.position = { 7.f, -0.0115f - 0.499f, -35.f };
	float house_scale = 1.f / glm::max(house_model->size().x, glm::max(house_model->size().y, house_model->size().z)); ;
	house_props.scale = glm::vec3(house_scale);
	house_props.bounding_shape = house_model->size();
	m_house = engine::game_object::create(house_props);

	m_house->set_offset(house_model->offset());

	//load the second house model, Create a road object, Set its properties
	engine::ref<engine::model> house2_model = engine::model::create("assets/models/static/house-modern.obj");
	engine::game_object_properties house2_props;
	house2_props.meshes = house2_model->meshes();
	house2_props.textures = house2_model->textures();
	house2_props.position = { -8.4f, -1.7001f - 0.499f, -35.f };
	float house2_scale = 1.f / glm::max(house2_model->size().x, glm::max(house2_model->size().y,house2_model->size().z)); ;
	house2_props.scale = glm::vec3(house2_scale);
	house2_props.bounding_shape = house2_model->size();
	m_house2 = engine::game_object::create(house2_props);

	m_house2->set_offset(house2_model->offset());

	//load the road model, Create a road object, Set its properties
	engine::ref<engine::model> gun_model = engine::model::create("assets/models/static/shotgun.obj");
	engine::game_object_properties gun_props{};
	gun_props.meshes = gun_model->meshes();
	gun_props.textures = gun_model->textures();
	float gun_scale = 3.f / glm::max(gun_model->size().x, glm::max(gun_model->size().y, gun_model->size().z));
	gun_scale /= 3.f;
	gun_props.scale = glm::vec3(gun_scale);
	gun_props.rotation_amount = AI_DEG_TO_RAD(180);
	m_gun = engine::game_object::create(gun_props);

	//load the second house model, Create a road object, Set its properties
	engine::ref<engine::model> zombie_model = engine::model::create("assets/models/static/zombie.obj");
	engine::game_object_properties zombie_props{};
	zombie_props.meshes = zombie_model->meshes();
	zombie_props.textures = zombie_model->textures();
	zombie_props.position = glm::vec3(4.f, 0.5f, 0.f);
	float zom_scale = 1.f / glm::max(zombie_model->size().x, glm::max(zombie_model->size().y, zombie_model->size().z)); ;
	zombie_props.scale = glm::vec3(zom_scale);
	zombie_props.bounding_shape = zombie_model->size();

	//PUSH BACK FOR ZOMBIES WITH DIFFERING POSITIONS INTO ZOMBIES VECTOR//
	for (int i = 0; i < 10; ++i) {
		if (i <= 1) {
			if (i % 2 == 0) {
				
				engine::ref<zombie_enemy> m_enemy = zombie_enemy::create(zombie_props, zombie_model,glm::vec3(4.f, 0.5f, -35.f), glm::vec3(-1.f, 0.f, 0.f));
				m_zombies.push_back(m_enemy);
			}
			else {
				
				engine::ref<zombie_enemy> m_enemy = zombie_enemy::create(zombie_props, zombie_model, glm::vec3(-4.f, 0.5f, -35.f), glm::vec3(1.f, 0.f, 0.f));
				m_zombies.push_back(m_enemy);
			}
		}
		else if (i <= 3) {
			if (i % 2 == 0) {
				
				engine::ref<zombie_enemy> m_enemy = zombie_enemy::create(zombie_props, zombie_model, glm::vec3(4.f, 0.5f, -21.f), glm::vec3(-1.f, 0.f, 0.f));
				m_zombies.push_back(m_enemy);
			}
			else {
				
				engine::ref<zombie_enemy> m_enemy = zombie_enemy::create(zombie_props, zombie_model, glm::vec3(-4.f, 0.5f, -21.f), glm::vec3(1.f, 0.f, 0.f));
				m_zombies.push_back(m_enemy);
			}
		}
		else if (i <= 5) {
			if (i % 2 == 0) {
				
				engine::ref<zombie_enemy> m_enemy = zombie_enemy::create(zombie_props, zombie_model, glm::vec3(24.f, 0.5f, 14.f), glm::vec3(-1.f, 0.f, 0.f));
				m_zombies.push_back(m_enemy);
			}
			else {
				
				engine::ref<zombie_enemy> m_enemy = zombie_enemy::create(zombie_props, zombie_model, glm::vec3(16.f, 0.5f, 14.f), glm::vec3(1.f, 0.f, 0.f));
				m_zombies.push_back(m_enemy);
			}
		}
		else if (i <= 7) {
			if (i % 2 == 0) {
				
				engine::ref<zombie_enemy> m_enemy = zombie_enemy::create(zombie_props, zombie_model, glm::vec3(24.f, 0.5f, 21.f), glm::vec3(-1.f, 0.f, 0.f));
				m_zombies.push_back(m_enemy);
			}
			else {
				
				engine::ref<zombie_enemy> m_enemy = zombie_enemy::create(zombie_props, zombie_model, glm::vec3(16.f, 0.5f, 21.f), glm::vec3(1.f, 0.f, 0.f));
				m_zombies.push_back(m_enemy);
			}
		}
	}

	//Setting all the vertices for the diamond made from two tetrahedrons
	std::vector<glm::vec3> tetrahedron_vertices;
	tetrahedron_vertices.push_back(glm::vec3(0.f, 10.f, 0.f));	//0
	tetrahedron_vertices.push_back(glm::vec3(0.f, 0.f, 10.f));	//1
	tetrahedron_vertices.push_back(glm::vec3(-10.f, 0.f, -10.f));	//2
	tetrahedron_vertices.push_back(glm::vec3(10.f, 0.f, -10.f));	//3
	tetrahedron_vertices.push_back(glm::vec3(0.f, -10.f, 0.f));	//4

	std::vector<glm::vec3> octagonal_vertices;
	octagonal_vertices.push_back(glm::vec3(0.f,25.f,0.f));	//0
	octagonal_vertices.push_back(glm::vec3(1.f,25.f,-3.f));	//1
	octagonal_vertices.push_back(glm::vec3(3.f,25.f,-1.f));	//2
	octagonal_vertices.push_back(glm::vec3(3.f,25.f,1.f));	//3
	octagonal_vertices.push_back(glm::vec3(1.f,25.f,3.f));	//4
	octagonal_vertices.push_back(glm::vec3(-1.f,25.f,3.f));	//5
	octagonal_vertices.push_back(glm::vec3(-3.f,25.f,1.f));	//6
	octagonal_vertices.push_back(glm::vec3(-3.f,25.f,-1.f));	//7
	octagonal_vertices.push_back(glm::vec3(-1.f,25.f,-3.f));	//8

	octagonal_vertices.push_back(glm::vec3(0.f, 0.f, 0.f));//9
	octagonal_vertices.push_back(glm::vec3(1.f, 0.f, -3.f));//10
	octagonal_vertices.push_back(glm::vec3(3.f, 0.f, -1.f));//11
	octagonal_vertices.push_back(glm::vec3(3.f, 0.f, 1.f));//12
	octagonal_vertices.push_back(glm::vec3(1.f, 0.f, 3.f));//13
	octagonal_vertices.push_back(glm::vec3(-1.f, 0.f, 3.f));//14
	octagonal_vertices.push_back(glm::vec3(-3.f, 0.f, 1.f));//15
	octagonal_vertices.push_back(glm::vec3(-3.f, 0.f, -1.f));//16
	octagonal_vertices.push_back(glm::vec3(-1.f, 0.f, -3.f));//17

	std::vector<glm::vec3> diamond_vertices;
	diamond_vertices.push_back(glm::vec3(0.f, 10.f, 0.f));	//0
	diamond_vertices.push_back(glm::vec3(10.f, 0.f, -10.f));	//1
	diamond_vertices.push_back(glm::vec3(10.f, 0.f, 10.f));	//2
	diamond_vertices.push_back(glm::vec3(-10.f, 0.f, 10.f));	//3
	diamond_vertices.push_back(glm::vec3(-10.f, 0.f, -10.f));	//4
	diamond_vertices.push_back(glm::vec3(0.f, -10.f, 0.f));	//5

	//text for powerups
	engine::ref<engine::cuboid> text_shape = engine::cuboid::create(glm::vec3(0.7f, 0.5f, 0.001f), false);
	engine::ref<engine::texture_2d> text_texture = engine::texture_2d::create("assets/textures/pickUpText.png", false);
	engine::game_object_properties text_props;
	text_props.meshes = { text_shape->mesh() };
	text_props.textures = { text_texture };

	//slow down movement powerup setup
	engine::ref<engine::tetrahedron> tetrahedron_shape = engine::tetrahedron::create(tetrahedron_vertices);
	engine::game_object_properties tetrahedron_props;
	std::vector<engine::ref<engine::texture_2d>> tetrahedron_textures = { engine::texture_2d::create("assets/textures/lava.png", false) };
	tetrahedron_props.position = { 0.f, 1.f, -35.f };
	tetrahedron_props.meshes = { tetrahedron_shape->mesh() };
	tetrahedron_props.scale /= 20.f;
	tetrahedron_props.textures = tetrahedron_textures;
	

	//Defining primitive game object shape and properties
	engine::ref<engine::octagonal> octagonal_shape = engine::octagonal::create(octagonal_vertices);
	engine::game_object_properties octagonal_props;
	octagonal_props.position = { 2.5f, 3.f, 10.f };
	octagonal_props.meshes = { octagonal_shape->mesh() };
	octagonal_props.scale /= 100.f;
	octagonal_props.rotation_amount = AI_DEG_TO_RAD(90);
	m_octagonal = engine::game_object::create(octagonal_props);
	pickup dam;
	m_pick.push_back(dam);
	m_pick.at(0).init(tetrahedron_props, text_props, pickup::pick::damage);

	//damage powerup setup
	engine::ref<engine::diamond> diamond_shape = engine::diamond::create(diamond_vertices);
	engine::game_object_properties diamond_props;
	std::vector<engine::ref<engine::texture_2d>> diamond_textures = { engine::texture_2d::create("assets/textures/lava.png", false) };
	diamond_props.position = { 0.f, 1.f, -15.f };
	diamond_props.meshes = { diamond_shape->mesh() };
	diamond_props.scale /= 20.f;
	diamond_props.textures = diamond_textures;
	pickup slow;
	m_pick.push_back(slow);
	m_pick.at(1).init(diamond_props, text_props, pickup::pick::slow);

	engine::ref<engine::sphere> sphere_shape = engine::sphere::create(20, 40, 0.5f);
	m_sphere_props.meshes = { sphere_shape->mesh() };
	m_sphere_props.type = 1;
	m_sphere_props.bounding_shape = glm::vec3(0.5f);
	m_sphere_props.restitution = 0.92f;
	m_sphere_props.mass = 0.000001f;
	float sphere_scale = 0.08f;
	m_sphere_props.scale = glm::vec3(sphere_scale);
	m_sphere_props.bounding_shape = glm::vec3(sphere_shape->radius());

	//rock powerup setup
	engine::ref<engine::sphere> ball_shape = engine::sphere::create(10, 20, 0.35f);
	engine::game_object_properties ball_props;
	ball_props.position = { 0.f, 1.f, 5.f };
	ball_props.meshes = { ball_shape->mesh() };
	ball_props.type = 1;
	ball_props.bounding_shape = glm::vec3(0.35f);
	pickup rock;
	m_pick.push_back(rock);
	m_pick.at(2).init(ball_props, text_props, pickup::pick::rock);

	m_game_objects.push_back(m_terrain);
	m_physics_manager = engine::bullet_manager::create(m_game_objects);

	m_text_manager = engine::text_manager::create();

	m_cross_fade = cross_fade::create("assets/textures/Red.bmp", 2.0f, 1.6f, 0.9f);
	m_HUD = HUD::create("assets/textures/slowdownWhite.png","assets/textures/moredamageWhite.png","assets/textures/rockmusicWhite.png");
}

example_layer::~example_layer() {}

void example_layer::on_update(const engine::timestep& time_step)
{
	glm::vec3 pos = m_player.object()->position();//local varible for player position
	if (m_start_game && !m_birdview.view_on()) {// if statement for updating most rendering assets if the birdview cam is not in use
		m_timer += time_step;// timer used for the skybox disappearing
		m_fire_rate += time_step;//timer used for the fire rate of the gun
		m_game_timer -= time_step;
		m_3d_camera.on_update(time_step);//updating camera
		m_player.on_update(time_step, m_3d_camera);//updating player
		m_player.update_camera(m_3d_camera);//updating the camera when attached to the player
		for (int i = 0; i < m_zombies.size(); ++i) {//zombies are really annoying 1st loop for update and collisions
			m_zombies.at(i)->on_update(time_step, pos, m_player.p_box());//update of zombies
			m_enemy.on_update(time_step, pos, m_zombies.at(i)->object()->position());//update of enemy as he can destroy random zombies
			if (m_zombies.at(i)->box().collision(m_player.p_box())) {//collision testing for zombies
				m_player.object()->set_position(glm::vec3(pos.x, pos.y, pos.z) - (m_player.object()->forward() * 5.f * (float)time_step));//pushing player back after attack
				m_zombies.at(i)->object()->set_position(m_zombies.at(i)->object()->position() + (m_3d_camera.front_vector() * 5.f * (float)time_step));//doing same for zombie
				m_player.up_health(m_player.Health() - 1);//reducing player health
				m_cross_fade->activate();//cross fade to show damage was taken
			}
		}
		for (int i = 1; i < m_zombies.size(); ++i) {//2nd loop, peer collisions
			if (m_zombies.at(i - 1)->box().collision(m_zombies.at(i)->box())) {//tests if the preivous and current zombie collided
				m_zombies.at(i - 1)->object()->set_position(m_zombies.at(i - 1)->object()->position());//resetting position
				m_zombies.at(i)->object()->set_position(m_zombies.at(i)->object()->position());//resetting position
			}
		}
		if (m_player.p_box().collision(m_enemy.box())){//enemy player collision testing
			m_player.object()->set_position(pos - (m_3d_camera.front_vector() * 10.f * (float)time_step));//pushes player back
			m_enemy.object()->set_position(m_enemy.object()->position() - m_enemy.object()->forward() * 5.f * (float)time_step);//also pushes enemy back
			m_player.up_health(m_player.Health() - 10);//reducing player health
			m_player.up_speed(m_player.Speed() + 0.001f);//increase speed for doing damage
			m_cross_fade->activate();//cross fade to show damage was taken
		}
		m_cross_fade->on_update(time_step);// updating fade
		m_touchLight.Direction = glm::normalize(m_3d_camera.front_vector());//updating touch light
		for (int i = 0; i < m_house2_box.size(); ++i) {//house collisions
			if (m_house_box.at(i).collision(m_player.p_box()) || m_house2_box.at(i).collision(m_player.p_box()))//testing if either house is collided with
				m_player.object()->set_position(pos);//resetting player pos
		}
		for (int i = 0; i < m_bullets.size(); ++i) {//bullets
			m_bullets.at(i)->on_update(time_step, glm::normalize(glm::vec3(m_3d_camera.front_vector().x + (i * 0.008f), m_3d_camera.front_vector().y, m_3d_camera.front_vector().z)));//bullets update
			if (m_enemy.box().collision(m_bullets.at(i)->bull_box()))
				m_enemy.set_health(m_enemy.health() - m_player.sDam());
			if (!m_zombies.empty()) {//don't think I need this anymore, if its here still I'm sorry. Doesn't affect anything
				for (int j = 0; j < m_zombies.size(); ++j) {//nested for loop for zombie killing
					if (m_zombies.at(j)->box().collision(m_bullets.at(i)->bull_box()) && m_zombies.at(j)->health() > 0.f) {//testing bullet zombie collision
						m_zombies.at(j)->set_health(m_zombies.at(j)->health() - m_player.Dam());//reducing zombie health
					}
					else if (m_zombies.at(j)->health() <= 0.f) {//testing for zombie health
						m_zombies.erase(m_zombies.begin() + j);//if 0, erase from vector
						m_player.up_speed(m_player.Speed() + 0.001f);
					}
				}
			}
			if (m_bullets.at(i)->time_alive() >= 0.5f)//how long bullets last, 0.5f
				m_bullets.erase(m_bullets.begin() + i);//erase from vector if 0.5f seconds as past
		}
		if (!m_pick.empty()) {
			m_pick.at(0).update(time_step, pickup::pick::damage);//update pickup
			m_pick.at(1).update(time_step, pickup::pick::slow);//update pickup
			m_pick.at(2).update(time_step, pickup::pick::rock);//update pickup
		}

		m_audio_manager->update_with_camera(m_3d_camera);

		if (glm::distance(m_enemy.object()->position(), m_player.object()->position()) <= 40.f) {
			m_audio_manager->pause("game music");
			m_audio_manager->play_spatialised_sound("shrek",m_3d_camera.position(),m_enemy.object()->position());
			m_audio_manager->unpause("game music");
		}

		//PowerUP collision testing
		if (m_player.p_box().collision(m_pick.at(0).d_box())) {
			dam = true;
			m_HUD->on_update(HUD::e_power::more);
			m_pick.at(0).dam_object()->set_position(glm::vec3(20.f,1.f,21.f));
		}
		else if (m_player.p_box().collision(m_pick.at(1).s_box())) {
			slow = true;
			m_HUD->on_update(HUD::e_power::slow);
			m_pick.at(0).dam_object()->set_position(glm::vec3(20.f, 1.f, 21.f));
		}
		else if (m_player.p_box().collision(m_pick.at(2).r_box())) {
			rock = true;
			m_HUD->on_update(HUD::e_power::rock);
			m_pick.at(0).dam_object()->set_position(glm::vec3(20.f, 1.f, 21.f));
		}

		if (m_player.Health() == 0)//if you die you lose
			m_lose_game = true;
		else if (m_enemy.health() <= 0)//if you kill shrek you win
			m_win_game = true;
		else if (m_game_timer == 0.f) {// if the timer runs out
			if (m_player.Health() < m_enemy.health())//and you have the least health, you lose
				m_lose_game = true;
			else
				m_win_game = true;//if you have more health, you win
		}
		else if (m_player.object()->position().z >= 28.f && m_zombies.empty())//if you reach the desination and have kill all zombies
			m_win_game = true;
	}
	else if (m_start_game && m_birdview.view_on())//if birdview is true
		m_birdview.camera_update(m_3d_camera);//the camera is given a new view matrix dirctly above the player

	m_physics_manager->dynamics_world_update(m_game_objects, double(time_step));//updating the game world

} 

void example_layer::on_render() 
{
	//Make the colour of the screen not just black
	engine::render_command::clear_color({ 0.f,0.f,0.f, 1.0f });
	engine::render_command::clear();

	// Render text
	const auto text_shader = engine::renderer::shaders_library()->get("text_2D");
	if (!m_start_game) {
		//Title banner for intro screen
		m_text_manager->render_text(text_shader, "Shreks Suburban Swap", 120.f, (float)engine::application::window().height() - 100.f, 1.f, glm::vec4(1.f));
		m_text_manager->render_text(text_shader, "Press Enter to Start", 220.f, (float)engine::application::window().height() - 200.f, 0.875f, glm::vec4(1.f));

		//List of controls for intro screen
		m_text_manager->render_text(text_shader, "The Controls: ", 15.f, (float)engine::application::window().height() - 300.f, 0.625f, glm::vec4(1.f));
		m_text_manager->render_text(text_shader, "- Mouse motion to move ", 15.f, (float)engine::application::window().height() - 350.f, 0.5f, glm::vec4(1.f));
		m_text_manager->render_text(text_shader, "- Left click to shoot", 15.f, (float)engine::application::window().height() - 400.f, 0.5f, glm::vec4(1.f));
		m_text_manager->render_text(text_shader, "- C for birdseye view of map", 15.f, (float)engine::application::window().height() - 450.f, 0.5f, glm::vec4(1.f));
		m_text_manager->render_text(text_shader, "- Collide with powerups to pick up", 15.f, (float)engine::application::window().height() - 500.f, 0.5f, glm::vec4(1.f));
		m_text_manager->render_text(text_shader, "- S for use of slow powerup", 15.f, (float)engine::application::window().height() - 550.f, 0.5f, glm::vec4(1.f));
		m_text_manager->render_text(text_shader, "- D for use of damage powerup", 15.f, (float)engine::application::window().height() - 600.f, 0.5f, glm::vec4(1.f));
		m_text_manager->render_text(text_shader, "- R for use of rock music powerup", 15.f, (float)engine::application::window().height() - 650.f, 0.5f, glm::vec4(1.f));
	}

	//Object and Mesh render once enter key is pressed
	if (m_start_game) {
		//Hide cursor here instead of in the constructor for intro screen
		engine::application::window().hide_mouse_cursor();

		// Set up  shader. (renders textures and materials)
		const auto mesh_shader = engine::renderer::shaders_library()->get("mesh");
		engine::renderer::begin_scene(m_3d_camera, mesh_shader);

		// Set up some of the scene's parameters in the shader
		std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("gEyeWorldPos", m_3d_camera.position());

		// Position the skybox centred on the player and render it
		glm::mat4 skybox_tranform(1.0f);
		skybox_tranform = glm::translate(skybox_tranform, m_3d_camera.position());
		for (const auto& texture : m_skybox->textures())
		{
			texture->bind();
		}
		//stop skybox after 4 seconds has past
		if (m_timer <= 4.f) engine::renderer::submit(mesh_shader, m_skybox, skybox_tranform);

		engine::renderer::submit(mesh_shader, m_terrain);

		//render map objects
		mapRender(mesh_shader);

		//render powerups here cunt

		//player model render (just a cuboid as fps)
		m_player.on_render(mesh_shader);

		//render the gun
		gunRender(mesh_shader);

		//render the touch (octagonal prism)
		touchRender(mesh_shader);

		//render the bullets
		m_ballistic_material->submit(mesh_shader);
		for (int i = 0; i < m_bullets.size(); ++i) {
			m_bullets.at(i)->on_render(mesh_shader);
		}

		//render the zombies
		if (!m_zombies.empty()) {//This should be deleted, sorry if it is not
			for (int i = 0; i < m_zombies.size(); ++i)
				m_zombies.at(i)->on_render(mesh_shader);
		}

		//render shrek
		m_enemy.on_render(mesh_shader);

		//pickup renderer
		if (!m_pick.empty()) {
			m_pick.at(0).on_render(mesh_shader, pickup::pick::damage);
			m_pick.at(1).on_render(mesh_shader, pickup::pick::slow);
			m_pick.at(2).on_render(mesh_shader, pickup::pick::rock);
		}

		//render of 2D text for player health
		m_text_manager->render_text(text_shader, "Health:" + std::to_string((int)m_player.Health()), 4.f, (float)engine::application::window().height() - 30.f, 0.5f, glm::vec4(1.f));
		m_text_manager->render_text(text_shader, "Shrek Health:" + std::to_string((int)m_enemy.health()), 900.f, (float)engine::application::window().height() - 30.f, 0.5f, glm::vec4(1.f));
		m_text_manager->render_text(text_shader, "Time Remaining:" + std::to_string((int)m_game_timer), 400.f, (float)engine::application::window().height() - 30.f, 0.5f, glm::vec4(1.f));

		//win or lose screen
		if (m_win_game == true) {
			m_start_game = false;
			m_text_manager->render_text(text_shader, "YOU WIN!! Press esc to leave", 220.f, (float)engine::application::window().height() - 200.f, 0.875f, glm::vec4(1.f));
		}
		else if (m_lose_game == true) {
			m_start_game = false;
			m_text_manager->render_text(text_shader, "YOU LOSE! Press esc to leave", 220.f, (float)engine::application::window().height() - 200.f, 0.875f, glm::vec4(1.f));
		}
		engine::renderer::end_scene();

		//Render of HUD and cross fade in 2D camera
		engine::renderer::begin_scene(m_2d_camera, mesh_shader);
		std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("lighting_on", false);
		m_cross_fade->on_render(mesh_shader);
		m_HUD->on_render(mesh_shader, glm::vec3(-0.8f, -0.7f, 0.1f), glm::vec3(0.f, -0.7f, 0.1f), glm::vec3(0.8f, -0.7f, 0.1f));
		std::dynamic_pointer_cast<engine::gl_shader>(mesh_shader)->set_uniform("lighting_on", true);
		engine::renderer::end_scene();
	}
} 

void example_layer::on_event(engine::event& event) 
{ 
    if(event.event_type() == engine::event_type_e::key_pressed) 
    { 
        auto& e = dynamic_cast<engine::key_pressed_event&>(event); 
		if (e.key_code() == engine::key_codes::KEY_TAB)
		{
			engine::render_command::toggle_wireframe();
		}
		else if (e.key_code() == engine::key_codes::KEY_ENTER) {//test if enter is pressed
			m_start_game = true;//set bool to true
			m_audio_manager->stop("menu music");
			m_audio_manager->play("game music");
		}
		else if (e.key_code() == engine::key_codes::KEY_C && !m_birdview.view_on()) {//test if birdview is false
			m_birdview.on_update(m_player.object()->position()); m_player.birdStop();//if it is false, male it true
		}
		else if (e.key_code() == engine::key_codes::KEY_C && m_birdview.view_on()) {//if birdview is true
			m_birdview.set_view(false); m_player.birdStart();//make it false
		}
		else if (e.key_code() == engine::key_codes::KEY_S && slow == true){//if the power up is collected
			m_player.up_speed(m_player.Speed() - 0.002f);//player speed decreased
			m_HUD->on_update(HUD::e_power::t_slow);
		}
		else if (e.key_code() == engine::key_codes::KEY_D && dam == true) {//if the power up is collected
			m_HUD->on_update(HUD::e_power::t_more);
			m_player.up_damage(m_player.Dam() + 0.3f);
			m_player.up_sdamage(m_player.sDam() + 0.75f);
		}
		else if (e.key_code() == engine::key_codes::KEY_R && rock == true) {//if the power up is collected
			m_HUD->on_update(HUD::e_power::t_rock);
			m_audio_manager->pause("game music");
			m_audio_manager->play("rock music");
			m_audio_manager->unpause("game music");
		}
    }
	else if (engine::input::mouse_button_pressed(0))//if the left mouse button is pressed
	{
		//do a lot of geometry to make the bullets fire like a shotgun out of said shotgun
		glm::vec3 pos = glm::vec3(m_player.object()->position().x, m_player.object()->position().y - 0.15f, m_player.object()->position().z);
		glm::vec3 forward = m_3d_camera.front_vector();
		glm::vec3 right = m_3d_camera.right_vector();
		glm::vec3 p = pos + 0.5f * forward + 0.2f * right;
		if (m_fire_rate >= 0.8f) {
			for (int i = 0; i < 5; ++i) {
				engine::ref<ballistic> bullet = ballistic::create(m_sphere_props);
				m_bullets.push_back(bullet);
				bullet->fire(p, glm::normalize(glm::vec3(m_3d_camera.front_vector().x + (i * RandomFloat(0.f, 0.008f)), m_3d_camera.front_vector().y + (i * RandomFloat(-0.008f, 0.008f)), m_3d_camera.front_vector().z)), 20.f);
				m_audio_manager->play_spatialised_sound("shotgun", m_3d_camera.position(), glm::vec3(m_player.object()->position()));
				m_audio_manager->volume("shotgun",1000.f);
				m_fire_rate = 0.f;
			}
		}
	}
}

engine::perspective_camera example_layer::getCamera() {
	return m_3d_camera;
}

void example_layer::gunRender(const engine::ref<engine::shader>& shader) {

	//positional data needed from player object
	glm::vec3 pos = glm::vec3(m_player.object()->position().x, m_player.object()->position().y - 0.15f, m_player.object()->position().z);
	glm::vec3 forward = m_3d_camera.front_vector();
	glm::vec3 right = m_3d_camera.right_vector();

	//angles of rotations 
	float theta = engine::PI / 2.0f - acos(forward.y);
	float phi = atan2(forward.x, forward.z);

	//position needed
	glm::vec3 p = pos + 0.5f * forward + 0.2f * right;

	//gun rendering
	glm::mat4 gun_transform(1.0f);
	gun_transform = glm::translate(gun_transform, p);
	gun_transform = glm::rotate(gun_transform, phi + m_gun->rotation_amount(), glm::vec3(0.f, 1.f, 0.f));
	gun_transform = glm::rotate(gun_transform, theta, glm::vec3(1.f, 0.f, 0.f));
	gun_transform = glm::scale(gun_transform, m_gun->scale());
	engine::renderer::submit(shader, gun_transform, m_gun);
}

void example_layer::touchRender(const engine::ref<engine::shader>& shader) {

	//positional data needed from player
	glm::vec3 pos = glm::vec3(m_player.object()->position().x, m_player.object()->position().y - 0.15f, m_player.object()->position().z);
	glm::vec3 forward = m_3d_camera.front_vector();
	glm::vec3 right = m_3d_camera.right_vector();

	//angles needed for rotations
	float theta = engine::PI / 2.0f - acos(forward.y);
	float phi = atan2(forward.x, forward.z);

	//positions needed for the touch and the light source
	glm::vec3 p2 = pos + 0.3f * forward - 0.3f * right;
	glm::vec3 p3 = p2 + 0.5f * forward;

	//spot light rendering
	m_touchLight.Position = glm::vec3(p3);
	std::dynamic_pointer_cast<engine::gl_shader>(shader)->set_uniform("gNumSpotLights", (int)num_spot_lights);
	m_lightsource_material->submit(shader);
	m_touchLight.submit(shader, 0);

	//touch rendering
	m_octagonal_material->submit(shader);
	glm::mat4 touch_transform(1.0f);
	touch_transform = glm::translate(touch_transform, p2);
	touch_transform = glm::rotate(touch_transform, phi, glm::vec3(0.f, 1.f, 0.f));
	touch_transform = glm::rotate(touch_transform, -theta + m_octagonal->rotation_amount(), glm::vec3(1.f, 0.f, 0.f));
	touch_transform = glm::scale(touch_transform, m_octagonal->scale());
	engine::renderer::submit(shader, touch_transform, m_octagonal);
}

void example_layer::mapRender(const engine::ref<engine::shader> &shader) {
	//loop for rendering multiple instances of the road model
	glm::mat4 road_transform(1.0f);
	float z = -35.f;//initial Z position
	for (int i = 0; i <= 15; ++i) {
		road_transform = glm::mat4(1.f);
		if (i <= 6) {
			road_transform = glm::translate(road_transform, glm::vec3(0.f, -0.495f, z));
			road_transform = glm::rotate(road_transform, glm::pi<float>() / 2.f, m_road->rotation_axis());
			engine::renderer::submit(shader, road_transform, m_road);
			z += 7;//delta zpos for each new zpos
		}
		else {
			if (i < 8) {
				road_transform = glm::translate(road_transform, glm::vec3(0.0f, -0.495f, z));
				road_transform = glm::rotate(road_transform, -glm::pi<float>() / 2.f, m_road_turn->rotation_axis());
				engine::renderer::submit(shader, road_transform, m_road_turn);
			}
			else {
				if (i == 8) {
					road_transform = glm::translate(road_transform, glm::vec3(20.0f, -0.495f, z));
					road_transform = glm::rotate(road_transform, glm::pi<float>() / 2.f, m_road_turn->rotation_axis());
					engine::renderer::submit(shader, road_transform, m_road_turn);
				}
				else {
					z += 7;
					road_transform = glm::translate(road_transform, glm::vec3(20.f, -0.495f, z));
					road_transform = glm::rotate(road_transform, glm::pi<float>() / 2.f, m_road->rotation_axis());
					engine::renderer::submit(shader, road_transform, m_road);
				}
			}
		}
	}

	//Render the house mesh multiple times in a zigzag against the road
	glm::mat4 house_transform(1.0f);
	float house_x = m_house->position().x;//Temp for changing xpos
	float house_z = m_house->position().z;//Temp for changing zpos
	float negRot = -1;//Change rotate so house is facing the road
	for (int i = 0; i < 15; ++i) {
		if (i <= 6) {
			if (i % 2 != 0 && i != 0) {//Change xpos and rotation
				house_x = -house_x;
				negRot = 1;
			}
			else {
				house_x = m_house->position().x;
				negRot = -1;
			}
			house_transform = glm::mat4(1.f);
			house_transform = glm::translate(house_transform, glm::vec3(house_x, m_house->position().y, house_z));// -glm::vec3(m_house->offset().x, 0.f, m_house->offset().z));
			house_transform = glm::rotate(house_transform, negRot * (glm::pi<float>() / 2.f), m_house->rotation_axis());
			engine::renderer::submit(shader, house_transform, m_house);
			m_house_box.at(i).set_box(m_house->bounding_shape().x, m_house->bounding_shape().y, m_house->bounding_shape().z, glm::vec3(house_x, m_house->position().y, house_z), true);
			m_house_box.at(i).on_update(glm::vec3(house_x, m_house->position().y, house_z), m_house->rotation_amount(), m_house->rotation_axis(), true);
			m_house_box.at(i).on_render(1.f,0.f,0.f, shader, true);
			house_z += 7;//delta zpos for each new zpos
		}
		else if (i == 7) house_z += 7;
		else if(i >= 8){
			if (i % 2 != 0 && i != 0) {//Change xpos and rotation
				house_x = 13.f;
				negRot = 1;
			}
			else {
				house_x = 27.f;
				negRot = -1;
			}
			house_transform = glm::mat4(1.f);
			house_transform = glm::translate(house_transform, glm::vec3(house_x, m_house->position().y, house_z));// -glm::vec3(m_house->offset().x, 0.f, m_house->offset().z));
			house_transform = glm::rotate(house_transform, negRot * (glm::pi<float>() / 2.f), m_house->rotation_axis());
			engine::renderer::submit(shader, house_transform, m_house);
			m_house_box.at(i).set_box(m_house->bounding_shape().x, m_house->bounding_shape().y, m_house->bounding_shape().z, glm::vec3(house_x, m_house->position().y, house_z), true);
			m_house_box.at(i).on_update(glm::vec3(house_x, m_house->position().y, house_z), m_house->rotation_amount(), m_house->rotation_axis() , true);
			m_house_box.at(i).on_render(1.f,0.f,0.f, shader, true);
			house_z += 7;//delta zpos for each new zpos
		}
	}

	//Render the modern house mesh multiple times in an opposite zigzag against the road
	house_x = m_house2->position().x;//Temp for changing xpos
	house_z = m_house2->position().z;//Temp for changing zpos
	negRot = 1;//Change rotate so house is facing the road
	glm::mat4 house2_transform(1.0f);
	for (int i = 0; i < 15; ++i) {//Change xpos and rotation
		if (i <=6) {
			if (i % 2 != 0) {
				house_x = -house_x;
				negRot = -1;
			}
			else {
				house_x = m_house2->position().x;
				negRot = 1;
			}
			house2_transform = glm::mat4(1.f);
			house2_transform = glm::translate(house2_transform, glm::vec3(house_x, m_house2->position().y, house_z));//- glm::vec3(m_house2->offset().x, 0.f, m_house2->offset().z));
			house2_transform = glm::rotate(house2_transform, negRot * (glm::pi<float>() / 2.f), m_house2->rotation_axis());
			engine::renderer::submit(shader, house2_transform, m_house2);
			m_house2_box.at(i).set_box(m_house2->bounding_shape().x , m_house2->bounding_shape().y , m_house2->bounding_shape().z , glm::vec3(house_x, m_house2->position().y, house_z) , true);
			m_house2_box.at(i).on_update(glm::vec3(house_x, m_house2->position().y, house_z), m_house2->rotation_amount(), m_house2->rotation_axis() , true);
			m_house2_box.at(i).on_render(1.f, 0.f,0.f, shader, true);
			house_z += 7;//delta zpos for each new zpos
		}
		else {
			if (i % 2 != 0) {
				house_x = 28.4f;
				negRot = -1;
			}
			else {
				house_x = 11.6f;
				negRot = 1;
			}
			house2_transform = glm::mat4(1.f);
			house2_transform = glm::translate(house2_transform, glm::vec3(house_x, m_house2->position().y, house_z));// - glm::vec3(m_house2->offset().x, 0.f, m_house2->offset().z));
			house2_transform = glm::rotate(house2_transform, negRot * (glm::pi<float>() / 2.f), m_house2->rotation_axis());
			engine::renderer::submit(shader, house2_transform, m_house2);
			m_house2_box.at(i).set_box(m_house2->bounding_shape().x, m_house2->bounding_shape().y, m_house2->bounding_shape().z, glm::vec3(house_x, m_house2->position().y, house_z), true);
			m_house2_box.at(i).on_update(glm::vec3(house_x, m_house2->position().y, house_z), m_house2->rotation_amount(), m_house2->rotation_axis(), true);
			m_house2_box.at(i).on_render(1.f,0.f,0.f, shader,true);
			house_z += 7;//delta zpos for each new zpos
		}
	}
}

//Code sourced from stackoverflow https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats/5289624
float example_layer::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
