#ifndef __HELPERS_H__
#define __HELPERS_H__

/**
 * --- Binary arithmetics ---
 * Returns a binary representation of the provided options
 */
static const int get_bin_options(struct Options *opts) {
    int result = 0b000;

    if (opts->comple == true) {
        result ^= COMPLE_BIN << 0;
    }

    if (opts->del == true) {
        result ^= DELETE_BIN << 0;
    }

    if (opts->shrink == true) {
        result ^= SHRINK_BIN << 0;
    }

    return result;
}

/**
 * --- Set checkers ---
 *
 * They respectively require TWO, ONE or AT LEAST ONE set
 * Might generate error messages
 */
static const int check_two_sets(struct Sets *sets) {
    if (sets->set1 == nullptr || sets->set2 == nullptr){
        LAST_ERROR_MESSAGE = TWO_SETS_REQUIRED;
        return -1;
    }

    return 0;
}

static const int check_one_set(struct Sets *sets) {
    if (sets->set1 == nullptr || sets->set2 != nullptr){
        LAST_ERROR_MESSAGE = ONE_SET_REQUIRED;
        return -1;
    }

    return 0;
}

static const int check_one_two_sets(struct Sets *sets) {
    if (sets->set1 == nullptr) {
        LAST_ERROR_MESSAGE = ONE_TWO_SETS_REQUIRED;
        return -1;
    }

    return 0;
}

/**
 * --- The set-validator ---
 *
 * Based on the binary representation of the options for the command
 * it indicates wheather or not the sets requirements are fulfilled
 *
 * Might generate error-message
 */
Validator op_set_validator(const int op) {
    if (op == OP_CLN || op == OP_XXC || op == OP_SDX || op == OP_SDC) {
        return check_two_sets;
    }

    if (op == OP_XDX || op == OP_XDC) {
        return check_one_set;
    }

    if(op == OP_SXX || OP_SXC) {
        return check_one_two_sets;
    }

    LAST_ERROR_MESSAGE = UNKOWN_OPERATIONS;
    return nullptr;
}

/// make it easy to print error message and exit
void perror_exit() {
    fprintf(stderr, "ERROR: %s\n", LAST_ERROR_MESSAGE);
    exit(0);
}

#endif /// __HELPERS_H__
