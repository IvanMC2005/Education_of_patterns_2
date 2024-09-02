#include <iostream>
#include <limits>
#include <locale>
#include <stdexcept>
char ch;
using namespace std;
template <typename T1>
class Queue_vec
{
public:
    Queue_vec(Queue_vec && other)
    {
        current_length = other.current_length;
        front = other.front;
        tail = other.tail;
        inf = other.inf;
        other.inf = nullptr;
    }
    Queue_vec(Queue_vec & other)
    {
        T1 odt;
        int k = other.current_length;
        current_length = 0;
        mas_lenght = other.mas_lenght;
        inf = new T1[mas_lenght];
        front = 0;
        tail = mas_lenght - 1;
        while(k)
        {
            odt = other.delete_elem();
            add_elem(odt);
            other.add_elem(odt);
            k--;
        }
    }
    Queue_vec & operator = ( Queue_vec & other )
    {
        if (inf)
            delete[] inf;
        if (other.Empty()) return *this;
        T1 odt;
        int k = other.current_length;
        current_length = 0;
        mas_lenght = other.mas_lenght;
        inf = new T1[mas_lenght];
        front = 0;
        tail = mas_lenght - 1;
        while(k)
        {
            odt = other.delete_elem();
            add_elem(odt);
            other.add_elem(odt);
            k--;
        }
    }
    void operator = ( Queue_vec && other )
    {
        if (inf)
            delete[] inf;
        current_length = other.current_length;
        front = other.front;
        tail = other.tail;
        inf = other.inf;
        other.inf = nullptr;
    }
    Queue_vec(int n): mas_lenght(n)
    {
        current_length = 0;
        inf = new T1[mas_lenght];
        front = 0;
        tail = mas_lenght - 1;
    }
    ~Queue_vec()
    {
        cout << "Деструктор класса Queue_vec";
        if (inf)
            delete[] inf;
    }
    int add_elem(T1 item)
    {
        if (Full()) return 0;
        tail = (tail + 1) % mas_lenght;
        inf[tail] = item;
        current_length++;
        return 1;
    }
    T1 delete_elem()
    {
        if (!Empty())
        {
            front = (front + 1) % mas_lenght;
            current_length--;
            return inf[front - 1];
        }
        throw invalid_argument("Попытка удалить элемент пустой очереди\n");
    }
    T1 ndread()
    {
        return inf[front];
    }
    bool Full() const
    {
        return (tail + 2) % mas_lenght == front;
    }
    bool Empty() const
    {
        return (tail + 1) % mas_lenght == front;
    }
private:
    int front, tail;
    int mas_lenght;
    T1 * inf;
    int current_length;
};

template <typename T> void ReleaseQueue()
{
    T number;
    Queue_vec<T> que(10);
    int menu;
    do
    {
        system("cls");
        cout << "1 - добавить элемент в очередь\n2 - удалить элемент из очереди\n3 - прочитать превый элемент очереди\n4 - проверить на полноту\n5 - проверить на пустоту\n6 - Выход\n";
        cin >> menu;
        if (menu > 6 || menu < 0) cin.setstate(ios_base::failbit);
        while((ch = getchar()) != '\n');
        while(cin.fail())
        {
            cin.clear();
            cout << "1 - добавить элемент в очередь\n2 - удалить элемент из очереди\n3 - прочитать превый элемент очереди\n4 - проверить на полноту\n5 - проверить на пустоту\n6 - Выход\n";
            cin >> menu;
            if (menu > 6 || menu < 0) cin.setstate(ios_base::failbit);
            while((ch = getchar()) != '\n');
        }
        switch(menu)
        {
            case 1:
            {
                if (que.Full())
                {
                    cout << "Очередь заполнена\n";
                break;
                }
                cout << "Введите элемент очереди\n";
                cin >> number;
                while((ch = getchar()) != '\n');
                while(cin.fail())
                {
                    cin.clear();
                    cout << "Введите элемент очереди\n";
                    cin >> number;
                    while((ch = getchar()) != '\n');
                }
                que.add_elem(number);
                break;
            }
            case 2:
            {
                if (que.Empty())
                {
                    cout << "Очередь пуста\n";
                    break;
                }
                try
                {
                    cout << que.delete_elem() << endl;
                }
                catch(invalid_argument & ex)
                {
                    cout << ex.what() << endl;
                }
                break;
            }
            case 3:
            {
                if (que.Empty())
                {
                    cout << "Очередь пуста\n";
                    break;
                }
                if (typeid(char) == typeid(number))
                {
                    cout << static_cast<int>(que.ndread()) << endl; break;
                }
                cout << que.ndread() << endl; break;
            }
            case 4: cout << (que.Full() ? "Очередь заполнена\n" : "Очередь не заполнена\n");break;
            case 5: cout << (que.Empty() ? "Очередь пуста\n" : "Очередь не пуста\n");break;
        }
        system("pause");
    }
    while(menu != 6);
}

int main()
{
    setlocale(0, "rus");
    int type;
    cout << "Какой тип использовать? 0 - char 1 - double\n";
    cin >> type;
    if(type != 0 && type != 1)
    {
        cin.setstate(ios_base::failbit);
    }
    while(cin.fail())
    {
        cin.clear();
        while((ch = getchar()) != '\n');
        cout << "Какой тип использовать? 0 - char 1 - double\n";
        cin >> type;
        if(type != 0 && type != 1)
        {
            cin.setstate(ios_base::failbit);
        }
    }
    if (type == 1)
    {
        ReleaseQueue<double>();
    }
    else
    {
        ReleaseQueue<char>();
    }
    return 0;
}
