#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include <SFML/System.hpp>
#include "sortableObject.h"

#define numberOfObjs 150

class visualization {
		
		public:
				enum State {
						RUN,
						BUBBLESORT,
						SELECTIONSORT,
						INSERTIONSORT,
						MERGESORT,
						QUICKSORT
				};

				visualization(int width, int length);
				~visualization();
				bool isClosed();
				void createList();
				void randomizeList();

				void run();
				void pollEvents();
				void render();

				void switchObjects(int index1, int index2);
				void completionAnimation();

				void bubbleSort();
				void selectionSort();
				void insertionSort();
				void mergeSort(int start, int end);
				void merge(int start, int mid, int end);
				void quickSort(int low, int high);
				int partition(int low, int high);

		private:
				int width;
				int length;
				double objectWidth;
				std::vector<sortableObject> objectsToSort;
				State state;

				sf::RenderWindow* window;
				sf::Event event;
				sf::Font* font;
				sf::Text* info;
				sf::Clock clock;
};
