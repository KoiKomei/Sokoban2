#include "Sokoban.h"

Sokoban::Sokoban() {
	
	bitmap = al_load_bitmap("yukki.png");
	tile = al_load_bitmap("tilesheet1.png");
	bgm = al_load_sample("Gameplay.ogg");
	passi = 0;
	spin = 0;
	tot.resize(2);
	tot[0] = passi;
	tot[1] = spin;

}

void Sokoban::gioca(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_FONT *font) {
	al_install_keyboard();
	al_register_event_source(queue, al_get_keyboard_event_source());
	level[0] = true;
	al_play_sample(bgm, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	bool done = false;
	load();
	
	stampa(font);
	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(queue, &ev);
		
		bool tro = false;
		if (key[ESC]) {
			key[ESC] = false;
			passi = 0;
			spin = 0;
			tot[0] = 0;
			tot[1] = 0;
			level[0] = false;
			level[1] = false;
			level[2] = false;
			done = true;
			break;

		}
	
		move(tro, ev, font);
		
		int cont = 0;
		for (unsigned i = 0; i < mat.size(); i++) {
			for (unsigned j = 0; j < mat[i].size(); j++) {
				
					if (mat[i][j] == 3 && def[i][j] == 4) {
						cont++;
					}
				
			}
		}
		if (cont == 6 && level[0]) {
			al_draw_text(font, al_map_rgb(255, 0, 0), 640, 600, ALLEGRO_ALIGN_CENTRE, "PRIMO LIVELLO SUPERATO");
			al_flip_display();
	
			al_rest(2.0f);
			
			passi = 0;
			spin = 0;
			level[0] = false;
			level[1] = true;
			load();
			stampa(font);
		}
		else if(cont==10 && level[1]){
			al_draw_text(font, al_map_rgb(255, 0, 0), 640, 600, ALLEGRO_ALIGN_CENTRE, "SECONDO LIVELLO SUPERATO");
			al_flip_display();
			al_rest(2.0f);
			passi = 0;
			spin = 0;
			level[1] = false;
			level[2] = true;
			load();
			stampa(font);
		}
		else if (cont ==11 && level[2]) {
			al_draw_text(font, al_map_rgb(255, 0, 0), 640, 600, ALLEGRO_ALIGN_CENTRE, "COMPLIMENTI, HAI FINITO TUTTI I LIVELLI");
			al_flip_display();
			ifstream record("record.txt");
			int score[2] = { 0 };
			for (int i = 1; i < 3; i++) {
				record >> score[i-1];
				
			}
			record.close();
			
			if (tot[0] < score[0]) {
				ofstream rec("record.txt");
				
				rec << tot[0]<<endl;
				rec << tot[1];
				rec.close();
			}
			
			tot[0] = 0;
			tot[1] = 0;
			passi = 0;
			spin = 0;
			al_rest(4.0f);
			level[2] = false;
			done = true;
		}

	}
	
	al_stop_samples();
	al_uninstall_keyboard();
}

void Sokoban::stampa(ALLEGRO_FONT *font) {
	al_clear_to_color(al_map_rgb(0,0,0));
	
	for (unsigned i = 0; i < mat.size(); i++) {
		for (unsigned j = 0; j < mat[i].size(); j++) {
		
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
				
					al_draw_bitmap_region(bitmap, 0, 64, 32, 32, (SCREEN_H/22) * j + 320, (SCREEN_H/22)*i + 180, 0);
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
		
	}
	char pas[256];
	char spinte[256];
	char totpas[256];
	char totspin[256];
	snprintf(pas,sizeof(pas), "%d", passi);
	snprintf(spinte, sizeof(spinte), "%d", spin);
	snprintf(totpas, sizeof(totpas), "%d", tot[0]);
	snprintf(totspin, sizeof(totspin), "%d", tot[1]);
	al_draw_text(font, al_map_rgb(255, 255, 255), 20, 0, ALLEGRO_ALIGN_LEFT, "MOSSE: ");
	al_draw_text(font, al_map_rgb(255, 255, 255), 160, 0, ALLEGRO_ALIGN_LEFT, pas);
	al_draw_text(font, al_map_rgb(255, 255, 255), 20, 100, ALLEGRO_ALIGN_LEFT, "MOSSE TOT: ");
	al_draw_text(font, al_map_rgb(255, 255, 255), 240, 100, ALLEGRO_ALIGN_LEFT, totpas);
	al_draw_text(font, al_map_rgb(255, 255, 255), 20, 50, ALLEGRO_ALIGN_LEFT, "SPINTE: ");
	al_draw_text(font, al_map_rgb(255, 255, 255), 160, 50, ALLEGRO_ALIGN_LEFT, spinte);
	al_draw_text(font, al_map_rgb(255, 255, 255), 20, 150, ALLEGRO_ALIGN_LEFT, "SPINTE TOT: ");
	al_draw_text(font, al_map_rgb(255, 255, 255), 240, 150, ALLEGRO_ALIGN_LEFT, totspin);
	al_draw_text(font, al_map_rgb(255, 0, 0), 970, 0, ALLEGRO_ALIGN_LEFT, "ISTRUZIONI");
	al_draw_text(font, al_map_rgb(255, 255, 255), 900, 50, ALLEGRO_ALIGN_LEFT, "WASD MOVIMENTO");
	al_draw_text(font, al_map_rgb(255, 255, 255), 970, 100, ALLEGRO_ALIGN_LEFT, "ESC MENU'");
	al_draw_text(font, al_map_rgb(255, 255, 255), 960, 150, ALLEGRO_ALIGN_LEFT, "R RESTART");
	
	al_flip_display();

}

void Sokoban::move(bool tro, ALLEGRO_EVENT ev, ALLEGRO_FONT *font) {
	if (ev.type == ALLEGRO_EVENT_TIMER) {
		if (key[W]) {
			for (unsigned i = 0; i < mat.size(); i++) {
				for (unsigned j = 0; j < mat[i].size(); j++) {
					if (mat[i][j] == 1 && i > 0 && mat[i - 1][j] != 2) {
						if (mat[i - 1][j] == 3) {
							if (mat[i - 2][j] == 0 || mat[i - 2][j] == 4) {
								mat[i][j] = 0;
								mat[i - 1][j] = 1;
								mat[i - 2][j] = 3;
								spin++;
								tot[1]++;
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
					tot[0]++;
					stampa(font);
					break;
				}
			}

		}
		if (key[A]) {
			for (unsigned i = 0; i < mat.size(); i++) {
				for (unsigned j = 0; j < mat[i].size(); j++) {
					if (mat[i][j] == 1 && j > 0 && mat[i][j - 1] != 2) {
						if (mat[i][j - 1] == 3) {
							if (mat[i][j - 2] == 0 || mat[i][j - 2] == 4) {
								mat[i][j] = 0;
								mat[i][j - 1] = 1;
								mat[i][j - 2] = 3;
								spin++;
								tot[1]++;
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
					tot[0]++;
					stampa(font);
					break;
				}
			}

		}
		if (key[S]) {
			for (unsigned i = 0; i < mat.size(); i++) {
				for (unsigned j = 0; j < mat[i].size(); j++) {
					if (mat[i][j] == 1 && i < mat.size() && mat[i + 1][j] != 2) {
						if (mat[i + 1][j] == 3) {
							if (mat[i + 2][j] == 0 || mat[i + 2][j] == 4) {
								mat[i][j] = 0;
								mat[i + 1][j] = 1;
								mat[i + 2][j] = 3;
								spin++;
								tot[1]++;
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
					tot[0]++;
					stampa(font);
					break;
				}

			}

		}
		if (key[D]) {
			for (unsigned i = 0; i < mat.size(); i++) {
				for (unsigned j = 0; j < mat[i].size(); j++) {
					if (mat[i][j] == 1 && j < mat[i].size() && mat[i][j + 1] != 2) {
						if (mat[i][j + 1] == 3) {
							if (mat[i][j + 2] == 0 || mat[i][j + 2] == 4) {
								mat[i][j] = 0;
								mat[i][j + 1] = 1;
								mat[i][j + 2] = 3;
								spin++;
								tot[1]++;
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
					tot[0]++;
					passi++;
					stampa(font);
					break;
				}

			}
		}
		if (key[R]) {
			tot[0] -= passi;
			tot[1] -= spin;
			passi = 0;
			spin = 0;
			for (unsigned i = 0; i < mat.size(); i++) {
				for (unsigned j = 0; j < mat[i].size(); j++) {
					
						mat[i][j] = def[i][j];

				}
			}
			stampa(font);
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
			
			break;
		}
	}

}

void Sokoban::load() {
	if (level[0]) {
		map.open("map1.txt");
		def.resize(11);
		mat.resize(11);
		for (unsigned i = 0; i < 11; i++) {
			def[i].resize(21);
			mat[i].resize(21);
		}

	}
	else if (level[1]) {
		map.open("map2.txt");
		def.resize(10);
		mat.resize(10);
		for (unsigned i = 0; i < 10; i++) {
			def[i].resize(14);
			mat[i].resize(14);
		}
		
	}
	else if (level[2]) {
		map.open("map3.txt");
		def.resize(10);
		mat.resize(10);
		for (unsigned i = 0; i < 10; i++) {
			def[i].resize(17);
			mat[i].resize(17);
		}
	}
	
	for (unsigned i = 0; i < def.size(); i++) {
		for (unsigned j = 0; j < def[i].size(); j++) {
			map >> def[i][j];
			mat[i][j] = def[i][j];
		}
	}
	map.close();
}