#include "mocha.h"
Mocha::~Mocha()
{
    for (const auto &i : side_items)
        delete i;
    side_items.clear();
}
extern std::vector<Ingredient *> deepCopyVector(const std::vector<Ingredient *> &original);
Mocha::Mocha(const Mocha &cap) : EspressoBased(cap)
{
    side_items = deepCopyVector(cap.side_items);
}
void Mocha::operator=(const Mocha &cap)
{
    EspressoBased::operator=(cap);
    side_items = deepCopyVector(cap.side_items);
}