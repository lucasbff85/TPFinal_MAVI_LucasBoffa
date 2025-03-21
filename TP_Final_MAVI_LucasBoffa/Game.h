#pragma once
#include "stdafx.h"
#include "Start.h"
#include "End.h"
#include "Nivel.h"

using namespace sf;

class Game {
	Start* _start;
	End* _end;
	Nivel* _nivel;
	Font _font;
	Text _text;
	int _puntos;
	bool _jugando;
public:
	Game();
	void Play();
};
