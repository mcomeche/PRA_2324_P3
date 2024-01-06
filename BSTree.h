
#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename V>
class BSTree {
    private:
        //miembros privados
        int nelem;
        BSNode<V> *root;

        BSNode<V>* search(BSNode<V>* n, V e) const{
                if(n == nullptr)
                        throw std::runtime_error("No encontrado");
                else if(n->elem == e)
                        return n;
                else if (n->elem > e)
                        return search(n->left, e);
                else{
			return search(n->right, e);
		}
        }
        BSNode<V>* insert(BSNode<V>* n, V e){
                if(n == nullptr){
                        return new BSNode<V>(e);
		
		}
                else if(n->elem == e){
                       	throw std::runtime_error("Duplicado");
		}
                else if(n->elem < e)
                        n->right = insert(n->right, e);
                else{
                        n->left = insert(n->left, e);
		}
                return n;
        }
        void print_inorder(std::ostream &out, BSNode<V>* n) const{
                if(n != nullptr){
                        print_inorder(out, n->left);
                        out<<n->elem<<" ";
                        print_inorder(out, n->right);
                }
                else
                        out<<"";
        }


        BSNode<V>* remove(BSNode<V>* n, V e){
                if(n == nullptr)
                        throw std::runtime_error("Vacio");
                else if(n->elem < e)
                        n->right = remove(n->right, e);
                else if(n->elem > e)
                        n->left = remove(n->left, e);
                else{
                        if(n->left != nullptr && n->right != nullptr){
                                n->elem = max(n->left);
                                n->left = remove_max(n->left);
                        }
                        else
                                n = (n->left != nullptr) ? n->left : n->right;
                }

                return n;
        }
	V max(BSNode<V>* n) const{
                if(n == nullptr){
                        throw std::runtime_error("Vacio");
                }
                else if(n->right != nullptr)
                        return max(n->right);
                else{
                        return n->elem;
                }
        }

        BSNode<V>* remove_max(BSNode<V>* n){
                if(n->right == nullptr)
                        return n-> left;
                else{
                        n->right = remove_max(n->right);
			return n;
                }
        }


	void delete_cascade(BSNode<V> * n){
		if(n != nullptr){
			delete_cascade(n->right);
			delete_cascade(n->left);

			delete n;
		}
	}

    public:
        // miembros públicos
        BSTree(){
                nelem = 0;
                root = nullptr;
        }
	~BSTree(){
                delete_cascade(root);
        }

        int size() const{
                return nelem;
        }
	V search(V e) const{

		return search(root, e)->elem;
        }
        V operator[](V e) const{
                return search(e);
        }

        void insert(V e){
                root = insert(root, e);
		nelem++;
        }
        friend std::ostream& operator<<(std::ostream &out, const BSTree<V> &bst){
               if(bst.root != nullptr)
		       bst.print_inorder(out,bst.root);
                return out;
        }

        void remove(V e){
                remove(root, e);
		nelem--;
			
        }

};

#endif

