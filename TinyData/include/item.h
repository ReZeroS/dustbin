#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
    public:
        Item();

        Item(std::string table, std::string name, std::string value);

        std::string table;
        std::string name;
        std::string value;

    protected:

    private:
};

#endif // ITEM_H
