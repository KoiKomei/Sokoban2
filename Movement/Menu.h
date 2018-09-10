#pragma once
#ifndef MENU_H
#define MENU_H
#include <fstream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include <iostream>
using namespace std;
class Menu {

private:
	ALLEGRO_SAMPLE * bgm;
	ALLEGRO_EVENT_QUEUE *menu;
	ALLEGRO_BITMAP *bitmap;
	ifstream score;

public:
	Menu();
	void inizio(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, bool &done);



};
#endif // !MENU_H
