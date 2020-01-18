#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "macroses.h"
#include "globals.h"

#include "parsers.h"
#include "helpers.h"
#include "functions.h"

/**
 * Gets the corresponding set-validator and runs it
 */
static const int run_set_validator(const int op, struct Sets *sets) {
    Validator validator = op_set_validator(op);
    if (nullptr == validator) {
        perror_exit();
    }

    return validator(sets);
}

int main(int argc, const char *const *argv){

    /// init defaults
	struct Options options = Options_default;
	struct Sets sets = Sets_default;

	/// parse the options and sets
	if(-1 == parse_args(argc - 1, argv + 1, &options, &sets)){
		perror_exit();
	}

    /// the representation of options of the command is a binary number
    const int op = get_bin_options(&options);

    /// check the if the number of sets is correct for the command
    if (-1 == run_set_validator(op, &sets)) {
        perror_exit();
    }

    /// we can start the command `tr`
    start_tr(op, &sets);

    /// finally exit
	exit(EXIT_SUCCESS);
}
