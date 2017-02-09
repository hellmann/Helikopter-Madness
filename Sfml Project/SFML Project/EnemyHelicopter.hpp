#ifndef ENEMYHELICOPTER_HPP
#define ENEMYHELICOPTER_HPP

#include "SFML\Graphics.hpp"
#include "Helicopter.hpp"
#include "Player.hpp"


class EnemyHelicopter :public Helicopter{
private:
	sf::Texture enemyText;
	sf::Texture rotorText;
	sf::Sprite enemySprite;
	sf::Sprite rotorSprite;
	
	sf::Vector2i eCurrentKeyFrame;
	sf::Vector2i eKeyFrameSize;
	int eSpriteSheetWidth;
	float eAnimationSpeed;
	float eKeyFrameDuration;
	
	sf::RectangleShape rect;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	EnemyHelicopter(const int hp, const float speed);
	void Update(float dt, Player p);
	bool proximity(Player p, float radius1, float radius2);
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();
	float getRotation();

};




#endif