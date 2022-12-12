enum class LogLevel {
	Debug,
	Error,
	Warning
};

enum class Lang {
	RU,
	EN
};

enum class ItemModification {
	Added,
	Deleted,
	Changed
};

enum class EnergyTypes {
	HP,
	MP,
	EP
};

enum class ParamTypes {
	Strength,
	Vitality,
	Agility,
	Dexterity,
	Concentration,
	Will,
	Intelligence,
	Spirit,
	Speed
};

enum class WeaponTypes {
	Hands,
	Sword,
	Dagger,
	Axe,
	Hammer,
	Spear,
	Hallberd,
	Staff,
	Scepter,
	Wand,
	Book,
	Knuckles
};

enum class ArmorTypes {
	Leather,
	Armored,
	Cloth,
	Scale,
	Shell,
	Skin
};

enum class EquipSlotTypes {
	None,
	Head,
	Body,
	Legs,
	Hands,
	Feets,
	Finger,
	Neck,
	Ear,
	RightWeapon,
	LeftWeapon
};

enum class ItemTypes {
	Resource,
	Potion,
	Elixier,
	Scroll,
	Book,
	Equippable
};

enum class ItemRareTypes {
	Normal,
	Rarest,
	Unique,
	Epic,
	Legendary
};

enum class BaseCmdTypes {
	/*
	Команда атаки: наносит урон противнику где
	расчёты берутся исходя из strength атакующего
	и vitality защищающегося.
	*/
	Attack,
	/*
	Команда защиты: принимает стойку защиты, которая
	снижает получаемый урон от любой прямой атаки в
	зависимости от параметра defence_power защищающегося.
	Исключение: оружие или способности - игнорирующие
	команду defend.
	*/
	Defend,
	/*
	Команда уклонения: делает попытку уклонения от атаки
	срабатывает 1 раз за ход, если успешно, то атакующий
	в 2 раза медленнее восстанавливает свои ep, а атака
	считается полностью заблокированной как и её эффект
	Исключение: оружие или способности - игнорирующие
	команду evade.
	*/
	Evade,
	/*
	Команда блока: проводит попытку блокировать следующую
	атаку, игнорируя эффект и урон. В случае успеха
	весь урон и эффект блокируются, а атакующий впадает
	в состояние оглушение на следующие 7 секунд. Возможно
	только при экипированном shield оружии.
	Исключение: оружие или способности - игнорирующие
	команду block.
	*/
	Block,
	/*
	Команда парирования: пытается парировать атаку врага
	(не skill/spell), чтобы сделать контратаку обратно
	в случае успеха. Если провалено, то получается урон,
	который игнорирует все показатели защиты и который
	всегда critical!. В случае успеха, такой же урон получит
	и нападающий.
	*/
	Parry,
	/*
	Команда манёвр: пытается обойти врага за спину, в случае
	успеха, следующая команда
	*/
	Maneuvr,
	Item,
	Ability
};

enum class ItemCmdTypes {
	// использовать
	Use,
	// бросить
	Throw,
};

enum class AbilityGroupTypes {
	Active,
	Passive,
	Toggle
};

enum class AbilityCategoryTypes {
	/* Включается в SkillCommands */
	Skill,
	/* Включается в SpellCommands */
	Spell
};

enum class MoveCmdTypes {
	// взобраться
	ClimbUp,
	// окружить
	Surround,
	// подойти
	ComeUp,
	// отойти
	MoveAway
};

enum class QualityTypes {
	Normal,
	Bad,
	Broken,
	Good,
	Perfect
};

enum class JobTypes {
	None,
	Thief,
	Knight,
	Archer,
	Swordsman,
	Lancer
};

enum class TraitTypes {
	/* Вы больше не тонете в воде от усталости. */
	Swimer,
	/* Штрафы на промахи и другие ньюансы больше на вас не действуют при экуипировке предметов в обеих руках */
	Abmidexter,
	/* Вы получаете ability command - steal */
	Thievery
};