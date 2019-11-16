#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <array>
#include <map>



std::default_random_engine createRandomEngine()
{
	auto seed = static_cast<unsigned long>(std::time(nullptr));
	return std::default_random_engine(seed);
}

auto RandomEngine = createRandomEngine();

int randomInt(int min, int max)
{
	std::uniform_int_distribution<> distr(min, max);
	return distr(RandomEngine);
}


std::string convertNumberToString(int number)
{
	std::ostringstream ostream;
	ostream << number;
	return ostream.str();
}

void computeBestPosition(const int roofSize)
{
	std::vector<int> roof{ roofSize * roofSize, 0 }; //the roof where the solar panel is supposed to go
	roof.resize(roofSize * roofSize);

	for (int i = 0; i < roofSize; ++i)
	{
		for (int j = 0; j < roofSize; ++j)
		{
			roof[j + i * roofSize] = randomInt(0, 9);
			std::cout << roof[j + i * roofSize] << ", ";
		}
		std::cout << std::endl;
	}

	const int panelSize = roofSize / 2;
	std::vector<int> panelsSums{ (roofSize - 1) * (roofSize - 1), 0 };
	panelsSums.resize((roofSize - 1) * (roofSize - 1));
	int maxSum = -1;
	int winningCol = -1;
	int winningRow = -1;


	unsigned int panelSum = 0;
	int panelSizeBuffer = panelSize;

	for (int row = 0; row < roofSize; ++row)
	{
		for (int col = 0; col < roofSize + panelSize / 2; ++col)
		{
			if (col > panelSize - 1)
			{

				if (row > 0 && row < roofSize - 1)
				{
					int colIndex = col - panelSize;

					panelsSums[colIndex + (row - 1) * (roofSize - 1)] += panelSum;
					panelsSums[colIndex + row * (roofSize - 1)] += panelSum;

					panelSum -= roof[col - panelSize + row * roofSize];

					if (panelsSums[col - panelSize + row * (roofSize - 1)] >= maxSum)
					{
						maxSum = panelsSums[col - panelSize + row * (roofSize - 1)];
						winningCol = colIndex;
						winningRow = row;
					}
					if (panelsSums[col - panelSize + (row - 1) * (roofSize - 1)] >= maxSum)
					{
						maxSum = panelsSums[col - panelSize + (row - 1) * (roofSize - 1)];
						winningCol = colIndex;
						winningRow = row - 1;
					}

				}
				else
				{
					int rowIndex = row;
					if (row == roofSize - 1)
						rowIndex = row - 1;

					panelsSums[col - panelSize + rowIndex * (roofSize - 1)] += panelSum;
					panelSum -= roof[col - panelSize + row * roofSize];

					if (panelsSums[col - panelSize + rowIndex * (roofSize - 1)] >= maxSum)
					{
						maxSum = panelsSums[col - panelSize + rowIndex * (roofSize - 1)];
						winningCol = col - panelSize;
						winningRow = rowIndex;
					}
				}

			}

			if (col < roofSize)
				panelSum += roof[col + row * roofSize];

		}

		panelSum = 0;
	}


	for (int i = 0; i < roofSize - 1; ++i)
	{
		for (int j = 0; j < roofSize - 1; ++j)
		{
			std::cout << "(" << i << ", " << j << ") " << panelsSums[j + (roofSize - 1) * i] << ", ";
		}
		std::cout << std::endl;
	}

	std::cout << "max sum : " << maxSum << " (" << winningRow << ", " << winningCol << ")" << std::endl;
}

int main() {
	
	int roofSize = 4;
	while (roofSize > 3)
	{
		std::cout << "type a number to start : ";
		std::cin >> roofSize;
		std::cout << "\n\n";
		
		computeBestPosition(roofSize);

		std::cout << "\n";
	}
	return 0;
}
