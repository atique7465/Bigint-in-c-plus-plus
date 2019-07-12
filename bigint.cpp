///Big integer library in c++.
#include<bits/stdc++.h>
using namespace std;

struct bigint
{
    string p; /// used to store the bigint digits;
    int sign; /// sign=1 for positive integers otherwise sign=-1;

    ///constructors
    bigint() {}    ///default constructor
    bigint(string q)///constructor for string
    {
        (*this)=q;
    }

    ///some methods
    int size()
    {
        return p.size();
    }
    bigint inverseSign()
    {
        sign*=-1;
        return (*this);
    }
    bigint normalize(int newSign) /// removes leading zeros and fixes the sign
    {
        for(int i=p.size()-1; i>0 && p[i]=='0'; i--)
            p.erase(p.begin()+i);
        sign=( p.size()==1 && p[0]=='0' ) ? 1:newSign;
        return (*this);
    }

    ///assignment operator
    void operator = (string q)
    {
        p= q[0]=='-'? q.substr(1):q;
        reverse(p.begin(),p.end());
        this->normalize(q[0]=='-' ? -1:1);
    }

    ///conditional operators
    bool operator < (const bigint &q) const
    {
        if(sign!=q.sign)
            return sign<q.sign;
        if(p.size()!=q.p.size())
            return (sign==1) ? (p.size()<q.p.size()) : (p.size()>q.p.size());
        for(int i=p.size()-1; i>=0; i--)
        {
            if(p[i]!=q.p[i])
                return sign==1 ? p[i]<q.p[i] : p[i]>q.p[i];
        }
        return false;
    }
    bool operator == (const bigint &q)const
    {
        return p==q.p && sign==q.sign;
    }

    ///Arithmatical operator
    bigint operator + ( bigint q )
    {
        if(sign!=q.sign)
            return (*this) - q.inverseSign();
        bigint c;
        for(int i=0, carry=0; i<p.size() || i<q.size() || carry; i++)
        {
            carry+=(i<p.size() ? p[i]-48:0)+(i<q.size() ? q.p[i]-48:0);
            c.p+=(carry % 10 + 48);
            carry/=10;
        }
        return c.normalize(sign);
    }
    bigint operator - (bigint q)
    {
        if(sign!=q.sign)
            return (*this) + q.inverseSign();
        int s=sign;
        sign=q.sign=1;
        if((*this)<q)
            return ((q-(*this)).inverseSign()).normalize(-s);
        bigint c;
        for(int i=0,borrow=0; i<p.size(); i++)
        {
            borrow=p[i]-borrow-(i<q.size() ? q.p[i]:48);
            c.p+= (borrow>=0) ? borrow + 48 : borrow +58;
            borrow= (borrow>=0) ? 0:1;
        }
        return c.normalize(s);
    }

    bigint operator * (bigint q)
    {
        bigint c("0");
        for(int i=0,k=p[i]-48; i<p.size(); i++,k=p[i]-48)
        {
            while(k--)
                c=c+q;
            q.p.insert(q.p.begin(),'0'); /// multiple by 10
        }
        return c.normalize(sign * q.sign);
    }

    bigint operator / ( bigint q )   // division operator overloading
    {
        if( q.size() == 1 && q.p[0] == '0' )
            q.p[0] /= ( q.p[0] - 48 );
        bigint c("0"), d;
        for( int j = 0; j < p.size(); j++ )
            d.p += "0";
        int dSign = sign * q.sign;
        q.sign = 1;
        for( int i = p.size() - 1; i >= 0; i-- )
        {
            c.p.insert( c.p.begin(), '0');
            c = c + p.substr( i, 1 );
            while( !( c < q ) )
                c = c - q, d.p[i]++;
        }
        return d.normalize(dSign);
    }

    bigint operator % ( bigint q )   /// modulo operator overloading
    {
        if( q.size() == 1 && q.p[0] == '0' )
            q.p[0] /= ( q.p[0] - 48 );
        bigint c("0");
        q.sign = 1;
        for( int i = p.size() - 1; i >= 0; i-- )
        {
            c.p.insert( c.p.begin(), '0');
            c = c + p.substr( i, 1 );
            while( !( c < q ) )
                c = c - q;
        }
        return c.normalize(sign);
    }

    /// output method
    void print()
    {
        if( sign == -1 )
            putchar('-');
        for( int i = p.size() - 1; i >= 0; i-- )
            putchar(p[i]);
    }
};

int main()
{
    bigint a, b, c;

    string input;
    cin >> input;
    a = input;
    cin >> input;
    b = input;

    c = a + b;
    c.print();
    cout<<endl;

    c = a - b;
    c.print();
    cout<<endl;

    c = a * b;
    c.print();
    cout<<endl;

    c = a / b;
    c.print();
    cout<<endl;

    c = a % b;
    c.print();
    cout<<endl;

    if( a == b )
        puts("equal");
    else
        puts("not equal");
    if( a < b )
        puts("a is smaller than b");

    return 0;
}
