#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

/// global buffers for reading and writing
static char BUFF[BUFSIZ];      /// user input
static char OUTPUT[BUFSIZ];    /// processed user input

/// get the index of a character from a set
const int get_position(const char c, const char* set){
	const char* position_ptr = strchr(set, c);

	if (position_ptr == nullptr) {
        return -1;
	}

	return position_ptr - set;
}

/**
 * Returns the character at index pos from the given set
 * Or the last character from the set if pos exceeds the length of set
 */
char transformation(const int pos, const char* set){
	int n = strlen(set);
	if(pos > n) return set[n - 1];
	else return set[pos];
}

/**
 * --- The following functions are the whole implementation of the command `tr` with different options and sets ---
 * They all accept number of characters which are to be processed and sets to work with
 * They all return the size of the processed user input
 */

/// fills the output with the characters from the user input that are NOT IN the set
static int delete(const int read_count, const char* set){
    int new_size = 0;
    for(int i = 0; i < read_count; ++i) {
        if(-1 == get_position(BUFF[i], set)){
            OUTPUT[new_size] = BUFF[i];
            ++new_size;
        }
    }

    return new_size;
}

/// the same like delete() except it fills with characters that are IN the set
static int delete_compl(const int read_count, const char* set){
    int new_size = 0;
    for(int i = 0; i < read_count; ++i) {
        if(-1 != get_position(BUFF[i], set) || '\n' == BUFF[i]){
            OUTPUT[new_size] = BUFF[i];
            ++new_size;
        }
    }

    return new_size;
}

/// replaces the characters from set1 with their corresponding characters from set2
static int transform(const int read_count, const char* set1, const char* set2){
	int pos;
	for(int i = 0; i < read_count; ++i) {
        pos = get_position(BUFF[i], set1);

        if(-1 != pos) {
            OUTPUT[i] = transformation(pos, set2);
        }
        else {
            OUTPUT[i] = BUFF[i];
        }
	}

    return read_count;
}

/// replaces the characters that are NOT in set1 with the last character from set2
static int transform_complementary(const int read_count, const char* set1, const char* set2){
	const char last = set2[strlen(set2) - 1];

    int pos;
    for(int i = 0; i < read_count; ++i) {
        pos = get_position(BUFF[i], set1);

        if(-1 == pos && '\n' != BUFF[i]){
            OUTPUT[i] = last;
        }
        else {
            OUTPUT[i] = BUFF[i];
        }
    }

    return read_count;
}

/// replaces all repetitions of characters from set
static int shrink_all(const int read_count, const char* set) {
    OUTPUT[0] = BUFF[0];

    int new_size = 1;
    int pos;
    for(int i = 1; i < read_count; ++i) {
        pos = get_position(BUFF[i], set);
        if(-1 != pos && BUFF[i - 1] == BUFF[i]) {
            continue;
        }
        else {
            OUTPUT[new_size] = BUFF[i];
            ++new_size;
        }
    }

    return new_size;
}

/// self explanatory
static int shrink(const int read_count, const char* set1, const char* set2) {
    if (set2 == nullptr) {
        return shrink_all(read_count, set1);
    }
    else {
        transform(read_count, set1, set2);
        strcpy(BUFF, OUTPUT);
        return shrink_all(read_count, set2);
    }
}

/// replaces all repetitions of characters that are NOT IN set
static int shrink_compl_all(const int read_count, const char* set) {
    OUTPUT[0] = BUFF[0];

    int new_size = 1;
    int pos;
    for(int i = 1; i < read_count; ++i) {
        pos = get_position(BUFF[i], set);
        if(-1 == pos && BUFF[i - 1] == BUFF[i]) {
            continue;
        }
        else {
            OUTPUT[new_size] = BUFF[i];
            ++new_size;
        }
    }

    return new_size;
}

/// self explanatory
static int shrink_compl(const int read_count, const char* set1, const char* set2) {
    if (set2 == nullptr) {
        return shrink_compl_all(read_count, set1);
    }
    else {
        transform_complementary(read_count, set1, set2);
        strcpy(BUFF, OUTPUT);
        return shrink_all(read_count, set2);
    }
}

/// self explanatory
static int shrink_delete(const int read_count, const char* set1, const char* set2) {
    const int new_size = delete(read_count, set1);
    strcpy(BUFF, OUTPUT);
    return shrink_all(new_size, set2);
}

/// self explanatory
static int shrink_delete_compl(const int read_count, const char* set1, const char* set2) {
    const int new_size = delete_compl(read_count, set1);
    strcpy(BUFF, OUTPUT);
    return shrink_all(new_size, set2);
}

/**
 * Used to define the operation which is to be executed
 * based on the provided options and sets
 */
static void start_tr(const int op, struct Sets *sets) {
    Operation operation;

    /// get the operation
    switch(op) {
        case OP_CLN: operation = transform; break;
        case OP_XXC: operation = transform_complementary; break;
        case OP_XDX: operation = delete; break;
        case OP_XDC: operation = delete_compl; break;
        case OP_SXX: operation = shrink; break;
        case OP_SXC: operation = shrink_compl; break;
        case OP_SDX: operation = shrink_delete; break;
        case OP_SDC: operation = shrink_delete_compl; break;
    }

    int read_count;
    int modified_size = 0;
    while(-1 != (read_count = read(STDIN_FILENO, BUFF, BUFSIZ))) {

        /// keep the size of the modified output
        modified_size = operation(read_count, sets->set1, sets->set2);

        /// print the output
        write(STDOUT_FILENO, OUTPUT, modified_size);

        /// reset the size
        modified_size = 0;
	}
}

#endif /// __FUNCTIONS_H__
