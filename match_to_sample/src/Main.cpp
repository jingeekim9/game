#include "SFML/Graphics.hpp"
#include <dirent.h>
#include <iostream>
#include <string>
using namespace std;

int main()
{

	DIR* dir;
	struct dirent* diread;
	vector<string> files;

	if ((dir = opendir("images/")) != nullptr)
	{
		while ((diread = readdir(dir)) != nullptr)
		{
			if (!strcmp(diread->d_name, ".") || !strcmp(diread->d_name, ".."))
			{
			}
			else
			{
				files.push_back(diread->d_name);
			}
		}
		closedir(dir);
	}
	else
	{
		perror("opendir");
		return EXIT_FAILURE;
	}

	// for (int i = 0; i < (int)files.size(); i++)
	// {
	// 	cout << files[i] << endl;
	// }

#if defined(_DEBUG)
	std::cout << "Game Initialized!" << std::endl;
#endif

	sf::RenderWindow window(sf::VideoMode(1000, 600), "Match To Sample Game");
	sf::Color color1(0, 128, 128);
	sf::RectangleShape background;
	background.setFillColor(color1);

	int correctAnswers = 0;
	int questionsAsked = 0;
	bool asking = false;
	bool showImages = false;
	int currentImage = 0;
	int wrongImage = 0;
	int placement = 0;
	bool imagePressed = false;
	bool answerChosen = false;
	bool gameFinished = false;

	const int imageCount = (int)files.size();
	int* nums = new int[imageCount];
	for (int i = 0; i < imageCount; i++)
	{
		nums[i] = i;
	}
	srand(time(0));
	random_shuffle(nums, nums + imageCount);

	sf::RectangleShape whitebox;
	whitebox.setFillColor(sf::Color::White);

	sf::Font font;
	font.loadFromFile("fonts/Lato-Regular.ttf");
	sf::Text answerText;
	answerText.setFont(font);
	answerText.setCharacterSize(20);
	answerText.setFillColor(sf::Color::White);

	sf::Text startOverText;
	startOverText.setFont(font);
	startOverText.setCharacterSize(20);
	startOverText.setFillColor(sf::Color::White);

	sf::RectangleShape image1;
	image1.setFillColor(sf::Color::White);
	sf::Texture image1Texture;
	image1Texture.loadFromFile("images/" + files[nums[currentImage]]);
	image1.setTexture(&image1Texture);

	sf::RectangleShape image2;
	image2.setFillColor(sf::Color::White);
	sf::Texture image2Texture;

	sf::RectangleShape image3;
	image3.setFillColor(sf::Color::White);
	sf::Texture image3Texture;

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

		sf::Vector2f backgroundSize(1000.0f, 600.0f);
		background.setSize(backgroundSize);
		background.setPosition(0, 0);
		window.draw(background);

		if (!gameFinished)
		{
			if (!asking)
			{
				sf::Vector2f boxSize(200.0f, 120.0f);
				whitebox.setSize(boxSize);
				whitebox.setPosition((1000 / 2) - 100, (600 / 2) - 60);
				window.draw(whitebox);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2i localPosition = sf::Mouse::getPosition(window);
					if (localPosition.x > ((1000 / 2) - 100) && localPosition.x < ((1000 / 2) + 100) && localPosition.y > ((600 / 2) - 60) && localPosition.y < ((600 / 2) + 60))
					{
						asking = true;
					}
				}
			}
			else
			{
				sf::Vector2f imageSize(200.0f, 120.0f);
				image1.setSize(imageSize);
				image1.setPosition((1000 / 2) - 100, (600 / 2) - 200);
				window.draw(image1);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2i localPosition = sf::Mouse::getPosition(window);
					if (localPosition.x > ((1000 / 2) - 100) && localPosition.x < ((1000 / 2) + 100) && localPosition.y > ((600 / 2) - 200) && localPosition.y < ((600 / 2) - 80) && !imagePressed)
					{
						showImages = true;
						placement = rand() % 2;

						wrongImage = rand() % imageCount;
						while (wrongImage == currentImage)
						{
							wrongImage = rand() % imageCount;
						}

						if (placement == 0)
						{
							image2Texture.loadFromFile("images/" + files[nums[currentImage]]);
							image2.setTexture(&image2Texture);

							image3Texture.loadFromFile("images/" + files[nums[wrongImage]]);
							image3.setTexture(&image3Texture);
						}
						else
						{
							image2Texture.loadFromFile("images/" + files[nums[wrongImage]]);
							image2.setTexture(&image2Texture);

							image3Texture.loadFromFile("images/" + files[nums[currentImage]]);
							image3.setTexture(&image3Texture);
						}

						imagePressed = true;
					}
				}

				if (showImages)
				{
					image2.setSize(imageSize);
					image2.setPosition((1000 / 3) - 100, (600 / 2) + 50);
					window.draw(image2);

					image3.setSize(imageSize);
					image3.setPosition((1000 / 3) * 2 - 100, (600 / 2) + 50);
					window.draw(image3);

					if (placement == 0)
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							sf::Vector2i localPosition = sf::Mouse::getPosition(window);
							if (localPosition.x > ((1000 / 3) - 100) && localPosition.x < ((1000 / 3) + 100) && localPosition.y > ((600 / 2) + 50) && localPosition.y < ((600 / 2) + 170) && !answerChosen)
							{
								image2.setOutlineColor(sf::Color::Green);
								image2.setOutlineThickness(5.0f);
								answerChosen = true;
								correctAnswers = correctAnswers + 1;
								questionsAsked = questionsAsked + 1;
								clock.restart();
							}
							if (localPosition.x > ((1000 / 3) * 2 - 100) && localPosition.x < ((1000 / 3) * 2 + 100) && localPosition.y > ((600 / 2) + 50) && localPosition.y < ((600 / 2) + 170) && !answerChosen)
							{
								image3.setOutlineColor(sf::Color::Red);
								image3.setOutlineThickness(5.0f);
								answerChosen = true;
								questionsAsked = questionsAsked + 1;
								clock.restart();
							}
						}
					}
					else
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							sf::Vector2i localPosition = sf::Mouse::getPosition(window);
							if (localPosition.x > ((1000 / 3) * 2 - 100) && localPosition.x < ((1000 / 3) * 2 + 100) && localPosition.y > ((600 / 2) + 50) && localPosition.y < ((600 / 2) + 170) && !answerChosen)
							{
								image3.setOutlineColor(sf::Color::Green);
								image3.setOutlineThickness(5.0f);
								answerChosen = true;
								correctAnswers = correctAnswers + 1;
								questionsAsked = questionsAsked + 1;
								clock.restart();
							}
							if (localPosition.x > ((1000 / 3) - 100) && localPosition.x < ((1000 / 3) + 100) && localPosition.y > ((600 / 2) + 50) && localPosition.y < ((600 / 2) + 170) && !answerChosen)
							{
								image2.setOutlineColor(sf::Color::Red);
								image2.setOutlineThickness(5.0f);
								answerChosen = true;
								questionsAsked = questionsAsked + 1;
								clock.restart();
							}
						}
					}

					if (answerChosen)
					{
						sf::Time elapsed = clock.getElapsedTime();
						if (elapsed.asSeconds() > 1)
						{
							asking = false;
							showImages = false;
							imagePressed = false;
							answerChosen = false;
							currentImage += 1;

							image2.setOutlineColor(sf::Color::Transparent);
							image2.setOutlineThickness(0.0f);
							image3.setOutlineColor(sf::Color::Transparent);
							image3.setOutlineThickness(0.0f);

							image1Texture.loadFromFile("images/" + files[nums[currentImage]]);
							image1.setTexture(&image1Texture);
						}
					}
				}
			}

			answerText.setString("Correct " + to_string(correctAnswers) + "/" + to_string(questionsAsked));
			float answerTextWidth = answerText.getLocalBounds().width;
			float answerTextHeight = answerText.getLocalBounds().height;
			answerText.setPosition(1000 - answerTextWidth - 30, 600 - answerTextHeight - 30);
			window.draw(answerText);
		}
		else
		{
			answerText.setString(to_string(correctAnswers) + " correct out of " + to_string(questionsAsked) + " questions");
			float answerTextWidth = answerText.getLocalBounds().width;
			float answerTextHeight = answerText.getLocalBounds().height;
			answerText.setPosition((1000 / 2) - (answerTextWidth / 2), (600 / 2) - answerTextHeight);
			window.draw(answerText);

			startOverText.setString("Press anywhere to start again");
			float startOverTextWidth = startOverText.getLocalBounds().width;
			float startOverTextHeight = startOverText.getLocalBounds().height;
			startOverText.setPosition((1000 / 2) - (startOverTextWidth / 2), (600 / 2) - (startOverTextHeight - 50));
			window.draw(startOverText);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				gameFinished = false;
				asking = false;
				showImages = false;
				imagePressed = false;
				answerChosen = false;
				currentImage = 0;
				correctAnswers = 0;
				questionsAsked = 0;
				random_shuffle(nums, nums + imageCount);

				image1Texture.loadFromFile("images/" + files[nums[currentImage]]);
				image1.setTexture(&image1Texture);
			}
		}
		window.display();
	}

	delete[] nums;
	return 0;
}
