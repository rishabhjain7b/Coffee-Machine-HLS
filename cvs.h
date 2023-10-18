
/********************************************
 * Author:  Rishabh Jain
 * Date:    Oct'23
 * Desc:    Coffee Vending System Top
********************************************/

#ifndef _CVS_H_
#define _CVS_H_

#include "defines.h"
#include "aoem.h"
#include "ccdm.h"
#include <mc_scverify.h>

class vendingSys {
    
    private:
        // instance for automated order entry machine
        aoem aoem_inst;

        // instance for common coffee dispenser machine
        ccdm ccdm_inst;

        ac_channel<coffeeSelect> requestedBeverage;
        ac_channel<flagDTYPE> coffee_served;

    public:
        vendingSys() {}

#ifdef _CATAPULT_
#pragma hls_design interface top
#endif
        void CCS_BLOCK(run)(
                // Inputs
                ac_channel<coffeeSelect> &inputBeverage,
                ac_channel<coinSelect> &inputCoins,
                //ac_channel<flagDTYPE>& amountEntered,

                //Outputs
                ac_channel<ledDTYPE> &green_led_ch,
                ac_channel<ledDTYPE> &yellow_led_ch,
                ac_channel<flagDTYPE>& filter_coffee,
                ac_channel<flagDTYPE>& black_coffee,
                ac_channel<flagDTYPE>& bru_coffee,
                ac_channel<flagDTYPE>& nescafe_coffee
                )
        {
#ifndef __SYNTHESIS__
            cout << "LOG: " << "Machine Starts" << endl;
#endif

            // Call to automated order entry machine
            aoem_inst.run(inputBeverage, inputCoins, /*amountEntered,*/ coffee_served, 
                            requestedBeverage, green_led_ch, yellow_led_ch);
            
            // Call to common coffee dispenser machine
            ccdm_inst.run(requestedBeverage, filter_coffee, black_coffee, 
                            bru_coffee, nescafe_coffee, coffee_served);

#ifndef __SYNTHESIS__
            cout << "LOG: " << "Machine Ends" << endl;
#endif
        }
};
#endif // _CVS_H_
