#ifndef MENU_HPP
#define MENU_HPP
#include"SFML\Graphics.hpp"



class Menu{
private:
	int index;
	sf::Font font;
	sf::Text menu[8];
public:
	Menu(float width, float height);
	~Menu();

	void moveUp();
	void moveDown();

	int getIndex()const;
	void setIndex(const int index);
	void updateColor();

	void draw(sf::RenderWindow &window)const;

	void setHighScore(float arr[]);
	bool highScoreRead(float arr[]);
	bool highScoreWrite(float arr[]);

	void selectionSort(float arr[], int size);
	void swapThem(float &a, float &b);

	
};

#endif
