#include "Nivel.h"
#include <iostream>

using namespace sf;
using namespace std;

Nivel::Nivel(){
	_wnd = new RenderWindow(VideoMode(1280, 1080), "Asteroids");
	size = Vector2u(_wnd->getSize().x, _wnd->getSize().y);
	_wnd->setFramerateLimit(120);
	_jugador = new Player(_wnd);
    deltaTime = 0;
}

Nivel::~Nivel(){

}

void Nivel::ProcesarEventos() {
	
    while (_wnd->isOpen())
    {
        sf::Event event;
        while (_wnd->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _wnd->close();
            }
			_jugador->ProcesarEventos();
            
        }

		deltaTime = _clock.restart().asMilliseconds();

        Actualizar();

        Dibujar();

    }
}


void Nivel::Actualizar() {
	//timer -= deltaTime;

    GenerarAsteroides();
	_jugador->Actualizar(size, deltaTime);

    for (int i = 0; i < asteroides.size(); i++)
    {
        asteroides[i].Actualizar(deltaTime,size);

        //  DETECCIÓN DE COLISIÓN 
        if (_jugador->GetSprite().getGlobalBounds().intersects(asteroides[i].GetSprite().getGlobalBounds())) {
            cout << "COLISION DETECTADA " << endl;
            _vidas--;
            _jugador->Iniciar(_wnd);

            if (asteroides[i].Esta_Vivo())
            {
                asteroides[i].Romperse(asteroides, size);
                asteroides.erase(asteroides.begin() + i); // Eliminar asteroide original
                i--; // Ajustar índice después de eliminar
            }
        }


       
    }

}


void Nivel::GenerarAsteroides() {
    if (asteroides.size() < 6) { // Límite de asteroides en pantalla
        int cantidad = rand() % 2 + 1; // Agregar 1 o 2 asteroides
        for (int i = 0; i < cantidad; i++) {
            Asteroide nuevoAsteroide;
            nuevoAsteroide.Iniciar(size); // Método que debes definir en Asteroide.cpp
            asteroides.push_back(nuevoAsteroide);

            // Debug: Mostrar posición en consola
            Vector2f pos = nuevoAsteroide.sprite_asteroide.getPosition();
            cout << "Asteroide creado en: " << pos.x << ", " << pos.y << endl;
        }
    }
}

void Nivel::Dibujar() {

	_wnd->clear();

    if (_jugador->EstaVivo()) {
        _jugador->Dibujar(_wnd);
    }
	

    for (int i = 0; i < asteroides.size(); i++)
        {
            if (asteroides[i].Esta_Vivo())
            {
                asteroides[i].Dibujar(_wnd);
            }
        }

	_wnd->display();
}

int Nivel::GetVidas() {
    return _vidas;
}





