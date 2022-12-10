#include "settings.h"
using namespace sf;

int main()
{
	srand(time(nullptr));
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(FPS);
	//создание объектов игры
	//ракетки
	RectangleShape leftBat, rightBat;
	leftBat.setSize(batSize);
	rightBat.setSize(batSize);
	leftBat.setFillColor(leftBatColor);
	rightBat.setFillColor(rightBatColor);
	leftBat.setPosition(batOffset, (WINDOW_HEIGHT - batHeight) / 2);
	rightBat.setPosition(WINDOW_WIDTH - batOffset, (WINDOW_HEIGHT - batHeight) / 2);
	float leftBatSpeedY = 0.f;
	float rightBatSpeedY = 0.f;
	//шарик
	CircleShape ball(ballRadius);
	ball.setFillColor(ballColor);
	ball.setPosition((WINDOW_WIDTH - 2 * ballRadius) / 2,
		(WINDOW_HEIGHT - 2 * ballRadius) / 2);
	float ball_dx = 2.f;
	float ball_dy = 2.f;
	float arr_speed[]{ -5.f, -4.f, -3.f, -2.f, -1.f, 1.f, 2.f, 3.f, 4.f,5.f };
	int index = rand() % 10;
	float ball_speedx = arr_speed[index];
	index = rand() % 10;
	float ball_speedy = arr_speed[index];

	//СЧЕТ
	int leftPlayerScore = 0;
	int rightPlayerScore = 0;

	Font font;
	font.loadFromFile("ds-digib.ttf");

	Text leftPlayerScoreText;
	leftPlayerScoreText.setString(std::to_string(leftPlayerScore));//передать строку для отображения
	leftPlayerScoreText.setFont(font);
	leftPlayerScoreText.setCharacterSize(64);
	Text rightPlayerScoreText;
	rightPlayerScoreText.setString(std::to_string(rightPlayerScore));
	rightPlayerScoreText.setFont(font);
	rightPlayerScoreText.setCharacterSize(64);

	leftPlayerScoreText.setPosition(200.f, 10.f);
	rightPlayerScoreText.setPosition(600.f, 10.f);

	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		//1 Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				//тогда закрываем его
				window.close();
		}
		//2 Обновление объектов
		//шарик
		ball.move(ball_speedx, ball_speedy);
		if (ball.getPosition().x <= 0) {
			ball_speedx = -ball_speedx;
			rightPlayerScore++;
			rightPlayerScoreText.setString(std::to_string(rightPlayerScore));
		}
		if (ball.getPosition().x >= (WINDOW_WIDTH - 2 * ballRadius)) {
			ball_speedx = -ball_speedx;
			leftPlayerScore++;
			leftPlayerScoreText.setString(std::to_string(leftPlayerScore));
		}
		ball.move(ball_speedx, ball_speedy);
		//попал-вышел за вернхнюю или нижнюю границу
		if (ball.getPosition().y <= 0 || ball.getPosition().y >= (WINDOW_HEIGHT - 2 * ballRadius))
		{
			//скорость по оси у изменилась на противополжную
			ball_speedy = -ball_speedy;
		}
		//проверка нажатий клавиш
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			leftBatSpeedY = -batSpeed;
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			leftBatSpeedY = batSpeed;
		}
		if (Keyboard::isKeyPressed(Keyboard::R))
		{
			rightBatSpeedY = -batSpeed;
		}
		if (Keyboard::isKeyPressed(Keyboard::F)) {
			rightBatSpeedY = batSpeed;
		}
		//двигаем ракетку
		leftBat.move(0, leftBatSpeedY);
		//сразу обнуляем скорость
		leftBatSpeedY = 0.f;
		//двигаем ракетку
		rightBat.move(0, rightBatSpeedY);
		//сразу обнуляем скорость
		rightBatSpeedY = 0.f;
		if (leftBat.getPosition().y >= WINDOW_HEIGHT - batHeight)
		{
			leftBat.setPosition(batOffset, WINDOW_HEIGHT - batHeight);
		}
		if (leftBat.getPosition().y <= 0)
		{
			leftBat.setPosition(batOffset, 0);
		}
		leftBatSpeedY = 0.f;
		if (rightBat.getPosition().y >= WINDOW_HEIGHT - batHeight)
		{
			rightBat.setPosition(800 - batOffset, WINDOW_HEIGHT - batHeight);
		}
		if (rightBat.getPosition().y <= 0)
		{
			rightBat.setPosition(800 - batOffset, 0);
		}
		//3 Отрисовка окна
		//3.1 Очистка окна
		window.clear();
		//3.2 Отрисовка объектов (В ПАМЯТИ!)
		window.draw(leftBat);
		window.draw(rightBat);
		window.draw(ball);
		window.draw(leftPlayerScoreText);
		window.draw(rightPlayerScoreText);
		//3.3 вывод на экран
		window.display();
	}
	return 0;
}