#include <iostream>
using namespace std;

class Player{
public:
    void Attack();
    void Die();
    void HealMe(int value);

public:
    int _hp;
    int _attack;
    int _defence;
};