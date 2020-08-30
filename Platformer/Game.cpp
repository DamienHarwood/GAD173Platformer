#include "Game.h"
//Damien Harwood
GameClass::GameClass()
{
	//physics
	gravity = 0.5f;
	friction = 5.0f;

	//loop though tiles for init
	for (int i = 0; i < x; i++)
	{
		tile[i] = new Tile[y];
	}
}

void GameClass::LoadLevel(std::string levelName, Tile** incTile)
{
	//cleanup current tiles
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			incTile[i][j].type = Tile::Type::Sky;
			incTile[i][j].actor.type = Actor::Type::None;
			incTile[i][j].RefreshTile();
		}
	}

	//exisisting load code from load function
	std::string line;
	std::ifstream myfile(levelName);
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
						player.type = Actor::Type::Player;
						player.init(stoi(xStr) * 32 + ((1025 / 2) - ((32 * x) / 2)), stoi(yStr) * 32);
						player.startPos = sf::Vector2f(stoi(xStr) * 32 + ((1025 / 2) - ((32 * x) / 2)), stoi(yStr) * 32);
						player.Respawn();
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

void Player::Respawn()
{
	setPosition(startPos);
	Refresh();

}

Collision Player::CollisionCheck(sf::FloatRect other)
{
	Collision col;
	float deltaX = (nextPos.x - (nextRect.width / 2)) - (other.left - other.width / 2);
	float deltaY = (nextPos.y - (nextRect.height / 2)) - (other.top - other.height / 2);
	
	float intersectX = abs(deltaX) - ((other.width / 2) + (nextRect.width / 2));
	float intersectY = abs(deltaY) - ((other.height / 2) + (nextRect.height / 2));

	col.hit = (intersectX < 0.0f && intersectY < 0.0f);

	if (col.hit)
	{
		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				col.dir = sf::Vector2f(intersectX, 0.0f);
			}
			else
			{
				col.dir = sf::Vector2f(-intersectX, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				col.dir = sf::Vector2f(0.0f, intersectY);
			}											 											
			
			else
			{
				col.dir = sf::Vector2f(0.0f, -intersectY);
			}											  
		}
	}
	else
	{
		col.dir = sf::Vector2f(0.0f, 0.0f);
	}
	return col;
}

Player::Player()
{
	lives = 3;
	coins = 0;
	isDead = false;
	isGrounded = true;
	speed = 2.5f;
	jumpSpeed = 0.75f;
	velocity = sf::Vector2f(0.0f, 0.0f);
}

void Player::Refresh()
{
	Actor::RefreshActor();
	velocity = sf::Vector2f(0.0f, 0.0f);
	nextPos = getPosition();
}

sf::Vector2f Player::getPosition()
{
	return sprite.getPosition();
}

void Player::setPosition(sf::Vector2f p)
{
	sprite.setPosition(p);
}

int sign(int x)
{
	return (x > 0) - (x < 0);
}
int sign(float x)
{
	return (x > 0.0f) - (x < 0.0f);
}

void Enemy::Killed()
{
	type = Actor::Type::None;
	RefreshActor();
}

bool Player::isAnyKeyPressed()
{
	for (int i = -1; i < sf::Keyboard::KeyCount; i++)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
		{
			return true;
		}
	}
	return false;
}