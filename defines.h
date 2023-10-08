
#ifndef _DEF_H_
#define _DEF_H_

#include <ac_int.h>
#include <ac_channel.h>
#include <mc_scverify.h>

typedef ac_int<4, false> coinDTYPE;
typedef ac_int<1, false> ledDTYPE;

struct coffeeSelect {
    ac_int<1, false> is_select_filter_coffee;
    ac_int<1, false> is_select_black_coffee;
    ac_int<1, false> is_select_bru_coffee;
    ac_int<1, false> is_select_nescafe_coffee;
    coinDTYPE entered_coin;

    coffeeSelect() {
        is_select_filter_coffee = 0;
        is_select_black_coffee = 0;
        is_select_bru_coffee = 0;
        is_select_nescafe_coffee = 0;
        entered_coin = 0;
    }
};

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
    const coinDTYPE OneRupee = 1;
    const coinDTYPE TwoRupee = 2;
    const coinDTYPE FiveRupee = 5;
    const coinDTYPE TenRupee = 10;
}

// Types of coffee avilable
enum CoffeeTypes { 
    Filter = Coins::TwoRupee, 
    Black = Coins::OneRupee,
    Bru = Coins::FiveRupee,
    Nescafe = Coins::TenRupee
};  

#endif

