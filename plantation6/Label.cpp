#include "Label.h"
#include <iostream>

Label::Label(sf::Rect<unsigned> area, const std::u16string& text)
    : m_label(text)
{
    m_position.x = static_cast<float>(area.left);
    m_position.y = static_cast<float>(area.top);
    m_width = static_cast<float>(area.width);
    m_height = static_cast<float>(area.height);

    setupGraphics();
    fitTextToArea(); // Подбираем размер шрифта под прямоугольник
    centerText();    // Центрируем текст
}

// Конструктор только с текстом
Label::Label(const std::u16string& text)
    : m_label(text)
{
    m_position = { 0, 0 };
    m_width = 0;
    m_height = 0;

    setupGraphics();
    // Для второго конструктора просто центрируем текст по позиции
    centerText();
}

void Label::setText(const std::u16string& text)
{
    m_label = text;
    m_text.setString(sf::String::fromUtf16(m_label.begin(), m_label.end()));

    if (m_width > 0 && m_height > 0) {
        fitTextToArea();
    }
    centerText();
}

void Label::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
    centerText();
}

void Label::setSize(unsigned size)
{
    // Этот метод больше не используется
    // Размер шрифта теперь подбирается автоматически
}

void Label::setColor(sf::Color color)
{
    m_color = color;
    m_text.setFillColor(m_color);
}

void Label::draw(sf::RenderWindow* window)
{
    if (!isVisible() || !window) return;
    window->draw(m_text);
}

sf::Rect<unsigned> Label::area()
{
    return sf::Rect<unsigned>(
        static_cast<unsigned>(m_position.x),
        static_cast<unsigned>(m_position.y),
        static_cast<unsigned>(m_width),
        static_cast<unsigned>(m_height)
    );
}

void Label::setupGraphics()
{
    // Загрузка шрифта
    if (!m_font.loadFromFile("resources/Strogo-Regular.ttf"))
    {
        std::cout << "Strogo-Regular.ttf" << std::endl;
    }

    m_text.setFont(m_font);
    m_text.setString(sf::String::fromUtf16(m_label.begin(), m_label.end()));
    m_text.setFillColor(m_color);

    // Начальный размер шрифта
    m_text.setCharacterSize(20);
}

void Label::fitTextToArea()
{
    if (m_width <= 0 || m_height <= 0) return;

    // Получаем границы текста с текущим размером
    sf::FloatRect bounds = m_text.getLocalBounds();

    // Вычисляем масштаб по ширине и высоте
    float scaleX = m_width / bounds.width;
    float scaleY = m_height / bounds.height;

    // Берем минимальный масштаб, чтобы текст точно поместился
    float scale = std::min(scaleX, scaleY);

    // Учитываем небольшой отступ (90% от размера, чтобы не впритык)
    scale *= 0.9f;

    // Устанавливаем новый размер шрифта
    unsigned int newSize = static_cast<unsigned int>(20 * scale);
    if (newSize < 8) newSize = 8; // Минимальный размер
    if (newSize > 200) newSize = 200; // Максимальный размер

    m_text.setCharacterSize(newSize);
}

void Label::centerText()
{
    sf::FloatRect bounds = m_text.getLocalBounds();

    if (m_width > 0 && m_height > 0) {
        // Центрируем внутри прямоугольника
        float textX = m_position.x + (m_width - bounds.width) / 2 - bounds.left;
        float textY = m_position.y + (m_height - bounds.height) / 2 - bounds.top;
        m_text.setPosition(textX, textY);
    }
    else {
        // Если размеры не заданы, просто ставим текст в указанную позицию
        m_text.setOrigin(bounds.width / 2, bounds.height / 2);
        m_text.setPosition(m_position);
    }
}