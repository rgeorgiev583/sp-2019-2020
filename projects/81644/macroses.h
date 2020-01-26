#ifndef __MACROSES_H__
#define __MACROSES_H__

/// possible options
#define COMPLE_OPT "-c"
#define DELETE_OPT "-d"
#define SHRINK_OPT "-s"


/// binary representation of the options
#define COMPLE_BIN 0b001
#define DELETE_BIN 0b010
#define SHRINK_BIN 0b100


/// parser messages
#define NO_SET_OPTIONS "Cannot have options in between the sets"
#define TOO_MANY_SETS "You have provided too many sets"


/// set-validator messages
#define ONE_TWO_SETS_REQUIRED "At least one set is required"
#define ONE_SET_REQUIRED "Only one set is required"
#define TWO_SETS_REQUIRED "Two sets are required"
#define UNKOWN_OPERATIONS "The provided set of combination is unknown"


/// a global macro-definition
#define nullptr (void *)0

#endif /// __MACROSES_H__
