#include "Menu.h"


/*COSTRUTTORE DELLA CLASSE MENU*/
Menu::Menu() {
	bgm = al_load_sample("Menu.ogg");
	bitmap = al_load_bitmap("menu.png");
	menu = al_create_event_queue();
}

/*DISEGNA TUTTO IL MENU'*/
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
			/*ESCE DAL GIOCO*/
			if (ev.mouse.x >= 600 && ev.mouse.x <= 600 + al_get_text_width(font, "EXIT") && ev.mouse.y >= 360 && ev.mouse.y <= 360 + al_get_font_ascent(font)) {
				done = true;
				al_destroy_event_queue(menu);
				ok = true;
			}
			/*AVVIA LA PARTITA*/
			if (ev.mouse.x >= 540 && ev.mouse.x <= 540 + al_get_text_width(font, "PLAYGAME") && ev.mouse.y >= 240 && ev.mouse.y <= 240 + al_get_font_ascent(font))
				ok = true;

			/*CONTROLLA IL FILE RECORD E LO STAMPA*/
			if (ev.mouse.x >= 560 && ev.mouse.x <= 560 + al_get_text_width(font, "RECORD") && ev.mouse.y >= 300 && ev.mouse.y <= 300 + al_get_font_ascent(font)) {
				score.open("record.txt");
				int spacing = 450;
				for (int i = 0; i < score.end; i++) {
					score >> some;
					char som[256];
					snprintf(som, sizeof(som), "%d", some);
					if (spacing == 450) {
						al_draw_text(font, al_map_rgb(255, 255, 255), 610, spacing, ALLEGRO_ALIGN_CENTER, "Minori mosse: ");
					}
					else {
						al_draw_text(font, al_map_rgb(255, 255, 255), 610, spacing, ALLEGRO_ALIGN_CENTER, "Minori spinte: ");
					}
					al_draw_text(font, al_map_rgb(255, 255, 0), 730, spacing, ALLEGRO_ALIGN_LEFT, som);
					
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