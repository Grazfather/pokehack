#include "window.h"
#include <QtDebug>
#include <iostream>

void Window::loadSave()
{
	int err;
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open savestate"),
						"./../..", tr("Savestates (*.*)") );

	err = parser->load(fileName.toLocal8Bit().data());
	if (err)
	{
		return;
	}
	openFileName = fileName;

	pokePersonalityEdit->setText(QString::number(parser->pokemon[0]->personality, 16).toUpper());
	// TODO: Convert the nickname to ASCII
	// pokeNameEdit->setText(QString::
	pokeTrainerIDEdit->setText(QString::number(parser->pokemon[0]->otid, 16).toUpper());
	// QLineEdit *pokeTrainerNameEdit;

	pokeStatusEdit->setCurrentIndex(parser->pokemon[0]->status);
	// QComboBox *pokeMarkEdit;
	pokePokeballEdit->setCurrentIndex(pokePokeballEdit->findData(QVariant(parser->pokemon_misc[0]->pokeball)));
	// QComboBox *pokeLocationEdit;

	pokeHeldEdit->setCurrentIndex(pokeHeldEdit->findData(QVariant(parser->pokemon_growth[0]->held)));
	pokeExperienceEdit->setText(QString::number(parser->pokemon_growth[0]->xp));
	pokeLevelEdit->setText(QString::number(parser->pokemon[0]->level));
	pokeSpeciesEdit->setCurrentIndex(pokeSpeciesEdit->findData(QVariant(parser->pokemon_growth[0]->species)));

	pokeAtk1->setCurrentIndex(parser->pokemon_attacks[0]->atk1);
	pokePP1->setValue(parser->pokemon_attacks[0]->pp1);
	pokeAtk2->setCurrentIndex(parser->pokemon_attacks[0]->atk2);
	pokePP2->setValue(parser->pokemon_attacks[0]->pp2);
	pokeAtk3->setCurrentIndex(parser->pokemon_attacks[0]->atk3);
	pokePP3->setValue(parser->pokemon_attacks[0]->pp3);
	pokeAtk4->setCurrentIndex(parser->pokemon_attacks[0]->atk4);
	pokePP4->setValue(parser->pokemon_attacks[0]->pp4);

	pokeHPEV->setValue(parser->pokemon_effort[0]->hp);
	pokeAtkEV->setValue(parser->pokemon_effort[0]->attack);
	pokeDefEV->setValue(parser->pokemon_effort[0]->defense);
	pokeSpdEV->setValue(parser->pokemon_effort[0]->speed);
	pokeSpAtkEV->setValue(parser->pokemon_effort[0]->spatk);
	pokeSpDefEV->setValue(parser->pokemon_effort[0]->spdef);
	// Total label will update itself since it is waiting on a signal from each spinbox
	// TODO: Add a validator to the above spin boxes to force a user to keep them <= 510

	pokeHPIV->setValue(parser->pokemon_misc[0]->hpiv);
	pokeAtkIV->setValue(parser->pokemon_misc[0]->atkiv);
	pokeDefIV->setValue(parser->pokemon_misc[0]->defiv);
	pokeSpdIV->setValue(parser->pokemon_misc[0]->spdiv);
	pokeSpAtkIV->setValue(parser->pokemon_misc[0]->spatkiv);
	pokeSpDefIV->setValue(parser->pokemon_misc[0]->spdefiv);
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
	int i = 0; // For now we're only viewing/saving first pokemon

	// Save values back to ramfile

	// Don't save personality or OTID for now
	//Q_ASSERT(parser->pokemon[i]->personality == pokePersonalityEdit->text().toInt(NULL, 16));
	//parser->pokemon[i]->personality = pokePersonalityEdit->text().toInt(NULL, 16);
	// pokeTrainerNameEdit;
	// pokeNameEdit->setText(QString::
	//Q_ASSERT(parser->pokemon[i]->otid == pokeTrainerIDEdit->text().toInt(NULL, 16));
	//parser->pokemon[i]->otid = pokeTrainerIDEdit->text().toInt(NULL, 16);

	Q_ASSERT(parser->pokemon[i]->status == pokeStatusEdit->currentIndex());
	parser->pokemon[i]->status = pokeStatusEdit->currentIndex();
	// QComboBox *pokeMarkEdit;
	Q_ASSERT(parser->pokemon_misc[i]->pokeball == pokePokeballEdit->currentIndex());
	parser->pokemon_misc[i]->pokeball = pokePokeballEdit->currentIndex();
	// QComboBox *pokeLocationEdit;

	Q_ASSERT(parser->pokemon_growth[i]->held == pokeHeldEdit->itemData(pokeHeldEdit->currentIndex()).toInt());
	parser->pokemon_growth[i]->held = pokeHeldEdit->itemData(pokeHeldEdit->currentIndex()).toInt();
	Q_ASSERT(parser->pokemon_growth[i]->xp == pokeExperienceEdit->text().toInt());
	parser->pokemon_growth[i]->xp = pokeExperienceEdit->text().toInt();
	Q_ASSERT(parser->pokemon[i]->level == pokeLevelEdit->text().toInt());
	parser->pokemon[i]->level = pokeLevelEdit->text().toInt();
	//Q_ASSERT(parser->pokemon_growth[i]->species == pokeSpeciesEdit->itemData(pokeSpeciesEdit->currentIndex()).toInt());
	parser->pokemon_growth[i]->species = pokeSpeciesEdit->itemData(pokeSpeciesEdit->currentIndex()).toInt();

	//Q_ASSERT(parser->pokemon_attacks[i]->atk1 == pokeAtk1->itemData(pokeAtk1->currentIndex()).toInt());
	parser->pokemon_attacks[i]->atk1 = pokeAtk1->itemData(pokeAtk1->currentIndex()).toInt();
	Q_ASSERT(parser->pokemon_attacks[i]->pp1 == pokePP1->value());
	parser->pokemon_attacks[i]->pp1 = pokePP1->value();
	//Q_ASSERT(parser->pokemon_attacks[i]->atk2 == pokeAtk2->itemData(pokeAtk2->currentIndex()).toInt());
	parser->pokemon_attacks[i]->atk2 = pokeAtk2->itemData(pokeAtk2->currentIndex()).toInt();
	Q_ASSERT(parser->pokemon_attacks[i]->pp2 == pokePP2->value());
	parser->pokemon_attacks[i]->pp2 = pokePP2->value();
	//Q_ASSERT(parser->pokemon_attacks[i]->atk3 == pokeAtk3->itemData(pokeAtk3->currentIndex()).toInt());
	parser->pokemon_attacks[i]->atk3 = pokeAtk3->itemData(pokeAtk3->currentIndex()).toInt();
	Q_ASSERT(parser->pokemon_attacks[i]->pp3 == pokePP3->value());
	parser->pokemon_attacks[i]->pp3 = pokePP3->value();
	//Q_ASSERT(parser->pokemon_attacks[i]->atk4 == pokeAtk4->itemData(pokeAtk4->currentIndex()).toInt());
	parser->pokemon_attacks[i]->atk4 = pokeAtk4->itemData(pokeAtk4->currentIndex()).toInt();
	Q_ASSERT(parser->pokemon_attacks[i]->pp4 == pokePP4->value());
	parser->pokemon_attacks[i]->pp4 = pokePP4->value();

	Q_ASSERT(parser->pokemon_effort[i]->hp == pokeHPEV->value());
	parser->pokemon_effort[i]->hp = pokeHPEV->value();
	Q_ASSERT(parser->pokemon_effort[i]->attack == pokeAtkEV->value());
	parser->pokemon_effort[i]->attack = pokeAtkEV->value();
	Q_ASSERT(parser->pokemon_effort[i]->defense == pokeDefEV->value());
	parser->pokemon_effort[i]->defense = pokeDefEV->value();
	Q_ASSERT(parser->pokemon_effort[i]->speed == pokeSpdEV->value());
	parser->pokemon_effort[i]->speed = pokeSpdEV->value();
	Q_ASSERT(parser->pokemon_effort[i]->spatk == pokeSpAtkEV->value());
	parser->pokemon_effort[i]->spatk = pokeSpAtkEV->value();
	Q_ASSERT(parser->pokemon_effort[i]->spdef == pokeSpDefEV->value());
	parser->pokemon_effort[i]->spdef = pokeSpDefEV->value();
	// TODO: Assert total EVs are within limit
/*
	Q_ASSERT(parser->pokemon_misc[i]->hpiv == pokeHPIV->value());
	parser->pokemon_misc[i]->hpiv = pokeHPIV->value();
	Q_ASSERT(parser->pokemon_misc[i]->atkiv == pokeAtkIV->value());
	parser->pokemon_misc[i]->atkiv = pokeAtkIV->value();
	Q_ASSERT(parser->pokemon_misc[i]->defiv == pokeDefIV->value());
	parser->pokemon_misc[i]->defiv = pokeDefIV->value();
	Q_ASSERT(parser->pokemon_misc[i]->spdiv == pokeSpdIV->value());
	parser->pokemon_misc[i]->spdiv = pokeSpdIV->value();
	Q_ASSERT(parser->pokemon_misc[i]->spatkiv == pokeSpAtkIV->value());
	parser->pokemon_misc[i]->spatkiv = pokeSpAtkIV->value();
	Q_ASSERT(parser->pokemon_misc[i]->spdefiv == pokeSpDefIV->value());
	parser->pokemon_misc[i]->spdefiv = pokeSpDefIV->value();
parser->pokemon_misc[i]->egg = 0;
parser->pokemon_misc[i]->ability = 0;*/
	// Save ramfile back to disk
	parser->save(openFileName.toLocal8Bit().data());
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
	QFormLayout* headerLayout = new QFormLayout();
	QHBoxLayout* topLayout = new QHBoxLayout();
	QFormLayout* topLeftLayout = new QFormLayout();
	QFormLayout* topCentreLayout = new QFormLayout();
	QFormLayout* topRightLayout = new QFormLayout();
	QHBoxLayout* bottomLayout = new QHBoxLayout();
	
	// Create menus
	QMenu* file = new QMenu("&File");
	file->addAction( "Load savestate",  this, SLOT(loadSave()), Qt::CTRL+Qt::Key_L );
	file->addAction( "Save",  this, SLOT(save()), Qt::CTRL+Qt::Key_S );
	file->addAction( "Save As...",  this, SLOT(saveAs()), Qt::CTRL+Qt::ALT+Qt::Key_S );
	file->addAction( "Exit",  this, SLOT(quit()), Qt::CTRL+Qt::Key_Q );

	QMenu* help = new QMenu("&Help");
	help->addAction( "About", this, SLOT(About()), Qt::Key_F1 );

	// Select which game this file is from
	// TODO: Detect this automatically
	gameEdit = new GameComboBox();
	headerLayout->addRow(tr("Game:"), gameEdit);

	// Basic pokemon data
	// Left
	pokeSpeciesEdit = new SpeciesComboBox();
	pokeLevelEdit = new QLineEdit();
	pokeLevelEdit->setValidator(new QIntValidator(this));
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
	pokeTrainerIDEdit = new QLineEdit();
	pokeTrainerIDEdit->setValidator(new QIntValidator(this));
	pokeTrainerNameEdit = new QLineEdit();
	pokeTrainerNameEdit->setMaxLength(7);
	pokePersonalityEdit = new QLineEdit();
	pokePersonalityEdit->setValidator(new QIntValidator(this));
	
	topCentreLayout->addRow(tr("&Nick Name:"), pokeNameEdit);
	topCentreLayout->addRow(tr("Trainer &ID:"), pokeTrainerIDEdit);
	topCentreLayout->addRow(tr("&Trainer Name:"), pokeTrainerNameEdit);
	topCentreLayout->addRow(tr("&Personality:"), pokePersonalityEdit);
	
	// Right
	pokeStatusEdit = new StatusComboBox();
	pokeMarkEdit = new QComboBox();
	pokePokeballEdit = new PokeballComboBox();
	pokeLocationEdit = new QComboBox();

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
