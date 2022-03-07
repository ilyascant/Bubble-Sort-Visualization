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


	class BubbleSort {

	public:

		Sort& parent;

		BubbleSort(Sort& _parent) : parent(_parent) {};

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
					if (parent.replay == true) break;
					parent.control();

					parent.window->clear();
					parent.createRectangle(j, n - i);
					parent.window->display();

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
					_vec[j + 1] = _vec[j];
					j--;

					//////////////////
					if (parent.replay == true) break;
					parent.control();

					parent.window->clear();
					parent.createRectangle(j, i);
					parent.window->display();
					////////////////////
				}
				_vec[j + 1] = key;

				//////////////
				if (i == _vec.size() - 1) {

					parent.window->clear();
					parent.createRectangle(j, i);
					parent.window->display();
				}
				//////////////


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

					///////////////////////////////
					parent.control();

					parent.window->clear();
					parent.createRectangle(j, i);
					parent.window->display();
					///////////////////////////////
				}
				swap(&_vec[i], &_vec[minIndex]);
			}

		}



	};
	class QuickSort { /// CALISMIYOR

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

			for (int j = low; j < high; j++) {

				if (_vec[j] < pivot)
					i++;

			}
			swap(&_vec[i + 1], &_vec[high]);

			return i + 1;

		}

		void quickSort(std::vector<int>& _vec, int low, int high) {
			if (low < high) {

				int pi = partition(_vec, low, high);

				quickSort(_vec, low, pi - 1);
				quickSort(_vec, pi + 1, high);



			}
			///////////////////////////////
			parent.control();

			parent.window->clear();
			parent.createRectangle(0, 0);
			parent.window->display();
			///////////////////////////////
		}



	};
	class MergeSort {

	public:

		Sort& parent;
		MergeSort(Sort& _parent) : parent(_parent) {};

		void merge(std::vector<int>& _vec, int low, int mid, int high) {
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

				parent.control();
				parent.window->clear();
				parent.createRectangle(k, k);
				parent.window->display();
				k++;

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
			parent.control();
			parent.window->clear();
			parent.createRectangle(k, k);
			parent.window->display();
			k++;

		}

		void mergeSort(std::vector<int>& _vec, int low, int high) {


			if (low < high) {
				int mid = (high + low) / 2;

				mergeSort(_vec, low, mid);
				mergeSort(_vec, mid + 1, high);
				merge(_vec, low, mid, high);


			}

		}

	};

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
			bubbleSortClass.shuffle(vec);
			bubbleSortClass.bubbleSort(vec);
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
		//bubbleSortClass.bubbleSort(vec);
		//insertionSortClass.insertionSort(vec);
		//selectionSortClass.selectionSort(vec);
		quickSortClass.quickSort(vec, 0, vec.size() - 1);
		//mergeSortClass.mergeSort(vec, 0, vec.size() - 1);






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
				//bubbleSortClass.bubbleSort(vec);
				//insertionSortClass.insertionSort(vec);
				//selectionSortClass.selectionSort(vec);
				quickSortClass.quickSort(vec, 0, vec.size() - 1);
				//mergeSortClass.mergeSort(vec, 0, vec.size() - 1);



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