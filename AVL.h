#ifndef AVL_H
#define AVL_H

#include <iostream>

using namespace std;

struct AVLNode
{
	int value;
	int height;
	AVLNode* left;
	AVLNode* right;
};

class AVL
{
	public:
		AVL( );

		int height ( AVLNode* t );
		const int & findMin( ) const;
		const int & findMax( ) const;
		//void printTree( ostream & out = cout ) const;
		void print() const;
		void print( AVLNode* const & root ) const;
		bool search( const int & x );
		void insert( const int & x );
		//void insert( int && x );
		void remove( const int & x );
		unsigned compare() { return comCount; }

	private:
		AVLNode* rootPtr;
		static const int ALLOWED_IMBALANCE = 1;
		unsigned comCount;

		bool search( const int & x , AVLNode* t );
		void insert( const int & x, AVLNode* & t );
		//void insert( int && x, AVLNode* & t );
		void remove( const int & x, AVLNode* & t );
		AVLNode* findMin( AVLNode* t ) const;
		AVLNode* findMax( AVLNode* t ) const;

		void balance( AVLNode* & t );
		void rotateWithLeftChild( AVLNode* & k2 );
		void rotateWithRightChild( AVLNode* & k2 );
		void doubleWithLeftChild( AVLNode* & k3 );
		void doubleWithRightChild( AVLNode* & k3 );

}; //AVL class

/***************
**CONSTRUCTORS**
***************/

//defualt constructor
AVL::AVL() {
	rootPtr = NULL;
}
//AVL::AVL

/*******************
**MEMBER FUNCTIONS**
*******************/

void AVL::print() const {
	print( rootPtr );
	cout << endl;
}

void AVL::print( AVLNode* const & root ) const {
	cout << "[" << root->value;
	if ( root->left != NULL || root->right != NULL ) {
		if (root->left != NULL)
			print( root->left );
		if ( root->right != NULL )
			print( root->right );
	}
	
	cout << "]";
}

bool AVL::search( const int & x ) {
	return search( x , rootPtr );
}

bool AVL::search( const int & x , AVLNode* t ) {
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

int AVL::height( AVLNode* t ){
	return t == NULL ? -1 : t->height;
}

void AVL::insert( const int & x ) {
	insert( x , rootPtr );
}

void AVL::insert( const int & x, AVLNode * & t ) {
	if( t == NULL )
		t = new AVLNode{ x, NULL, NULL };
	else if( x < t->value ) {
		comCount++;
		insert( x, t->left );
	}
	else if( t->value < x ) {
		comCount++;
		insert( x, t->right );
	}

	balance( t );
}

AVLNode* AVL::findMin( AVLNode *t ) const{
	if( t == NULL )
		return NULL;
	if( t->left == NULL )
		return t;
	return findMin( t->left );
}

AVLNode* AVL::findMax( AVLNode *t ) const{
	if( t == NULL )
		return NULL;
	if( t->right == NULL )
		return t;
	return findMin( t->right );
}

void AVL::remove( const int & x ) {
	remove( x , rootPtr );
}


void AVL::remove( const int & x, AVLNode * & t ) {
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
		remove( t->value, t->left );
	}
	else {
		AVLNode *oldNode = t;
		t = ( t->left != NULL ) ? t->left : t->right;
		delete oldNode;
	}

	balance( t );
}

void AVL::balance( AVLNode* & t ) {
	if( t == NULL )
		return;

	if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
		if( height( t->left->left ) >= height( t->left->right ) )
			rotateWithLeftChild( t );
		else
			doubleWithLeftChild( t );
	}
	
	if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
		if( height( t->right->right ) >= height( t->right->left ) )
			rotateWithRightChild( t );
		else
			doubleWithRightChild( t );
	}

	t->height = max( height( t->left ), height( t->right ) ) + 1;
}

void AVL::rotateWithLeftChild( AVLNode* & k2 ) {
	AVLNode *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
	k1->height = max( height( k1->left ), k2->height ) + 1;
	k2 = k1;
}

void AVL::doubleWithLeftChild( AVLNode* & k3 ) {
	rotateWithRightChild( k3->left );
	rotateWithLeftChild( k3 );
}

void AVL::rotateWithRightChild( AVLNode* & k2 ) {
	AVLNode *k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max( height( k2->right ), height( k2->left ) ) + 1;
	k1->height = max( height( k1->right ), k2->height ) + 1;
	k2 = k1;
}

void AVL::doubleWithRightChild( AVLNode* & k3 ) {
	rotateWithLeftChild( k3->right );
	rotateWithRightChild( k3 );
}

#endif // AVL_H
