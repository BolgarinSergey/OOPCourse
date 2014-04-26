#ifndef SHAPES_H
#define SHAPES_H

#include "Base.h"
#include "XList.hpp"

namespace oop{

class XPoint : public Shape, public Printable{
public:
    XPoint( std::string const & name, float x, float y )
		: Named(name)
		, Shape(name)
		, Printable(name)
		, m_x( x )
		, m_y( y )
	{ }
	virtual ~XPoint( ){ }

	float getX()const { return m_x; }
	float getY()const { return m_y; }
	void print(std::ostream& _stream)const{
		_stream << this->getName() << " : Точка(" << m_x << ", " << m_y << ")" << std::endl;
	}

private:
	float m_x, m_y;
};

class XCircle : public Shape, public Printable{
public:
	XCircle( std::string const & name, XPoint const & c, float r )
		: Named(name)
		, Shape(name)
		, Printable(name)
		, m_c(c)
        , m_r (r)
        , m_area(3.14159f*m_r*m_r)
	{ }
	virtual ~XCircle( ){ }

	virtual void print(std::ostream& _stream)const{
		_stream << this->getName() << " : Окружность( центр(" << m_c.getX() << ", " << m_c.getY() << ") радиус(" << m_r <<  ") площадь(" << m_area << ") )" << std::endl;
	}

private:
	XPoint m_c;
	float m_r, m_area;
};

class XRect : public Shape, public Printable{
public:
	XRect( std::string const & name, XPoint const & p1, XPoint const & p2 )
		: Named(name)
		, Shape(name)
		, Printable(name)
		, m_p1( p1 )
	, m_p2( p2 )
	{
		m_area = (p2.getX() - p1.getX()) * (p2.getY() - p1.getY());
    }
	virtual ~XRect( ){ }

	XPoint const & getTopLeft()const { return m_p1; }
	XPoint const & getBottomRight()const { return m_p2; }
	float getArea()const { return m_area; }
	virtual void print(std::ostream& _stream)const{
		_stream << this->getName() << " : Прямоугольник( левая верхняя(" << m_p1.getX() << ", " << m_p1.getY() << ") Правая нижняя(" << m_p2.getX() << ", " << m_p2.getY() << ") Площадь(" << getArea() << ") )" << std::endl;
	}

private:
	XPoint m_p1, m_p2;
	float m_area;
};

class XSquare : public XRect{
public:
	XSquare::XSquare( std::string const & name, XPoint const & p, float size )
		: Named(name)
		, XRect(name, p, XPoint("Временно", p.getX()+size, p.getY()+size))
		, m_size(size)
	{ }
	virtual ~XSquare( ){ }

	virtual void print(std::ostream& _stream)const{
		_stream << this->getName() << " : Квадрат( левая верхняя(" << XRect::getTopLeft().getX() << ", " << XRect::getTopLeft().getY() << ") Размер(" << m_size << ") Площадь(" << XRect::getArea() << ") )" << std::endl;
	}

private:
	float m_size;
};

class XPolyline : public Shape, public Printable{
public:
	XPolyline( std::string const & name )
		: Named(name)
		, Shape( name )
		, Printable(name)
		, m_summLength(0.0f)
	{ }
	virtual ~XPolyline( ){ }

	virtual void print(std::ostream & _stream)const{
		_stream << this->getName() << " : Ломаная( ";
		if(m_pList.empty())
			_stream << "пусто";
		else{
			_stream << std::endl;
			for(oop::XList<XPoint>::XIterator i = m_pList.begin(); i != m_pList.end(); ++i){
				_stream << '\t' << *i;
			}
		}
		_stream << "\tДлина: " << m_summLength << std::endl;
		_stream << ")" << std::endl;
	}

	void AddPoint(XPoint const & p){
		m_pList.push_back(p);
		XList<XPoint>::XRevIterator lastPoint = m_pList.rbegin();
		float dx = (*lastPoint).getX() - p.getX();
		float dy = (*lastPoint).getY() - p.getY();
		m_summLength += sqrt(dx*dx + dy*dy);
	}

private:
	oop::XList<XPoint> m_pList;
	float m_summLength;
};

}

#endif
