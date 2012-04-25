#define FROM 0
#define TO 1
#define COND 2

#include <QtGui>
#include "diagramitem.h"
#include "arrow.h"

DiagramItem::DiagramItem(DiagramType diagramType, QMenu *contextMenu,
		QGraphicsItem *parent, QGraphicsScene *scene)
: QGraphicsPolygonItem(parent, scene)
{
	myDiagramType = diagramType;
	myContextMenu = contextMenu;

	//Se dibujan los poligonos a utilizar
	QPainterPath path;
	switch (myDiagramType) {
		case StartEnd:
			path.moveTo(120,0);
			path.arcTo(-120.0, -90.0, 240.0, 160.0, 0.0, 360.0);
			myPolygon = path.toFillPolygon();
			break;
		case Conditional:
			myPolygon << QPointF(-100, 0) << QPointF(0, 100)
				<< QPointF(100, 0) << QPointF(0, -100)
				<< QPointF(-100, 0);
			break;
		case While:
			myPolygon << QPointF(-100, 0) << QPointF(0, 50)
				<< QPointF(100, 0) << QPointF(0, -50)
				<< QPointF(-100, 0);
			break;
		case Step:
			myPolygon << QPointF(-100, -100) << QPointF(100, -100)
				<< QPointF(100, 100) << QPointF(-100, 100)
				<< QPointF(-100, -100);
			break;
		default:
			myPolygon << QPointF(-120, -80) << QPointF(-70, 80)
				<< QPointF(120, 80) << QPointF(70, -80)
				<< QPointF(-120, -80);
			break;
	}
	setPolygon(myPolygon);
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

	//Crea los espacios para las flechas
	arrowStruct[0]=NULL;
	arrowStruct[1]=NULL;
	arrowStruct[2]=NULL;
}

void DiagramItem::removeArrow(Arrow *arrow)
{
	qDebug() << ">>>>>>>>>>DiagramItem::removeArrow()";
	int index = arrows.indexOf(arrow);

	if (index != -1)
		arrows.removeAt(index);
}

void DiagramItem::removeArrows()
{
	qDebug()<< ">>>>>>>>>>DiagramItem::removeArrows()";
	foreach (Arrow *arrow, arrows) {
		arrow->startItem()->removeArrow(arrow);
		arrow->endItem()->removeArrow(arrow);
		scene()->removeItem(arrow);
		delete arrow;
	}
}

void DiagramItem::addArrow(Arrow *arrow)
{
	arrows.append(arrow);
}

//Agrega la flecha que apunta a este objeto
void DiagramItem::addArrowFrom(Arrow *arrow){
	//Si es el inicio de una funcion
	if(this->isStartEnd())
		return;
	//Si ya hay un objeto asignado
	if(arrowStruct[FROM] != NULL)
		return;

	arrowStruct[FROM]=arrow;
}

//Agrega la flecha a la cual este objeto apunta
void DiagramItem::addArrowTo(Arrow *arrow){
	//Si ya hay un objeto asignado
	if(arrowStruct[TO] != NULL)
		return;

	//Si el objeto al cual se quiere hacer la conexion es un StartEnd
	if((arrow->endItem())->isStartEnd()){
		(arrow->endItem())->removeArrowFrom(arrow);
	}
	arrowStruct[TO]=arrow;
}

//Si es un condicional agrega la flecha que apunta al condicional
void DiagramItem::addArrowConditional(Arrow *arrow){
	if(this->myDiagramType != Conditional)
		return;

	if(arrowStruct[COND] != NULL)
		return;
	if((arrow->endItem())->isStartEnd()){
		(arrow->endItem())->removeArrowFrom(arrow);
	}
	arrowStruct[COND]=arrow;
}

void DiagramItem::removeArrowFrom(Arrow *arrow){
	//Si no es la misma flecha regresa
	if(arrow != arrowStruct[FROM])
		return;

	//Pone como NULL el Arrow del otro Objeto
	(arrowStruct[FROM]->startItem())->setArrow(TO,NULL);
	//Elimina e iguala a NULL
	delete arrowStruct[FROM];
	arrowStruct[FROM]=NULL;
}

void DiagramItem::removeArrowTo(Arrow *arrow){
	//Si no es la misma flecha regresa
	if(arrow != arrowStruct[TO])
		return;

	//Pone como NULL el otro lado de la flecha
	(arrowStruct[FROM]->endItem())->setArrow(FROM,NULL);
	//Elimina e iguala a NULL
	delete arrowStruct[TO];
	arrowStruct[TO]=NULL;
}

void DiagramItem::removeArrowConditional(Arrow *arrow){
	if(arrow != arrowStruct[COND])
		return;

	//Pone como NULL El area condicional
	//Opcionalmente se agregara una flecha especial
	//Para el condicional o se eliminara todo si se
	//Elimina la flecha
	(arrowStruct[COND]->endItem())->setArrow(FROM,NULL);
	delete arrowStruct[COND];
	arrowStruct[COND]=NULL;

}

void DiagramItem::setArrow(const int INDEX,Arrow *arrow){
	arrowStruct[INDEX]=arrow;
}
QPixmap DiagramItem::image() const
{
	QPixmap pixmap(250, 250);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	painter.setPen(QPen(Qt::black, 8));
	painter.translate(125, 125);
	painter.drawPolyline(myPolygon);

	return pixmap;
}

void DiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	scene()->clearSelection();
	setSelected(true);
	myContextMenu->exec(event->screenPos());
}

QVariant DiagramItem::itemChange(GraphicsItemChange change,
		const QVariant &value)
{
	if (change == QGraphicsItem::ItemPositionChange) {
		foreach (Arrow *arrow, arrows) {
			arrow->updatePosition();
		}
	}

	return value;
}
