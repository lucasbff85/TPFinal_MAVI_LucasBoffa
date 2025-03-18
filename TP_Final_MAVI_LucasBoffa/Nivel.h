#pragma once
#include "stdafx.h"
#include "Player.h"
#include "vector"


using namespace std;
using namespace sf;


class Nivel {
	Player* _jugador;
	RenderWindow* _wnd;
	Clock _clock;
	float timeBetweenShots = 200.f;
	float deltaTime;
	//float timer;
	

	const float acceleration = 1.75f;
	const Vector2f max_velocity = Vector2f(2.5f, 2.5f);
	const float rotateSpeed = 0.3f;


public:
	Vector2i size;
	Nivel();
	~Nivel();
	void ProcesarEventos();
	void Actualizar();
	void Dibujar();
};
