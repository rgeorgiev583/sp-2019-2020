#ifndef __GLOBALS_H__
#define __GLOBALS_H__

/**
 * All possible ways to start the command `tr`
 * ----- example -----    -bin-  -hex-  -enum-
 * set1 set2           == 0b000 == 0 == OP_CLN
 * -c set1 set2        == 0b001 == 1 == OP_XXC
 * -d set1             == 0b010 == 2 == OP_XDX
 * -c -d set1          == 0b011 == 3 == OP_XDC
 * -s set1 [set2]      == 0b100 == 4 == OP_SXX
 * -s -c set1 [set2]   == 0b101 == 5 == OP_SXC
 * -s -d set1 set2     == 0b110 == 6 == OP_SDX
 * -s -d -c set1 set2  == 0b111 == 7 == OP_SDC
 */
enum { OP_CLN, OP_XXC, OP_XDX, OP_XDC, OP_SXX, OP_SXC, OP_SDX, OP_SDC };


/**
 * The two main structures
 * They are filled from the line-parser
 * And are used basically everywhere
 */
struct Options {
    bool comple;    /// -c
    bool del;       /// -d
    bool shrink;    /// -s
} Options_default = { false, false, false };

struct Sets {
    const char *set1;
    const char *set2;
} Sets_default = { nullptr, nullptr };


/// type of the set-validator
typedef const int (*Validator)(struct Sets*);

/// type of the operation-function
typedef int (*Operation)();

/// the global error message
static char *LAST_ERROR_MESSAGE = nullptr;

#endif /// __GLOBALS_H__
