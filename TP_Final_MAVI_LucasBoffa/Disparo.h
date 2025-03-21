#pragma once
#include "stdafx.h"

using namespace sf;

class Disparo {
    
    Vector2f _direccion;
    float _velocidad;
    float _tiempoVida;
    float _tiempoRestante;
    bool _estaVivo;
    sf::Vector2f size;
    sf::Vector2f posicion;
    sf::Vector2f direccion;
	
public:
    CircleShape _bala;
    Disparo();
    ~Disparo();
    void Iniciar(Vector2f pos, float angulo);
    void Actualizar(float deltaTime);
    void Morir();
    void Dibujar(RenderWindow* wnd);
    bool Esta_Vivo();
};