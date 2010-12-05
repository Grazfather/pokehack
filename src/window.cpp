#include "window.h"
#include "SaveParser.h"
#include <iostream>

using namespace std;

void Window::loadSave()
{
/*	QString fileName = QFileDialog::getOpenFileName(
                    "./saves",
                    "Save files",
                    this,
                    "load savestate",
                    "Choose a savestate" );*/
	// SaveParser::Instance()->load(fileName);
		
		pokePersonalityEdit->setText(QString::number(SaveParser::Instance()->pokemon[0]->personality, 16).toUpper());
		// QLineEdit *pokeNameEdit;
		pokeTrainerIDEdit->setText(QString::number(SaveParser::Instance()->pokemon[0]->otid, 16).toUpper());
		// QLineEdit *pokeTrainerNameEdit;
		
		// QComboBox *pokeStatusEdit;
		// QComboBox *pokeMarkEdit;
		// QComboBox *pokePokeballEdit;
		// QComboBox *pokeLocationEdit;

		// QComboBox *pokeHeldEdit;
		pokeExperienceEdit->setText(QString::number(SaveParser::Instance()->pokemon_growth[0]->xp));
		pokeLevelEdit->setText(QString::number(SaveParser::Instance()->pokemon[0]->level));
		// QComboBox *pokeSpeciesEdit;
		
		// QComboBox *pokeAtk1;
		pokePP1->setValue(SaveParser::Instance()->pokemon_attacks[0]->pp1);
		// QComboBox *pokeAtk2;
		pokePP2->setValue(SaveParser::Instance()->pokemon_attacks[0]->pp2);
		// QComboBox *pokeAtk3;
		pokePP3->setValue(SaveParser::Instance()->pokemon_attacks[0]->pp3);
		// QComboBox *pokeAtk4;
		pokePP4->setValue(SaveParser::Instance()->pokemon_attacks[0]->pp4);
		
		// QSpinBox *pokeHPEV;
		// QSpinBox *pokeAtkEV;
		// QSpinBox *pokeDefEV;
		// QSpinBox *pokeSpdEV;
		// QSpinBox *pokeSpAtkEV;
		// QSpinBox *pokeSpDefEV;
		
		// QSpinBox *pokeHPIV;
		// QSpinBox *pokeAtkIV;
		// QSpinBox *pokeDefIV;
		// QSpinBox *pokeSpdIV;
		// QSpinBox *pokeSpAtkIV;
		// QSpinBox *pokeSpDefIV;
}

void Window::save()
{
	
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
    // Basic layout manager
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
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
	
	// Basic pokemon data
	 // Left
	pokeNameEdit = new QLineEdit();
	pokeNameEdit->setMaxLength(10);
	pokeTrainerIDEdit = new QLineEdit();
	pokeTrainerIDEdit->setValidator(new QIntValidator(this));
	pokeTrainerNameEdit = new QLineEdit();
	pokeTrainerNameEdit->setMaxLength(7);
	pokePersonalityEdit = new QLineEdit();
	pokePersonalityEdit->setValidator(new QIntValidator(this));
	
	topLeftLayout->addRow(tr("&Nick Name:"), pokeNameEdit);
	topLeftLayout->addRow(tr("Trainer &ID:"), pokeTrainerIDEdit);
	topLeftLayout->addRow(tr("&Trainer Name:"), pokeTrainerNameEdit);
	topLeftLayout->addRow(tr("&Personality:"), pokePersonalityEdit);
	
	 // Centre
	pokeStatusEdit = new QComboBox();
	pokeMarkEdit = new QComboBox();
	pokePokeballEdit = new QComboBox();
	pokeLocationEdit = new QComboBox();

	topCentreLayout->addRow(tr("S&tatus:"), pokeStatusEdit);
	topCentreLayout->addRow(tr("&Mark:"), pokeMarkEdit);
	topCentreLayout->addRow(tr("&Pokeball:"), pokePokeballEdit);
	topCentreLayout->addRow(tr("&Location:"), pokeLocationEdit);
	
	 // Right
	QComboBox* pokeHeldEdit = new QComboBox();
	pokeExperienceEdit = new QLineEdit();
	pokeExperienceEdit->setValidator(new QIntValidator(this));
	pokeLevelEdit = new QLineEdit();
	pokeLevelEdit->setValidator(new QIntValidator(this));
	QComboBox* pokeSpeciesEdit = new QComboBox();

	topRightLayout->addRow(tr("&Item Held:"), pokeHeldEdit);
	topRightLayout->addRow(tr("&Experience:"), pokeExperienceEdit);
	topRightLayout->addRow(tr("&Level:"), pokeLevelEdit);
	topRightLayout->addRow(tr("&Species:"), pokeSpeciesEdit);
	
	// Pokemon Attacks
	QGridLayout *pokeAttackLayout = new QGridLayout();
	pokeAtk1 = new QComboBox();
	pokePP1 = new QSpinBox();
	pokePP1->setRange(0, 56);
	pokeAtk2 = new QComboBox();
	pokePP2 = new QSpinBox();
	pokePP2->setRange(0, 56);
	pokeAtk3 = new QComboBox();
	pokePP3 = new QSpinBox();
	pokePP3->setRange(0, 56);
	pokeAtk4 = new QComboBox();
	pokePP4 = new QSpinBox();
	pokePP4->setRange(0, 56);
	
	pokeAttackLayout->addWidget(new QLabel(tr("Attacks")), 0, 0);
	pokeAttackLayout->addWidget(pokeAtk1, 1, 0);
	pokeAttackLayout->addWidget(pokePP1, 1, 1);
	pokeAttackLayout->addWidget(pokeAtk2, 1, 2);
	pokeAttackLayout->addWidget(pokePP2, 1, 3);
	pokeAttackLayout->addWidget(pokeAtk3, 2, 0);
	pokeAttackLayout->addWidget(pokePP3, 2, 1);
	pokeAttackLayout->addWidget(pokeAtk4, 2, 2);
	pokeAttackLayout->addWidget(pokePP4, 2, 3);	
	
	bottomLayout->addLayout(pokeAttackLayout);
	
	// Pokemon EVs
	QFormLayout *pokeEVsLayout = new QFormLayout();
	pokeHPEV = new QSpinBox();
	pokeHPEV->setRange(0, 255);
	pokeAtkEV = new QSpinBox();
	pokeAtkEV->setRange(0, 255);
	pokeDefEV = new QSpinBox();
	pokeDefEV->setRange(0, 255);
	pokeSpdEV = new QSpinBox();
	pokeSpdEV->setRange(0, 255);
	pokeSpAtkEV = new QSpinBox();
	pokeSpAtkEV->setRange(0, 255);
	pokeSpDefEV = new QSpinBox();
	pokeSpDefEV->setRange(0, 255);
	QLabel *pokeTotalEVs = new QLabel(tr("Total EVs: "));
	
	pokeEVsLayout->addWidget(new QLabel(tr("EVs")));
	pokeEVsLayout->addRow(tr("HP:"), pokeHPEV);
	pokeEVsLayout->addRow(tr("Atk:"), pokeAtkEV);
	pokeEVsLayout->addRow(tr("Def:"), pokeDefEV);
	pokeEVsLayout->addRow(tr("Spd:"), pokeSpdEV);
	pokeEVsLayout->addRow(tr("SpAtk:"), pokeSpAtkEV);
	pokeEVsLayout->addRow(tr("SpDef:"), pokeSpDefEV);
	pokeEVsLayout->addWidget(pokeTotalEVs);
	
	bottomLayout->addLayout(pokeEVsLayout);
	
	// Pokemon IVs
	QFormLayout* pokeIVsLayout = new QFormLayout();
	pokeHPIV = new QSpinBox();
	pokeHPIV->setRange(0, 31);
	pokeAtkIV = new QSpinBox();
	pokeAtkIV->setRange(0, 31);
	pokeDefIV = new QSpinBox();
	pokeDefIV->setRange(0, 31);
	pokeSpdIV = new QSpinBox();
	pokeSpdIV->setRange(0, 31);
	pokeSpAtkIV = new QSpinBox();
	pokeSpAtkIV->setRange(0, 31);
	pokeSpDefIV = new QSpinBox();
	pokeSpDefIV->setRange(0, 31);
	QLabel *pokeTotalIVs = new QLabel(tr("Total IVs: "));
	
	pokeIVsLayout->addWidget(new QLabel(tr("IVs")));
	pokeIVsLayout->addRow(tr("HP:"), pokeHPIV);
	pokeIVsLayout->addRow(tr("Atk:"), pokeAtkIV);
	pokeIVsLayout->addRow(tr("Def:"), pokeDefIV);
	pokeIVsLayout->addRow(tr("Spd:"), pokeSpdIV);
	pokeIVsLayout->addRow(tr("SpAtk:"), pokeSpAtkIV);
	pokeIVsLayout->addRow(tr("SpDef:"), pokeSpDefIV);
	pokeIVsLayout->addWidget(pokeTotalIVs);
	
	bottomLayout->addLayout(pokeIVsLayout);
	
	// Pokemon Growth
	QGridLayout* pokeGrowthLayout = new QGridLayout();
	
	bottomLayout->addLayout(pokeGrowthLayout);
	
	// Pokemon Misc
	QGridLayout* pokeMiscLayout = new QGridLayout();
	
	bottomLayout->addLayout(pokeMiscLayout);
	
	mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
	
	topLayout->addLayout(topLeftLayout);
	topLayout->addLayout(topCentreLayout);
	topLayout->addLayout(topRightLayout);
	
    // Create a menu bar
    QMenuBar* menu = new QMenuBar( this );
    menu->addSeparator();
    menu->addMenu( file );
    menu->addMenu( help );
	mainLayout->setMenuBar( menu );
	
	setLayout(mainLayout);
}
