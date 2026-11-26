#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <cstdarg>
#include <cwchar>
#include <stdlib.h>
#include <locale>
#include <cstddef>

#include "Error.h"
#include "Parm.h"
#include "Str.h"
#include "LT.h"
#include "IT.h"
#include "In.h"
#include "Log.h"
#include "Lexer.h"
#include "FST.h"
#include "GRB.h"      // грамматика Грейбах
#include "LEX.h"      // результат лексического анализа (ТЛ + ТИ)
#include "MFST.h"     // магазинный автомат