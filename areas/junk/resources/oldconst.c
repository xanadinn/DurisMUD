
/*
 * ***************************************************************************
 * *  File: constant.c                                         Part of Duris *
 * *  Usage: almost all of the tables and wordlists.
 * * *  Copyright  1990, 1991 - see 'license.doc' for complete information.
 *  * *  Copyright  1994, 1995 - Duris Systems Ltd.
 * *
 * ***************************************************************************
 */


/*
 * mob race lookup table, used to assign a race to a mob when reading them
 * from the .mob file.  Need to update this table when adding new races.
 *
 * A note on the codes:  when I set them up, I tried to follow a pattern of
 * general/specific, like all 'player' races are "Px", all elementals are
 * "Ex", undead "Ux", humanoid "Hx", animals "Ax", etc.  Current this is not
 * used for anything specific, but it looked like a good idea, so try to
 * follow it if you add more races.  JAB
 */

const char *item_types[] =
{
  "UNDEFINED",
  "LIGHT",
  "SCROLL",
  "WAND",
  "STAFF",
  "WEAPON",
  "FIRE WEAPON",
  "MISSILE",
  "TREASURE",
  "ARMOR",
  "POTION",
  "WORN",
  "OTHER",
  "TRASH",
  "TRAP",
  "CONTAINER",
  "NOTE",
  "LIQUID CONT",
  "KEY",
  "FOOD",
  "MONEY",
  "PEN",
  "BOAT",
  "BOOK",
  "CORPSE",
  "TELEPORT",
  "TIMER",
  "VEHICLE",
  "SHIP",
  "SWITCH",
  "QUIVER",
  "PICK",
  "INSTRUMENT",
  "SPELLBOOK",
  "TOTEM",
  "STORAGE",
  "SCABBARD",
  "SHIELD",
  "\n"
};

const char *wear_bits[] =
{
  "TAKE",
  "FINGER",
  "NECK",
  "BODY",
  "HEAD",
  "LEGS",
  "FEET",
  "HANDS",
  "ARMS",
  "SHIELD",
  "ABOUT",
  "WAIST",
  "WRIST",
  "WIELD",
  "HOLD",
  "THROW",
  "LIGHT",
  "EYES",
  "FACE",
  "EARRING",
  "QUIVER",
  "INSIGNIA",
  "BACK",
  "ATTACH_BELT",
  "HORSE_BACK",
  "TAIL",
  "NOSE",
  "HORN",
  "\n"
};

const char *extra_bits[] =
{
  "GLOW",
  "NOSHOW",
  "DARK",
  "NOSELL",
  "EVIL",
  "INVISIBLE",
  "MAGIC",
  "NODROP",
  "BLESS",
  "ANTI-GOOD",
  "ANTI-EVIL",
  "ANTI-NEUTRAL",
  "SECRET",
  "FLOAT",
  "NOBURN",
  "NOLOCATE",
  "NOIDENTIFY",
  "NOSUMMON",
  "LIT",
  "TRANSIENT",
  "NOSLEEP",
  "NOCHARM",
  "TWOHANDS",
  "NORENT",
  "GOOD",
  "HUM",
  "LEVITATES",
  "**",
  "**",
  "WHOLE-BODY",
  "WHOLE-HEAD",
  "WAS-DISARMED",
  "\n"
};

const char *extra2_bits[] =
{
  "SILVER",
  "PLUSONE",
  "PLUSTWO",
  "PLUSTHREE",
  "PLUSFOUR",
  "PLUSFIVE",
  "RETURNING",
  "CAN_THROW1",
  "CAN_THROW2",
  "ENCHANT_FIRE",
  "ENCHANT_COLD",
  "ENCHANT_LIGHTNING",
  "ENCHANT_GAS",
  "ENCHANT_GOOD",
  "ENCHANT_EVIL",
  "NOMORE_ENCHANT",
  "\n"
};

const char *anti_bits[] =
{
  "ALLOW_ALL",
  "ALLOW_WARRIOR",
  "ALLOW_RANGER",
  "ALLOW_PALADIN",
  "ALLOW_ANTIPALADIN",
  "ALLOW_CLERIC",
  "ALLOW_MONK",
  "ALLOW_DRUID",
  "ALLOW_SHAMAN",
  "ALLOW_SORCERER",
  "ALLOW_NECROMANCER",
  "ALLOW_CONJURER",
  "ALLOW_PSIONICIST",
  "ALLOW_THIEF",
  "ALLOW_ASSASSIN",
  "ALLOW_MERCENARY",
  "ALLOW_BARD",
  "ANTI_HUMAN",
  "ANTI_GREYELF",
  "ANTI_HALFELF",
  "ANTI_DWARF",
  "ANTI_HALFLING",
  "ANTI_GNOME",
  "ANTI_BARBARIAN",
  "ANTI_DUERGAR",
  "ANTI_DROWELF",
  "ANTI_TROLL",
  "ANTI_OGRE",
  "ANTI_ILLITHID",
  "ANTI_ORC",
  "ANTI_EVILRACE",
  "ANTI_GOODRACE",
  "\n"
};

const char *anti2_bits[] =
{
  "ANTI_THRIKREEN",
  "ANTI_CENTAUR",
  "ANTI_GITHYANKI",
  "ANTI_MINOTAUR",
  "ANTI_MALE",
  "ANTI_FEMALE",
  "ANTI_NEUTER",
  "ANTI_AQUAELF",
  "ANTI_SAHUAGIN",
  "\n"
};

const char *room_bits[] =
{
  "DARK",
  "DEATH",
  "NO_MOB",
  "INDOORS",
  "ROOM_SILENT",
  "UNDERWATER",
  "NORECALL",
  "NO_MAGIC",
  "TUNNEL",
  "PRIVATE",
  "ARENA",
  "SAFE_ZONE",
  "NO_PRECIP",
  "SINGLE_FILE",
  "JAIL",
  "NO_TELEPORT",
  "PRIV-ZONE",
  "HEAL",
  "NO_HEAL",
  "LARGE",
  "DOCKABLE",
  "MAGIC_DARK",
  "MAGIC_LIGHT",
  "NO_SUMMON",
  "GUILD",
  "TWILIGHT",
  "NO_PSI",
  "NO_GATE",
  "HOUSE",
  "ATRIUM",
  "BLOCK_SIGHT",
  "BFS_MARK",
  "\n"
};

const char *zone_bits[] =
{
  "SILENT",
  "SAFE",
  "TOWN",
  "\n"
};

const char *exit_bits[] =
{
  "IS-DOOR",
  "CLOSED",
  "LOCKED",
  "RSCLOSED",
  "RSLOCKED",
  "PICKABLE",
  "SECRET",
  "BLOCKED",
  "PICKPROOF",
  "WALLED",
  "\n"
};

const char *sector_types[] =
{
  "Inside",
  "City",
  "Field",
  "Forest",
  "Hills",
  "Mountains",
  "Water-Swim",
  "Water-NoSwim",
  "No-Ground",
  "Underwater",
  "Underwater-Ground",
  "Plane-of-Fire",
  "Ocean",
  "UD-Wild",
  "UD-City",
  "UD-Inside",
  "UD-Water-Swim",
  "UD-Water-NoSwim",
  "UD-No-Ground",
  "Plane-of-Air",
  "Plane-of-Water",
  "Plane-of-Earth",
  "Plane-of-Etheral",
  "Plane-of-Astral",
  "Desert",
  "Tundra/Ice",
  "Swamp",
  "UD-Mountains",
  "UD-Slime",
  "UD-Low Ceilings",
  "UD-Liquid Mithril",
  "UD-Mushroom Forest",
  "Outer Castle Wall",
  "Castle Gate",
  "Castle",
  "\n"
};
