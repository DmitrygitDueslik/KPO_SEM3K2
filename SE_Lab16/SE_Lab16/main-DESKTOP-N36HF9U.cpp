#include <iostream>
#include <locale>
#include "FST.h"

// автомат дл€ while(?)*(write+read+seek)*?+do;l+  (21 состо€ние, 0 - старт, 20 - финал)
#define MY_FST(str) FST::FST(str, 22, \
    FST::NODE(1, FST::RELATION('w', 1)), \
    FST::NODE(1, FST::RELATION('h', 2)), \
    FST::NODE(1, FST::RELATION('i', 3)), \
    FST::NODE(1, FST::RELATION('l', 4)), \
    FST::NODE(1, FST::RELATION('e', 5)), \
    FST::NODE(5, FST::RELATION(' ', 5), FST::RELATION(' ', 17), FST::RELATION('w', 6), FST::RELATION('r', 10), FST::RELATION('s', 13)), \
    FST::NODE(1, FST::RELATION('r', 7)), \
    FST::NODE(1, FST::RELATION('i', 8)), \
    FST::NODE(1, FST::RELATION('t', 9)), \
    FST::NODE(1, FST::RELATION('e', 16)), \
    FST::NODE(1, FST::RELATION('e', 11)), \
    FST::NODE(1, FST::RELATION('a', 12)), \
    FST::NODE(1, FST::RELATION('d', 16)), \
    FST::NODE(1, FST::RELATION('e', 14)), \
    FST::NODE(1, FST::RELATION('e', 15)), \
    FST::NODE(1, FST::RELATION('k', 16)), \
    FST::NODE(4, FST::RELATION('w', 6), FST::RELATION('r', 10), FST::RELATION('s', 13), FST::RELATION(' ', 17)), \
    FST::NODE(2, FST::RELATION(' ', 17), FST::RELATION('d', 18)), \
    FST::NODE(1, FST::RELATION('o', 19)), \
    FST::NODE(1, FST::RELATION(';', 20)), \
    FST::NODE(2, FST::RELATION('l',21),FST::RELATION('l',20)),\
    FST::NODE() \
    )

void test(char* str)
{
    FST::FST fst = MY_FST(str);
    if (FST::execute(fst))
    {
        std::cout << "÷епочка \"" << str << "\" распознана" << std::endl;
    }
    else
    {
        std::cout << "÷епочка \"" << str << "\" не распознана" << std::endl;
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    // 7 цепочек (должны распознаватьс€)
    test((char*)"while do;l");
    test((char*)"while read do;lll");
    test((char*)"while write do;");
    test((char*)"while seek do;");
    test((char*)"while writeread do;");
    test((char*)"while readseek do;");
    test((char*)"while writereadseek do;");

    // 2 цепочки, которые Ќ≈ должны распознаватьс€
    test((char*)"while do");        // все символы прочитаны, но не хватает ";"
    test((char*)"while xyz do;");   // разбор обрываетс€ раньше конца строки

    system("pause");
    return 0;
}