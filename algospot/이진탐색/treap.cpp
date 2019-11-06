#include<iostream>
#include<cstdlib>
 
using namespace std;
 
typedef int KeyType; ///< key 값의 데이터 형
 
/**
        @class  Treap
        @data   2014/7/31
        @author 이원석
        @brief  트립(TREAP)의 노드를 구현
*/
class TreapNode
{
        public:
                KeyType key; ///< 저장하고자 하는 값
                int priority; ///< 노드가 갖는 우선 순위
                int size; ///< 노드를 루트로 하는 서브트립의 크기
                TreapNode* left; ///< 노드의 왼쪽 자손의 포인터
                TreapNode* right; ///< 노드의 오른쪽 자손의 포인터
               
                //_key를 key로 갖는 노드를 생성하는 생성자.
                TreapNode(const KeyType _key ///< 새로만들 노드의 key 값
                          )
                        :key(_key),priority(rand()),size(1),left(NULL),right(NULL)
                {}
                //newLeft를 노드의 왼쪽 자손으로 설정
                void setLeft(TreapNode* newLeft ///< 새로 삽입될 노드
                             )
                {
                        left=newLeft;
                        //서브트립의 크기 재계산
                        calcSize();
                        return;
                }
                //newRight를 노드의 오른쪽 자손으로 설정
                void setRight(TreapNode* newRight ///< 새로 삽입될 노드
                              )
                {
                        right=newRight;
                        //서브트립의 크기 재계산
                        calcSize();
                        return;
                }
                //노드를 루트로 하는 서브트립의 크기 계산
                void calcSize(void)
                {
                        size=1;
                        size=(left!=NULL)? size+left->size:size;
                        size=(right!=NULL)? size+right->size:size;
                        return;
                }
};
 
typedef pair<TreapNode*,TreapNode*> TreapNodePair; ///< 아래 split함수의 리턴 값 구조체
 
//root를 노트로 하는 트립을 key를 기준으로 나누어 <left,right>로 반환
TreapNodePair split(TreapNode* root, ///< 나누려고 하는 트리의 루트노드
                    KeyType key ///< 기준이 되는 key 값
                    )
{
        //트리가 존재하지 않는 경우 <NULL,NULL>을 반환
        if(root==NULL)
        {
                return TreapNodePair(NULL,NULL);
        }
        //루트가 key값 보다 작다면, 루트의 right를 나눔
        if(root->key<key)
        {
                TreapNodePair rs=split(root->right,key); ///< 재귀적으로 나뉘어진 오른쪽 서브트립의 루트
                //기존 루트의 오른쪽 서브트립을 루트보다 크고, key보다 작은 서브트립으로 대체
                root->setRight(rs.first);
                //key보다 작은 값만 있는 root와 큰값만 있는 rs.second를 반환
                return TreapNodePair(root,rs.second);
        }
        //루트가 key값 보다 크다면, 루트의 left를 나눈다.
        else
        {
                TreapNodePair ls=split(root->left,key); ///< 재귀적으로 나뉘어진 왼쪽 서브트립의 루트
                //기존 루트의 왼쪽 서브트립을 루트보다 작고, key보다 큰 서브트립으로 대체
                root->setLeft(ls.second);
                //key보다 작은 값만 있는 ls.first와 큰 값만 있는 root를 반환
                return TreapNodePair(ls.first,root);
        }
        //에러방지용, 수행되지 않음
        return TreapNodePair(NULL,NULL);
}
 
//root를 루트로 하는 트립에 new_node를 삽입후 결과 트립의 루트를 반환
TreapNode* insert(TreapNode* root, ///< 삽입할 트립의 루트
                  TreapNode* new_node ///< 삽입될 새로운 노드
                  )
{
        //기존에 트리가 존재하지 않는 경우 곧바로 new_node를 반환
        if(root==NULL)
        {
                return new_node;
        }
        //루트의 우선순위가 새노드의 우선 순위보다 높다면 재귀적으로 삽입을 수행
        if(root->priority>new_node->priority)
        {
                //BST의 속성을 만족시키도록 아래를 수행
                if(root->key>new_node->key)
                {
                        root->setLeft(insert(root->left,new_node));
                }
                else
                {
                        root->setRight(insert(root->right,new_node));
                }
                return root;
        }
        //루트의 우선순위가 새노드의 우선 순위보다 낮다면 split을 수행하여 삽입
        else
        {
                TreapNodePair splited=split(root,new_node->key); ///< 새노드의 키를 기준으로 나눠진 트립
                //새노드의 왼쪽 트립을 세팅
                new_node->setLeft(splited.first);
                //새노드의 오른쪽 트립을 세팅
                new_node->setRight(splited.second);
                //새로이 루트가 된 new_node를 반환
                return new_node;
        }
        //에러방지용, 수행되지 않음
        return NULL;
}
 
//두 트립의 루트 t1,t2가 주어지고 t1의 최대값이 t2의 최소값보다 작을 때 둘을 합쳐 새 루트를 반환
TreapNode* merge(TreapNode* t1, ///< max(t1)<max(t2)를 만족하는 한 서브트립
                 TreapNode* t2 ///< max(t1)<max(t2)를 만족하는 한 서브트립
                 )
{
        //두 트립중 하나가 NULL인 경우 남은 한 쪽을 반환
        if(t1==NULL)
        {
                return t2;
        }
        if(t2==NULL)
        {
                return t1;
        }
        //t2가 루트가 되어야하는 경우 재귀적으로 트립을 수정후 반환
        if(t1->priority<t2->priority)
        {
                t2->setLeft(merge(t1,t2->left));
                return t2;
        }
        //t1이 루트가 되어야하는 경우 재귀적으로 트립을 수정후 반환
        else
        {
                t1->setRight(merge(t1->right,t2));
                return t1;
        }
        //에러방지용, 수행되지 않음
        return NULL;
}
 
//root를 루트로 하는 트립에서 key값을 삭제한 트립의 루트를 반환
TreapNode* erase(TreapNode* root, ///< 삭제할 값을 지니고 있는 트립
                 KeyType key ///< 삭제할 key 값
                 )
{
        //삭제할 값을 찾지 못한 경우 root를 반환
        if(root==NULL)
        {
                return root;
        }
        //삭제할 값을 찾아낸 경우 merge된 양 서브트립을 반환
        if(root->key==key)
        {
                TreapNode* ret=merge(root->left,root->right);
                delete root;
                return ret;
        }
        //BST의 속성을 만족시키도록 아래를 수행
        else if(root->key>key)
        {
                root->setLeft(erase(root->left,key));
                return root;
        }
        else
        {
                root->setRight(erase(root->right,key));
                return root;
        }
        //에러방지용, 수행되지 않음
        return root;
}
 
//root를 루트로 하는 트립을 inorder로 순회
void inorder(TreapNode* root ///< 중위순회하고자 하는 트립의 루트
             )
{
        if(root!=NULL)
        {
                inorder(root->left);
                cout<<root->key<<' ';
                inorder(root->right);
        }
        return;
}
 
int main(void)
{
        //테스트 코드 시작
       
        TreapNode* root=NULL; ///< 트립 선언
        //[0,9]의 숫자를 오름차순으로 삽입
        for(int i=0;i<10;i++)
        {
                root=insert(root,new TreapNode(i));
        }
        //트립을 중위순회
        inorder(root);
        cout<<endl;
        //트립에서 1,6,5,8의 값을 삭제
        root=erase(root,1);
        root=erase(root,6);
        root=erase(root,5);
        root=erase(root,8);
        //트립을 중위순회
        inorder(root);
        cout<<endl;
       
        //테스트 코드 끝
        return 0;
}
