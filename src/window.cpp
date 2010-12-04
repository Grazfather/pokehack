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
		char *s;
		qDebug() << "Test: " << s << endl;
		itoa(SaveParser::Instance()->pokemon_growth[0]->xp, s, 10);
		pokeExperienceEdit->setText(s);
		itoa(SaveParser::Instance()->pokemon[0]->level, s, 10);
		pokeLevelEdit->setText(s);
		itoa(SaveParser::Instance()->pokemon[0]->personality, s, 10);
		pokePersonalityEdit->setText(s);
	
}

void Window::save()
{
	
}

void Window::saveAs()
{
	
}

void Window::quit()
{
	qDebug() << "TEst\n";
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
	QComboBox* pokeStatusEdit = new QComboBox();
	QComboBox* pokeMarkEdit = new QComboBox();
	QComboBox* pokePokeballEdit = new QComboBox();
	QComboBox* pokeLocationEdit = new QComboBox();

	topCentreLayout->addRow(tr("S&tatus:"), pokeStatusEdit);
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
	QLabel* pokeAttacksTitle = new QLabel(tr("Attacks"));
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
	
	pokeAttackLayout->addWidget(pokeAttacksTitle, 0, 0);
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
	QLabel* pokeEVsTitle = new QLabel(tr("EVs"));
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
	QLabel* pokeTotalEVs = new QLabel(tr("Total EVs: "));
	
	pokeEVsLayout->addWidget(pokeEVsTitle);
	pokeEVsLayout->addRow(tr("HP:"), pokeHPEV);
	pokeEVsLayout->addRow(tr("Atk:"), pokeAtkEV);
	pokeEVsLayout->addRow(tr("Def:"), pokeDefEV);
	pokeEVsLayout->addRow(tr("Spd:"), pokeSpdEV);
	pokeEVsLayout->addRow(tr("SpAtk:"), pokeSpAtkEV);
	pokeEVsLayout->addRow(tr("SpDef:"), pokeSpDefEV);
	pokeEVsLayout->addWidget(pokeTotalEVs);
	
	bottomLayout->addLayout(pokeEVsLayout);
	
	// Pokemon IVs
	QLabel* pokeIVsTitle = new QLabel(tr("IVs"));
	QFormLayout* pokeIVsLayout = new QFormLayout();
	QSpinBox* pokeHPIV = new QSpinBox();
	pokeHPIV->setRange(0, 31);
	QSpinBox* pokeAtkIV = new QSpinBox();
	pokeAtkIV->setRange(0, 31);
	QSpinBox* pokeDefIV = new QSpinBox();
	pokeDefIV->setRange(0, 31);
	QSpinBox* pokeSpdIV = new QSpinBox();
	pokeSpdIV->setRange(0, 31);
	QSpinBox* pokeSpAtkIV = new QSpinBox();
	pokeSpAtkIV->setRange(0, 31);
	QSpinBox* pokeSpDefIV = new QSpinBox();
	pokeSpDefIV->setRange(0, 31);
	QLabel* pokeTotalIVs = new QLabel(tr("Total IVs: "));
	
	pokeIVsLayout->addWidget(pokeIVsTitle);
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
