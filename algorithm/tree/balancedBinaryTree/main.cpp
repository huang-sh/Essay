#include <iostream>
#include <cstdlib>
#include "balanced.h"

using std::cout;
using std::cin;
using std::endl;

uint64_t field = 50000;
uint64_t Max = 9999;
uint64_t size = 10;
int main(void)
{
    pbalaTree tree = nullptr;
    uint64_t num = 1;
    field *= time(nullptr);
    for (int index = 0; index < size; ++index)
    {
        field *= num;
        field = (field >> 3) * num;
        srand(field);
        num = rand() % Max + 1;
        cout << num << " ";
        tree = insertBalanceTree(tree, num);
    }
    ElemType key;
    do {
        cout.put('\n');
        DLR(tree);
        cout.put('\n');
        LRD(tree);
        cout.put('\n');
        LDR(tree);
        cout.put('\n');
        cin >> key;
        if (key == 0)
        {
            break;
        }
        tree= deleteNodeLeft(tree, key);
    } while(1);
    deleteAll(tree);
    DLR(tree);
    return 0;
}
