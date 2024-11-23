#include "cappuccino.h"
Cappuccino::~Cappuccino()
{
    for (const auto &i : side_items)
        delete i;
    side_items.clear();
}
extern std::vector<Ingredient *> deepCopyVector(const std::vector<Ingredient *> &original);
Cappuccino::Cappuccino(const Cappuccino &cap) : EspressoBased(cap)
{
    side_items = deepCopyVector(cap.side_items);
}
void Cappuccino::operator=(const Cappuccino &cap)
{
    EspressoBased::operator=(cap);
    side_items = deepCopyVector(cap.side_items);
}