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
	/* ������ ��������� (max=true ������ �������� �����������-��������� ���-�� ��������� �����������) */
	UInt capacity(Boolean max = false) const;
	/* ���������� ��������� (���������) �� ��������� (��������: id - ����������� �� id)*/
	template<typename Id>
	vector<Item> sort(String strategy, Id id);
	/* ��������� ������� � ��������� */
	Boolean add(Item& item);
	/* ������� ������� �� ���������: �� ������ */
	Boolean remove(Item& item);
	/* ������� ������� �� ���������: �� id */
	Boolean remove(const UInt uid);
	/* �������� ������ ��������� */
	vector<Item> collection();
	/* �������� ������� �� ��������� �� index � ������� */
	Item& getByIndex(const UInt index);
	/* �������� ������� �� ��������� �� uid � ������� */
	Item& getByUid(const UInt uid);
};

#endif // !WND_INVENTORY_HPP

