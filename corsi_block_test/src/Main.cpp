#include "Platform/Platform.hpp"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Game Initialized!" << std::endl;
#endif

	const int easyColumns = 3;
	const int easyRows = 3;
	const int mediumColumns = 4;
	const int mediumRows = 4;
	const int hardColumns = 5;
	const int hardRows = 5;
	float sizeCell;
	int gameScore = 0;
	string gameType = "";
	bool gameChosen = false;

	sf::Font font;
	font.loadFromFile("fonts/Lato-Regular.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("Score:");
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);

	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(30);
	score.setStyle(sf::Text::Bold);
	score.setFillColor(sf::Color::White);

	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(30);
	gameOverText.setStyle(sf::Text::Bold);
	gameOverText.setFillColor(sf::Color::White);

	sf::Text restartText;
	restartText.setFont(font);
	restartText.setCharacterSize(25);
	restartText.setStyle(sf::Text::Bold);
	restartText.setFillColor(sf::Color::White);

	sf::RenderWindow window(sf::VideoMode(1000, 600), "Corsi Block Test");

	sf::RectangleShape easyBox;
	sf::RectangleShape mediumBox;
	sf::RectangleShape hardBox;
	easyBox.setFillColor(sf::Color::White);
	mediumBox.setFillColor(sf::Color::White);
	hardBox.setFillColor(sf::Color::White);

	sf::Text easyText;
	sf::Text mediumText;
	sf::Text hardText;
	easyText.setFont(font);
	easyText.setCharacterSize(20);
	easyText.setStyle(sf::Text::Bold);
	easyText.setFillColor(sf::Color::Black);
	mediumText.setFont(font);
	mediumText.setCharacterSize(20);
	mediumText.setStyle(sf::Text::Bold);
	mediumText.setFillColor(sf::Color::Black);
	hardText.setFont(font);
	hardText.setCharacterSize(20);
	hardText.setStyle(sf::Text::Bold);
	hardText.setFillColor(sf::Color::Black);

	int random_x;
	int random_y;
	bool startNewLevel = true;

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();

		if (!gameChosen)
		{
			restartText.setString("Please choose a difficulty level");
			restartText.setPosition(320, 250);
			window.draw(restartText);

			sf::Vector2f cellSize(100.0f, 50.0f);
			easyBox.setSize(cellSize);
			easyBox.setPosition(320, 300);
			window.draw(easyBox);
			mediumBox.setSize(cellSize);
			mediumBox.setPosition(450, 300);
			window.draw(mediumBox);
			hardBox.setSize(cellSize);
			hardBox.setPosition(580, 300);
			window.draw(hardBox);

			easyText.setString("EASY");
			easyText.setPosition(345, 312);
			window.draw(easyText);
			mediumText.setString("MEDIUM");
			mediumText.setPosition(455, 312);
			window.draw(mediumText);
			hardText.setString("HARD");
			hardText.setPosition(600, 312);
			window.draw(hardText);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				if (localPosition.x > 320 && localPosition.x < 420 && localPosition.y > 300 && localPosition.y < 350)
				{
					gameChosen = true;
					gameType = "easy";
					sizeCell = 200.0f;
				}
				else if (localPosition.x > 450 && localPosition.x < 550 && localPosition.y > 300 && localPosition.y < 350)
				{
					gameChosen = true;
					gameType = "medium";
					sizeCell = 150.0f;
				}
				else if (localPosition.x > 580 && localPosition.x < 680 && localPosition.y > 300 && localPosition.y < 350)
				{
					gameChosen = true;
					gameType = "hard";
					sizeCell = 120.0f;
				}
			}
		}
		else
		{
			sf::Vector2f cellSize(sizeCell, sizeCell);

			if (gameType == "easy")
			{
				sf::RectangleShape grid[easyColumns][easyRows];

				if (startNewLevel)
				{
					random_x = rand() % 3;
					random_y = rand() % 3;

					startNewLevel = false;
				}

				for (int i = 0; i < easyColumns; i++)
				{
					for (int j = 0; j < easyRows; j++)
					{
						grid[i][j].setSize(cellSize);
						grid[i][j].setOutlineColor(sf::Color::Black);
						grid[i][j].setOutlineThickness(2.0f);

						grid[i][j].setPosition(i * cellSize.x + 2.0f, j * cellSize.y + 2.0f);

						window.draw(grid[i][j]);
					}
				}

				grid[random_x][random_y].setFillColor(sf::Color::Red);
				window.draw(grid[random_x][random_y]);
			}
			else if (gameType == "medium")
			{
				sf::RectangleShape grid[mediumColumns][mediumRows];

				if (startNewLevel)
				{
					random_x = rand() % 4;
					random_y = rand() % 4;

					startNewLevel = false;
				}

				for (int i = 0; i < mediumColumns; i++)
				{
					for (int j = 0; j < mediumRows; j++)
					{
						grid[i][j].setSize(cellSize);
						grid[i][j].setOutlineColor(sf::Color::Black);
						grid[i][j].setOutlineThickness(2.0f);

						grid[i][j].setPosition(i * cellSize.x + 2.0f, j * cellSize.y + 2.0f);

						window.draw(grid[i][j]);
					}
				}

				grid[random_x][random_y].setFillColor(sf::Color::Red);
				window.draw(grid[random_x][random_y]);
			}
			else if (gameType == "hard")
			{
				sf::RectangleShape grid[hardColumns][hardRows];

				if (startNewLevel)
				{
					random_x = rand() % 5;
					random_y = rand() % 5;

					startNewLevel = false;
				}

				for (int i = 0; i < hardColumns; i++)
				{
					for (int j = 0; j < hardRows; j++)
					{
						grid[i][j].setSize(cellSize);
						grid[i][j].setOutlineColor(sf::Color::Black);
						grid[i][j].setOutlineThickness(2.0f);

						grid[i][j].setPosition(i * cellSize.x + 2.0f, j * cellSize.y + 2.0f);

						window.draw(grid[i][j]);
					}
				}

				grid[random_x][random_y].setFillColor(sf::Color::Red);
				window.draw(grid[random_x][random_y]);
			}

			text.setPosition(700, 200);
			window.draw(text);

			score.setString(to_string(gameScore));
			score.setPosition(800, 200);
			window.draw(score);
		}

		window.display();
	}

	return 0;
}
