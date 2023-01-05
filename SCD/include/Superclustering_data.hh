#ifndef __SUPERCLUSTERING_DATA_H__
#define __SUPERCLUSTERING_DATA_H__

#include "Superclustering.hh"
#include "Supercluster.hh"
#include "TTree.h"

class Superclustering_data
{
    private:

    public:
    Superclustering_data();
    ~Superclustering_data();
    static Superclustering_data &GetInstance()
    {
        static Superclustering_data instance;
        return instance;
    };
    void set_tree_branches(TTree *outTree);
    void fill_supercluster_data();
    void clear();
    std::vector<Supercluster> super_list;
    std::vector<float> super_e;
    std::vector<float> seed_idx;
    std::vector<float> track_idx;
};

#endif