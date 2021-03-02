#ifndef BST_H
#define BST_H

#include <iostream>

using namespace std;

struct binaryNode
{
	int value;
	binaryNode* left;
	binaryNode* right;
};

class BST
{
	public:
		BST( );

		const int & findMin( ) const;
		const int & findMax( ) const;
		//void printTree( ostream & out = cout ) const;
		void print() const;
		void print( binaryNode* const & root ) const;
		bool search( const int & x );
		void insert( const int & x );
		//void insert( int && x );
		void remove( const int & x );
		unsigned compare() { return comCount; }

	private:
		binaryNode* rootPtr;
		unsigned comCount;

		bool search( const int & x , binaryNode* t );
		void insert( const int & x, binaryNode* & t );
		//void insert( int && x, binaryNode* & t );
		void remove( const int & x, binaryNode* & t );
		binaryNode* findMin( binaryNode* t ) const;
		binaryNode* findMax( binaryNode* t ) const;

}; //BST class

/***************
**CONSTRUCTORS**
***************/

//defualt constructor
BST::BST() {
	rootPtr = NULL;
}
//BST::BST

/*******************
**MEMBER FUNCTIONS**
*******************/

void BST::print() const {
	print( rootPtr );
	cout << endl;
}

void BST::print( binaryNode* const & root ) const {
	cout << "[" << root->value;
	if ( root->left != NULL || root->right != NULL ) {
		if (root->left != NULL)
			print( root->left );
		if ( root->right != NULL )
			print( root->right );
	}
	
	cout << "]";
}

bool BST::search( const int & x ) {
	return search( x , rootPtr );
}

bool BST::search( const int & x , binaryNode* t ) {
	if( t == NULL )
		return false;
	else if( x < t->value ) {
		return search( x, t->left );
	}
	else if( t->value < x ) {
		return search( x, t->right );
	}
	else
		return true; // Match
}

void BST::insert( const int & x ) {
	insert( x , rootPtr );
}

void BST::insert( const int & x, binaryNode * & t ) {
	if( t == NULL )
		t = new binaryNode{ x, NULL, NULL };
	else if( x < t->value ) {
		comCount++;
		insert( x, t->left );
	}
	else if( t->value < x ) {
		comCount++;
		insert( x, t->right );
	}
}

binaryNode* BST::findMin( binaryNode *t ) const{
	if( t == NULL )
		return NULL;
	if( t->left == NULL )
		return t;
	return findMin( t->left );
}

binaryNode* BST::findMax( binaryNode *t ) const{
	if( t == NULL )
		return NULL;
	if( t->right == NULL )
		return t;
	return findMin( t->right );
}

void BST::remove( const int & x ) {
	remove( x , rootPtr );
}


void BST::remove( const int & x, binaryNode * & t ) {
	if( t == NULL )
		return; // Item not found; do nothing
	if( x < t->value ) {
		remove( x, t->left );
	}
	else if( t->value < x ) {
		remove( x, t->right );
	}
	else if( t->left != NULL && t->right != NULL ) { // Two children
		t->value = findMax( t->left )->value;
		cout << "T value is " << t->value << endl;
		remove( t->value, t->left );
	}
	else {
		binaryNode *oldNode = t;
		t = ( t->left != NULL ) ? t->left : t->right;
		delete oldNode;
	}
}

#endif // BST_H
