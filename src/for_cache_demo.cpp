#include <iostream>
#include <cstdlib>
#include <chrono>
#include <vector>

#define SIZE 64 * 1024 * 1024
#define K 16

int main() {

	std::vector<int> arr(SIZE);

	std::cout << "Step:           " << K << " Elements \n";
	std::cout << "Array Size:     " << SIZE/(1024*1024) << " MBs \n";
	std::cout << "Array Elements: " << arr.size() << "\n";
	std::cout << "Int Size:       " << sizeof(int) << "\n";

	auto show_duration = [&](auto title, auto duration){ 
		std::cout << "[" << title << "] Duration: " << 
			std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() <<
			" (milisecs) \n";
	};

	auto start = std::chrono::steady_clock::now();
	// Loop 1
	for (int i = 0; i < SIZE; i++) arr[i]++;
	show_duration("FullArray", 
				(std::chrono::steady_clock::now() - start));


	start = std::chrono::steady_clock::now();
	// Loop 1
	for (int i = 0; i < SIZE; i += K) arr[i]++;

	show_duration(std::string("Array Step ") + std::to_string(K), 
				(std::chrono::steady_clock::now() - start));


	return EXIT_SUCCESS;
}