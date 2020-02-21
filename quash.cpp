#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <array>
#include <queue>
#include <algorithm>



using namespace std;

class intPoint{
    public:
        int value;
        int count;
		int index;
        intPoint* point;
		intPoint() {
			value = 0;
			count = 1;
			index = 0;
			point = NULL;
		}

		//bool operator>(const intPoint& a);
		//bool operator<(const intPoint& a);
		//bool operator==(const intPoint& a);
		
			
};

bool operator>(const intPoint& a, const intPoint& b) {
	return a.value > b.value;
}

bool operator<(const intPoint& a, const intPoint& b) {
	return a.value < b.value;
}

bool operator==(const intPoint& a, const intPoint& b) {
	return a.value == b.value;
}



class minHeap{
    public:
		//std::priority_queue<intPoint> heap;
		vector<intPoint*> A;
	
		
		

		// return parent of A[i]
		// don't call this function if i is already a root node
		
		int PARENT(int i)
		{
			return (i - 1) / 2;
		}

		// return left child of A[i]	
		int LEFT(int i)
		{
			return (2 * i + 1);
		}

		// return right child of A[i]	
		int RIGHT(int i)
		{
			return (2 * i + 2);
		}

		/*
		void swap(intPoint*& a, intPoint*& b) {
			intPoint* temp = a;
			a = b;
			b = temp;

			int tempInt = a->index;
			a->index = b->index;
			b->index = tempInt;

		}
		*/
		

		void heapify_down(int i)
		{
			// get left and right child of node at index i
			int left = LEFT(i);
			int right = RIGHT(i);

			int smallest = i;

			// compare A[i] with its left and right child
			// and find smallest value
			if (left < size() && A[left]->value < A[i]->value)
				smallest = left;

			if (right < size() && A[right]->value < A[smallest]->value)
				smallest = right;

			// swap with child having lesser value and 
			// call heapify-down on the child
			if (smallest != i) {
				swap(A[i], A[smallest]);
				swap(A[i]->index, A[smallest]->index);
				heapify_down(smallest);
			}
		}

		void heapify_up(int i)
		{
			// check if node at index i and its parent violates 
			// the heap property
			if (i && A[PARENT(i)]->value > A[i]->value)
			{
				// swap the two if heap property is violated
				swap(A[i], A[PARENT(i)]);
				swap(A[i]->index, A[PARENT(i)]->index);

				// call Heapify-up on the parent
				heapify_up(PARENT(i));
			}
		}

		unsigned int size()
		{
			return A.size();

		}

		// function to check if heap is empty or not
		bool empty()
		{
			return size() == 0;
		}

		// insert key into the heap
		void push(intPoint* key){
			// insert the new element to the end of the vector
			
			A.push_back(key);
			

			
			

			// get element index and call heapify-up procedure
			int index = size() - 1;
			key->index = index;
			//cout << key.index;
			heapify_up(index);
			
		}

		// function to remove element with highest priority (present at root)
		void pop()
		{
			try {
				// if heap has no elements, throw an exception
				if (size() == 0)
					throw out_of_range("Vector<X>::at() : "
						"index is out of range(Heap underflow)");

				// replace the root of the heap with the last element
				// of the vector
				swap(A[0], A.back());
				A.pop_back();
			

				// call heapify-down on root node
				heapify_down(0);
			}
			// catch and print the exception
			catch (const out_of_range & oor) {
				cout << "\n" << oor.what();
			}
		}

		// function to return element with highest priority (present at root)
		intPoint* top()
		{
			try {
				// if heap has no elements, throw an exception
				if (size() == 0)
					throw out_of_range("Vector<X>::at() : "
						"index is out of range(Heap underflow)");

				// else return the top (first) element
				return A.at(0);	// or return A[0];
			}
			// catch and print the exception
			catch (const out_of_range & oor) {
				cout << "\n" << oor.what();
			}
		}

		void deleteAt(int a) {

			A[a]->value = -1000000;
			heapify_up(a);
			pop();
		
		}



};

class hashMap{
    public:

    std::array<std::list<intPoint>, 43> mainMap;

    int insert(intPoint& a);
    int deleteAt(int a, bool flag);
    int find(int a);

};

int hashMap::insert(intPoint& a){
	
	

	int bucket = a.value % 43;
	if (bucket < 0) {
		bucket += 43;
	}
	//bool flag = false;
	for (list<intPoint>::iterator i = mainMap[bucket].begin(); i != mainMap[bucket].end(); i++) {

		if (i->value == a.value) {
			i->count++;
			i->point->count++;
			return i->count;
		}

	}
		mainMap[bucket].emplace_front(a);
		//cout << a.point->value;
		return -1;
	
	
    
}

int hashMap::deleteAt(int a, bool flag){
    int bucket = a % 43;
	if (bucket < 0) {
		bucket += 43;
	}
	for(list<intPoint>::iterator i = mainMap[bucket].begin(); i != mainMap[bucket].end(); i++ ){
        if(i->value == a && i->count == 1){
			//cout << i->point->index;
			int ind = i->point->index;
			if (flag == true) {
				cout << "item successfully deleted\n";
			}
			else {
				cout << "min item ";
				cout << a;
				cout << " successfully deleted\n";
			}
			mainMap[bucket].erase(i);

			return ind;
        }
        else if(i->value == a && i->count > 1){

            i->count--;
			i->point->count--;
			if (flag == true) {
				cout << "item successfully deleted\n";
			}
			else {
				cout << "min item = ";
				cout << a;
				cout << ", count decremented, new count = ";
				cout << i->count;
				cout << "\n";
			}
			return -1;

        }
    }  
	return -2;
	
	

}

int hashMap::find(int a){
    int bucket = a % 43;
	if (bucket < 0) {
		bucket += 43;
	}
	bool temp = false;
    for(list<intPoint>::iterator i = mainMap[bucket].begin(); i != mainMap[bucket].end(); i++ ){
        
		if(i->value == a ){
			
			//cout << i->point->index;
		
				cout << "item found, count = ";
				cout << i->count;
				cout << "\n";
		
			temp = true;
			return i->count;
        }
		

    }
	if (temp == false) {
		cout << "item not found\n";
		//list<intPoint>::iterator i = mainMap[bucket].end();
			return -1;
	}
}


class quash{

public:
    
    minHeap m1;
    hashMap h1;

    friend void parseCommand(string a);
    void insert(int a);
    void lookup(int a);
    void deleteMin();
    void deleteAt(int a);
    void print();

 

};



void parseCommand(string a){

    
    quash q;
    vector<string> input;
    string temp = "";
    a.push_back(',');

    for(int i = 0; i < a.length(); i++){
        if(a[i] != ','){
           if(a[i] != ' '){
            temp += a[i];
           }
        }
        else {
            input.push_back(temp);
            temp ="";
        }
    }

    /*
    for(int i = 0; i < input.size(); i++){
        cout<<input[i];
        cout<<" ";
    }
    */
   
    for(int i = 0; i < input.size(); i++){

        if(input[i].find("insert") != string::npos){
            input[i].erase(0,6);
            q.insert(stoi(input[i]));
        }
        else if (input[i].find("lookup") != string::npos){
            input[i].erase(0,6);
            q.lookup(stoi(input[i]));
        }
        else if (input[i].find("deleteMin") != string::npos){
            q.deleteMin();
        } 
        else if (input[i].find("delete") != string::npos){
            input[i].erase(0,6);
            q.deleteAt(stoi(input[i]));
        } 
        else if (input[i].find("print") != string::npos){
            q.print();
        }                      
    }


    

}

void quash::insert(int a) {
	//cout<<"in insert";

	intPoint hashElem;
	intPoint* heapElem = new intPoint;
	hashElem.value = a;
	heapElem->value = a;
	hashElem.point = heapElem;
	heapElem->point = &hashElem;



	int dup = h1.insert(hashElem);
	if (dup == -1) {
		m1.push(heapElem);
		cout << "item successfully inserted, count = 1\n";
	}
	else {
		cout << "item successfully inserted, count = ";
		cout << dup;
		cout << "\n";
	}
}

void quash::lookup(int a){
   //cout<<"in lookup";
	h1.find(a);
}

void quash::deleteMin(){
    
	if (m1.A.empty() == true) {
		cout << "min item not present since table is empty\n";
		return;
	}
	intPoint* min = m1.top();
	//cout << min->value;

	int dup = h1.deleteAt(min->value, false);
	if (dup != -1) {

		m1.pop();

		return;

	}
	





}

void quash::deleteAt(int a){
    //cout<<"in deleteAt";
	int ind = h1.deleteAt(a, true);
	if (ind == -2) {
		cout << "item not present in table\n";

	}
	else if (ind > -1) {
		//cout << ind;
		m1.deleteAt(ind);
	}

}

void quash::print(){
	for (int i = 0; i < m1.A.size(); i++) {
		cout<< m1.A[i]->value;
		cout << " ";
	}
	cout << "\n";
}

int main(int argv, char** argc){

        if( argv != 2)  {
            return 1;
        }

        parseCommand(argc[1]);
        
        return 0;
}