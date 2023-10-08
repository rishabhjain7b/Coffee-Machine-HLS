
/********************************************
 * Author:  Rishabh Jain
 * Date:    Oct'23
 * Desc:    Common Coffee Dispenser Machine
********************************************/

#ifndef _CCDM_H_
#define _CCDM_H_

#include "defines.h"

class ccdm {

    ledDTYPE yellow_led_status;
    coffeeSelect coffee_served;

    public:
        ccdm() {
            yellow_led_status = 0;
        }

#ifdef _CATAPULT_
#pragma hls_design interface
#endif
        void CCS_BLOCK(run) (
                ac_channel<coffeeSelect> &coffeeRequest,
                ac_channel<ledDTYPE> &yellow_led_in_ch,
                ac_channel<ledDTYPE> &yellow_led_out_ch,
                ac_int<1, false> &coffee_dispensed
                )
        {
            yellow_led_status = yellow_led_in_ch.read();
            yellow_led_out_ch.write(yellow_led_status);

            if (yellow_led_status == ledDTYPE(1) ) {
                coffee_served = coffeeRequest.read();
                if (coffee_served.is_select_filter_coffee == 1 ||
                    coffee_served.is_select_black_coffee == 1 ||
                    coffee_served.is_select_bru_coffee == 1 ||
                    coffee_served.is_select_nescafe_coffee == 1)
                    coffee_dispensed = 1;

                yellow_led_status = !yellow_led_status;
                yellow_led_out_ch.write(yellow_led_status);
            }
            else {
                coffee_dispensed = 0;
            }
        }

};


#endif // _CCDM_H_
