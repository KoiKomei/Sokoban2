#pragma once
#ifndef SOKOBAN_H
#define SOKOBAN_H
#define _CRT_SECURE_NO_WARNINGS
#include "allegro5/allegro_primitives.h"
#include "allegro5/keyboard.h"
#include "allegro5/bitmap.h"
#include "allegro5/allegro_image.h"
#include <vector>
#include "Menu.h"
const int SCREEN_W = 1280;
const int SCREEN_H = 720;
enum KEYS { W, A, S, D , R, ESC};

class Sokoban {

private:
	ALLEGRO_BITMAP * bitmap;
	ALLEGRO_BITMAP *tile;
	ALLEGRO_SAMPLE * bgm;
	vector<vector<int>> mat;
	vector<vector<int>> def;
	ifstream map;
	bool key[6] = { false, false, false, false, false, false };
	bool level[3] = { false, false, false };
	int passi;
	int spin;
	vector<int> tot;


public:
	Sokoban();
	void gioca(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_FONT *font);
	void stampa(ALLEGRO_FONT *font);
	void move(bool tro, ALLEGRO_EVENT ev, ALLEGRO_FONT *font);
	void load();
};

#endif // !SOKOBAN_H

