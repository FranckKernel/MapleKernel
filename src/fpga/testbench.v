module testbench;
reg a, b;
wire sum, carry;

adder1bit uut (.a(a), .b(b), .sum(sum), .carry(carry));

initial begin
    $dumpfile("adder1bit.vcd");
    $dumpvars(0, testbench);

    a = 0; b = 0; #10;
    a = 0; b = 1; #10;
    a = 1; b = 0; #10;
    a = 1; b = 1; #10;

    $finish;
end
endmodule
