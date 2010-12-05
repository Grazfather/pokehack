#ifndef WINDOW_H
#define WINDOW_H

#define WIN_W 400
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

#include <QDebug>

class Window : public QWidget
{
    Q_OBJECT

    public:
        Window( QWidget* parent = 0);

    signals:
        // Define any signals necessary

    public slots:
        // Define any slots
		void loadSave();
		void save();
		void saveAs();
		void quit();
    
    private:
        // Declare all widgets that will need to be accessed outside of the
        // constructor (for example, if you need to get the value of a slider)
		QLineEdit *pokePersonalityEdit;
		QLineEdit *pokeNameEdit;
		QLineEdit *pokeTrainerIDEdit;
		QLineEdit *pokeTrainerNameEdit;
		
		QComboBox *pokeStatusEdit;
		QComboBox *pokeMarkEdit;
		QComboBox *pokePokeballEdit;
		QComboBox *pokeLocationEdit;

		QComboBox *pokeHeldEdit;
		QLineEdit *pokeExperienceEdit;
		QLineEdit *pokeLevelEdit;
		QComboBox *pokeSpeciesEdit;
		
		QComboBox *pokeAtk1;
		QSpinBox *pokePP1;
		QComboBox *pokeAtk2;
		QSpinBox *pokePP2;
		QComboBox *pokeAtk3;
		QSpinBox *pokePP3;
		QComboBox *pokeAtk4;
		QSpinBox *pokePP4;
		
		QSpinBox *pokeHPEV;
		QSpinBox *pokeAtkEV;
		QSpinBox *pokeDefEV;
		QSpinBox *pokeSpdEV;
		QSpinBox *pokeSpAtkEV;
		QSpinBox *pokeSpDefEV;
		
		QSpinBox *pokeHPIV;
		QSpinBox *pokeAtkIV;
		QSpinBox *pokeDefIV;
		QSpinBox *pokeSpdIV;
		QSpinBox *pokeSpAtkIV;
		QSpinBox *pokeSpDefIV;
};

#endif
