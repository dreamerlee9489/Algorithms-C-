#include <list>
#include <vector>
#include <iostream>
typedef long uint64;

enum struct ItemType
{
    None,
    Potion,
    Weapon
};

enum struct KnapType
{
    World,
    Bag,
    Equip,
    Action,
    Trade
};

struct ItemSlot
{
    int itemId = 0;
    ItemType itemType = ItemType::None;
    KnapType knapType = KnapType::World;
    std::list<uint64> items;

    ItemSlot& operator=(const ItemSlot& slot) 
    {
        itemId = slot.itemId;
        itemType = slot.itemType;
        knapType = slot.knapType;
        items = slot.items;
        return *this;
    }

    ItemSlot &operator=(ItemSlot &&slot) noexcept
    {
        itemId = std::move(slot.itemId);
        itemType = std::move(slot.itemType);
        knapType = std::move(slot.knapType);
        items = std::move(slot.items); // slot.items.size()=0
        slot.itemId = 0;
        
        return *this;
    }

    ItemSlot() = default;

    ItemSlot(const ItemSlot &slot) { *this = slot; }

    ItemSlot(ItemSlot &&slot) noexcept { *this = std::move(slot); }

    ~ItemSlot() = default;
};

int main()
{
    // std::vector<ItemSlot> slots(30); // 调用默认构造函数
    // slots[15].itemId = 30;
    // slots[1] = std::move(slots[15]);
    // std::cout << "15 id=" << slots[15].itemId << "\n";
    // std::cout << "1 id=" << slots[1].itemId << "\n";
    // getchar();
    return 0;
}