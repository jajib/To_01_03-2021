#include <iostream>

struct Node
{
	int value;
	Node* next;	
};

struct List
{
	Node* first;
	Node* last;
	int len;	
};

int PrintNode(Node* node)
{
	std::cout << node->value << std::endl; 	
};

int PrintList(List* list)
{
	Node* buffer_node = list->first;
	while(buffer_node != nullptr)
	{
		std::cout << buffer_node->value << std::endl;
		buffer_node = buffer_node->next;
	}
};

List* CreateEmptyList()
{
	List* result = new List;
	
	result->first = nullptr;	
	result->last  = nullptr;
	result->len   = 0;

	return result;
};

int add_to_end (List* list_, int n)
{
	Node* last_element = new Node;
	last_element->value = n;
	last_element->next = nullptr;
	
	if (list_->len == 0)
	{
		list_->first = last_element;
	} else
	{
		list_->last->next = last_element;
	}
	
	list_->last  = last_element;
	list_->len += 1;	
};

List* CreateList(int* values_array, int array_len)
{
	List* new_list = CreateEmptyList();
	
	for (int cnt = 0; cnt < array_len; cnt++)
	{
		add_to_end(new_list, values_array[cnt]);
	}	
	
	return new_list;
};

int add_to_begin (List* list, int new_value)
{
	Node* new_node = new Node;
	new_node->value = new_value;
	new_node->next = list->first;
	list->first = new_node;
	list->len += 1;	
};

Node* find_by_index(List* list, int index) //index starts from 1
{
	Node* buffer_node = list->first;
	int cnt = 0;
	while(cnt < index - 1 && buffer_node != nullptr)
	{
		buffer_node = buffer_node->next;
		cnt++;
	}
	
	return buffer_node;
};

Node* add_i (List* list, int index, int new_value)
{
	Node* buffer = find_by_index(list, index - 1);
	if (buffer != nullptr)
	{
		Node* new_element = new Node;
		new_element->value = new_value;
	
		new_element->next = buffer->next;
		buffer->next = new_element;
		return new_element;
	} else
	{
		return buffer;
	}
};

int main ()
{
	int array [5] = {101, 202, 303, 404, 505};
	List list;
	list.first = nullptr;
	list.last = nullptr;
	list.len = 0;
	
	List* my_list = CreateEmptyList();
	add_to_end(my_list, 1);
	add_to_end(my_list, 20);
	
	List* my_list_2 = CreateList(array, 5);
	add_to_begin(my_list_2, 99);

	
	add_i(my_list_2, 2, 1000);
	PrintList(my_list_2);
	
	
	//PrintNode( find_by_index(my_list_2, 3) );
}
