#include "window.h"
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
	// Parser->parseSave(fileName);
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
    file->addAction( "Load savestate",  this, SLOT(loadModel()), Qt::CTRL+Qt::Key_L );
    file->addAction( "Save",  this, SLOT(save()), Qt::CTRL+Qt::Key_S );
	file->addAction( "Save As...",  this, SLOT(saveAs()), Qt::CTRL+Qt::ALT+Qt::Key_S );
    file->addAction( "Exit",  this, SLOT(quit()), Qt::CTRL+Qt::Key_Q );

    QMenu* help = new QMenu("&Help");
    help->addAction( "About", this, SLOT(About()), Qt::Key_F1 );
	
	// Basic pokemon data
	 // Left
	QLineEdit* pokeNameEdit = new QLineEdit();
	pokeNameEdit->setMaxLength(10);
	QLineEdit* pokeTrainerIDEdit = new QLineEdit();
	pokeTrainerIDEdit->setValidator(new QIntValidator(this));
	QLineEdit* pokeTrainerNameEdit = new QLineEdit();
	pokeTrainerNameEdit->setMaxLength(7);
	QLineEdit* pokePersonalityEdit = new QLineEdit();
	pokePersonalityEdit->setValidator(new QIntValidator(this));
	
	topLeftLayout->addRow(tr("&Nick Name:"), pokeNameEdit);
	topLeftLayout->addRow(tr("Trainer &ID:"), pokeTrainerIDEdit);
	topLeftLayout->addRow(tr("&Trainer Name:"), pokeTrainerNameEdit);
	topLeftLayout->addRow(tr("&Personality:"), pokePersonalityEdit);
	
	 // Centre

	QComboBox* pokeSpeciesnEdit = new QComboBox();
	QComboBox* pokeMarkEdit = new QComboBox();
	QComboBox* pokePokeballEdit = new QComboBox();
	QComboBox* pokeLocationEdit = new QComboBox();

	topCentreLayout->addRow(tr("&Species:"), pokeSpeciesnEdit);
	topCentreLayout->addRow(tr("&Mark:"), pokeMarkEdit);
	topCentreLayout->addRow(tr("&Pokeball:"), pokePokeballEdit);
	topCentreLayout->addRow(tr("&Location:"), pokeLocationEdit);
	
	 // Right
	QComboBox* pokeHeldEdit = new QComboBox();
	QLineEdit* pokeExperienceEdit = new QLineEdit();
	pokeExperienceEdit->setValidator(new QIntValidator(this));
	QLineEdit* pokeLevelEdit = new QLineEdit();
	pokeLevelEdit->setValidator(new QIntValidator(this));
	QComboBox* pokeSpeciesEdit = new QComboBox();

	topRightLayout->addRow(tr("&Item Held:"), pokeHeldEdit);
	topRightLayout->addRow(tr("&Experience:"), pokeExperienceEdit);
	topRightLayout->addRow(tr("&Level:"), pokeLevelEdit);
	topRightLayout->addRow(tr("&Species:"), pokeSpeciesEdit);
	
	// Pokemon Attacks
	QGridLayout* pokeAttackLayout = new QGridLayout();
	QComboBox* pokeAtk1 = new QComboBox();
	QSpinBox* pokePP1 = new QSpinBox();
	pokePP1->setRange(0, 56);
	QComboBox* pokeAtk2 = new QComboBox();
	QSpinBox* pokePP2 = new QSpinBox();
	pokePP2->setRange(0, 56);
	QComboBox* pokeAtk3 = new QComboBox();
	QSpinBox* pokePP3 = new QSpinBox();
	pokePP3->setRange(0, 56);
	QComboBox* pokeAtk4 = new QComboBox();
	QSpinBox* pokePP4 = new QSpinBox();
	pokePP4->setRange(0, 56);
	
	pokeAttackLayout->addWidget(pokeAtk1, 0, 0);
	pokeAttackLayout->addWidget(pokePP1, 0, 1);
	pokeAttackLayout->addWidget(pokeAtk2, 0, 2);
	pokeAttackLayout->addWidget(pokePP2, 0, 3);
	pokeAttackLayout->addWidget(pokeAtk3, 1, 0);
	pokeAttackLayout->addWidget(pokePP3, 1, 1);
	pokeAttackLayout->addWidget(pokeAtk4, 1, 2);
	pokeAttackLayout->addWidget(pokePP4, 1, 3);	
	
	bottomLayout->addLayout(pokeAttackLayout);
	
	// Pokemon EVs
	QFormLayout* pokeEVsLayout = new QFormLayout();
	QSpinBox* pokeHPEV = new QSpinBox();
	pokeHPEV->setRange(0, 255);
	QSpinBox* pokeAtkEV = new QSpinBox();
	pokeAtkEV->setRange(0, 255);
	QSpinBox* pokeDefEV = new QSpinBox();
	pokeDefEV->setRange(0, 255);
	QSpinBox* pokeSpdEV = new QSpinBox();
	pokeSpdEV->setRange(0, 255);
	QSpinBox* pokeSpAtkEV = new QSpinBox();
	pokeSpAtkEV->setRange(0, 255);
	QSpinBox* pokeSpDefEV = new QSpinBox();
	pokeSpDefEV->setRange(0, 255);
	QLabel* pokeTotalEVs = new QLabel(tr("Total Evs: "));
	
	pokeEVsLayout->addRow(tr("HP:"), pokeHPEV);
	pokeEVsLayout->addRow(tr("Atk:"), pokeAtkEV);
	pokeEVsLayout->addRow(tr("Def:"), pokeDefEV);
	pokeEVsLayout->addRow(tr("Spd:"), pokeSpdEV);
	pokeEVsLayout->addRow(tr("SpAtk:"), pokeSpAtkEV);
	pokeEVsLayout->addRow(tr("SpDef:"), pokeSpDefEV);
	pokeEVsLayout->addWidget(pokeTotalEVs);
	
	bottomLayout->addLayout(pokeEVsLayout);
	
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
