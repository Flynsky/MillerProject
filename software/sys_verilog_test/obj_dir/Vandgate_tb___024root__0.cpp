// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vandgate_tb.h for the primary calling header

#include "Vandgate_tb__pch.h"

VlCoroutine Vandgate_tb___024root___eval_initial__TOP__Vtiming__0(Vandgate_tb___024root* vlSelf);

void Vandgate_tb___024root___eval_initial(Vandgate_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___eval_initial\n"); );
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vandgate_tb___024root___eval_initial__TOP__Vtiming__0(vlSelf);
}

VlCoroutine Vandgate_tb___024root___eval_initial__TOP__Vtiming__0(Vandgate_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("a b | y\n---------\n",0);
    vlSymsp->_vm_contextp__->dumpfile("wave.vcd"s);
    vlSymsp->_traceDumpOpen();
    vlSelfRef.andgate_tb__DOT__a = 0U;
    vlSelfRef.andgate_tb__DOT__b = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "andgate_tb.sv", 
                                         24);
    VL_WRITEF_NX("%b %b | %b\n",3, '#',1,vlSelfRef.andgate_tb__DOT__a
                 , '#',1,(IData)(vlSelfRef.andgate_tb__DOT__b)
                 , '#',1,vlSelfRef.andgate_tb__DOT__dut__DOT__y);
    vlSelfRef.andgate_tb__DOT__a = 0U;
    vlSelfRef.andgate_tb__DOT__b = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "andgate_tb.sv", 
                                         27);
    VL_WRITEF_NX("%b %b | %b\n",3, '#',1,vlSelfRef.andgate_tb__DOT__a
                 , '#',1,(IData)(vlSelfRef.andgate_tb__DOT__b)
                 , '#',1,vlSelfRef.andgate_tb__DOT__dut__DOT__y);
    vlSelfRef.andgate_tb__DOT__a = 1U;
    vlSelfRef.andgate_tb__DOT__b = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "andgate_tb.sv", 
                                         30);
    VL_WRITEF_NX("%b %b | %b\n",3, '#',1,vlSelfRef.andgate_tb__DOT__a
                 , '#',1,(IData)(vlSelfRef.andgate_tb__DOT__b)
                 , '#',1,vlSelfRef.andgate_tb__DOT__dut__DOT__y);
    vlSelfRef.andgate_tb__DOT__a = 1U;
    vlSelfRef.andgate_tb__DOT__b = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                         nullptr, "andgate_tb.sv", 
                                         33);
    VL_WRITEF_NX("%b %b | %b\n",3, '#',1,vlSelfRef.andgate_tb__DOT__a
                 , '#',1,(IData)(vlSelfRef.andgate_tb__DOT__b)
                 , '#',1,vlSelfRef.andgate_tb__DOT__dut__DOT__y);
    VL_FINISH_MT("andgate_tb.sv", 36, "");
    co_return;
}

void Vandgate_tb___024root___eval_triggers_vec__act(Vandgate_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___eval_triggers_vec__act\n"); );
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(vlSelfRef.__VdlySched.awaitingCurrentTime()));
}

bool Vandgate_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vandgate_tb___024root___act_sequent__TOP__0(Vandgate_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___act_sequent__TOP__0\n"); );
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.andgate_tb__DOT__dut__DOT__y = ((IData)(vlSelfRef.andgate_tb__DOT__a) 
                                              & (IData)(vlSelfRef.andgate_tb__DOT__b));
}

void Vandgate_tb___024root___eval_act(Vandgate_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___eval_act\n"); );
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        Vandgate_tb___024root___act_sequent__TOP__0(vlSelf);
    }
}

void Vandgate_tb___024root___eval_nba(Vandgate_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___eval_nba\n"); );
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vandgate_tb___024root___act_sequent__TOP__0(vlSelf);
    }
}

void Vandgate_tb___024root___timing_resume(Vandgate_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___timing_resume\n"); );
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vandgate_tb___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vandgate_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vandgate_tb___024root___eval_phase__act(Vandgate_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___eval_phase__act\n"); );
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vandgate_tb___024root___eval_triggers_vec__act(vlSelf);
    Vandgate_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vandgate_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vandgate_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vandgate_tb___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vandgate_tb___024root___timing_resume(vlSelf);
        Vandgate_tb___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vandgate_tb___024root___eval_phase__inact(Vandgate_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___eval_phase__inact\n"); );
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("andgate_tb.sv", 3, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vandgate_tb___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vandgate_tb___024root___eval_phase__nba(Vandgate_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___eval_phase__nba\n"); );
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vandgate_tb___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vandgate_tb___024root___eval_nba(vlSelf);
        Vandgate_tb___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vandgate_tb___024root___eval(Vandgate_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___eval\n"); );
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vandgate_tb___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("andgate_tb.sv", 3, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("andgate_tb.sv", 3, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vandgate_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("andgate_tb.sv", 3, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vandgate_tb___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vandgate_tb___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vandgate_tb___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vandgate_tb___024root___eval_debug_assertions(Vandgate_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vandgate_tb___024root___eval_debug_assertions\n"); );
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
