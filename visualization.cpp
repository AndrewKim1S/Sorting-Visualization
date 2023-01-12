#include "visualization.h"


visualization::visualization(int width, int length) {
		this->width = width;
		this->length = length;
		state = State::RUN;

		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
		window = new sf::RenderWindow(sf::VideoMode(width, length, desktop.bitsPerPixel), "Sorting Visualization");
		window->setFramerateLimit(60);
		window->setVerticalSyncEnabled(false);
		window->setPosition(sf::Vector2i(200, 200));

		createList();

		font = new sf::Font();
		assert(font->loadFromFile("util/PlatNomor-eZ2dm.otf"));		

		info = new sf::Text();
		info->setFont(*font);
		info->setFillColor(sf::Color::White);
		info->setCharacterSize(18);
		info->setString("Sorting Algorithm  ...  List Sorted");
		info->setPosition(sf::Vector2f(width/28, length/30));
}

visualization::~visualization() {
		delete window;
		delete font;
}

bool visualization::isClosed() {
		return !window->isOpen();
}

void visualization::createList() {
		objectWidth =  width / numberOfObjs;
		double upperBound = 0.65 * length;
		double incrementFactor = upperBound / numberOfObjs;
		double index = 0.0;
		for(int i = 0; i < numberOfObjs; i++) {
				index += incrementFactor;
				double value = index;
				sortableObject s = sortableObject(value, objectWidth);
				s.setPosition(objectWidth * i, length - value);
				objectsToSort.push_back(s);
		}
}

void visualization::randomizeList() {
		info->setString("Sorting Algorithm  ...  List Randomized");
		for(int i = 0; i < numberOfObjs*3; i++) {
				int randIndex1 = rand() % (numberOfObjs);
				int randIndex2 = rand() % (numberOfObjs);
				while(randIndex1 == randIndex2) {
						randIndex2 = rand() % (numberOfObjs);
				}
				switchObjects(randIndex1, randIndex2);
		}
}

void visualization::run() {
		switch(state) {
				case State::RUN:
						pollEvents();
						render();
						break;
				case State::BUBBLESORT:
						info->setString("Bubble Sort  ...  Sorting In Progress");
						bubbleSort();
						completionAnimation();
						break;
				case State::SELECTIONSORT:
						info->setString("Selection Sort  ...  Sorting In Progress");
						selectionSort();
						completionAnimation();
						break;
				case State::INSERTIONSORT:
						info->setString("Insertion Sort  ...  Sorting In Progress");
						insertionSort();
						completionAnimation();
						break;
				case State::MERGESORT:
						info->setString("Merge Sort  ...  Sorting In Progress");
						mergeSort(0, numberOfObjs - 1);
						completionAnimation();
						break;
				case State::QUICKSORT:
						info->setString("Quick Sort  ...  Sorting In Progress");
						quickSort(0, numberOfObjs - 1);
						completionAnimation();
						break;
				default:
						break;
		}
}

void visualization::pollEvents() {
		while(window->pollEvent(event)) {
				switch(event.type) {
						case sf::Event::Closed:
								window->close();
								break;
						case sf::Event::KeyPressed:
								if(event.key.code == sf::Keyboard::Escape) {
										window->close();
								} else if(event.key.code == sf::Keyboard::R) {
										state = State::RUN;
										randomizeList();
								} else if(event.key.code == sf::Keyboard::B) {
										state = State::BUBBLESORT;
								} else if(event.key.code == sf::Keyboard::S) {
										state = State::SELECTIONSORT;
								} else if(event.key.code == sf::Keyboard::I) {
										state = State::INSERTIONSORT;
								} else if(event.key.code == sf::Keyboard::M) {
										state = State::MERGESORT;
								} else if(event.key.code == sf::Keyboard::Q) {
										state = State::QUICKSORT;
								}
						default:
								break;
				}
		}
}

void visualization::render() {
		window->clear(sf::Color(32, 32, 32));
		window->draw(*info);
		for(int i = 0; i < numberOfObjs; i++) {
				objectsToSort[i].render(*window);
		}
		window->display();
}

void visualization::switchObjects(int index1, int index2) {
		sortableObject obj1 = objectsToSort[index1];
		sortableObject obj2 = objectsToSort[index2];
		objectsToSort[index1].setPosition(obj2.getXPos(), length - obj1.getValue());
		objectsToSort[index2].setPosition(obj1.getXPos(), length - obj2.getValue());
				
		sortableObject temp = objectsToSort[index1];
		objectsToSort[index1] = objectsToSort[index2];
		objectsToSort[index2] = temp;
}

void visualization::completionAnimation() {
		state = State::RUN;
		info->setString("Sorting Algorithm ... Complete");
		clock.restart();
		bool animationComplete = false;
		for(int i = 0; i < numberOfObjs; i++) {
				objectsToSort[i].blinkAnimation();
		}
		render();
		while(!animationComplete) {
				if(clock.getElapsedTime().asMilliseconds() > 200) {
						for(int i = 0; i < numberOfObjs; i++) {
								objectsToSort[i].setOriginalColor();
						}
						render();
						animationComplete = true;
				}
		}
}

void visualization::bubbleSort() {
		for(int i = 0; i < numberOfObjs; i++){
				pollEvents();
				if(state != State::BUBBLESORT) {
						break;
				}
				for(int k = 0; k < numberOfObjs - 1; k++){
						sortableObject j = objectsToSort[k];
						if(j.getValue() > objectsToSort[k+1].getValue()) {
								switchObjects(k, k+1);
								render();
						}
				}
		}
}

void visualization::selectionSort() {
		for(int i = 0; i < numberOfObjs; i++){
				pollEvents();
				if(state != State::SELECTIONSORT){
						break;
				}
				int minIndex = i;
				for(int k = i+1; k < numberOfObjs; k++){
						if(objectsToSort[k].getValue() < objectsToSort[minIndex].getValue()){
								minIndex = k;
						}
				}	if(minIndex != i){
						switchObjects(i, minIndex);
						render();
				}
		}
}

void visualization::insertionSort() {
		for(int i = 0; i < numberOfObjs; i++){
				pollEvents();
				if(state != State::INSERTIONSORT) {
						break;
				}
				int k = i-1;
				int value = objectsToSort[i].getValue();
				sortableObject test = objectsToSort[i];
				while(objectsToSort[k].getValue() > value && k >= 0){
						sortableObject temp = objectsToSort[k+1];
						objectsToSort[k+1] = objectsToSort[k];
						objectsToSort[k+1].setPosition(temp.getXPos(), 
								length - objectsToSort[k+1].getValue());
						k--;
						render();
				} 
				double XPos = objectsToSort[k+1].getXPos();
				objectsToSort[k+1] = test;
				objectsToSort[k+1].setPosition(XPos, length - test.getValue());
		} 
}

void visualization::mergeSort(int start, int end) {
		if(start >= end){
				return;
		}
		int mid = start + (end - start) / 2;
		mergeSort(start, mid);
		mergeSort(mid+1, end);
		merge(start, mid, end);
}

void visualization::merge(int start, int mid, int end) {
		pollEvents();
		if(state != State::MERGESORT) {
				return;
		}
		std::vector<sortableObject> left(mid - start + 1);
		std::vector<sortableObject> right(end - mid);

		for(size_t i = 0; i < left.size(); i++) {
				left[i] = objectsToSort[i + start];

		} for(size_t k = 0; k < right.size(); k++) {
				right[k] = objectsToSort[k + mid + 1];
		
		}
		size_t indexLeft = 0, indexRight = 0;
		int indexMerged = start;

		while(indexLeft < left.size() && indexRight < right.size()){
				if(left[indexLeft].getValue() <= right[indexRight].getValue()) {
						double xPos = objectsToSort[indexMerged].getXPos();
						objectsToSort[indexMerged] = left[indexLeft];
						objectsToSort[indexMerged].setPosition(xPos, length - 
								left[indexLeft].getValue());
						indexLeft++;
						render();
				} else {
						double xPos = objectsToSort[indexMerged].getXPos();
						objectsToSort[indexMerged] = right[indexRight];
						objectsToSort[indexMerged].setPosition(xPos, length - 
								right[indexRight].getValue());
						indexRight++;
						render();
				}
				indexMerged++;
		}
		while(indexLeft < left.size()){
				double xPos = objectsToSort[indexMerged].getXPos();
				objectsToSort[indexMerged] = left[indexLeft];
				objectsToSort[indexMerged].setPosition(xPos, length - 
						left[indexLeft].getValue());
				indexMerged++;
				indexLeft++;
				render();
		}	while(indexRight < right.size()){
				double xPos = objectsToSort[indexMerged].getXPos();
				objectsToSort[indexMerged] = right[indexRight];
				objectsToSort[indexMerged].setPosition(xPos, length - 
						right[indexRight].getValue());
				indexMerged++;
				indexRight++;
				render();
		}
}

void visualization::quickSort(int low, int high) {
		if(low >= high){
				return;
		} 
		int index = partition(low, high);
		quickSort(low, index - 1);
		pollEvents();
		if(state != State::QUICKSORT){
				return;
		}
		quickSort(index + 1, high);
}

int visualization::partition(int low, int high) {
		sortableObject pivot = objectsToSort[high];
		int j = low-1;
		for(int i = low; i < high; i++){
				if(objectsToSort[i].getValue() < pivot.getValue()){
						j++;
						switchObjects(i, j);
						render();
				}
		}
		switchObjects(j+1, high);
		render();
		return j+1;
}
