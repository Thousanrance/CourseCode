#ifndef CLOSEHASHTABLE_H_INCLUDED
#define CLOSEHASHTABLE_H_INCLUDED

template <class KEY, class OTHER>
class dynamicSearchTable
{
public:
    virtual SET<KEY, OTHER> *find(const KEY &x)const = 0;
    virtual void insert(const SET<KEY, OTHER> &x) = 0;
    virtual void remove(const KEY &x) = 0;
    virtual ~dynamicSearchTable(){};
};

template <class KEY, class OTHER>
class closeHashTable:public dynamicSearchTable<KEY, OTHER>
{
private:
    struct node
    {
        //散列表的结点类
        SET <KEY, OTHER> data;
        int state; //0 -- empty 1 -- active 2 -- deleted
        node()
        {
            state = 0;
        }
    };
    node *array;
    int size;
    int (*key)(const KEY &x);
    static int defaultKey(const int &x) //静态好处，不依赖于对象即可调用
    {
        return x;
    }
    public:
    closeHashTable(int length = 101, int (*f)(const KEY &x) = defaultKey) ;
    ~closeHashTable()
    {
        delete [] array;
    }
    SET<KEY, OTHER> *find(const KEY &x) const;
    void insert(const SET<KEY, OTHER> &x);
    void remove(const KEY &x);
};

template <class Type>
closeHashTable<Type>::closeHashTable(int length, int (*f)(const Type &x))
{
    size = length;
    array = new node[size];
    key = f;
}

template <class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::insert(const SET<KEY, OTHER> &x)
{
    int initPos, pos ;
    initPos = pos = key(x.key) % size;
    do
    {
        if (array[pos].state != 1)
        {
            // 0或者2，找到空单元
            array[pos].data = x;
            array[pos].state = 1;
            return;
        }
        pos = (pos+1) % size;
    }while (pos != initPos);
}

template <class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::remove(const KEY &x)
{
    int initPos, pos ;
    initPos = pos = key(x) % size;
    do
    {
        if(array[pos].state == 0)
        {
            return;
        }
        if(array[pos].state == 1 && array[pos].data.key == x)
        {
            // 找到，删除
            array[pos].state = 2;
            return;
        }
        pos = (pos+1) % size;
    }while (pos != initPos);
}

template <class KEY, class OTHER>
SET<KEY, OTHER> *closeHashTable<KEY, OTHER>::find(const KEY &x)const
{
    int initPos, pos;
    initPos = pos = key(x) % size;
    do
    {
        if(array[pos].state == 0) //没有找到
        {
            return NULL;
        }
        if(array[pos].state == 1 && array[pos].data.key == x) // 找到
        {
            return (SET<KEY,OTHER> *) &array[pos];
        }
        pos = (pos+1) % size;
    }while (pos != initPos);
}



#endif // CLOSEHASHTABLE_H_INCLUDED
