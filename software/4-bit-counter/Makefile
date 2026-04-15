FPGA_DEVICE = CCGM1A1
TOP = counter
TOP_TB = counter_tb
TESTBENCH = counter_tb.sv
FILE_SV_0 = counter.sv
BITFILE = out.txt
BITSTREAM = bitfile.txt
TEST_BITSTREAM = blinky_test.bit
# PATH_OPENFPGALOADER = /home/furz1000/olimex-gatemate/oss-cad-suite/bin/openFPGALoader 
PATH_OPENFPGALOADER = /home/fynn/opt/oss-cad-suite/bin/openFPGALoader
synthesize:
	yosys -ql synth_log.txt -p "read_verilog -defer -sv $(FILE_SV_0); synth_gatemate -top $(TOP) -luttree -nomx8; write_json $(TOP)_netlist.json; write_verilog $(TOP)_netlist.v"

schematic:
	yosys -p "read_verilog -sv $(FILE_SV_0); synth; show -format png -prefix schematic"


simulation:
	verilator --binary --trace --sv $(FILE_SV_0) $(TESTBENCH) --top $(TOP_TB)
	./obj_dir/Vcounter_tb
	gtkwave wave.vcd

gui_implement:
	nextpnr-himbaechel --device=$(FPGA_DEVICE) --gui

implement:
	nextpnr-himbaechel --device=$(FPGA_DEVICE) --vopt allow-unconstrained --json $(TOP)_netlist.json -o out=out.txt --router router2

bitstream:
	gmpack $(BITFILE) $(BITSTREAM)


flash:
	sudo $(PATH_OPENFPGALOADER) -c dirtyJtag $(TEST_BITSTREAM)

clean:
	rm schematic.dot schematic.png $(BITFILE) $(BITSTREAM) wave.vcd
#olimex_gatemateevb         dirtyJtag          GM1A1                    
#gatemate_evb_spi         0x0403:6010
#/home/furz1000/olimex-gatemate/oss-cad-suite/bin
# sudo /home/furz1000/olimex-gatemate/oss-cad-suite/bin/openFPGALoader -c dirtyJtag blinky_test.bit
