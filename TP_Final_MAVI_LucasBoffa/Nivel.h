#pragma once
#include "stdafx.h"
#include "Player.h"
#include <vector>
#include "Asteroide.h"
#include "Disparo.h"


using namespace std;
using namespace sf;


class Nivel {
	Player* _jugador;
	bool puedeDisparar;
	RenderWindow* _wnd;
	Clock _clock;
	float tiempoEntreDisparos;
	float deltaTime;
	int _vidas;
	int _puntos;
	SoundBuffer _sonidoDisparo, _explosion1, _explosion2, _explosion3, _bufferMusica;

	Sound _sonidoBala, _sonidoAsteroide1, _sonidoAsteroide2, _sonidoAsteroide3, _soundMusica;
	
	float timer;
	Font _fuente;
	Text _textoPuntos, _textoVidas;

	const float acceleration = 1.75f;
	const Vector2f max_velocity = Vector2f(2.5f, 2.5f);
	const float rotateSpeed = 0.3f;
	vector<Asteroide> asteroides;
	vector<Disparo> balas;

public:
	Vector2u size;
	Nivel();
	~Nivel();
	void Iniciar();
	void ProcesarEventos();
	void Actualizar();
	void Dibujar();
	void MoverAsteroidesAparte(Asteroide& asteroide1, Asteroide& asteroide2);
	void CambiarDireccionAsteroide(Asteroide& asteroide);
	void GenerarAsteroides();
	int GetVidas();
	int GetPuntos();
	void ReproducirExplosion(int nivel);
	void ActualizarPuntos();
	void ActualizarVidas();
	void PlayMusic();
};
