#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>

#include "Object.h"
#include "GameDefaultConstant.h"

#pragma region Node

class Node
{
public:
	Node();
	Node(T6Rect* range);
	Node(T6Rect* range, vector<Object*>& objectList);
	~Node();

	void assign(vector<Object*>& objectList);
	vector<Object*> getObjects(const T6Rect& cameraRange);
	void release();

private:
	bool isSplitable();
	T6Rect* caculateSubNodeRange(int index, const T6Rect& baseRect);

private:
	vector<Object*> nodeObjects_;

	// Sub node indexes signed as
	// 2 3
	// 0 1
	Node* subNode_[4];

	T6Rect* range_;
};

#pragma endregion

#pragma region Tree

class QuadTree
{
public:
	QuadTree();
	QuadTree(T6Rect* range);
	~QuadTree();

	void assign(vector<Object*>& objectList);
	void update();
	void draw(T6Rect range);

private:
	void removeDuplicate(vector<Object*>& objectList);
	vector<Object*> getObjectInRange(T6Rect range);

private:
	Node* root_;
	vector<Object*> assignedObjects_;
};

#pragma endregion

#endif
