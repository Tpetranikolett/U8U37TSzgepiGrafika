#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
	load_model(&(scene->target[0].model), "assets/models/archery.obj");
	scene->target[0].texture = load_texture("assets/textures/archery.jpg");
	load_model(&(scene->target[1].model), "assets/models/archery.obj");
	scene->target[1].texture = load_texture("assets/textures/archery.jpg");
	load_model(&(scene->target[2].model), "assets/models/archery.obj");
	scene->target[2].texture = load_texture("assets/textures/archery.jpg");
	load_model(&(scene->bullet.model), "assets/models/lovedek.obj");
	scene->bullet.texture = load_texture("assets/textures/bullet_texture.jpg");
	load_model(&(scene->grass), "assets/models/grass_2.obj");
	scene->texture_grass = load_texture("assets/textures/grass.jpg"); 
	//load_model(&(scene->area), "assets/models/area.obj");
	//scene->texture_area = load_texture("assets/texture/area_texture.jpg");
	
	/*load_model(&(scene->sky[0]), "assets/models/grass.obj");
	scene->texture_sky = load_texture("assets/textures/area_texture.jpg");
	
	load_model(&(scene->sky[1]), "assets/models/grass.obj");
	scene->texture_sky = load_texture("assets/textures/area_texture.jpg");

	load_model(&(scene->sky[2]), "assets/models/grass.obj");
	scene->texture_sky = load_texture("assets/textures/area_texture.jpg");
	
	load_model(&(scene->sky[3]), "assets/models/grass.obj");
	scene->texture_sky = load_texture("assets/textures/area_texture.jpg");*/

	load_model(&(scene->sky[0]), "assets/models/giant_cube.obj");
	scene->texture_sky = load_texture("assets/textures/area_texture.jpg");
	
	scene->shadow_texture = load_texture("assets/textures/shadow.jpg");
	
	
    //glBindTexture(GL_TEXTURE_2D, scene->texture_id);

    scene->material.ambient.red = 0.7;
    scene->material.ambient.green = 0.7;
    scene->material.ambient.blue = 0.7;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
	
	scene->bullet.position.x = 2.0;
	scene->bullet.position.y = -1.0;
	scene->bullet.position.z = 4.0;
	
	scene->target[0].position.x = 40.0;
	scene->target[0].position.y = 0.0;
	scene->target[0].position.z = 0.0;
	
	scene->target[1].position.x = 35.0;
	scene->target[1].position.y = -5.0;
	scene->target[1].position.z = 0.0;
	
	scene->target[2].position.x = 30.0;
	scene->target[2].position.y = 5.0;
	scene->target[2].position.z = 0.0;
	
	scene->light.ambient_light[0] = 0.5f;
	scene->light.ambient_light[1] = 0.5f;
	scene->light.ambient_light[2] = 0.5f;
	scene->light.ambient_light[3] = 0.5f;
	
	scene->bullet.speed = 0.0;
	
	scene->light.brightness = 0.0;
	
	scene->target[0].rotation = 0.0;
	scene->target[1].rotation = 0.0;
	scene->target[2].rotation = 0.0;
	
	scene->bullet.hit = 0;
	
	scene->target[0].speed = 0.0;
	scene->target[1].speed = 0.0;
	scene->target[2].speed = 0.0;
	
	scene->target[0].hit = 0;
	scene->target[1].hit = 0;
	scene->target[2].hit = 0;
	
	scene->HelpMenuTexture = load_texture("assets/textures/help.jpg");
}



void set_lighting(Scene* scene)
{
    float ambient_light[] = { scene->light.ambient_light[0], scene->light.ambient_light[1], scene->light.ambient_light[2], scene->light.ambient_light[3] };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene, double time, Camera* camera)
{
	
	scene->bullet.position.x += scene->bullet.speed * time;
	scene->bullet.position.y += camera->speed.y*time;
	scene->bullet.position.z += camera->speed.z*time;
	
	
	//scene->target[0].position.y += scene->target[0].speed * time * time;
	//scene->target[1].position.y += scene->target[1].speed * time * time;
	//scene->target[2].position.y += scene->target[2].speed * time * time;
	
	scene->target[0].position.y += scene->target[0].speed * time;
	scene->target[1].position.y += scene->target[1].speed * time;
	scene->target[2].position.y += scene->target[2].speed * time;
	for(int i = 0; i<3; i++)
	{
		if(scene->target[i].speed < 5 && scene->target[i].speed >= -5 && scene->target[i].hit < 1)
		{
			scene->target[i].speed = -10;
		}
	}
	//if(scene->target[0].speed <=50 && scene->target[0].speed >= -50)
	//{
	if(scene->target[0].position.y >= 10 && scene->target[0].position.y <= 20)
	{	if(scene->target[0].speed <= 50 && scene->target[0].speed >= -50)
		{
		scene->target[0].speed = (scene->target[0].speed * (-1)) - 1.3;
		}
		else scene->target[0].speed = (scene->target[0].speed * (-1));

	}
	if(scene->target[0].position.y <= -10 && scene->target[0].position.y >= -20)
	{
		if(scene->target[0].speed <= 50 && scene->target[0].speed >= -50)
		{
		scene->target[0].speed = scene->target[0].speed * (-1) + 1.3;
		}
		else scene->target[0].speed = scene->target[0].speed * (-1);

	}
	//}
	//if(scene->target[1].speed <=50 && scene->target[1].speed >= -50)
	//{
	if(scene->target[1].position.y >= 10 && scene->target[1].position.y <= 20)
	{
		if(scene->target[1].speed <= 50 && scene->target[1].speed >= -50)
		{
		scene->target[1].speed = (scene->target[1].speed * (-1)) - 0.7;
		}
		else scene->target[1].speed = (scene->target[1].speed * (-1));

	}
		
	if(scene->target[1].position.y <= -10 && scene->target[1].position.y >= -20)
	{
		if(scene->target[1].speed <= 50 && scene->target[1].speed >= -50)
		{
		scene->target[1].speed = scene->target[1].speed * (-1) + 0.7;
		}
		else scene->target[1].speed = scene->target[1].speed * (-1);

		
	}
	//}
	//if(scene->target[2].speed <=50 && scene->target[2].speed >= -50)
	//{
	if(scene->target[2].position.y >= 10 && scene->target[2].position.y <= 20)
	{
		if(scene->target[2].speed <= 50 && scene->target[2].speed >= -50)
		{
		scene->target[2].speed = (scene->target[2].speed * (-1)) - 0.3;
		}
		else scene->target[2].speed = (scene->target[2].speed * (-1));

		
	}
	if(scene->target[2].position.y <= -10 && scene->target[2].position.y >= -20)
	{
		if(scene->target[2].speed <= 50 && scene->target[2].speed >= -50)
		{
		scene->target[2].speed = scene->target[2].speed * (-1) + 0.3;
		}
		else scene->target[2].speed = scene->target[2].speed * (-1);

		
	}
	//}
		//printf("target 0 x: %f \n", scene->target[0].position.x);
		//printf("target 0 y: %f \n", scene->target[0].position.y);
		//printf("target 0 z: %f \n", scene->target[0].position.z);
		//printf("target 1 x: %f \n", scene->target[1].position.x);
		//printf("target 1 y: %f \n", scene->target[1].position.y);
		//printf("target 1 z: %f \n", scene->target[1].position.z);
		//printf("target 2 x: %f \n", scene->target[2].position.x);
		//printf("target 2 y: %f \n", scene->target[2].position.y);
		//printf("target 2 z: %f \n", scene->target[2].position.z);

	if(scene->bullet.is_it_shot = true)
	{
		//scene->bullet.position.y = scene->bullet.current_pos.y;
		//scene->bullet.position.z = scene->bullet.current_pos.z;

	}
	
		//printf("bullet x: %f \n", scene->bullet.position.x);
		//printf("bullet y: %f \n", scene->bullet.position.y);
		//printf("bullet z: %f \n", scene->bullet.position.z);
	for(int i=0; i<3; i++){
		if(scene->bullet.position.x  <= scene->target[i].position.x + 0.5 &&  scene->bullet.position.x  >= scene->target[i].position.x - 0.5 && scene->bullet.position.y <= scene->target[i].position.y + 2 && scene->bullet.position.y >= scene->target[i].position.y - 2 && scene->bullet.position.z >= scene->target[i].position.z - 2 && scene->bullet.position.z <= scene->target[i].position.z + 2)
		{
		//printf("bullet x: %f \n", scene->bullet.position.x);
		//printf("bullet y: %f \n", scene->bullet.position.y);
		//printf("bullet z: %f \n", scene->bullet.position.z);
		
		scene->bullet.speed = 0;
		scene->target[i].speed = 0;
		if(scene->target[i].rotation < 60)
		{
			scene->target[i].rotation += 40*time;
		}
		scene->target[i].hit = 1;
		//	scene->bullet.hit = i;
	
		if(scene->bullet.hit < 2 && scene->target[i].rotation >= 60)
		{
			scene->bullet.position.x = camera->position.x + 1.5;
			scene->bullet.position.y = camera->position.y - 0.5;
			scene->bullet.position.z = camera->position.z -0.5;
			scene->bullet.hit++;
		}
			
		//set_ambient_light(scene, +1000);
		//break;
		}

	}

	
	
	for(int i = 0; i <4; i++)
	{
		scene->light.ambient_light[i] += scene->light.brightness * time;
	}
	
	if(scene->bullet.position.x >= 50)
	{
		scene->bullet.speed = 0;
		scene->bullet.position.x = camera->position.x + 1.5;
		scene->bullet.position.y = camera->position.y - 0.5;
		scene->bullet.position.z = camera->position.z -0.5;
	}
		
	
		
		

	render_scene(scene, camera);
}

void render_scene(const Scene* scene, Camera* camera)
{
    set_material(&(scene->material));
    set_lighting(scene);
    //draw_origin();
	
	
	glPushMatrix();
	glTranslatef(scene->target[0].position.x, scene->target[0].position.y, scene->target[0].position.z);
	glRotatef(90, 0, 0, 1);
	glRotatef(scene->target[0].rotation, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, scene->target[0].texture);
    draw_model(&(scene->target[0].model));
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(scene->target[0].position.x, scene->target[0].position.y, scene->target[0].position.z-3);
	glScalef(1, 1, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(scene->target[0].rotation, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, scene->shadow_texture);
    draw_model(&(scene->target[0].model));
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(scene->target[1].position.x, scene->target[1].position.y, scene->target[1].position.z);
	glRotatef(90, 0, 0, 1);
	glRotatef(scene->target[1].rotation, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, scene->target[1].texture);
    draw_model(&(scene->target[1].model));
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(scene->target[1].position.x, scene->target[1].position.y, scene->target[1].position.z-3);
	glScalef(1, 1, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(scene->target[1].rotation, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, scene->shadow_texture);
    draw_model(&(scene->target[1].model));
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(scene->target[2].position.x, scene->target[2].position.y, scene->target[2].position.z);
	glRotatef(90, 0, 0, 1);
	glRotatef(scene->target[2].rotation, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, scene->target[2].texture);
    draw_model(&(scene->target[2].model));
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(scene->target[2].position.x, scene->target[2].position.y, scene->target[2].position.z-3);
	glScalef(1, 1, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(scene->target[2].rotation, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, scene->shadow_texture);
    draw_model(&(scene->target[2].model));
	glPopMatrix();
	
	if(scene->HelpMenuOn)
	{
		loadHelpMenu(scene->HelpMenuTexture);
	}

	//set_target_position(target[0], -10, -10, 5);
	glPushMatrix();
	glTranslatef(scene->bullet.position.x, scene->bullet.position.y, scene->bullet.position.z);
	glRotatef(-25, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, scene->bullet.texture);
	glBegin(GL_TRIANGLES);
	draw_model(&(scene->bullet.model));
	glEnd();
	glPopMatrix();
	
	
	glPushMatrix();
	glTranslatef(0, 0, -5.5);
	glBindTexture(GL_TEXTURE_2D, scene->texture_grass);
	draw_model(&(scene->grass));
	glPopMatrix();
	//glBindTexture(GL_TEXTURE_2D, scene->texture);
	//draw_model(&(scene->area));
	
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glBindTexture(GL_TEXTURE_2D, scene->texture_sky);
	draw_model(&(scene->sky[0]));
	glPopMatrix();
	
	/*glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, 1, 0);
	glEnd();*/
	
	//glPushMatrix();
	
	
	/*glPushMatrix();
	glTranslatef(1000, 0, 0);
	glRotatef(90, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, scene->texture_sky);
	draw_model(&(scene->sky[1]));
	glPopMatrix();*/
	
	/*glPushMatrix();
	glTranslatef(-1000, 0, 0);
	glRotatef(90, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, scene->texture_sky);
	draw_model(&(scene->sky[2]));
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, -1000, 0);
	glRotatef(90, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, scene->texture_sky);
	draw_model(&(scene->sky[3]));
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 1000, 0);
	glRotatef(90, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, scene->texture_sky);
	draw_model(&(scene->sky[4]));
	glPopMatrix();*/
	
	
	
	
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void set_bullet_speed(Scene* scene, float speed)
{
	scene->bullet.speed = speed;
}

void set_ambient_light(Scene* scene, float brightness)
{
	scene->light.brightness = brightness;
}
	
void set_target_speed(Scene* scene, float speed, int i)
{
	scene->target[i].speed = speed;
}

void loadHelpMenu(GLuint control) 
{
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, control);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-4, 3, -5);

    glTexCoord2f(1, 0);
    glVertex3d(4, 3, -5);

    glTexCoord2f(1, 1);
    glVertex3d(4, -3, -5);

    glTexCoord2f(0, 1);
    glVertex3d(-4, -3, -5);
    glEnd();

    glEnable(GL_LIGHTING);
}

void set_HelpMenuState(Scene* scene, bool state)
{
	scene->HelpMenuOn = state;
}

