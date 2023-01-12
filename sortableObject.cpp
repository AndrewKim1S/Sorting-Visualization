#include "sortableObject.h"


sortableObject::sortableObject() {
		value = 0.0;
}

sortableObject::sortableObject(double value, double width) {
		this->value = value;
		shape = sf::RectangleShape();
		shape.setSize(sf::Vector2f(width, value));
		shape.setOutlineThickness(width * 0.1);
		shape.setOutlineColor(sf::Color(32, 32, 32));
		shape.setFillColor(sf::Color(255, 255, 255));
		original = sf::Color(255, 255, 255);
		animation = sf::Color(0, 204, 102);
}

sortableObject::~sortableObject() {
}

double sortableObject::getValue() {
		return value;
}

void sortableObject::blinkAnimation() {
		shape.setFillColor(animation);
}

void sortableObject::setOriginalColor() {
		shape.setFillColor(original);
}

void sortableObject::setPosition(float posX, float posY) {
		position.x = posX;
		position.y = posY;
		shape.setPosition(sf::Vector2f(position.x, position.y));
}

void sortableObject::render(sf::RenderWindow& window) {
		window.draw(shape);
}

sf::RectangleShape sortableObject::getShape() {
		return shape;
}
