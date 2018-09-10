#include <iostream>

#include "Sokoban.h"


using namespace std;


int main() {
	const float FPS = 20;
	const int SCREEN_W = 1280;
	const int SCREEN_H = 720;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *queue = NULL;
	ALLEGRO_EVENT_QUEUE *menu = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bitmap = NULL;
	ALLEGRO_BITMAP *tile=NULL;
	ALLEGRO_FONT *font = NULL;
	
	al_init();
	
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	al_install_keyboard();
	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	al_clear_to_color(al_map_rgb(255, 0, 255));

	queue = al_create_event_queue();
	if (!queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	al_install_mouse();
	al_register_event_source(queue, al_get_display_event_source(display));

	al_register_event_source(queue, al_get_timer_event_source(timer));

	al_register_event_source(queue, al_get_keyboard_event_source());

	al_init_primitives_addon();
	al_init_image_addon();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	bitmap = al_load_bitmap("yukki.png");
	
	tile = al_load_bitmap("tilesheet1.png");
	al_init_font_addon();
	al_init_ttf_addon();
	font = al_load_font("ariali.ttf", 48, 0);
	al_init_acodec_addon();
	al_install_audio();
	al_reserve_samples(1);
	

	al_start_timer(timer);
	bool done = false;
	
	Menu men;
	Sokoban soko;
	while (!done) {
		
		men.inizio(display, font, done);
		if (!done) {
			
			soko.gioca(display, queue, bitmap, tile, font);
			
		}
		
	}
	return 0;

}