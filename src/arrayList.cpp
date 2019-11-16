#ifndef ARRAYLIST_H
#include "arrayList.h"
#endif

#ifndef NULL
#define NULL 0
#endif

//Resize array to make space for more data
template <class T>
void arrayList<T>::resize() {
    T *temp = new T[length * 2];
    for (int i = 0; i < length; i++)
    {
        temp[i] = data[i];
    }
    data = temp;
    length *= 2;
}

//Check whether or not the length of the array is the same as the number of elements
template <class T>
bool arrayList<T>::arrayFull() {
    return length == count;
}

//Add data to the array
template <class T> 
void arrayList<T>::add(T item) {
    //If the array is full, we resize it
    if(arrayFull()) {
        resize();
    }
    //Adding the new data 
    data[count] = item;
    count++;
}

//Add data to the array at a specific index
template <class T> 
void arrayList<T>::add(T item, int index) {
    //If the array is full, we resize it
    if(arrayFull()) {
        resize();
    }

    //Creating a temporary array with the new element
    bool newItemPlaced = false;
    T *temp = new T[length];
    for (int i = 0; i < length; i++)
    {
        if(i == index) {
            temp[i] = item;
            newItemPlaced = true;
        } else {
            if(newItemPlaced) {
                temp[i] = data[i - 1];
            } else {
                temp[i] = data[i];
            }
        }
    }
    
    //Adding new data
    data = temp;
    count++;
}

template <class T>
void arrayList<T>::set(int index, T item) {
    if(index >= 0 && index <= count) {
        data[index] = item;
    }
}

template <class T> 
void arrayList<T>::remove(int index) {
    for (int i = index; i < count; i++)
    {
        if(i == length) {
            data[i] = NULL;
        } else {
            data[i] = data[i + 1];
        }
    }
    
    count--;
}

template <class T>
void arrayList<T>::remove(T item) {
    bool foundItem = false;

    for (int i = 0; i < count; i++)
    {
        if(foundItem) {
            if(i == length) {
                data[i] = NULL;
            } else {
                data[i] = data[i + 1];
            }
        } else {
            if(data[i] == item) {
                foundItem = true;
            }
        }   
    }
    
    count--;
}

template <class T>
T* arrayList<T>::getElementAt(int index) {
    if(index <= length) {
        return &data[index];
    } else {
        return NULL;
    }
}

template <class T>
bool arrayList<T>::contains(T item) {
    bool itemFound = false;

    for (int i = 0; i < length; i++)
    {
        if(data[i] == item) {
            itemFound = true;
            break;
        }
    }
    
    return itemFound;
}

template <class T>
int arrayList<T>::indexOf(T item) {
    int itemAt = -1;

    for (int i = 0; i < length; i++)
    {
        if(data[i] == item) {
            itemAt = i;
            break;
        }
    }
    
    return itemAt;
}