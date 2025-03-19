#pragma once
#include <SFML/Window.hpp>
#include <SFML/graphics.hpp>
#include "Disparo.h"

using namespace std;
using namespace sf;

class Player {
	Texture tex_nave;
	Sprite sprite_nave;
	SoundBuffer _soundbuffer;
	Sound _sound;

	float x_dir;
	float y_dir;
	vector<Disparo> proyectiles;


	bool play_thrust;
	bool play_one = false;
	bool esta_vivo;

	float aceleracion = 0.2f;
	float velocidadRotacion = 3.0f;
	float velocidadMaxima = 4.0f;
	float friccion = 0.99f;;
	int v_move, h_move;





	float acceleration = 1.75f;
	float rotateSpeed = 0.3f;
	Vector2f max_velocity = Vector2f(2.5f, 2.5f);
	Vector2f velocity;
	Vector2f u_velocity;

	



	Vector2f velocidad;
	Vector2f u_velocidad;
	float mag;

public:
	Player(RenderWindow* wnd);
	~Player();
	void Iniciar(RenderWindow* wnd);
	bool EstaVivo();
	void Morir();
	void Dibujar(sf::RenderWindow* wnd);
	void ProcesarEventos();
	void Actualizar(Vector2u size, float deltaTime);
	void ManejarBordes(Vector2u size);
	void MovePlay();
	void MoveStop();
	void Posicionar(Vector2u posicion);
	Sprite& GetSprite();
};




