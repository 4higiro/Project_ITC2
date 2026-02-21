#include "checkbox.h"
#include <iostream>

CheckBox::CheckBox(unsigned x, unsigned y, unsigned size, const std::u16string& text)
    : m_position(x, y)
    , m_size(size)
    , m_label(text)
    , m_checked(false)
    , m_hovered(false)
    , m_normalColor(255, 255, 255)      // Белый
    , m_hoverColor(255, 0, 0)       // Светло-голубой
    , m_checkedColor(46, 204, 113)        // Зеленый
    , m_textColor(44, 62, 80)           // Темно-синий
    , m_outlineColor(80, 80, 80)        // Темно-серый
{
    setupGraphics();
}

bool CheckBox::isChecked() const
{
    return m_checked;
}

void CheckBox::setChecked(bool checked)
{
    m_checked = checked;
    updateColor();
}

void CheckBox::setText(const std::u16string& text)
{
    m_label = text;
    m_text.setString(sf::String::fromUtf16(text.begin(), text.end()));
    centerText();
}

void CheckBox::draw(sf::RenderWindow* window)
{
    if (!isVisible() || !window) return;

    updateColor();

    // Рисуем рамку чекбокса
    window->draw(m_box);

    // Если отмечен, рисуем галочку
    if (m_checked)
    {
        
    }

    // Рисуем текст
    window->draw(m_text);
}

sf::Rect<unsigned> CheckBox::area()
{
    float textWidth = m_text.getLocalBounds().width;
    return sf::Rect<unsigned>(
        m_position.x - 2,
        m_position.y - 2,
        m_size + 5 + static_cast<unsigned>(textWidth) + 2,
        m_size + 2
    );
}

void CheckBox::mousePressedEvent(unsigned x, unsigned y, sf::Mouse::Button button)
{
    if (button == sf::Mouse::Left && isMouseOver(x, y))
    {
        m_checked = !m_checked;
        updateColor();
    }
}

void CheckBox::mouseMoveEvent(unsigned x, unsigned y)
{
    bool wasHovered = m_hovered;
    m_hovered = isMouseOver(x, y);

    if (wasHovered != m_hovered)
    {
        updateColor();
    }
}

void CheckBox::resizeEvent(unsigned width, unsigned height)
{
    // Не требуется для чекбокса
}

void CheckBox::showEvent()
{
    // Действия при показе (если нужны)
}

void CheckBox::hideEvent()
{
    // Действия при скрытии (если нужны)
}

void CheckBox::setupGraphics()
{
    // Настройка рамки чекбокса
    m_box.setSize(sf::Vector2f(m_size, m_size));
    m_box.setPosition(static_cast<float>(m_position.x), static_cast<float>(m_position.y));
    m_box.setOutlineThickness(2);
    m_box.setOutlineColor(m_outlineColor);
    m_box.setFillColor(m_normalColor);

    // Настройка шрифта
    if (!m_font.loadFromFile("resources/Drabina-Outline.otf"))
    {
        std::cout << "Warning: Could not load arial.ttf" << std::endl;
    }

    m_text.setFont(m_font);
    m_text.setString(sf::String::fromUtf16(m_label.begin(), m_label.end()));
    m_text.setCharacterSize(static_cast<unsigned>(m_size * 0.8f));
    m_text.setFillColor(m_textColor);

    centerText();
}

void CheckBox::centerText()
{
    // Позиционируем текст справа от чекбокса
    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setPosition(
        static_cast<float>(m_position.x + m_size + 5),
        static_cast<float>(m_position.y + (m_size - textBounds.height) / 2 - textBounds.top)
    );
}

void CheckBox::updateColor()
{
    if (m_checked)
    {
        // Если отмечен - красный фон
        m_box.setFillColor(m_checkedColor);
    }
    else if (m_hovered)
    {
        m_box.setFillColor(m_hoverColor);
    }
    else
    {
        m_box.setFillColor(m_normalColor);
    }

    if (m_checked)
    {
        
    }
    else
    {
        
    }
}

bool CheckBox::isMouseOver(unsigned x, unsigned y) const
{
    return x >= m_position.x && x <= m_position.x + m_size &&
        y >= m_position.y && y <= m_position.y + m_size;
}
