#include <math.h>

#include "bank_rounding.h"

double bank_rounding(double value) {
    return roundf(value * 100.0) / 100.0;
}
