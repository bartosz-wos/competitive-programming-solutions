#include <iostream>
#include <cstdint>
#include <cmath>
#include <print>

int main(){
	uint32_t n, m;
	std::cin >> n >> m;

	const double inv_m{ 1.0 / m }; 
	double cumsum{};

	for(uint32_t k{ m - 1 }; k >= 1; --k){
		double term = std::pow(k * inv_m, n);
		if(term < 1e-16){
			break;
		}
		cumsum += term;
	}

	std::println("{:.7f}", m - cumsum);
	return 0;
}
