#include "CheckBox.h"

#include <iostream>

CheckBox::CheckBox(sf::Vector2u res, const std::u16string& text)
    : m_label(text), m_winHeight(res.y)
{
    m_realsize = m_size * m_winHeight / 1000.0;

    m_checkedHoveredTexture.loadFromFile("resources/gg1.png");
    m_checkedTexture.loadFromFile("resources/gg2.png");
    m_uncheckedHoveredTexture.loadFromFile("resources/gg3.png");
    m_uncheckedTexture.loadFromFile("resources/gg4.png");
    setupGraphics();

}

bool CheckBox::isChecked() const
{
    return m_checked;
}

void CheckBox::setChecked(bool checked)
{
    m_checked = checked;
    updateTexture();
}

void CheckBox::setSize(unsigned size)
{
    m_size = size;
    m_realsize = m_size * m_winHeight / 1000.0;
    setupGraphics(); // Пересоздаем графику с новым размером
}

void CheckBox::setPosition(sf::Vector2u pos)
{
    m_position = pos;
    updatePosition(); // Обновляем позицию всех элементов
}
void CheckBox::updatePosition()
{
    m_box.setPosition(static_cast<float>(m_position.x), static_cast<float>(m_position.y));
    centerText();
}

void CheckBox::render(sf::RenderWindow* window)
{
    if (!isActive()) return;

    // Рисуем рамку чекбокса
    window->draw(m_box);

    // Рисуем текст
    window->draw(m_text);
}

sf::Rect<unsigned> CheckBox::mouseArea()
{
    float textWidth = m_text.getLocalBounds().width;
    return sf::Rect<unsigned>(
        m_position.x,
        m_position.y,
        m_realsize + 5 + static_cast<unsigned>(textWidth),
        m_realsize 
    );
}

void CheckBox::mousePressedEvent(unsigned x, unsigned y, sf::Mouse::Button button)
{
    if (button == sf::Mouse::Left )
    {
        m_checked = !m_checked;
        updateTexture();
    }
}


void CheckBox::mouseHitEvent()
{
    m_hovered = true;
    updateTexture();
}
void CheckBox::mouseMissedEvent()
{
    m_hovered = false;
    updateTexture();
}


void CheckBox::setupGraphics()
{
    // Настройка рамки чекбокса
    m_box.setSize(sf::Vector2f(m_realsize, m_realsize));
    m_box.setPosition(static_cast<float>(m_position.x), static_cast<float>(m_position.y));
    m_box.setOutlineThickness(2);
    m_box.setOutlineColor(m_outlineColor);

    m_box.setTexture(&m_uncheckedTexture);


    // Настройка шрифта
    if (!m_font.loadFromFile("resources/Strogo-Regular.ttf"))
    {
        std::cout << "Strogo-Regular.ttf" << std::endl;
    }

    m_text.setFont(m_font);
    m_text.setString(sf::String::fromUtf16(m_label.begin(), m_label.end()));
    m_text.setCharacterSize(static_cast<unsigned>(m_realsize * 0.8f));
    m_text.setFillColor(m_textColor);
    m_text.setCharacterSize(m_realsize);
    centerText();
}

void CheckBox::centerText()
{
    // Позиционируем текст справа от чекбокса
    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setPosition(
        static_cast<float>(m_position.x + m_realsize + 5),
        static_cast<float>(m_position.y + (m_realsize - textBounds.height) / 2 - textBounds.top)
    );
}

void CheckBox::updateTexture()
{
    if (m_checked && m_hovered)
    {
        // Если отмечен и есть текстура для отмеченного состояния
        m_box.setTexture(&m_checkedHoveredTexture);
    }
    else if (m_checked && !m_hovered)
    {
        // Если наведен курсор и есть текстура для наведения
        m_box.setTexture(&m_checkedTexture);
    }
    else if (!m_checked && m_hovered)
    {
        // Обычное состояние
        m_box.setTexture(&m_uncheckedHoveredTexture);
    }
    else
    {
        m_box.setTexture(&m_uncheckedTexture);
    }
}



