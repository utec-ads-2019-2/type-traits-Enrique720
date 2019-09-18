#ifndef TRAITS_LIST_H
#define TRAITS_LIST_H

#include "node.h"

template <typename Tr>
class TraitsList {
public:
    typedef typename Tr::T T;
    typedef typename Tr::Operation Operation;

private:
    Node<T>* head;
    Operation cmp;
    int nodes;

    bool find(T data, Node<T> **&pointer) {
        while((*pointer) != nullptr){

            if ((*pointer)->data == data){
                return true;
            }
            else if(cmp(data,(*pointer)->data)){
                break;
            }
            pointer = &((*pointer)->next);
        }
        return false;
    }
public:
    TraitsList() : head(nullptr),nodes{0} {};

    bool insert(T data) {
        auto ** pointer = &(this->head);
        if(!find(data, pointer)){
            auto* temp = new Node<T>(data);
            temp->next = (*pointer);
            (*pointer) = temp;
            this->nodes++;
            return true;
        }
        else{
            return false;
        }
    }
    bool remove(T data) {
         auto ** pointer = &(this->head);
        if(find(data,pointer)){
            auto* temp = (*pointer);
            (*pointer) = temp->next;

            delete temp;
            (this->nodes)--;
            return true;
        }
        return false;
    }
    bool find(T data) {
        auto** temp = &(this->head);
        return find(data,temp);

    }

    T operator [] (int index) {
        if(index < nodes && index >= 0){
            auto * it = head;
            for(int i = 0; i < index ; i++){
                it = it->next;
            }
            return it->data;
        }
        return -1;
    }

    int size() {
        return nodes;
    }

    void print() {
        auto * temp =this->head;
        for(int i = 0 ;i < this->nodes; i ++){
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    }


    ~TraitsList() {
        if(nodes == 0){
            delete this;
        }
        else{
            this->head->killSelf();
            this->head = nullptr;
            this->nodes = 0;
        }
    }
};
#endif
