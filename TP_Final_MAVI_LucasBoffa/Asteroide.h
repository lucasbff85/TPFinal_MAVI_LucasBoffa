#pragma once
#include "stdafx.h"
#include <vector>
#include <map>

using namespace sf;
using namespace std;


class Asteroide {
	static std::map<int, sf::Texture> texturas;  // Almacena todas las texturas
	bool esta_vivo;
	float velocidad;
	float angulo;
	Vector2f direccion;
	int nivel;

public:
	Sprite sprite_asteroide;
	Asteroide();
	~Asteroide();
	void Iniciar(Vector2u size);
	void ManejarBordes(Vector2u size);
	bool Esta_Vivo() const;
	float Obtener_Angulo() const;
	void Romperse(std::vector<Asteroide>& asteroides, Vector2u size);
	void Actualizar(float deltaTime, Vector2u size);
	void Dibujar(RenderWindow* wnd);
	Vector2f Aparecer(Vector2u size);
	Sprite& GetSprite();
	void Desprenderse(Vector2f posicion);

};
