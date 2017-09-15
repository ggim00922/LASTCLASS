//Row.cpp

#include "Row.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"

Row::Row(Long capacity) : TextComposite(capacity) {
	this->x = 5;
	this->y = 5;
	this->rowHeight = 20;
	this->classID = -1;
	this->capacity = capacity;
	this->length = 0;
}

Row::Row(Long x, Long y, Long rowHeight, Long classID, Long capacity) : TextComposite(capacity) {
	this->x = x;
	this->y = y;
	this->rowHeight = rowHeight;
	this->classID = classID;
	this->capacity = capacity;
	this->length = 0;
}

Row::Row(const Row& source) {
	this->textComponents = source.textComponents;
	this->x = source.x;
	this->y = source.y;
	this->rowHeight = source.rowHeight;
	this->classID = source.classID;
	this->capacity = source.capacity;
	this->length = source.length;
	Long i = 0;
	while (i < source.length) {
		this->textComponents.Modify(i, (const_cast<Row&>(source)).textComponents[i]->Clone());
		i++;
	}
}

Row::~Row() {
}

Long Row::Add(TextComponent *textComponent) {
	Long index;
	if (this->length < this->capacity) {
		index = this->textComponents.Store(this->length, textComponent);
	}
	else {
		index = this->textComponents.AppendFromRear(textComponent);
		this->capacity++;
	}
	this->length++;
	return index;
}

Long Row::Add(Character *character) {
	Long index;
	if (this->length < this->capacity) {
		index = this->textComponents.Store(this->length, character->Clone());
	}
	else {
		index = this->textComponents.AppendFromRear(character->Clone());
		this->capacity++;
	}
	this->length++;
	return index;
}

Long Row::Modify(Long index, TextComponent *textComponent) {
	return this->textComponents.Modify(index, textComponent);
}
Long Row::Remove(Long index) {
	index = this->textComponents.Delete(index);
	this->length--;
	this->capacity--;

	return index;
}

Long Row::Insert(Long index, TextComponent *textComponent) {
	this->length++;
	this->capacity++;
	return this->textComponents.Insert(index, textComponent);
}

Character* Row::GetAt(Long index) {
	return static_cast<Character*>(this->textComponents[index]);
}

TextComponent* Row::Clone() const {
	return new Row(*this);
}

#include <iostream>
using namespace std;

void Row::PrintCharacter(SmartPointer<TextComponent*>& index) {
	for (index->First(); !index->IsDone(); index->Next()) {
		if (dynamic_cast<SingleByteCharacter*>(index->Current())) {
			cout << "PrintCharacter Single 확인" << endl;
		}
		else if (dynamic_cast<DoubleByteCharacter*>(index->Current())) {
			cout << "PrintCharacter Double 확인" << endl;
		}
	}
}

string Row::PrintRowString() {
	char tempChar[256] = { 0, };
	Long i = 0;

	SmartPointer<TextComponent*> iterator = this->CreateIterator();
	for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
		if (dynamic_cast<SingleByteCharacter*>(iterator->Current())) {
			tempChar[i] = static_cast<SingleByteCharacter*>(iterator->Current())->GetCharacter();
		}
		else if (dynamic_cast<DoubleByteCharacter*>(iterator->Current())) {
			tempChar[i] = static_cast<DoubleByteCharacter*>(iterator->Current())->GetCharacters()[0];
			i++;
			tempChar[i] = static_cast<DoubleByteCharacter*>(iterator->Current())->GetCharacters()[1];
		}
		i++;
	}
	//tempChar[i] = '\n';
	string tempString(tempChar, i);

	return tempString;
}

void Row::Accept(Visitor& visitor, CDC* cPaintDc) {
	visitor.Visit(this, cPaintDc);
}

Row& Row::operator = (const Row& source) {
	this->x = source.x;
	this->y = source.y;
	this->rowHeight = source.rowHeight;
	this->classID = source.classID;
	this->capacity = source.capacity;
	this->length = source.length;
	this->textComponents = source.textComponents;
	Long i = 0;
	while (i < source.length) {
		this->textComponents.Modify(i, (const_cast<Row&>(source)).textComponents.GetAt(i)->Clone());
		i++;
	}
	return *this;
}

Character* Row::operator [] (Long index) {
	return static_cast<Character*>(this->textComponents[index]);
}

//#include <iostream>
//#include "SingleByteCharacter.h"
//#include "DoubleByteCharacter.h"
//
//using namespace std;
//
//int main(int argc, char* argv[]) {
//	Row object0(100);
//cout << object0.GetCapacity() << " " << object0.GetLength() << endl;
//
//Row object1;
//cout << object1.GetCapacity() << " " << object1.GetLength() << endl;
//
//Row object2(object1);
//cout << object2.GetCapacity() << " " << object2.GetLength() << endl;
//
//SingleByteCharacter singleByteCharacter('a');
//
//object1.Add(static_cast<Character*>(&singleByteCharacter));
//
//cout << (static_cast<SingleByteCharacter*>(object1.GetAt(0)))->GetCharacter() << endl;
//
//DoubleByteCharacter doubleByteCharacter("가");
//
//object2.Add(static_cast<Character*>(&doubleByteCharacter));
//object2.Add(static_cast<Character*>(&doubleByteCharacter));
//object2.Add(static_cast<Character*>(&doubleByteCharacter));
//object2.Add(static_cast<Character*>(&doubleByteCharacter));
//
//cout << (static_cast<DoubleByteCharacter*>(object2.GetAt(0)))->GetCharacters() << endl;
//cout << (static_cast<DoubleByteCharacter*>(object2.GetAt(1)))->GetCharacters() << endl;
//cout << (static_cast<DoubleByteCharacter*>(object2.GetAt(2)))->GetCharacters() << endl;
//cout << (static_cast<DoubleByteCharacter*>(object2.GetAt(3)))->GetCharacters() << endl;
//
//
//
//	return 0;
//}