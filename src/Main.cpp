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

	const int columns = 3;
	const int rows = 3;
	int gameScore = 0;
	double level = 1;
	bool startGame = true;
	bool pressed = false;
	bool correct = false;
	bool wrong = false;
	bool term = false;
	bool missedTime = false;
	bool gameOver = false;

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

	sf::RenderWindow window(sf::VideoMode(1000, 600), "Monkey Game");
	sf::RectangleShape grid[columns][rows];

	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::White);

	sf::Texture shapeTexture;
	shapeTexture.loadFromFile("images/butterfly.png");
	shape.setTexture(&shapeTexture);

	int random_x = rand() % 3;
	int random_y = rand() % 3;
	int wrong_x = 0;
	int wrong_y = 0;
	int missedTime_x = 0;
	int missedTime_y = 0;

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

		if (startGame)
		{
			restartText.setString("Press Anywhere to Start");
			restartText.setPosition(350, 250);
			window.draw(restartText);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed)
			{
				startGame = false;
				pressed = true;
				term = true;
				clock.restart();
			}
		}
		else if (!gameOver)
		{
			sf::Vector2f cellSize(200.0f, 200.0f);

			sf::Time elapsed = clock.getElapsedTime();
			if (elapsed.asSeconds() > (2 / level) && !term)
			{
				if (!pressed)
				{
					gameOver = true;
					pressed = true;
					clock.restart();
				}
				random_x = rand() % 3;
				random_y = rand() % 3;
				clock.restart();
				pressed = false;
				correct = false;
				wrong = false;
				term = true;
			}

			int cur_pos_x = random_x * cellSize.x + 2.0f;
			int cur_pos_y = random_y * cellSize.y + 2.0f;

			for (int i = 0; i < columns; i++)
			{
				for (int j = 0; j < rows; j++)
				{
					grid[i][j].setSize(cellSize);
					grid[i][j].setOutlineColor(sf::Color::Black);
					grid[i][j].setOutlineThickness(2.0f);

					grid[i][j].setPosition(i * cellSize.x + 2.0f, j * cellSize.y + 2.0f);

					window.draw(grid[i][j]);
				}
			}

			if (correct)
			{
				grid[random_x][random_y].setOutlineColor(sf::Color::Green);
				grid[random_x][random_y].setOutlineThickness(4.0f);
				window.draw(grid[random_x][random_y]);
			}
			else if (missedTime)
			{
				grid[missedTime_x][missedTime_y].setOutlineColor(sf::Color::Red);
				grid[missedTime_x][missedTime_y].setOutlineThickness(4.0f);
				window.draw(grid[missedTime_x][missedTime_y]);
			}

			if (wrong)
			{
				grid[wrong_x][wrong_y].setOutlineColor(sf::Color::Red);
				grid[wrong_x][wrong_y].setOutlineThickness(4.0f);
				window.draw(grid[wrong_x][wrong_y]);
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !term)
			{
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				if (localPosition.x < 600)
				{
					if (localPosition.x > cur_pos_x && localPosition.x < (cur_pos_x + 200) && localPosition.y > cur_pos_y && localPosition.y < (cur_pos_y + 200) && !pressed)
					{
						gameScore = gameScore + 1;
						level = level + 0.1;
						pressed = true;
						correct = true;
					}
					else if (!pressed)
					{
						gameOver = true;
						pressed = true;
						clock.restart();
					}
				}
			}

			text.setPosition(700, 200);
			window.draw(text);

			if (!term)
			{
				shape.setSize(cellSize);
				shape.setPosition(cur_pos_x, cur_pos_y);

				window.draw(shape);
			}
			else
			{
				sf::Time elapsed2 = clock.getElapsedTime();
				if (elapsed2.asSeconds() > 1)
				{
					clock.restart();
					term = false;
					missedTime = false;
					pressed = false;
				}
			}
			if (gameScore < 0)
			{
				gameOver = true;
				clock.restart();
			}

			score.setString(to_string(gameScore));
			score.setPosition(800, 200);
			window.draw(score);
		}
		else
		{
			gameOverText.setString("Game Over");
			gameOverText.setPosition(430, 200);
			window.draw(gameOverText);

			text.setPosition(430, 280);
			window.draw(text);

			score.setString(to_string(gameScore));
			score.setPosition(550, 280);
			window.draw(score);

			restartText.setString("Press Anywhere to Start Again");
			restartText.setPosition(330, 350);
			window.draw(restartText);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed)
			{
				gameScore = 0;
				gameOver = false;
				pressed = true;
				correct = false;
				wrong = false;
				term = true;
				missedTime = false;
				level = 1;
				clock.restart();
			}

			sf::Time elapsed3 = clock.getElapsedTime();
			if (elapsed3.asSeconds() > 0.5 && pressed)
			{
				pressed = false;
			}
		}

		window.display();
	}

	return 0;
}
