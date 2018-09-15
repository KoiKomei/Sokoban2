#include "Menu.h"

Menu::Menu() {
	bgm = al_load_sample("Menu.ogg");
	bitmap = al_load_bitmap("menu.png");
	menu = al_create_event_queue();
}


void Menu::inizio(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, bool &done) {
	al_install_mouse();
	al_play_sample(bgm, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	bool ok = false;	
	int some = 0;
	al_register_event_source(menu, al_get_mouse_event_source());
	al_register_event_source(menu, al_get_display_event_source(display));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(bitmap, 0, 0, 0);
	al_draw_text(font, al_map_rgb(255, 255, 0), 640, 240, ALLEGRO_ALIGN_CENTER, "PLAY GAME");
	al_draw_text(font, al_map_rgb(255, 255, 0), 640, 300, ALLEGRO_ALIGN_CENTER, "RECORD");
	al_draw_text(font, al_map_rgb(255, 255, 0), 640, 360, ALLEGRO_ALIGN_CENTER, "EXIT");
	al_flip_display();
	while (!ok) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(menu, &ev);
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if (ev.mouse.x >= 600 && ev.mouse.x <= 600 + al_get_text_width(font, "EXIT") && ev.mouse.y >= 360 && ev.mouse.y <= 360 + al_get_font_ascent(font)) {
				done = true;
				cout << "You are clicking here";
				al_destroy_event_queue(menu);
				ok = true;
			}
			if (ev.mouse.x >= 520 && ev.mouse.x <= 520 + al_get_text_width(font, "PLAYGAME") && ev.mouse.y >= 240 && ev.mouse.y <= 240 + al_get_font_ascent(font))
				ok = true;
			if (ev.mouse.x >= 560 && ev.mouse.x <= 560 + al_get_text_width(font, "RECORD") && ev.mouse.y >= 300 && ev.mouse.y <= 300 + al_get_font_ascent(font)) {
				score.open("Record.txt");
				int spacing = 450;
				for (int i = 0; i < score.end; i++) {
					score >> some;
					char som[256];
					sprintf(som, "%d", some);
					if (spacing == 450) {
						al_draw_text(font, al_map_rgb(255, 255, 255), 400, spacing, ALLEGRO_ALIGN_LEFT, "Minori mosse: ");
					}
					else {
						al_draw_text(font, al_map_rgb(255, 255, 255), 400, spacing, ALLEGRO_ALIGN_LEFT, "Minori spinte: ");
					}
					al_draw_text(font, al_map_rgb(255, 255, 0), 800, spacing, ALLEGRO_ALIGN_CENTER, som);
					cout << some << endl;
					
					if (spacing == 450) {
						spacing += 60;
					}
					else {
						spacing = 450;
					}
					
					
				}
				score.close();
				al_flip_display();
				
			}
		
		}
		
		
	}
	al_uninstall_mouse();
	al_stop_samples();
}