#include "read_file.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
// #include <numeric>
#include <map>
#include <queue>
#include <string>
#include <vector>

constexpr char default_file[] = "day7/input2.txt";
constexpr size_t line_buf_size = 256; //* max line length
constexpr size_t val_base = 10;       //* try 16 for hex
// constexpr size_t cmd_size = 3;        //* including the space after
constexpr size_t dir_shift = 2;
constexpr unsigned max_dir_size = 100000;
constexpr unsigned total_disk_space = 70000000;
constexpr unsigned des_free_space = 30000000;

struct Dir {
	size_t size = 0;
	size_t total_size = 0;
	std::map<std::string, Dir *> children;
	Dir *parent = nullptr;
};

// size_t
// get_children_size(Dir *dir)
//{
//	size_t children_size = dir.size;

//	for (auto const &c : dir->children) {
//		children_size += get_children_size(c.second);
//	}
//	return children_size;
//}

void
set_total_size(Dir *dir)
{
	dir->total_size = dir->size;

	for (auto const &c : dir->children) {
		set_total_size(c.second);
		dir->total_size += c.second->total_size;
	}
}

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

	Dir *cur_dir = nullptr;

	// std::map<std::string, Dir *> dirs;

	for (size_t i_grp = 0; i_grp < grp_end_idx.size(); ++i_grp) {
		//* iterate over groups...
		const auto grp_start_idx = i_grp == 0 ? 0 : grp_end_idx[i_grp - 1];
		std::vector<size_t> vals_dir;
		printf("Group %zu:\n", i_grp);
		Dir root_dir;
		std::vector<Dir *> flat_dir;

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

			if (str[2] == 'c' && str[3] == 'd') {

				if (str[5] == '.' && str[6] == '.') {
					if (cur_dir->parent != nullptr) {
						cur_dir = cur_dir->parent;
					}
					// cur_dir = cur_dir->parent;
				} else if (str[5] == '/') {
					cur_dir = &root_dir;
				} else {
					std::string dir_str;

					for (size_t i = 5; i < col_size; ++i) {
						dir_str.push_back(str[i]);
					}

					if (cur_dir->children.count(dir_str) < 1) {
						cur_dir->children[dir_str] = new Dir;
						cur_dir->children[dir_str]->parent = cur_dir;
						flat_dir.push_back(cur_dir->children[dir_str]);
					}
					cur_dir = cur_dir->children[dir_str];
				}
			}

			if (str[0] != '$' && str[0] != 'd') {
				//* convert to val if needed
				const size_t val =
				    strtoull(str, NULL, val_base); //* strtoull or similar
				cur_dir->size += val;
				// printf("%-32s [%zu]=%llu\n", str, j_row, val);
			}
		}
		set_total_size(&root_dir);
		printf("Size of /: %llu\n", root_dir.total_size);

		int free_space_margin =
		    static_cast<int>(total_disk_space) - root_dir.total_size - des_free_space;

		size_t sum = 0;
		Dir *sel_for_del = &root_dir;

		for (auto const &c : flat_dir) {
			set_total_size(c);

			if (c->total_size <= max_dir_size) {
				sum += c->total_size;
			}

			if (free_space_margin < 0 &&
			    c->total_size >= static_cast<size_t>(-free_space_margin) &&
			    c->total_size < sel_for_del->total_size) {
				sel_for_del = c;
			}
		}
		// printf("%zu\n", sum);
		printf("Deleting %zu\n", sel_for_del->total_size);
	}
	printf("\n");

	//* close the file
	if (fclose(input_file) != 0) {
		perror("Error closing file");
	}
	return 0;
}
