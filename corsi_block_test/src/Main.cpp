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
	bool showBox = true;
	int** rememberBox;
	int level = 1;
	int curShowLevel;
	int curPressLevel;
	bool pressed = false;
	int levelFinished = false;
	bool gameOver = false;
	int wrong_x;
	int wrong_y;
	bool pressed2 = false;
	bool realGameOver = false;

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

	sf::Text wrongBoxText;
	wrongBoxText.setFont(font);
	wrongBoxText.setCharacterSize(20);
	wrongBoxText.setStyle(sf::Text::Bold);
	wrongBoxText.setFillColor(sf::Color::Black);

	sf::Text startAgainText;
	startAgainText.setFont(font);
	startAgainText.setCharacterSize(30);
	startAgainText.setStyle(sf::Text::Bold);
	startAgainText.setFillColor(sf::Color::White);

	int random_x;
	int random_y;
	bool startNewLevel = true;
	bool startPressed = true;
	bool timeUpGameOver = false;

	sf::Clock clock;
	sf::Clock clock2;
	sf::Clock clock3;

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

			sf::Time startElapsed = clock.getElapsedTime();
			if (startElapsed.asSeconds() > 1)
			{
				startPressed = false;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !startPressed)
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
					level = 3;
				}
				else if (localPosition.x > 580 && localPosition.x < 680 && localPosition.y > 300 && localPosition.y < 350)
				{
					gameChosen = true;
					gameType = "hard";
					sizeCell = 120.0f;
					level = 5;
				}
			}
		}
		else if (!realGameOver)
		{
			sf::Vector2f cellSize(sizeCell, sizeCell);

			if (gameType == "easy")
			{
				sf::RectangleShape grid[easyColumns][easyRows];

				if (startNewLevel)
				{
					clock.restart();
					curShowLevel = 0;
					curPressLevel = 0;
					pressed = false;
					levelFinished = false;
					rememberBox = new int*[level];
					int temp = -1;
					bool notSame = false;
					for (int i = 0; i < level; i++)
					{
						notSame = false;
						while (!notSame)
						{
							random_x = rand() % 3;
							random_y = rand() % 3;
							if ((random_x + random_y) != temp)
							{
								notSame = true;
								temp = random_x + random_y;
							}
						}
						rememberBox[i] = new int[2];
						rememberBox[i][0] = random_x;
						rememberBox[i][1] = random_y;
					}
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

				if (showBox)
				{
					grid[rememberBox[curShowLevel][0]][rememberBox[curShowLevel][1]].setFillColor(sf::Color::Blue);
					window.draw(grid[rememberBox[curShowLevel][0]][rememberBox[curShowLevel][1]]);
				}
				else
				{
					sf::Time timeIsUp = clock3.getElapsedTime();
					if (timeIsUp.asSeconds() > 3 && !timeUpGameOver)
					{
						timeUpGameOver = true;
						clock.restart();
					}

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !gameOver)
					{
						sf::Vector2i localPosition = sf::Mouse::getPosition(window);
						int curX = rememberBox[curPressLevel][0] * cellSize.x + 2.0f;
						int curY = rememberBox[curPressLevel][1] * cellSize.y + 2.0f;

						if (localPosition.x < 600)
						{
							if (localPosition.x > curX && localPosition.x < (curX + cellSize.x) && localPosition.y > curY && localPosition.y < (curY + cellSize.y) && !pressed)
							{
								if (curPressLevel == (level - 1))
								{
									levelFinished = true;
									clock.restart();
									clock2.restart();
									pressed = true;
									pressed2 = true;
								}
								else
								{
									clock2.restart();
									clock3.restart();
									pressed2 = true;
									curPressLevel += 1;
								}
							}
							else if (!pressed2)
							{
								curPressLevel = 0;
								wrong_x = (localPosition.x - 2.0f) / cellSize.x;
								wrong_y = (localPosition.y - 2.0f) / cellSize.y;
								gameOver = true;
								clock.restart();
							}
						}
					}

					sf::Time elapsed3 = clock2.getElapsedTime();
					if (elapsed3.asSeconds() > 0.5 && pressed2)
					{
						pressed2 = false;
					}

					if (gameOver)
					{
						grid[wrong_x][wrong_y].setFillColor(sf::Color::Red);
						window.draw(grid[wrong_x][wrong_y]);
						wrongBoxText.setString("Wrong Box!");
						float textWidth = wrongBoxText.getLocalBounds().width;
						float textHeight = wrongBoxText.getLocalBounds().height;
						wrongBoxText.setPosition(((wrong_x * cellSize.x + 2.0f) + (cellSize.x / 2)) - textWidth / 2, ((wrong_y * cellSize.y + 2.0f) + (cellSize.y / 2)) - textHeight / 2);
						window.draw(wrongBoxText);
						sf::Time elapsed4 = clock.getElapsedTime();
						if (elapsed4.asSeconds() > 1.5)
						{
							realGameOver = true;
						}
					}

					if (timeUpGameOver)
					{
						grid[rememberBox[curPressLevel][0]][rememberBox[curPressLevel][1]].setFillColor(sf::Color::Red);
						window.draw(grid[rememberBox[curPressLevel][0]][rememberBox[curPressLevel][1]]);
						wrongBoxText.setString("Times Up!");
						float textWidth = wrongBoxText.getLocalBounds().width;
						float textHeight = wrongBoxText.getLocalBounds().height;
						wrongBoxText.setPosition(((rememberBox[curPressLevel][0] * cellSize.x + 2.0f) + (cellSize.x / 2)) - textWidth / 2, ((rememberBox[curPressLevel][1] * cellSize.y + 2.0f) + (cellSize.y / 2)) - textHeight / 2);
						window.draw(wrongBoxText);
						sf::Time elapsed4 = clock.getElapsedTime();
						if (elapsed4.asSeconds() > 1.5)
						{
							realGameOver = true;
						}
					}

					if (curPressLevel == (level - 1) && pressed)
					{
						grid[rememberBox[curPressLevel][0]][rememberBox[curPressLevel][1]].setFillColor(sf::Color::Green);
						window.draw(grid[rememberBox[curPressLevel][0]][rememberBox[curPressLevel][1]]);

						if (levelFinished)
						{
							sf::Time elapsed2 = clock.getElapsedTime();
							if (elapsed2.asSeconds() > 1)
							{
								for (int i = 0; i < level; i++)
								{
									delete[] rememberBox[i];
								}
								delete[] rememberBox;

								gameScore += 1;
								pressed = true;
								level += 1;
								startNewLevel = true;
								showBox = true;
							}
						}
					}
					else if (curPressLevel > 0)
					{
						grid[rememberBox[curPressLevel - 1][0]][rememberBox[curPressLevel - 1][1]].setFillColor(sf::Color::Green);
						window.draw(grid[rememberBox[curPressLevel - 1][0]][rememberBox[curPressLevel - 1][1]]);

						if (levelFinished)
						{
							sf::Time elapsed2 = clock.getElapsedTime();
							if (elapsed2.asSeconds() > 1)
							{
								for (int i = 0; i < level; i++)
								{
									delete[] rememberBox[i];
								}
								delete[] rememberBox;

								gameScore += 1;
								pressed = true;
								level += 1;
								startNewLevel = true;
								showBox = true;
							}
						}
					}
				}

				sf::Time elapsed = clock.getElapsedTime();
				if (elapsed.asSeconds() > 1)
				{
					if (curShowLevel < level - 1)
					{
						curShowLevel += 1;
						clock.restart();
					}
					else if (showBox)
					{
						showBox = false;
						clock3.restart();
					}
				}
			}
			else if (gameType == "medium")
			{
				sf::RectangleShape grid[mediumColumns][mediumRows];

				if (startNewLevel)
				{
					clock.restart();
					curShowLevel = 0;
					curPressLevel = 0;
					pressed = false;
					levelFinished = false;
					rememberBox = new int*[level];
					int temp = -1;
					bool notSame = false;
					for (int i = 0; i < level; i++)
					{
						notSame = false;
						while (!notSame)
						{
							random_x = rand() % 4;
							random_y = rand() % 4;
							if ((random_x + random_y) != temp)
							{
								notSame = true;
								temp = random_x + random_y;
							}
						}
						rememberBox[i] = new int[2];
						rememberBox[i][0] = random_x;
						rememberBox[i][1] = random_y;
					}
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

				if (showBox)
				{
					grid[rememberBox[curShowLevel][0]][rememberBox[curShowLevel][1]].setFillColor(sf::Color::Blue);
					window.draw(grid[rememberBox[curShowLevel][0]][rememberBox[curShowLevel][1]]);
				}
				else
				{
					sf::Time timeIsUp = clock3.getElapsedTime();
					if (timeIsUp.asSeconds() > 3 && !timeUpGameOver)
					{
						timeUpGameOver = true;
						clock.restart();
					}

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !gameOver)
					{
						sf::Vector2i localPosition = sf::Mouse::getPosition(window);
						int curX = rememberBox[curPressLevel][0] * cellSize.x + 2.0f;
						int curY = rememberBox[curPressLevel][1] * cellSize.y + 2.0f;

						if (localPosition.x < 600)
						{
							if (localPosition.x > curX && localPosition.x < (curX + cellSize.x) && localPosition.y > curY && localPosition.y < (curY + cellSize.y) && !pressed)
							{
								if (curPressLevel == (level - 1))
								{
									levelFinished = true;
									clock.restart();
									clock2.restart();
									pressed = true;
									pressed2 = true;
								}
								else
								{
									clock2.restart();
									clock3.restart();
									pressed2 = true;
									curPressLevel += 1;
								}
							}
							else if (!pressed2)
							{
								curPressLevel = 0;
								wrong_x = (localPosition.x - 2.0f) / cellSize.x;
								wrong_y = (localPosition.y - 2.0f) / cellSize.y;
								gameOver = true;
								clock.restart();
							}
						}
					}

					sf::Time elapsed3 = clock2.getElapsedTime();
					if (elapsed3.asSeconds() > 0.5 && pressed2)
					{
						pressed2 = false;
					}

					if (gameOver)
					{
						grid[wrong_x][wrong_y].setFillColor(sf::Color::Red);
						window.draw(grid[wrong_x][wrong_y]);
						wrongBoxText.setString("Wrong Box!");
						float textWidth = wrongBoxText.getLocalBounds().width;
						float textHeight = wrongBoxText.getLocalBounds().height;
						wrongBoxText.setPosition(((wrong_x * cellSize.x + 2.0f) + (cellSize.x / 2)) - textWidth / 2, ((wrong_y * cellSize.y + 2.0f) + (cellSize.y / 2)) - textHeight / 2);
						window.draw(wrongBoxText);
						sf::Time elapsed4 = clock.getElapsedTime();
						if (elapsed4.asSeconds() > 1.5)
						{
							realGameOver = true;
						}
					}

					if (timeUpGameOver)
					{
						grid[rememberBox[curPressLevel][0]][rememberBox[curPressLevel][1]].setFillColor(sf::Color::Red);
						window.draw(grid[rememberBox[curPressLevel][0]][rememberBox[curPressLevel][1]]);
						wrongBoxText.setString("Times Up!");
						float textWidth = wrongBoxText.getLocalBounds().width;
						float textHeight = wrongBoxText.getLocalBounds().height;
						wrongBoxText.setPosition(((rememberBox[curPressLevel][0] * cellSize.x + 2.0f) + (cellSize.x / 2)) - textWidth / 2, ((rememberBox[curPressLevel][1] * cellSize.y + 2.0f) + (cellSize.y / 2)) - textHeight / 2);
						window.draw(wrongBoxText);
						sf::Time elapsed4 = clock.getElapsedTime();
						if (elapsed4.asSeconds() > 1.5)
						{
							realGameOver = true;
						}
					}

					if (curPressLevel == (level - 1) && pressed)
					{
						grid[rememberBox[curPressLevel][0]][rememberBox[curPressLevel][1]].setFillColor(sf::Color::Green);
						window.draw(grid[rememberBox[curPressLevel][0]][rememberBox[curPressLevel][1]]);

						if (levelFinished)
						{
							sf::Time elapsed2 = clock.getElapsedTime();
							if (elapsed2.asSeconds() > 1)
							{
								for (int i = 0; i < level; i++)
								{
									delete[] rememberBox[i];
								}
								delete[] rememberBox;

								gameScore += 1;
								pressed = true;
								level += 2;
								startNewLevel = true;
								showBox = true;
							}
						}
					}
					else if (curPressLevel > 0)
					{
						grid[rememberBox[curPressLevel - 1][0]][rememberBox[curPressLevel - 1][1]].setFillColor(sf::Color::Green);
						window.draw(grid[rememberBox[curPressLevel - 1][0]][rememberBox[curPressLevel - 1][1]]);

						if (levelFinished)
						{
							sf::Time elapsed2 = clock.getElapsedTime();
							if (elapsed2.asSeconds() > 1)
							{
								for (int i = 0; i < level; i++)
								{
									delete[] rememberBox[i];
								}
								delete[] rememberBox;

								gameScore += 1;
								pressed = true;
								level += 2;
								startNewLevel = true;
								showBox = true;
							}
						}
					}
				}

				sf::Time elapsed = clock.getElapsedTime();
				if (elapsed.asSeconds() > 1)
				{
					if (curShowLevel < level - 1)
					{
						curShowLevel += 1;
						clock.restart();
					}
					else if (showBox)
					{
						showBox = false;
						clock3.restart();
					}
				}
			}
			else if (gameType == "hard")
			{
				sf::RectangleShape grid[hardColumns][hardRows];

				if (startNewLevel)
				{
					clock.restart();
					curShowLevel = 0;
					curPressLevel = 0;
					pressed = false;
					levelFinished = false;
					rememberBox = new int*[level];
					int temp = -1;
					bool notSame = false;
					for (int i = 0; i < level; i++)
					{
						notSame = false;
						while (!notSame)
						{
							random_x = rand() % 5;
							random_y = rand() % 5;
							if ((random_x + random_y) != temp)
							{
								notSame = true;
								temp = random_x + random_y;
							}
						}
						rememberBox[i] = new int[2];
						rememberBox[i][0] = random_x;
						rememberBox[i][1] = random_y;
					}
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

				if (showBox)
				{
					grid[rememberBox[curShowLevel][0]][rememberBox[curShowLevel][1]].setFillColor(sf::Color::Blue);
					window.draw(grid[rememberBox[curShowLevel][0]][rememberBox[curShowLevel][1]]);
				}
				else
				{
					sf::Time timeIsUp = clock3.getElapsedTime();
					if (timeIsUp.asSeconds() > 3 && !timeUpGameOver)
					{
						timeUpGameOver = true;
						clock.restart();
					}

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !gameOver)
					{
						sf::Vector2i localPosition = sf::Mouse::getPosition(window);
						int curX = rememberBox[curPressLevel][0] * cellSize.x + 2.0f;
						int curY = rememberBox[curPressLevel][1] * cellSize.y + 2.0f;

						if (localPosition.x < 600)
						{
							if (localPosition.x > curX && localPosition.x < (curX + cellSize.x) && localPosition.y > curY && localPosition.y < (curY + cellSize.y) && !pressed)
							{
								if (curPressLevel == (level - 1))
								{
									levelFinished = true;
									clock.restart();
									clock2.restart();
									pressed = true;
									pressed2 = true;
								}
								else
								{
									clock2.restart();
									clock3.restart();
									pressed2 = true;
									curPressLevel += 1;
								}
							}
							else if (!pressed2)
							{
								curPressLevel = 0;
								wrong_x = (localPosition.x - 2.0f) / cellSize.x;
								wrong_y = (localPosition.y - 2.0f) / cellSize.y;
								gameOver = true;
								clock.restart();
							}
						}
					}

					sf::Time elapsed3 = clock2.getElapsedTime();
					if (elapsed3.asSeconds() > 0.5 && pressed2)
					{
						pressed2 = false;
					}

					if (gameOver)
					{
						grid[wrong_x][wrong_y].setFillColor(sf::Color::Red);
						window.draw(grid[wrong_x][wrong_y]);
						wrongBoxText.setString("Wrong Box!");
						float textWidth = wrongBoxText.getLocalBounds().width;
						float textHeight = wrongBoxText.getLocalBounds().height;
						wrongBoxText.setPosition(((wrong_x * cellSize.x + 2.0f) + (cellSize.x / 2)) - textWidth / 2, ((wrong_y * cellSize.y + 2.0f) + (cellSize.y / 2)) - textHeight / 2);
						window.draw(wrongBoxText);
						sf::Time elapsed4 = clock.getElapsedTime();
						if (elapsed4.asSeconds() > 1.5)
						{
							realGameOver = true;
						}
					}

					if (timeUpGameOver)
					{
						grid[rememberBox[curPressLevel][0]][rememberBox[curPressLevel][1]].setFillColor(sf::Color::Red);
						window.draw(grid[rememberBox[curPressLevel][0]][rememberBox[curPressLevel][1]]);
						wrongBoxText.setString("Times Up!");
						float textWidth = wrongBoxText.getLocalBounds().width;
						float textHeight = wrongBoxText.getLocalBounds().height;
						wrongBoxText.setPosition(((rememberBox[curPressLevel][0] * cellSize.x + 2.0f) + (cellSize.x / 2)) - textWidth / 2, ((rememberBox[curPressLevel][1] * cellSize.y + 2.0f) + (cellSize.y / 2)) - textHeight / 2);
						window.draw(wrongBoxText);
						sf::Time elapsed4 = clock.getElapsedTime();
						if (elapsed4.asSeconds() > 1.5)
						{
							realGameOver = true;
						}
					}

					if (curPressLevel == (level - 1) && pressed)
					{
						grid[rememberBox[curPressLevel][0]][rememberBox[curPressLevel][1]].setFillColor(sf::Color::Green);
						window.draw(grid[rememberBox[curPressLevel][0]][rememberBox[curPressLevel][1]]);

						if (levelFinished)
						{
							sf::Time elapsed2 = clock.getElapsedTime();
							if (elapsed2.asSeconds() > 1)
							{
								for (int i = 0; i < level; i++)
								{
									delete[] rememberBox[i];
								}
								delete[] rememberBox;

								gameScore += 1;
								pressed = true;
								level += 3;
								startNewLevel = true;
								showBox = true;
							}
						}
					}
					else if (curPressLevel > 0)
					{
						grid[rememberBox[curPressLevel - 1][0]][rememberBox[curPressLevel - 1][1]].setFillColor(sf::Color::Green);
						window.draw(grid[rememberBox[curPressLevel - 1][0]][rememberBox[curPressLevel - 1][1]]);

						if (levelFinished)
						{
							sf::Time elapsed2 = clock.getElapsedTime();
							if (elapsed2.asSeconds() > 1)
							{
								for (int i = 0; i < level; i++)
								{
									delete[] rememberBox[i];
								}
								delete[] rememberBox;

								gameScore += 1;
								pressed = true;
								level += 3;
								startNewLevel = true;
								showBox = true;
							}
						}
					}
				}

				sf::Time elapsed = clock.getElapsedTime();
				if (elapsed.asSeconds() > 1)
				{
					if (curShowLevel < level - 1)
					{
						curShowLevel += 1;
						clock.restart();
					}
					else if (showBox)
					{
						showBox = false;
						clock3.restart();
					}
				}
			}

			text.setPosition(700, 200);
			window.draw(text);

			score.setString(to_string(gameScore));
			score.setPosition(800, 200);
			window.draw(score);
		}
		else
		{
			score.setString("Score: " + to_string(gameScore));
			float scoreWidth = score.getLocalBounds().width;
			score.setPosition(500 - (scoreWidth / 2), 200);
			window.draw(score);

			startAgainText.setString("Press Anywhere to Start Again.");
			float startAgainWidth = startAgainText.getLocalBounds().width;
			startAgainText.setPosition(500 - (startAgainWidth / 2), 400);
			window.draw(startAgainText);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				clock.restart();
				clock2.restart();
				gameChosen = false;
				gameScore = 0;
				showBox = true;
				realGameOver = false;
				gameOver = false;
				startNewLevel = true;
				level = 1;
				startPressed = true;
			}
		}

		window.display();
	}

	return 0;
}
