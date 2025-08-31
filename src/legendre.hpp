// Copyright (c) 2025 Thomas Klietsch, all rights reserved.
//
// Licensed under the GNU Lesser General Public License, version 3.0 or later
//
// This program is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or ( at your option ) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General
// Public License along with this program.If not, see < https://www.gnu.org/licenses/>. 

#pragma once

#include <cstdint>
#include <vector>

#include "./mathematics/integer.hpp"

// Polynomials with a vector of coefficients
// starting at the lowest power at index zero
// For a 3th degree polynomial;
// a3 x^3 + a2 x^2 + a1 x^1 + a0
// The vector 'a' is {a0,a1,a2,a3}
namespace Polynomial
{

	// Polynomial to the N-th power
	std::vector<Integer> Power(
		std::vector<Integer> const& polynomial,
		std::uint8_t const N
	)
	{
		if (N == 0)
			return { 1 };

		std::uint64_t const k = polynomial.size();

		std::vector<Integer> result{ polynomial };

		// Power
		for (std::uint8_t n{ 1 }; n < N; ++n)
		{
			// Size of new polynomial.
			std::vector<Integer> temp(result.size() + k - 1, 0);

			// Multiply
			for (std::uint64_t j{ 0 }; j < result.size(); ++j)
				for (std::uint64_t i{ 0 }; i < k; ++i)
					temp[i + j] += result[j] * polynomial[i];

			std::swap(temp, result);
		}

		return result;
	};

	// N-th derivative of a polynomial
	// (d/dx)^N, d^N/(d^N x)
	std::vector<Integer> Derivative(
		std::vector<Integer> const& polynomial,
		std::uint8_t const N
	)
	{
		if (N == 0)
			return polynomial;
		if (N > polynomial.size())
			return{ 0 };

		std::vector<Integer> result{ polynomial };

		// d/dx to N-th power
		result.erase(std::begin(result), std::begin(result) + N);
		// Multiply elements with their exponents from (d/dx)^N
		for (std::uint64_t i{ 0 }; i < result.size(); ++i)
			result[i] *= FactorialFalling(N + i, N);
		return result;
	};

};

// Adrien-Marie Legendre (1752-1833)
// The Legendre polynomials, of the first kind.
namespace Legendre
{

	// Generates coefficients for Legendre polynomial P(N,x)
	// N larger than 13 are not supported with 64bit integers
	// Uses the Rodrigues Formula:
	//             1      d^n
	//	Pn(x) = ------ * ---- [ (x^2-1)^n ] , n E N0
	//          2^n n!   d^nx
	void Coefficients(
		std::uint8_t const& N
	)
	{
		// x^2-1
		std::vector<Integer> base_polynomial{ -1, 0, 1 };

		// (x^2-1)^n
		auto power = Polynomial::Power(base_polynomial, N);

		// d^n/d^nx (power)
		auto derivative = Polynomial::Derivative(power, N);

		// 2^n n!
		Integer factor = Pow2(N) * Factorial(N);

		Integer const gcd = GCD(factor, GCD(derivative));

		std::cout << "P(" << N + 0 << ",x) = ";

		std::int64_t const n_elements = static_cast<int16_t>(derivative.size()) - 1;

		Integer const prefix = factor / gcd;
		if (prefix != 1)
			std::cout << "1/" << prefix << " ( ";

		for (std::int64_t i{ n_elements }; i > -1; --i)
		{
			if (derivative[i] != 0)
			{
				Integer const value = abs(derivative[i]) / gcd;

				if (i != n_elements)
					std::cout << (derivative[i].is_positive() ? "+ " : "- ");
				if ((abs(value) != 1) || (i == 0))
					std::cout << value << " ";
				if (i > 1)
					std::cout << "x^" << i << " ";
				else if (i == 1)
					std::cout << "x ";
			}
		}
		if (prefix != 1)
			std::cout << ")";

		std::cout << "\n";
	};

	// Generates coefficients for shifted Legendre polynomial /P(N,x)
	// Uses the Rodrigues Formula:
	//           1     d^n
	//	Pn(x) = --- * ---- [ (x^2-x)^n ] , n E N0
	//           n!   d^nx
	void ShiftedCoefficients(
		std::uint8_t const& N
	)
	{
		// x^2-x
		std::vector<Integer> base_polynomial{ 0, -1, 1 };

		// (x^2-x)^n
		auto power = Polynomial::Power(base_polynomial, N);

		// d^n/d^nx (power)
		auto derivative = Polynomial::Derivative(power, N);

		// n!
		Integer factor = Factorial(N);

		Integer const gcd = GCD(factor, GCD(derivative));

		std::cout << "/P(" << N + 0 << ",x) = ";

		std::int64_t const n_elements = static_cast<int16_t>(derivative.size()) - 1;

		Integer const prefix = factor / gcd;
		if (prefix != 1)
			std::cout << "1/" << prefix << " ( ";

		for (std::int64_t i{ n_elements }; i > -1; --i)
		{
			if (derivative[i] != 0)
			{
				Integer const value = abs(derivative[i]) / gcd;

				if (i != n_elements)
					std::cout << (derivative[i].is_positive() ? "+ " : "- ");
				if ((abs(value) != 1) || (i == 0))
					std::cout << value << " ";
				if (i > 1)
					std::cout << "x^" << i << " ";
				else if (i == 1)
					std::cout << "x ";
			}
		}
		if (prefix != 1)
			std::cout << ")";

		std::cout << "\n";
	};

};
