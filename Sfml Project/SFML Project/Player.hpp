#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Helicopter.hpp"
#include "SFML\Graphics.hpp"

class EnemyHelicopter;

class Player : public Helicopter{
private:
	sf::Texture playerTextUp;
	sf::Texture rotorText;
	sf::Sprite playerSprite;
	sf::Sprite rotorSprite;

	sf::Vector2i pCurrentKeyFrame;
	sf::Vector2i pKeyFrameSize;
	int pSpriteSheetWidth;
	float pAnimationSpeed;
	float pKeyFrameDuration;

	sf::RectangleShape rect;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	
public:
	Player(const int hp, const float speed);
	void Update(float dt);
	sf::Vector2f getPosition();
	float getRotation();
	sf::FloatRect getGlobalBounds();
};


#endif