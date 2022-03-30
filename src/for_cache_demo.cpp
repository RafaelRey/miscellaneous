#include <iostream>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <string>
#include <cmath>


//Comment this to use C array instead of std vector
//#define USE_C_ARRAY 

int test(int array_size, int step, int tries) {

	int total_time = 0;
	for (int tr = 0; tr < tries; tr++) {

#if defined(USE_C_ARRAY)
		int* arr = new int[array_size];
#else 
		std::vector<int> arr(array_size);
#endif

		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < array_size; i += step) arr[i]++;

		total_time += std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::high_resolution_clock::now() - start)).count();

#if defined(USE_C_ARRAY)
		delete[] arr;
#endif
	}
	return total_time/tries;
}
int main(int argc, char** argv) {

	if (argc < 4)
		return EXIT_FAILURE;
	//First arg Size in MB
	//Second arg Step 
	int size, k, tries;
	try
	{
		size  = std::stoi(std::string(argv[1])) * 1024 * 1024;
		k     = std::stoi(std::string(argv[2]));
		tries = std::stoi(std::string(argv[3]));
	}
	catch (const std::exception&)
	{
		std::cout << "Bad arguments. Usage ./program SIZE STEP NUM_TRIES arguments should be integers" << std::endl;
		return EXIT_FAILURE;
	}
	/*
	
	std::cout << "Step:           " << k << " Elements \n";
	std::cout << "Array Elements: " << size << "\n";
	std::cout << "Array Size:     " << size/(1024*1024) << " MBs \n";
	std::cout << "Int Size:       " << sizeof(int) << "\n";
	std::cout << "[" << k <<" Step]: " << test(size, k) << " microsecs\n" << std::endl;
	*/
	std::cout << "Testing with size " << size << " and step " << k << " for " << tries << " tries: " << test(size, k, tries) << " ms" << "\n";
	std::cout << "Accesing same number of elements (contiguous): " << test(std::floor(size/k), 1, tries) << " ms" << std::endl;
	return EXIT_SUCCESS;
}