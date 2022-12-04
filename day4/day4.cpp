#include <cstdio>
#include <cstdlib>
#include <vector>

constexpr char default_file[] = "day4/input.txt";
constexpr size_t line_buf_size = 64;

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
	char line_buf[line_buf_size];
	size_t line_counter = 0;
	std::vector<std::vector<char>> line_arr;
	std::vector<size_t> line_len_arr;
	std::vector<size_t> grp_end_idx;

	while (fgets(line_buf, line_buf_size, input_file) != NULL) {
		std::vector<char> lines;

		for (size_t j = 0; j < line_buf_size; ++j) {
			if (line_buf[j] == '\n' || line_buf[j] == '\0') {
				if (j > 0) { //* if line is not empty
					++line_counter;
					line_arr.push_back(lines);
					line_len_arr.push_back(j);
				} else {
					grp_end_idx.push_back(line_counter);
				}
				break;
			}
			lines.push_back(line_buf[j]);
		}
	}
	grp_end_idx.push_back(line_counter);
	const size_t grup_count = grp_end_idx.size();
	const size_t line_count = line_counter;
	printf("Read %zu lines in %zu groups\n", line_count, grup_count);

	//* parse the lines and groups
	size_t a_counter = 0;
	size_t b_counter = 0;

	for (size_t i = 0; i < grp_end_idx.size(); ++i) {
		//* iterate over groups...
		// printf("Group %zu: ", i);
		const size_t grp_start_idx = i == 0 ? 0 : grp_end_idx[i - 1];

		for (size_t j = grp_start_idx; j < grp_end_idx[i]; ++j) {
			//* iterate over lines in group...
			// printf("[%zu]", j);
			const size_t line_len = line_len_arr[j];
			char str[line_buf_size];

			for (size_t k = 0; k < line_len; ++k) {
				//* iterate over characters in line...
				// printf("%c", line_arr[j][k]);
				str[k] = line_arr[j][k];
			}
			str[line_len] = '\0'; //* null termination
			// printf("%s", str);

			static size_t r1, r2, r3, r4;
			sscanf(str, "%zu-%zu,%zu-%zu", &r1, &r2, &r3, &r4);

			if ((r1 <= r3 && r2 >= r4) || (r1 >= r3 && r2 <= r4)) {
				++a_counter;
				// printf("%zu-%zu,%zu-%zu\n", r1, r2, r3, r4);
			}

			if (r2 >= r3 && r1 <= r4) {
				++b_counter;
				// printf("%zu-%zu,%zu-%zu\n", r1, r2, r3, r4);
			}
		}
		printf("\n");
	}
	printf("a %zu, b %zu\n", a_counter, b_counter);

	//* close the file
	if (fclose(input_file) != 0) {
		perror("Error closing file");
	}
	return 0;
}