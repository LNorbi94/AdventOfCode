#include "HashMap.h"
#include "Hash.h"

void Box::setBoxNumber(int64_t boxNumber)
{
    m_boxNumber = boxNumber;
}

void Box::removeValue(std::string_view label)
{
    m_lenses.remove_if([label](const Lens& lens) { return lens.label == label; });
}

void Box::addValue(std::string_view label, int64_t focalLength)
{
    auto lens = std::find_if(m_lenses.begin(), m_lenses.end(), [label](const Lens& lens) { return lens.label == label; });
    if (lens != m_lenses.end()) {
        lens->focalLength = focalLength;
    } else {
        m_lenses.emplace_back(label.data(), focalLength);
    }
}

int64_t Box::getFocusingPower() const
{
    int64_t focusingPower = 0;
    auto i = 0;
    for (const auto& lens : m_lenses) {
        focusingPower += (m_boxNumber + 1) * (i + 1) * lens.focalLength;
        ++i;
    }
    return focusingPower;
}

HashMap::HashMap()
{
    for (auto i = 0; i < 256; ++i) {
        m_boxes[i].setBoxNumber(i);
    }
}

void HashMap::removeValue(std::string_view label)
{
    Hash h{ label };
    m_boxes[h.value()].removeValue(label);
}

void HashMap::addValue(std::string_view label, int64_t focalLength)
{
    Hash h{ label };
    m_boxes[h.value()].addValue(label, focalLength);
}

int64_t HashMap::calculateFocusingPower() const
{
    int64_t focusingPower = 0;
    for (const auto& box : m_boxes) {
        focusingPower += box.getFocusingPower();
    }
    return focusingPower;
}
