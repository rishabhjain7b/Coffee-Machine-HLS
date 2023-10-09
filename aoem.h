
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

#ifdef _CATAPULT_
#pragma hls_design ccore
#pragma hls_ccore_type combinational
#endif
        ledDTYPE costCheck (const coffeeSelect& itemSelected, 
                            const coinDTYPE& amount) {
            ledDTYPE green_led_out = ledDTYPE(0);
            coinSelect coinUsed;

            if (itemSelected.is_select_filter_coffee == 1) {
                if (amount == coinUsed.TwoRp) { green_led_out = ledDTYPE(1); }
                else { green_led_out = ledDTYPE(0); }
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Coffee Selected is Filter Coffee" << endl;
#endif
            }
            else if (itemSelected.is_select_black_coffee == 1) {
                if (amount == coinUsed.OneRp) { green_led_out = ledDTYPE(1); }
                else { green_led_out = ledDTYPE(0); }
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Coffee Selected is Black Coffee" << endl;
#endif
            }
            else if (itemSelected.is_select_bru_coffee == 1) {
                if (amount == coinUsed.FiveRp) { green_led_out = ledDTYPE(1); }
                else { green_led_out = ledDTYPE(0); }
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Coffee Selected is Bru Coffee" << endl;
#endif
            }
            else if (itemSelected.is_select_nescafe_coffee == 1) {
                if (amount == coinUsed.TenRp) { green_led_out = ledDTYPE(1); }
                else { green_led_out = ledDTYPE(0); }
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Coffee Selected is Nescafe Coffee" << endl;
#endif
            }
            else { green_led_out = ledDTYPE(0); }

#ifndef __SYNTHESIS__
            cout << "LOG: " << "Amount Received = " << amount << endl;
            cout << "LOG: " << "if (Amount Received == Coffee Selected): " << green_led_out << endl;
#endif

            return green_led_out;
        }


    public:
        aoem() {
            green_led_val = ledDTYPE(0);
        }

#ifdef _CATAPULT_
#pragma hls_design interface
#endif
        void CCS_BLOCK(run)(
                // Inputs
                ac_channel<coffeeSelect> &coffeeEntered,
                ac_channel<coinSelect>& coinEntered,
                flagDTYPE& amountReceived,
                ac_channel<flagDTYPE>& is_dispensed,

                // Outputs
                ac_channel<coffeeSelect> &coffeeRequest,
                ac_channel<ledDTYPE> &green_led_ch,
                ac_channel<ledDTYPE> &yellow_led_ch
                )
        {
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Entering AOEM" << endl;
#endif
#ifndef __SYNTHESIS__
            if (coffeeEntered.available(1))
#endif
            {
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Received Coffee Request" << endl;
#endif
                itemSelected = coffeeEntered.read();
            }

            coinDTYPE sum = 0;

#ifndef __SYNTHESIS__
            while (coinEntered.available(1) )
#endif
            {
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Accepting Coins..." << endl;
#endif
                coinSelect coin = coinEntered.read();
                sum += coin.get_value(coin);
            }

            if (amountReceived == flagDTYPE(1)) {
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Checking Amount Received with Coffee Selected" << endl;
#endif
                green_led_val = costCheck(itemSelected, sum);
            }
            else {
                green_led_val = 0;
            }
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Green LED Output:" << green_led_val << endl;
#endif
            green_led_ch.write(green_led_val);

            if (green_led_val == 1) {
                coffeeRequest.write(itemSelected);
                green_led_ch.write(ledDTYPE(0));
                yellow_led_ch.write(ledDTYPE(1));
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Sending Request to CCD" << endl;
            cout << "LOG: " << "Green LED Output: 0" << endl;
            cout << "LOG: " << "Yellow LED Output: 1" << endl;
#endif
            }

            flagDTYPE dispense_status;
            if (is_dispensed.nb_read(dispense_status)) {
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Reading Dispense Status: " << dispense_status << endl;
#endif
                if (dispense_status == flagDTYPE(1)) {
                    yellow_led_ch.write(ledDTYPE(0));
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Yellow LED Output: 0" << endl;
#endif
                }
            }
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Leaving AOEM" << endl;
#endif
        
        }
        
};


#endif //_AOEM_H_ 
