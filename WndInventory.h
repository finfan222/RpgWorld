#ifndef WND_INVENTORY_HPP
#define WND_INVENTORY_HPP

#include "System.h"
#include "WndBasic.h"
#include "Item.h"

class WndInventory : public WndBasic
{
private:
	UShort maxSize;
	vector<Item> items;

public:
	WndInventory(GameScene* scene, UShort maxSize, Boolean isShown = false);
	~WndInventory();
	CString title();
	void open(void(*Exit)()) override;
	/* Размер инвентаря (max=true значит получаем максимально-возможное кол-во предметов переносимых) */
	UInt capacity(Boolean max = false) const;
	/* Сортировка инвентаря (предметов) по стратегии (например: id - отсортирует по id)*/
	template<typename Id>
	vector<Item> sort(String strategy, Id id);
	/* Добавляет предмет в инвентарь */
	Boolean add(Item& item);
	/* Удаляет предмет из инвентаря: по адресу */
	Boolean remove(Item& item);
	/* Удаляет предмет из инвентаря: по id */
	Boolean remove(const UInt uid);
	/* Получаем вектор предметов */
	vector<Item> collection();
	/* Получаем предмет из инвентаря по index в векторе */
	Item& getByIndex(const UInt index);
	/* Получаем предмет из инвентаря по uid в векторе */
	Item& getByUid(const UInt uid);
};

#endif // !WND_INVENTORY_HPP

