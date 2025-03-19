#pragma once
#include "stdafx.h"
#include "Player.h"
#include <vector>
#include "Asteroide.h"


using namespace std;
using namespace sf;


class Nivel {
	Player* _jugador;
	RenderWindow* _wnd;
	Clock _clock;
	float timeBetweenShots = 200.f;
	float deltaTime;
	int _vidas = 3;
	//float timer;
	

	const float acceleration = 1.75f;
	const Vector2f max_velocity = Vector2f(2.5f, 2.5f);
	const float rotateSpeed = 0.3f;
	vector<Asteroide> asteroides;

public:
	Vector2u size;
	Nivel();
	~Nivel();
	void ProcesarEventos();
	void Actualizar();
	void Dibujar();
	void GenerarAsteroides();
	int GetVidas();
};
