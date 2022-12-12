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
	������� �����: ������� ���� ���������� ���
	������� ������� ������ �� strength ����������
	� vitality �������������.
	*/
	Attack,
	/*
	������� ������: ��������� ������ ������, �������
	������� ���������� ���� �� ����� ������ ����� �
	����������� �� ��������� defence_power �������������.
	����������: ������ ��� ����������� - ������������
	������� defend.
	*/
	Defend,
	/*
	������� ���������: ������ ������� ��������� �� �����
	����������� 1 ��� �� ���, ���� �������, �� ���������
	� 2 ���� ��������� ��������������� ���� ep, � �����
	��������� ��������� ��������������� ��� � � ������
	����������: ������ ��� ����������� - ������������
	������� evade.
	*/
	Evade,
	/*
	������� �����: �������� ������� ����������� ���������
	�����, ��������� ������ � ����. � ������ ������
	���� ���� � ������ �����������, � ��������� �������
	� ��������� ��������� �� ��������� 7 ������. ��������
	������ ��� ������������� shield ������.
	����������: ������ ��� ����������� - ������������
	������� block.
	*/
	Block,
	/*
	������� �����������: �������� ���������� ����� �����
	(�� skill/spell), ����� ������� ���������� �������
	� ������ ������. ���� ���������, �� ���������� ����,
	������� ���������� ��� ���������� ������ � �������
	������ critical!. � ������ ������, ����� �� ���� �������
	� ����������.
	*/
	Parry,
	/*
	������� �����: �������� ������ ����� �� �����, � ������
	������, ��������� �������
	*/
	Maneuvr,
	Item,
	Ability
};

enum class ItemCmdTypes {
	// ������������
	Use,
	// �������
	Throw,
};

enum class AbilityGroupTypes {
	Active,
	Passive,
	Toggle
};

enum class AbilityCategoryTypes {
	/* ���������� � SkillCommands */
	Skill,
	/* ���������� � SpellCommands */
	Spell
};

enum class MoveCmdTypes {
	// ����������
	ClimbUp,
	// ��������
	Surround,
	// �������
	ComeUp,
	// ������
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
	/* �� ������ �� ������ � ���� �� ���������. */
	Swimer,
	/* ������ �� ������� � ������ ������� ������ �� ��� �� ��������� ��� ����������� ��������� � ����� ����� */
	Abmidexter,
	/* �� ��������� ability command - steal */
	Thievery
};