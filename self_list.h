#ifndef SELF_LIST_H
#define SELF_LIST_H

#include "node.h"

template <typename T>
class SelfList {
    public:
        enum Method {
            Move, Count, Transpose
        };

    protected:
        Node<T>* head;
        Method method;
        int nodes;

    public:
        SelfList(Method method) : head(nullptr) , nodes{0}, method{method} {};

        bool insert(T data) {
            auto *temp = new Node<T>(data);
            if (head == nullptr) {
                head = temp;
            } else {
                auto *re = head;
                while (re->next != nullptr)
                    re = re->next;
                re->next = temp;
            }
            nodes++;
            return true;
        }
        bool remove(T data) {
            auto * it = head;
            if(head->data == data) {
                if (size()==1) {
                    head = nullptr;
                    nodes = 0;
                    return true;
                }
                else {
                    auto * temp = head;
                    head = head->next;
                    delete temp;
                    nodes--;
                    return true;
                }
            }
            else {
                while (it->next != nullptr) {
                    if (it->next->data == data) {
                        break;
                    }
                    it = it->next;
                }
                if(it->next == nullptr){
                    return false;
                }
                auto * temp = it->next;
                it->next = it->next->next;
                nodes--;
                delete temp;
                return true;
            }
        }

        bool find(T data) {
            switch(this->method){
                case Transpose:{
                    auto *temp = head;
                    if(head->data == data) {
                        return true;}
                    if (nodes > 1) {
                            while (temp->next != nullptr) {
                                if (temp->next->data == data) {
                                    break;
                                }
                                temp = temp->next;
                            }
                            if(temp->next == nullptr){
                            return false;
                            }
                            swap(temp->next->data, temp->data);
                            return true;
                        }
                    return false;

                }
                case Move:{
                    auto *temp = head;
                    if(head->data == data) {
                        return true;}
                    if (nodes > 1) {
                        while (temp->next != nullptr) {
                            if (temp->next->data == data) {
                                break;
                            }
                            temp = temp->next;
                        }
                        // Por qué?
                        if(temp->next == nullptr){
                            return false;
                        }
                        auto* new_head = temp->next;
                        temp->next = temp->next->next;
                        new_head->next =head;
                        head =new_head;
                        return true;
                    }

                }
                case Count: {
                    auto *temp = head;
                    while (temp != nullptr) {
                        if (temp->data == data) {
                            temp->count++;
                            break;
                        }
                        temp = temp->next;
                    }
                    if(temp== nullptr){
                        return false;
                    }
                    else {
                        auto *it = head;
                        while (it != nullptr) {
                            if (temp == it)
                                break;
                            if (it->count < temp->count) {
                                swap(it->data, temp->data);
                                swap(it->count, temp->count);
                                return true;
                            }
                            it = it->next;
                        }
                        return false;
                    }
                }
            }
            return false;
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
            if(head!= nullptr) {
                auto *it = head;
                while (it != nullptr) {
                    std::cout << it->data << " ";
                    it = it->next;
                }
            }
        }

        ~SelfList() {

            if(nodes == 0){
                // Y esto?
            }
            else{
                this->head->killSelf();
                this->head = nullptr;
                this->nodes = 0;
            }
        }
};

#endif
