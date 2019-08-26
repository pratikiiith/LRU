#include<iostream>
#include <bits/stdc++.h>
#include<unordered_map>
#include <string>

using namespace std;


template<class T>
class Deque{
public:
	int s=0;
	int capacity = 0;
	int start;
	int end;
	T *arr = NULL;
	T *p = NULL;

	Deque()
	{	
		start=-1;
		end = -1;
		arr = new T[50];
		capacity = 50;
	}

	Deque(long long n,T x){
		p = new T[n];
		capacity = n;
		s = n;
		for(long long i=0;i<n;i++)
		{
			p[i] = x;
		}
		delete [] arr;
		arr=p;
		start=0;
		end = n-1;
	}

	void create(long long newsize){
		p = new T[newsize];
	 	long long j =   start;
	 	long long i =	start;
	 	
	 	while(j!=end){
	 		p[i] = arr[j];
	 		j++;
	 		i++;
	 		if(j== capacity){
	 			j=0;
	 			}
	 		}
	 		p[i] = arr[j];
	 		end = i;
	 		delete [] arr;
			arr = p;
			capacity = newsize;
		}

	void pushback(T x){
		if (s == capacity) {
				create(2*s);
  			  		} 
	    if (end == -1) { 
        		start = 0; 
        		end = 0; 
        		arr[end]  = x;
        		s++;
    		}
    	else if(end == capacity-1){
    		end = 0;
    		arr[end] = x;
    		s++;
    	}  
    	else{
        	end = end+1;
        	arr[end] = x;
        	s++;
  		}
   
	}

	void popback(){
		if(end == -1){
			cout << "Deque is Empty" << endl;
		}
		else if(start  == end){
			start = -1;
			end = -1;
			s--;
		}
		else if(end == 0){
			end = capacity-1;
			s--;
		}
		else{
			end = end-1;
			s--;
		}
	}

	void pushfront(T x){

		if(s == capacity){
			create(2*s);
		}
		if(start==-1){
			start=0;
			end=0;
			arr[start] = x;
			s++;
		}
		else if(start == 0){
			start = capacity-1;
			arr[start] = x;
			s++;
		}
		else{
			start = (start-1);
			arr[start] = x;
			s++;
		}
	}

	void popfront(){
		if(start == -1){
			cout << "Deque is Empty" << endl;
		}

		else if(start  == end){
			start = -1;
			end = -1;
			s--;
		}
		else if(start == capacity-1){
			start = 0;
			s--;
		}
		else{
			start = start+1;
			s--;
		}
	}

	long long size(){
		return s;
	}

	void clear(){

		start=-1;
		end=-1;
		s=0;
		delete[] arr;
		p= new T[100];
		arr=p;
		capacity=100;
	}

	bool empty()
	{
		if(start==-1) return true;
		else return false;
	}

	void resize(long long n){
		
		if(s==0 && s<n){
			p = new T[n];
			delete [] arr;
			arr =p;
	 		start = -1;
	 		end = -1;
	 		capacity = n;
		}

		else if(s>0 && s < n){
					capacity = n;
					p = new T[capacity]{};
	 				long long j = 0;	 	
	 					if(start <= end){
	 						long long i = start;
	 						while(i<=end){
	 						p[j] = arr[i];
	 						i++;
	 						j++;
	 						}
	 					}
	 				
	 				else{
	 				
	 					long long i = start;
	 						while(i<=capacity-1){
	 						p[j] = arr[i];
	 						i++;
	 						j++;
	 						}
	 						i=0;
	 						while(i<=end){
	 						p[j] = arr[i];
	 						i++;
	 						j++;
	 						}		
	 					}
	 			delete [] arr;
	 			arr=p;
	 			start =0;
	 			end = n-1;
	 			s = n;
			}
		else{
			while(s!=n){
				popback();
				}
			}

		}

	T front(){
		if(start == -1) throw "-1";
		return arr[start];
	}
	T back(){
		if(end == -1) throw "-1";
		return arr[end];
	}

	void erase(T x){

		int i=0;
		while(arr[i] != x){
			i++;
		}
		while(i!=end){

			arr[i] = arr[(i+1)%capacity];
			i = (i + 1)%capacity;
		}		
		end = (i - 1)%capacity;
		if(end < 0) end = end + capacity;
	}

	void display(){
		
		int i = start;
		while(i!=end){
			cout << arr[i] << " ";
			i = (i+1)%capacity;
		}
		cout << arr[i] << endl;
		cout << "start is " << start << " end is " << end << " size is " << s << endl;
	}

	void display2()
	{
		for(int i=start;i<capacity;i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;

		cout << start << " " << end << endl;
	}

	T operator [](long long index){
		if(index > s) throw "-1";
		return arr[(start+index)%s];
		}

	
 };


template<class T, class K>
class LRU
{
	unordered_map<T,K> m;
	int capacity=0;
	Deque<T> d;

public:

	LRU(long long c){
		capacity =c;
		d.resize(capacity);
	}

	void set(T key,K value){

		if(m.find(key) == m.end()){

			if(d.s == capacity){	
				m.erase(d.front());
				d.popfront();
			}
			d.pushback(key);
			m[key]=value;
		}
		else{
			if(d.front() == key){
				
				m.erase(d.front());
				
				d.popfront();

				d.pushback(key);

				m[key]=value;

			}
			else if(d.back() == key){
				m[key] = value;
			}
				else{
				d.erase(key);
				d.pushback(key);
				d.s--;
				m[key]=value;
			}
		}
		
	}

	K get(T key){

		if(m.find(key) != m.end()){
			set(key,m[key]);
			return m[key];
		}
		else{
			throw "-1";
		}
	}
	
	void display()
	{
		d.display();
	}


};

int main()
{
	long long frames;
	cin >> frames;

	LRU<float,string> l(frames);

	int q;
	cin >> q;

	for(int i=0;i<q;i++)
	{
		char choice;
		cin >> choice;
		float a;
		string b;
		float c;
		switch(choice){
			case 'S':
				cin >> a;
				cin >> b;
				l.set(a,b);
				break;
			case 'G':
				cin >> c;
				try{
					cout << l.get(c) << endl;
				}
				catch(const char *m){
					cout << m << endl;	
				}
				break;
		}
	}	

	return 0;
}