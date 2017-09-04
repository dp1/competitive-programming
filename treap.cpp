/* Treap implementation
 * supports find/insert/erase as well as split/merge
 */

#include <cstdlib>
#include <utility>
using namespace std;

template<typename T>
struct Treap
{
	struct Node
	{
		Node() { left = right = this; }
		Node(T v, int p, Node *l, Node *r) { prior = p; val = v; left = l; right = r; }
		T val;
		int prior;
		Node *left, *right;
	};
	
	Node *bottom = new Node();
	Node *root = bottom;
	
	Treap() { srand(42); }
	~Treap() { destroy(root); delete bottom; }
	
	void destroy(Node *r)
	{
		if(r == bottom) return;
		destroy(r->left);
		destroy(r->right);
		delete r;
	}
	
	pair<Node *, Node *> split(Node *r, T key)
	{
		if(r == bottom) return make_pair(bottom, bottom);
		if(key <= r->val)
		{
			auto t = split(r->left, key);
			r->left = t.second;
			return make_pair(t.first, r);
		}
		else
		{
			auto t = split(r->right, key);
			r->right = t.first;
			return make_pair(r, t.second);
		}
	}
	
	Node *merge(Node *a, Node *b)
	{
		if(a == bottom || b == bottom) return (a == bottom) ? b : a;
		if(a->prior > b->prior)
		{
			a->right = merge(a->right, b);
			return a;
		}
		else
		{
			b->left = merge(a, b->left);
			return b;
		}
	}
	
	bool find(T val) { return find(val, root); }
	void insert(T val) { root = insert(val, rand(), root); }
	void erase(T val) { root = erase(val, root); }
	
	bool find(T val, Node *r)
	{
		if(r == bottom) return false;
		if(val < r->val) return find(val, r->left);
		if(val > r->val) return find(val, r->right);
		return true;
	}
	
	Node *insert(T val, int prior, Node *r)
	{
		if(r == bottom) return new Node(val, prior, bottom, bottom);
		if(prior > r->prior)
		{
			auto t = split(r, val);
			return new Node(val, prior, t.first, t.second);
		}
		if(val < r->val) r->left = insert(val, prior, r->left);
		if(val > r->val) r->right = insert(val, prior, r->right);
		return r;
	}
	
	Node *erase(T val, Node *r)
	{
		if(r == bottom) return bottom;
		if(val < r->val) r->left = erase(val, r->left);
		else if(val > r->val) r->right = erase(val, r->right);
		else return merge(r->left, r->right);
		return r;
	}
};
