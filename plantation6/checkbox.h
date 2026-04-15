#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "EventProcessor.h"

class CheckBox : public EventProcessor
{
public:
    // Конструктор
    CheckBox(sf::Vector2u res, const std::u16string& text = u"");
    ~CheckBox() = default;

    // Геттеры и сеттеры
    bool isChecked() const;
    void setChecked(bool checked);

    void setSize(unsigned size);
    void setPosition(sf::Vector2u pos);

    // Переопределение виртуальных методов
    void render(sf::RenderWindow* window) override;
    sf::Rect<unsigned> mouseArea() override;

protected:
    void mousePressedEvent(unsigned x, unsigned y, sf::Mouse::Button button) override;
    void mouseHitEvent() override;
    void mouseMissedEvent() override;

private:
    void setupGraphics();
    void centerText();
    void updateTexture();
    void updatePosition();

private:
    sf::Vector2u m_position = { 0,0 };
    unsigned m_size=20;
    unsigned m_realsize;
    unsigned m_winHeight;
    std::u16string m_label;
    bool m_checked = false;
    bool m_hovered = false;

    // Графические элементы
    sf::RectangleShape m_box;
    sf::Text m_text;
    sf::Font m_font;




    sf::Texture m_uncheckedTexture;
    sf::Texture m_uncheckedHoveredTexture;
    sf::Texture m_checkedTexture;
    sf::Texture m_checkedHoveredTexture;
    

 
    sf::Color m_textColor = sf::Color(255, 0, 0);        // Цвет текста
    sf::Color m_outlineColor = sf::Color(44, 62, 80);     // Цвет рамки
};