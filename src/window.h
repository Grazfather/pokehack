#ifndef WINDOW_H
#define WINDOW_H

#define WIN_W 400
#define WIN_H 400

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
};

#endif
