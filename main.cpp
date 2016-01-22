#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <Windows.h>
#include "Input.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Platformer !");
	sf::Clock deltaClock;
	sf::View view(window.getDefaultView());
	float deltaTime;

	float Gravity = 0;
	float NormalGravity = 70;
	float SlowGravity = 30;
	float DownGravity = 200;
	float JumpHeight = -4;
	float Acceleration = 1;
	bool IsGrounded = false;
	bool Walltouching = false;
	bool WalltouchingRight = false;
	bool WalltouchingLeft = false;
	sf::Vector2f Velocity = sf::Vector2f(0, 0);
	sf::Vector2f Position = sf::Vector2f(300, 0);
	sf::Vector2f Size = sf::Vector2f(50, 50);
	float Speed = 8000;
	float Horizontal = 0;
	float Vertical = 0;
	sf::RectangleShape Player;
	Player.setSize(Size);
	Player.setFillColor(sf::Color(150, 40, 70, 200));
	sf::RectangleShape BLOK;
	BLOK.setSize(Size + Size);
	BLOK.setFillColor(sf::Color(250, 130, 40, 150));
	BLOK.setPosition(sf::Vector2f(500, 900));
	window.setFramerateLimit(240);
	// Game Loop
	while (window.isOpen())
	{
		Input input;


		sf::Event event;
		float Framerate = 1 / deltaClock.getElapsedTime().asSeconds();
		sf::Time dt = deltaClock.restart();
		deltaTime = dt.asSeconds();

		if (deltaTime >= 0.0005)
			deltaTime = 0.0005;
		else if (deltaTime <= 0.0003)
			deltaTime = 0.0003;

		while (window.pollEvent(event))  // Events
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(view = sf::View(sf::FloatRect(0.f, 0.f,
					static_cast<float>(window.getSize().x),
					static_cast<float>(window.getSize().y))));
				break;
			/*case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space){
					//if (IsGrounded){
						Velocity.y = JumpHeight;
						printf("JUMPIN");
					//}
				}*/
				//break;
			}
		}

			// Update

			// Horizontal Input

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
				Horizontal = -1;
				if (Acceleration <= 3)
					Acceleration += 10*deltaTime;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
				Horizontal = 1;
				if (Acceleration <= 3)
					Acceleration += 10*deltaTime;
			}
			else {
				if (Acceleration <= 0.01)
					Acceleration = 1;
				if (Horizontal >= 0.1)
					Horizontal -= 20*deltaTime;
				else if (Horizontal <= 0.1)
					Horizontal += 20*deltaTime;
				else
					Horizontal = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				Gravity = DownGravity;
			}
			else
				Gravity = NormalGravity;

			// Wall Collision

			if (Position.x <= 0){
				//IsGrounded = true;
				Position.x = 0;
				Walltouching = true;
				WalltouchingLeft = true;
				Gravity = SlowGravity;
			}
			else if (Position.x >= window.getSize().x-50){
				//IsGrounded = true;
				Position.x = window.getSize().x - 50;
				Walltouching = true;
				WalltouchingRight = true;
				Gravity = SlowGravity;
			}
			else {
				Walltouching = false;
				WalltouchingRight = false;
				WalltouchingLeft = false;
			}

			// COLLISION

			if (Position.x < BLOK.getPosition().x + 100 &&
				Position.x + 50 > BLOK.getPosition().x &&
				Position.y < BLOK.getPosition().y + 100 &&
				50 + Position.y > BLOK.getPosition().y){
				printf("\nTOUCHING !");
			}
			else{
				//system("cls");
			}

			// Gravity and down collision

			if (Position.y >= window.getSize().y - 50){
				IsGrounded = true;
				Velocity.y = 0;
			}
			else if (Walltouching){
				IsGrounded = true;
				Velocity.y += Gravity*deltaTime;
			}
			else {
				IsGrounded = false;
				Velocity.y += Gravity*deltaTime;
			}

			// Jumping Input
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
				if (IsGrounded){
					Velocity.y = JumpHeight;
				}
			}
			
			// Movement Calculations
			//14JumpHeight = -(window.getSize().x / window.getSize().x / 1.5);
			Velocity.x = Horizontal*Acceleration*Speed*deltaTime;
			Player.setPosition(Position);
			Position += Velocity;
			printf("\nHorizontal:     %f", Horizontal);
			
			// Draw
			window.clear();
			window.draw(Player);
			window.draw(BLOK);
			window.display();
		}

		return 0;
	}
