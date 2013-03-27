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

#define NUM_POKEMON 6
#define POKEMON_DATA_LENGTH 48

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
	unsigned char mark;
	unsigned short int checksum;
	unsigned short int x1; 				// unused
	unsigned char data[48];
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
	unsigned char locationcaught;
	signed char levelcaught:7;
	unsigned char gamelsb:1;				// 'Game of Origin' lsb
	unsigned char gamemsbs:3;				// 'Game of Origin' msbs
	unsigned char pokeball:4;
	unsigned char tgender:1;
	unsigned int ability:1;
	unsigned int egg:1;
	unsigned int spdefiv:5;
	unsigned int spatkiv:5;
	unsigned int spdiv:5;
	unsigned int defiv:5;
	unsigned int atkiv:5;
	unsigned int hpiv:5;
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

unsigned short int encrypt( unsigned char *, unsigned int, unsigned int );
char* parse_save( char*, char*, block *[NUM_BLOCKS_TOTAL]);

#endif
