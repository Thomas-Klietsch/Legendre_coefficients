
#include "./legendre.hpp"

int main()
{
	std::cout << "Legendre polynomials of the first kind.\n";
	for (std::uint8_t N{ 0 };N <= 13;++N)
		Legendre::Coefficients(N);

	std::cout << "Reference:\n";
	std::cout << "P(13,x) = 1/1024 ( 1300075 x^13 - 4056234 x^11 + 4849845 x^9 - 2771340 x^7 + 765765 x^5 - 90090 x^3 + 3003 x )\n";

	std::cout << "\nShifted Legendre polynomials.\n";
	for (std::uint8_t N{ 0 };N <= 5;++N)
		Legendre::ShiftedCoefficients(N);
	std::cout << "Reference:\n";
	std::cout << "/P(5,x) = 252 x^5 - 630 x^4 + 560 x^3 - 210 x^2 + 30 x - 1\n";
};
