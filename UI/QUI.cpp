#include <QApplication>
#include <QMainWindow>
#include "ui_UI.h"

int main(int argc, char *argv[]){
	QApplication app(argc,argv);
	Ui::MainWindow userInterface;
	QMainWindow *main = new QMainWindow;
	userInterface.setupUi(main);
	main->show();
	return app.exec();
}
