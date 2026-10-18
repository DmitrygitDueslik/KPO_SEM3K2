#pragma once
#define ID_MAXSIZE        5              // максимальное количество символов в идентификаторе
#define TI_MAXSIZE     4096              // максимальное количество строк в таблице идентификаторов
#define TI_INT_DEFAULT 0x00000000        // значение по умолчанию дл€ типа integer
#define TI_STR_DEFAULT 0x00              // значение по умолчанию дл€ типа string
#define TI_NULLIDX     0xffffffff        // нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE 255

namespace IT                // таблица идентификаторов
{
    enum IDDATATYPE { INT = 1, STR = 2 };            // типы данных идентификаторов: integer, string
    enum IDTYPE { V = 1, F = 2, P = 3, L = 4 };   // типы идентификаторов: переменна€, функци€, параметр, литерал

    struct Entry                    // строка таблицы идентификаторов
    {
        int         idxfirstLE;             // индекс первой строки в таблице лексем
        char        id[ID_MAXSIZE];         // идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
        IDDATATYPE  iddatatype;             // тип данных
        IDTYPE      idtype;                 // тип идентификатора
        union
        {
            int vint;                        // значение integer
            struct
            {
                char len;                        // количество символов в string
                char str[TI_STR_MAXSIZE - 1];    // символы string
            } vstr;                           // значение string
        } value;                             // значение идентификатора
    };

    struct IdTable                  // экземпл€р таблицы идентификаторов
    {
        int    maxsize;              // емкость таблицы идентификаторов < TI_MAXSIZE
        int    size;                 // текущий размер таблицы идентификаторов < maxsize
        Entry* table;                // массив строк таблицы идентификаторов
    };

    IdTable Create(int size);                                     // создать таблицу идентификаторов
    void Add(IdTable& idtable, Entry entry);                      // добавить строку в таблицу идентификаторов
    Entry GetEntry(IdTable& idtable, int n);                      // получить строку таблицы идентификаторов
    int IsId(IdTable& idtable, char id[ID_MAXSIZE]);              // вернуть номер строки, если есть, иначе TI_NULLIDX
    void Delete(IdTable& idtable);                                // удалить таблицу идентификаторов (освободить пам€ть)
}