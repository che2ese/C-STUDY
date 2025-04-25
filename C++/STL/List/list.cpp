#include <iostream>
using namespace std;
#include <list>

int main()
{
    list<int> li{1, 2, 3, 4, 5};

    /*
        li.push_back(100);
        li.push_front(100);

        list<int>::iterator it = li.insert(li.end(), 6);
        li.insert(li.end(), 7);
        li.erase(it);
    */

   for (list<int>::iterator it = li.begin(); it != li.end();)
   {
        int value = *it;
        if (value % 2 == 0 )
            it = li.erase(it);
        else
            it++;
   }
}
