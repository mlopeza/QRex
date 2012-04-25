#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPixmapItem>
#include <QList>

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
		void addArrow(Arrow *arrow);

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

		QPixmap image() const;
		int type() const
		{ return Type;}
		bool isStartEnd()
			{return myDiagramType==StartEnd?true:false;}

	protected:
		void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);

	private:
		DiagramType myDiagramType;
		QPolygonF myPolygon;
		QMenu *myContextMenu;
		QList<Arrow *> arrows;
		Arrow *arrowStruct[3];
};

#endif
