
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
        ledDTYPE yellow_led_val;

#ifdef _CATAPULT_
#pragma hls_design ccore
#pragma hls_ccore_type combinational
#endif
        ledDTYPE costCheck (const coffeeSelect& itemSelected, 
                            const coinDTYPE& amount) {
            ledDTYPE green_led_out = ledDTYPE(0);

            if (itemSelected.is_select_filter_coffee == 1) {
                if (amount == Coins::TwoRp) { green_led_out = ledDTYPE(1); }
                else { green_led_out = ledDTYPE(0); }

#ifdef _DEBUG_
            cout << "LOG: " << "Coffee Selected is Filter Coffee" << endl;
#endif

            }
            else if (itemSelected.is_select_black_coffee == 1) {
                if (amount == Coins::OneRp) { green_led_out = ledDTYPE(1); }
                else { green_led_out = ledDTYPE(0); }

#ifdef _DEBUG_
            cout << "LOG: " << "Coffee Selected is Black Coffee" << endl;
#endif

            }
            else if (itemSelected.is_select_bru_coffee == 1) {
                if (amount == Coins::FiveRp) { green_led_out = ledDTYPE(1); }
                else { green_led_out = ledDTYPE(0); }

#ifdef _DEBUG_
            cout << "LOG: " << "Coffee Selected is Bru Coffee" << endl;
#endif

            }
            else if (itemSelected.is_select_nescafe_coffee == 1) {
                if (amount == Coins::TenRp) { green_led_out = ledDTYPE(1); }
                else { green_led_out = ledDTYPE(0); }

#ifdef _DEBUG_
            cout << "LOG: " << "Coffee Selected is Nescafe Coffee" << endl;
#endif

            }
            else { green_led_out = ledDTYPE(0); }

#ifdef _DEBUG_
            cout << "LOG: " << "Amount Received = " << amount << endl;
            cout << "LOG: " << "if (Amount Received == Coffee Selected): " << green_led_out << endl;
#endif

            return green_led_out;
        }


    public:
        aoem() {
            green_led_val = ledDTYPE(0);
            yellow_led_val = ledDTYPE(0);
        }

#ifdef _CATAPULT_
#pragma hls_design interface
#endif
        void CCS_BLOCK(run)(
                // Inputs
                ac_channel<coffeeSelect> &coffeeEntered,
                ac_channel<coinSelect>& coinEntered,
                ac_channel<flagDTYPE>& is_dispensed,

                // Outputs
                ac_channel<coffeeSelect> &coffeeRequest,
                ac_channel<ledDTYPE> &green_led_ch,
                ac_channel<ledDTYPE> &yellow_led_ch
                )
        {

#ifdef _DEBUG_
            cout << "LOG: " << "Entering AOEM" << endl;
#endif
            flagDTYPE amountReceived = flagDTYPE(0);
            flagDTYPE itemReceived = flagDTYPE(0);

#ifndef __SYNTHESIS__
            if (coffeeEntered.available(1))
#endif
            {

#ifdef _DEBUG_
                cout << "LOG: " << "Received Coffee Request" << endl;
#endif

                itemSelected = coffeeEntered.read();
                itemReceived = flagDTYPE(1);
            }

            coinDTYPE sum = 0;

#ifndef __SYNTHESIS__
            while (coinEntered.available(1) )
#endif
            {

#ifdef _DEBUG_
                cout << "LOG: " << "Accepting Coins..." << endl;
#endif

                coinSelect coin = coinEntered.read();
                sum += coin.get_value(coin);
                amountReceived = flagDTYPE(1);
            }

            if (amountReceived == flagDTYPE(1) && itemReceived == flagDTYPE(1)) {

#ifdef _DEBUG_
                cout << "LOG: " << "Checking Amount Received with Coffee Selected" << endl;
#endif

                green_led_val = costCheck(itemSelected, sum);
                yellow_led_val = ~green_led_val;
                amountReceived = flagDTYPE(0);
                itemReceived = flagDTYPE(0);

#ifdef _DEBUG_
                cout << "LOG: " << "Green LED Output:" << green_led_val << endl;
                cout << "LOG: " << "Yellow LED Output:" << yellow_led_val << endl;
#endif

                green_led_ch.write(green_led_val);
                yellow_led_ch.write(yellow_led_val);
            }

            if (green_led_val == flagDTYPE(1) && yellow_led_val == flagDTYPE(0)) {

                coffeeRequest.write(itemSelected);

                green_led_val = flagDTYPE(0);
                yellow_led_val = ~green_led_val;

                green_led_ch.write(green_led_val);
                yellow_led_ch.write(yellow_led_val);

#ifdef _DEBUG_
                cout << "LOG: " << "Sending Request to CCD" << endl;
                cout << "LOG: " << "Green LED Output:" << green_led_val << endl;
                cout << "LOG: " << "Yellow LED Output:" << yellow_led_val << endl;
#endif

            }

            flagDTYPE dispense_status = flagDTYPE(0);

            if (green_led_val == flagDTYPE(0) && yellow_led_val == flagDTYPE(1)) 
            {
#ifndef __SYNTHESIS__
                if (is_dispensed.available(1))
#endif
                {
                    dispense_status = is_dispensed.read(); 
                }

#ifdef _DEBUG_
                cout << "LOG: " << "Reading Dispense Status: " << dispense_status << endl;
#endif

                if (dispense_status == flagDTYPE(1)) {
                    yellow_led_val = ~dispense_status;
                }
                
                yellow_led_ch.write(yellow_led_val);

#ifdef _DEBUG_
                    cout << "LOG: " << "Yellow LED Output: " << yellow_led_val << endl;
#endif

            }


#ifdef _DEBUG_
            cout << "LOG: " << "Leaving AOEM" << endl;
#endif
        
        }
        
};


#endif //_AOEM_H_ 
