#include <algorithm>
#include <cstdio>
#include <vector>

constexpr char default_file[] = "day3/input.txt";
constexpr size_t sizeof_line = 64;
constexpr size_t item_types = 52;

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
	std::vector<std::vector<char>> left_pairs;
	std::vector<std::vector<char>> right_pairs;
	std::vector<size_t> pair_lengths;

	std::vector<char[sizeof_line / 2]> list2;
	char line[sizeof_line];

	while (fgets(line, sizeof_line, input_file) != NULL) {
		if (line[0] != '\n') {
			++i;

			// static char *s;
			static std::vector<char> left;
			static std::vector<char> right;

			left.clear();
			right.clear();
			// sscanf(line, "%s", s);

			size_t pair_length = 0;
			size_t j = 0;

			while (true && j < sizeof_line) {
				++j;

				if (line[j] == '\0') {
					pair_length = j - 1;
					break;
				}
			}

			for (size_t j = 0; j < pair_length; ++j) {
				if (j < pair_length / 2) {
					left.push_back(line[j]);
				} else {
					right.push_back(line[j]);
				}
			}
			left_pairs.push_back(left);
			right_pairs.push_back(right);
			pair_lengths.push_back(pair_length / 2);
		} else {
			//* empty line
		}
	}
	const size_t pair_count = i;

	//* process
	printf("---------------------------------\n");
	printf("%llu bag pairs\n", pair_count);
	printf("---------------------------------\n");

	// for (std::vector<char> i : left_pairs) {
	//	for (char j : i) {
	//		printf("%c", j);
	//	}
	//	printf(" | ");
	// }
	// printf("\n");

	// for (std::vector<char> i : right_pairs) {
	//	for (char j : i) {
	//		printf("%c", j);
	//	}
	//	printf(" | ");
	// }
	// printf("\n");

	unsigned total = 0;

	for (size_t i = 0; i < pair_count; i += 3) {
		bool freq[3][item_types];

		for (size_t j = 0; j < 3; ++j) {
			for (size_t k = 0; k < item_types; ++k) {
				freq[j][k] = false;
			}
		}

		for (size_t j = 0; j < 3; ++j) {
			for (size_t k = 0; k < pair_lengths[i + j]; ++k) {
				int left = static_cast<size_t>(left_pairs[i + j][k]);

				if (left - 97 > 0) {
					left = left - 97;
				} else {
					left = left - 65 + 26;
				}
				if (!freq[j][left]) {
					freq[j][left] = true;
				}

				int right = static_cast<size_t>(right_pairs[i + j][k]);

				if (right - 97 > 0) {
					right = right - 97;
				} else {
					right = right - 65 + 26;
				}
				if (!freq[j][right]) {
					freq[j][right] = true;
				}
			}
		}

		for (size_t i = 0; i < item_types; ++i) {
			if (freq[0][i] && freq[1][i] && freq[2][i]) {
				total += i + 1;
			}
		}
	}

	// for (size_t i = 0; i < pair_count; ++i) {
	//	bool left_freq[item_types];
	//	bool right_freq[item_types];

	//	for (size_t i = 0; i < item_types; ++i) {
	//		left_freq[i] = 0;
	//		right_freq[i] = 0;
	//	}

	//	for (size_t j = 0; j < pair_lengths[i]; ++j) {
	//		int left = static_cast<size_t>(left_pairs[i][j]);

	// if (left - 97 > 0) {
	//	left = left - 97;
	// } else {
	//	left = left - 65 + 26;
	// }
	// if (!left_freq[left]) {
	//	left_freq[left] = true;
	// }

	// int right = static_cast<size_t>(right_pairs[i][j]);

	// if (right - 97 > 0) {
	//	right = right - 97;
	// } else {
	//	right = right - 65 + 26;
	// }
	// if (!right_freq[right]) {
	//	right_freq[right] = true;
	// }
	//	}

	//	for (size_t i = 0; i < item_types; ++i) {
	//		if (left_freq[i] && right_freq[i]) {
	//			total += i + 1;
	//		}
	//	}
	//}

	printf("%u total\n", total);

	//* close the file
	if (fclose(input_file) != 0) {
		perror("Error closing file");
	}
	return 0;
}