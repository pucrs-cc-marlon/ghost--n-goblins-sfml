/*
* Nome: Marlon Baptista de Quadros
*/
#include "include/FirstMap.hpp"
#include "include/InputManager.hpp"
#include <iostream>

namespace cgf{

	FirstMap FirstMap::m_FirstMap;

	void FirstMap::init(cgf::Game* game){
		im = cgf::InputManager::instance();
		im->addKeyInput("left", sf::Keyboard::Left);
    	im->addKeyInput("right", sf::Keyboard::Right);

		window = game->getWindow();

		player = new Player("assets/hero.png", 50, window->getSize().y-50, 1, 10);
		playerXML = new Player("assets/hero1.xml", "assets/heroAnim1.xml");
	}

	void FirstMap::handleEvents(cgf::Game* game){
		sf::Event event;
    	// sf::View view = screen->getView();

		while (window->pollEvent(event)){
			if(event.type == sf::Event::Closed)
				game->close();
    	}
		if(im->testEvent("right"))
			player->move(0.1f, 0.f);
		if(im->testEvent("left"))
			player->move(-0.1f, 0.f);
	}

	void FirstMap::update(cgf::Game* game){

	}

	void FirstMap::draw(cgf::Game* game){
		window->clear(sf::Color(0,0,0));
		player->draw(window);
	}

	void FirstMap::cleanup(){

	}

	void FirstMap::pause(){

	}

	void FirstMap::resume(){

	}

}