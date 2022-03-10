#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
#include <fstream>


class Sort {

private:
	int W = 720;
	int H = 480;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(W, H), "Sort Visualization", sf::Style::Close | sf::Style::Titlebar);
	sf::Text* text = new sf::Text;
	sf::Font* font = new sf::Font;
	std::vector<int> vec;
	int arrSize;
	int largest = *std::max_element(vec.begin(), vec.end());

	float rectangleWidth = (float)W / (arrSize * 2);
	float maxPercentage = ((float)H * .9) / largest;

	bool replay = false;

	int addToVec = 20;
	int delay = 10;


	void swap(int* x, int* y)
	{
		int temp = *x;
		*x = *y;
		*y = temp;
	}
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
	void sortSettings(int cyanRectangle, int yellowRectangle) {
		control();
		window->clear();
		createRectangle(cyanRectangle, yellowRectangle);
		*text = setText(sortChooseTxt);
		window->draw(*text);
		window->display();
	}

	class BubbleSort {

	public:

		Sort& parent;

		BubbleSort(Sort& _parent) : parent(_parent) {};

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
				if (parent.replay == true) return;
				for (int j = 0; j < n - i - 1; j++) {
					if (parent.replay == true) return;
					parent.sortSettings(j, n - i);

					if (_vec[j] > _vec[j + 1])
						swap(&_vec[j], &_vec[j + 1]);
				}
			}
		}
	};
	class InsertionSort {

	public:

		Sort& parent;
		InsertionSort(Sort& _parent) : parent(_parent) {};

		void insertionSort(std::vector<int>& _vec) {
			int key, j;

			for (int i = 1; i < _vec.size(); i++) {
				key = _vec[i];
				j = i - 1;
				while (j >= 0 && _vec[j] > key) {
					if (parent.replay == true) return;
					parent.sortSettings(j, i);

					_vec[j + 1] = _vec[j];
					j--;

				}

				if (parent.replay == true) return;
				parent.sortSettings(j, i);

				_vec[j + 1] = key;

				if (i == _vec.size() - 1) {
					parent.sortSettings(j, i);
				}


			}
		}

	};
	class SelectionSort {

	public:

		Sort& parent;
		SelectionSort(Sort& _parent) : parent(_parent) {};

		void swap(int* x, int* y)
		{
			int temp = *x;
			*x = *y;
			*y = temp;
		}

		void selectionSort(std::vector<int>& _vec) {

			int minIndex;
			for (int i = 0; i < _vec.size() - 1; i++)
			{
				minIndex = i;
				for (int j = i + 1; j < _vec.size(); j++)
				{
					if (_vec[minIndex] > _vec[j])
						minIndex = j;

					if (parent.replay == true) return;
					parent.sortSettings(j, i);
				}
				swap(&_vec[i], &_vec[minIndex]);
			}

		}

	};
	class QuickSort {

	public:

		Sort& parent;
		QuickSort(Sort& _parent) : parent(_parent) {};

		void swap(int* x, int* y)
		{
			int temp = *x;
			*x = *y;
			*y = temp;
		}

		int partition(std::vector<int>& _vec, int low, int high) {

			int pivot = _vec[high];
			int i = low - 1;
			if (parent.replay == true) return(i + 1);

			for (int j = low; j < high; j++) {
				if (parent.replay == true) return(i + 1);

				if (_vec[j] < pivot)
				{
					i++;
					swap(&_vec[i], &_vec[j]);
				}
				parent.sortSettings(j, j);
				if (parent.replay == true) return(i + 1);
			}
			swap(&_vec[i + 1], &_vec[high]);

			return i + 1;

		}

		void quickSort(std::vector<int>& _vec, int low, int high) {
			if (low < high) {
				if (parent.replay == true) return;
				int pi = partition(_vec, low, high);


				quickSort(_vec, low, pi - 1);
				quickSort(_vec, pi + 1, high);

			}
			parent.sortSettings(0, 0);
		}



	};
	class MergeSort {

	public:

		Sort& parent;
		MergeSort(Sort& _parent) : parent(_parent) {};

		void merge(std::vector<int>& _vec, int low, int mid, int high) {
			if (parent.replay == true) return;
			int i, j, k;

			int n1 = mid - low + 1;
			int n2 = high - mid;

			int* L = new int[n1];
			int* R = new int[n2];

			for (i = 0; i < n1; i++) {
				L[i] = _vec[low + i];
			}
			for (j = 0; j < n2; j++) {
				R[j] = _vec[mid + j + 1];
			}

			i = 0; j = 0; k = low;

			while (i < n1 && j < n2) {



				if (L[i] <= R[j]) {
					_vec[k] = L[i];
					i++;

				}
				else {
					_vec[k] = R[j];

					j++;
				}
				k++;


				parent.sortSettings(k, k);
				if (parent.replay == true) return;
			}

			while (i < n1) {
				_vec[k] = L[i];
				i++;
				k++;

			}
			while (j < n2) {
				_vec[k] = R[j];
				j++;
				k++;

			}

			k++;
		}

		void mergeSort(std::vector<int>& _vec, int low, int high) {


			if (low < high) {
				if (parent.replay == true) return;
				int mid = (high + low) / 2;
				mergeSort(_vec, low, mid);
				mergeSort(_vec, mid + 1, high);
				merge(_vec, low, mid, high);

			}
		}
	};
	enum SortsEnum {
		chooseBubbleSort = 1,
		chooseInsertionSort = 2,
		chooseSelectionSort = 3,
		chooseQuickSort = 4,
		chooseMergeSort = 5
	};


	SortsEnum sortChoose = chooseBubbleSort;
	std::string sortChooseTxt = "BubbleSort";

	void sortThem(std::vector<int>& _vec, SortsEnum _sortChoose = chooseBubbleSort) {

		switch (_sortChoose)
		{
		case Sort::chooseBubbleSort:
			bubbleSortClass.bubbleSort(_vec);
			break;
		case Sort::chooseInsertionSort:
			insertionSortClass.insertionSort(_vec);
			break;
		case Sort::chooseSelectionSort:
			selectionSortClass.selectionSort(_vec);
			break;
		case Sort::chooseQuickSort:
			quickSortClass.quickSort(_vec, 0, _vec.size() - 1);
			break;
		case Sort::chooseMergeSort:
			mergeSortClass.mergeSort(_vec, 0, _vec.size() - 1);
			break;
		default:
			break;
		}
	}
	sf::Text setText(sf::String _string) {

		if (!font->loadFromFile("Fonts/arial.ttf"))
		{
			throw("Couldn't load the font");
		}


		text->setFont(*font);
		text->setString(_string);
		text->setCharacterSize(24);
		text->setFillColor(sf::Color::White);
		text->setPosition(sf::Vector2f(0.f, 0.f));

		return (*text);
	}
	void createRectangle(int j, int n) {
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
				rectangle[2].position = sf::Vector2f(rectangleWidth * .5 + 2 * x * rectangleWidth, H - (maxPercentage * vec[x]));
				rectangle[3].position = sf::Vector2f(rectangleWidth * .5 + 2 * x * rectangleWidth + rectangleWidth, H - (maxPercentage * vec[x]));
			}
			else
			{
				rectangle[0].position = sf::Vector2f(rectangleWidth * .5 + x * rectangleWidth, H);
				rectangle[1].position = sf::Vector2f(rectangleWidth * .5 + x * rectangleWidth + rectangleWidth, H);
				rectangle[2].position = sf::Vector2f(rectangleWidth * .5 + x * rectangleWidth, H - (maxPercentage * vec[x]));
				rectangle[3].position = sf::Vector2f(rectangleWidth * .5 + x * rectangleWidth + rectangleWidth, H - (maxPercentage * vec[x]));
			}

			window->draw(rectangle);

		}
	}
	void controlSettings(int sleepMS) {
		std::this_thread::sleep_for(std::chrono::milliseconds(sleepMS));
		replay = true;
		shuffle(vec);
	}
	void control() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			std::this_thread::sleep_for(std::chrono::microseconds(500));
			sortChooseTxt = "BubbleSort";
			sortChoose = chooseBubbleSort;
			controlSettings(250);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			std::this_thread::sleep_for(std::chrono::microseconds(500));
			sortChooseTxt = "InsertionSort";
			sortChoose = chooseInsertionSort;
			controlSettings(250);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			std::this_thread::sleep_for(std::chrono::microseconds(500));
			sortChooseTxt = "SelectionSort";
			sortChoose = chooseSelectionSort;
			controlSettings(250);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
			std::this_thread::sleep_for(std::chrono::microseconds(500));
			sortChooseTxt = "QuickSort";
			sortChoose = chooseQuickSort;
			controlSettings(250);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
			std::this_thread::sleep_for(std::chrono::microseconds(500));
			sortChooseTxt = "MergeSort";
			sortChoose = chooseMergeSort;
			controlSettings(250);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
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
			controlSettings(500);
			sortThem(vec, sortChoose);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			std::this_thread::sleep_for(std::chrono::microseconds(500));

			for (int i = 0; i < addToVec; i++)
			{
				vec.push_back(std::rand());
			}
			std::cout << "Array size = " << vec.size() << std::endl;
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
			std::cout << "Array size = " << vec.size() << std::endl;
			replay = true;
			arrSize = vec.size();
			largest = *std::max_element(vec.begin(), vec.end());
			rectangleWidth = (float)W / (arrSize * 2);
			maxPercentage = ((float)H * .9) / largest;

		}
	}


public:

	BubbleSort bubbleSortClass;
	InsertionSort insertionSortClass;
	SelectionSort selectionSortClass;
	QuickSort quickSortClass;
	MergeSort mergeSortClass;

	Sort(std::vector<int> _vec) :
		vec(_vec),
		arrSize(_vec.size()),
		bubbleSortClass(*this),
		insertionSortClass(*this),
		selectionSortClass(*this),
		quickSortClass(*this),
		mergeSortClass(*this) {};

	bool render() {

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
				sortThem(vec, sortChoose);
			}
			else {
				window->clear();
				createRectangle(0, 0);
				window->draw(*text);
				window->display();
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