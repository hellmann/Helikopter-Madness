#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "SFML\Graphics.hpp"
#include "Player.hpp"
#include "EnemyHelicopter.hpp"


class Projectile : public sf::Drawable{
private:
	sf::Texture projectileTexture;
	sf::Sprite projectileSprite;
	float prSpeed = 600.0f;
	sf::RectangleShape rect;

	sf::Texture projectileTextureCanon;
	sf::Sprite projectileSpriteCanon;
	sf::RectangleShape rect2;
	void draw(sf::RenderTarget &target, sf::RenderStates states)const;

public:
	Projectile();
	Projectile(std::string filepath);
	void Update(float dt);
	void setPosition(sf::Vector2f position);
	void setRotation(float rotation);
	void setPositionCanon(sf::Vector2f position);
	void setRotationCanon(float rotation);
	sf::Vector2f getPosition()const;
	sf::FloatRect getGlobalBounds();
	sf::FloatRect getGlobalBoundsCanon();
};




#endif