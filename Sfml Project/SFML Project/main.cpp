#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Game.hpp"
#include "Player.hpp"
#include "Menu.hpp"
#include <crtdbg.h>
#include <iostream>

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	bool gameStart = false;
	float highScore[6] = { 0, 0, 0, 0, 0, 0 };
	sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
	sf::View player_view(sf::FloatRect(0, 0, 1200, 800));

	Game *game;

	sf::Clock gameTime;

	Menu menu((float)window.getSize().x, (float)window.getSize().y);
	menu.highScoreRead(highScore);

	sf::Music music;
	music.openFromFile("Resources/GameMusic.wav");
	music.play();
	music.setLoop(true);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//kollar om du rör dig upp eller ner i menyn
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Up)){
				menu.moveUp();
			}
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Down)){
				menu.moveDown();
			}
			//om du trycker på escape så kommer du till första sidan i menyn
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape)){
				menu.setIndex(0);
			}
			//om du klicker på enter över ett visst val i menyn
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Return)){
				if (menu.getIndex() == 3){
					game = new Game("easy");
					gameStart = true;
				}
				if (menu.getIndex() == 4){
					game = new Game("medium");
					gameStart = true;
				}
				if (menu.getIndex() == 5){
					game = new Game("hard");
					gameStart = true;
				}
				if (menu.getIndex() == 0){
					menu.setIndex(3);
				}
				if (menu.getIndex() == 1){
					menu.setIndex(6);
				}
				if (menu.getIndex() == 2){
					window.close();
				}
				
			}
				
			if (event.type == sf::Event::Closed)
				window.close();
		}
		 
		//om du starta ett game så blir gamestart sann och jag börjar uppdatera spelet
		if (gameStart == true){
			game->Update(gameTime.restart().asSeconds(), highScore);
			window.clear();
			player_view.setCenter(game->getPlayerPosition());
			game->cameraFollow(player_view);
			window.setView(player_view);
			window.draw(*game);
			window.display();
			//om du spelar klart spelet så uppdaterar jag din highscore
			if (game->gameEnd() == true){
				menu.selectionSort(highScore, 6);
				menu.highScoreWrite(highScore);
				delete[]game;
				gameStart = false;
				menu.setIndex(0);
			}
		}
		//om du är i menyn så är gamestart false och jag uppdaterar bara menyn
		if (gameStart == false){
			window.clear();
			player_view.setCenter(sf::Vector2f(600, 400));
			window.setView(player_view);
			menu.draw(window);
			window.display();
		}
	}
	//om du skulle trycka ner spelet mitt å så delatar jag fortfarande spelet
	if (gameStart == true){
		delete[]game;
	}
	
	return 0;
}