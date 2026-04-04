#pragma once
#include "AbstractGraphics.h"
#include "Label.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>

struct Item
{
	std::u16string name;
	sf::Texture texture;
	bool isEmptyItem = true;
};

class ItemBar : public AbstractGraphics
{
private:
	std::array<sf::RectangleShape, 5> boxes;

	std::vector<Item> items;
	Label currentName = Label(u"");

	int selectionIndex = 0;

	sf::Vector2u winResolution;
	unsigned realSize;
	unsigned size;
	sf::Vector2u position = sf::Vector2u(0, 0);
	static constexpr int maxItemsCount = 5;

	sf::Color inColor = sf::Color(0, 0, 255);
	sf::Color outColor = sf::Color(150, 150, 150);
	sf::Color selectColor = sf::Color(0, 255, 255);

	void setupGraphics();
protected:
	void mouseScrollEvent(unsigned x, unsigned y, int delta) override;
public:
	ItemBar(sf::Vector2u windowResolution);

	void draw(sf::RenderWindow* window) override;
	sf::Rect<unsigned> area() override;

	void setPosition(sf::Vector2u pos);
	sf::Vector2u getPosition();
	void setSize(unsigned newSize);
	unsigned getSize();

	bool addItem(Item newItem);
	void clearItems();
	
	Item getSelectedItem();
};