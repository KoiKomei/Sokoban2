#include "Menu.h"

void Menu::inizio(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, bool &done) {
	ALLEGRO_EVENT_QUEUE *menu = NULL;
	menu = al_create_event_queue();
	bool ok = false;	
	al_register_event_source(menu, al_get_mouse_event_source());
	al_register_event_source(menu, al_get_display_event_source(display));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(font, al_map_rgb(255, 0, 0), 640, 100, ALLEGRO_ALIGN_CENTER, "SOKOBAN");
	al_draw_text(font, al_map_rgb(0, 255, 0), 640, 360, ALLEGRO_ALIGN_CENTER, "PLAY GAME");
	al_draw_text(font, al_map_rgb(0, 255, 0), 640, 480, ALLEGRO_ALIGN_CENTER, "EXIT");
	al_flip_display();
	while (!ok) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(menu, &ev);
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if (ev.mouse.x >= 600 && ev.mouse.x <= 600 + al_get_text_width(font, "EXIT") && ev.mouse.y >= 480 && ev.mouse.y <= 480 + al_get_font_ascent(font)) {
				done = true;
				cout << "You are clicking here";
				ok = true;
			}
			if (ev.mouse.x >= 520 && ev.mouse.x <= 520 + al_get_text_width(font, "PLAYGAME") && ev.mouse.y >= 360 && ev.mouse.y <= 360 + al_get_font_ascent(font))
				ok = true;
			
		}
		
		
	}
}