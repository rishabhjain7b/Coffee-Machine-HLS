
/********************************************
 * Author:  Rishabh Jain
 * Date:    Oct'23
 * Desc:    Coffee Vending System Top
********************************************/

#ifndef _CVS_H_
#define _CVS_H_

#include "defines.h"
#include "aoem_def.h"
#include "ccdm_def.h"
#include <mc_scverify.h>

class vendingSys {
    
    private:
        // instance for automated order entry machine
        aoem aoem_inst;

        // instance for common coffee dispenser machine
        ccdm ccdm_inst;

        ac_channel<coffeeSelect> requestedBeverage;

    public:
        vendingSys() {}

        void CCS_BLOCK(run)(
                ac_channel<coffeeSelect> &inputBeverage,
                ac_channel<ledDTYPE> &green_led_ch,
                ac_channel<ledDTYPE> &yellow_led_ch,
                ac_int<1, false> &coffee_served)
        {
            aoem_inst.run(inputBeverage, requestedBeverage, green_led_ch);
            ccdm_inst.run(requestedBeverage);
        }
};
#endif // _CVS_H_