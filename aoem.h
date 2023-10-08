
/********************************************
 * Author:  Rishabh Jain
 * Date:    Oct'23
 * Desc:    Automated Order Entry Machine
********************************************/

#ifndef _AOEM_H_
#define _AOEM_H_

#include "defines.h"

// Defintion of Automated Order Entry Machine
class aoem {

    private:
        coffeeSelect itemSelected;
        ledDTYPE green_led_val;

        ledDTYPE costCheck (const coffeeSelect itemSelected) {
            ledDTYPE green_led_out = 0;

            if (itemSelected.is_select_filter_coffee == 1) {
                if (itemSelected.entered_coin == Coins::TwoRupee) {
                    green_led_out = 1;
                }
                else {
                    green_led_out = 0;
                }
            }
            else if (itemSelected.is_select_black_coffee == 1) {
                if (itemSelected.entered_coin == Coins::OneRupee) {
                    green_led_out = 1;
                }
                else {
                    green_led_out = 0;
                }
            }
            else if (itemSelected.is_select_bru_coffee == 1) {
                if (itemSelected.entered_coin == Coins::FiveRupee) {
                    green_led_out = 1;
                }
                else {
                    green_led_out = 0;
                }
            }
            else if (itemSelected.is_select_nescafe_coffee == 1) {
                if (itemSelected.entered_coin == Coins::TenRupee) {
                    green_led_out = 1;
                }
                else {
                    green_led_out = 0;
                }
            }
            else {
                is_select_filter_coffee = 0;
                is_select_black_coffee = 0;
                is_select_bru_coffee = 0;
                is_select_nescafe_coffee = 0;
                entered_coin = 0;
                green_led_out = 0;
            }

            return green_led_out;
        }


    public:
        aoem() {
            green_led_val = 0;
        }

        void CCS_BLOCK(run)(
                ac_channel<coffeeSelect> &coffeeEntered,
                ac_channel<coffeeSelect> &coffeeRequest,
                ac_channel<ledDTYPE> &green_led_ch
                )
        {
            itemSelected = coffeeEntered.read();

            green_led_val = costCheck(itemSelected);
            green_led_ch.write(green_led_val);

            if (green_led_val == 1) {
                coffeeRequest.write(itemSelected);
                green_led_ch.write(ledDTYPE(0));
            }

        }
        
};


#endif //_AOEM_H_ 
