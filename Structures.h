#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include "System.h"
#include "Item.h"

#define REQUEST_TEST		0x00
#define RESPONSE_TEST		0x01
#define REQUEST_VERSION	    0x02
#define RESPONSE_VERSION	0x03

static const uint16_t MAX_LOGIN_CHARS = 4;
static const uint16_t MAX_PASSWORD_CHARS = 6;

////////////////////////////// PACKETS
#pragma pack(push, 1)
struct BaseStruct {
    static const UShort OPCODE = REQUEST_TEST;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ResponseTest {
    static const UShort OPCODE = RESPONSE_TEST;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct VersionRequest : BaseStruct {
    static const UShort OPCODE = REQUEST_VERSION;
    Int version;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct VersionAnswer : BaseStruct {
    static const UShort OPCODE = RESPONSE_VERSION;
    Int answer;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct RequestLogin {

    String login;
    String password;

    bool validate() {
        if (login.length() < MAX_LOGIN_CHARS) {
            return false;
        }
        if (password.length() < MAX_PASSWORD_CHARS) {
            return false;
        }
        return true;
    }
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ResponseLogin {
    Character login[MAX_LOGIN_CHARS];
    Character password[MAX_PASSWORD_CHARS];
};
#pragma pack(pop)

////////////////////////////// INVENTORY 0xA
#define REQUEST_INVENTORY_UPDATE 	        0xa0 // изменения в инвентаре
#define REQUEST_INVENTORY_ITEM_SELECTED 	0xa1 // предмет выбран (бромление синего цвета)

#pragma pack(push, 1)
struct RequestInventoryUpdate {
    static const UShort OPCODE_CHANGED = REQUEST_INVENTORY_UPDATE;

    struct Data {
        UInt uid;
        UInt id;
        UInt count;
        ItemModification modification;
    };

    UInt size;          // кол-во предметов которые были модифицированы
    Data* data;         // массив предметов и того что изменилось
    Boolean show;       // показать инвентарь?
 };
#pragma pack(pop)

#pragma pack(push, 1)
struct RequestInventoryItemSelected {
    static const UShort OPCODE_CHANGED = REQUEST_INVENTORY_ITEM_SELECTED;
    UInt itemId;
    UInt type; // Shift/Ctrl
};
#pragma pack(pop)


#endif