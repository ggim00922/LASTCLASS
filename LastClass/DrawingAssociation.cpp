#include "DrawingAssociation.h"
#include "DefaultState.h"
#include "Figure.h"
#include "Selection.h"
#include "Class.h"
#include "Finder.h"
#include "Association.h"
#include "SelfAssociation.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "RollNameBox.h"
DrawingAssociation* DrawingAssociation::instance = 0;

MouseLButtonAction* DrawingAssociation::Instance() {
	if (instance == 0) {
		instance = new DrawingAssociation;
	}
	return instance;
}

void DrawingAssociation::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Long index;
	Figure *figure = 0;

	Long quadrant;
	Long quadrant2;

	classDiagramForm->historyGraphic->PushUndo(diagram, classDiagramForm->zoomRate);
	selection->SelectByPointForRelation(diagram, currentX, currentY);

	if (selection->GetLength() == 2 && dynamic_cast<Class*>(selection->GetAt(0)) && dynamic_cast<Class*>(selection->GetAt(1)) 
		&& selection->GetAt(0) != selection->GetAt(1)) {
		Class * classObject = dynamic_cast<Class*>(selection->GetAt(0));
		Class * classObject2 = dynamic_cast<Class*>(selection->GetAt(1));
		CPoint lineStart(startX, startY);
		CPoint lineEnd(currentX, currentY);

		CRect rect(selection->GetAt(0)->GetX(), selection->GetAt(0)->GetY(),
			selection->GetAt(0)->GetX() + selection->GetAt(0)->GetWidth(),
			selection->GetAt(0)->GetY() + selection->GetAt(0)->GetHeight());

		Finder finder;
		CPoint cross1 = finder.GetCrossPoint(lineStart, lineEnd, rect);

		rect.left = selection->GetAt(1)->GetX();
		rect.top = selection->GetAt(1)->GetY();
		rect.right = selection->GetAt(1)->GetX() + selection->GetAt(1)->GetWidth();
		rect.bottom = selection->GetAt(1)->GetY() + selection->GetAt(1)->GetHeight();
		CPoint cross2 = finder.GetCrossPoint(lineStart, lineEnd, rect);


		quadrant = finder.FindQuadrant(cross1.x, cross1.y, classObject->GetX(), classObject->GetY(),
			classObject->GetX() + classObject->GetWidth(), classObject->GetY() + classObject->GetHeight());

		quadrant2 = finder.FindQuadrant(cross2.x, cross2.y, classObject2->GetX(), classObject2->GetY(),
			classObject2->GetX() + classObject2->GetWidth(), classObject2->GetY() + classObject2->GetHeight());

		if (classObject->GetTempletePosition() != -1 && quadrant == 1
			&& cross1.x >= classObject->GetAt(classObject->GetTempletePosition())->GetX() - 10) {
			cross1.x = classObject->GetAt(classObject->GetTempletePosition())->GetX() - 10;
		}

		if (classObject2->GetTempletePosition() != -1 && quadrant2 == 1
			&& cross2.x >= classObject2->GetAt(classObject2->GetTempletePosition())->GetX() - 10) {
			cross2.x = classObject2->GetAt(classObject2->GetTempletePosition())->GetX() - 10;
		}

		Association object(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
		index = static_cast<FigureComposite*>(selection->GetAt(0))->Add(object.Clone());
		figure = static_cast<FigureComposite*>(selection->GetAt(0))->GetAt(index);
	}

	else if (selection->GetLength() == 2 && dynamic_cast<Class*>(selection->GetAt(0)) && selection->GetAt(0) == selection->GetAt(1)) {
		Class *object = static_cast<Class*>(selection->GetAt(0));
		Long i = 0;
		bool ret = false;
		while (i < object->GetLength()) {
			if (dynamic_cast<SelfRelation*>(object->GetAt(i))) {
				ret = true;
			}
			i++;
		}
		if (ret == false) { // 셀프선이 없으면
			Long k;
			if (object->GetTempletePosition() != -1) { // 템플릿기호가 있으면
				SelfAssociation  selfAssociation(object->GetX() + 30 * classDiagramForm->zoomRate / 100,
					object->GetY(), 30 * classDiagramForm->zoomRate / 100, 30 * classDiagramForm->zoomRate / 100);
				//k = 0;
				//while (k < 5) {
				//	CPoint cPoint(selfAggregation.rollNamePoints->GetAt(k).x, selfAggregation.rollNamePoints->GetAt(k).y - classDiagramForm->seventeen);
				//	selfAggregation.rollNamePoints->Modify(k, cPoint);
				//	k++;
				//}
				index = object->Add(selfAssociation.Clone());
				static_cast<SelfRelation*>(object->GetAt(index))->leftRigtFlag = 1;
			}
			else if (object->GetTempletePosition() == -1) {
				SelfAssociation  selfAssociation(object->GetX() + object->GetWidth() - 30 * classDiagramForm->zoomRate / 100,
					object->GetY(), 30 * classDiagramForm->zoomRate / 100, 30 * classDiagramForm->zoomRate / 100);
				//selfAggregation.Move(0, -classDiagramForm->seventeen);
				k = 0;
				/*while (k < 5) {
				CPoint cPoint(selfAggregation.rollNamePoints->GetAt(k).x, selfAggregation.rollNamePoints->GetAt(k).y - classDiagramForm->seventeen);
				selfAggregation.rollNamePoints->Modify(k, cPoint);
				k++;
				}*/
				index = object->Add(selfAssociation.Clone());
				static_cast<SelfRelation*>(object->GetAt(index))->leftRigtFlag = 0;
			}
			figure = object->GetAt(index);
		}
	}
	selection->DeleteAllItems();
	this->ChangeDefault(mouseLButton);
}
void DrawingAssociation::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	selection->DeleteAllItems();
	selection->SelectByPoint(diagram, currentX, currentY);
}

void DrawingAssociation::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	if (startX == currentX&&startY == currentY) {
		selection->DeleteAllItems();
		selection->SelectByPoint(diagram, currentX, currentY);
	}
	pDC->MoveTo(startX, startY);
	pDC->LineTo(currentX, currentY);

}