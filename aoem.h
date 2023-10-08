
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


    public:
        aoem() {}

        void CCS_BLOCK(run)(
                ac_channel<coffeeSelect> &coffeeEntered,
                ac_channel<coffeeSelect> &coffeeRequest,
                ac_channel<ledDTYPE> &green_led_ch
                )
        {
            itemSelected = coffeeEntered.read();



        }
        
};


#endif //_AOEM_H_ 
