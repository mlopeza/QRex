#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H
#define FROM 0
#define TO 1
#define COND 2

#include <QGraphicsPixmapItem>
#include <QList>
#include <QDialog>
class QPixmap;
class QGraphicsItem;
class QGraphicsScene;
class QTextEdit;
class QGraphicsSceneMouseEvent;
class QMenu;
class QGraphicsSceneContextMenuEvent;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QPolygonF;

class Arrow;

class DiagramItem : public QGraphicsPolygonItem
{
	public:
		enum { Type = UserType + 15 };
		enum DiagramType { Step, Conditional, StartEnd, Io, While };

		DiagramItem(DiagramType diagramType, QMenu *contextMenu,
				QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

		void removeArrow(Arrow *arrow);
		void removeArrows();
		DiagramType diagramType() const
		{ return myDiagramType; }
		QPolygonF polygon() const
		{ return myPolygon; }

		//Se agregan las conexiones de las flechas
		void addArrowFrom(Arrow *arrow);
		void addArrowTo(Arrow *arrow);
		void addArrowConditional(Arrow *arrow);

		//Se eliminan las conexiones de las flechas
		void removeArrowFrom(Arrow *arrow);
		void removeArrowTo(Arrow *arrow);
		void removeArrowConditional(Arrow *arrow);
		
		//Iguala una flecha a un valor u objeto arrow
		void setArrow(const int INDEX,Arrow *arrow);

		bool hasConnection(DiagramItem *item);
		bool hasArrows();
		DiagramItem *getFrom();
		DiagramItem *getTo();
		DiagramItem *getConditional();


		QPixmap image() const;
		int type() const
		{ return Type;}
		bool isStartEnd()
			{return myDiagramType==StartEnd?true:false;}
		bool isConditional()
			{return myDiagramType==Conditional?true:false;}
		bool isWhile()
			{return myDiagramType==While?true:false;}
		bool isStep()
			{return myDiagramType==Step?true:false;}
		bool isIO()
			{return myDiagramType==Io?true:false;}
		QDialog *getDialog(){
			return dialog;
		}

		void setDialog(QDialog *x){
			dialog=x;
		}
	protected:
		void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);

	private:
		DiagramType myDiagramType;
		QPolygonF myPolygon;
		QMenu *myContextMenu;
		Arrow *arrowStruct[3];
		QDialog *dialog;
		
};

#endif
