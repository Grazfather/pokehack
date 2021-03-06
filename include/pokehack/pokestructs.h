#ifndef POKEMON_STRUCTURES
#define POKEMON_STRUCTURES

#define SAVEFILE_LEN (1 << 17)
#define NUM_BLOCKS_SLOT 14
#define NUM_BLOCKS_EXTRA 4
#define NUM_BLOCKS_TOTAL 32
#define BLOCK_DATA_LEN 3968
#define BLOCK_PADDING_LEN 116
#define BLOCK_FOOTER_LEN 12
#define BLOCK_TOTAL_LEN (BLOCK_DATA_LEN + BLOCK_PADDING_LEN + BLOCK_FOOTER_LEN)
#define SAVESLOT_LEN (14 * 3968)
#define BELT_OFFSET_RSE 0x11B8
#define BELT_OFFSET_FRLG 0xFB8
#define BOX_OFFSET 0x4D84

#define NUM_BELT_POKEMON 6
#define NUM_BOXES 14
#define NUM_POKEMON_PER_BOX 30
#define NUM_BOX_POKEMON (NUM_BOXES * NUM_POKEMON_PER_BOX)
#define POKEMON_DATA_LENGTH 48

#define NUM_POKEMON_SPECIES 440
#define NUM_ITEMS 377
#define NUM_ATTACKS 355

#include <pokehack/config.h>

typedef struct {
	unsigned char blocknum;
	unsigned char padding;
	unsigned short checksum;
	unsigned int validation; // 0x08012025
	int savenumber;
} block_footer;

typedef struct {
	unsigned char data[BLOCK_DATA_LEN];
	unsigned char padding[BLOCK_PADDING_LEN];
	block_footer footer;
} block;

unsigned short get_checksum( block* );

typedef struct {
	unsigned int personality;
	unsigned int otid;
	unsigned char name[10];
	unsigned short language;
	unsigned char otname[7];
	union {
		struct {
			unsigned char circle:1;
			unsigned char triangle:1;
			unsigned char square:1;
			unsigned char heart:1;
			unsigned char xbit:4; // unused
		} mark;
		unsigned char markint;
	};
	unsigned short int checksum;
	unsigned short int x1;				// unused
	unsigned char data[POKEMON_DATA_LENGTH];
	unsigned int status;
	unsigned char level;
	unsigned char pokerus;
	unsigned short int currentHP;
	unsigned short int maxHP;
	unsigned short attack;
	unsigned short defense;
	unsigned short speed;
	unsigned short spatk;
	unsigned short spdef;
} belt_pokemon_t;

typedef struct {
	unsigned int personality;
	unsigned int otid;
	unsigned char name[10];
	unsigned short language;
	unsigned char otname[7];
	unsigned char mark;
	unsigned short int checksum;
	unsigned short int x1;				// unused
	unsigned char data[POKEMON_DATA_LENGTH];
} box_pokemon_t;

typedef struct{
	unsigned short int species;
	unsigned short int held;
	unsigned int xp;
	unsigned char ppbonuses;
	unsigned char happiness;
	unsigned char x;				// unused
} pokemon_growth_t ;

typedef struct {
	unsigned short int atk1;
	unsigned short int atk2;
	unsigned short int atk3;
	unsigned short int atk4;
	unsigned char pp1;
	unsigned char pp2;
	unsigned char pp3;
	unsigned char pp4;
} pokemon_attacks_t;

typedef struct
{
	unsigned char hp;
	unsigned char attack;
	unsigned char defense;
	unsigned char speed;
	unsigned char spatk;
	unsigned char spdef;
	unsigned char coolness;
	unsigned char beauty;
	unsigned char cuteness;
	unsigned char smartness;
	unsigned char toughness;
	unsigned char feel;
} pokemon_effort_t;

typedef struct {
	unsigned char pokerus;
	unsigned char locationcaught;
	signed char levelcaught:7;
	unsigned char game:4;
	unsigned char pokeball:4;
	unsigned char tgender:1;
	union {
		struct {
			unsigned int hp:5;
			unsigned int atk:5;
			unsigned int def:5;
			unsigned int spd:5;
			unsigned int spatk:5;
			unsigned int spdef:5;
			unsigned int egg:1;
			unsigned int ability:1;
		} IVs;
		unsigned int IVint;
	};
	union {
		struct {
			unsigned char coolnormal:1;
			unsigned char coolsuper:1;
			unsigned char coolhyper:1;
			unsigned char coolmaster:1;
			unsigned char beautynormal:1;
			unsigned char beautysuper:1;
			unsigned char beautyhyper:1;
			unsigned char beautymaster:1;
			unsigned char cutenormal:1;
			unsigned char cutesuper:1;
			unsigned char cutehyper:1;
			unsigned char cutemaster:1;
			unsigned char smartnormal:1;
			unsigned char smartsuper:1;
			unsigned char smarthyper:1;
			unsigned char smartmaster:1;
			unsigned char toughnormal:1;
			unsigned char toughsuper:1;
			unsigned char toughhyper:1;
			unsigned char toughmaster:1;
			unsigned char champion:1;
			unsigned char winning:1;
			unsigned char victory:1;
			unsigned char artist:1;
			unsigned char effort:1;
			unsigned char marine:1;
			unsigned char land:1;
			unsigned char sky:1;
			unsigned char country:1;
			unsigned char national:1;
			unsigned char earth:1;
			unsigned char world:1;
		} ribbons;
		unsigned int ribbonint;
	};
} pokemon_misc_t;

/* Order:
	00. GAEM	 06. AGEM	 12. EGAM	 18. MGAE
	01. GAME	 07. AGME	 13. EGMA	 19. MGEA
	02. GEAM	 08. AEGM	 14. EAGM	 20. MAGE
	03. GEMA	 09. AEMG	 15. EAMG	 21. MAEG
	04. GMAE	 10. AMGE	 16. EMGA	 22. MEGA
	05. GMEA	 11. AMEG	 17. EMAG	 23. MEAG
*/
// Where in data each struct is, based on AEGM order
static const int DataOrderTable[24][4] = { \
/*          A  E  G  M */ \
/* GAEM */ {1, 2, 0, 3}, \
/* GAME */ {1, 3, 0, 2}, \
/* GEAM */ {2, 1, 0, 3}, \
/* GEMA */ {3, 1, 0, 2}, \
/* GMAE */ {2, 3, 0, 1}, \
/* GMEA */ {3, 2, 0, 1}, \
/* AGEM */ {0, 2, 1, 3}, \
/* AGME */ {0, 3, 1, 2}, \
/* AEGM */ {0, 1, 2, 3}, \
/* AEMG */ {0, 1, 3, 2}, \
/* AMGE */ {0, 3, 2, 1}, \
/* AMEG */ {0, 2, 3, 1}, \
/* EGAM */ {2, 0, 1, 3}, \
/* EGMA */ {3, 0, 1, 2}, \
/* EAGM */ {1, 0, 2, 3}, \
/* EAMG */ {1, 0, 3, 2}, \
/* EMGA */ {3, 0, 2, 1}, \
/* EMAG */ {2, 0, 3, 1}, \
/* MGAE */ {2, 3, 1, 0}, \
/* MGEA */ {3, 2, 1, 0}, \
/* MAGE */ {1, 3, 2, 0}, \
/* MAEG */ {1, 2, 3, 0}, \
/* MEGA */ {3, 1, 2, 0}, \
/* MEAG */ {2, 1, 3, 0} };

static const int belt_offsets[] = { BELT_OFFSET_RSE, BELT_OFFSET_FRLG };

int POKEHACK_API pack_save(char*, char*, block*[NUM_BLOCKS_TOTAL], char[SAVEFILE_LEN]);

//Allow global variables to be used outside library in MSVC
#ifdef _MSC_VER
    #ifdef __cplusplus
        extern "C"
        {
            POKEHACK_API char* pokemon_species[];
            POKEHACK_API char* items[];
            POKEHACK_API char* natures[];
            POKEHACK_API char* attacks[];
            POKEHACK_API char text[];
            POKEHACK_API char* parse_save( char*, char*, block*[NUM_BLOCKS_TOTAL]);
        }
    #else
        POKEHACK_API extern char* pokemon_species[];
        POKEHACK_API extern char* items[];
        POKEHACK_API extern char* natures[];
        POKEHACK_API extern char* attacks[];
        POKEHACK_API extern char text[];
        POKEHACK_API char* parse_save( char*, char*, block*[NUM_BLOCKS_TOTAL]);
    #endif
    #else
        POKEHACK_API extern char* pokemon_species[];
        POKEHACK_API extern char* items[];
        POKEHACK_API extern char* natures[];
        POKEHACK_API extern char* attacks[];
        POKEHACK_API extern char text[];
        #endif
#endif
