#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Shoot
{
	Model model;
	GLuint texture;
	Material material;
	vec3 position;
	float speed;
	bool is_it_shot;
	vec3 current_pos;
	int hit;
	float rotation;
} Shoot;

typedef struct Targets
{
	Model model;
	GLuint texture;
	Material material;
	vec3 position;
	float rotation;
	float speed;
	int hit;
} Targets;

typedef struct Light
{
	float ambient_light[4];
	float brightness;
}Light;

typedef struct Scene
{
    Material material;
	Targets target[3];
	Shoot bullet;
	Model grass;
	Model sky[5];
	GLuint texture_grass;
	GLuint texture_sky;
	Light light;
	bool HelpMenuOn;
	GLuint HelpMenuTexture;
	GLuint shadow_texture;
} Scene;


typedef struct Help
{
	Model model;
} Help;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(Scene* scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double time, Camera* camera);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene, Camera* camera);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void set_bullet_speed(Scene* scene, float speed);

void set_ambient_light(Scene* scene, float brightness);

void set_target_speed(Scene* scene, float speed, int i);

void set_HelpMenuState(Scene* scene, bool state);

//void loadHelpMenu(GLuint control);

#endif /* SCENE_H */


