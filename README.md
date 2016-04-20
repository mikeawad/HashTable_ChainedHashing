Be sure to read through Chapter 12 section 12.7 of the textbook before starting this assignment. 

Below you will find C++ code for two different implementations of a hash table.

The first implementation is a simple hash table that uses linear probing to resolve collisions. In this version the data is stored directly in an array, so the number of entries is limited by the size of the array.

The second implementation uses chained hashing to resolve collisions. Each element in the array is a pointer to a linked list that stores all data that hashes to that index. So the number of entries in the table is limited only by the amount of memory that you can dynamically allocate.

Note: the chained-hashing version of the Table class really should have a destructor, copy constructor and overloaded assignment operator. You do not need to write these functions. You should be able to do this assignment and test your code without these functions.

Neither of these implementations has a delete operation to delete an entry. For each implementation, do the following.

Study the implementation and your textbook to be sure that you understand how it works.
Add a function that deletes an entry as follows. Be sure to include documentation for your function in the class header file. 
void erase(int key);    
Preconditions:  key >= 0     
Postconditions: If a record with the specified key exists in the table, then     
that record has been removed; otherwise the table is unchanged.
Modify the driver program so that you can test your delete function.
See important hints at the end of this page.
Submit all your code for each of the two implementations.

Sample code. Note that depending on your browser settings, the code may not display correctly in your browser. But you should be able to copy the code to your local machine and view it in your C++ editor.

Hash Table with Linear Probing

Driver program drv_hwlp.cpp

Header hash_lp.h

Implementation hash_lp.cpp

Hash Table with Chained Hashing

Driver program drv_hwch.cpp

Header hash_chn.h

Implementation hash_chn.cpp

Hints:

It is important to realize that the insert function will allow you to add a new entry to the table, or to update an existing entry in the table.
For the linear probing version, notice that the code to insert an item has two searches. The insert() function calls function findIndex() to search the table to see if the item is already in the table. If the item is not in the table, a second search is done to find the position in the table to insert the item. Adding the ability to delete an entry will require that the insertion process be modified. When searching for an existing item, be sure that the search does not stop when it comes to a location that was occupied but is now empty because the item was deleted. When searching for a position to insert a new item, use the first empty position - it does not matter if the position has ever been occupied or not. 
For the chained hashing version, the easiest node to delete in a linked-list is the head node. Instead of deleting a node in the middle of the list, you can copy the data from the head node into the node to be deleted, then delete the head node.
For debugging purposes, you may want to add a function to the class to print the entire table. For example, this function prints a table for the linear probing version:
void Table::print( )
{   
    cout << "The hash table is: " << endl;   
    cout << "Index  Key    Data" << endl;   
    for( int i=0; i < CAPACITY; i++ )   
    {      
        cout << setw(5) << i           
               << setw(5) << table[i].key;     
        if ( table[i].key != -1 ) 
            cout  << setw(8) << table[i].data;      
        cout << endl;    
    }   
    cout << endl;
}
Be sure to remove this function before you turn in your assignment.
Upload all source files including your driver program.
