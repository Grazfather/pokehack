#include "window.h"
#include <QtDebug>
#include <iostream>

void Window::loadSave()
{
	int err;
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open savestate"),
						"./../..", tr("Savestates (*.*)") );

	err = parser->load(fileName.toLocal8Bit().data(), gameEdit->currentIndex());
	if (err)
	{
		return;
	}
	openFileName = fileName;

	currentPokemon = 0;
	switchPokemonSpinBox->setValue(0);
	loadPokemon(parser->pokemon[currentPokemon], parser->pokemon_attacks[currentPokemon],
				parser->pokemon_effort[currentPokemon], parser->pokemon_misc[currentPokemon],
				parser->pokemon_growth[currentPokemon]);
}

void Window::switchPokemon()
{
	currentPokemon = switchPokemonSpinBox->value();
	loadPokemon(parser->pokemon[currentPokemon], parser->pokemon_attacks[currentPokemon],
				parser->pokemon_effort[currentPokemon], parser->pokemon_misc[currentPokemon],
				parser->pokemon_growth[currentPokemon]);
}

void Window::loadPokemon(belt_pokemon_t* pokemon, pokemon_attacks_t* pa, pokemon_effort_t* pe, pokemon_misc_t* pm, pokemon_growth_t* pg)
{
	pokePersonalityEdit->setText(QString::number(pokemon->personality, 16).toUpper());
	pokeNameEdit->setText(QString::fromLocal8Bit(parser->get_text(pokemon->name, true)));
	pokeTrainerIDEdit->setText(QString::number(pokemon->otid, 16).toUpper());
	pokeTrainerNameEdit->setText(QString::fromLocal8Bit(parser->get_text(pokemon->otname, false)));

	pokeStatusEdit->setCurrentIndex(pokemon->status);
	// QComboBox *pokeMarkEdit;
	pokePokeballEdit->setCurrentIndex(pokePokeballEdit->findData(QVariant(pm->pokeball)));
	// QComboBox *pokeLocationEdit;

	pokeHeldEdit->setCurrentIndex(pokeHeldEdit->findData(QVariant(pg->held)));
	pokeExperienceEdit->setText(QString::number(pg->xp));
	pokeLevelEdit->setText(QString::number(pokemon->level));
	pokeSpeciesEdit->setCurrentIndex(pokeSpeciesEdit->findData(QVariant(pg->species)));

	pokeAtk1->setCurrentIndex(pa->atk1);
	pokePP1->setValue(pa->pp1);
	pokeAtk2->setCurrentIndex(pa->atk2);
	pokePP2->setValue(pa->pp2);
	pokeAtk3->setCurrentIndex(pa->atk3);
	pokePP3->setValue(pa->pp3);
	pokeAtk4->setCurrentIndex(pa->atk4);
	pokePP4->setValue(pa->pp4);

	pokeHPEV->setValue(pe->hp);
	pokeAtkEV->setValue(pe->attack);
	pokeDefEV->setValue(pe->defense);
	pokeSpdEV->setValue(pe->speed);
	pokeSpAtkEV->setValue(pe->spatk);
	pokeSpDefEV->setValue(pe->spdef);
	// Total label will update itself since it is waiting on a signal from each spinbox
	// TODO: Add a validator to the above spin boxes to force a user to keep them <= 510

	pokeHPIV->setValue(pm->IVs.hp);
	pokeAtkIV->setValue(pm->IVs.atk);
	pokeDefIV->setValue(pm->IVs.def);
	pokeSpdIV->setValue(pm->IVs.spd);
	pokeSpAtkIV->setValue(pm->IVs.spatk);
	pokeSpDefIV->setValue(pm->IVs.spdef);
	// Total label will update itself since it is waiting on a signal from each spinbox
}

void Window::updateTotalEVs()
{
	pokeTotalEVs->setText("Total EVs: " + QString::number(pokeHPEV->value() + pokeAtkEV->value() + pokeDefEV->value() + \
										pokeSpdEV->value() + pokeSpAtkEV->value() + pokeSpDefEV->value()));
}

void Window::updateTotalIVs()
{
	pokeTotalIVs->setText("Total IVs: " + QString::number(pokeHPIV->value() + pokeAtkIV->value() + pokeDefIV->value() + \
										pokeSpdIV->value() + pokeSpAtkIV->value() + pokeSpDefIV->value()));
}

#undef Q_ASSERT
#define Q_ASSERT(x) {}while(0);

void Window::save()
{
	// Since GUI only keeps track of one pokemon, we can
	// only save the visible pokemon
	int i = currentPokemon;

	// Don't save personality or OTID for now
	//Q_ASSERT(parser->pokemon[i]->personality == pokePersonalityEdit->text().toInt(NULL, 16));
	//parser->pokemon[i]->personality = pokePersonalityEdit->text().toInt(NULL, 16);
	// pokeTrainerNameEdit;
	// pokeNameEdit->setText(QString::
	//Q_ASSERT(parser->pokemon[i]->otid == pokeTrainerIDEdit->text().toInt(NULL, 16));
	//parser->pokemon[i]->otid = pokeTrainerIDEdit->text().toInt(NULL, 16);

	parser->pokemon[i]->status = pokeStatusEdit->currentIndex();
	parser->pokemon_misc[i]->pokeball = pokePokeballEdit->currentIndex();

	parser->pokemon_growth[i]->held = pokeHeldEdit->itemData(pokeHeldEdit->currentIndex()).toInt();
	parser->pokemon_growth[i]->xp = pokeExperienceEdit->text().toInt();
	parser->pokemon_growth[i]->species = pokeSpeciesEdit->itemData(pokeSpeciesEdit->currentIndex()).toInt();

	parser->pokemon_attacks[i]->atk1 = pokeAtk1->itemData(pokeAtk1->currentIndex()).toInt();
	parser->pokemon_attacks[i]->pp1 = pokePP1->value();
	parser->pokemon_attacks[i]->atk2 = pokeAtk2->itemData(pokeAtk2->currentIndex()).toInt();
	parser->pokemon_attacks[i]->pp2 = pokePP2->value();
	parser->pokemon_attacks[i]->atk3 = pokeAtk3->itemData(pokeAtk3->currentIndex()).toInt();
	parser->pokemon_attacks[i]->pp3 = pokePP3->value();
	parser->pokemon_attacks[i]->atk4 = pokeAtk4->itemData(pokeAtk4->currentIndex()).toInt();
	parser->pokemon_attacks[i]->pp4 = pokePP4->value();

	// TODO: Assert total EVs are within limit
	parser->pokemon_effort[i]->hp = pokeHPEV->value();
	parser->pokemon_effort[i]->attack = pokeAtkEV->value();
	parser->pokemon_effort[i]->defense = pokeDefEV->value();
	parser->pokemon_effort[i]->speed = pokeSpdEV->value();
	parser->pokemon_effort[i]->spatk = pokeSpAtkEV->value();
	parser->pokemon_effort[i]->spdef = pokeSpDefEV->value();

	parser->pokemon_misc[i]->IVs.hp = pokeHPIV->value();
	parser->pokemon_misc[i]->IVs.atk = pokeAtkIV->value();
	parser->pokemon_misc[i]->IVs.def = pokeDefIV->value();
	parser->pokemon_misc[i]->IVs.spd = pokeSpdIV->value();
	parser->pokemon_misc[i]->IVs.spatk = pokeSpAtkIV->value();
	parser->pokemon_misc[i]->IVs.spdef = pokeSpDefIV->value();

	// Save pokemon to .sav file
	parser->save(openFileName.toLocal8Bit().data());
	// And re-loader it so that we can continue to work on it.
	parser->load(openFileName.toLocal8Bit().data(), gameEdit->currentIndex());
	// Re-load the pokemon into the GUI
	switchPokemon();
}

void Window::saveAs()
{
	
}

void Window::quit()
{
	exit(0);
}

Window::Window( QWidget* parent ) : QWidget( parent )
{
	// Grab parser instance
	parser = SaveParser::Instance();

	// Basic layout manager
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	QHBoxLayout* headerLayout = new QHBoxLayout();
	QFormLayout* headerLeftLayout = new QFormLayout();
	QFormLayout* headerRightLayout = new QFormLayout();
	QHBoxLayout* topLayout = new QHBoxLayout();
	QFormLayout* topLeftLayout = new QFormLayout();
	QFormLayout* topCentreLayout = new QFormLayout();
	QFormLayout* topRightLayout = new QFormLayout();
	QHBoxLayout* bottomLayout = new QHBoxLayout();
	
	// Create menus
	QMenu* file = new QMenu("&File");
	file->addAction( "Load savefile",  this, SLOT(loadSave()), Qt::CTRL+Qt::Key_L );
	file->addAction( "Save",  this, SLOT(save()), Qt::CTRL+Qt::Key_S );
	file->addAction( "Save As...",  this, SLOT(saveAs()), Qt::CTRL+Qt::ALT+Qt::Key_S );
	file->addAction( "Exit",  this, SLOT(quit()), Qt::CTRL+Qt::Key_Q );

	QMenu* help = new QMenu("&Help");
	help->addAction( "About", this, SLOT(About()), Qt::Key_F1 );

	// Select which game this file is from
	gameEdit = new GameComboBox();
	headerLeftLayout->addRow(tr("Game:"), gameEdit);

	// Add a mechanism to switch between current pokemon
	switchPokemonSpinBox = new QSpinBox();
	switchPokemonSpinBox->setRange(0, 5);
	QObject::connect(switchPokemonSpinBox, SIGNAL(valueChanged(int)), this, SLOT(switchPokemon()));
	headerRightLayout->addRow(tr("&Pokemon:"), switchPokemonSpinBox);

	// Basic pokemon data
	// Left
	pokeSpeciesEdit = new SpeciesComboBox();
	pokeLevelEdit = new QLineEdit();
	pokeLevelEdit->setEnabled(0);
	pokeHeldEdit = new ItemComboBox();
	pokeExperienceEdit = new QLineEdit();
	pokeExperienceEdit->setValidator(new QIntValidator(this));

	topLeftLayout->addRow(tr("&Species:"), pokeSpeciesEdit);
	topLeftLayout->addRow(tr("&Level:"), pokeLevelEdit);
	topLeftLayout->addRow(tr("&Item Held:"), pokeHeldEdit);
	topLeftLayout->addRow(tr("&Experience:"), pokeExperienceEdit);

	// Centre
	pokeNameEdit = new QLineEdit();
	pokeNameEdit->setMaxLength(10);
	pokeNameEdit->setEnabled(1);
	pokeTrainerIDEdit = new QLineEdit();
	pokeTrainerIDEdit->setValidator(new QIntValidator(this));
	pokeTrainerNameEdit = new QLineEdit();
	pokeTrainerNameEdit->setMaxLength(7);
	pokeTrainerNameEdit->setEnabled(1);
	pokePersonalityEdit = new QLineEdit();
	pokePersonalityEdit->setEnabled(0);
	pokePersonalityEdit->setValidator(new QIntValidator(this));

	topCentreLayout->addRow(tr("&Nick Name:"), pokeNameEdit);
	topCentreLayout->addRow(tr("Trainer &ID:"), pokeTrainerIDEdit);
	topCentreLayout->addRow(tr("&Trainer Name:"), pokeTrainerNameEdit);
	topCentreLayout->addRow(tr("&Personality:"), pokePersonalityEdit);

	// Right
	pokeStatusEdit = new StatusComboBox();
	pokeMarkEdit = new QComboBox();
	pokeMarkEdit->setEnabled(0);
	pokePokeballEdit = new PokeballComboBox();
	pokeLocationEdit = new QComboBox();
	pokeLocationEdit->setEnabled(0);

	topRightLayout->addRow(tr("S&tatus:"), pokeStatusEdit);
	topRightLayout->addRow(tr("&Mark:"), pokeMarkEdit);
	topRightLayout->addRow(tr("&Pokeball:"), pokePokeballEdit);
	topRightLayout->addRow(tr("&Location:"), pokeLocationEdit);
	
	// Pokemon Attacks
	QFormLayout *pokeAttackLayout = new QFormLayout();
	pokeAtk1 = new AttackComboBox();
	pokePP1 = new QSpinBox();
	pokePP1->setRange(0, 64);
	pokeAtk2 = new AttackComboBox();
	pokePP2 = new QSpinBox();
	pokePP2->setRange(0, 64);
	pokeAtk3 = new AttackComboBox();
	pokePP3 = new QSpinBox();
	pokePP3->setRange(0, 64);
	pokeAtk4 = new AttackComboBox();
	pokePP4 = new QSpinBox();
	pokePP4->setRange(0, 64);

	pokeAttackLayout->addRow(new QLabel(tr("Attacks:")));
	pokeAttackLayout->addRow(pokeAtk1, pokePP1);
	pokeAttackLayout->addRow(pokeAtk2, pokePP2);
	pokeAttackLayout->addRow(pokeAtk3, pokePP3);
	pokeAttackLayout->addRow(pokeAtk4, pokePP4);

	bottomLayout->addLayout(pokeAttackLayout);

	// Pokemon EVs
	pokeTotalEVs = new QLabel(tr("Total EVs: "));
	pokeHPEV = new QSpinBox();
	pokeHPEV->setRange(0, 255);
	QObject::connect(pokeHPEV, SIGNAL(valueChanged(int)), this, SLOT(updateTotalEVs()));
	pokeAtkEV = new QSpinBox();
	pokeAtkEV->setRange(0, 255);
	QObject::connect(pokeAtkEV, SIGNAL(valueChanged(int)), this, SLOT(updateTotalEVs()));
	pokeDefEV = new QSpinBox();
	pokeDefEV->setRange(0, 255);
	QObject::connect(pokeDefEV, SIGNAL(valueChanged(int)), this, SLOT(updateTotalEVs()));
	pokeSpdEV = new QSpinBox();
	pokeSpdEV->setRange(0, 255);
	QObject::connect(pokeSpdEV, SIGNAL(valueChanged(int)), this, SLOT(updateTotalEVs()));
	pokeSpAtkEV = new QSpinBox();
	pokeSpAtkEV->setRange(0, 255);
	QObject::connect(pokeSpAtkEV, SIGNAL(valueChanged(int)), this, SLOT(updateTotalEVs()));
	pokeSpDefEV = new QSpinBox();
	pokeSpDefEV->setRange(0, 255);
	QObject::connect(pokeSpDefEV, SIGNAL(valueChanged(int)), this, SLOT(updateTotalEVs()));
	QFormLayout *pokeEVsLayout = new QFormLayout();

	pokeEVsLayout->addRow(new QLabel(tr("EVs:")));
	pokeEVsLayout->addRow(tr("HP:"), pokeHPEV);
	pokeEVsLayout->addRow(tr("Atk:"), pokeAtkEV);
	pokeEVsLayout->addRow(tr("Def:"), pokeDefEV);
	pokeEVsLayout->addRow(tr("Spd:"), pokeSpdEV);
	pokeEVsLayout->addRow(tr("SpAtk:"), pokeSpAtkEV);
	pokeEVsLayout->addRow(tr("SpDef:"), pokeSpDefEV);
	pokeEVsLayout->addRow(pokeTotalEVs);

	bottomLayout->addLayout(pokeEVsLayout);

	// Pokemon IVs
	QFormLayout* pokeIVsLayout = new QFormLayout();
	pokeHPIV = new QSpinBox();
	pokeHPIV->setRange(0, 31);
	QObject::connect(pokeHPIV, SIGNAL(valueChanged(int)), this, SLOT(updateTotalIVs()));
	pokeAtkIV = new QSpinBox();
	pokeAtkIV->setRange(0, 31);
	QObject::connect(pokeAtkIV, SIGNAL(valueChanged(int)), this, SLOT(updateTotalIVs()));
	pokeDefIV = new QSpinBox();
	pokeDefIV->setRange(0, 31);
	QObject::connect(pokeDefIV, SIGNAL(valueChanged(int)), this, SLOT(updateTotalIVs()));
	pokeSpdIV = new QSpinBox();
	pokeSpdIV->setRange(0, 31);
	QObject::connect(pokeSpdIV, SIGNAL(valueChanged(int)), this, SLOT(updateTotalIVs()));
	pokeSpAtkIV = new QSpinBox();
	pokeSpAtkIV->setRange(0, 31);
	QObject::connect(pokeSpAtkIV, SIGNAL(valueChanged(int)), this, SLOT(updateTotalIVs()));
	pokeSpDefIV = new QSpinBox();
	pokeSpDefIV->setRange(0, 31);
	QObject::connect(pokeSpDefIV, SIGNAL(valueChanged(int)), this, SLOT(updateTotalIVs()));
	pokeTotalIVs = new QLabel(tr("Total IVs: "));

	pokeIVsLayout->addRow(new QLabel(tr("IVs:")));
	pokeIVsLayout->addRow(tr("HP:"), pokeHPIV);
	pokeIVsLayout->addRow(tr("Atk:"), pokeAtkIV);
	pokeIVsLayout->addRow(tr("Def:"), pokeDefIV);
	pokeIVsLayout->addRow(tr("Spd:"), pokeSpdIV);
	pokeIVsLayout->addRow(tr("SpAtk:"), pokeSpAtkIV);
	pokeIVsLayout->addRow(tr("SpDef:"), pokeSpDefIV);
	pokeIVsLayout->addRow(pokeTotalIVs);

	bottomLayout->addLayout(pokeIVsLayout);

	// Pokemon Growth
	QGridLayout* pokeGrowthLayout = new QGridLayout();

	bottomLayout->addLayout(pokeGrowthLayout);

	// Pokemon Misc
	QGridLayout* pokeMiscLayout = new QGridLayout();

	mainLayout->addLayout(headerLayout);
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(bottomLayout);

	headerLayout->addLayout(headerLeftLayout);
	headerLayout->addLayout(headerRightLayout);

	topLayout->addLayout(topLeftLayout);
	topLayout->addLayout(topCentreLayout);
	topLayout->addLayout(topRightLayout);
	
	bottomLayout->addLayout(pokeMiscLayout);

	// Create a menu bar
	QMenuBar* menu = new QMenuBar( this );
	menu->addSeparator();
	menu->addMenu( file );
	menu->addMenu( help );

	mainLayout->setMenuBar( menu );

	setLayout(mainLayout);
}
