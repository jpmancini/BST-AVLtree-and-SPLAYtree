#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>

using namespace std;

struct splayNode
{
	int value;
	splayNode* left;
	splayNode* right;
};

class Splay
{
	public:
		Splay( );

		//void printTree( ostream & out = cout ) const;
		void print() const;
		void print( splayNode* const & root ) const;
		void insert( const int & x );
		//void insert( int && x );
		void remove( const int & x );
		void splay( const int & x );
		bool contains( const int & x );
		unsigned compare() { return comCount; }

	private:
		splayNode* rootPtr;
		splayNode* nullNode;
		unsigned comCount;

		bool contains( const int & x , splayNode* t );
		void splay( const int & x , splayNode* & t );
		void rotateWithLeftChild( splayNode* & k2 );
		void rotateWithRightChild( splayNode* & k2 );

}; //Splay class

/***************
**CONSTRUCTORS**
***************/

//defualt constructor
Splay::Splay() {
	nullNode = new splayNode;
	nullNode->left = nullNode->right = nullNode;
	rootPtr = nullNode;
}
//Splay::Splay

/*******************
**MEMBER FUNCTIONS**
*******************/

void Splay::print() const {
	print( rootPtr );
	cout << endl;
}

void Splay::print( splayNode* const & root ) const {
	cout << "[" << root->value;
	if ( root->left != nullNode || root->right != nullNode ) {
		if (root->left != nullNode)
			print( root->left );
		if ( root->right != nullNode )
			print( root->right );
	}
	
	cout << "]";
}

bool Splay::contains( const int & x ) {
	return contains( x , rootPtr );
}

bool Splay::contains( const int & x , splayNode* t ) {
	if( t == NULL )
		return false;
	else if( x < t->value ) {
		return contains( x, t->left );
	}
	else if( t->value < x ) {
		return contains( x, t->right );
	}
	else
		return true; // Match
}

void Splay::insert( const int & x ) {
	static splayNode* newNode = NULL;

	if( newNode == NULL )
		newNode = new splayNode{ x , NULL , NULL };
	newNode->value = x;

	if( rootPtr == nullNode ) {
		newNode->left = newNode->right = nullNode;
		rootPtr = newNode;
	}
	else {
		splay( x );
		if( x < rootPtr->value ) {
			comCount++;
			newNode->left = rootPtr->left;
			newNode->right = rootPtr;
			rootPtr->left = nullNode;
			rootPtr = newNode;
		}
		else
		if( x > rootPtr->value ) {
			comCount++;
			newNode->right = rootPtr->right;
			newNode->left = rootPtr;
			rootPtr->right = nullNode;
			rootPtr = newNode;
		}
		else
			return;
	}

	//cout << rootPtr->value << " " << rootPtr->left->value << " " << rootPtr->right->value << endl;
	newNode = NULL; // So next insert will call new
}

void Splay::remove( const int & x ) {
	if( !contains( x ) ) {
		return; // Item not found; do nothing
	}

	// If x is found, it will be splayed to the root by contains
	splayNode *newTree;

	if( rootPtr->left == nullNode )
		newTree = rootPtr->right;
	else {
		// Find the maximum in the left subtree
		// Splay it to the root; and then attach right child
		newTree = rootPtr->left;
		splay( x, newTree );
		newTree->right = rootPtr->right;
	}
	delete rootPtr;
	rootPtr = newTree;
}

void Splay::splay( const int & x ) {
	splay( x , rootPtr );
}

void Splay::splay( const int & x , splayNode* & t ) {
	splayNode* leftTreeMax;
	splayNode* rightTreeMin;
	static splayNode header;

	header.left = header.right = nullNode;
	leftTreeMax = rightTreeMin = &header;

	nullNode->value = x;

	for ( ; ; ) {
		if( x < t->value ) {
			if( x < t->left->value )
				rotateWithLeftChild( t );
			if( t->left == nullNode )
				break;
			rightTreeMin->left = t;
			rightTreeMin = t;
			t = t->left;
		}
		else if( x > t->value ) {
			if( x > t->right->value )
				rotateWithRightChild( t );
			if( t->right == nullNode )
				break;
			leftTreeMax->right = t;
			leftTreeMax = t;
			t = t->right;
		}
		else
			break;
	}

	leftTreeMax->right = t->left;
	rightTreeMin->left = t->right;
	t->left = header.right;
	t->right = header.left;

}

void Splay::rotateWithLeftChild( splayNode * & k2 ) {
	splayNode *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2 = k1;
}

void Splay::rotateWithRightChild( splayNode * & k2 ) {
	splayNode *k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2 = k1;
}

#endif // Splay_H
