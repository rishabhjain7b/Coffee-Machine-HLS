
#ifndef _DEF_H_
#define _DEF_H_

#include <ac_int.h>
#include <ac_channel.h>
#include <mc_scverify.h>

// Definition of Buttons for Coffee Dispensing
template <int COST>
class Button {
    private:
        int itemCost;

    public:
        Button() {
            itemCost = COST;
        }

        int getCost () {
            return this.itemCost;
        }
};

// Defintions of types of Coins available
namespace Coins {
    const int OneRupee = 1;
    const int TwoRupee = 2;
    const int FiveRupee = 5;
    const int TenRupee = 10;
}

// Types of coffee avilable
enum CoffeeTypes { 
    Filter = Coins::TwoRupee, 
    Black = Coins::OneRupee,
    Bru = Coins::FiveRupee,
    Nescafe = Coins::TenRupee
};  

#endif

