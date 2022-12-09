#ifndef ITEM_HPP
#define ITEM_HPP

#include "System.h"

class Item
{
private:
	UInt uid;
	UInt id;
	String name;

public:
	Item(UInt uid, UInt id, String name);
	~Item();
	UInt getId() const;
	String getName() const;
	UInt getUid() const;
};

#endif // !ITEM_HPP