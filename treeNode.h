#ifndef TREENode_H
#define TREENode_H

#include <iostream>

class treeNode 
{
	public:
		treeNode( const int& );
		void setValue( const int& );
		int& getValue();
		void setRightPtr( treeNode* );
		treeNode* getRightPtr() const;
		void setLeftPtr( treeNode* );
		treeNode* getLeftPtr() const;
	private:
		int value;
		treeNode* rightPtr;
		treeNode* leftPtr;

}; //treeNode class

treeNode::treeNode( const int& value )
{
  this->value = value;
  this->rightPtr = NULL;
  this->leftPtr = NULL;
} //treeNode::treeNode

void treeNode::setValue( const int& value )
{
  this->value = value;
} //treeNode::setvalue

int& treeNode::getValue()
{
  return value;
} //treeNode::getvalue

void treeNode::setRightPtr( treeNode* rightPtr )
{
  this->rightPtr = rightPtr;
} //treeNode::setRightPtr

treeNode* treeNode::getRightPtr() const
{
  return rightPtr;
} //treeNode::getRightPtr

void treeNode::setLeftPtr( treeNode* leftPtr )
{
  this->leftPtr = leftPtr;
} //treeNode::getLeftPtr

treeNode* treeNode::getLeftPtr() const
{
  return leftPtr;
} //treeNode::getLeftPtr

#endif // treeNode_H

