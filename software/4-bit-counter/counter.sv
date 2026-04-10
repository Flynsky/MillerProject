`timescale 1ns / 1ps

module counter(
  input  logic clk,
  input  logic reset,
  input  logic [15:0] delay_ms,
  input  logic [3:0]  limit,
  output logic [3:0]  counter_value
);

  // interne Register
  logic [27:0] clk_counter = 0;
  logic [15:0] ms_counter  = 0;
  logic [3:0]  cnt_sig     = 0;

  // alles innerhalb eines always_ff Blocks
  always_ff @(posedge clk or posedge reset) begin
    if (reset) begin
      clk_counter <= 0;
      ms_counter  <= 0;
      cnt_sig     <= 0;
    end else begin
      clk_counter <= clk_counter + 1;

      // 1 ms bei 100 MHz Clock
      if (clk_counter >= 100_000 - 1) begin
        clk_counter <= 0;
        ms_counter  <= ms_counter + 1;
      end

      if (ms_counter >= delay_ms) begin
        ms_counter <= 0;
        cnt_sig    <= cnt_sig + 1;
      end

      if (cnt_sig >= limit) begin
        cnt_sig <= 0;
      end

      counter_value <= cnt_sig;
    end
  end

endmodule

