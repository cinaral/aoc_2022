#include <cstdio>
#include <vector>

constexpr char default_file[] = "template/input.txt";
constexpr size_t sizeof_line = 32;

int
main(int argc, char *argv[])
{
	//* open the file
	printf("Usage: main [input (Default: \"%s\")]\n", default_file);
	FILE *const input_file = fopen(argc > 1 ? argv[1] : default_file, "r");

	if (input_file != NULL) {
		printf("Opened %s\n", argc > 1 ? argv[1] : default_file);
	} else {
		perror("Error opening file");
	}

	//* read the file
	size_t i = 0;
	std::vector<int> list;
	char line[sizeof_line];

	while (fgets(line, sizeof_line, input_file) != NULL) {
		if (line[0] != '\n') {
			++i;
			static int d;
			sscanf(line, "%d", &d);
			list.push_back(d);
		} else {
			//* empty line
		}
	}
	const size_t list_size = i;

	//* process
	printf("---------------------------------\n");
	printf("%llu values\n", list_size);
	printf("---------------------------------\n");

	for (size_t i = 0; i < list_size; ++i) {
		printf("%d ", list[i]);
	}
	printf("\n");

	//* close the file
	if (fclose(input_file) != 0) {
		perror("Error closing file");
	}
	return 0;
}