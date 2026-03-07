#pragma once
#include "AbstractGraphics.h"
#include <SFML/Graphics.hpp>
#include <string> 
class Label : public AbstractGraphics
{
public:
    // Конструктор 1: с позицией, размером и текстом
    Label(sf::Rect<unsigned> area, const std::u16string& text = u"");

    // Конструктор 2: только текст (с позицией по умолчанию)
    Label(const std::u16string& text = u"");

    ~Label() = default;

    // Методы для установки свойств
    void setText(const std::u16string& text);
    void setPosition(float x, float y);
    void setSize(unsigned size);
    void setColor(sf::Color color);

    // Переопределение виртуальных методов
    void draw(sf::RenderWindow* window) override;
    sf::Rect<unsigned> area() override;

private:
    void setupGraphics();
    void fitTextToArea();     // Новый метод для подбора размера шрифта
    void centerText();        // Новый метод для центрирования

private:
    sf::Vector2f m_position = { 0, 0 };
    float m_width = 0;        // Ширина области
    float m_height = 0;       // Высота области
    std::u16string m_label;

    // Графические элементы
    sf::Text m_text;
    sf::Font m_font;
    sf::Color m_color = sf::Color::Red;

};

