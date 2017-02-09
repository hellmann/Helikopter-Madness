#ifndef CANON_HPP
#define CANON_HPP
#include "SFML\Graphics.hpp"
#include "Player.hpp"

class Canon : public sf::Drawable{
private:
	int hp;
	sf::Texture canonTexture;
	sf::Sprite canonSprite;
	sf::RectangleShape rect;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	
public:
	Canon(int hp);
	void Update(float dt, Player p);
	bool proximity(Player p, float radius1, float radius2);
	sf::Vector2f getPosition();
	float getRotation();
	sf::FloatRect getGlobalBounds();

	void setHp(const int hp);
	int getHp()const;
};



#endif