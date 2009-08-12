
#define MODE_ACT	0
#define MODE_UNACT	1

#define MAX_STRING_LENGTH 8192

#define RESOURCE_NONE           0
#define RESOURCE_ORE            2
#define RESOURCE_GOLD           4
#define RESOURCE_GEM            8
#define RESOURCE_HERB           16
#define RESOURCE_MINERAL        32
#define RESOURCE_TIMBER         64
#define RESOURCE_FERTILE        128
#define RESOURCE_PEOPLE         256

#define SECT_INSIDE            0
#define SECT_CITY              1
#define SECT_FIELD             2
#define SECT_FOREST            3
#define SECT_HILLS             4
#define SECT_MOUNTAIN          5
#define SECT_WATER_SWIM        6
#define SECT_WATER_NOSWIM      7
#define SECT_NO_GROUND         8
#define SECT_UNDERWATER        9
#define SECT_UNDERWATER_GR    10
#define SECT_FIREPLANE        11
#define SECT_OCEAN            12
#define SECT_UNDRWLD_WILD     13
#define SECT_UNDRWLD_CITY     14
#define SECT_UNDRWLD_INSIDE   15
#define SECT_UNDRWLD_WATER    16
#define SECT_UNDRWLD_NOSWIM   17
#define SECT_UNDRWLD_NOGROUND 18
#define SECT_AIR_PLANE        19
#define SECT_WATER_PLANE      20
#define SECT_EARTH_PLANE      21
#define SECT_ETHEREAL         22
#define SECT_ASTRAL           23
#define SECT_DESERT           24
#define SECT_ARCTIC           25
#define SECT_SWAMP            26
#define SECT_UNDRWLD_MOUNTAIN 27
#define SECT_UNDRWLD_SLIME    28
#define SECT_UNDRWLD_LOWCEIL  29
#define SECT_UNDRWLD_LIQMITH  30
#define SECT_UNDRWLD_MUSHROOM 31
#define SECT_CASTLE_WALL      32
#define SECT_CASTLE_GATE      33
#define SECT_CASTLE           34

/* utils.c */
int number(int from, int to);
int add_resources(int sector);
int get_line(FILE * fl, char *buf, FILE *actfile);
void fread_string(FILE * fl, char *error, FILE * outfile);
FILE *get_outputfile(char *fn, int mode);
char *bitvector_to_string(int number, char *words[]);
char *select_to_string(int number, char *words[]);
long string_to_bitvector(char *s, char *words[]);
long string_to_select(char *s, char *words[]);
int str_cmp(char *arg1, char *arg2);
int strn_cmp(char *arg1, char *arg2, int n);

/* [un]actwld.c */
void parse_room(FILE * fl, int virtual_nr, FILE *outfile);

/* [un]actobj.c */
char *parse_object(FILE * obj_f, int nr, FILE *actfile);

/* [un]actmob.c */
void parse_mobile(FILE * mob_f, int nr, FILE *actfile);

long erandom(void);
