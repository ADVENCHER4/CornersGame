#pragma once

template<typename T>
class List
{
private:
   struct Node             // ������� ������
   {
      T _val;              // ��������
      Node* _next;         // ��������� �������
      Node(T val) : _val(val), _next(nullptr) {}
   };
   Node* _head;            // ��������� �������
   Node* _last;            // ��������� �������
   int _length;            // �����

public:
   List();
   void add(T val);        // ���������� �������� � ������
   T get(int);             // ��������� �������� �� �������
   int getLength();        // ��������� �����
   ~List();
};

template<typename T>
List<T>::List() : _head(nullptr), _length(0), _last(nullptr)
{
}

template<typename T>
void List<T>::add(T val)
{
   Node* element = new Node(val);   // ������� �������
   if (!_head)                      // ���� ��������� ������� ������
   {
      _head = element;
      _last = element;
      _length++;
      return;
   }
   _last->_next = element;          // ������ ����� ������� ��������� ��� ����������
   _last = element;                 // ������ ��� ���������
   _length++;
}

template<typename T>
T List<T>::get(int index)           
{
   Node* cursor = _head;
   for (int i = 0; i < index; i++)  // ���������� ������, ���� �� ������ �� ������� �������
   {
      cursor = cursor->_next;
   }
   return cursor->_val;
}

template<typename T>
int List<T>::getLength()
{
   return _length;                  // ����� ������
}

template<typename T>
List<T>::~List()
{
   Node* cursor = _head;
   while (cursor)                   // ������� ������
   {
      Node* tmp = cursor;
      cursor = cursor->_next;
      delete tmp;
   }
}