#include"header.h"

void Queue::push(Cell c)
{
	data.push_back(c);
}
Cell Queue::pop()
{
	Cell pop_cell = data[0];
	data.erase(data.begin());
	return pop_cell;
}
void Queue::display()
{
	if (data.empty())
		cout << "The queue is empty" << endl;
	else
		for (auto a : data)
		{
			cout << a.value << " ";
		}
	cout << endl;
}

bool Queue::empty() {
	return data.empty();
}

int Queue::size() {
	return data.size();
}

Cell Queue::at(int i) {
	return data[i];
}

void Queue::swap(Cell* a, Cell* b)
{
	Cell t = *a;
	*a = *b;
	*b = t;
}

int Queue::partition(int low, int high)
{
	int pivot = data[low].heuristic;    // pivot 
	int i = low;  // Index of smaller element 

	for (int j = low+1; j <= high; j++)
	{
		// If current element is smaller than or 
		// equal to pivot
		if (data[j].heuristic > pivot)
		{
			i++;    // increment index of smaller element 
			swap(&data[i], &data[j]);
		}
	}
	swap(&data[i], &data[low]);
	return i;
}

void Queue::quickSort(int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		   at right place */
		int pi = partition(low, high);

		// Separately sort elements before 
		// partition and after partition 
		quickSort(low, pi);
		quickSort(pi + 1, high);
	}
}
