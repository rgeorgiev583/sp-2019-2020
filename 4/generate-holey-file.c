// Употреба: generate-holey-file БРОЙ-ДУПКИ РАЗМЕР-НА-ДУПКА ФАЙЛ

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_FILE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

#define REQUIRED_ARG_COUNT 3
#define TEST_PATTERN "123456:890_HelloWorld\n"
#define TEST_PATTERN_LENGTH sizeof(TEST_PATTERN) - 1

int main(int argc, const char *const *argv)
{
	if (argc < REQUIRED_ARG_COUNT + 1)
		exit(EXIT_FAILURE);

	long hole_count = atol(argv[1]);
	if (hole_count < 0)
		exit(EXIT_FAILURE);

	long hole_size = atol(argv[2]);
	if (hole_size <= 0)
		exit(EXIT_FAILURE);

	int output_fileno = creat(argv[3], DEFAULT_FILE_MODE);
	if (-1 == output_fileno)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	for (long i = 0; i < hole_count; i++)
	{
		if (-1 == write(output_fileno, TEST_PATTERN, TEST_PATTERN_LENGTH))
		{
			perror("write");
			exit(EXIT_FAILURE);
		}

		if (-1 == lseek(output_fileno, hole_size, SEEK_CUR))
		{
			perror("lseek");
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}