#include "espresso_based.h"
EspressoBased::~EspressoBased()
{
    for (const auto &i : ingredients)
        delete i;
    ingredients.clear();
}

std::vector<Ingredient *> deepCopyVector(const std::vector<Ingredient *> &original)
{
    std::vector<Ingredient *> copy;

    for (Ingredient *ingredient : original)
    {
        // Create a new instance of the appropriate type (deep copy)
        if (dynamic_cast<Cinnamon *>(ingredient))
        {
            copy.push_back(new Cinnamon(*dynamic_cast<Cinnamon *>(ingredient)));
        }
        else if (dynamic_cast<Chocolate *>(ingredient))
        {
            copy.push_back(new Chocolate(*dynamic_cast<Chocolate *>(ingredient)));
        }
        else if (dynamic_cast<Sugar *>(ingredient))
        {
            copy.push_back(new Sugar(*dynamic_cast<Sugar *>(ingredient)));
        }
        else if (dynamic_cast<Milk *>(ingredient))
        {
            copy.push_back(new Milk(*dynamic_cast<Milk *>(ingredient)));
        }
        else if (dynamic_cast<MilkFoam *>(ingredient))
        {
            copy.push_back(new MilkFoam(*dynamic_cast<MilkFoam *>(ingredient)));
        }
        else if (dynamic_cast<Water *>(ingredient))
        {
            copy.push_back(new Water(*dynamic_cast<Water *>(ingredient)));
        }
        else if (dynamic_cast<Cookie *>(ingredient))
        {
            copy.push_back(new Cookie(*dynamic_cast<Cookie *>(ingredient)));
        }
        else if (dynamic_cast<Espresso *>(ingredient))
        {
            copy.push_back(new Espresso(*dynamic_cast<Espresso *>(ingredient)));
        }
    }

    return copy;
}
EspressoBased::EspressoBased(const EspressoBased &esp) : name(esp.name)
{
    ingredients = deepCopyVector(esp.ingredients);
}

void EspressoBased::operator=(const EspressoBased &esp)
{
    name = esp.name;
    ingredients = deepCopyVector(esp.ingredients);
}
