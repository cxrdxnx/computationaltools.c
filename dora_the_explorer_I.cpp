#include <cmath>
#include <iostream>
#include <utility>

using ll = long long int;

ll gauss_sum(ll n);
ll get_diagonal(ll steps);
std::pair<int, int> get_coordinates(ll steps);


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	ll steps{};

	while (std::cin >> steps && steps != 0)
	{
		auto coordinates{ get_coordinates(steps) };
		std::cout << coordinates.first << " " << coordinates.second << '\n';
	}
	
	return 0;
}

ll gauss_sum(ll n)
{
	return (n * (n + 1L)) / 2L;
}

ll get_diagonal(ll steps)
{
	ll diagonal_candidate = sqrt(2L * steps);

	ll sum_candidate = gauss_sum(diagonal_candidate);

	if (steps <= sum_candidate)
		return diagonal_candidate;
	else
		return ++diagonal_candidate;
}

std::pair<int, int> get_coordinates(ll steps)
{
	ll diagonal = get_diagonal(steps);
	
	// Calculate the steps inside the diagonal by substracting the total steps up to the previous diagonal.
	ll steps_inside_diagonal = steps - gauss_sum(diagonal - 1);

	if (diagonal % 2 == 0)
		// Coordinate pattern for even diagonals.
		return std::pair<int, int>(steps_inside_diagonal, diagonal - steps_inside_diagonal + 1);
	
	// Coordinate pattern for odd diagonals.
	return std::pair<int, int>(diagonal - steps_inside_diagonal + 1, steps_inside_diagonal);
}


