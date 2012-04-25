#include <QtGui>
#include <QLabel>

#include "mainwindow.h"
#include "diagramitem.h"
#include "diagramscene.h"
#include "diagramtextitem.h"
#include "arrow.h"

const int InsertTextButton = 10;

MainWindow::MainWindow()
{
	//Crea la pantalla
	createActions();
	createToolBox();
	createMenus();
	
	//Se crea la escena
	scene = new DiagramScene(itemMenu, this);

	//Se le asigna un tamaño maximo a la escena
	scene->setSceneRect(QRectF(0, 0, 5000, 5000));

	//Se hacen las conexiones de eventos
	//Cuando se inserta un Una figura al diagrama	
	connect(scene, SIGNAL(itemInserted(DiagramItem*)),
		this, SLOT(itemInserted(DiagramItem*)));

	//Cuando se inserta texto al diagrama
	connect(scene, SIGNAL(textInserted(QGraphicsTextItem*)),
		this, SLOT(textInserted(QGraphicsTextItem*)));

	//Cuando se selecciona un Objeto de la escena
	connect(scene, SIGNAL(itemSelected(QGraphicsItem*)),
		this, SLOT(itemSelected(QGraphicsItem*)));

	//Crea las barras de herramientas
	createToolbars();

	//Los layouts que le dan la forma a la ventana
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(toolBox);
	view = new QGraphicsView(scene);
	layout->addWidget(view);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	setCentralWidget(widget);
	setWindowTitle(tr("QRex"));
	setUnifiedTitleAndToolBarOnMac(true);
}

//Estas acciones se hacen cuando se selecciona un fondo
void MainWindow::backgroundButtonGroupClicked(QAbstractButton *button)
{
	//Se obtienen todos los botones del background
	//Y se comparan con el que se recibio, de esta forma se pone como
	//Selecionado solo el que se recibio
	QList<QAbstractButton *> buttons = backgroundButtonGroup->buttons();
	foreach (QAbstractButton *myButton, buttons) {
		if (myButton != button)
			button->setChecked(false);
	}

	//Se obtiene el nombre del boton
	//Y se selecciona el background correspondiente
	QString text = button->text();
	if (text == tr("Blue Grid"))
		scene->setBackgroundBrush(QPixmap(":/images/background1.png"));
	else if (text == tr("White Grid"))
		scene->setBackgroundBrush(QPixmap(":/images/background2.png"));
	else if (text == tr("Gray Grid"))
		scene->setBackgroundBrush(QPixmap(":/images/background3.png"));
	else
		scene->setBackgroundBrush(QPixmap(":/images/background4.png"));

	//Se actualiza la escena y la vista
	//Para que cambie el fondo
	scene->update();
	view->update();
}

//Cuando se da click a un boton del grupo de botones
//Del area de diagramas
void MainWindow::buttonGroupClicked(int id)
{
	//Se deselcciona el boton seleccionado anteriormente
	QList<QAbstractButton *> buttons = buttonGroup->buttons();
	foreach (QAbstractButton *button, buttons) {
		if (buttonGroup->button(id) != button)
			button->setChecked(false);
	}

	//Si es un texto, se inserta texto
	//De lo contrario es un elemnto de diagrama
	//Asi que se obtiene el tipo y se manda insertar
	if (id == InsertTextButton) {
		scene->setMode(DiagramScene::InsertText);
	} else {
		scene->setItemType(DiagramItem::DiagramType(id));
		scene->setMode(DiagramScene::InsertItem);
	}
}

//Cuando se desean eliminar objetos con el boton de delete
void MainWindow::deleteItem()
{
	//Todos los objetos seleccionados pasan por el foreach
	foreach (QGraphicsItem *item, scene->selectedItems()) {
		//Si es del tipo flecha deben eliminarse las referencias
		if (item->type() == Arrow::Type) {
			scene->removeItem(item);
			Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
			arrow->startItem()->removeArrow(arrow);
			arrow->endItem()->removeArrow(arrow);
			delete item;
		}
	}

	//Si es del tipo ELemento de diagrama se remueven las
	//flechas y se elimina el objeto
	//Si no significa que solo es texto y se elimina
	foreach (QGraphicsItem *item, scene->selectedItems()) {
		if (item->type() == DiagramItem::Type) {
			qgraphicsitem_cast<DiagramItem *>(item)->removeArrows();
		}
		scene->removeItem(item);
		delete item;
	}
}

//Se selecciona el tipo de apuntador, si es flecha o seleccion
void MainWindow::pointerGroupClicked(int)
{
	scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

//Trae un objeto al frente de otro situandolo en una coordenada z superior
void MainWindow::bringToFront()
{
	if (scene->selectedItems().isEmpty())
		return;

	QGraphicsItem *selectedItem = scene->selectedItems().first();
	QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

	qreal zValue = 0;
	foreach (QGraphicsItem *item, overlapItems) {
		if (item->zValue() >= zValue &&
				item->type() == DiagramItem::Type)
			zValue = item->zValue() + 0.1;
	}
	selectedItem->setZValue(zValue);
}

//Manda un objeto a atras
void MainWindow::sendToBack()
{
	if (scene->selectedItems().isEmpty())
		return;

	QGraphicsItem *selectedItem = scene->selectedItems().first();
	QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

	qreal zValue = 0;
	foreach (QGraphicsItem *item, overlapItems) {
		if (item->zValue() <= zValue &&
				item->type() == DiagramItem::Type)
			zValue = item->zValue() - 0.1;
	}
	selectedItem->setZValue(zValue);
}

//Un objeto es insertado
void MainWindow::itemInserted(DiagramItem *item)
{
	//Se selecciona el Elemento del diagrama que se acaba de insertar
	pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
	//Se asigna el modo a la escena para saber que acciones se pueden ejecutar
	scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
	//Se deselecciona el boton del objeto a insertar
	buttonGroup->button(int(item->diagramType()))->setChecked(false);
}

//CUando se quiere insertar texto en la escena
void MainWindow::textInserted(QGraphicsTextItem *)
{
	//Se deselecciona el boton de insertar texto
	buttonGroup->button(InsertTextButton)->setChecked(false);
	//Se da la accion a ejecutar a la escena
	scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

//CUando se cambia la fuente
void MainWindow::currentFontChanged(const QFont &)
{
	handleFontChange();
}

//CUando se cambia el tamaño de la fuente
void MainWindow::fontSizeChanged(const QString &)
{
	handleFontChange();
}

//Se cambia la escala de al fuente
void MainWindow::sceneScaleChanged(const QString &scale)
{
	//Aqui se definen las acciones a la hora de cambiar el
	//Tamaño de todo, esto lo hace automaticamente el GraphicsView
	//SOlo hay que definir la escala a la cual se debe cambiar
	double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
	QMatrix oldMatrix = view->matrix();
	view->resetMatrix();
	view->translate(oldMatrix.dx(), oldMatrix.dy());
	view->scale(newScale, newScale);
}

//Accion al cambiar el colo de fuente
void MainWindow::textColorChanged()
{
	textAction = qobject_cast<QAction *>(sender());
	fontColorToolButton->setIcon(createColorToolButtonIcon(
				":/images/textpointer.png",
				qVariantValue<QColor>(textAction->data())));
	textButtonTriggered();
}

//CUando se cambia un color de objeto
void MainWindow::itemColorChanged()
{
	fillAction = qobject_cast<QAction *>(sender());
	fillColorToolButton->setIcon(createColorToolButtonIcon(
				":/images/floodfill.png",
				qVariantValue<QColor>(fillAction->data())));
	fillButtonTriggered();
}

//CUando se cambia un color de linea
void MainWindow::lineColorChanged()
{
	lineAction = qobject_cast<QAction *>(sender());
	lineColorToolButton->setIcon(createColorToolButtonIcon(
				":/images/linecolor.png",
				qVariantValue<QColor>(lineAction->data())));
	lineButtonTriggered();
}

//Cambiar de color el texto
void MainWindow::textButtonTriggered()
{
	scene->setTextColor(qVariantValue<QColor>(textAction->data()));
}

//Rellenar Objeto
void MainWindow::fillButtonTriggered()
{
	scene->setItemColor(qVariantValue<QColor>(fillAction->data()));
}

//Cambiar el color de la flecha
void MainWindow::lineButtonTriggered()
{
	scene->setLineColor(qVariantValue<QColor>(lineAction->data()));
}

//Cuandos e cambia el tipo de fuente
void MainWindow::handleFontChange()
{
	QFont font = fontCombo->currentFont();
	font.setPointSize(fontSizeCombo->currentText().toInt());
	font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
	font.setItalic(italicAction->isChecked());
	font.setUnderline(underlineAction->isChecked());

	scene->setFont(font);
}


//Se selecciona un objeto de texto en la escena
void MainWindow::itemSelected(QGraphicsItem *item)
{
	DiagramTextItem *textItem = qgraphicsitem_cast<DiagramTextItem *>(item);
	QFont font = textItem->font();
	QColor color = textItem->defaultTextColor();
	fontCombo->setCurrentFont(font);
	fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
	boldAction->setChecked(font.weight() == QFont::Bold);
	italicAction->setChecked(font.italic());
	underlineAction->setChecked(font.underline());
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("Acerca de QRex"),
			tr("<b>QRex</b> Damn! this is going to be good :)<br/>"
				"authors:<br/> Mario Lopez <br/>y<br/> Luis Aviles."));
}

//Crea los Tool Box
void MainWindow::createToolBox()
{
	buttonGroup = new QButtonGroup(this);
	buttonGroup->setExclusive(false);
	connect(buttonGroup, SIGNAL(buttonClicked(int)),this, SLOT(buttonGroupClicked(int)));

	//Agrega los diagramas al layout
	//De los botones para agregarlos
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(createCellWidget(tr("Conditional"),
				DiagramItem::Conditional), 0, 0);
	layout->addWidget(createCellWidget(tr("Process"),
				DiagramItem::Step),0, 1);
	layout->addWidget(createCellWidget(tr("Input/Output"),
				DiagramItem::Io), 1, 0);
	layout->addWidget(createCellWidget(tr("Start"),
			DiagramItem::StartEnd), 1, 1);
	layout->addWidget(createCellWidget(tr("While"),
				DiagramItem::While), 2, 0);

	//Agrega los botones a las herramientas
	//De edicion de los elementos
	QToolButton *textButton = new QToolButton;
	textButton->setCheckable(true);
	buttonGroup->addButton(textButton, InsertTextButton);
	textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png")
				.scaled(30, 30)));
	textButton->setIconSize(QSize(50, 50));
	QGridLayout *textLayout = new QGridLayout;
	textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
	//Agrega el Text al layout
	textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
	QWidget *textWidget = new QWidget;
	textWidget->setLayout(textLayout);
	layout->addWidget(textWidget, 2, 1);

	layout->setRowStretch(3, 10);
	layout->setColumnStretch(2, 10);

	QWidget *itemWidget = new QWidget;
	itemWidget->setLayout(layout);

	backgroundButtonGroup = new QButtonGroup(this);
	connect(backgroundButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
			this, SLOT(backgroundButtonGroupClicked(QAbstractButton*)));

	//Agrega los fondos al layout
	QGridLayout *backgroundLayout = new QGridLayout;
	backgroundLayout->addWidget(createBackgroundCellWidget(tr("Blue Grid"),
				":/images/background1.png"), 0, 0);
	backgroundLayout->addWidget(createBackgroundCellWidget(tr("White Grid"),
				":/images/background2.png"), 0, 1);
	backgroundLayout->addWidget(createBackgroundCellWidget(tr("Gray Grid"),
				":/images/background3.png"), 1, 0);
	backgroundLayout->addWidget(createBackgroundCellWidget(tr("No Grid"),
				":/images/background4.png"), 1, 1);

	backgroundLayout->setRowStretch(2, 10);
	backgroundLayout->setColumnStretch(2, 10);

	QWidget *backgroundWidget = new QWidget;
	backgroundWidget->setLayout(backgroundLayout);

	toolBox = new QToolBox;
	toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
	toolBox->setMinimumWidth(itemWidget->sizeHint().width());

	//Agrega los menus  al ToolBox
	toolBox->addItem(itemWidget, tr("Basic Flowchart Shapes"));
	toolBox->addItem(backgroundWidget, tr("Backgrounds"));
}


//Las acciones son elementos que deben de ser creados
void MainWindow::createActions()
{
	toFrontAction = new QAction(QIcon(":/images/bringtofront.png"),
			tr("Bring to &Front"), this);
	toFrontAction->setShortcut(tr("Ctrl+F"));
	toFrontAction->setStatusTip(tr("Bring item to front"));
	connect(toFrontAction, SIGNAL(triggered()),
			this, SLOT(bringToFront()));

	sendBackAction = new QAction(QIcon(":/images/sendtoback.png"),
			tr("Send to &Back"), this);
	sendBackAction->setShortcut(tr("Ctrl+B"));
	sendBackAction->setStatusTip(tr("Send item to back"));
	connect(sendBackAction, SIGNAL(triggered()),
			this, SLOT(sendToBack()));

	deleteAction = new QAction(QIcon(":/images/delete.png"),
			tr("&Delete"), this);
	deleteAction->setShortcut(tr("Delete"));
	deleteAction->setStatusTip(tr("Delete item from diagram"));
	connect(deleteAction, SIGNAL(triggered()),
			this, SLOT(deleteItem()));

	exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcuts(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Quit Scenediagram example"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	boldAction = new QAction(tr("Bold"), this);
	boldAction->setCheckable(true);
	QPixmap pixmap(":/images/bold.png");
	boldAction->setIcon(QIcon(pixmap));
	boldAction->setShortcut(tr("Ctrl+B"));
	connect(boldAction, SIGNAL(triggered()),
			this, SLOT(handleFontChange()));

	italicAction = new QAction(QIcon(":/images/italic.png"),
			tr("Italic"), this);
	italicAction->setCheckable(true);
	italicAction->setShortcut(tr("Ctrl+I"));
	connect(italicAction, SIGNAL(triggered()),
			this, SLOT(handleFontChange()));

	underlineAction = new QAction(QIcon(":/images/underline.png"),
			tr("Underline"), this);
	underlineAction->setCheckable(true);
	underlineAction->setShortcut(tr("Ctrl+U"));
	connect(underlineAction, SIGNAL(triggered()),
			this, SLOT(handleFontChange()));

	aboutAction = new QAction(tr("A&bout"), this);
	aboutAction->setShortcut(tr("Ctrl+B"));
	connect(aboutAction, SIGNAL(triggered()),
			this, SLOT(about()));
}

//Se crean los menus
void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(exitAction);

	itemMenu = menuBar()->addMenu(tr("&Item"));
	itemMenu->addAction(deleteAction);
	itemMenu->addSeparator();
	itemMenu->addAction(toFrontAction);
	itemMenu->addAction(sendBackAction);

	aboutMenu = menuBar()->addMenu(tr("&Help"));
	aboutMenu->addAction(aboutAction);
}

//Se crean las barras de herramientas con los iconos
//Y la creacion
void MainWindow::createToolbars()
{
	editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(deleteAction);
	editToolBar->addAction(toFrontAction);
	editToolBar->addAction(sendBackAction);

	fontCombo = new QFontComboBox();
	//COnexion del tipo de fuente
	connect(fontCombo, SIGNAL(currentFontChanged(QFont)),
			this, SLOT(currentFontChanged(QFont)));

	fontSizeCombo = new QComboBox;
	fontSizeCombo->setEditable(true);
	for (int i = 8; i < 30; i = i + 2)
		fontSizeCombo->addItem(QString().setNum(i));
	QIntValidator *validator = new QIntValidator(2, 64, this);
	fontSizeCombo->setValidator(validator);

	//Conexion del tamaño de fuente
	connect(fontSizeCombo, SIGNAL(currentIndexChanged(QString)),
			this, SLOT(fontSizeChanged(QString)));

	fontColorToolButton = new QToolButton;
	fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
	fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()),
				Qt::black));
	textAction = fontColorToolButton->menu()->defaultAction();
	fontColorToolButton->setIcon(createColorToolButtonIcon(
				":/images/textpointer.png", Qt::black));
	fontColorToolButton->setAutoFillBackground(true);

	//Conexion del color de fuente presionado
	connect(fontColorToolButton, SIGNAL(clicked()),
			this, SLOT(textButtonTriggered()));

	fillColorToolButton = new QToolButton;
	fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
	fillColorToolButton->setMenu(createColorMenu(SLOT(itemColorChanged()),
				Qt::white));
	fillAction = fillColorToolButton->menu()->defaultAction();
	fillColorToolButton->setIcon(createColorToolButtonIcon(
				":/images/floodfill.png", Qt::white));

	//Conexion de reellenar
	connect(fillColorToolButton, SIGNAL(clicked()),
			this, SLOT(fillButtonTriggered()));

	lineColorToolButton = new QToolButton;
	lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
	lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()),
				Qt::black));
	lineAction = lineColorToolButton->menu()->defaultAction();
	lineColorToolButton->setIcon(createColorToolButtonIcon(
				":/images/linecolor.png", Qt::black));
	connect(lineColorToolButton, SIGNAL(clicked()),
			this, SLOT(lineButtonTriggered()));

	textToolBar = addToolBar(tr("Font"));
	textToolBar->addWidget(fontCombo);
	textToolBar->addWidget(fontSizeCombo);
	textToolBar->addAction(boldAction);
	textToolBar->addAction(italicAction);
	textToolBar->addAction(underlineAction);

	colorToolBar = addToolBar(tr("Color"));
	colorToolBar->addWidget(fontColorToolButton);
	colorToolBar->addWidget(fillColorToolButton);
	colorToolBar->addWidget(lineColorToolButton);

	//CReacion del menu de apuntadores
	QToolButton *pointerButton = new QToolButton;
	pointerButton->setCheckable(true);
	pointerButton->setChecked(true);
	pointerButton->setIcon(QIcon(":/images/pointer.png"));
	QToolButton *linePointerButton = new QToolButton;
	linePointerButton->setCheckable(true);
	linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

	pointerTypeGroup = new QButtonGroup(this);
	pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
	pointerTypeGroup->addButton(linePointerButton,
			int(DiagramScene::InsertLine));

	//Conexion para el tipo de pointer (linea o apuntador)
	connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
			this, SLOT(pointerGroupClicked(int)));

	sceneScaleCombo = new QComboBox;
	QStringList scales;
	scales << tr("40%") << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
	sceneScaleCombo->addItems(scales);
	sceneScaleCombo->setCurrentIndex(2);

	//Conexion para el cambio de escala
	connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
			this, SLOT(sceneScaleChanged(QString)));

	pointerToolbar = addToolBar(tr("Pointer type"));
	pointerToolbar->addWidget(pointerButton);
	pointerToolbar->addWidget(linePointerButton);
	pointerToolbar->addWidget(sceneScaleCombo);
}

//Se regresa un Botton con los elementos del backgroundCell
QWidget *MainWindow::createBackgroundCellWidget(const QString &text,
		const QString &image)
{
	QToolButton *button = new QToolButton;
	button->setText(text);
	button->setIcon(QIcon(image));
	button->setIconSize(QSize(50, 50));
	button->setCheckable(true);
	backgroundButtonGroup->addButton(button);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}


//Crea un boton del tipo de elemento que deseamos dibujar
QWidget *MainWindow::createCellWidget(const QString &text,
		DiagramItem::DiagramType type)
{
	//Se asigna el tipo de diagrama y el elemento del menu
	//A un item nuevo
	DiagramItem item(type, itemMenu);
	//Se crea un nuevo icono de la imagen del diagrama
	QIcon icon(item.image());

	//Se agrega el boton a QToolButton
	QToolButton *button = new QToolButton;
	button->setIcon(icon);
	button->setIconSize(QSize(50, 50));
	button->setCheckable(true);
	buttonGroup->addButton(button, int(type));

	//Se agrega el boton a un grid layout
	//Junto con el Texto del mismo
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}

//Creas un menu con colores
QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor)
{
	//Creas la lista de colores
	QList<QColor> colors;
	colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
	QStringList names;
	names << tr("black") << tr("white") << tr("red") << tr("blue")
		<< tr("yellow");

	//Crea el menu creando los colores segun los nombres
	QMenu *colorMenu = new QMenu(this);
	for (int i = 0; i < colors.count(); ++i) {
		QAction *action = new QAction(names.at(i), this);
		action->setData(colors.at(i));
		action->setIcon(createColorIcon(colors.at(i)));
		//Crea la conexion con el slot que se mando
		connect(action, SIGNAL(triggered()),
				this, slot);
		colorMenu->addAction(action);
		if (colors.at(i) == defaultColor) {
			colorMenu->setDefaultAction(action);
		}
	}
	return colorMenu;
}

//Se crea el icono de cambio de color
QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile,
		QColor color)
{
	QPixmap pixmap(50, 80);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	QPixmap image(imageFile);
	QRect target(0, 0, 50, 60);
	QRect source(0, 0, 42, 42);
	painter.fillRect(QRect(0, 60, 50, 80), color);
	painter.drawPixmap(target, image, source);

	return QIcon(pixmap);
}

//Se crea el color Icon
QIcon MainWindow::createColorIcon(QColor color)
{
	QPixmap pixmap(20, 20);
	QPainter painter(&pixmap);
	painter.setPen(Qt::NoPen);
	painter.fillRect(QRect(0, 0, 20, 20), color);

	return QIcon(pixmap);
}
