//
// Created by Yaser Alkayale on 2017-06-04.
//

#ifndef KMEANSII_KMEANSII_H
#define KMEANSII_KMEANSII_H


#include "Kmeans.h"
#include "Kmeanspp.h"

class KmeansII : public Kmeanspp{
public:
    KmeansII(Table &_data, const int k, const double l);
    ~KmeansII();

private:
    void run() override;
    void findCentres() override;

private:
    const double _l; //this the the constant passed in by the user.
};


#endif //KMEANSII_KMEANSII_H
