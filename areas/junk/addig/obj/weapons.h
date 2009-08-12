// WEAPONS.H - constants for weapon types

#ifndef _WEAPONS_H_

// wacky-ass weapon damage types.  bah.

#define WEAP_LOWEST     2
#define WEAP_WHIP       2
#define WEAP_SLASH      3
#define WEAP_CRUSH      6
#define WEAP_POUND      7
#define WEAP_PIERCE    11
#define WEAP_HIGHEST   11

// weapon types

#define WEAPON_LOWEST       1
#define WEAPON_AXE          1  // axes - slashing
#define WEAPON_DAGGER       2  // daggers, knives - piercing, slashing (with -)
#define WEAPON_FLAIL        3  // flails - whip
#define WEAPON_HAMMER       4  // hammers - bludgeon
#define WEAPON_LONGSWORD    5  // long swords - slashing/piercing (with -)
#define WEAPON_MACE         6  // mace - bludgeon
#define WEAPON_SPIKED_MACE  7  // spiked mace - bludgeon with pierce thrown in
#define WEAPON_POLEARM      8  // polearm - halberds, pikes, etc - piercing
#define WEAPON_SHORTSWORD   9  // short swords - slashing/piercing
#define WEAPON_CLUB        10  // clubs - bludgeon
#define WEAPON_SPIKED_CLUB 11  // spiked clubs - bludgeon and piercing
#define WEAPON_STAFF       12  // staff - like club but longer, maybe 2-handed -
                               //   bludgeon
#define WEAPON_2HANDSWORD  13  // two-handed swords - slash
#define WEAPON_WHIP        14  // whips - whip
#define WEAPON_PICK        15  // pick - pierce
#define WEAPON_LANCE       16  // lance - special handling probably
#define WEAPON_SICKLE      17  // sickle - slash/pierce?
#define WEAPON_FORK        18  // forks/rakes - slash
#define WEAPON_HORN        19  // curved piercer - piercing
#define WEAPON_NUMCHUCKS   20  // numchucks - bludgeon
#define WEAPON_HIGHEST     20

#define _WEAPONS_H_
#endif
