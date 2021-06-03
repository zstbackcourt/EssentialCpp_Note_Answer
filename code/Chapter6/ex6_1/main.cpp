#include <iostream>
using namespace std;


template <typename elemType>
class example{
public:
    example(const elemType &min, const elemType &max);
    example(const elemType *array, int size);
    elemType& operator[](int index);
    bool insert(const elemType*, int);
    bool insert(const elemType&);
    elemType min() const { return _min;}
    elemType max() const { return _max;}
    void min(const elemType&);
    void max(const elemType&);
    int count(const elemType &value) const;
private:
    int size;
    double *parray;
    double _min;
    double _max;
};