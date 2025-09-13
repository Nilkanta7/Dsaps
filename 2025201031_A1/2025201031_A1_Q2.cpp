#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Node{
  Node *link[26];//array of 26 length
  bool flag;//for marking end of the word

  //constructor
  Node(){
    flag=0;
    for(int i=0;i<26;i++){
      link[i]=NULL;
    }
  }

  bool contain(char ch){
      return link[ch-'a']!=NULL;
  }

  void put(char ch,Node* node){
      link[ch-'a']=node;
  }

  Node* get(char ch){
      return link[ch-'a'];
  }

  void setend(){
    flag=1;
  }
};

class Trie{
  private: Node *root;

  public:
  Trie(){
    root=new Node();
  }

  void insert(string str){
    Node * node=root;
    for(int i=0;i<str.size();i++){
      if(!node->contain(str[i])){
        node->put(str[i],new Node());
      }
      node=node->get(str[i]);
    }
    node->setend();

  }

  bool search(string str){
    Node * node=root;
    for(int i=0;i<str.size();i++){
      int indx=str[i]-'a';
      if(!node->link[indx])return 0;

      node=node->link[indx];
    }

    return node->flag;
  }

  void wordstoring(Node * node,string &temp,vector<string>&ans){
    //check base-condintion
    if(node->flag){
      ans.push_back(temp);
    }

    //checking for maximum 26 codintions
    for(int i=0;i<26;i++){
      if(node->link[i]){
        temp.push_back(i+'a');
        wordstoring(node->link[i],temp,ans);
        temp.pop_back();
      }
    }
  }

  vector<string>autocomplete(string str){
    Node * node=root;
    vector<string>ans;
    for(int i=0;i<str.size();i++){
      int indx=str[i]-'a';

      if(!node->link[indx])return ans;

      node=node->link[indx];
    }

    string temp=str;
    //check recursively for matching in the trie
    wordstoring(node,temp,ans);

    return ans;
  }

  void autofun(Node* node,string &str,string &temp,vector<int>&dp,int maxi,vector<string>&res){
    int n=str.size();
    vector<int>tempdp(n+1);
    tempdp[0]=dp[0]+1;

    for(int i=1;i<=n;i++){
      int t=(str[i-1]!=temp.back());
      tempdp[i]=min({dp[i]+1,tempdp[i-1]+1,dp[i-1]+t});
    }

    if(node->flag && tempdp[n]<=maxi){
      res.push_back(temp);
    }

    for(int i=0;i<26;i++){
      if(node->link[i]){
        temp.push_back('a'+i);
        autofun(node->link[i],str,temp,tempdp,maxi,res);
        temp.pop_back();
      }
    }
  }

  
  vector<string>autocorrect(string &str,int maxi){
    int n=str.size();
    vector<int>dp(n+1);
    for(int i=0;i<=n;i++)dp[i]=i;

    vector<string>res;
    string temp;

    for(int i=0;i<26;i++){
      if(root->link[i]){
        temp.push_back('a'+i);
        autofun(root->link[i],str,temp,dp,maxi,res);
        temp.pop_back();
      }
    }

    return res;
  }

};



int main(){

  ios::sync_with_stdio(false);

  int n,t;
  cin>>n>>t;
  Trie root;

  for(int i=0;i<n;i++){
    string str;
    cin>>str;

    root.insert(str);
    

  }

  while(t--){
    int x;
    string str;
    cin>>x>>str;
    if(x==1){
      cout<<(root.search(str))<<endl;
    }
    else if(x==2){
      vector<string>ans=root.autocomplete(str);
      cout<<ans.size()<<endl;
      for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<endl;
      }

    }
    else if(x==3){
      vector<string>ans=root.autocorrect(str,3);
      cout<<ans.size()<<endl;
      for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<endl;
      }
    }
  }


}