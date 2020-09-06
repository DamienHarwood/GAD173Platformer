#pragma once
# include <SFML/Graphics.hpp>
# include <iostream>
# include <functional>
# include "WindowHeader.h"

class Mode
{
public:
	enum MenuMode
	{
		MainMenu,
		Editor,
		EditorLevelSelect,
		Game,
		GameLevelSelect
	};
	MenuMode currentMode = MainMenu;
};

class EditorLevelSelect
{

};

class GameLevelSelect
{

};

class MenuButton : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
	{
		target.draw(rect, states);
		target.draw(text, states);
	}
public:
	int textSize = 30;
	float rectOutline = 1;
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text text;
	sf::FloatRect rBounds;

	//Init
	MenuButton()
	{
		font.loadFromFile("arial.ttf");
			text.setFont(font);
			text.setCharacterSize(textSize);
			text.setFillColor(sf::Color::Black);
			text.setStyle(sf::Text::Regular);

			//setup visuals
			rect.setFillColor(sf::Color::White);
			rect.setOutlineColor(sf::Color::Yellow);
			rect.setOutlineThickness(rectOutline);
	}
	bool mouseOver(sf::Vector2f windPos)
	{
		rBounds = rect.getGlobalBounds();
		if (rBounds.contains(windPos.x, windPos.y))
		{
			rect.setOutlineThickness(rectOutline * 5);
			rect.setFillColor(sf::Color::Green);
			return true;
		}
		else
		{
			rect.setOutlineThickness(rectOutline);
			rect.setFillColor(sf::Color::White);
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

class MainMenu
{
public:
	MenuButton levelEditorButton;
	MenuButton gameButton;

	Mode myMode;
	MainMenu()
	{
		levelEditorButton.text.setString("Level Editor");
		levelEditorButton.rect.setSize(sf::Vector2f(levelEditorButton.text.getGlobalBounds().width + 6,
													levelEditorButton.text.getGlobalBounds().height + 12));
		levelEditorButton.rect.setPosition(sf::Vector2f(1025 - (1025 / 2 - (levelEditorButton.rect.getSize().x / 2)),
														650 - (650 / 2 - (levelEditorButton.rect.getSize().y / 2))));
		levelEditorButton.text.setPosition(levelEditorButton.rect.getPosition().x + (levelEditorButton.rect.getSize().x / 4000000),
			levelEditorButton.rect.getPosition().y);

		gameButton.text.setString("Game");
		gameButton.rect.setSize(sf::Vector2f(gameButton.text.getGlobalBounds().width + 6,
			gameButton.text.getGlobalBounds().height + 12));
		gameButton.rect.setPosition(sf::Vector2f(1025 - (1025 / 2 + 150 - (gameButton.rect.getSize().x / 2)),
			650 - (650 / 2 - (gameButton.rect.getSize().y / 2))));
		gameButton.text.setPosition(gameButton.rect.getPosition().x + (gameButton.rect.getSize().x / 4000000),
			gameButton.rect.getPosition().y);

		

	}

	sf::Vector2f worldPos;

	bool Start();
	void Update(MainRenderWindow& mainWindow);
	bool menuActive = true;
	void ChangeMode(Mode::MenuMode m)
	{
		myMode.currentMode = m;
		menuActive = false;
	}
};

