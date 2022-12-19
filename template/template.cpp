#include "read_file.hpp"
#include <cstdio>
#include <cstdlib>
#include <vector>

constexpr char default_file[] = "template/input.txt";
constexpr size_t line_buf_size = 256; //* max line length
constexpr size_t val_base = 10; //* try 16 for hex
using Val_T = unsigned long long;

int
main(int argc, char *argv[])
{
	//* open and read the file
	printf("Usage: main [input (Default: \"%s\")]\n", default_file);
	FILE *const input_file = fopen(argc > 1 ? argv[1] : default_file, "r");

	if (input_file != NULL) {
		printf("Opened %s\n", argc > 1 ? argv[1] : default_file);
	} else {
		perror("Error opening file");
	}
	std::vector<std::vector<char>> rows;
	std::vector<size_t> col_sizes;
	std::vector<size_t> grp_end_idx;
	read_file<line_buf_size>(input_file, rows, col_sizes, grp_end_idx);

	//* parse the lines and groups
	std::vector<std::vector<Val_T>> vals_by_groups;

	for (size_t i_grp = 0; i_grp < grp_end_idx.size(); ++i_grp) {
		//* iterate over groups...
		const auto grp_start_idx = i_grp == 0 ? 0 : grp_end_idx[i_grp - 1];
		std::vector<Val_T> vals_row;
		printf("Group %zu:\n", i_grp);

		for (size_t j_row = grp_start_idx; j_row < grp_end_idx[i_grp]; ++j_row) {
			//* iterate over lines in group...
			const auto col_size = col_sizes[j_row];
			char str[line_buf_size];

			for (size_t k_col = 0; k_col < col_size; ++k_col) {
				//* iterate over characters in line...
				const char c = rows[j_row][k_col];
				str[k_col] = c;
			}
			//* add null termination char
			str[col_size] = '\0';
			//* convert to val if needed
			const Val_T val = strtoull(str, NULL, val_base); //* strtoull or similar
			vals_row.push_back(val);
			printf("%-32s [%zu]=%llu\n", str, j_row, val);
		}
		vals_by_groups.push_back(vals_row);
	}
	//* close the file
	if (fclose(input_file) != 0) {
		perror("Error closing file");
	}
	return 0;
}