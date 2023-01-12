#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class sortableObject {

		public:
				sortableObject();
				sortableObject(double value, double width);
				~sortableObject();
				double getValue();
				void render(sf::RenderWindow& window);
				
				void setPosition(float posX, float posY);
				void blinkAnimation();
				void setOriginalColor();
				inline float getXPos() { return position.x; }
				inline float getYPos() { return position.y; }
				sf::RectangleShape getShape();

		private:
				double value;

				sf::Vector2f position;
				sf::RectangleShape shape;
				sf::Color original;
				sf::Color animation;
};

