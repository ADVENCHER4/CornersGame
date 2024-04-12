#pragma once

template<typename T>
class List
{
private:
   struct Node             // элемент списка
   {
      T _val;              // значение
      Node* _next;         // следующий элемент
      Node(T val) : _val(val), _next(nullptr) {}
   };
   Node* _head;            // начальный элемент
   Node* _last;            // последний элемент
   int _length;            // длина

public:
   List();
   void add(T val);        // добавление элемента в список
   T get(int);             // получение элемента по индексу
   int getLength();        // получение длины
   ~List();
};

template<typename T>
List<T>::List() : _head(nullptr), _length(0), _last(nullptr)
{
}

template<typename T>
void List<T>::add(T val)
{
   Node* element = new Node(val);   // создаем элемент
   if (!_head)                      // если начальный элемент пустой
   {
      _head = element;
      _last = element;
      _length++;
      return;
   }
   _last->_next = element;          // делаем новый элемент следующим для последнего
   _last = element;                 // делаем его последним
   _length++;
}

template<typename T>
T List<T>::get(int index)           
{
   Node* cursor = _head;
   for (int i = 0; i < index; i++)  // перебираем список, пока не дойдем до нужного индекса
   {
      cursor = cursor->_next;
   }
   return cursor->_val;
}

template<typename T>
int List<T>::getLength()
{
   return _length;                  // длина списка
}

template<typename T>
List<T>::~List()
{
   Node* cursor = _head;
   while (cursor)                   // очищаем память
   {
      Node* tmp = cursor;
      cursor = cursor->_next;
      delete tmp;
   }
}