//  Catapult Ultra Synthesis 2023.2/1059873 (Production Release) Mon Aug  7 10:54:31 PDT 2023
//  
//          Copyright (c) Siemens EDA, 1996-2023, All Rights Reserved.
//                        UNPUBLISHED, LICENSED SOFTWARE.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                   PROPERTY OF SIEMENS EDA OR ITS LICENSORS.
//  
//  Running on Linux rijain@orw-cds-bm20 3.10.0-1160.92.1.el7.x86_64 x86_64 aol
//  
//  Package information: SIFLIBS v26.2_0.0, HLS_PKGS v26.2_0.0, 
//                       SIF_TOOLKITS v26.2_0.0, SIF_XILINX v26.2_0.0, 
//                       SIF_ALTERA v26.2_0.0, CCS_LIBS v26.2_0.0, 
//                       CDS_PPRO v2023.1, CDS_DesignChecker v2023.2, 
//                       CDS_OASYS v21.1_3.1, CDS_PSR v23.1_1.18, 
//                       DesignPad v2.78_1.0
//  
solution new -state initial
solution options defaults
solution options set /OnTheFly/VthAttributeType cell_lib
solution options set /Input/CompilerFlags {-D_CATAPULT_ }
solution options set /Output/GenerateCycleNetlist false
solution file add ./cvs.cpp -type C++
directive set -DESIGN_GOAL area
directive set -SPECULATE true
directive set -MERGEABLE true
directive set -REGISTER_THRESHOLD 256
directive set -MEM_MAP_THRESHOLD 32
directive set -LOGIC_OPT false
directive set -FSM_ENCODING none
directive set -FSM_BINARY_ENCODING_THRESHOLD 64
directive set -REG_MAX_FANOUT 0
directive set -NO_X_ASSIGNMENTS true
directive set -SAFE_FSM false
directive set -REGISTER_SHARING_MAX_WIDTH_DIFFERENCE 8
directive set -REGISTER_SHARING_LIMIT 0
directive set -ASSIGN_OVERHEAD 0
directive set -TIMING_CHECKS true
directive set -MUXPATH true
directive set -REALLOC true
directive set -UNROLL no
directive set -IO_MODE super
directive set -CHAN_IO_PROTOCOL use_library
directive set -ARRAY_SIZE 1024
directive set -IDLE_SIGNAL {}
directive set -STALL_FLAG_SV off
directive set -STALL_FLAG false
directive set -TRANSACTION_DONE_SIGNAL true
directive set -DONE_FLAG {}
directive set -READY_FLAG {}
directive set -START_FLAG {}
directive set -TRANSACTION_SYNC ready
directive set -RESET_CLEARS_ALL_REGS use_library
directive set -CLOCK_OVERHEAD 20.000000
directive set -ON_THE_FLY_PROTOTYPING false
directive set -OPT_CONST_MULTS use_library
directive set -CHARACTERIZE_ROM false
directive set -PROTOTYPE_ROM true
directive set -ROM_THRESHOLD 64
directive set -CLUSTER_ADDTREE_IN_WIDTH_THRESHOLD 0
directive set -CLUSTER_ADDTREE_IN_COUNT_THRESHOLD 0
directive set -CLUSTER_OPT_CONSTANT_INPUTS true
directive set -CLUSTER_RTL_SYN false
directive set -CLUSTER_FAST_MODE false
directive set -CLUSTER_TYPE combinational
directive set -PROTOTYPING_ENGINE oasys
directive set -PIPELINE_RAMP_UP true
go new
go analyze
go compile
solution library add mgc_Xilinx-ZYNQ-uplus-1LV_beh -- -rtlsyntool Vivado -manufacturer Xilinx -family ZYNQ-uplus -speed -1LV -part xczu11eg-ffvb1517-1LV-i
solution library add Xilinx_RAMS
solution library add Xilinx_ROMS
go libraries
directive set -CLOCKS {clk {-CLOCK_PERIOD 100.0 -CLOCK_EDGE rising -CLOCK_UNCERTAINTY 0.0 -CLOCK_HIGH_TIME 50.0 -RESET_SYNC_NAME rst -RESET_ASYNC_NAME arst_n -RESET_KIND sync -RESET_SYNC_ACTIVE high -RESET_ASYNC_ACTIVE low -ENABLE_ACTIVE high}}
go assembly
directive set /vendingSys/ccdm/coffeeRequest:rsc -FIFO_DEPTH 4
directive set /vendingSys/aoem/coffeeRequest:rsc -FIFO_DEPTH 4
directive set /vendingSys/requestedBeverage:cns -FIFO_DEPTH 4
directive set /vendingSys/ccdm/yellow_led_in_ch:rsc -FIFO_DEPTH -1
directive set /vendingSys/aoem/yellow_led_ch:rsc -FIFO_DEPTH -1
directive set /vendingSys/yellow_led_sh_ch:cns -FIFO_DEPTH -1
go architect
go extract