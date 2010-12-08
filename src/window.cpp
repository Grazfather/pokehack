#include "window.h"
#include "SaveParser.h"
#include <iostream>

using namespace std;

void Window::loadSave()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open savestate"),
                    "./", tr("Savestates (*.*)") );
	SaveParser::Instance()->load(fileName.toLocal8Bit().data());
		
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
	
	pokeHPEV->setValue(SaveParser::Instance()->pokemon_effort[0]->hp);
	pokeAtkEV->setValue(SaveParser::Instance()->pokemon_effort[0]->attack);
	pokeDefEV->setValue(SaveParser::Instance()->pokemon_effort[0]->defense);
	pokeSpdEV->setValue(SaveParser::Instance()->pokemon_effort[0]->speed);
	pokeSpAtkEV->setValue(SaveParser::Instance()->pokemon_effort[0]->spatk);
	pokeSpDefEV->setValue(SaveParser::Instance()->pokemon_effort[0]->spdef);
	// Total label will update itself since it is waiting on a signal from each spinbox
	// TODO: Add a validator to the above spin boxes to force a user to keep them <= 510
	
	pokeHPIV->setValue(SaveParser::Instance()->pokemon_misc[0]->hpiv);
	pokeAtkIV->setValue(SaveParser::Instance()->pokemon_misc[0]->atkiv);
	pokeDefIV->setValue(SaveParser::Instance()->pokemon_misc[0]->defiv);
	pokeSpdIV->setValue(SaveParser::Instance()->pokemon_misc[0]->spdiv);
	pokeSpAtkIV->setValue(SaveParser::Instance()->pokemon_misc[0]->spatkiv);
	pokeSpDefIV->setValue(SaveParser::Instance()->pokemon_misc[0]->spdefiv);
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
