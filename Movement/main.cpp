#include <iostream>
#include "allegro5/allegro_native_dialog.h"
#include "Sokoban.h"


using namespace std;


int main() {
	const float FPS = 60;
	const int SCREEN_W = 1280;
	const int SCREEN_H = 720;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;
	
	al_init();
	
	if (!al_init()) {
		
		cout<<"failed to initialize allegro!"<<endl;
		return -1;
	}
	int avvertimento = al_show_native_message_box(display, "ATTENZIONE",
		"Riguardo gli fps, si possono modificare, se si vuole, tramite il file fps.txt", 
		"A causa del timer di allegro, la ripetizione dei tasti potrebbe essere troppo veloce a 60fps, quindi gli fps base sono a 4/60 ovvero 15 frames al secondo", NULL, 0);
	ifstream frames("fps.txt");
	float fp = 0.0;
	frames >> fp;
	frames.close();
	cout << "Il gioco va a " << FPS/fp <<" fps"<< endl;
	timer = al_create_timer(fp / FPS);
	if (!timer) {
		cout<<"failed to initialize timer!"<<endl;
		return -1;
	}
	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		cout << "failed to initialize display!" << endl;
		al_destroy_timer(timer);
		return -1;
	}

	al_clear_to_color(al_map_rgb(255, 0, 255));

	queue = al_create_event_queue();
	if (!queue) {
		cout << "failed to initialize queue!" << endl;
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	

	al_init_primitives_addon();
	if (!al_init_primitives_addon()) {
		cout << "failed to initialize primitives!" << endl;
		return -1;
	}
	al_init_image_addon();
	if (!al_init_image_addon()) {
		cout << "failed to initialize image!" << endl;
		return -1;
	}
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	al_init_font_addon();
	al_init_ttf_addon();
	if (!al_init_ttf_addon()) {
		cout << "failed to initialize ttf!" << endl;
		return -1;
	}
	font = al_load_font("ariali.ttf", 36, 0);
	al_init_acodec_addon();
	if (!al_init_acodec_addon()) {
		cout << "failed to initialize audiocodec!" << endl;
		return -1;
	}
	al_install_audio();
	if (!al_install_audio()) {
		cout << "failed to initialize audio!" << endl;
		return -1;
	}
	al_reserve_samples(1);
	
	
	al_start_timer(timer);
	bool done = false;
	
	Menu men;
	Sokoban soko;
	while (!done) {
		
		men.inizio(display, font, done);
		if (!done) {
		
			soko.gioca(display, queue, font);
			
		}
		
	}
	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	return 0;

}