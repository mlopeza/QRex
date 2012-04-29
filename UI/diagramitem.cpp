#include <QtGui>
#include "diagramitem.h"
#include "arrow.h"
#include "functiondialog.h" //Para Dialogos de Funciones
#include "conditionaldialog.h" //Para Dialogos de Condicionales
#include "stepdialog.h" //Para Dialogos de Procesos
#include "iodialog.h" //Para Dialogos de IO
#include <QString>
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
	dialog=NULL;
}

//Elimina una flecha de un Objeto
void DiagramItem::removeArrow(Arrow *arrow)
{
	qDebug() << "DiagramItem::removeArrow()";
	if(arrow == NULL)
		return;
	if(arrow == arrowStruct[TO]){
		qDebug()<<"1";
		arrowStruct[TO]=NULL;
	}else if(arrow == arrowStruct[FROM]){
		qDebug()<<"2";
		arrowStruct[FROM]=NULL;
	}else if(arrow == arrowStruct[COND]){
		qDebug()<<"3";
		arrowStruct[COND]=NULL;
	}
	qDebug() << "DiagramItem::removeArrow() ENDED";

}

bool DiagramItem::hasArrows(){
	if(arrowStruct[TO]!=NULL || arrowStruct[FROM]!=NULL || arrowStruct[COND]!=NULL)
		return true;
	return false;
}
//Elimina todas las flechas de ub objeto
void DiagramItem::removeArrows()
{
	qDebug() << "DiagramItem::removeArrows()";
	qDebug() << "1";
	if(arrowStruct[TO] != NULL){
		qDebug() << ">> delete arrowStruct[TO]";
		qDebug() << "arrowStruct[TO]->endItem()->removeArrow(arrowStruct[FROM]);";
		arrowStruct[TO]->endItem()->removeArrow(arrowStruct[TO]);
		qDebug() << "scene()->removeItem(arrowStruct[TO]);";
		scene()->removeItem(arrowStruct[TO]);
		qDebug()<<"delete arrowStruct[TO];";
		delete arrowStruct[TO];
		qDebug() << "arrowStruct[TO]=NULL;";
		arrowStruct[TO]=NULL;
	}
	qDebug() << "2";
	if(arrowStruct[FROM] != NULL){
		qDebug() << ">> delete arrowStruct[FROM]";
		qDebug() << ">>	arrowStruct[FROM]->startItem()->removeArrow(arrowStruct[TO]);";
		arrowStruct[FROM]->startItem()->removeArrow(arrowStruct[FROM]);
		qDebug() << ">>scene()->removeItem(arrowStruct[FROM]);";
		scene()->removeItem(arrowStruct[FROM]);
		qDebug()<<"delete arrowStruct[FROM];";
		delete arrowStruct[FROM];
		qDebug()<<"arrowStruct[FROM]=NULL;";
		arrowStruct[FROM]=NULL;
	}
	qDebug() << "3";
	if(arrowStruct[COND] != NULL){
		qDebug() << ">> delete arrowStruct[COND]";
		qDebug() <<"arrowStruct[COND]->endItem()->removeArrow(arrowStruct[FROM]);"; 
		arrowStruct[COND]->endItem()->removeArrow(arrowStruct[COND]);
		qDebug()<<"scene()->removeItem(arrowStruct[COND]);";
		scene()->removeItem(arrowStruct[COND]);
		qDebug()<<"delete arrowStruct[COND];";
		delete arrowStruct[COND];
		qDebug()<<"arrowStruct[COND]=NULL;";
		arrowStruct[COND]=NULL;
	}
	qDebug() << "4";
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
	if(!(this->myDiagramType == Conditional || this->myDiagramType == While))
		return;

	if(arrowStruct[COND] != NULL){
		return;
	}
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

//Iguala el INDEX de el arreeglo de las flechas a la flecha que se manda
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
	qDebug() << "Selected!!";
	scene()->clearSelection();
	setSelected(true);
	myContextMenu->exec(event->screenPos());
}


bool DiagramItem::hasConnection(DiagramItem *item){
	qDebug() << "DiagramItem::hasConnection()";
	if(arrowStruct[TO] != NULL){
		qDebug() << ">>arrowStruct[TO] != NULL";
		if(arrowStruct[TO]->endItem() == item)
			return true;
	}
	if(arrowStruct[FROM] != NULL){
		qDebug() << ">>arrowStruct[FROM] != NULL";
		if(arrowStruct[FROM]->startItem() == item)
			return true;
	}
	if(arrowStruct[COND] != NULL){
		qDebug() << ">>arrowStruct[COND] != NULL";
		if(arrowStruct[COND]->endItem() == item)
			return true;
	}
	return false;
}

void DiagramItem::printSignature(QTextStream *out){
	//Si es main no tiene firma
	if(!(QString::compare(((FunctionDialog *)dialog)->typeComboBox->currentText().trimmed(), "main")))
		return;
	//Tipo de funcion
	*out<<"sign "<<((FunctionDialog *)dialog)->typeComboBox->currentText()<<" ";
	//Nombre de la funcion
	*out<<((FunctionDialog *)dialog)->functionName->text()<<"(";

	//Por medio de un proceso se obtienen los tipos de variables de las
	//funciones
	QString parameters(((FunctionDialog *)dialog)->functionParameters->text().simplified());
	QString delimiterPattern(",");
	QString space(" ");
	QStringList plist = parameters.split(delimiterPattern);
	int numero=1;
	//Checa cada uno de los parametros
	foreach(QString param, plist){
		QStringList x = (param.simplified()).split(space);
        	*out<<x.first();
		if(numero!=plist.size()){
			*out<<",";
			numero++;
		}
	}
	*out<<");\n";
	
}

//Imprime de forma recursiva toda la informacion de la estructura
//Recibe como parametro el stream de salida
void DiagramItem::recursivePrint(QTextStream *out){
	switch(myDiagramType){
		case While:
			*out<<" while(";
			*out<<((ConditionalDialog *)dialog)->conditionText->text().simplified();
			*out<<"){";
			if(arrowStruct[COND] != NULL){
				DiagramItem *cNext = arrowStruct[COND]->endItem();
				cNext->recursivePrint(out);
			}

			*out<<"}";
		break;
		case Conditional:
			*out<<" if(";
			*out<<((ConditionalDialog *)dialog)->conditionText->text().simplified();
			*out<<"){";
			if(arrowStruct[COND] != NULL){
				DiagramItem *cNext = arrowStruct[COND]->endItem();
				cNext->recursivePrint(out);
			}
			*out<<"}";
		break;
		case Step:
			*out<<((StepDialog *)dialog)->stepText->toPlainText();
		break;
		case Io:
			if(!(QString::compare(((IODialog *)dialog)->ioComboBox->currentText(), "Input"))){
				*out<<" read(";
				*out<<((IODialog *)dialog)->IOText->text().simplified();
				*out<<");";
			}else{
				*out<<" print(";
				*out<<((IODialog *)dialog)->IOText->text().simplified();
				*out<<");";
			}
		break;
		case StartEnd:
			qDebug()<<((FunctionDialog *)dialog)->typeComboBox->currentText().trimmed();
			if(!(QString::compare(((FunctionDialog *)dialog)->typeComboBox->currentText().trimmed(), "main"))){
				qDebug()<<"Funcion Main";
				*out<<" main(){";
				//Imprime cuerpo
				if(arrowStruct[TO]!=NULL){
					DiagramItem *next = arrowStruct[TO]->endItem();
					next->recursivePrint(out);
				}			
				*out<<"}";
			}else{
				qDebug()<<"Funcion Normal";
				*out<<" "<<((FunctionDialog *)dialog)->typeComboBox->currentText()<<" ";
				*out<<((FunctionDialog *)dialog)->functionName->text().simplified()<<" ";
				*out<<"("<<((FunctionDialog *)dialog)->functionParameters->text().simplified()<<"){";
				//Imprime cuerpo
				if(arrowStruct[TO]!=NULL){
					DiagramItem *next = arrowStruct[TO]->endItem();
					next->recursivePrint(out);
				}			
				*out<<"}";
			}
		break;
	}
	//Va al siguiente elemento en la lista
	if(arrowStruct[TO]==NULL || myDiagramType == StartEnd)
		return;
	DiagramItem *next = arrowStruct[TO]->endItem();
	next->recursivePrint(out);
	
}
//Retorna los objetos con los que se hace referencia
DiagramItem *DiagramItem::getFrom()
{return arrowStruct[FROM]!=NULL?arrowStruct[FROM]->startItem():NULL;}

DiagramItem *DiagramItem::getTo()
{return arrowStruct[TO]!=NULL?arrowStruct[TO]->endItem():NULL;}

DiagramItem *DiagramItem::getConditional()
{return arrowStruct[COND]!=NULL?arrowStruct[COND]->endItem():NULL;}


QVariant DiagramItem::itemChange(GraphicsItemChange change,
		const QVariant &value)
{
	if (change == QGraphicsItem::ItemPositionChange) {
		if(arrowStruct[TO] !=NULL){
			arrowStruct[TO]->updatePosition();
			update();
		}
		if(arrowStruct[FROM] != NULL){
			arrowStruct[FROM]->updatePosition();
			update();
		}
		if(arrowStruct[COND] !=NULL){
			arrowStruct[COND]->updatePosition();
			update();
		}
	}

	return value;
}