/*
* Nome: Marlon Baptista de Quadros
*/
#ifndef GAME_MAIN_H_
#define GAME_MAIN_H_
#include "Main.hpp"
#include <stack>

namespace cgf{
	class GameState;
	class Game{
		public:
			Game(unsigned int minFPS, unsigned int maxFPS);
			virtual void init(std::string title, unsigned int height, unsigned int width, bool fullScreen);
			virtual void changeState(cgf::GameState* state);
			virtual void handleEvents();
			virtual void update();
			virtual void draw();
			virtual void clean();
			bool isRunning(){ return running; };
			void close() { running = false; };
			sf::RenderWindow* getWindow() { return window; }

		private:
			sf::RenderWindow* window;
			sf::View view;
        	bool running;
			unsigned int minFPS;
			unsigned int maxFPS;
			std::string title;
			std::stack<GameState*> states;
			unsigned int height;
			unsigned int width;
			bool fullScreen;
			sf::Clock gameClock;
			double updateInterval;
			double maxCyclesPerFrame;
			double lastFrameTime;
			double cyclesLeftOver;
	};
}
#endif