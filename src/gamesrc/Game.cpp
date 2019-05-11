#include "include/Game.hpp"
#include "include/GameState.hpp"

namespace cgf
{
	using namespace std;

	Game::Game(unsigned int minFPS, unsigned int maxFPS){
		this->minFPS = minFPS;
		this->maxFPS = maxFPS;
	}

	void Game::init(std::string title, unsigned int height, unsigned int width, bool fullScreen){
		this->height = height;
		this->width = width;
		this->window = new sf::RenderWindow(sf::VideoMode(width, height), title);
		this->view = window->getView();
		this->fullScreen = fullScreen;
		running = true;

		cout << "Game Started!" << endl;
	}

	void Game::changeState(cgf::GameState* state){
		if ( !states.empty() ) {
			states.top()->cleanup();
			states.pop();
		}

		states.push(state);
		states.top()->init(this);
	}

	void Game::handleEvents(){
		states.top()->handleEvents(this);
	}

	void Game::update(){
		double currentTime, updateIterations;

		currentTime = gameClock.getElapsedTime().asMilliseconds();
		updateIterations = ((currentTime - lastFrameTime) + cyclesLeftOver);

		if (updateIterations > maxCyclesPerFrame * updateInterval) {
			updateIterations = maxCyclesPerFrame * updateInterval;
		}

		// int cont = 1;
		while(updateIterations > updateInterval) {
			updateIterations -= updateInterval;
			//cout << "updating " << cont++ << endl;
			if ( !states.empty() )
				states.top()->update(this);
		}
		cyclesLeftOver = updateIterations;
		lastFrameTime = currentTime;
	}

	void Game::draw(){
		window->clear();
		// clock.beginFrame();
		states.top()->draw(this);

		window->display();
		// clock.endFrame();
	}
	void Game::clean(){
		this->window->clear();
	}
} // cgf
