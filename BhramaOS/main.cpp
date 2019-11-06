#define _USE_MATH_DEFINES

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>
#include <math.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <list>

#include "Sphere.h"
#include "sim_consts.h"

const int len = 128;
const int sca = 4;

std::vector<Sphere*> genFluid(int numParticles, double averageSize, double sizeStdDev, double averageOmega, double omegaStdDev) {
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::normal_distribution<> size{ averageSize, sizeStdDev };
	std::normal_distribution<> curl{ averageSize, sizeStdDev };
	std::normal_distribution<> velo{ -(double)sca, (double)sca };
	std::uniform_real_distribution<> loca{ 2.0, (double)len-2.0 };

	std::vector<Sphere*> set;

	for (int x = 0; x < numParticles; x++) {
		double adjustSize = size(gen);
		double adjustOmega = curl(gen);
		Vector2 vel = Vector2(velo(gen), velo(gen));
		Vector2 pos = Vector2(loca(gen), loca(gen));
		double size = ((averageSize + adjustSize) > 0) ? (averageSize + adjustSize) : averageSize;
		double curl = averageOmega + adjustOmega;
		Sphere* sp = new Sphere(size, size*size*sim_consts::RHO_WATER*M_PI, 0, pos, vel, 0, averageOmega + adjustOmega);
		sp->color = al_map_rgb(224, 23, 149);
		sp->a.y = -0.5;
		set.push_back(sp);
	}
	return set;
}


int main()
{
	al_init();
	assert(al_init_primitives_addon());
	assert(al_init_font_addon());
	assert(al_init_ttf_addon());
	ALLEGRO_DISPLAY* display = al_create_display(len * sca, len * sca);
	ALLEGRO_FONT *font = al_load_ttf_font("drakon.ttf",12,0);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

	al_clear_to_color(al_map_rgb(0, 0, 0));
	std::vector<Sphere*> sphere = genFluid(200, 4, 1, 0, M_2_PI);


	while (true) {

		
		for (int i = 0; i < sphere.size(); i++) {
			// Render and move objects
			sphere[i]->render();
			sphere[i]->step();

			// Allow Collisions with other bodies
			for (int j = i+1; j < sphere.size(); j++) {
				// Use electrodynamics for EM forces
				Abstract_Object::gauss(sphere[i], sphere[j]);
				// Use kinematics for collisions if the bodies collide
				if (sphere[i]->has_collided(sphere[j])) {
					Abstract_Object::collide(sphere[i], sphere[j]);
				}
			}

			// Collide with Walls
			sphere[i]->hit_wall(len*sca, len*sca, .99);
		}
		al_draw_text(font, white, 640/2, (480/4), ALLEGRO_ALIGN_CENTRE, "FPS:: ");
		al_flip_display();
		al_rest(0.01);

		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	al_rest(5.0);
	return 0;
}