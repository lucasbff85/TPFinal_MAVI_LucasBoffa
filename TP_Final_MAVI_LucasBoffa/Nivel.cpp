#include "Nivel.h"

using namespace sf;
using namespace std;

Nivel::Nivel(){
	_wnd = new RenderWindow(VideoMode(1280, 1080), "Asteroids");
	size = Vector2i(_wnd->getSize().x, _wnd->getSize().y);
	_wnd->setFramerateLimit(120);
	_jugador = new Player();
	_jugador->Posicionar(Vector2i(_wnd->getSize().x / 2, _wnd->getSize().y / 2));
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
	_jugador->Actualizar(size, deltaTime);

}

void Nivel::Dibujar() {

	_wnd->clear();

	_jugador->Dibujar(_wnd);

	_wnd->display();
}





