#pragma once
#define NULL 0
#define BST_INSERT_WITHCOMMAN

template<typename T>
struct BST {
	T key;
	BST *p;
	BST *left;
	BST *right;
	BST(T value) :key(value), p(NULL), left(NULL), right(NULL) {}
};


template<typename T>
BST<T>* BST_Search(BST<T> *t, T value) {
	if (t == NULL || t->key == value) {
		return t;
	}
	if (value < t->key) {
		BST_Search(t->left, value);
	}
	else {
		BST_Search(t->right, value);
	}
}

template<typename T>
BST<T>* Iterative_BST_Search(BST<T> *t, T value) {
	if (t == NULL || t->key == value) {
		return t;
	}
	while (t && t->key != value) {
		if (t->key < value) {
			t = t->right;
		}
		else {
			t = t->left;
		}
	}
	return t;
}

template<typename T>
BST<T>* BST_Minimum(BST<T> *t) {
	if (!t) {
		return NULL;
	}
	while (t->left) {
		t = t->left;
	}
	return t;
}

template<typename T>
BST<T>* BST_Maximum(BST<T> *t) {
	if (!t) {
		return NULL;
	}
	while (t->right) {
		t = t->right;
	}
	return t;
}

template<typename T>
BST<T>* BST_Predecessor(BST<T> *t, T value) {
	BST<T> *pNode = BST_Search(t, value);
	if (pNode == NULL) {
		return NULL;
	}
	if (pNode->left) {
		return BST_Maximum(pNode->left);
	}
	while (pNode->p && pNode == pNode->p->left){
		pNode = pNode->p;
	}
	return pNode->p;
}




template<typename T>
BST<T>* BST_Successor(BST<T> *t, T value) {
	BST<T> *pNode = BST_Search(t, value);
	if (pNode == NULL) {
		return NULL;
	}
	if (pNode->right) {
		return BST_Minimum(pNode->right);
	}
	while (pNode->p && pNode == pNode->p->right) {
		pNode = pNode->p;
	}
	return pNode->p;
}







template<typename T>
void BST_Insert(BST<T> *t, T value) {
	BST<T> *tmp = new BST<T>(value);
	if (t == NULL) {
		t = tmp;
	}
	else {
		BST<T> *in = t;
		while (t) {
			in = t;
			if (t->key > value) {
				t = t->left;
			}
#ifdef BST_INSERT_WITHCOMMAN
			else {
				t = t->right;
			}
#elif
			else if (t->key == value) {
				std::cout << "same value has been inserted to BST" << std::endl;
				return;
			}
			else {
				t = t->right;
			}
#endif
		}
		if (in->key > value) {
			in->left = tmp;
			tmp->p = in;
		}
		else {
			in->right = tmp;
			tmp->p = in;
		}
	}
}

template<typename T>
BST<T>* BST_Delete(BST<T> *t, T value) {
	BST<T> *vNode = Iterative_BST_Search(t, value);
	BST<T> *root;
	if (vNode == NULL) {
		return NULL;
	}
	if (vNode->left == NULL && vNode->right == NULL) {//1
		if (vNode->p != NULL) {
			if (vNode == vNode->p->left) {
				vNode->p->left = NULL;
			}
			else {
				vNode->p->right = NULL;
			}
		}
		if (vNode == t) {
			root = NULL;
		}
		else {
			root = t;
		}
		delete vNode;
		return root;
	}
	else if (vNode->left != NULL && vNode->right == NULL) {//2
		vNode->left->p = vNode->p;
		if (vNode->p != NULL) {
			if (vNode == vNode->p->left) {
				vNode->p->left = vNode->left;
			}
			else {
				vNode->p->right = vNode->left;
			}			
		}
		if (vNode == t) {
			root = vNode->left;
		}
		else {
			root = t;
		}
		delete vNode;
		return root;
	}
	else if (vNode->left == NULL && vNode->right != NULL) {//3
		vNode->right->p = vNode->p;
		if (vNode->p != NULL) {
			if (vNode == vNode->p->left) {
				vNode->p->left = vNode->right;
			}
			else {
				vNode->p->right = vNode->right;
			}			
		}
		if (vNode == t) {
			root = vNode->right;
		}
		else {
			root = t;
		}
		delete vNode;
		return root;
	}
	else {
		BST<T> *bt = BST_Minimum(vNode->right);
		if (bt == vNode->right) {
			vNode->right->p = vNode->p;
			if (vNode->p != NULL) {
				if (vNode == vNode->p->left) {
					vNode->p->left = vNode->right;
				}
				else {
					vNode->p->right = vNode->right;
				}
			}
			vNode->left->p = bt;
			bt->left = vNode->left;
		}
		else {
			bt->p->left = bt->right;
			if (bt->right) {
				bt->right->p = bt->p->left;
			}

			bt->p = vNode->p;
			if (vNode->p != NULL) {
				if (vNode == vNode->p->left) {
					vNode->p->left = bt;
				}
				else {
					vNode->p->right = bt;
				}
			}
			bt->right = vNode->right;
			vNode->right->p = bt;

			vNode->left->p = bt;
			bt->left = vNode->left;

		}
		if (vNode == t) {
			root = bt;
		}
		else {
			root = t;
		}
		delete vNode;
		return root;
	}
}


