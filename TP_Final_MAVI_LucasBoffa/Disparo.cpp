#include "Disparo.h"
#include "iostream"
#include "stdafx.h"

using namespace sf;

Disparo::Disparo() {
    _bala.setRadius(3);
    _bala.setFillColor(sf::Color::White);
    _tiempoVida = 3.0f;
    _velocidad = 20.0f;
    _direccion = Vector2f(0, 0); // Inicializar dirección
}
Disparo::~Disparo() {

}


void Disparo::Iniciar(Vector2f posicion, float angulo) {
   // Calcular la dirección
    _direccion.x = -cos(angulo * 3.14159f / 180.0f);
    _direccion.y = -sin(angulo * 3.14159f / 180.0f);

    // Ajustar la posición inicial de la bala
    posicion.x += 14.f * _direccion.x; // Mover la bala un poco hacia adelante
    posicion.y += 14.f * _direccion.y;
    _bala.setPosition(posicion);


    _estaVivo = true;
    _tiempoRestante = _tiempoVida * 1000.f; // Convertir a milisegundos
}



void Disparo::Actualizar(float deltaTime) {

    if (!_estaVivo) return;

    _tiempoRestante -= deltaTime;
    if (_tiempoRestante <= 0)
    {
        Morir();
        return;
    }


    Vector2f distancia = _direccion * _velocidad * deltaTime / 100.f;


    _bala.move(distancia);
}

void Disparo::Dibujar(RenderWindow* wnd) {
    wnd->draw(_bala);
}

void Disparo::Morir() {
    _estaVivo = false;
}

bool Disparo::Esta_Vivo() {
    return _estaVivo;
}