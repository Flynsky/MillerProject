// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vandgate_tb__Syms.h"


void Vandgate_tb___024root__trace_chg_0_sub_0(Vandgate_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vandgate_tb___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root__trace_chg_0\n"); );
    // Body
    Vandgate_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vandgate_tb___024root*>(voidSelf);
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vandgate_tb___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vandgate_tb___024root__trace_chg_0_sub_0(Vandgate_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root__trace_chg_0_sub_0\n"); );
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    bufp->chgBit(oldp+0,(vlSelfRef.andgate_tb__DOT__a));
    bufp->chgBit(oldp+1,(vlSelfRef.andgate_tb__DOT__b));
    bufp->chgBit(oldp+2,(((IData)(vlSelfRef.andgate_tb__DOT__a) 
                          & (IData)(vlSelfRef.andgate_tb__DOT__b))));
}

void Vandgate_tb___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root__trace_cleanup\n"); );
    // Locals
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    Vandgate_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vandgate_tb___024root*>(voidSelf);
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
