#include "WndInventory.h"

WndInventory::WndInventory(GameScene* scene, UShort maxSize, Boolean isShown)
    : maxSize(maxSize), WndBasic(scene, ID_INVENTORY_AREA, ID_INVENTORY_AREA_WIDTH, ID_INVENTORY_AREA_HEIGHT, isShown)
{
}

WndInventory::~WndInventory()
{
}

CString WndInventory::title()
{
    return String(ID_INVENTORY_AREA)
        .append(" (").append(to_string(capacity())).append("/")
        .append(to_string(maxSize)).append(")").c_str();
}

void WndInventory::open(void(*Exit)())
{
	using namespace ImGui;
    isShown = true;

    if (ImGui::Begin(this->title(), &isShown, wndflag::Unresize | wndflag::Uncollapse)) {
        ////////////////////////// INVENTORY AREA
        {
             // set new UI area window size
            ImGui::SetWindowSize(ImVec2(width, height));
            ImGui::BeginTable(ID_INVENTORY_AREA_TABLE, ID_INVENTORY_COLUMNS, tabflag::Bordered | tabflag::SizingFixedSame | tabflag::SizingStretchSame);
            {
                for (int i = 0; i < ID_INVENTORY_COLUMNS; i++) {
                    ImGui::TableSetupColumn(String("InventoryColumn").append(to_string(i)).c_str(), ImGuiTableColumnFlags_WidthStretch, 34); // Default to 100.0f
                }

                static ImVec2 ColumnSize(ID_INVENTORY_ITEM_SIZE, ID_INVENTORY_ITEM_SIZE);
                UInt counter = 0;
                for (UInt row = 0; row < ID_INVENTORY_ROWS; row++) {
                    ImGui::TableNextRow();
                    {
                        ImGui::PushID(row);
                        for (UInt col = 0; col < ID_INVENTORY_COLUMNS; col++, counter++) {
                            ImGui::PushID(row * col);
                            ImGui::TableSetColumnIndex(col);
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - ColumnSize.x + 2);
                            if (counter < capacity()) {
                                Item& next = getByIndex(counter);
                                if (ImGui::Button(next.getName().c_str(), ColumnSize)) {
                                    cout << next.getName().c_str() << endl;
                                }
                            }
                            else {
                                if (ImGui::InvisibleButton("", ColumnSize)) {
                                }
                            }
                            ImGui::PopID();
                        }
                        ImGui::PopID();
                    }
                }
                ImGui::EndTable();
            }
        }
        ImGui::End();
    }
}

UInt WndInventory::capacity(Boolean max) const
{
    return max ? maxSize : items.size();
}

Boolean WndInventory::add(Item& item)
{
    items.push_back(item);
    logging::print(LogLevel::Debug, "WndInventory::add(Item& item)", 3,
        "Item ",
        to_string(item.getId()),
        " was added to inventory.");
    return true;
}

Boolean WndInventory::remove(Item& item)
{
    vector<Item>::iterator iter;
    for (iter = items.begin(); iter != items.end(); iter++) {
        Item& next = *iter;
        if (item.getUid() == next.getUid()) {
            items.erase(iter);
            logging::print(LogLevel::Debug, "WndInventory::remove(Item& item)", 1, "Item founded and was removed from inventory.");
            return true;
        }
    }

    logging::print(LogLevel::Warning, "WndInventory::remove(Item& item)", 1, "Item NOT founded and can't be removed.");
    return false;
}

Boolean WndInventory::remove(const UInt uid)
{
    Item* removable = nullptr;
    for (Item& next : items) {
        if (next.getId() == uid) {
            removable = &next;
            logging::print(LogLevel::Debug, "WndInventory::remove(const UInt uid)", 1, "Removable item found in items.");
            break;
        }
    }

    if (removable != nullptr) {
        return remove(*removable);
    }

    logging::print(LogLevel::Warning, "WndInventory::remove(const UInt uid)", 1, "Removable item not found in items.");
    return false;
}

vector<Item> WndInventory::collection()
{
    return items;
}

Item& WndInventory::getByIndex(const UInt index)
{
    return items[index];
}

Item& WndInventory::getByUid(const UInt uid)
{
    for (int i = 0; i < capacity(); i++) {
        Item& next = items[i];
        if (next.getUid() == uid) {
            return next;
        }
    }
}

template<typename Id>
vector<Item> WndInventory::sort(String strategy, Id id)
{
    /*if (StrExt::equalsIgnoreCase(strategy, "name")) {
        if (std::is_same(Id, String)) {
            items.sort([](const Item& next, const String& str) {return next.getName() < id; });
        }
        else {
            cerr << "wrong strategy or id?" << endl;
        }
    }*/
    return items;
}