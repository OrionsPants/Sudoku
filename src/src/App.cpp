#include "App.h"
#include <iostream>






	//auto window = sf::RenderWindow{{window_width, window_height}, "Pong", sf::Style::Default, settings};

/*
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window.setFramerateLimit(144);


	sf::Font font;

	font.loadFromFile("./fonts/futura.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("Test");

	sf::Text score_text;
	score_text.setFont(font);
	score_text.setString("0:0");

	score_text.setPosition(sf::Vector2f(window_width/2, 0));

	std::chrono::time_point begin = std::chrono::high_resolution_clock::now();
	std::chrono::time_point start_time = std::chrono::high_resolution_clock::now();
	auto end_time = start_time;
	double deltaTime = 0;
	double previous_delta_time = 0;
	double delta_time_accumulated = 0;
	uint64_t frame_counter = 0;


	Player player = Player();
	player.SetNormal(1.0f, 0.0f);
	Opponent opponent = Opponent();
	opponent.SetNormal(-1.0f, 0.0f);

	Ball ball = Ball();

	Wall top_wall = Wall(window_width, window_height / 16, 0, 0);
	top_wall.SetNormal(0.0f, 1.0f);
	Wall bot_wall = Wall(window_width, window_height / 16, 0, window_height - window_height/16);
	bot_wall.SetNormal(0.0f, -1.0f);

	std::vector<Collidable*> bbs;
	bbs.push_back((&player));
	bbs.push_back((&opponent));
	bbs.push_back((&top_wall));
	bbs.push_back((&bot_wall));


	while(window.isOpen())
	{
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() * 1e-6;
		delta_time_accumulated += deltaTime;
		deltaTime = (deltaTime + previous_delta_time) / 2;
		previous_delta_time = deltaTime;

		start_time = std::chrono::high_resolution_clock::now();

		if(delta_time_accumulated > 1)
		{
			text.setString(std::to_string(static_cast<int>(std::floor(1 / deltaTime))));
			delta_time_accumulated = 0;
		}

		for(auto event = sf::Event{}; window.pollEvent(event);)
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color(10, 10, 10, 255));
		

		// Draw everything here

		window.draw(player.shape);
		window.draw(opponent.shape);
		window.draw(ball.shape);

		window.draw(top_wall.shape);
		window.draw(bot_wall.shape);
		window.draw(text);
		window.draw(score_text);

		window.display();



		// handle input

		player.HandleInput(deltaTime);
		ball.Update(deltaTime);
		if(ball.Collide(bbs))
		{
			ball.speed += 25;
			opponent.speed += 10;
			movement_speed += 25;
		}
		opponent.Update(deltaTime, ball);

		if(CheckGameCondition(ball))
		{
			score_text.setString(std::to_string(player_score) + " : " + std::to_string(computer_score));
			ball.Reset();
			player.Reset();
			opponent.Reset();
			movement_speed = 200.0f;

			
			bool game_over = false;
				sf::Text txt;
				txt.setFont(font);
				txt.setPosition(sf::Vector2f(window_width / 2, window_height / 2));

			if(computer_score == 5)
			{
				game_over = true;
				txt.setString("You Lost!\nPlay Again?\ny/n");
			}
			else if(player_score == 5)
			{
				game_over = true;
				txt.setString("You Won!\nPlay Again?\ny/n");
			}

			while(game_over)
			{
				window.clear(sf::Color(10, 10, 10, 255));

				

				window.draw(txt);

				window.display();

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
				{
					player_score = 0;
					computer_score = 0;
					ball.Reset();
					movement_speed = 200.0f;
					opponent.Reset();
					player.Reset();
					score_text.setString(std::to_string(player_score) + " : " + std::to_string(computer_score));
					game_over = false;
					break;
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
				{
					window.close();
					break;
				}


			}
		
		}






		frame_counter++;
		end_time = std::chrono::high_resolution_clock::now();
		if(frame_counter == 10000)
		{
			std::cout << "Elapsed time for 10000 frames: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin).count() << " ms"
					  << std::endl;
		}
	}
}

*/