#include "my_include.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>

void insert_pet(Pet_Node*& head)
{
    // 1. Create a new pet node
    // 2. Define a character array with the maximum name size (MAX_NAME_SIZE)
    // 3. Assign the ID of the new node by the next_id, then increase next_id by 1
    // 4. Request the user to input the name of pet
    // 5. Use strcpy() to assign the name of the new node by the input name
    // 6. Request the user to input integers for how cute, active, and tidy the pet is
    // 7. Assign the variables cute, active, and tidy with the corresponding user inputs
    // 8. Use the header node to check whether it is a empty list
    // 9. If it is a empty list, the next item of new pet node should point to NOTHING
    // 10. Otherwise, the next item of new pet node should point to the header node
    // 11. Finally, put the new pet node as a header node
	/* YOUR CODE HERE */

	if(head==NULL){
		head = new Pet_Node;
		head->ID = next_id;
		next_id++;
		char name[MAX_NAME_SIZE];
		cout << "Please Insert a name for your pet";
		cin >> name;
		cout << "Please enter cuteness/activeness/tidyness";
		cin >> head->cute >> head->active >> head->tidy;
		strcpy(head->name,name);
		head->next = NULL;		
	}else{		
		Pet_Node *temp = new Pet_Node;
		temp->ID = next_id;
		next_id++;
		char name[MAX_NAME_SIZE];
		cout << "Please Insert a name for your pet";
		cin >> name;
		cout << "Please enter cuteness/activeness/tidyness";
		cin >> temp->cute >> temp->active >> temp->tidy;
		strcpy(temp->name,name);
		temp->next = head;
		head = temp;
	}	
}

void delete_pet(Pet_Node*& head, const Pet_Node* pet)
{

    // 1. Check whether the pet node is the header node
    // 2. If it is the header node, the header node should now point to the next item of the current header node
    // 3. Otherwise,
    //    a) Find the previous pet node (Hints: Using a loop to transverse from the header node to just before the pet node)
    //    b) The next item of previous pet node should point to the next item of the pet node
    // 4. Finally, delete the pet node
   
	/* YOUR CODE HERE */
	Pet_Node* prev = NULL;
	Pet_Node* current = head;

	while(current->ID != pet->ID){
		prev = current;
		current = current->next;
	}
	if(current==head){
		head = head->next;
	}else{
		prev->next = current->next;
	}
	delete current;
}

const Pet_Node* best_match(const Pet_Node* head, int cute, int active, int tidy)
{

    // 1. Create a best pet node and the best pet node points to the header node
    // 2. Compute the value of dissimilarity from the user input criteria, i.e. cute, active, and tidy (Hints: using dissimilarity())
    // 3. Transverse the linked list
    //    a) Compute and compare the value of dissimilarity for each node
    //    b) Find the best pet node with the minimum dissimilarity value.
    // 4. Finally, return the best pet node
	/* YOUR CODE HERE */
	Pet_Node* bestfit = new Pet_Node;
	Pet_Node* current = head->next;
	int firstVal = abs(head->cute - cute) + abs(head->active - active) + abs(head->tidy - tidy);
	int bestVal = firstVal;
	
	while(current != NULL){
		int val = abs(current->cute - cute) + abs(current->active - active) + abs(current->tidy - tidy);
		if(val<bestVal){
			bestVal = val;
			bestfit = current;
		}
		current = current->next;
	}

	if(firstVal<=bestVal){
		return head;
	}else{
		return bestfit;
	}	
}


void view_pets(const Pet_Node* const head)
{
    // 1. If it is empty list, print out "There are no pets available!"
    // 2. Otherwise, transverse the linked list and use print_pet() to print out each node.
	/* YOUR CODE HERE */
	if(head==NULL){
		cout << "There are no pets available"<< endl;
	}else{
		print_pet(head);
		if(head->next != NULL){
			view_pets(head->next);
		}
	}
}


int main()
{
	Pet_Node* head = NULL;
	char c;
	
	while((c = get_menu_choice()) != '6')
	{
		switch(c)
		{
			case '1':
				insert_pet(head);
				break;
			case '2':
				view_pets(head);
				break;
			case '3':
				buy_pet(head);
				break;
			case '4':
				save_pets(head);
				break;
			case '5':
				load_pets(head);
				break;
			default:
				break;
		}
	}
	
	return 0;
}


char get_menu_choice()
{
	char c;
	cout << "--- Menu ---" << endl;
	cout << "1: Insert a pet" << endl;
	cout << "2: View pets" << endl;
	cout << "3: Buy a pet" << endl;
	cout << "4: Save pets" << endl;
	cout << "5: Load pets" << endl;
	cout << "6: Exit" << endl;
	cout << "Please select one from the above: ";
	cin >> c;
	return c;
}

void print_pet(const Pet_Node* pet)
{
	cout << endl;
	cout << "ID: " << pet->ID << endl;
	cout << "Name: " << pet->name << endl;
	cout << "Cute: " << pet->cute << endl;
	cout << "Active: " << pet->active << endl;
	cout << "Tidy: " << pet->tidy << endl;
	cout << endl;
}


// Similarity computation

int absolute(int a)
{
	return (a<0) ? -a : a;
}

int dissimilarity(const Pet_Node* pet, int cute, int active, int tidy)
{
	return (absolute(pet->cute - cute) + absolute(pet->active - active) + absolute(pet->tidy - tidy));
}

// The buy_pet function

void buy_pet(Pet_Node*& head)
{
	if(head==NULL) 
	{
		cout << endl << "There are no pets available!" << endl << endl;
		return;
	}
	
	int cute, active, tidy;
	const Pet_Node* best_pet;
	
	cout << "Enter how cute, active, and tidy the pet you wish to be: ";
	cin >> cute >> active >> tidy;
	best_pet = best_match(head, active, cute, tidy);
	
	print_pet(best_pet);
	cout << "Do you wish to buy this pet? ('Y'/'y' for yes, any input otherwise): ";
	char c; cin >> c;
	if(c=='Y' || c=='y')
	{
		delete_pet(head, best_pet);
		cout << endl << "Congratulations on your new pet!" << endl << endl;
	}
	else cout << endl << "Maybe next time!" << endl << endl ;
}

// Saving to file

void save_pet_to_file(const Pet_Node* pet, ofstream& fout)
{
	fout << endl;
	fout << pet->ID << endl;
	fout << pet->name << endl;
	fout << pet->cute << endl;
	fout << pet->active << endl;
	fout << pet->tidy << endl;
	fout << endl;
}

void save_pets(const Pet_Node* const head)
{
	if(head == NULL) 
	{
		cout << endl << "There are no pets to save!" << endl << endl;
		return;
	}
	
	ofstream fout("pets.txt");
	
	fout << next_id << endl;
	for(const Pet_Node* p = head; p!=NULL; p=p->next)
		save_pet_to_file(p, fout);
	
	fout.close();
	
	cout << endl << "Pets saved!" << endl << endl;
}

// Loading from file

bool load_pet_from_file(Pet_Node*& pet, ifstream& fin)
{
	pet = new Pet_Node;

	fin >> pet->ID;
	
	if(fin.eof())
	{
		delete pet;
		return false;
	}
	
	fin >> pet->name;
	fin >> pet->cute;
	fin >> pet->active;
	fin >> pet->tidy;
	pet->next = NULL;
	
	return true;
}

void load_pets(Pet_Node*& head)
{	
	if(head != NULL)
	{
		cout << endl << "Cannot load pets - database not empty!" << endl << endl;
		return;
	}
	
	ifstream fin("pets.txt");
	
	if(!fin)
	{
		cout << endl << "There are no pets to load!" << endl << endl;
		return;
	}
	
	fin >> next_id;
	
	head = new Pet_Node;
	load_pet_from_file(head, fin);
	
	Pet_Node* p;
	while(load_pet_from_file(p, fin))
	{
		p->next = head;
		head = p;
	}
	
	cout << endl << "Pets loaded!" << endl << endl;
	
	fin.close();
}


