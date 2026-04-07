// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vandgate_tb.h for the primary calling header

#ifndef VERILATED_VANDGATE_TB___024ROOT_H_
#define VERILATED_VANDGATE_TB___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vandgate_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vandgate_tb___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ andgate_tb__DOT__a;
    CData/*0:0*/ andgate_tb__DOT__b;
    CData/*0:0*/ andgate_tb__DOT__dut__DOT__y;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlDelayScheduler __VdlySched;

    // INTERNAL VARIABLES
    Vandgate_tb__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vandgate_tb___024root(Vandgate_tb__Syms* symsp, const char* namep);
    ~Vandgate_tb___024root();
    VL_UNCOPYABLE(Vandgate_tb___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
