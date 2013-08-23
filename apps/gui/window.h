#ifndef WINDOW_H
#define WINDOW_H

#define WIN_W 450
#define WIN_H 300

// Include all the headers for the Qt widgets you will be using
#include <QMenu>
#include <QMenuBar>
#include <QKeySequence>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QFileDialog>
#include "GameComboBox.h"
#include "AttackComboBox.h"
#include "ItemComboBox.h"
#include "SpeciesComboBox.h"
#include "PokeballComboBox.h"
#include "StatusComboBox.h"
#include <pokehack/SaveParser.h>

#include <QDebug>

class Window : public QWidget
{
	Q_OBJECT

	public:
		Window( QWidget* parent = 0 );

	signals:
		// Define any signals necessary

	public slots:
		// Define any slots
		void loadSave();
		void switchPokemon();
		void save();
		void saveAs();
		void quit();
		void updateTotalEVs();
		void updateTotalIVs();

	private:
		// Declare all widgets that will need to be accessed outside of the
		// constructor (for example, if you need to get the value of a slider)
		void loadPokemon(belt_pokemon_t*, pokemon_attacks_t*, pokemon_effort_t*, pokemon_misc_t*, pokemon_growth_t*);

		QString openFileName;
		pokehack::SaveParser *parser;
		int currentPokemon;

		QLineEdit *pokePersonalityEdit;
		QLineEdit *pokeNameEdit;
		QLineEdit *pokeTrainerIDEdit;
		QLineEdit *pokeTrainerNameEdit;

		StatusComboBox *pokeStatusEdit;
		QComboBox *pokeMarkEdit;
		PokeballComboBox *pokePokeballEdit;
		QComboBox *pokeLocationEdit;

		ItemComboBox *pokeHeldEdit;
		QLineEdit *pokeExperienceEdit;
		QLineEdit *pokeLevelEdit;
		SpeciesComboBox *pokeSpeciesEdit;
		GameComboBox *gameEdit;

		AttackComboBox *pokeAtk1;
		QSpinBox *pokePP1;
		AttackComboBox *pokeAtk2;
		QSpinBox *pokePP2;
		AttackComboBox *pokeAtk3;
		QSpinBox *pokePP3;
		AttackComboBox *pokeAtk4;
		QSpinBox *pokePP4;
		QSpinBox *switchPokemonSpinBox;

		QSpinBox *pokeHPEV;
		QSpinBox *pokeAtkEV;
		QSpinBox *pokeDefEV;
		QSpinBox *pokeSpdEV;
		QSpinBox *pokeSpAtkEV;
		QSpinBox *pokeSpDefEV;
		QLabel *pokeTotalEVs;

		QSpinBox *pokeHPIV;
		QSpinBox *pokeAtkIV;
		QSpinBox *pokeDefIV;
		QSpinBox *pokeSpdIV;
		QSpinBox *pokeSpAtkIV;
		QSpinBox *pokeSpDefIV;
		QLabel *pokeTotalIVs;
};

#endif
