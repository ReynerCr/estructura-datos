#include <iostream>
//#include "Cola_Array.h"
//#include "Queue.h"
//#include "Stack.h"
#include "List.h"

using namespace std;

int main(int argc, char** argv) {
	int val;
	//QUEUE:
	//Queue<int>obj;
	
	//STACK:
	//Stack<int>obj;
	
	//LIST:
	List<int>obj;
	
	obj.add(13);
	cout<<"MADRE"<<endl;
	obj.add(16);
	obj.add(15);
	obj.add(14);
    obj.print();
    cout<<endl;
    
	/*obj.delet(val);
    obj.print();
    cout<<endl;
    
	obj.delet(val);
	obj.print();
	cout<<endl;
	
	obj.add(90);
    obj.delet(val);
    obj.print();
    cout<<endl;
    
    obj.add(80);
    obj.print();
    cout<<endl;
    
    obj.add(50);
    obj.print();
    cout<<endl;

    obj.delet(val);
    obj.delet(val);
    obj.print();
	cout<<endl;*/
	
	
	system("pause");
	return 0;
}
