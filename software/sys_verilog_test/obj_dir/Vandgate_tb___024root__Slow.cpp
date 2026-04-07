// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vandgate_tb.h for the primary calling header

#include "Vandgate_tb__pch.h"

void Vandgate_tb___024root___ctor_var_reset(Vandgate_tb___024root* vlSelf);

Vandgate_tb___024root::Vandgate_tb___024root(Vandgate_tb__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vandgate_tb___024root___ctor_var_reset(this);
}

void Vandgate_tb___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vandgate_tb___024root::~Vandgate_tb___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
