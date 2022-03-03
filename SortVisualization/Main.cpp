#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>


class Sort {

private:
	int W = 720;
	int H = 480;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(W, H), "Sort Visualization", sf::Style::Close | sf::Style::Titlebar);

	std::vector<int> vec;
	int arrSize;
	int largest = *std::max_element(vec.begin(), vec.end());

	float rectangleWidth = (float)W / (arrSize * 2);
	float maxPercentage = ((float)H * .9) / largest;

	bool replay = false;

	int addToVec = 20;
	int delay = 10;


	void shuffle(std::vector<int>& _vec) {
		std::srand(time(NULL));
		for (int times = 0; times < 4; times++)
		{
			for (int i = 0; i < _vec.size(); i++)
			{
				int randNumber = rand() % _vec.size();
				swap(&_vec[randNumber], &_vec[i]);
			}
		}
	}

	void swap(int* x, int* y)
	{
		int temp = *x;
		*x = *y;
		*y = temp;
	}

	void bubbleSort(std::vector<int>& _vec)
	{
		int n = _vec.size();

		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++) {
				if (replay == true) break;
				control();

				window->clear();
				createRectangle(j, n - i);
				window->display();

				if (_vec[j] > _vec[j + 1])
					swap(&_vec[j], &_vec[j + 1]);
			}
		}
	}

	void createRectangle(int j, int n) {
		auto heightClamp = [this](int x) { return (std::fmax(H * .01, std::fmin(H, (maxPercentage * vec[x])))); };
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));

		for (int x = 0; x < arrSize; x++)
		{
			sf::VertexArray rectangle(sf::TriangleStrip, 4);
			if (x == j) {
				rectangle[0].color = sf::Color::Cyan;
				rectangle[1].color = sf::Color::Cyan;
				rectangle[2].color = sf::Color::Cyan;
				rectangle[3].color = sf::Color::Cyan;
			}
			else if (x == j + 1) {
				rectangle[0].color = sf::Color::Cyan;
				rectangle[1].color = sf::Color::Cyan;
				rectangle[2].color = sf::Color::Cyan;
				rectangle[3].color = sf::Color::Cyan;
			}
			else if (x == n) {
				rectangle[0].color = sf::Color::Yellow;
				rectangle[1].color = sf::Color::Yellow;
				rectangle[2].color = sf::Color::Yellow;
				rectangle[3].color = sf::Color::Yellow;
			}
			else {
				rectangle[0].color = sf::Color::Red;
				rectangle[1].color = sf::Color::Red;
				rectangle[2].color = sf::Color::Red;
				rectangle[3].color = sf::Color::Red;
			}
			if (x != 0) {

				rectangle[0].position = sf::Vector2f(rectangleWidth * .5 + 2 * x * rectangleWidth, H);
				rectangle[1].position = sf::Vector2f(rectangleWidth * .5 + 2 * x * rectangleWidth + rectangleWidth, H);
				rectangle[2].position = sf::Vector2f(rectangleWidth * .5 + 2 * x * rectangleWidth, H - heightClamp(x));
				rectangle[3].position = sf::Vector2f(rectangleWidth * .5 + 2 * x * rectangleWidth + rectangleWidth, H - heightClamp(x));
			}
			else
			{
				rectangle[0].position = sf::Vector2f(rectangleWidth * .5 + x * rectangleWidth, H);
				rectangle[1].position = sf::Vector2f(rectangleWidth * .5 + x * rectangleWidth + rectangleWidth, H);
				rectangle[2].position = sf::Vector2f(rectangleWidth * .5 + x * rectangleWidth, H - heightClamp(x));
				rectangle[3].position = sf::Vector2f(rectangleWidth * .5 + x * rectangleWidth + rectangleWidth, H - heightClamp(x));
			}

			window->draw(rectangle);

		}
	}

	void control() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			delay > 0 ? delay -= 100 : delay = 0;
			std::cout << delay << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			delay += 20;
			std::cout << delay << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			std::this_thread::sleep_for(std::chrono::microseconds(500));
			replay = true;
			shuffle(vec);
			bubbleSort(vec);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			std::this_thread::sleep_for(std::chrono::microseconds(500));

			for (int i = 0; i < addToVec; i++)
			{
				vec.push_back(std::rand());
			}

			replay = true;
			arrSize = vec.size();
			largest = *std::max_element(vec.begin(), vec.end());
			rectangleWidth = (float)W / (arrSize * 2);
			maxPercentage = ((float)H * .9) / largest;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && vec.size() > addToVec) {
			std::this_thread::sleep_for(std::chrono::microseconds(500));
			for (int i = 0; i < addToVec; i++)
			{
				vec.pop_back();
			}
			replay = true;
			arrSize = vec.size();
			largest = *std::max_element(vec.begin(), vec.end());
			rectangleWidth = (float)W / (arrSize * 2);
			maxPercentage = ((float)H * .9) / largest;

		}
	}

public:

	Sort(std::vector<int> _vec) : vec(_vec), arrSize(_vec.size()) {}

	bool render() {
		bubbleSort(vec);
		while (window->isOpen()) {
			control();

			sf::Event event;
			while (window->pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window->close();
			}

			if (replay == true) {
				std::this_thread::sleep_for(std::chrono::microseconds(500));
				replay = false;
				bubbleSort(vec);

			}

		}
		return true;
	}
};




int main(void) {

	std::vector<int> vec;
	std::srand(time(0));
	for (int i = 0; i < 20; i++)
	{
		vec.push_back(std::rand());

	}

	Sort sort(vec);
	sort.render();

	return 0;
}