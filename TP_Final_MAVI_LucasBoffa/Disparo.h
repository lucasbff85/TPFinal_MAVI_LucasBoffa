#pragma once
#include "stdafx.h"

using namespace sf;

class Disparo {
    CircleShape bala;
    Vector2f direccion;
    float velocidad = 5.0f;
	
public:
    
    Disparo(Vector2f pos, Vector2f dir);
    void Actualizar();
    void Dibujar(RenderWindow* wnd);
};