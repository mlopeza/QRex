#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "diagramitem.h"

class DiagramScene;

class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow();

		//Funciones que se activan a cualquier suceso en la ventana principal
		private slots:
		//Cuando se da click al Button Group donde se encuentran los fondos
		void backgroundButtonGroupClicked(QAbstractButton *button);
		//Cuando se da click a un boton del Grupo
		void buttonGroupClicked(int id);
		//Cuando se borra un objecto
		void deleteItem();
	
		void pointerGroupClicked(int id);
		//Traer al frente
		void bringToFront();
		//Enviar atras
		void sendToBack();
		//Un objecto se inserta en escena
		void itemInserted(DiagramItem *item);
		//Un texto se inserta a la escena
		void textInserted(QGraphicsTextItem *item);
		//Se cambio la fuente
		void currentFontChanged(const QFont &font);
		//Se cambio el tamaño de la fuente
		void fontSizeChanged(const QString &size);
		//Cambio la escala de la escena
		void sceneScaleChanged(const QString &scale);
		//Se cambio el color del Texto
		void textColorChanged();
		//Se cambio el color del objeto
		void itemColorChanged();
		//Se cambio el color de la linea
		void lineColorChanged();
		//Se presiono el boton de texto
		void textButtonTriggered();
		//Se presiono el boton de relleno
		void fillButtonTriggered();
		//Se presiono el boton de linea
		void lineButtonTriggered();
		//Maneja el evento de cambio de fuente
		void handleFontChange();
		//Objeto seleccionado
		void itemSelected(QGraphicsItem *item);
		//Acerca de
		void about();

		//Se llama modificar Funcion
		void setProperties();
	
		void debugObject();

	private:
		//Crea el ToolBox que es donde se encuentran los objetos como eliminar, cambair font,etc.
		void createToolBox();
		//Crea las acciones que es cada uno de los objetos que van dentro del toolbox
		void createActions();
		//Crea el menu que va en la parte superior
		void createMenus();
		//Crea la barra de herramientas
		void createToolbars();

		//Funciones para crear los diferentes elementos del menu
		QWidget *createBackgroundCellWidget(const QString &text,const QString &image);
		QWidget *createCellWidget(const QString &text,DiagramItem::DiagramType type);
		QMenu *createColorMenu(const char *slot, QColor defaultColor);
		QIcon createColorToolButtonIcon(const QString &image, QColor color);
		QIcon createColorIcon(QColor color);
		
		//Crea la escena donde se va a dibujar y la vista donde ira la escena
		DiagramScene *scene;
		QGraphicsView *view;

		//Acciones de la clase que se insertan en los menus
		QAction *exitAction;
		QAction *addAction;
		QAction *deleteAction;

		QAction *toFrontAction;
		QAction *sendBackAction;
		QAction *aboutAction;
		QAction *changeProperties;
		QAction *objDebug;

		//Objetos del  Menu
		QMenu *fileMenu;
		QMenu *itemMenu;
		QMenu *aboutMenu;

		//Hay cuatro toolbars que pueden ser movidas por la pantalla
		QToolBar *textToolBar;
		QToolBar *editToolBar;
		QToolBar *colorToolBar;
		QToolBar *pointerToolbar;

		//Hay 5 combo box que se utilizan para escoger los valores a implementar
		QComboBox *sceneScaleCombo;
		QComboBox *itemColorCombo;
		QComboBox *textColorCombo;
		QComboBox *fontSizeCombo;
		QFontComboBox *fontCombo;

		//Botones para aceptar acciones seleccionadas
		QToolBox *toolBox;
		QButtonGroup *buttonGroup;
		QButtonGroup *pointerTypeGroup;
		QButtonGroup *backgroundButtonGroup;
		QToolButton *fontColorToolButton;
		QToolButton *fillColorToolButton;
		QToolButton *lineColorToolButton;
		QAction *boldAction;
		QAction *underlineAction;
		QAction *italicAction;
		QAction *textAction;
		QAction *fillAction;
		QAction *lineAction;
};

#endif
