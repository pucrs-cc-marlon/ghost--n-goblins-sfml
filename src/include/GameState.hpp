/*
* Nome: Marlon Baptista de Quadros
*/
#include "Game.hpp"

#ifndef GAME_STATE_H_
#define GAME_STATE_H_
namespace cgf{
	class GameState
	{
		public:

		virtual void init(cgf::Game* game) = 0;
		virtual void cleanup() = 0;

		virtual void pause() = 0;
		virtual void resume() = 0;

		virtual void handleEvents(cgf::Game* game) = 0;
		virtual void update(cgf::Game* game) = 0;
		virtual void draw(cgf::Game* game) = 0;

		void changeState(cgf::Game* game, cgf::GameState* state) {
			game->changeState(state);
		}

		protected:

		GameState() { }
	};
}
#endif