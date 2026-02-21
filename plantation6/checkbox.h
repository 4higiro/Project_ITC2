#pragma once

#include "AbstractGraphics.h"
#include <SFML/Graphics.hpp>
#include <string>

class CheckBox : public AbstractGraphics
{
public:
    // Конструктор
    CheckBox(unsigned x, unsigned y, unsigned size = 20, const std::u16string& text = u"");
    ~CheckBox() = default;

    // Геттеры и сеттеры
    bool isChecked() const;
    void setChecked(bool checked);
    void setText(const std::u16string& text);

    // Переопределение виртуальных методов
    void draw(sf::RenderWindow* window) override;
    sf::Rect<unsigned> area() override;

protected:
    void mousePressedEvent(unsigned x, unsigned y, sf::Mouse::Button button) override;
    void mouseMoveEvent(unsigned x, unsigned y) override;
    void resizeEvent(unsigned width, unsigned height) override;
    void showEvent() override;
    void hideEvent() override;

private:
    void setupGraphics();
    void centerText();
    void updateColor();
    bool isMouseOver(unsigned x, unsigned y) const;

private:
    sf::Vector2<unsigned> m_position;
    unsigned m_size;
    std::u16string m_label;
    bool m_checked;
    bool m_hovered;

    // Графические элементы
    sf::RectangleShape m_box;
    sf::Text m_text;
    sf::Font m_font;

    // Цвета
    sf::Color m_normalColor = sf::Color(255, 255, 255);      // Обычное состояние
    sf::Color m_hoverColor = sf::Color(200, 230, 255);       // При наведении
    sf::Color m_checkedColor = sf::Color(46, 204, 113);       // Цвет галочки
    sf::Color m_textColor = sf::Color(44, 62, 80);        // Цвет текста
    sf::Color m_outlineColor = sf::Color(44, 62, 80);     // Цвет рамки
};