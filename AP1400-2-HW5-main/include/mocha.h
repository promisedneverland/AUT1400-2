#ifndef MOCHA_H
#define MOCHA_H
#include"espresso_based.h"
class Mocha : public EspressoBased
{
public:
    Mocha() {
        ingredients.push_back(new Espresso(2));
        ingredients.push_back(new Milk(2));
        ingredients.push_back(new MilkFoam(1));
        ingredients.push_back(new Chocolate(1));
    }
    Mocha(const Mocha& cap);
	~Mocha();
    void operator=(const Mocha& cap);

    virtual std::string get_name() {
        return "Mocha";
    }
    virtual double price() {
        double ret = 0;
        for(auto ingredient : ingredients) {
            ret += ingredient->price();
        }
        for(auto ingredient : side_items) {
            ret += ingredient->price();
        }
        return ret;
    }

    void add_side_item(Ingredient* side) {
        side_items.push_back(side);
    }
    std::vector<Ingredient*>& get_side_items() {return side_items;}

private:
    std::vector<Ingredient*> side_items;

};
#endif // MOCHA_H