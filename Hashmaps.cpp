//******* HashMaps
#include<iostream>
#include<string>
using namespace std;

//Create a mapnode class
template <typename V>
class Mapnode{
    //Each Mapnode is of linked list type
    public:
    string key;
    V value;
    Mapnode* next;

    //Create a constructor
    Mapnode(string key,V value){
        this->key=key;
        this->value=value;
        next=NULL;
    }

    //Call a destructor recursively
    ~Mapnode(){
        delete next;
    }  
};

//Create a class of Mapnodes in an arraybucket
template <typename V>
class ourmap{
    //Basically ourmap is a class which returns the bucketarray in which each element has
    //head if the linkedlist of Mapnodes
    Mapnode<V>** buckets;
    int count;
    int numbuckets;
    public:
    //Constructor to initialize the declared data members
    ourmap(){
        count=0;
        numbuckets=5;
        buckets=new Mapnode<V>*[numbuckets];
        for(int i=0;i<numbuckets;i++){
            buckets[i]=NULL;
        }
    }

    //Destructor to delete ourmap(i.e, array of mapnodes(mapnodes is address of mapnode linked list heads))
    ~ourmap(){
        for(int i=0;i<numbuckets;i++){
            delete buckets[i];
        }
        delete []buckets;
    }

    int size(){
        return count;
    }
    
    private:
    //create a function to return a index corresponding to the key
    int getbucketindex(string key){
        int hashvalue=0;
        int curr=1;
        for(int i=key.length()-1;i>=0;i--){
            hashvalue+=key[i]*curr;
            hashvalue%=numbuckets;
            curr*=37;
            curr%=numbuckets;
        }
        return hashvalue%numbuckets;
    }

    void rehash(){
        Mapnode<V>** temp=buckets;
        buckets=new Mapnode<V>*[2*numbuckets];
        for(int i=0;i<2*numbuckets;i++){
            buckets[i]=NULL;
        }
        int oldbucketcount=numbuckets;
        numbuckets*=2;
        count=0;
        for(int i=0; i<oldbucketcount; i++){
            Mapnode<V>* temphead=temp[i];
            while(temphead!=NULL){
                string key=temphead->key;
                V value=temphead->value;
                insert(key,value);
                temphead=temphead->next;
            }
        }
        for(int i=0;i<oldbucketcount;i++){
            Mapnode<V>* temphead=temp[i];
            delete temphead;
        }  
        delete []temp;
    }

    public:
    void insert(string key, V value){
        int bucketindex = getbucketindex(key); 
        Mapnode<V>* temphead=buckets[bucketindex];
        while(temphead!=NULL){
            if(temphead->key==key){
                temphead->value=value;
                return;
            }
            temphead=temphead->next;
        }
        temphead=buckets[bucketindex];
        Mapnode<V>* newMapnode= new Mapnode<V>(key,value);
        newMapnode->next=temphead;
        buckets[bucketindex]=newMapnode;
        count++;
        double loadfactor= (1.0*count/numbuckets);
        if(loadfactor>0.7){
            rehash();
        }
    }

    //Function to remove the Mapnode of the key passed and we have to return the value
    V remove(string key){
        int bucketindex=getbucketindex(key);
        Mapnode<V>* temphead=buckets[bucketindex];
        Mapnode<V>* prev=NULL;
        while(temphead!=NULL){
            if(temphead->key==key){
                if(prev==NULL){
                    buckets[bucketindex]=temphead->next;
                }
                else{
                    prev->next=temphead->next;
                }
                V value=temphead->value;
                temphead->next=NULL;
                delete temphead;
                count--;
                return value;
            }
            prev=temphead;
            temphead=temphead->next;
        }
        return 0;
    }

    //Function to get a value when a key is provided
    V getvalue(string key){
        int bucketindex=getbucketindex(key);
        Mapnode<V>* temphead=buckets[bucketindex];
        while(temphead!=NULL){
            if(temphead->key==key){
                return temphead->value;
            }
            temphead=temphead->next;
        }
        return 0;
    }

};

//DRIVER FUNCTION
int main(){
    ourmap<int> map;
    for(int i=0;i<10;i++){
        char c='0'+i;
        string key="abc";
        key+=c;
        int value=i+1;
        map.insert(key,value);
       // cout<<map.getLoadFactor()<<endl;
    }
    cout<<map.size()<<endl;;
    map.remove("abc2");
    map.remove("abc7");
    cout<<map.size()<<endl;
    for(int i=0;i<10;i++){
        char c='0'+i;
        string key="abc";
        key+=c;
        cout<<key<<":"<<map.getvalue(key)<<endl;
    }
    cout<<map.size()<<endl;
}



