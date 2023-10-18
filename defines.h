
/********************************************
 * Author:  Rishabh Jain
 * Date:    Oct'23
 * Desc:    Coffee Vending System Definitions
********************************************/

#ifndef _DEF_H_
#define _DEF_H_

#include <ac_int.h>
#include <ac_channel.h>
#include <ac_wait.h>

#ifndef __SYNTHESIS__
#include <iostream>
using namespace std;
#endif

#include <mc_scverify.h>

typedef ac_int<4, false> coinDTYPE;
typedef ac_int<1, false> ledDTYPE;
typedef ac_int<1, false> flagDTYPE;

// Types of coins available
namespace Coins {
    const coinDTYPE OneRp = 1;
    const coinDTYPE TwoRp = 2;
    const coinDTYPE FiveRp = 5;
    const coinDTYPE TenRp = 10;
}

// Defintions of types of Coins available
struct coinSelect {
    flagDTYPE entered_one_rp;
    flagDTYPE entered_two_rp;
    flagDTYPE entered_five_rp;
    flagDTYPE entered_ten_rp;

    coinSelect() {
        entered_one_rp = 0;
        entered_two_rp = 0;
        entered_five_rp = 0;
        entered_ten_rp = 0;
    }

    coinDTYPE get_value ( const coinSelect& input ) {
        if (input.entered_one_rp == flagDTYPE(1)) {
            return Coins::OneRp;
        }
        else if (input.entered_two_rp == flagDTYPE(1)) {
            return Coins::TwoRp;
        }
        else if (input.entered_five_rp == flagDTYPE(1)) {
            return Coins::FiveRp;
        }
        else if (input.entered_ten_rp == flagDTYPE(1)) {
            return Coins::TenRp;
        }
        else {
            return coinDTYPE(0);
        }
    }
};

struct coffeeSelect {
    flagDTYPE is_select_filter_coffee;
    flagDTYPE is_select_black_coffee;
    flagDTYPE is_select_bru_coffee;
    flagDTYPE is_select_nescafe_coffee;

    coffeeSelect() {
        is_select_filter_coffee = 0;
        is_select_black_coffee = 0;
        is_select_bru_coffee = 0;
        is_select_nescafe_coffee = 0;
    }
};


#endif //_DEF_H_

