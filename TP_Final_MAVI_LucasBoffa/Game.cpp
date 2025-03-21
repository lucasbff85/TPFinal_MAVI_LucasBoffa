#include "Game.h"


Game::Game() {
	_end = new End();
	_nivel = new Nivel();
	_start = new Start();
	bool _jugando = true;
	_puntos = 0;
}

void Game::Play() {
	_start->Loop();
	_nivel->Iniciar();
	_puntos = _nivel->GetPuntos();
	_end->SetPuntos(_puntos);
	_end->Loop();
	_jugando = _end->GetReiniciar();
	while (_jugando) {
		_jugando = false;
		_nivel->Iniciar();
		_puntos = _nivel->GetPuntos();
		_end->SetPuntos(_puntos);
		_end->Loop();
		_jugando = _end->GetReiniciar();
	}
	
}
