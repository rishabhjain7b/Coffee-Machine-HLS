
#/********************************************************
# * Author:  Rishabh Jain
# * Date:    Oct'23
# * Desc:    TCL file for Catapult Ultra Synthesis 2023.2
#*********************************************************/
  
solution new -state initial
solution options defaults
solution options set /OnTheFly/VthAttributeType cell_lib
solution options set /Input/CompilerFlags {-D_CATAPULT_ }
solution options set /Output/GenerateCycleNetlist false
solution file add ./cvs.cpp -type C++
solution file add ./tb.cpp -exclude true
go new

go analyze

go compile

directive set STRICT_IO_SCHEDULING default

solution library add mgc_Xilinx-ZYNQ-uplus-1LV_beh -- -rtlsyntool Vivado -manufacturer Xilinx -family ZYNQ-uplus -speed -1LV -part xczu11eg-ffvb1517-1LV-i
solution library add Xilinx_RAMS
solution library add Xilinx_ROMS
solution library add Xilinx_FIFO
go libraries

directive set -CLOCKS {clk {-CLOCK_PERIOD 100.0 -CLOCK_EDGE rising -CLOCK_UNCERTAINTY 0.0 -CLOCK_HIGH_TIME 50.0 -RESET_SYNC_NAME rst -RESET_ASYNC_NAME arst_n -RESET_KIND sync -RESET_SYNC_ACTIVE high -RESET_ASYNC_ACTIVE low -ENABLE_ACTIVE high}}
go assembly

directive set /vendingSys/aoem/run/main -PIPELINE_INIT_INTERVAL 2
directive set /vendingSys/aoem/run/main -PIPELINE_STALL_MODE flush

directive set /vendingSys/ccdm/run/main -PIPELINE_INIT_INTERVAL 2
directive set /vendingSys/ccdm/run/main -PIPELINE_STALL_MODE flush

go extract


#flow run /SCVerify/launch_make ./scverify/Verify_concat_sim_rtl_v_msim.mk {} SIMTOOL=msim simgui

