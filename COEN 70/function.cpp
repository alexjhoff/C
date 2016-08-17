#include <iostream>

class Functional;
{
    public:
        //default constructor 0/1
        Fractional();
        //accessor functions
        int get_num();
        int get_denom() const;
        //mutator functions
        void set_num(int new_num);
        void set_denom(int new_denom);
    
        //add two fractional
        Fractional add(Fractional f2);
    
    private:
        int num;
        int denom;
}

int main()
{
    Fractional first();
    first.set_num(5);
    cout << first.get_num()<<endl;
    return 0;
}

Fractional::Fractional()
{
    num=0;
    denom=1;
}

Fractional::set_num(int i)
{
    num=i;
}

int Fractional::get_num()
{
    
}