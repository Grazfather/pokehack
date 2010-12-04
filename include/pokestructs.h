#include <stdio.h>

#define STATE_SIZE 0xB49FE

// Either compile for each game, allow a choice, or detect automatically
#define BELT_OFFSET 0x2C863 // Uncompressed save state for Pokemon FireRed

#define NUM_POKEMON 6 // This will never change, but whatever.
#define DATA_LENGTH 48

typedef struct {
	unsigned int personality;
	unsigned int otid;
	unsigned char name[10];
	unsigned char font;
	unsigned char sanity;
	unsigned char otname[7];
	unsigned char mark;
	unsigned short int checksum;
	unsigned short int x1; 				// unused
	unsigned char data[48];
	unsigned int status;
	unsigned char level;
	unsigned char x2; 				// unused
	unsigned short int currentHP;
	unsigned short int maxHP;
	unsigned short attack;
	unsigned short defense;
	unsigned short speed;
	unsigned short spatk;
	unsigned short spdef;
} pokemon_t;

typedef struct{
	unsigned short int species;
	unsigned short int held;
	unsigned int xp;
	unsigned char ppbonuses;
	unsigned char happiness;
	unsigned char x; 				// unused
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
	unsigned char location;
	signed char level;
	unsigned char pokeball; 		// As well as trainer gender?
	unsigned int IVs; 				// TODO: Split into groups of 5 bytes + 2 for egg
	unsigned int ribbons;
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
