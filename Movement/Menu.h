#pragma once
#ifndef MENU_H
#define MENU_H
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <iostream>
using namespace std;
class Menu {

private:


public:
	Menu() {};
	void inizio(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, bool &done);



};
#endif // !MENU_H
