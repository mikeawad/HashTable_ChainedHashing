#include <cassert>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "hash_chn.h"

Table::Table( )
{
   used = 0;
   for ( int i = 0; i < CAPACITY; i++ )
      table[i] = NULL;
}

void Table::insert( const RecordType& entry )
{
   bool alreadyThere;
   Node* nodePtr;

   assert( entry.key >= 0 );

   findPtr( entry.key, alreadyThere, nodePtr );
   if( !alreadyThere )
   {
      int i = hash( entry.key );      // get index of "bucket" where entry belongs
      // insert at beginning of list
      Node* temp = new Node;
      temp->rec = entry;      // copy record
      temp->next = table[i];
      table[i] = temp;
      used++;
   }
   else
   {
      // nodePtr points to existing record that should be updated
      nodePtr->rec = entry;
   }
}


int Table::hash( int key ) const
{
   return key % CAPACITY;
}

int Table::size( ) const
{
   return used;
}

// findPtr function
//     void findPtr( int key, bool& found, Node*& nodePtr ) const;
// Preconditions:  key >= 0
// Postconditions: If a record with the indicated key is in the table,
//    then found is true and nodePtr is set to point to that record.
//    Otherwise, found is false and nodePtr contains garbage.

void Table::findPtr( int key, bool& found, Node*& nodePtr ) const
{
   int i;
   Node* ptr;

   i = hash( key );
   ptr = table[i];
   //cout << "DEBUG: ptr = <" << ptr << ">" << endl;
   found = false;
   while ( !found && ptr != NULL )
   {
      //cout << "DEBUG: Loop entered : rec.key = " << ptr->rec.key  << " key = " << key << endl;
      if ( key == ptr->rec.key )
      {
         found = true;
         nodePtr = ptr;
      }
      ptr = ptr->next;
   }
   if ( !found )
      nodePtr = NULL;
}

void Table::find( int key, bool& found, RecordType& result ) const
{
   Node* nodePtr;

   assert( key >= 0 );

   findPtr( key, found, nodePtr );
   if ( found )
   {
      result = nodePtr->rec;
   }
}

/// erase function
/// This function is used to erase individual records from the table.
/// It does this by determining if the head node is the node to be deleted, if so,
/// delete and move. If the record is in the the middle or end of the linked list,
/// it will copy the contents of the head node into the node which is to be deleted,
/// then deletes the head node.
void Table::erase(  int key, bool& found, RecordType& result)
{
	Node *nodePtr,
		  *delPtr;

	findPtr( key, found, nodePtr );
	int i = hash(key);

	if(!found)
		cout << "Item not found in table." << endl;

	else if( found && (table[i] == nodePtr))
	{
		delPtr = table[i];
		table[i] = table[i]->next;
		delete delPtr;
		used--;
	}

	else
	{
		nodePtr->rec.key = table[i]->rec.key;
		nodePtr->rec.data = table[i]->rec.data;
		delPtr = table[i];
		table[i] = table[i]->next;
		delete delPtr;
		used--;
	}
}

/// print() function to print out the records in the hash table.
void Table::print() const
{
   Node* ptr;
   for (int i = 0; i < CAPACITY; i++)
   {  ptr = table[i];
      if (table[i] == NULL)continue;
      else
         while(ptr != NULL)
         {
            cout << "Key = " << ptr->rec.key << endl;
            cout << "Hash = " << hash(ptr->rec.key) << endl;
            cout << "Data = " << ptr->rec.data << endl << endl;
            ptr = ptr->next;
         }
   }
}
