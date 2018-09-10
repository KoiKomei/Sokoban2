#pragma once
#ifndef SOKOBAN_H
#define SOKOBAN_H
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/keyboard.h"
#include "allegro5/bitmap.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/mouse.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "Menu.h"
using namespace std;
const int SCREEN_W = 1280;
const int SCREEN_H = 720;
enum KEYS { W, A, S, D , R, ESC};

class Sokoban {

private:
	vector<vector<int>> mat;
	vector<vector<int>> def;
	ifstream map;
	bool key[6] = { false, false, false, false, false, false };
	bool level[3] = { true, false, false };
	int passi = 0;
	int spin = 0;

public:
	Sokoban() {};
	void gioca(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_BITMAP *bitmap, ALLEGRO_BITMAP *tile, ALLEGRO_FONT *font);
	void stampa(ALLEGRO_BITMAP *bitmap, ALLEGRO_BITMAP *tile, ALLEGRO_FONT *font);
	void move(bool tro, ALLEGRO_EVENT ev, ALLEGRO_BITMAP *bitmap, ALLEGRO_BITMAP *tile, ALLEGRO_FONT *font);
	void load();
};

#endif // !SOKOBAN_H

