#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <list>
#include <functional>
#include "WindowHeader.h"


class Actor : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}
public:
	sf::Sprite sprite;
	enum Type
	{
		None,
		Player,
		Enemy,
		Coin,
		Spike,
		Exit
	};
	Type type = None;
	sf::Texture blankTexture;
	sf::Texture playerTexture;
	sf::Texture enemyTexture;
	sf::Texture coinTexture;
	sf::Texture spikeTexture;
	sf::Texture doorTexture;
	Actor() {}

	void loadTextures()
	{
		if (!blankTexture.loadFromFile("SpritesPlatformer/None.png"))
		{
			std::cout << "Failed to load None.png";
		}
		if (!playerTexture.loadFromFile("SpritesPlatformer/Player.png"))
		{
			std::cout << "Failed to load Player.png";
		}
		if (!enemyTexture.loadFromFile("SpritesPlatformer/EnemyAlive.png"))
		{
			std::cout << "Failed to load EnemyAlive.png";
		}
		if (!coinTexture.loadFromFile("SpritesPlatformer/Coin.png"))
		{
			std::cout << "Failed to load Coin.png";
		}
		if (!spikeTexture.loadFromFile("SpritesPlatformer/Spike.png"))
		{
			std::cout << "Failed to load Spike.png";
		}
		if (!doorTexture.loadFromFile("SpritesPlatformer/Door.png"))
		{
			std::cout << "Failed to load Door.png";
		}
	}

	void init(int x, int y)
	{
		loadTextures();
		sprite.setPosition(x, y);
		RefreshActor();
	}

	void ChangeActor(Type t)
	{
		type = t;
		RefreshActor();
	}

	void RefreshActor()
	{
		switch (type)
		{
		case None:
			sprite.setTexture(blankTexture);
			break;
		case Player:
			sprite.setTexture(playerTexture);
			break;
		case Enemy:
			sprite.setTexture(enemyTexture);
			break;
		case Coin:
			sprite.setTexture(coinTexture);
			break;
		case Spike:
			sprite.setTexture(spikeTexture);
			break;
		case Exit:
			sprite.setTexture(doorTexture);
			break;
		}
	}
};

class Tile : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
		target.draw(actor, states);
	}
public:
	sf::Sprite sprite;
	Actor actor;
	enum Type
	{
		Sky,
		Platform,
		Lava,
	};
	Type type = Sky;
	sf::Texture skyTexture;
	sf::Texture platformTexture;
	sf::Texture lavaTexture;


	void loadTextures()
	{
		if (!skyTexture.loadFromFile("SpritesPlatformer/BlockSky.png"))
		{
			std::cout << "Failed to load BlockSky.png";
		}
		if (!platformTexture.loadFromFile("SpritesPlatformer/BlockPlatform.png"))
		{
			std::cout << "Failed to load BlockPlatform.png";
		}
		if (!lavaTexture.loadFromFile("SpritesPlatformer/BlockLava.png"))
		{
			std::cout << "Failed to load BlockLava.png";
		}

	}

	void init(int x, int y)
	{
		loadTextures();
		sprite.setPosition(x, y);
		RefreshTile();
		actor.init(x, y);
	}

	void ChangeTile(Type t)
	{
		type = t;
		RefreshTile();
	}

	void ChangeActor(Actor::Type a)
	{
		actor.ChangeActor(a);
	}

	void RefreshTile()
	{
		switch (type)
		{
		case Sky:
			sprite.setTexture(skyTexture);
			break;
		case Platform:
			sprite.setTexture(platformTexture);
			break;
		case Lava:
			sprite.setTexture(lavaTexture);
			break;

		}
	}



	bool mouseOver(sf::Vector2f windPos)
	{
		sf::FloatRect rBounds = sprite.getGlobalBounds();
		return rBounds.contains(windPos.x, windPos.y);
	}
};

class Button : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(rect, states);
		target.draw(text, states);
	}
public:
	int textSize = 16;
	float rectOutline = 1;
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text text;
	sf::FloatRect rBounds;

	Button()
	{
		font.loadFromFile("arial.ttf");
		text.setFont(font);
		text.setCharacterSize(textSize);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Regular);
		rect.setFillColor(sf::Color::White);
		rect.setOutlineColor(sf::Color::Black);
rect.setOutlineThickness(rectOutline);
	}

	bool mouseOver(sf::Vector2f windPos)
	{
		rBounds = rect.getGlobalBounds();
		if (rBounds.contains(windPos.x, windPos.y))
		{
			rect.setOutlineThickness(rectOutline * 2);
			return true;
		}
		else
		{
			rect.setOutlineThickness(rectOutline);
			return false;
		}
	}

	void checkClick(std::function<void()> f, sf::Vector2f windPos)
	{
		if (mouseOver(windPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			f();
		}
	}
};

class InputField : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(rect, states);
		target.draw(text, states);
	}
public:
	sf::RectangleShape rect;
	sf::Text text;
	sf::Font font;
	int fontSize = 16;
	InputField()
	{
		font.loadFromFile("arial.ttf");
		text.setFont(font);
		text.setCharacterSize(fontSize);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Regular);
	}

	void UpdatePos(sf::Vector2f newPos)
	{
		rect.setSize(sf::Vector2f(text.getGlobalBounds().width + 6, text.getGlobalBounds().height + 6));
		rect.setPosition(newPos);
		text.setPosition(rect.getPosition().x + (rect.getSize().x / 400000), rect.getPosition().y);
	}
};

class ToolPanel : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(loadButton, states);
		target.draw(saveButton, states);
	}
public:
	Button loadButton;
	Button saveButton;

	ToolPanel() //Sets the location and other settings of the save and load buttons
	{
		loadButton.text.setString("Load");
		loadButton.rect.setSize(sf::Vector2f(loadButton.text.getGlobalBounds().width + 6, loadButton.text.getGlobalBounds().height + 6));

		loadButton.rect.setPosition(sf::Vector2f(2, 2));
		loadButton.text.setPosition(loadButton.rect.getPosition().x + (loadButton.rect.getSize().x / 40000), loadButton.rect.getPosition().y);

		saveButton.text.setString("Save");
		saveButton.rect.setSize(sf::Vector2f(saveButton.text.getGlobalBounds().width + 6, saveButton.text.getGlobalBounds().height + 6));

		saveButton.rect.setPosition(sf::Vector2f(2, 27));
		saveButton.text.setPosition(saveButton.rect.getPosition().x + (saveButton.rect.getSize().x / 40000), saveButton.rect.getPosition().y);
	}
};

class EditorClass
{
public:
	EditorClass();
	//grid amounts
	static const int x = 30;
	static const int y = 20;

	//keep track of if we're painting with an actor or a tile
	bool actorNotTile = false;

	//window size
	const int windowWidth = 1025;
	const int windowHeight = 650;

	sf::Vector2f worldPos;
	sf::View toolsView;
	sf::View levelEditView;
	sf::RenderWindow window;

	Tile::Type curTileType;
	Actor::Type curActorType;

	ToolPanel tools;

	Tile tileButton[9];
	//setup tiles array
	//Tile tile[x][y];
	Tile** tile = new Tile* [x];

	bool Start(MainRenderWindow &mainWindow);
	void Update(MainRenderWindow &mainWindow);

	bool editorActive = false;

	std::string playerInput;
	InputField inputField;

	//saving
	void save(std::string fileName, Tile** incTile)
	{
		//write text to a file
		std::ofstream myfile(fileName + ".sav");
		std::list<sf::Vector2i> coinPos;
		std::list<sf::Vector2i> enemyPos;
		std::list<sf::Vector2i> spikePos;
		sf::Vector2i playerPos;
		sf::Vector2i exitPos;

		if (myfile.is_open())
		{
			std::cout << "saving file \n";
			for (int i = 0; i < x; i++)
			{
				for (int j = 0; j < y; j++)
				{
					switch (incTile[i][j].type)
					{
					case Tile::Type::Sky:
						myfile << "0";
						break;
					case Tile::Type::Platform:
						myfile << "1";
						break;
					case Tile::Type::Lava:
						myfile << "2";
						break;
					}
					myfile << ",";
					switch (incTile[i][j].actor.type)
					{
					case Actor::Type::Coin:
						coinPos.push_back(sf::Vector2i(i, j));
						break;
					case Actor::Type::Enemy:
						enemyPos.push_back(sf::Vector2i(i, j));
						break;
					case Actor::Type::Spike:
						spikePos.push_back(sf::Vector2i(i, j));
						break;
					case Actor::Type::Player:
						playerPos = sf::Vector2i(i, j);
						break;
					case Actor::Type::Exit:
						exitPos = sf::Vector2i(i, j);
						break;
					
					}
				}
				myfile << "\n";
			}
			//loop through all of the lists, add them to the save file, then add the player/exit positions
			//coins
			if (!coinPos.empty())
			{
				std::cout << "Saving Coins \n";
				myfile << "Coin";
				std::list <sf::Vector2i>::iterator cIt;
				for (cIt = coinPos.begin(); cIt != coinPos.end(); cIt++)
				{
					sf::Vector2i curCoinPos = sf::Vector2i(cIt->x, cIt->y);
					std::cout << "Saving coin at: " << curCoinPos.x << "," << curCoinPos.y << "\n";
					myfile << '(' << curCoinPos.x << ',' << curCoinPos.y << ')';
				}
				myfile << "\n";
			}

			//enemies
			if (!enemyPos.empty())
			{
				std::cout << "Saving enemies \n";
				myfile << "Enemy";
				std::list <sf::Vector2i>::iterator eIt;
				for (eIt = enemyPos.begin(); eIt != enemyPos.end(); eIt++)
				{
					sf::Vector2i curEnemyPos = sf::Vector2i(eIt->x, eIt->y);
					std::cout << "Saving enemy at: " << curEnemyPos.x << "," << curEnemyPos.y << "\n";
					myfile << '(' << curEnemyPos.x << ',' << curEnemyPos.y << ')';
				}
				myfile << "\n";
			}
			//spikes
			if (!spikePos.empty())
			{
				std::cout << "Saving spikes \n";
				myfile << "Spike";
				std::list <sf::Vector2i>::iterator sIt;
				for (sIt = spikePos.begin(); sIt != spikePos.end(); sIt++)
				{
					sf::Vector2i curSpikePos = sf::Vector2i(sIt->x, sIt->y);
					std::cout << "Saving spikes at: " << curSpikePos.x << "," << curSpikePos.y << "\n";
					myfile << '(' << curSpikePos.x << ',' << curSpikePos.y << ')';
				}
				myfile << "\n";
			}
			//player
			std::cout << "Saving player at: " << playerPos.x << ',' << playerPos.y << "\n";
			myfile << "Player" << '(' << playerPos.x << ',' << playerPos.y << ')' << "\n";
			//exit
			std::cout << "Saving exit at: " << exitPos.x << ',' << exitPos.y << "\n";
			myfile << "Exit" << '(' << exitPos.x << ',' << exitPos.y << ')' << "\n";

			myfile.close();
			std::cout << "Saving Complete \n";
		}
		else
		{
			std::cout << "Can't open file \n";
		}
	}
	//loading
	void load(std::string fileName, Tile** incTile)
	{
		std::string line;
		std::ifstream myfile(fileName + ".sav");
		if (myfile.is_open())
		{
			int a = 0;
			int b = 0;
			std::string saveHold;
			while (std::getline(myfile, line))
			{
				if (b == 0)
				{
					std::cout << "Loading Tiles \n";
				}
				if (b < x)
				{
					for (int i = 0; i < line.size(); i++)
					{
						switch (line[i])
						{
						case ',':
							a++;
							break;
						case '0':
							incTile[b][a].ChangeTile(Tile::Type::Sky);
							break;
						case'1':
							incTile[b][a].ChangeTile(Tile::Type::Platform);
							break;
						case'2':
							incTile[b][a].ChangeTile(Tile::Type::Lava);

						}
						incTile[b][a].RefreshTile();
						incTile[b][a].ChangeActor(Actor::Type::None);
					}
				}
				else if (b >= x) //loading actors
				{
					std::string lineHold = line;
					int curStart;
					int curEnd = 0;
					std::string posString;
					if (line[0] == 'C' && line[1] == 'o') //[C][o]ins
					{
						std::cout << "Loading Coins \n";
						while (curEnd < lineHold.length() && lineHold.find('(') != std::string::npos)
						{
							curStart = lineHold.find('('); //Find opening bracket
							curEnd = lineHold.find(')'); //Find closing bracket
							posString = lineHold.substr(curStart + 1, curEnd - (curStart + 1)); //cut the numbers out
							std::cout << "Loaded Coins at: " << posString << "\n"; // we now have " #,# "
							std::string xStr = posString.substr(0, posString.find(','));
							std::string yStr = posString.substr(posString.find(',') + 1, posString.length());

							incTile[std::stoi(xStr)][std::stoi(yStr)].ChangeActor(Actor::Type::Coin);
							lineHold[curStart] = '<';
							lineHold[curEnd] = '>';
						}
					}
					else if (line[0] == 'E' && line[1] == 'n') //enemies
					{
						std::cout << "Loading Enemies \n";
						while (curEnd < lineHold.length() && lineHold.find('(') != std::string::npos)
						{
							curStart = lineHold.find('('); //Find opening bracket
							curEnd = lineHold.find(')'); //Find closing bracket
							posString = lineHold.substr(curStart + 1, curEnd - (curStart + 1)); //cut the numbers out
							std::cout << "Loaded Enemy at: " << posString << "\n"; // we now have " #,# "
							std::string xStr = posString.substr(0, posString.find(','));
							std::string yStr = posString.substr(posString.find(',') + 1, posString.length());

							incTile[std::stoi(xStr)][std::stoi(yStr)].ChangeActor(Actor::Type::Enemy);
							lineHold[curStart] = '<';
							lineHold[curEnd] = '>';
						}
					}
					else if (line[0] == 'S' && line[1] == 'p') //Spikes
					{
						std::cout << "Loading Spikes \n";
						while (curEnd < lineHold.length() && lineHold.find('(') != std::string::npos)
						{
							curStart = lineHold.find('('); //Find opening bracket
							curEnd = lineHold.find(')'); //Find closing bracket
							posString = lineHold.substr(curStart + 1, curEnd - (curStart + 1)); //cut the numbers out
							std::cout << "Loaded Spike at: " << posString << "\n"; // we now have " #,# "
							std::string xStr = posString.substr(0, posString.find(','));
							std::string yStr = posString.substr(posString.find(',') + 1, posString.length());

							incTile[std::stoi(xStr)][std::stoi(yStr)].ChangeActor(Actor::Type::Spike);
							lineHold[curStart] = '<';
							lineHold[curEnd] = '>';
						}
					}
					else if (line[0] == 'P' && line[1] == 'l') //Player
					{
						std::cout << "Loading Player \n";
						while (curEnd < lineHold.length() && lineHold.find('(') != std::string::npos)
						{
							curStart = lineHold.find('('); //Find opening bracket
							curEnd = lineHold.find(')'); //Find closing bracket
							posString = lineHold.substr(curStart + 1, curEnd - (curStart + 1)); //cut the numbers out
							std::cout << "Loaded Player at: " << posString << "\n"; // we now have " #,# "
							std::string xStr = posString.substr(0, posString.find(','));
							std::string yStr = posString.substr(posString.find(',') + 1, posString.length());

							incTile[std::stoi(xStr)][std::stoi(yStr)].ChangeActor(Actor::Type::Player);
							lineHold[curStart] = '<';
							lineHold[curEnd] = '>';
						}
					}
					else if (line[0] == 'E' && line[1] == 'x') //Exit
					{
						std::cout << "Loading Exit \n";
						while (curEnd < lineHold.length() && lineHold.find('(') != std::string::npos)
						{
							curStart = lineHold.find('('); //Find opening bracket
							curEnd = lineHold.find(')'); //Find closing bracket
							posString = lineHold.substr(curStart + 1, curEnd - (curStart + 1)); //cut the numbers out
							std::cout << "Loaded Exit at: " << posString << "\n"; // we now have " #,# "
							std::string xStr = posString.substr(0, posString.find(','));
							std::string yStr = posString.substr(posString.find(',') + 1, posString.length());

							incTile[std::stoi(xStr)][std::stoi(yStr)].ChangeActor(Actor::Type::Exit);
							lineHold[curStart] = '<';
							lineHold[curEnd] = '>';
						}
					}
				}
				b += 1;
				a = 0;
			}
			myfile.close();
			std::cout << "File Loaded \n";
		}
		else
		{
			std::cout << "Cannot open save file \n";
		}
	}
	//printing out tiles (debug)


};