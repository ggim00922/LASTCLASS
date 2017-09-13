//ClassDiagramForm.cpp

#include "ClassDiagramForm.h"
#include "Class.h"
#include "Line.h"
//#include "Figure.h"
#include "Diagram.h"
#include "DrawingVisitor.h"
#include "Text.h"
#include "SingleByteCharacter.h"
#include "WritingVisitor.h"
#include "TextEdit.h"

#include "Template.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "MemoBox.h"
#include "Selection.h"
#include "DrawingController.h"
#include "FigureFactory.h"
#include "MemoLine.h"
#include "Unclicked.h"
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

BEGIN_MESSAGE_MAP(ClassDiagramForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

ClassDiagramForm::ClassDiagramForm() { // ������ �´µ�
	this->diagram = NULL;
	this->text = NULL;
	this->textEdit = NULL;
	this->selection = NULL;
	this->drawingController = NULL;
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
	this->currentClassIndex = -1;
	this->rowIndex = 0;
	this->characterIndex = 0;
	//this->selected = -1;
	this->classButton = false;
	this->relationButton = false;
	this->generalizationButton = false; //�Ϲ�ȭ
	this->realizationButton = false; //��üȭ
	this->dependencyButton = false; //����
	this->associationButton = false; //����ȭ  
	this->directedAssociationButton = false; //��������
	this->aggregationButton = false; // ����
	this->aggregationSButton = false; // ���տ���
	this->compositionButton = false; // �ռ�
	this->compositionSBtton = false; // ���տ���
	this->templateButton = false;
	this->memoBoxButton = false;
}

Long ClassDiagramForm::Save() {
   Long i = 0;
   Long j;
   ofstream fClass;
   ofstream fLine; // �������� ofstream

   fClass.open("ClassSave.txt");
   fLine.open("LineSave.txt");
   if (fClass.is_open() && fLine.is_open()) {
      while (i < this->diagram->GetLength() ) {
		  //���� ������ ���� ������ ĭ 
		  // 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(�Ϲ�ȭ), 5 = Realization(��üȭ), 6 = Dependency(����), 7 = Association(����ȭ),
		  // 8 = DirectedAssociation(��������),  9 = Aggregation(����), 10 = Aggregations(���տ���), 11 =  Composition(�ռ�), 12 = Compositions(���տ���), 13 = MemoLine

		  FigureComposite *object = 0;
		 if (dynamic_cast<Class*>(this->diagram->GetAt(i))) {
			 object = static_cast<FigureComposite*>(this->diagram->GetAt(i));
			 fClass << object->GetLength() << " " << object->GetX() << " " << object->GetY()
				 << " " << object->GetWidth() << " " << object->GetHeight() << " " << 0 << endl;
		 }

		 else if (dynamic_cast<MemoBox*>(this->diagram->GetAt(i))) {
			 object = static_cast<FigureComposite*>(this->diagram->GetAt(i));
			 fClass << object->GetLength() << " " << object->GetX() << " " << object->GetY()
				 << " " << object->GetWidth() << " " << object->GetHeight() << " " << 1 << endl;
		 }
         //object = dynamic_cast<Class*>(this->diagram->GetAt(i));
         //fClass << object->GetLength() << " " << object->GetX() << " " << object->GetY()
         //   << " " << object->GetWidth() << " " << object->GetHeight() << endl;
         j = 0;
         while (j < object->GetLength()) {
			 Figure *figure;
			 
			 if (dynamic_cast<Line*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 2 << endl;
			 }

			 else if (dynamic_cast<Template*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 3 << endl;
			 }

			 else if (dynamic_cast<Generalization*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 4 << endl;
			 }

			 else if (dynamic_cast<Realization*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 5 << endl;
			 }

			 else if (dynamic_cast<Dependency*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 6 << endl;
			 }

			 else if (dynamic_cast<Association*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 7 << endl;
			 }

			 else if (dynamic_cast<DirectedAssociation*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 8 << endl;
			 }

			 else if (dynamic_cast<Aggregation*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 9 << endl;
			 }

			 else if (dynamic_cast<Aggregations*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 10 << endl;
			 }

			 else if (dynamic_cast<Composition*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 11 << endl;
			 }

			 else if (dynamic_cast<Compositions*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 12 << endl;
			 }

			 else if (dynamic_cast<MemoLine*>(object->GetAt(j))) {
				 figure = object->GetAt(j);
				 fLine << figure->GetX() << " " << figure->GetY() << " " <<
					 figure->GetWidth() << " " << figure->GetHeight() << " " << 13 << endl;
			 }
            j++;
         }
         i++;
      }
      fClass.close();
      fLine.close();
   }
   return this->diagram->GetLength();
}

Long ClassDiagramForm::Load() {
	Long position = -1;
	Long i;
	Long x;
	Long y;
	Long width;
	Long height;
	Long length;
	Long lineX;
	Long lineY;
	Long lineWidth;
	Long lineHeight;
	ifstream fClass;
	ifstream fLine;
	Long type;

	FigureFactory factory;
	Figure *figure;

	fClass.open("ClassSave.txt");
	fLine.open("LineSave.txt");

	//���� ������ ���� ������ ĭ 
	// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(�Ϲ�ȭ), 5 = Realization(��üȭ), 6 = Dependency(����), 7 = Association(����ȭ),
	// 8 = DirectedAssociation(��������),  9 = Aggregation(����), 10 = Aggregations(���տ���), 11 =  Composition(�ռ�), 12 = Compositions(���տ���), 13 = MemoLine

	if (fClass.is_open() && fLine.is_open()) {
		fClass >> length >> x >> y >> width >> height >> type;
		while (!fClass.eof()) {
			figure  = factory.Create(x, y, width, height, type);
			position = this->diagram->Add(figure);
			i = 0;
			while (position !=-1 && i < length) {
				fLine >> lineX >> lineY >> lineWidth >> lineHeight >> type;
				figure = factory.Create(lineX, lineY, lineWidth, lineHeight, type);
				static_cast<FigureComposite*>(this->diagram->GetAt(position))->Add(figure);
				i++;
			}
			fClass >> length >> x >> y >> width >> height >> type;
		}
		fClass.close();
		fLine.close();
	}
	return this->diagram->GetLength();
}

Long ClassDiagramForm::TextSave() {
	Long i = 0;
	string s;
	ofstream fText;
	fText.open("Text.txt");
	if (fText.is_open()) {
		while (i < this->text->GetLength()) {
			s = this->text->GetAt(i)->PrintRowString();
			fText << this->text->GetAt(i)->GetX() << ' ' << this->text->GetAt(i)->GetY() << ' ' << this->text->GetAt(i)->GetRowHeight() << ' ' << endl;
			fText << s << endl;
			i++;
		}
		fText.close();
	}
	return i;
}

Long ClassDiagramForm::TextLoad() {
	FigureFactory textCreator;
	Long i = 0;
	Long x = 0;
	Long y = 0;
	Long rowHeight = 0;
	Long classID = -1;
	string str;
	TextComponent* Component = NULL;
	ifstream fText;

	fText.open("Text.txt");
	if (fText.is_open()) {
		while (!fText.eof() || getline(fText, str)) {
			fText >> x >> y >> rowHeight >> classID;
			getline(fText, str);
			fText.clear();
			getline(fText, str);
			fText.clear();

			Component = textCreator.CreateRow(x, y, rowHeight, classID, str);
			this->text->Add(Component);
			i++;
		}
	}
	return i;
}

int ClassDiagramForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {

	CFrameWnd::OnCreate(lpCreateStruct); //�ڵ����� �������̵� //��ӿ���
										 //1.1. ���̾�׷��� �غ��Ѵ�
	this->diagram = new Diagram();
	this->text = new Text;
	this->selection = new Selection;
	this->drawingController = new DrawingController;

	//1.2. �����Ѵ�
	//this->Load();
	//this->TextLoad();
	//1.3. �����츦 �����Ѵ�
	Invalidate();

	return 0;
}

void ClassDiagramForm::OnPaint() {
	CPaintDC dc(this);

	DrawingVisitor drawingVisitor;
	WritingVisitor writingVisitor;

	this->diagram->Accept(drawingVisitor, &dc);
	this->text->Accept(writingVisitor, &dc);

	this->drawingController->Draw(this->startX, this->startY, this->currentX, this->currentY, &dc);

	//���� ǥ�� ���Ƶ�
	//if (this->selected != -1) {

	Long i = 0;
	while (i < this->selection->GetLength()) {
		if (dynamic_cast<Class*>(this->selection->GetAt(i)) || dynamic_cast<MemoBox*>(this->selection->GetAt(i))) {
			dc.Rectangle(this->selection->GetAt(i)->GetX() - 5,
				this->selection->GetAt(i)->GetY() - 5,
				this->selection->GetAt(i)->GetX() + 5,
				this->selection->GetAt(i)->GetY() + 5);
			dc.Rectangle(this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() - 5,
				this->selection->GetAt(i)->GetY() - 5,
				this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() + 5,
				this->selection->GetAt(i)->GetY() + 5);
			dc.Rectangle(this->selection->GetAt(i)->GetX() - 5,
				this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() - 5,
				this->selection->GetAt(i)->GetX() + 5,
				this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() + 5);
			dc.Rectangle(this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() - 5,
				this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() - 5,
				this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() + 5,
				this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() + 5);

		}
		if (dynamic_cast<Realization*>(this->selection->GetAt(i)) || dynamic_cast<Generalization*>(this->selection->GetAt(i)) || dynamic_cast<Dependency*>(this->selection->GetAt(i)) ||
			dynamic_cast<Association*>(this->selection->GetAt(i)) || dynamic_cast<Aggregation*>(this->selection->GetAt(i)) || dynamic_cast<Aggregations*>(this->selection->GetAt(i)) ||
			dynamic_cast<Composition*>(this->selection->GetAt(i)) || dynamic_cast<Compositions*>(this->selection->GetAt(i)) || dynamic_cast<DirectedAssociation*>(this->selection->GetAt(i)) ||
			dynamic_cast<MemoLine*>(this->selection->GetAt(i))) {
			dc.Rectangle(this->selection->GetAt(i)->GetX() - 5,
				this->selection->GetAt(i)->GetY() - 5,
				this->selection->GetAt(i)->GetX() + 5,
				this->selection->GetAt(i)->GetY() + 5);
			dc.Rectangle(this->selection->GetAt(i)->GetX() + (this->selection->GetAt(i)->GetWidth() / 2) - 5,
				this->selection->GetAt(i)->GetY() + (this->selection->GetAt(i)->GetHeight() / 2) - 5,
				this->selection->GetAt(i)->GetX() + (this->selection->GetAt(i)->GetWidth() / 2) + 5,
				this->selection->GetAt(i)->GetY() + (this->selection->GetAt(i)->GetHeight() / 2) + 5);
			dc.Rectangle(this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() - 5,
				this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() - 5,
				this->selection->GetAt(i)->GetX() + this->selection->GetAt(i)->GetWidth() + 5,
				this->selection->GetAt(i)->GetY() + this->selection->GetAt(i)->GetHeight() + 5);

		}
		i++;
	}
}
void ClassDiagramForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	char nCharacter = nChar;
	Long key = -1;

	if (nChar == 48) {
		key = 0;
	}
	if (nChar == 49) {
		key = 1;
	}
	if (nChar == 50) {
		key = 2;
	}
	if (nChar == 51) {
		key = 3;
	}
	if (nChar == 52) {
		key = 4;
	}
	if (nChar == 53) {
		key = 5;
	}
	if (nChar == 54) {
		key = 6;
	}
	if (nChar == 55) {
		key = 7;
	}
	if (nChar == 56) {
		key = 8;
	}
	if (nChar == 57) {
		key = 9;
	}
	if (nChar == 113) {
		key = 10;
	}
	if (nChar == 119) {
		key = 11;
	}
	if (nChar == 101) {
		key = 12;
	}
	if (nChar == 114) {
		key = 13;
	}
	this->drawingController->ChangeState(key);

	if (this->text->GetLength() == 0) {
		Row newRow;
		this->text->Add(newRow.Clone());
	} 
	SingleByteCharacter singleByteCharacter(nCharacter);
	this->startX += 10;
	this->text->GetAt(this->rowIndex)->Add(singleByteCharacter.Clone());

	Invalidate();
}

void ClassDiagramForm::OnSetFocus(CWnd* pOldWnd) {

	this->Invalidate();
}

void ClassDiagramForm::OnLButtonDown(UINT nFlags, CPoint point) {
	this->startX = point.x;
	this->startY = point.y;
	this->currentX = point.x;
	this->currentY = point.y;
	//this->selected = this->diagram->Find(this->currentX, this->currentY);
	this->selection->DeleteAllItems();
	//if (this->relationButton == true) {
		Long x = this->startX;
		Long y = this->startY;
		this->selection->FindByPoint(this->diagram, x, y);
	//}

	//this->currentClassIndex = -1;
	//this->currentClassIndex = this->selection->FindByPoint(this->diagram, this->startX, this->startY);
	if (this->currentClassIndex >= 0) { //Ŭ���� ��ġ�� Ŭ������ �־��ٸ�
		this->textEdit = new TextEdit(this, // �ؽ�Ʈ���� ũ��� Ŭ���� ũ��, �ϴ���
			this->diagram->GetAt(currentClassIndex)->GetX() + 5,
			this->diagram->GetAt(currentClassIndex)->GetY() + 33,
			this->diagram->GetAt(currentClassIndex)->GetWidth() - 5,
			this->diagram->GetAt(currentClassIndex)->GetHeight() - 5);

		this->textEdit->Create(NULL, "textEdit", WS_DLGFRAME, CRect(
			this->textEdit->GetFormX(),
			this->textEdit->GetFormY(),
			this->textEdit->GetFormX() + this->textEdit->GetWidth(),
			this->textEdit->GetFormY() + this->textEdit->GetHeight()), NULL, NULL, WS_EX_TOPMOST);
		this->textEdit->ShowWindow(SW_SHOW);
	}
}

void ClassDiagramForm::OnLButtonDblClk(UINT nFlags, CPoint point) {
	this->startX = point.x;
	this->startY = point.y;
	this->currentX = point.x;
	this->currentY = point.y;

}

void ClassDiagramForm::OnLButtonUp(UINT nFlags, CPoint point) {
	this->currentX = point.x;
	this->currentY = point.y;
	if (dynamic_cast<Unclicked*>(this->drawingController->buttonState)) {
		CRect area;
		area.left = this->startX;
		area.top = this->startY;
		area.right = this->currentX;
		area.bottom = this->currentY;
		this->selection->FindByArea(this->diagram, area);
	}
	if (this->classButton == true) {
		if (this->currentX != this->startX && this->currentY != this->startY) {
			if (this->currentX - this->startX < 150) {
				this->currentX = this->startX + 150;
			}
			if (this->currentY - this->startY < 200) {
				this->currentY = this->startY + 200;
			}
			Long index = this->diagram->AddClass(this->startX, this->startY, this->currentX - this->startX, this->currentY - this->startY);

			//÷�ڿ����� �� �ȵŴ��� Ȯ���ؾ���
			static_cast<Class*>(this->diagram->GetAt(index))->Add(this->startX, this->startY + 50,
				this->currentX - this->startX, this->startY + 50);
			static_cast<Class*>(this->diagram->GetAt(index))->Add(this->startX, (this->startY + 50 + this->currentY) / 2,
				this->currentX - this->startX, (this->startY + 50 + this->currentY) / 2);

			this->textEdit = new TextEdit(this, // �ؽ�Ʈ���� ũ��� Ŭ���� ũ��, �ϴ���
				this->diagram->GetAt(index)->GetX() + 5,
				this->diagram->GetAt(index)->GetY() + 33,
				this->diagram->GetAt(index)->GetWidth() - 5,
				this->diagram->GetAt(index)->GetHeight() - 100);

			this->textEdit->Create(NULL, "textEdit", WS_DLGFRAME, CRect(
				this->textEdit->GetFormX(),
				this->textEdit->GetFormY(),
				this->textEdit->GetFormX() + this->textEdit->GetWidth(),
				this->textEdit->GetFormY() + this->textEdit->GetHeight() - 100), NULL, NULL, WS_EX_TOPMOST);
			this->textEdit->ShowWindow(SW_SHOW);
		}
	}
	if (this->startX != this->currentX && this->startY != this->currentY) {
		this->drawingController->AddToArray(this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY);
	}
	
	//Long length = this->selection->GetLength();
	
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;	

	Invalidate();
}

void ClassDiagramForm::OnMouseMove(UINT nFlags, CPoint point) {
	if (nFlags == MK_LBUTTON) {
		this->currentX = point.x;
		this->currentY = point.y;

		Invalidate();
	}
}

bool ClassDiagramForm::FindCrossPoint(const CPoint& line1Start, const CPoint& line1End, const CPoint& line2Start, const CPoint& line2End, CPoint *crossPoint) {
	double t;
	double s;
	bool ret = false;
	double under = (line2End.y - line2Start.y)*(line1End.x - line1Start.x) - (line2End.x - line2Start.x)*(line1End.y - line1Start.y);
	if (under != 0) {
		double _t = (line2End.x - line2Start.x)*(line1Start.y - line2Start.y) - (line2End.y - line2Start.y)*(line1Start.x - line2Start.x);
		double _s = (line1End.x - line1Start.x)*(line1Start.y - line2Start.y) - (line1End.y - line1Start.y)*(line1Start.x - line2Start.x);
		t = _t / under;
		s = _s / under;
		if (t >= 0.0 && t <= 1.0 && s >= 0.0 && s <= 1.0 && _t != 0 && _s != 0) {
			crossPoint->x = static_cast<LONG>(line1Start.x + t*(double)(line1End.x - line1Start.x));
			crossPoint->y = static_cast<LONG>(line1Start.y + t*(double)(line1End.y - line1Start.y));
			ret = true;
		}
	}
	return ret;
}

void ClassDiagramForm::OnClose() {
	//6.1. �����Ѵ�.
	//this->Save();
	//this->TextSave();
	//6.2. ���̾�׷��� �����.
	if (this->diagram != NULL) {
		delete this->diagram;
	}
	if (this->text != NULL) {
		delete this->text;
	}
	//6.3. �����츦 �ݴ´�.
	CFrameWnd::OnClose(); // �������̵� �ڵ�����
}