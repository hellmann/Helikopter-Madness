#include "Menu.hpp"
#include "SFML\Audio.hpp"
#include <fstream>
#include <sstream>


Menu::Menu(float width, float height){
	this->font.loadFromFile("Resources/arial.ttf");
	//dessa är mina olika meny texter
	this->menu[0].setFont(font);
	this->menu[0].setColor(sf::Color::Red);
	this->menu[0].setString("Play");
	this->menu[0].setPosition(sf::Vector2f((width / 2)-20, height / (3 + 1) * 1));

	this->menu[1].setFont(font);
	this->menu[1].setColor(sf::Color::White);
	this->menu[1].setString("HighScore");
	this->menu[1].setPosition(sf::Vector2f((width / 2) - 60, height / (3 + 1) * 2));

	this->menu[2].setFont(font);
	this->menu[2].setColor(sf::Color::White);
	this->menu[2].setString("Exit");
	this->menu[2].setPosition(sf::Vector2f((width / 2) - 20, height / (3 + 1) * 3));

	this->menu[3].setFont(font);
	this->menu[3].setColor(sf::Color::Red);
	this->menu[3].setString("Easy");
	this->menu[3].setPosition(sf::Vector2f((width / 2) - 20, height / (3 + 1) * 1));

	this->menu[4].setFont(font);
	this->menu[4].setColor(sf::Color::White);
	this->menu[4].setString("Medium");
	this->menu[4].setPosition(sf::Vector2f((width / 2) - 40, height / (3 + 1) * 2));

	this->menu[5].setFont(font);
	this->menu[5].setColor(sf::Color::White);
	this->menu[5].setString("Hard");
	this->menu[5].setPosition(sf::Vector2f((width / 2) - 20, height / (3 + 1) * 3));

	this->menu[6].setFont(font);
	this->menu[6].setColor(sf::Color::Red);
	this->menu[6].setString("HighScore");
	this->menu[6].setPosition(sf::Vector2f((width / 2) - 60, height / (4 + 1) * 1));

	this->menu[7].setFont(font);
	this->menu[7].setColor(sf::Color::White);
	
	this->menu[7].setPosition(sf::Vector2f((width / 2), height / (5 + 1) * 2));

	this->index = 0;
}


Menu::~Menu(){

}
//en funktion som ändrar färg på texten om du klickar uppåt 
void Menu::moveUp(){
	if (this->index -1 >= 0 && this->index<3){
		this->menu[this->index].setColor(sf::Color::White);
		this->index--;
		this->menu[this->index].setColor(sf::Color::Red);
	}
	if (this->index - 1 >= 3 && this->index<=5){
		this->menu[this->index].setColor(sf::Color::White);
		this->index--;
		this->menu[this->index].setColor(sf::Color::Red);
	}
}
//en funktion som ändrar färg på texten om du klickar neråt
void Menu::moveDown(){
	if (this->index +1 < 3){
		this->menu[this->index].setColor(sf::Color::White);
		this->index++;
		this->menu[this->index].setColor(sf::Color::Red);
	}
	if (this->index + 1 <= 5&& this->index>=3){
		this->menu[this->index].setColor(sf::Color::White);
		this->index++;
		this->menu[this->index].setColor(sf::Color::Red);
	}
}

int Menu::getIndex()const{
	return this->index;
}
void Menu::setIndex(const int index){
	this->index = index;
	this->updateColor();
}
void Menu::updateColor(){
	this->menu[0].setColor(sf::Color::Red);
	this->menu[1].setColor(sf::Color::White);
	this->menu[2].setColor(sf::Color::White);
	this->menu[3].setColor(sf::Color::Red);
	this->menu[4].setColor(sf::Color::White);
	this->menu[5].setColor(sf::Color::White);
	this->menu[6].setColor(sf::Color::Red);
}

void Menu::draw(sf::RenderWindow &window)const{
	if (this->index <= 2 && this->index >= 0){
		for (int i = 0; i < 3; i++){
			window.draw(this->menu[i]);
		}
	}
	if (this->index <= 5 && this->index >= 3){
		for (int i = 3; i < 6; i++){
			window.draw(this->menu[i]);
		}
	}
	if (this->index <= 6 && this->index >= 6){
		window.draw(this->menu[6]);
		window.draw(this->menu[7]);
	}
	
}
//här skriver jag ut higscore listan
void Menu::setHighScore(float arr[]){
	std::stringstream highScore;
	highScore << "1. " << arr[0] << std::endl << "2. " << arr[1] << std::endl << "3. " << arr[2]
		<< std::endl << "4. " << arr[3] << std::endl << "5. " << arr[4];
	this->menu[7].setString(highScore.str().c_str());
}
//läser highscoren från fil
bool Menu::highScoreRead(float arr[]){
	bool input = false;
	std::ifstream readFromFile("Resources/highscore.txt", std::ios::in);
	if (readFromFile.is_open()){
		int nr = 5;
		for (int i = 0; i < nr; i++){
			float highScore;
			readFromFile >> highScore;
			readFromFile.ignore();
			arr[i] = highScore;
			input = true;
		}
		readFromFile.close();
	}
	this->setHighScore(arr);
	return input;
}
//skriver highscoren till fil
bool Menu::highScoreWrite(float arr[]){
	bool output = false;
	std::ofstream writeToFile("Resources/highscore.txt", std::ios::out);
	if (writeToFile.is_open()){
		int nr = 5;
		for (int i = 0; i < nr; i++){
			writeToFile << arr[i]<<std::endl;
		}
		output = true;
		writeToFile.close();
	}
	return output;
}
//för att sortera highscore efter de 5 bästa
void Menu::selectionSort(float arr[], int size){
	for (int i = 0; i < size - 1; i++){
		for (int j = i; j < size; j++){
			if (arr[i]>arr[j]){
				swapThem(arr[i], arr[j]);
			}
		}
	}
}
//för att byta plats på highscore positioner
void Menu::swapThem(float &a, float &b){
	float temp = a;
	a = b;
	b = temp;
}

