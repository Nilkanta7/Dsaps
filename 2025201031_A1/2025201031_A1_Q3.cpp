#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class keyval{
    public:
    ll key,val;
};

class maap{
    public:

    vector<keyval>arr;

    //returns lower value of ind such that arr[ind].key>=x
    int lb(ll x){//O(log n)
        int s=0;
        int e=(int)arr.size()-1;
        int res=(int)arr.size();
        while(s<=e){
            int mid=s+(e-s)/2;
            if(arr[mid].key >= x){
                res=mid;
                e=mid-1;//left
            }
            else{
                s=mid+1;//riht
            }
        }
        return res;//returns index
    }

    //insert key val in sorted pair
    void insert(ll ke,ll value){//O(log n)
        int ind=lb(ke);
        int n=(int)arr.size();
        if(ind<n && arr[ind].key==ke){
            arr[ind].val=value;//if same value of key then only update it
        }
        else{
            arr.insert(arr.begin()+ind,{ke,value});
        }
    }

    //delet function for delettion
    void erase(ll key){//O(log n)
        int ind=lb(key);
        int n=(int)arr.size();
        if(ind<n && arr[ind].key==key){
            arr.erase(arr.begin()+ind);
        }
    }

    //checking prev value
    int prev(ll x){//O(log n)
        int ind=lb(x);

        return ind-1;
    }

    ll valueat(ll x){//O(log n)
        int ind=lb(x);
        int n=(int)arr.size();
        if(ind<n && arr[ind].key==x){
            return arr[ind].val;//if x exist return its value
        }
        int pr=prev(x);//return largexst value smaller than ut
        if(pr>=0)return arr[pr].val;
        return 0;
    }


    //printing all the key value pair
    void print(){
        for(int i=0;i<(int)arr.size();i++){
            cout<<arr[i].key<<" "<<arr[i].val<<endl;
        }
        cout<<endl;
    }
};

maap mp;

void update(ll l,ll r,ll h){
    //range [l,r)
    ll rh=mp.valueat(r);//ckecking which value stores at r
    int ind=mp.lb(l);//first key val >=l

    ll pre;
    if(ind>0){
        pre=mp.arr[ind-1].val;
    }
    else pre=0;

    if(!(ind<(int)mp.arr.size() && mp.arr[ind].key==l)){
        if(pre<h)mp.insert(l,h);//l not exsit int the prev range
    }
    else{
        if(mp.arr[ind].val<h)mp.insert(l,h);//l exist but height is greter
    }

    mp.insert(r,rh);

    int indx=mp.lb(l+1);

    //remove ehich are strrictly in [l,r)and height<=h

    while(indx<(int)mp.arr.size() && mp.arr[indx].key<r){
        if(mp.arr[indx].val<=h){
            mp.erase(mp.arr[indx].key);
        }
        else{
            indx++;
        }
    }

}

void printing(){
    mp.print();
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    while(q--){
        int t;
        cin>>t;
        if(t==0){
            ll l,r,h;
            cin>>l>>r>>h;
            update(l,r,h);
        }
        else{
            printing();
        }
    }
    //best case tc-O(log n)
    ////worst case- O(n)
    return 0;
}