#include <cstdio>
#include <cstdlib>
#include <vector>

constexpr char default_file[] = "template/input.txt";
constexpr size_t line_buf_size = 64;
using Val_T = int;

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
	std::vector<size_t> grup_end_idx;

	while (fgets(line_buf, line_buf_size, input_file) != NULL) {
		std::vector<char> lines;

		for (size_t j = 0; j < line_buf_size; ++j) {
			if (line_buf[j] == '\n') {
				if (j > 0) { //* if line is not empty
					++line_counter;
					line_arr.push_back(lines);
					line_len_arr.push_back(j);
				} else {
					grup_end_idx.push_back(line_counter);
				}
				break;
			}
			lines.push_back(line_buf[j]);
		}
	}
	grup_end_idx.push_back(line_counter);
	const size_t grup_count = grup_end_idx.size();
	const size_t line_count = line_counter;
	printf("Read %llu lines in %llu groups\n", line_count, grup_count);

	//* parse the lines and groups
	std::vector<std::vector<Val_T>> vals_in_grups;

	for (size_t i = 0; i < grup_end_idx.size(); ++i) {
		//* iterate over groups...
		printf("Group %llu: ", i);
		const size_t grp_start_idx = i == 0 ? 0 : grup_end_idx[i - 1];
		std::vector<Val_T> vals;

		for (size_t j = grp_start_idx; j < grup_end_idx[i]; ++j) {
			//* iterate over lines in group...
			printf("[%llu]", j);
			const size_t line_len = line_len_arr[j];
			char str[line_buf_size];

			for (size_t k = 0; k < line_len; ++k) {
				//* iterate over characters in line...
				// printf("%c", line_arr[j][k]);
				str[k] = line_arr[j][k];
			}
			str[line_len] = '\0'; //* null termination
			printf("%s", str);

			//* parse into values if needed
			const Val_T val = atoi(str);
			vals.push_back(val);
			printf("(%d)", val);
			printf(" ");
		}
		vals_in_grups.push_back(vals);
		printf("\n");
	}
	printf("\n");

	//* close the file
	if (fclose(input_file) != 0) {
		perror("Error closing file");
	}
	return 0;
}