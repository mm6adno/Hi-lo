#include <iostream>
#include <cstdlib>
#include <ctime>

//генерация псевдослучайного числа
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);

}

//функция определяет: вводимое число > < = сгенерированного
int moreLessCorrect(int random, int attempts, int x, int y)
{
	int count{ 1 };
	while (true)
	{
		int input;
		if (count <= attempts)
		{
			while (count <= attempts)
			{
				std::cout << "Guess #" << count << ": ";
				std::cin >> input;
				if ((input >= x && input <= y))

					++count;

				//отброс неверного ввода
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32767, '\n');
				}

				if (input > random)
				{
					std::cout << "Your guess is too high.\n";
				}
				if (input < random)
				{
					std::cout << "Your guess is too low.\n";
				}
				if (input == random)
				{
					std::cout << "Correct! You win!\n";
					return 0;
				}
			}
		}
		else
		{
			std::cout << "Sorry, you lose. The correct number was " << random << ".\n";
			return 0;
		}
		
	}
}

//настройка значения, от которого действует диапазон
int xSettings()
{
	int x;
	while (true)
	{
		std::cout << "Enter x: ";
		std::cin >> x;

		//отброс неверного ввода
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}

		else
			return x;
	}
}

//настройка значения, до которого действует диапазон
int ySettings()
{
	int y;
	while (true)
	{
		std::cout << "Enter y: ";
		std::cin >> y;

		//отброс неверного ввода
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}

		else
			return y;
	}
}

//настройка количества попыток
int attemptsSettings()
{
	int attempts;
	while (true)
	{
		std::cout << "Enter attempts: ";
		std::cin >> attempts;

		//отброс неверного ввода
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}

		else
			return attempts;
	}
}

int main()
{
	int x{ 1 };
	int y{ 100 };
	int attempts{ 7 };
	bool w{ false };
settings:		//сюда приводит goto
	char set;

	//блок настроек, вызываемый при w == true
	while (w == true)	
	{
		std::cout << "What setting you need: \n---Between x(" << x << ") and y(" << y << ") -- enter \"r\" \n---Number of attempts(" << attempts << ") -- enter \"a\"\nSettings will be reset after restart the program. \n" <<
			"Enter \"b\" to back. ";
		std::cin >> set;
		if (set == 'r')
		{
			x = xSettings();
			y = ySettings();
		}
		else if (set == 'a')
		{
			attempts = attemptsSettings();
		}
		else if (set == 'b')
		{
			w = false;
			break;
		}
		else if (set != 'b' && set != 'a' && set != 'r')
		{
			std::cout << "You not entered \"a\", \"r\" or \"b\". Enter again. ";
		}
	}

	while (true)
	{

		std::cout << "Let's play a game. I'm thinking of number. You have " << attempts << " tries to guess what it is.\nEnter \"g\" to play. \nEnter \"s\" to settings. ";

		while (true)
		{


			char choice;
			std::cin >> choice;
			if (choice == 's')
			{
				w = true;
				goto settings;	//здесь я был вынужден использовать goto, ибо сделать так, чтобы из функции settings() возвращалось несколько значений и они сохранялись в main я не смог или еще не умею
			}
			else if (choice != 'g' && choice != 's' && choice != 'c')
			{
				std::cout << "You not entered \"g\", \"s\" or \"c\". ";
			}
			else if (choice == 'g')
			{
				break;
			}
			else if (choice == 'c')
			{
				std::cout << "Hi-lo+ ver. 1.0.1 \\created by mm6adno. ";
			}

		}



		srand(static_cast<unsigned int>(time(0)));
		int r{ rand() };
		r = 0;
		int gr{ getRandomNumber(x, y) };
		moreLessCorrect(gr, attempts, x, y);

		std::cout << "Would you like to play again (y/n)? ";
		char z;
		bool ww{ true };
		while (ww == true)
		{
			std::cin >> z;
			if (z == 'n')
			{
				std::cout << "Thank you for playing.";

				//не выключает консоль автоматически
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				std::cin.get();

				return 0;
			}
			else if (z == 'y')
			{
				ww = false;
			}
			else if (z != 'n' && z != 'y')
			{
				std::cout << "Please, enter y/n. ";

			}
		}
	}
}
