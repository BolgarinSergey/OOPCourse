#ifndef C_NAMED_H
#define C_NAMED_H

#include <string>
#include <iostream>

namespace oop{ //(*)

class Named{
public:
	Named( std::string const & name ) : m_name( name ) {}
	~Named( ) {}

    std::string const & getName()const { return m_name; }

private:
	std::string m_name;
};

class Printable: public virtual Named{
public:
	Printable( std::string const & name ) : Named( name ) {}
	virtual ~Printable( ) {}

    virtual void print(std::ostream& _stream)const = 0;
};

class Shape : public virtual Named{
public:
	Shape( std::string const & name ) : Named( name ) { ++sm_count; }
	Shape( Shape const & s ) : Named( s.getName() ) { ++sm_count; }
	virtual ~Shape( ){ --sm_count; }

	static int GetCount(){ return sm_count; }

private:
	static int sm_count;
};

}//namespace oop ссылка на (*)

int oop::Shape::sm_count = 0;

std::ostream& operator << ( std::ostream & _stream, oop::Printable const & p ){
    p.print( _stream );
    return _stream;
}

#endif
