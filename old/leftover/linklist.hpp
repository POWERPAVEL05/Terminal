#ifndef LINKLIST
#define LINKLIST

#include <cstdio>
//todo: template
namespace pav{
    struct Knot{
        int element;
        Knot* next;
        
        Knot(Knot* t_knot, int t_element):
            next(t_knot),
            element(t_element)
        {}

        Knot(int t_element):
            next(nullptr),
            element(t_element)
        {}
        Knot():
            next(nullptr),
            element(0)
        {}

        //very important --> nextKnot is on heap!!!
        ~ Knot(){
            delete(next);
        }

    };

    struct LinkList{
        Knot* head;
        
        LinkList():
            head(new Knot())     
        {}

        ~LinkList(){
            delete(head);
        }

        void appKnot(int element = 0);

        void insertKnot(int element,int index);

        void deleteKnot(int index);

        void printList();

        long getLength();
    };
}


#endif
