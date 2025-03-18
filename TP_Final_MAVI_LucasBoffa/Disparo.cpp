#include "Disparo.h"
#include "iostream"
#include "stdafx.h"

using namespace sf;

Disparo::Disparo(Vector2f pos, Vector2f dir) {
    bala.setRadius(3);
    bala.setFillColor(sf::Color::White);
    bala.setPosition(pos);
    direccion = dir;
}

void Disparo::Actualizar() {
    bala.move(direccion * velocidad);
}

void Disparo::Dibujar(RenderWindow* wnd) {
    wnd->draw(bala);
}