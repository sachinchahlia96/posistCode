#include<bits/stdc++.h>
#include <time.h>
using namespace std;
struct Owner{
	string name, address, mobile, phone,password;
	float value;
	int ownerNum;
};
struct Node{
	int nodeNum, nodeId;
	vector<int> childNodeId;
	vector<Node*> refChildNodeId;
	time_t dt;
	Owner *owner;
	Node *refNodeId;
};

string encrypt(string s,int n){
	string solution = s;
	int len = s.length(), i;
	for(i = 0; i < len; i++){
		solution[i] += n;
	}
	return solution;
}

string decrypt(string str,int n){
	string sol = str;
	int length = str.length(), i;
	for(i = 0; i < length;i++){
		sol[i] -= n;
	}
	return sol;
}
Node *getNode(int num,Owner *own){
	Node *nnode = new Node;
	vector<Node*> v;
    vector<int> s;
	nnode->owner = own,			nnode->dt = time(0);
	nnode->nodeNum = num,		nnode->nodeId = (num);
	nnode->refChildNodeId = v,	nnode->refNodeId = NULL;

	nnode->childNodeId = s;
	return nnode;
}
Owner *getOwner(int num,string name, string address, string mobile, string phone, float value,string pass){

	Owner *temp = new Owner;

	temp->address=encrypt(address,num),	temp->address=encrypt(name,num);
	temp->address=encrypt(mobile,num),	temp->address=encrypt(phone,num);
	temp->password=encrypt(pass,num),	temp->value=value;
	temp->ownerNum = num;
	return temp;
}


void query3(Node *child,int id,vector<Node*> &v){
	int i, size = v.size();
	for(i = 0; i < size; i++){
		if(v[i]->nodeId == id){
			child->refNodeId = v[i];
			v[i]->childNodeId.push_back(child->nodeId);
			v[i]->refChildNodeId.push_back(child);
			break;
		}
	}
}

bool query4(vector<Owner*> &owners,Owner *currOwner,vector<Node*> &v){
	int id, i, size = v.size();
	bool flag;
	cout<<"NodeId: ";
			cin>>id;
			flag = false;
			for(i = 0; i < size; i++){
				if(v[i]->nodeId == id){
					if(currOwner == v[i]->owner){
						flag = true;
					}
					break;
				}
			}

			return flag;
}
//deleting particular node using nodeId
void query5(vector<Owner*> &owners, Owner *currOwner, vector<Node*> &v){
	int id, i, size = v.size(), k;
	bool flag = false;

	cout<<"Enter NodeId ";
	cin>>id;

	for(i = 0; i < size; i++){
		if(v[i]->nodeId == id){
			if(query4(owners, currOwner, v)){
				flag = true;
				Node *parent = v[i]->refNodeId;
				vector<Node*> child = parent->refChildNodeId;
				for(k = 0; k < child.size(); k++){
					if(child[k]->nodeId == id){
						child.erase(child.begin()+i);
						break;
					}
				}
			}
			else{
				cout<<"Error404"<<endl;
				return;
			}
			break;
		}
	}
	if(flag == true){
		cout<<"node has been removed"<<endl;
	}
	else{
		cout<<"unable to find node"<<endl;
	}
}
void query6(vector<Owner*> &owners,Owner *currOwner, vector<Node*> &v){
	int id,userId, i, k, size1 = v.size(), size2 = owners.size();
	bool flag = false;
	cout<<"Enter nodeId and userId: ";
	cin >> id >> userId;
	for(i = 0; i < size1; i++){
		if(v[i]->nodeId == id){
			if(query4(owners, currOwner, v)){
				Node *temp = v[i];
				for(k = 0; k < size2; k++){
					if(owners[k]->ownerNum == userId){
						temp->owner = owners[k];
						flag = true;
						break;
					}
				}
			}
			else{
				cout<<"Error404"<<endl;
				return;
			}
			break;
		}
	}
	if(flag){
		cout<<"Node Owner changed"<<endl;
	}else{
		cout<<"Node not found"<<endl;
	}
}
void query7(vector<Node*> v){

}
void dfs(Node *root,int &n,int num){
	if(root == NULL){
		n=max(n, num);
	}
	int count = num+1;
	vector<Node*> child = root->refChildNodeId;
	for(int i = 0; i < child.size(); i++){
		dfs(child[i], n, num+1);
	}
	n = max(n,count);
}
void mergeSet(vector<Node*> &first, vector<Node*> &second,Owner *currOwner){
	//merge sets of same owner
	int i = 0, j = 0;
	while(i < first.size() && j < second.size()){
		while(i < first.size() && first[i]->owner != currOwner){
			i++;
		}
		while(j < second.size() && second[j]->owner != currOwner){
			j++;
		}
		int n1 = -1,n2 = -1;
		dfs(second[j], n2, 0);
		dfs(first[i], n1, 0);
		if(n1 > n2){
			second[j]->refNodeId=first[i];
			first[i]->refChildNodeId.push_back(second[j]);
			second.erase(second.begin()+j);
			i++;
		}
		else{
			first[i]->refNodeId=second[j];
			second[j]->refChildNodeId.push_back(first[i]);
			second.erase(second.begin()+j);
			j++;
		}
	}

}
int main(){
	St:
	vector<Node*> v;
    vector<Owner*> owners;
    vector<vector<Node*> > set;

    int num = 0,nOwners = 0;

    int i, test;

    Owner *currOwner;
    bool flag=false;
    string pass;
	int key;
    while(!flag){
    	cout << "1-->login or 2-->signup";
    	cin >> test;
    	if(test == 1){
			cout<<"INPUT:-> password and key";
	    	cin >> pass >> key;
	    	for(i = 0; i < owners.size(); i++){
	    		if(owners[i]->ownerNum == key){
	    			if(pass == decrypt(owners[i]->password, owners[i]->ownerNum)){
	    				flag = true;
	    				currOwner = owners[i];
	    				break;
					}
				}
			}
			cout << "Login failed" << endl;
		}
		else{
			cout << "Enter name, address, mobile,phone, value, password:" << endl;
			string name,address,mobile,phone,pass;
			float value;
			cin >> name >> address >> mobile >> phone >> value >> pass;
			currOwner = getOwner(nOwners++, name, address, mobile, phone, value, pass);
			owners.push_back(currOwner);
			cout << "key : "<< currOwner->ownerNum << endl;
			flag = true;
		}
	}

    while(1){
    	cout<<"Enter Query: ";
		cin >> test;
		if(test == 1){
			//creating genesis node
			vector<Node*> v;
			v.push_back(getNode(num++,currOwner));
			set.push_back(v);
		}
		else if(test == 2){
			//pushing a set of child nodes
			int n = 0;
			cout << "Enter number of nodes: ";
			cin >> n;
			vector<Node*> v(1);
			for(i = 0; i < n; i++){
				v[0] = (getNode(num++, currOwner));
				set.push_back(v);
			}
			cout<<"nodes pushed"<<endl;
		}
		else if(test == 3){
			//adding node to any set
			Node *np = getNode(num++, currOwner);
			v.push_back(np);
			cout << "Enter setNo: ";
			int setNo;
			cin >> setNo;
			set[setNo].push_back(np);

		}
		else if(test == 4){
			//verify owner
			bool f=false;
			for(i = 0; i < set.size(); i++){
				f = query4(owners,currOwner,set[i]);
				if(f){
					cout << "you are the owner!" << endl;
				}
			}
			if(!f){
				cout << "you are not owner" << endl;
			}
		}
		else if(test == 5){
			//edit the node/ delete node
			query5(owners,currOwner,v);

		}
		else if(test == 6){
			// transfer owner
			query6(owners,currOwner,v);

		}
		else if(test == 7){
			//longest chain of genesis node
			int mx=-1;
			for(i = 0; i < set.size(); i++){
				dfs(set[i][0],mx,0);
			}
			cout<<"max chain="<<mx<<endl;

		}
		else if(test == 8){
			//longest chain of sub node
			cout << "enter node id" << endl;
			int id;
			cin >> id;
			int ans = -1;
			bool f = false;
			for(i = 0; i < set.size(); i++){
				for(int j = 0; j < set[i].size(); j++){
					if(set[i][j]->nodeId == id){
						f = true;
						dfs(set[i][j],ans,0);
						break;
					}
				}
				if(f){
					break;
				}
			}
		}
		else if(test==9){
			//merge nodes
			cout<<"enter 1st and 2nd set number"<<endl;
			int f,s;
			cin>>f>>s;
			mergeSet(set[f],set[s],currOwner);

		}
		else if(test==10){
			//log out
			currOwner=NULL;
			goto St;
		}
		else {
			break;
		}
	}
    return 0;
}
