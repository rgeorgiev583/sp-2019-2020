#ifndef __PARSER_H__
#define __PARSER_H__

/// used to traverse the available options
static const char* const OPTIONS[] = { COMPLE_OPT, DELETE_OPT, SHRINK_OPT, nullptr };

/// checks if the passed arg is an available option
static bool in_options(const char *arg) {
    for (int i = 0; ; ++i) {
        if (OPTIONS[i] == nullptr) {
            break;
        }

        if (0 == strcmp(arg, OPTIONS[i])) {
            return true;
        }
    }

    return false;
}

/**
 * Fills in the properties of the Options main struct
 * Returns the index of the argument after the last provided option
 */
static int parse_options(const int from, const int to, const char* const* argv, struct Options *options) {
    for(int i = from; i < to; ++i) {
        if (in_options(argv[i])) {
            if (0 == strcmp(argv[i], COMPLE_OPT)) options->comple = true;
            else if(0 == strcmp(argv[i], DELETE_OPT)) options->del = true;
            else if(0 == strcmp(argv[i], SHRINK_OPT)) options->shrink = true;
        }
        else return i;
	}
}

/**
 * Fills in the properties of the Sets main struct
 * Might generate an error message if an option is given in between the sets
 */
static int parse_sets(const int from, const int to, const char* const* argv, struct Sets *sets) {

    const int total_sets_given = to - from;
    if (total_sets_given <= 2) {
        for (int i = 0; i < total_sets_given; ++i) {
            const char *set = argv[from + i];
            if (in_options(set) == false) {
                switch(i) {
                    case 0: sets->set1 = set; break;
                    case 1: sets->set2 = set; break;
                }
            }
            else {
                LAST_ERROR_MESSAGE = NO_SET_OPTIONS;
                return -1;
            }
        }

        return 0;
	}

    LAST_ERROR_MESSAGE = TOO_MANY_SETS;
    return -1;
}

/// used to parse and feed the Options and Set structs from the raw line of arguments
static int parse_args(const int argc, const char* const* argv, struct Options *options, struct Sets *sets) {
    const int options_offset = parse_options(0, argc, argv, options);
    return parse_sets(options_offset, argc, argv, sets);
}

#endif /// __PARSER_H__
