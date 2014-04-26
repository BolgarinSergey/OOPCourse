#include <iostream>
#include <fstream>
#include <cassert>
#include "XList.hpp"
#include "Shapes.h"

template<class C>
void print( std::ostream & _stream, oop::XList<C> const & lst ){//список с головы
	if(lst.empty())
		_stream << "Список пуст" << std::endl;
	else{
		for(oop::XList<C>::XIterator i = lst.begin(); i != lst.end(); ++i)
			_stream << *i << std::endl;
		_stream << std::endl;
	}
}

template<class C>
void print_reverse( std::ostream & _stream, oop::XList<C> const & lst ){//список с хвоста
	if(lst.empty())
		_stream << "Список пуст" << std::endl;
	else{
		for(oop::XList<C>::XRevIterator i = lst.rbegin(); i != lst.rend(); ++i)
			_stream << *i << std::endl;
		_stream << std::endl;
	}
}

int main(){
	std::ofstream out("output.txt");

	out << "создание списка с формами..." << std::endl;
	oop::XList<oop::Printable*> lst;
	lst.push_back(new oop::XPoint("Точка 1", 0.1f, 0.0f));
	lst.push_back(new oop::XCircle("окружность 1", oop::XPoint("circle1.center", 3.6f, 2.0f), 3.0f));
	lst.push_back(new oop::XRect("прямоугольник 1", oop::XPoint("rectangle1.topleft", 2.2f, 5.0f), oop::XPoint("rectangle1.bottomright", 6.3f, 7.3f)));
	lst.push_back(new oop::XSquare("квадрат 1", oop::XPoint("square1.topleft", 5.4f, 0.0f), 1.0f));
	oop::XPolyline* pol = new oop::XPolyline("ломаная 1");
	pol ->AddPoint(oop::XPoint("ломанная 1.p1", 0.0f, 0.0f));
	pol ->AddPoint(oop::XPoint("ломанная 1.p2", 1.0f, 0.0f));
	pol ->AddPoint(oop::XPoint("ломанная 1.p3", 0.0f, 2.0f));
	lst.push_back(pol);
	out << "OK" << std::endl;

	out << "Содержание списка:" << std::endl;
	for(oop::XList<oop::Printable*>::XIterator i = lst.begin(); i != lst.end(); ++i){
		i->print(out);
	}
	out << std::endl;
	out << "количество форм: " << oop::Shape::GetCount() << std::endl;
	out << "Размер списка: " << lst.size() << std::endl;

	out << std::endl << "очистка памяти... ";
	for(oop::XList<oop::Printable*>::XIterator i = lst.begin(); i != lst.end(); ++i)
		delete *i;
	lst.clear();
	out << "OK" << std::endl;
	assert(lst.empty() && "Список должен быть пустым");
	out << std::endl << "количество форм: " << oop::Shape::GetCount() << std::endl;
	out << "Размер списка: " << lst.size() << std::endl;

	out << std::endl << "Успешно";
	return 0;
}
