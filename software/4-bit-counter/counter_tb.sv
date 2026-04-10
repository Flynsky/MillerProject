`timescale 1ns / 1ps

//module counter(
 // input logic clk,
 // input logic reset,
 // input logic[15:0] delay_ms,
 // input logic[3:0] limit,
 // output logic[3:0] counter_value
 // );

module counter_tb;
  logic clk;
  logic reset;
  logic[15:0] delay_ms;
  logic[3:0] limit;
  logic[3:0] counter_value;


  counter dut (
    .clk(clk),
    .reset(reset),
    .delay_ms(delay_ms),
    .limit(limit),
    .counter_value(counter_value)
    );

  always #5 clk = ~ clk;
  
  initial begin
  $dumpfile("wave.vcd");
  $dumpvars(0, counter_tb);
  end

  initial begin
  clk = 0;
  reset = 0;
  delay_ms = 1;
  limit = 5;
  counter_value = 0;
  #20000000;
  $finish;
  end
endmodule



