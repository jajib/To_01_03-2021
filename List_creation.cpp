#include <iostream>

struct Node
{
	int value;
	Node* next;	
	
	Node(int new_n = 0, Node* new_next = nullptr)
	{
		value = new_n;
		next = new_next;
	}
};

struct List
{
	Node* first;
	Node* last;
	int len;
	
	List()
	{
		first = nullptr;
		last = nullptr;
		len = 0;
	}	
};

int PrintNode(Node* node)
{
	if (node == nullptr)
	{
		return -1;
	}
	
	std::cout << node->value << std::endl; 	
};

int PrintList(List* list)
{
	if (list == nullptr)
	{
		return -1;
	}
		
	Node* buffer_node = list->first;
	while(buffer_node != nullptr)
	{
		std::cout << buffer_node->value << std::endl;
		buffer_node = buffer_node->next;
	}
};

List* CreateEmptyList()
{
	List* result = new List();
	
	return result;
};

Node* add_to_end (List* list_, int n)
{
	if (list_ == nullptr)
	{
		return nullptr;
	}
	
	Node* last_element = new Node(n);
	
	if (list_->len == 0)
	{
		list_->first = last_element;
	} 
	else
	{
		list_->last->next = last_element;
	}
	
	list_->last  = last_element;
	list_->len += 1;	

	return last_element;
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

Node* add_to_begin (List* list, int new_value)
{
	if (list == nullptr)
	{
		return nullptr;
	}
	
	Node* new_node = new Node(new_value, list->first);
	
	list->first = new_node;
	
	if (list->len == 0)
	{
		list->last = new_node;
	}
	
	list->len += 1;	
	
	return new_node;
};

Node* find_by_index(List* list, int index)
{
	if (list == nullptr)
	{
		return nullptr;
	}
	
	Node* buffer_node = list->first;
	int cnt = 0;
	while(cnt < index && buffer_node != nullptr)
	{
		buffer_node = buffer_node->next;
		cnt++;
	}
	
	return buffer_node;
};

Node* add_i (List* list, int index, int new_value)
{
	if (list == nullptr)
	{
		return nullptr;
	}
	
	if (index > list->len)
	{
		return nullptr;
	}
	
	if (list->len == 0)
	{
		list->first = new Node(new_value);
		list->last = new Node(new_value);
		
		list->len = 1;
		
		return new Node(new_value);
	}
	
	if (index == list->len)
	{
		return nullptr;
	}
	
	if (index == 0)
	{
		return add_to_begin(list, new_value);
	}
	
	if (index == list->len-1)
	{
		return add_to_end(list, new_value);
	}
	
	Node* buffer = find_by_index(list, index-1);
	
	Node* new_element = new Node(new_value, buffer->next);
	
	buffer->next = new_element;
	list->len += 1;
	return new_element;
};

bool remove_node (List* list, Node* previous_node)
{
	if (list == nullptr || list->len == 0)
	{
		return false;
	}
	
	if (previous_node != nullptr)
	{	
		list->len -= 1;
		Node* to_free = previous_node->next;
		previous_node->next = previous_node->next->next;
		delete to_free;
		return true;
	} 
	else
	{
		return false;
	}
			
};

Node* del_i (List* list, int index)
{
	if (list == nullptr)
	{
		return nullptr;
	}
	
	if (index >= list->len)
	{
		return nullptr;
	}
	
	if (index == 0)
	{
		Node* del_element = list->first;
		
		list->first = list->first->next;
		
		if (list->len == 1)
		{
			list->last == nullptr;
		}
		
		list->len -= 1;
		
		return del_element;
	}
	
	if (index == list->len-1)
	{
		Node* del_element = list->last;
	
		if (list->len == 1)
		{
			list->first = nullptr;
			list->last = nullptr;
		}
		else
		{
			Node* prev_buffer = find_by_index(list, list->len-2);
			prev_buffer->next = nullptr;
			list->last = prev_buffer;
		}
		
		list->len -= 1;
		
		return del_element;
	}
	
	Node* buffer = find_by_index(list, index - 1);
	Node* buffer_del = nullptr;
	
	if(buffer != nullptr)
	{	
		buffer_del = buffer->next;
	}
	
	remove_node(list, buffer);
	
	return buffer_del;	
	
};

Node* find_by_value(List* list, int search_value)
{
	if (list == nullptr)
	{
		return nullptr;
	}
		
	Node* buffer = list->first;
	while(buffer->value != search_value && buffer != nullptr)
	{
		buffer = buffer->next;
	}	
	
	return buffer;
};

Node* find_previous_to_value(List* list, int search_value)
{
	if (list == nullptr)
	{
		return nullptr;
	}
	
	Node* buffer = list->first;
	while( (buffer != nullptr && buffer->next != nullptr) && buffer->next->value != search_value )
	{
		buffer = buffer->next;
	}	
	
	return buffer;
};

int get_index_by_value(List* list, int value)
{
	if (list == nullptr || list->len == 0)
	{
		return -1;
	}
	
	Node* buffer = list->first;
	int cnt = 0;
	
	while (buffer != nullptr && buffer->value != value)
	{
		buffer = buffer->next;
		cnt++;
	}
	
	return cnt;
}

Node* remove_value(List* list, int value)
{
	if (list == nullptr)
	{
		return nullptr;
	}
		
	return del_i(list, get_index_by_value(list, value));
};

List* copy_list(List* source)
{
	if (source == nullptr)
	{
		return nullptr;
	}
	
	List* ret = new List();
	Node* buffer = source->first;
	
	while(buffer != nullptr)
	{
		add_to_end(ret, buffer->value);
		buffer = buffer->next;
	}
	
	return ret;
}

List* reverse(List* source)
{
	if (source == nullptr)
	{
		return nullptr;
	}
	
	List* ret = new List();
	Node* buffer = source->first;
	
	while(buffer != nullptr)
	{
		add_to_begin(ret, buffer->value);
		buffer = buffer->next;
	}
	
	return ret;
}

List* merge (List* list_a, List* list_b)
{
	if (list_a == nullptr || list_b == nullptr)
	{
		return nullptr;
	}
	
	List* ret = new List();
	Node* buffer = list_a->first;
	
	while (buffer != nullptr)
	{
		add_to_end(ret, buffer->value);
		buffer = buffer->next;
	}
	
	buffer = list_b->first;
	
	while (buffer != nullptr)
	{
		add_to_end(ret, buffer->value);
		buffer = buffer->next;
	}
	
	return ret;
}

int delete_list(List* list_)
{
	if (list_ == nullptr)
	{
		return -1;
	}
	
	Node* buffer = list_->first;
	Node* temp_buffer;
	while (buffer != nullptr)
	{
		temp_buffer = buffer->next;
		buffer->value = 0;
		buffer->next = nullptr;
		buffer = temp_buffer;
	}
	
	list_->first = nullptr;
	list_->last = nullptr;
	list_ = nullptr;

	return 0l
}

int main ()
{
	
}
