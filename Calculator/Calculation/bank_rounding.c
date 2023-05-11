#include "bank_rounding.h"

#include <math.h>

double bank_rounding(double value) { return roundf(value * 100.0) / 100.0; }
