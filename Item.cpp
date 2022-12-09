#include "Item.h"

Item::Item(UInt uid, UInt id, String name)
    : uid(uid), id(id), name(name)
{
}

Item::~Item()
{
}

UInt Item::getId() const
{
    return id;
}

String Item::getName() const
{
    return name;
}

UInt Item::getUid() const
{
    return uid;
}
