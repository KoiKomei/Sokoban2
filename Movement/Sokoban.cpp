#include "Sokoban.h"

void Sokoban::gioca(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_BITMAP *bitmap, ALLEGRO_BITMAP *tile, ALLEGRO_FONT *font) {
	ALLEGRO_SAMPLE *bgm = NULL;
	bgm = al_load_sample("101Day.ogg");
	al_play_sample(bgm, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	bool done = false;
	load();

	stampa(bitmap, tile, font);
	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(queue, &ev);
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || key[ESC]) {
			passi = 0;
			spin = 0;
			level[0] = true;
			level[1] = false;
			level[2] = false;
			key[ESC] = false;
			done = true;
		}
		bool tro = false;
		move(tro, ev, bitmap, tile, font);
		int cont = 0;
		for (int i = 0; i < mat.size(); i++) {
			for (int j = 0; j < mat[i].size(); j++) {
				
					if (mat[i][j] == 3 && def[i][j] == 4) {
						cont++;
					}
				
			}
		}
		//cout << cont << endl;
		if (cont == 1 && level[0]) {
			passi = 0;
			spin = 0;
			level[0] = false;
			level[1] = true;
			load();
			stampa(bitmap, tile, font);
		}
		else if(cont==1 && level[1]){
			passi = 0;
			spin = 0;
			level[1] = false;
			level[2] = true;
			load();
			stampa(bitmap, tile, font);
		}
		else if (cont == 1 && level[2]) {
			level[2] = false;
			level[0] = true;
			done = true;
		}

	}
	al_stop_samples();
}

void Sokoban::stampa(ALLEGRO_BITMAP *bitmap, ALLEGRO_BITMAP *tile, ALLEGRO_FONT *font) {
	al_clear_to_color(al_map_rgb(0,0,0));
	
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[i].size(); j++) {
			cout << mat[i][j];
			if (mat[i][j] == 0) {
				
				al_draw_bitmap_region(tile, 0, 0, 32, 32, (SCREEN_H/22)*j+320, (SCREEN_H/22)*i+180, 0);
			}
			if (def[i][j] == 4) {
					al_draw_bitmap_region(tile, 64, 0, 32, 32, (SCREEN_H/22)*j + 320, (SCREEN_H/22)*i + 180, 0);
			}
			if (mat[i][j] == 2) {
				al_draw_bitmap_region(tile, 32, 0, 32, 32, (SCREEN_H/22)*j+320, (SCREEN_H/22)*i+180, 0);
				
			}
			if (mat[i][j] == 1) {
				if (def[i][j] == 0 || def[i][j]==1 || def[i][j]==3) {
					al_draw_bitmap_region(tile, 0, 0, 32, 32, (SCREEN_H / 22)*j + 320, (SCREEN_H / 22)*i + 180, 0);
				}
				else if (def[i][j] == 4) {
					al_draw_bitmap_region(tile, 64, 0, 32, 32, (SCREEN_H / 22)*j + 320, (SCREEN_H / 22)*i + 180, 0);
				}
				
				if (!key[W] && !key[A] && !key[S] && !key[D]) {
				
					al_draw_bitmap_region(bitmap, 0, 0, 32, 32, (SCREEN_H/22) * j + 320, (SCREEN_H/22)*i + 180, 0);
				}
				else if (key[W]) {
					
					al_draw_bitmap_region(bitmap, 0, 0, 32, 32, (SCREEN_H/22) * j + 320, (SCREEN_H/22)*i + 180, 0);
				}
				else if (key[A]) {
				
					al_draw_bitmap_region(bitmap, 0, 96, 32, 32, (SCREEN_H/22) * j + 320, (SCREEN_H/22)*i + 180, 0);
				}
				else if (key[S]) {
					
					al_draw_bitmap_region(bitmap, 0, 64, 32, 32, (SCREEN_H/22) * j + 320, (SCREEN_H/22)*i + 180, 0);
				}
				else if (key[D]) {
					
					al_draw_bitmap_region(bitmap, 0, 32, 32, 32, (SCREEN_H/22) * j + 320, (SCREEN_H/22)*i + 180, 0);
				}
				
			}
			if (mat[i][j] == 3) {
				al_draw_bitmap_region(tile, 96, 0, 32, 32, (SCREEN_H/22)*j+320, (SCREEN_H/22)*i+180, 0);
			}
			if (mat[i][j] == 4) {
				al_draw_bitmap_region(tile, 64, 0, 32, 32, (SCREEN_H/22)*j + 320, (SCREEN_H/22)*i + 180, 0);
			}
			if (mat[i][j] == 3 && def[i][j] == 4) {
				al_draw_bitmap_region(tile, 128, 0, 32, 32, (SCREEN_H / 22)*j + 320, (SCREEN_H / 22)*i + 180, 0);
			}

		}
		cout << endl;
	}
	char pas[5];
	char spinte[5];
	sprintf_s(pas, "%d", passi);
	sprintf_s(spinte, "%d", spin);
	al_draw_text(font, al_map_rgb(255, 255, 255), 50, 100, ALLEGRO_ALIGN_LEFT, "MOSSE: ");
	al_draw_text(font, al_map_rgb(255, 255, 255), 250, 100, ALLEGRO_ALIGN_LEFT, pas);
	al_draw_text(font, al_map_rgb(255, 255, 255), 50, 200, ALLEGRO_ALIGN_LEFT, "SPINTE: ");
	al_draw_text(font, al_map_rgb(255, 255, 255), 250, 200, ALLEGRO_ALIGN_LEFT, spinte);
	
	al_flip_display();
	cout << endl;
}

void Sokoban::move(bool tro, ALLEGRO_EVENT ev, ALLEGRO_BITMAP *bitmap, ALLEGRO_BITMAP *tile, ALLEGRO_FONT *font) {
	if (ev.type == ALLEGRO_EVENT_TIMER) {
		if (key[W]) {
			for (int i = 0; i < mat.size(); i++) {
				for (int j = 0; j < mat[i].size(); j++) {
					if (mat[i][j] == 1 && i > 0 && mat[i - 1][j] != 2) {
						if (mat[i - 1][j] == 3) {
							if (mat[i - 2][j] == 0 || mat[i - 2][j] == 4) {
								mat[i][j] = 0;
								mat[i - 1][j] = 1;
								mat[i - 2][j] = 3;
								spin++;
								tro = true;
								break;
							}
						}
						else {
							mat[i][j] = 0;
							mat[i - 1][j] = 1;
							tro = true;
							break;
						}
					}
				}
				if (tro) {
					passi++;
					stampa(bitmap, tile, font);
					break;
				}
			}

		}
		if (key[A]) {
			for (int i = 0; i < mat.size(); i++) {
				for (int j = 0; j < mat[i].size(); j++) {
					if (mat[i][j] == 1 && j > 0 && mat[i][j - 1] != 2) {
						if (mat[i][j - 1] == 3) {
							if (mat[i][j - 2] == 0 || mat[i][j - 2] == 4) {
								mat[i][j] = 0;
								mat[i][j - 1] = 1;
								mat[i][j - 2] = 3;
								spin++;
								tro = true;
								break;
							}
						}
						else {
							mat[i][j] = 0;
							mat[i][j - 1] = 1;
							tro = true;
							break;
						}
					}
				}
				if (tro) {
					passi++;
					stampa(bitmap, tile, font);
					break;
				}
			}

		}
		if (key[S]) {
			for (int i = 0; i < mat.size(); i++) {
				for (int j = 0; j < mat[i].size(); j++) {
					if (mat[i][j] == 1 && i < mat.size() && mat[i + 1][j] != 2) {
						if (mat[i + 1][j] == 3) {
							if (mat[i + 2][j] == 0 || mat[i + 2][j] == 4) {
								mat[i][j] = 0;
								mat[i + 1][j] = 1;
								mat[i + 2][j] = 3;
								spin++;
								tro = true;
								break;
							}
						}
						else {
							mat[i][j] = 0;
							mat[i + 1][j] = 1;
							tro = true;
							break;
						}

					}
				}
				if (tro) {
					passi++;
					stampa(bitmap, tile, font);
					break;
				}

			}

		}
		if (key[D]) {
			for (int i = 0; i < mat.size(); i++) {
				for (int j = 0; j < mat[i].size(); j++) {
					if (mat[i][j] == 1 && j < mat[i].size() && mat[i][j + 1] != 2) {
						if (mat[i][j + 1] == 3) {
							if (mat[i][j + 2] == 0 || mat[i][j + 2] == 4) {
								mat[i][j] = 0;
								mat[i][j + 1] = 1;
								mat[i][j + 2] = 3;
								spin++;
								tro = true;
								break;
							}
						}
						else {
							mat[i][j] = 0;
							mat[i][j + 1] = 1;
							tro = true;
							break;
						}
					}
				}
				if (tro) {
					passi++;
					stampa(bitmap, tile, font);
					break;
				}

			}
		}
		if (key[R]) {
			passi = 0;
			spin = 0;
			for (int i = 0; i < mat.size(); i++) {
				for (int j = 0; j < mat[i].size(); j++) {
					
						mat[i][j] = def[i][j];

				}
			}
			stampa(bitmap, tile, font);
		}
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_W:
			key[W] = true;
			break;

		case ALLEGRO_KEY_S:
			key[S] = true;
			break;

		case ALLEGRO_KEY_A:
			key[A] = true;
			break;

		case ALLEGRO_KEY_D:
			key[D] = true;
			break;

		case ALLEGRO_KEY_R:
			key[R] = true;
			break;
		case ALLEGRO_KEY_ESCAPE:
			key[ESC] = true;
			break;
		}
		
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_W:
			key[W] = false;
			break;

		case ALLEGRO_KEY_S:
			key[S] = false;
			break;

		case ALLEGRO_KEY_A:
			key[A] = false;
			break;

		case ALLEGRO_KEY_D:
			key[D] = false;
			break;

		case ALLEGRO_KEY_R:
			key[R] = false;
			break;
		case ALLEGRO_KEY_ESCAPE:
			key[ESC] = false;
		}
	}

}

void Sokoban::load() {
	if (level[0]) {
		map.open("map1.txt");
		def.resize(11);
		mat.resize(11);
		for (int i = 0; i < 11; i++) {
			def[i].resize(21);
			mat[i].resize(21);
		}

	}
	else if (level[1]) {
		map.open("map2.txt");
		def.resize(10);
		mat.resize(10);
		for (int i = 0; i < 10; i++) {
			def[i].resize(14);
			mat[i].resize(14);
		}
		
	}
	else if (level[2]) {
		map.open("map3.txt");
		def.resize(10);
		mat.resize(10);
		for (int i = 0; i < 10; i++) {
			def[i].resize(17);
			mat[i].resize(17);
		}
	}
	
	for (int i = 0; i < def.size(); i++) {
		for (int j = 0; j < def[i].size(); j++) {
			map >> def[i][j];
			mat[i][j] = def[i][j];
		}
	}
	map.close();
}