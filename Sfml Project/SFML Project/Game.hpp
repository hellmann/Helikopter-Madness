#ifndef GAME_HPP
#define GAME_HPP
#include <sstream>
#include <SFML\Graphics.hpp>
#include "Player.hpp"
#include "Projectile.hpp"
#include "EnemyHelicopter.hpp"
#include "Canon.hpp"

class Game :public sf::Drawable
{
private:
	//anv�nder mig av enkelpekare f�r att initiera spelare och fiender
	Player *pPlayer;
	EnemyHelicopter *eEnemy;
	Canon *eCanon;
	//anv�nder mig av dubbelpekare f�r projektilerna
	Projectile **playerProjectiles;
	int playerCapacity;
	int nrOfPlayerProjectiles;

	Projectile **enemyProjectiles;
	int enemyCapacity;
	int nrOfEnemyProjectiles;

	Projectile **canonProjectiles;
	int canonCapacity;
	int nrOfCanonProjectiles;
	std::string filepath;
	//f�r att kunna expandera alla projektile arrayer
	void pExpand();
	void eExpand();
	void cExpand();
	//counters s� att man inte kan skjuta projektiler hur snabbt som helst
	int counter;
	int counter2;
	int counter3;
	//min bakgrunds sprite
	sf::Texture mBackgroundTex;
	sf::Sprite mBackgroundSprite;
	//variabler f�r explosions animationen
	sf::Texture explosionText;
	sf::Sprite explosionSprite;
	sf::Vector2i currentKeyFrame;
	sf::Vector2i keyFrameSize;
	int spriteSheetWidth;
	float animationSpeed;
	float keyFrameDuration;
	//variabler f�r highscore m�tning och r�kning
	bool output;
	sf::Clock clock;
	sf::Text text1;
	sf::Font font;
	sf::Time time;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	Game(const std::string &difficulty);
	~Game();
	void Update(float dt, float score[]);
	sf::Vector2f getPlayerPosition();
	sf::View cameraFollow(sf::View &player_view);
	void addEnemyProjectiles(EnemyHelicopter &enemy);
	void addPlayerProjectiles(Player &player);
	void addCanonProjectile(Canon &canon);
	void enemyCollision();
	void playerCollision();
	std::string highscore(float score[]);
	bool gameEnd();
};
#endif