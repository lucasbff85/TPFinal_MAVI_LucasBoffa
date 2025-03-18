#pragma once
#include "stdafx.h"
#include "Start.h"
#include "End.h"

using namespace sf;

class Game {
	Start* _start;
	End* _end;
	Font _font;
	Text _text;
	int _puntos;
	int _vidas;
public:
	Game();
	void Play();
};
