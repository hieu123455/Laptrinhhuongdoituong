#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

struct tong {
	private:
	    int value;
	public:
	    tong(){}
	    tong(int val) : value(val){}
	
	    void nhap(){
	        cin >> value;
	    }
	
	    tong operator +(tong x){
	        tong c;
	        c.value = this->value + x.value;
	        return c;
	    }
	    
	    void hienthi(){
			cout << value << endl;
		}
};

int main() {
    tong a, b;
    a.nhap();
    b.nhap();
    tong c = a + b;
    c.hienthi();
    return 0;
}

