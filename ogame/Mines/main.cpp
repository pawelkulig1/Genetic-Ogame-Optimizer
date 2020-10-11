#include <iostream>

#include "MetalMine2.h"
#include <chrono>


int main()
{
	constexpr uint64_t production = MetalMine::get_production(30);
	constexpr uint64_t production2 = CrystalMine::get_production(30);

	std::cout << "production " << production << " " << production2 << '\n';
}
