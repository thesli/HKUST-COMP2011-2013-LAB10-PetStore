#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

const int MAX_NAME_SIZE = 20;

struct Pet_Node
{
	unsigned int ID;
	char name[MAX_NAME_SIZE];
	unsigned int cute;
	unsigned int active;
	unsigned int tidy;
	Pet_Node* next;
};

char get_menu_choice();
void print_pet(const Pet_Node* pet);
int absolute(int a);
int dissimilarity(const Pet_Node* pet, int cute, int active, int tidy);
void insert_pet(Pet_Node*& head);
void view_pets(const Pet_Node* const head);
void delete_pet(Pet_Node*& head, const Pet_Node* pet);
const Pet_Node* best_match(const Pet_Node* head, int cute, int active, int tidy);
void buy_pet(Pet_Node*& head);
void save_pet_to_file(const Pet_Node* pet, ofstream& fout);
void save_pets(const Pet_Node* const head);
bool load_pet_from_file(Pet_Node*& pet, ifstream& fin);
void load_pets(Pet_Node*& head);
