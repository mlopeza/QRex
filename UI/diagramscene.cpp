#include <QtGui>
#include <QtGlobal>
#include <QPointF>
#include "diagramscene.h"
#include "arrow.h"

	DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
: QGraphicsScene(parent)
{
	myItemMenu = itemMenu;
	myMode = MoveItem;
	myItemType = DiagramItem::Step;
	line = 0;
	textItem = 0;
	myItemColor = Qt::white;
	myTextColor = Qt::black;
	myLineColor = Qt::black;
}

void DiagramScene::setLineColor(const QColor &color)
{
	myLineColor = color;
	if (isItemChange(Arrow::Type)) {
		Arrow *item =
			qgraphicsitem_cast<Arrow *>(selectedItems().first());
		item->setColor(myLineColor);
		update();
	}
}

void DiagramScene::setTextColor(const QColor &color)
{
	myTextColor = color;
	if (isItemChange(DiagramTextItem::Type)) {
		DiagramTextItem *item =
			qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
		item->setDefaultTextColor(myTextColor);
	}
}

void DiagramScene::setItemColor(const QColor &color)
{
	myItemColor = color;
	if (isItemChange(DiagramItem::Type)) {
		DiagramItem *item =
			qgraphicsitem_cast<DiagramItem *>(selectedItems().first());
		item->setBrush(myItemColor);
	}
}

void DiagramScene::setFont(const QFont &font)
{
	myFont = font;

	if (isItemChange(DiagramTextItem::Type)) {
		QGraphicsTextItem *item =
			qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
		if (item)
			item->setFont(myFont);
	}
}

void DiagramScene::setMode(Mode mode)
{
	myMode = mode;
}

void DiagramScene::setItemType(DiagramItem::DiagramType type)
{
	myItemType = type;
}

void DiagramScene::editorLostFocus(DiagramTextItem *item)
{
	QTextCursor cursor = item->textCursor();
	cursor.clearSelection();
	item->setTextCursor(cursor);

	if (item->toPlainText().isEmpty()) {
		removeItem(item);
		item->deleteLater();
	}
}

void DiagramScene::addConditionalDiagram(DiagramItem *item,DiagramItem::DiagramType type,QMenu *myItemMenu,QGraphicsSceneMouseEvent *mouseEvent){
				//Se crea un nuevo tipo de diagrama
				DiagramItem *item2 = new DiagramItem(type,myItemMenu);
				//Se pone el color
				item2->setBrush(myItemColor);
				//Se agrega a escena
				addItem(item2);
				//Se emite la señal de que se inserto un objeto
				emit itemInserted(item2);
				//Se cambia la posicion
				item2->setPos(mouseEvent->scenePos().x()+300,mouseEvent->scenePos().y());
				//Lo pone como visible
				item2->setVisible(true);
		
				//=====================Se agrega la linea
				Arrow *arrow = new Arrow(item,item2);
				item2->addArrowFrom(arrow);
				item->addArrowConditional(arrow);
				qDebug() << "item has arrows? "<<item->hasArrows();
				//Color especial
				arrow->setColor(QColor("purple"));
				arrow->setZValue(-1000.0);
				addItem(arrow);
				arrow->updatePosition();
				//=====================Se agrega la linea
				//Hace un update del objeto y de la escena
				item2->update();
				update();

}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton)
		return;

	DiagramItem *item;
	switch (myMode) {
		case InsertItem:
			item = new DiagramItem(myItemType, myItemMenu);
			item->setBrush(myItemColor);
			addItem(item);
			item->setPos(mouseEvent->scenePos());
			emit itemInserted(item);
			//Si es del tipo StartEnd se agrega a la lista de funciones
			//Y casos especiales de Condicional y While donde se agrega un elemento mas
			if(item->isStartEnd()){
				functions.append(item);
			}else if(item->isConditional() || item->isWhile()){
				addConditionalDiagram(item,DiagramItem::Step,myItemMenu,mouseEvent);
			}
			break;
		case InsertLine:
			line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
						mouseEvent->scenePos()));
			line->setPen(QPen(myLineColor, 5));
			addItem(line);
			break;
		case InsertText:
			textItem = new DiagramTextItem();
			textItem->setFont(myFont);
			textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
			textItem->setZValue(1000.0);
			connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
					this, SLOT(editorLostFocus(DiagramTextItem*)));
			connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
					this, SIGNAL(itemSelected(QGraphicsItem*)));
			addItem(textItem);
			textItem->setDefaultTextColor(myTextColor);
			textItem->setPos(mouseEvent->scenePos());
			emit textInserted(textItem);
			break;
		case InsertConditional:
			qDebug()<<"Conditional Inserted";
			line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
					mouseEvent->scenePos()));
			line->setPen(QPen(QColor("purple"), 5));
			addItem(line);
			break;
		default:
			break;
	}
	QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (myMode == InsertLine && line != 0) {
		QLineF newLine(line->line().p1(), mouseEvent->scenePos());
		line->setLine(newLine);
	} else if(myMode == InsertConditional && line != 0){
		QLineF newLine(line->line().p1(), mouseEvent->scenePos());
		line->setLine(newLine);
	}else if (myMode == MoveItem) {
		QGraphicsScene::mouseMoveEvent(mouseEvent);
	}
	update();
}

//En esta parte se agregan las lineas para conectarlas
//En este lugar tambien se aprovecha la conexion entre
//los diagramas para crear la estructura
void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	//Primero se checa si hay colisiones con los dos puntos
	//De la linea y se agregan en dos listas por cada punto
	if (line != 0 && myMode == InsertLine) {
		QList<QGraphicsItem *> startItems = items(line->line().p1());
		if (startItems.count() && startItems.first() == line)
			startItems.removeFirst();
		QList<QGraphicsItem *> endItems = items(line->line().p2());
		if (endItems.count() && endItems.first() == line)
			endItems.removeFirst();

		//Se remueve la linea pues solo se usa como
		//Un temporal de creacion
		removeItem(line);
		delete line;

		if (startItems.count() > 0 && endItems.count() > 0 &&
				startItems.first()->type() == DiagramItem::Type &&
				endItems.first()->type() == DiagramItem::Type &&
				startItems.first() != endItems.first()) {

			//Se obtienen los apuntadores a los objetos que colisionaron
			DiagramItem *startItem =
				qgraphicsitem_cast<DiagramItem *>(startItems.first());
			DiagramItem *endItem =
				qgraphicsitem_cast<DiagramItem *>(endItems.first());

			//No se permite que un StartEnd sea la conexion a algo
			if(endItem->isStartEnd())
				return;
			qDebug("DiagramScene::MouseReleaseEvent()   endItem->isStartEnd()");
			//No se permite conexion doble
			if(startItem->hasConnection(endItem) || endItem->hasConnection(startItem))
				return;
			qDebug("DiagramScene::MouseReleaseEvent()   hasConnection()");
			//No se permiten reemplazar flechas
			qDebug() << "Start Item:" << startItem->getTo();
			if(startItem->getTo() != NULL)
				return;
			qDebug("DiagramScene::MouseReleaseEvent()   getTo()");
			if(endItem->getFrom() != NULL)
				return;
			qDebug("DiagramScene::MouseReleaseEvent()   getTo() getFrom()");
			//Se Crea la flecha con referencia a los dos objetos creados
			Arrow *arrow = new Arrow(startItem, endItem);
			qDebug("1");
			//Se agregan los atributos de la flecha
			arrow->setColor(myLineColor);
			qDebug("1");
			//Se agregan  los apuntadores a los objetos
			//Colisionados
			startItem->addArrowTo(arrow);
			endItem->addArrowFrom(arrow);
			qDebug("1");
			//Se agregan los elementos a la escena
			arrow->setZValue(-1000.0);
			qDebug("1");
			addItem(arrow);
			qDebug("1");
			arrow->updatePosition();
			qDebug("1");
		}
	}else if (line != 0 && myMode == InsertConditional) {
		qDebug() << "InsertConditional! New";
		QList<QGraphicsItem *> startItems = items(line->line().p1());
		if (startItems.count() && startItems.first() == line)
			startItems.removeFirst();
		QList<QGraphicsItem *> endItems = items(line->line().p2());
		if (endItems.count() && endItems.first() == line)
			endItems.removeFirst();

		//Se remueve la linea pues solo se usa como
		//Un temporal de creacion
		removeItem(line);
		delete line;
		qDebug() << "InsertConditional! New";
		if (startItems.count() > 0 && endItems.count() > 0 &&
				startItems.first()->type() == DiagramItem::Type &&
				endItems.first()->type() == DiagramItem::Type &&
				startItems.first() != endItems.first()) {

			//Se obtienen los apuntadores a los objetos que colisionaron
			DiagramItem *startItem =
				qgraphicsitem_cast<DiagramItem *>(startItems.first());
			DiagramItem *endItem =
				qgraphicsitem_cast<DiagramItem *>(endItems.first());
		qDebug() << "InsertConditional! New 1";
			//Si no es condicional el Start Item no se hace nada
			if(!(startItem->isConditional() || startItem->isWhile()))
				return;
		qDebug() << "InsertConditional! New 2";
			//No se permite que un StartEnd sea la conexion a algo
			if(endItem->isStartEnd())
				return;
		qDebug() << "InsertConditional! New 3";
			//No se permite conexion doble
			if(startItem->hasConnection(endItem) || endItem->hasConnection(startItem))
				return;
		qDebug() << "InsertConditional! New 4";
			//No se permiten reemplazar flechas En este caso la condicional de la primera
			if(startItem->getConditional() != NULL || endItem->getFrom() != NULL)
				return;
		qDebug() << "InsertConditional! New 5";
			//Se Crea la flecha con referencia a los dos objetos creados
			Arrow *arrow = new Arrow(startItem, endItem);

			//Se agregan los atributos de la flecha
			arrow->setColor(QColor("purple"));

			//Se agregan  los apuntadores a los objetos
			//Colisionados
			startItem->addArrowConditional(arrow);
			endItem->addArrowFrom(arrow);

			//Se agregan los elementos a la escena
			arrow->setZValue(-1000.0);
			addItem(arrow);
			arrow->updatePosition();
			qDebug() << "Conditional Inserted!";
		}	
	}
	update();
	line = 0;
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool DiagramScene::isItemChange(int type)
{
	foreach (QGraphicsItem *item, selectedItems()) {
		if (item->type() == type)
			return true;
	}
	return false;
}