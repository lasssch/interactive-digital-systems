#define ARRAYLIST_H

template <class T>
class arrayList {
    private:
        T *data;
        void resize();
        bool arrayFull(); 

    public:
    int length; //Length of the array
    int count; //Number of elements withing the array
    arrayList(){
        data = new T[5];
        length = 5;
        count = 0;    
    }
    bool contains(T item);
    int indexOf(T item);
    T* getElementAt(int index);
    int size();
    void add(T item);
    void add(T item, int index);
    void set(int index, T item);
    void remove(int index);
    void remove(T item);


};