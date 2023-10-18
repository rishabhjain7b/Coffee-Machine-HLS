
/***********************************************
 * Author:  Rishabh Jain
 * Date:    Oct'23
 * Desc:    Testbench for Coffee Vending System
************************************************/

#include <iostream>

#include "./cvs.h"
#include <mc_scverify.h>

// some functions for generating random test vectors
#include <mc_random.h>

static void throw_dice_for_inputBeverage(ac_channel<coffeeSelect > &inputBeverage) {
   coffeeSelect tmp_ac_chan_struct_inputBeverage;

   tmp_ac_chan_struct_inputBeverage.is_select_filter_coffee = 0;
   tmp_ac_chan_struct_inputBeverage.is_select_black_coffee = 0;
   tmp_ac_chan_struct_inputBeverage.is_select_bru_coffee = 0;
   tmp_ac_chan_struct_inputBeverage.is_select_nescafe_coffee = 1;

   inputBeverage.write(tmp_ac_chan_struct_inputBeverage);
}

static void throw_dice_for_inputCoins(ac_channel<coinSelect > &inputCoins) {
   coinSelect tmp_ac_chan_struct_inputCoins;

   tmp_ac_chan_struct_inputCoins.entered_one_rp = 0;
   tmp_ac_chan_struct_inputCoins.entered_two_rp = 0;
   tmp_ac_chan_struct_inputCoins.entered_five_rp = 0;
   tmp_ac_chan_struct_inputCoins.entered_ten_rp = 1;

   inputCoins.write(tmp_ac_chan_struct_inputCoins);
}

template <int val>
static void throw_dice_for_amountEntered(ac_channel<flagDTYPE> &amountEntered) {
   flagDTYPE tmp_amountEntered = val;
   amountEntered.write(tmp_amountEntered);
}


// -------------------------------------------
// Start of MAIN

CCS_MAIN(int argc, char *argv[])
{
   vendingSys __obj;

   // Place local testbench variables here
   ac_channel<coffeeSelect > inputBeverage;
   ac_channel<coinSelect > inputCoins;
   ac_channel<flagDTYPE> amountEntered;
   
   ac_channel<ledDTYPE > green_led_ch;
   ac_channel<ledDTYPE > yellow_led_ch;
   ac_channel<flagDTYPE > filter_coffee;
   ac_channel<flagDTYPE > black_coffee;
   ac_channel<flagDTYPE > bru_coffee;
   ac_channel<flagDTYPE > nescafe_coffee;
   
   // Main test iterations start here
   for (int iteration = 1; iteration <= 5; ++iteration) {

       // Set test values for this iteration
       throw_dice_for_inputBeverage(inputBeverage);
       throw_dice_for_inputCoins(inputCoins);

       // Progress indicator
       std::cout << "Iteration: " << iteration << std::endl;

       // Call original function and capture data
       __obj.run(inputBeverage, inputCoins, 
               green_led_ch, yellow_led_ch, 
               filter_coffee, black_coffee, bru_coffee, nescafe_coffee);


       // Flushing ac_channel based outputs
       while (green_led_ch.available(1)) (void)green_led_ch.read();
       while (yellow_led_ch.available(1)) (void)yellow_led_ch.read();
       while (filter_coffee.available(1)) (void)filter_coffee.read();
       while (black_coffee.available(1)) (void)black_coffee.read();
       while (bru_coffee.available(1)) (void)bru_coffee.read();
       while (nescafe_coffee.available(1)) (void)nescafe_coffee.read();
      
   }
   // Return success
   CCS_RETURN(0);
}
