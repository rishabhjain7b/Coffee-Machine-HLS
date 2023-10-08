
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

    public:
        ccdm() {
            yellow_led_status = 0;
        }

        void CCS_BLOCK(run) (
                ac_channel<coffeeSelect> &coffeeRequest,
                ac_channel<ledDTYPE> &yellow_led_in_ch,
                ac_channel<ledDTYPE> &yellow_led_out_ch,
                ac_int<1, false> &coffee_served
                )
        {
            yellow_led_status = yellow_led_in_ch.read();
            yellow_led_out_ch.write(yellow_led_status);

            if (yellow_led_status == ledDTYPE(1) ) {
                // DISPENSE COFEE
                coffee_served = 1;
                yellow_led_status = !yellow_led_status;
                yellow_led_out_ch.write(yellow_led_status);
            }
            else {
                coffee_served = 0;
            }
        }

};


#endif // _CCDM_H_
