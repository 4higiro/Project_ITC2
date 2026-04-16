#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "EventProcessor.h"
#include "Label.h"

struct Item
{
	std::u16string name;
	sf::Texture texture;
	bool is_empty_item = true;
};

class ItemBar : public EventProcessor
{
private:
	std::array<sf::RectangleShape, 5> boxes;
	std::array<Item, 5> items;

	Label current_name;

	int selection_index = 0;

	sf::Vector2u win_resolution;
	unsigned real_size;
	unsigned size;
	sf::Vector2u position = sf::Vector2u(0, 0);

	sf::Color in_color = sf::Color(0, 0, 255);
	sf::Color out_color = sf::Color(150, 150, 150);
	sf::Color select_color = sf::Color(0, 255, 255);
	sf::Color text_color = sf::Color(0, 255, 0);

	void updateGeometry();
protected:
	void mouseScrollEvent(unsigned x, unsigned y, int delta) override;
public:
	ItemBar(sf::Vector2u window_resolution);

	void render(sf::RenderWindow* window) override;
	sf::Rect<unsigned> mouseArea() override;

	void setPosition(sf::Vector2u pos);
	sf::Vector2u getPosition();
	void setSize(unsigned newSize);
	unsigned getSize();

	bool addItem(Item newItem);
	void clearItems();
	
	Item getSelectedItem();
};