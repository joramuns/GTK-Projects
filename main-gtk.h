//
//  main.h
//  C7_SmartCalc
//
//  Created by Joramun Sasin on 8/29/22.
//

#ifndef main_h
#define main_h

#include "calculator.h"

typedef struct {
    GtkButton *button;
    GtkText *entry;
    char *value;
    char *name;
} buttonData;

#endif /* main_h */