#ifndef POKEBALLCOMBOBOX_H
#define POKEBALLCOMBOBOX_H

// Include all the headers for the Qt widgets you will be using
#include <QComboBox>

class PokeballComboBox : public QComboBox
{
	Q_OBJECT

	public:
		PokeballComboBox( QWidget* parent = 0);

	signals:
		// Define any signals necessary

	public slots:
		// Define any slots
	
	private:
		// Declare all widgets that will need to be accessed outside of the
		// constructor (for example, if you need to get the value of a slider)
};

#endif