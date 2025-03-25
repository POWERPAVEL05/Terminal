#include <stdexcept>
#include <cstdio>
#include "linklist.hpp"
using namespace pav;
using namespace std;

//add new Knot to end of last knot 

void pav::LinkList::appKnot(int element){
    if(!this->head->next){
        this->head->next = new Knot(nullptr,element);
    }else{
        Knot* current = this->head->next;
        while(current->next != nullptr){
             current = current->next;
        }
        current->next = new Knot(nullptr,element);  
    }
}

void pav::LinkList::insertKnot(int element,int index){
    if((pav::LinkList::getLength()) < index || index < 0){
        //printf("Out of Range");
        throw out_of_range("faulty index");
    }
    Knot* current = head;
    if(getLength() == index){
        appKnot(element);
    }
    else{
        for(int i = 0; i < index;i++){
            if(!current->next)break;//rethink!
            current = current->next;
        }
        Knot* hold = current->next;
        current->next = new Knot(hold,element);
    }
}

void pav::LinkList::deleteKnot(int index){
    if((getLength()-1) < index || index < 0){
        //printf("Out of Range");
        throw out_of_range("faulty index");
    }
    Knot* current = head;
    for(int i = 0;i<index;i++){
        current = current->next;  
    }
    Knot* hold = current->next->next;
    delete(current->next);
    current->next = hold;
}

void pav::LinkList::printList(){
    Knot* current = this->head;
    while(current != nullptr){
        printf("[%u]->",current->element);
        current = current->next;
    }
    printf("nullptr\n");//end of list
}

long pav::LinkList::getLength(){
    Knot* current = this->head->next;
    long length = 0;
    while(current != nullptr){
        length++;
        current = current->next;
    }
    return length;
}
