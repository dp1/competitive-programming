/* AVL tree implementation
 * supports the classical find/insert/erase operations of a set
 */

#include <algorithm>
using namespace std;

template<typename T>
struct AVLTree
{
	struct Node
	{
		Node() { height = 0; left = right = this; }
		Node(T v, Node *l, Node *r) { height = 1;  val = v; left = l; right = r; }
		void recalc() { height = max(left->height, right->height) + 1; }
		int balance() { return right->height - left->height; }
		T val;
		int height;
		Node *left, *right;
	};
	
	Node *bottom = new Node();
	Node *deleted = bottom, *last = bottom, *root = bottom;
	
	~AVLTree() { destroy(root); delete bottom; }
	
	void destroy(Node *r)
	{
		if(r == bottom) return;
		destroy(r->left);
		destroy(r->right);
		delete r;
	}
	
	Node *rotateleft(Node *r)
	{
		Node *t = r->right;
		r->right = t->left;
		t->left = r;
		r->recalc();
		t->recalc();
		return t;
	}
	
	Node *rotateright(Node *r)
	{
		Node *t = r->left;
		r->left = t->right;
		t->right = r;
		r->recalc();
		t->recalc();
		return t;
	}
	
	Node *rebalance(Node *r)
	{
		r->recalc();
		if(r->balance() > 1)
		{
			if(r->right->balance() < 0)
				r->right = rotateright(r->right);
			r = rotateleft(r);
		}
		else if(r->balance() < -1)
		{
			if(r->left->balance() > 0)
				r->left = rotateleft(r->left);
			r = rotateright(r);
		}
		return r;
	}
	
	bool find(T val) { return find(val, root); }
	void insert(T val) { root = insert(val, root); }
	void erase(T val) { root = erase(val, root); }
	
	bool find(T val, Node *r)
	{
		if(r == bottom) return false;
		if(val < r->val) return find(val, r->left);
		if(val > r->val) return find(val, r->right);
		return true;
	}
	
	Node *insert(T val, Node *r)
	{
		if(r == bottom) return new Node(val, bottom, bottom);
		if(val < r->val) r->left = insert(val, r->left);
		if(val > r->val) r->right = insert(val, r->right);
		return rebalance(r);
	}
	
	Node *erase(T val, Node *r)
	{
		if(r == bottom) return bottom;
		last = r;
		if(val < r->val) r->left = erase(val, r->left);
		else deleted = r, r->right = erase(val, r->right);
		
		if(r == last)
		{
			if(deleted != bottom && deleted->val == val)
			{
				deleted->val = last->val;
				deleted = bottom;
				Node *t = last->right;
				delete last;
				return t;
			}
			return r;
		}
		
		return rebalance(r);
	}
};
