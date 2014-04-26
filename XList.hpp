#ifndef C_XLIST_H
#define C_XLIST_H

#include <exception>

namespace oop{

template <typename C>
class XList{
private:
	//элементы списка
	struct ListNode{
		ListNode( C const & value ) : data(value)
		{
			this->next = NULL;
			this->prev = NULL;
		}
		~ListNode() { }
		C data;
		ListNode* next;
		ListNode* prev;
	};

public:
	//основные исключения
	class ListIsEmpty: public std::exception{ };
	class InvalidAccess: public std::exception{ };

	//типы итераций
	class XBaseIterator{
	public:
        XBaseIterator( ListNode* pointer ){ m_element = pointer;}
        XBaseIterator( XBaseIterator const & i ){ m_element = i.m_element; }

        XBaseIterator& operator=( XBaseIterator const & i ){
            m_element = i.m_element;
			return *this;
		}

        bool operator==( XBaseIterator const & i ){
            if(m_element == i.m_element)
				return true;
			return false;
		}

        bool operator!=( XBaseIterator const & i ){
            if(m_element != i.m_element)
				return true;
			return false;
		}

		C operator*()const{ return m_element->getData(); }
		C& operator*(){ return m_element->data; }
		C operator->(){ return m_element->data; }

	protected:
		ListNode* m_element;
	};

	class XIterator: public XBaseIterator{
	public:
		XIterator( ListNode* pointer ):XBaseIterator(pointer){ }
        XIterator( XIterator const &i ):XBaseIterator(i){ }
		~XIterator(void){ }

        XIterator & operator++(){
			m_element = m_element->next;
			return *this;
		}

        XIterator operator++( int ){
			XIterator temp = *this;
			++(*this);
			return temp;
		}

		XIterator & operator--(){
			m_element = m_element->prev;
			return *this;
		}

		XIterator operator--( int ){
			XIterator temp = *this;
			--*this;
			return temp;
		}
	};

	class XRevIterator: public XBaseIterator{
	public:
		XRevIterator( ListNode* pointer ):XBaseIterator(pointer){ }
        XRevIterator( XRevIterator const &i ):XBaseIterator(i){ }
		~XRevIterator(void){ }

        XRevIterator & operator++(){
			m_element = m_element->prev;
			return *this;
		}

        XRevIterator operator++( int ){
			XRevIterator temp = *this;
			++*this;
			return temp;
		}

		XRevIterator & operator--(){
			m_element = m_element->next;
			return *this;
		}

		XRevIterator operator--( int ){
			XRevIterator temp = *this;
			--*this;
			return temp;
		}
	};

//***************
//СПИСОК КЛАССА
//***************
public:
	XList( )
		:m_head(NULL)
		, m_tail(NULL)
		, m_size(0)
	{
		m_head = NULL;
		m_tail = NULL;
	}
	~XList( ){
		clear();
	}

    XIterator begin()const { return XIterator(m_head); }
    XIterator end()const { return XIterator(NULL); }

	XRevIterator rbegin()const { return XRevIterator(m_tail); }
	XRevIterator rend()const { return XRevIterator(NULL); }

	void push_front( C const & element ){
        ListNode* newEl = new ListNode(element);
		if(NULL = m_head){
			m_head = newEl;
			m_tail = newEl;
		}else{
			newEl->next = m_head;
			m_head->prev = newEl;
			m_head = newEl;
		}
		m_size++;
	}

	void push_back( C const & element ){
        ListNode* newEl = new ListNode(element);
		if(NULL == m_tail){
			m_head = newEl;
			m_tail = newEl;
		}else{
			newEl->prev = m_tail;
			m_tail->next = newEl;
			m_tail = newEl;
		}
		m_size++;
	}

	void pop_front(){
		if(empty())
			throw ListIsEmpty();
		ListNode* old = m_head;
		m_head = m_head->next;
		if(NULL == m_head)
			m_tail = NULL;
		delete old;
		m_size--;
	}

	void pop_back(){
		if(empty())
			throw ListIsEmpty();
		ListNode* old = m_tail;
		m_tail = m_tail->prev;
		if(NULL == m_tail)
			m_head = NULL;
		delete old;
		m_size--;
	}

	void clear(){
		ListNode* p = m_head;
		while(p != NULL){
			ListNode* t = p;
			p = p->next;
			delete t;
		}
		m_head = NULL;
		m_tail = NULL;
		m_size = 0;
	}

	inline bool empty()const{
		if(m_head == NULL)
			return true;
		return false;
	}

	inline size_t size()const{
		return m_size;
	}

private:
    //Запрет на копирование конструктором и операции присваивания 
	//поэтому выведен в отдельный блок
	XList(XList const &L);
	XList& operator=(XList const &L);

private:
	ListNode* m_head;
	ListNode* m_tail;
	size_t m_size;
};

}

#endif
