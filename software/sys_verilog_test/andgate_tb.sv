`timescale 1ns/1ps

module andgate_tb;

    // Testbench-Signale
    logic a;
    logic b;
    logic y;

    // Instanz des DUT (Device Under Test)
    andgate dut (
        .a(a),
        .b(b),
        .y(y)
    );

    // Testablauf
    initial begin
        $display("a b | y");
        $display("---------");
        $dumpfile("wave.vcd");
        $dumpvars(0,andgate_tb);

        a = 0; b = 0; #10;
        $display("%b %b | %b", a, b, y);

        a = 0; b = 1; #10;
        $display("%b %b | %b", a, b, y);

        a = 1; b = 0; #10;
        $display("%b %b | %b", a, b, y);

        a = 1; b = 1; #10;
        $display("%b %b | %b", a, b, y);

        $finish;
    end

endmodule
