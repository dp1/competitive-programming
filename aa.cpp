/* AA tree implementation
 * basically a binary 2-3 B-tree
 * http://user.it.uu.se/~arnea/ps/simp.pdf
 */

template<typename T>
struct AATree
{
	struct Node
	{
		Node() { level = 0; left = right = this; }
		Node(T v, Node *l, Node *r) { level = 1;  val = v; left = l; right = r; }
		T val;
		int level;
		Node *left, *right;
	};
	
	Node *bottom = new Node();
	Node *deleted = bottom, *last = bottom, *root = bottom;
	
	~AATree() { destroy(root); delete bottom; }
	
	void destroy(Node *r)
	{
		if(r == bottom) return;
		destroy(r->left);
		destroy(r->right);
		delete r;
	}
	
	Node *skew(Node *r)
	{
		if(r != bottom && r->left->level == r->level)
		{
			Node *t = r->left;
			r->left = t->right;
			t->right = r;
			return t;
		}	
		return r;
	}
	
	Node *split(Node *r)
	{
		if(r != bottom && r->right->right->level == r->level)
		{
			Node *t = r->right;
			r->right = t->left;
			t->left = r;
			t->level++;
			return t;
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
		if(r->left->level == r->level && r->right->level == r->level) r->level++;
		else r = split(skew(r));
		return r;
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
		
		if(r->left->level < r->level - 1 || r->right->level < r->level - 1)
		{
			r->level--;
			if(r->right->level > r->level) r->right->level--;
			r = skew(r);
			r->right = skew(r->right);
			r->right->right = skew(r->right->right);
			r = split(r);
			r->right = split(r->right);
		}
		return r;
	}
};
