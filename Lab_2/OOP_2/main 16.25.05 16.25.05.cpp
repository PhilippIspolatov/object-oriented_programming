#include "myset.h"
#include "my_exceptions.h"
#include <iostream>

using namespace std;

class Test{
public:
    Test(int _c): c(_c){ }
    int getC() const { return c; }
private:
    int c;
public:
    bool operator == (const Test &t) const{ return t.getC() == c ;}
    bool operator < (const Test &t) const{ return t.getC() < c ;}
};


int main()
{
    try
    {

        // Test 1
        cout << "TEST unite, intersect, subtract func:"<<endl<<endl;
        cout <<"TEST 1:"<<endl<<endl;
        {
            MySet<int> set {1, 2, 3};
            MySet<int> set2{2, 4, 8};

            cout << "Set1: " << set;
            cout << "Set2: " << set2;

            MySet<int> set3 = set + set2;
            MySet<int> set4 = set & set2;
            MySet<int> set5 = set - set2;
            cout << "Union (S1 + S2): " << set3;
            cout << "Intersect (S1 & S2): " << set4;
            cout << "Subtract (S1 - S2): " << set5 << endl;
        }

        cout << endl<<"TEST 2:"<<endl<<endl;
        // Test 2
        {
            MySet<int> set{1,2,3}, set2{2,4,6};
            cout << "Set1: " << set;
            cout << "Set2: " << set2 << endl;

            MySet<int> set3 = set.unite(set2);
            MySet<int> set4 = set.intersect(set2);
            MySet<int> set5 = set.subtract(set2);
            cout << "Union (S1 + S2): " << set3;
            cout << "Intersect (S1 & S2): " << set4;
            cout << "Subtract (S1 - S2): " << set5 << endl;

        }

        cout << endl<<"TEST 3:"<<endl<<endl;
        // Test 3
        {

            MySet<int> set, set2;
            cout << "Set1: " << set;
            cout << "Set2: " << set2 << endl;

            MySet<int> set3 = set.unite(set2);
            MySet<int> set4 = set.intersect(set2);
            MySet<int> set5 = set.subtract(set2);
            cout << "Union (S1 + S2): " << set3;
            cout << "Intersect (S1 & S2): " << set4;
            cout << "Subtract (S1 - S2): " << set5 << endl;
        }
        cout <<endl<<"TEST 4:"<<endl<<endl;
        {
            MySet<int> set {1, 2, 3};
            MySet<int> set2{1, 4, 2, 5};


            cout << "Set1: " << set;
            cout << "Set2: " << set2 << endl;

            set += set2;
            cout << "Union (S1 += S2)... "<<endl;
            cout << "Set1: " << set << endl;

            set -= set2;
            cout << "Subtract (S1 -= S2):... " << endl;
            cout << "Set1: " << set<<endl;

            set &= set2;
            cout << "Intersect (S1 &= S2):... "<<endl;
            cout << "Set1: " << set << endl;
        }

        cout << endl<<"TEST method remove:"<<endl<<endl;
        // Test 4
        {
            MySet<int> set{ 2, 4, 8, 7, 6 };
            cout << "Set: " << set;
            cout << "Remove 2 ..." << endl;
            set.remove(2);
            cout << "Set: " << set;
            cout << "Remove 8..." << endl;
            set.remove(8);
            cout << "Set: " << set;
            cout << "Remove 6..." << endl;
            set.remove(6);
            cout << "Set: " << set;
        }

        cout << endl<<"TEST operator ==:"<<endl<<endl;
        // Test 5
        {
            MySet<int> set{ 1, 2, 3 }, set2{ 1, 2, 3 }, set3{ 1, 2, 4 };
            cout << "Set1: " << set;
            cout << "Set2: " << set2;
            cout << "Set3: " << set3 << endl;

            if (set == set2)
                cout<<"Set1 and Set2 are equal!"<<endl;
            if (set != set3)
                cout<<"Set1 and Set3 aren't equal!"<<endl;
        }

        cout << endl<<"TEST operator =:"<<endl<<endl;
        // Test 6
        {
            MySet<int> set1{ 1, 2, 3 }, set2;
            cout << "Set1: " << set1;
            cout << "Set2: " << set2 << endl;

            set2 = move(set1);
            cout << "set2 = move(set1);" << endl;
            cout << "Set1: " << set1;
            cout << "Set2: " << set2 << endl;

            set1 = set2;
            cout << "set1 = set2;" << endl;
            cout << "Set1: " << set1;
            cout << "Set2: " << set2 << endl;

            MySet<int> set3(set1);
            cout << "MySet<int> set3(set1);" << endl;
            cout << "Set1: " << set1;
            cout << "Set3: " << set3 << endl;

            MySet<int> set4 = move(set2);
            cout << "MySet<int> set4 = move(set2);" << endl;
            cout << "Set2: " << set2;
            cout << "Set4: " << set4 << endl;
        }

        // Test contains and count
        cout <<endl<<"TEST contains and count:"<<endl<<endl;
        {
            MySet<int> set {1, 2, 3, 4, 5};
            MySet<int> set2{1, 3, 5};


            cout << "Set1: " << set;
            cout << "Set2: " << set2 << endl;

            if (set.contains(set2))
                cout << "Set1 contains Set2." << endl;
        }

        // Test operator []
        cout << endl<<"TEST operator []:"<<endl<<endl;
        {
            MySet<int> set{1, 2, 3, 4, 5};
            cout<< "Set: ";
            for (int i = 0; i < set.getSize(); i++)
                cout << set[i] << " ";
            cout << endl;
        }

        cout << endl<<"TEST Iterator:"<<endl<<endl;
        // Test iterator
        {
            MySet<int> set { 1, 2, 3, 4, 5 };
            auto it = set.createIterator();

            while(it.check())
            {
                cout << *it << " ";

                if (*it == 3)
                {
                    set.remove(it);
                    continue;
                }

                it++;    
            }

            cout << std::endl << "Set after remove 3: " << set;

            // Test iterator on custom class
            MySet<Test> set3{Test(1), Test(2)};
            auto it2 = set3.createIterator();
            it2->getC();
        }
    }
    catch (cEBaseException &ex)
    {
        cout << "Exception:" << ex.what( ) << endl;
    }
    return 0;
}
