
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
    flagDTYPE filter_coffee_status;
    flagDTYPE black_coffee_status;
    flagDTYPE bru_coffee_status;
    flagDTYPE nescafe_coffee_status;

#ifdef _CATAPULT_
#pragma hls_design ccore
#endif
        flagDTYPE dispenser (const coffeeSelect& itemSelected) 
        {
            flagDTYPE returnFlag = 1;

            if (itemSelected.is_select_filter_coffee == 1) {
                filter_coffee_status = 1;
                black_coffee_status = 0;
                bru_coffee_status = 0;
                nescafe_coffee_status = 0;
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Coffee Dispensed is Filter Coffee" << endl;
#endif
            }
            else if (itemSelected.is_select_black_coffee == 1) {
                filter_coffee_status = 0;
                black_coffee_status = 1;
                bru_coffee_status = 0;
                nescafe_coffee_status = 0;
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Coffee Dispensed is Black Coffee" << endl;
#endif
            }
            else if (itemSelected.is_select_bru_coffee == 1) {
                filter_coffee_status = 0;
                black_coffee_status = 0;
                bru_coffee_status = 1;
                nescafe_coffee_status = 0;
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Coffee Dispensed is Bru Coffee" << endl;
#endif
            }
            else if (itemSelected.is_select_nescafe_coffee == 1) {
                filter_coffee_status = 0;
                black_coffee_status = 0;
                bru_coffee_status = 0;
                nescafe_coffee_status = 1;
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Coffee Dispensed is Nescafe Coffee" << endl;
#endif
            }
            else {
                filter_coffee_status = 0;
                black_coffee_status = 0;
                bru_coffee_status = 0;
                nescafe_coffee_status = 0;
#ifndef __SYNTHESIS__
            cout << "LOG: " << "No Coffee Dispensed" << endl;
#endif
                returnFlag = flagDTYPE(0);
            }

            return returnFlag;
        }

    public:
        ccdm() {
            yellow_led_status = 0;
            filter_coffee_status = 0;
            black_coffee_status = 0;
            bru_coffee_status = 0;
            nescafe_coffee_status = 0;
            coffee_served.is_select_filter_coffee = 0;
            coffee_served.is_select_black_coffee = 0;
            coffee_served.is_select_bru_coffee = 0;
            coffee_served.is_select_nescafe_coffee = 0;
        }

#ifdef _CATAPULT_
#pragma hls_design interface
#endif
        void CCS_BLOCK(run) (
                ac_channel<coffeeSelect> &coffeeRequest,
                ac_channel<flagDTYPE>& filter_coffee,
                ac_channel<flagDTYPE>& black_coffee,
                ac_channel<flagDTYPE>& bru_coffee,
                ac_channel<flagDTYPE>& nescafe_coffee,
                ac_channel<flagDTYPE>& coffee_dispensed
                )
        {
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Entering CCDM" << endl;
#endif
#ifndef __SYNTHESIS__
            if (coffeeRequest.available(1))
#endif
            {
                coffee_served = coffeeRequest.read();
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Received Coffee Request in CCDM" << endl;
#endif
            }

            coffee_dispensed.write(flagDTYPE(0));
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Waiting to Dispense" << endl;
#endif

            flagDTYPE status = 0;
            status = dispenser(coffee_served);

#ifndef __SYNTHESIS__
            cout << "LOG: " << "Dispensing Requested Coffee" << endl;
#endif
            filter_coffee.write(filter_coffee_status);
            black_coffee.write(black_coffee_status);
            bru_coffee.write(bru_coffee_status);
            nescafe_coffee.write(nescafe_coffee_status);

            if (status == flagDTYPE(1)) {
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Dispensing Coffee Status for AOEM" << endl;
#endif
                coffee_dispensed.write(flagDTYPE(1));
            }
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Leaving CCDM" << endl;
#endif
        }

};


#endif // _CCDM_H_
