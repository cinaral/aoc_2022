#include <cstdio>
#include <cstdlib>
#include <vector>

constexpr char default_file[] = "input.txt";
constexpr size_t default_sizeof_toplist = 3;
constexpr size_t sizeof_line = 32;

int
main(int argc, char *argv[])
{
	//* open the file
	printf("Usage: main [input (Default: \"%s\")] [n]\n", default_file);
	FILE *const input_file = fopen(argc > 1 ? argv[1] : default_file, "r");

	if (input_file != NULL) {
		printf("Opened %s\n", argc > 1 ? argv[1] : default_file);
	} else {
		perror("Error opening file");
	}
	size_t sizeof_toplist = argc > 2 ? atoi(argv[2]) : default_sizeof_toplist;

	//* read the file
	size_t i = 0;
	std::vector<int> list;
	std::vector<size_t> elf_idx;
	char line[sizeof_line];

	while (fgets(line, sizeof_line, input_file) != NULL) {
		if (line[0] != '\n') {
			++i;
			static int d;
			sscanf(line, "%d", &d);
			list.push_back(d);
		} else {
			elf_idx.push_back(i);
		}
	}
	elf_idx.push_back(i);
	const size_t list_size = i;
	const size_t elf_count = elf_idx.size() - 1; //* -1 because of the last
	size_t *const elf_load = new size_t[elf_count];
	sizeof_toplist = sizeof_toplist > elf_count ? elf_count : sizeof_toplist;

	for (size_t i = 0; i < elf_count; ++i) {
		elf_load[i] = 0;

		for (size_t j = elf_idx[i]; j < elf_idx[i + 1]; ++j) {
			elf_load[i] += list[j];
		}
	}
	printf("%d values, %d elves\n", list_size, elf_count);

	//* process

	size_t *const toplist = new size_t[sizeof_toplist];
	toplist[0] = 0;

	for (size_t i = 0; i < elf_count; ++i) {
		for (size_t j = 0; j < sizeof_toplist; ++j) {
			if (elf_load[i] > toplist[j]) {
				for (size_t k = sizeof_toplist - 1; k > j; --k) {
					toplist[k] = toplist[k - 1];
				}
				toplist[j] = elf_load[i];
				break;
			}
		}
	}
	printf("Top %d: ", sizeof_toplist);
	size_t toplist_sum = 0;

	for (size_t i = 0; i < sizeof_toplist; ++i) {
		toplist_sum += toplist[i];
		printf("%d ", toplist[i]);
	}
	printf("\nSum: %d\n", toplist_sum);

	//* close the file
	if (fclose(input_file) != 0) {
		perror("Error closing file");
	}
	return 0;
}