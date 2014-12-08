#include <iostream>
#include <assert.h>
#include <cmath>

using namespace std;

/**
 * Holds an array of floating point numbers. The constructor accepts an integer
 * argument and dynamically alocates an array of floats to hold that many 
 * numbers. The following methods are available as the public API for 
 * this class:
 * 	- store() 		: Store a number in any element of this array 
 * 	- retrieve() 	: Retrive a number from any element of this array 
 * 	- highest()		: Return the highest value stored in this array 
 * 	- lowest()		: Return the lowest value stored in this array 
 * 	- average() 	: Return the average of all items in this array
 *
 **/
class NumberArray {

	private:
		// Used for averaging so it only counts numbers initialized with store()
		int numElements;

		// Manually keep track of length/size for pointer arithmetic
		int array_size;

		// The i'th entry is set to true when a number is initialized with 
		// store() in that position. Used to check whether numElements should 
		// be incremented.
		bool *has_been_set;

		// The actual underlying array
		float *contents;

	public:

		// Constructor: Dynamically allocates an array of size arr_size
		NumberArray(int arr_size) {
			this->numElements = 0;
			this->array_size = arr_size;
			contents = new float[arr_size]();
			has_been_set = new bool[arr_size]();
		}

		// Send a message to stdout for testing purpose (to see it works)
		~NumberArray() {
			cout << "Destructor called succesfully." << endl;
			delete(contents);
		}

		// Store 'value' at array[index]. 
		// Returns true if value is successfully stored
		bool store(float value, int index) {

			// Prevent out-of-bound segfault
			if (index > this->array_size) {
				return false;
			} else {
				*(this->contents + index) = value;

				// Is this the first time this index has been set?
				if(*(has_been_set + index) == false) {
					this->numElements++;
					*(has_been_set + index) = true;
				}
				return true;
			}
		}

		float retrieve(int index) {

			// Don't allow out-of-bounds or 0-valued indices that haven't been
			// set with store() yet.
			if (index > array_size || !has_been_set[index])
				return -1;
			else 
				return *(this->contents + index);
		}

		float highest() {

			// Initialize the highest so it always reflects 
			// some number actually in the array, even if 
			// everything else is lower.
			float highest_float = *(this->contents);

			for (int i = 0; i < array_size; i++) {
				float a_i = *(this->contents + i);
				if (a_i > highest_float)
					highest_float = a_i;
			}
			return highest_float;
		}

		float lowest() {

			// See note on highest() about initialization
			float lowest_float = *(this->contents);

			for (int i = 0; i < array_size; i++) {
				float a_i = *(this->contents + i);
				if (a_i < lowest_float)
					lowest_float = a_i;
			}
			return lowest_float;
		}

		float average() {
			float total = 0;
			for(int i = 0; i < this->array_size; i++) {
				total += *(this->contents + i);
			}
			return total / numElements;
		}

};

// Helper method for testing floating point "equality".
bool eq(float a, float b) {
	float e = .001;
	return abs(b-a) < e;
}

int main(void) {

	NumberArray *n = new NumberArray(5);

	// Run through some known states to make sure everything's 
	// consistent with what we would expect.
	cout << "Running tests..." << endl;

	assert(eq(n->retrieve(3), -1));

	// One number: Should be the highest, lowest, and average
	n->store(3.1, 2);
	assert(eq(n->retrieve(2), 3.1));
	assert(eq(n->lowest(), 0));
	assert(eq(n->highest(), 3.1));
	assert(eq(n->average(), 3.1));

	// Should change lowest and average
	n->store(-1.9, 4);
	assert(eq(n->retrieve(4), -1.9));
	assert(eq(n->lowest(), -1.9));
	assert(eq(n->highest(), 3.1));
	assert(eq(n->average(), (3.1 - 1.9) / 2));

	// Should replace highest and change average
	n->store(2.1, 2);
	assert(eq(n->retrieve(2), 2.1));
	assert(eq(n->lowest(), -1.9));
	assert(eq(n->highest(), 2.1));
	assert(eq(n->average(), (2.1 - 1.9) / 2));

	// Insert the first 5 natural numbers
	for(int i = 0; i < 5; i++)
		n->store(i + 1, i);

	// Ensure every insert went into the proper place
	assert(eq(n->retrieve(0), 1));
	assert(eq(n->retrieve(1), 2));
	assert(eq(n->retrieve(2), 3));
	assert(eq(n->retrieve(3), 4));
	assert(eq(n->retrieve(4), 5));

	// Shouldn't be able to access an out-of-bounds index
	assert(eq(n->retrieve(5), -1));

	// Should equal known average of 5 numbers
	assert(eq(n->average(), 3));

	// Highest and lowest are known
	assert(eq(n->highest(), 5));
	assert(eq(n->lowest(), 1));

	// Call destructor
	delete(n);

	cout << "Tests passed." << endl;

	cout << "Exiting program." << endl;
	return 0;
}
