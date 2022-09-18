#include<iostream>
#include<list>


class gc : public base
{
public:
    static std::list<std::list void*>> *memory_ref_table;
    static void add_list(void* address)
    {
      std::list<void*> buf_list;
      buf_list.push_back(address);
      memory_ref_table->push_back(buf_list);
    }
    static void add_ref(T* address, T& ref)
    {
      for(auto it: *memory_ref_table)
      {
        if(address == it.begin())
        {
          it.push_back(ref);
        }
      }
    }
    static void remove_list(std::list<T&>::iterator first_address,
      std::list<std::list<T&>>::iterator sub_list_iter)
    {
      delete *first_address;
      memory_ref_table->erase(sub_list_iter)
    }

    static void remove_ref(std::list<T&>::iterator del_iter,
      std::list<std::list<T&>>::iterator sub_list_iter)
    {
      sub_list_iter->erase(del_iter);
    }
    static void check()
    {
      for(auto element : *memory_ref_table)
      {
        auto first_address = element.begin(), sub_list_iter = first_address;
        sub_list_iter++;
        bool cur_bind = false;

        for(;sub_list_iter != element.end();sub_list_iter++)
        {
          if(*first_address != *sub_list_iter)
            remove_ref(sub_list_iter, element);
          else
            cur_bind = true;
        }

        if(!cur_bind)
        {
          remove_list(first_address, element);
        }
      }
    }
    static void init()
    {
      memory_ref_table = new std::list<std::list void*>>;
    }
};

class base
{
public:
    void operator=(const base &other);
    void operator=(void *ref_by);
}

<template T>
class TYPE_PTR// this class should be a template class
{
public:
    T *ptr;
    TYPE_PTR(){}
    TYPE_PTR(T *other){/*should put something*/}
    TYPE_PTR& operator=(const TYPE_PTR &other);
    TYPE_PTR& operator=(T *other);
    T &operator*(void);
    T *operator->(void);
};

class TYPE_INT
{
    int x;
};

class TYPE_POINT
{
    int x, y;
};
