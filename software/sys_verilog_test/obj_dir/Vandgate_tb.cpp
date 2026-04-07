// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vandgate_tb__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vandgate_tb::Vandgate_tb(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vandgate_tb__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vandgate_tb::Vandgate_tb(const char* _vcname__)
    : Vandgate_tb(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vandgate_tb::~Vandgate_tb() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vandgate_tb___024root___eval_debug_assertions(Vandgate_tb___024root* vlSelf);
#endif  // VL_DEBUG
void Vandgate_tb___024root___eval_static(Vandgate_tb___024root* vlSelf);
void Vandgate_tb___024root___eval_initial(Vandgate_tb___024root* vlSelf);
void Vandgate_tb___024root___eval_settle(Vandgate_tb___024root* vlSelf);
void Vandgate_tb___024root___eval(Vandgate_tb___024root* vlSelf);

void Vandgate_tb::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vandgate_tb::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vandgate_tb___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vandgate_tb___024root___eval_static(&(vlSymsp->TOP));
        Vandgate_tb___024root___eval_initial(&(vlSymsp->TOP));
        Vandgate_tb___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vandgate_tb___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

void Vandgate_tb::eval_end_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+eval_end_step Vandgate_tb::eval_end_step\n"); );
#ifdef VM_TRACE
    // Tracing
    if (VL_UNLIKELY(vlSymsp->__Vm_dumping)) vlSymsp->_traceDump();
#endif  // VM_TRACE
}

//============================================================
// Events and timing
bool Vandgate_tb::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vandgate_tb::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vandgate_tb::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vandgate_tb___024root___eval_final(Vandgate_tb___024root* vlSelf);

VL_ATTR_COLD void Vandgate_tb::final() {
    contextp()->executingFinal(true);
    Vandgate_tb___024root___eval_final(&(vlSymsp->TOP));
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vandgate_tb::hierName() const { return vlSymsp->name(); }
const char* Vandgate_tb::modelName() const { return "Vandgate_tb"; }
unsigned Vandgate_tb::threads() const { return 1; }
void Vandgate_tb::prepareClone() const { contextp()->prepareClone(); }
void Vandgate_tb::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vandgate_tb::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vandgate_tb___024root__trace_decl_types(VerilatedVcd* tracep);

void Vandgate_tb___024root__trace_init_top(Vandgate_tb___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vandgate_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vandgate_tb___024root*>(voidSelf);
    Vandgate_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vandgate_tb___024root__trace_decl_types(tracep);
    Vandgate_tb___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vandgate_tb___024root__trace_register(Vandgate_tb___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vandgate_tb::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vandgate_tb::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP), name(), false, 3);
    Vandgate_tb___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
