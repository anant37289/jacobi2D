#ifndef _DECL_jacobi2d_H_
#define _DECL_jacobi2d_H_
#include "charm++.h"
#include "envelope.h"
#include <memory>
#include "sdag.h"
#include "jacobi2d.h"

/* DECLS: readonly CProxy_Main main_proxy;
 */

/* DECLS: readonly CProxy_Block block_proxy;
 */

/* DECLS: readonly int grid_width;
 */

/* DECLS: readonly int grid_height;
 */

/* DECLS: readonly int n_chares_x;
 */

/* DECLS: readonly int n_chares_y;
 */

/* DECLS: readonly int n_iters;
 */

/* DECLS: readonly int warmup_iters;
 */

/* DECLS: readonly bool sync_ver;
 */

/* DECLS: readonly bool use_zerocopy;
 */

/* DECLS: readonly bool print_elements;
 */

/* DECLS: mainchare Main: Chare{
Main(CkArgMsg* impl_msg);
void initDone();
void startIter();
void updateDone();
void commDone();
void allDone();
void printDone();
};
 */
 class Main;
 class CkIndex_Main;
 class CProxy_Main;
/* --------------- index object ------------------ */
class CkIndex_Main:public CkIndex_Chare{
  public:
    typedef Main local_t;
    typedef CkIndex_Main index_t;
    typedef CProxy_Main proxy_t;
    typedef CProxy_Main element_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: Main(CkArgMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_Main_CkArgMsg();
    // Entry point index lookup
    
    inline static int idx_Main_CkArgMsg() {
      static int epidx = reg_Main_CkArgMsg();
      return epidx;
    }

    
    static int ckNew(CkArgMsg* impl_msg) { return idx_Main_CkArgMsg(); }
    
    static void _call_Main_CkArgMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_Main_CkArgMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void initDone();
     */
    // Entry point registration at startup
    
    static int reg_initDone_void();
    // Entry point index lookup
    
    inline static int idx_initDone_void() {
      static int epidx = reg_initDone_void();
      return epidx;
    }

    
    inline static int idx_initDone(void (Main::*)() ) {
      return idx_initDone_void();
    }


    
    static int initDone() { return idx_initDone_void(); }
    // Entry point registration at startup
    
    static int reg_redn_wrapper_initDone_void();
    // Entry point index lookup
    
    inline static int idx_redn_wrapper_initDone_void() {
      static int epidx = reg_redn_wrapper_initDone_void();
      return epidx;
    }
    
    static int redn_wrapper_initDone(CkReductionMsg* impl_msg) { return idx_redn_wrapper_initDone_void(); }
    
    static void _call_redn_wrapper_initDone_void(void* impl_msg, void* impl_obj_void);
    
    static void _call_initDone_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initDone_void(void* impl_msg, void* impl_obj);
    /* DECLS: void startIter();
     */
    // Entry point registration at startup
    
    static int reg_startIter_void();
    // Entry point index lookup
    
    inline static int idx_startIter_void() {
      static int epidx = reg_startIter_void();
      return epidx;
    }

    
    inline static int idx_startIter(void (Main::*)() ) {
      return idx_startIter_void();
    }


    
    static int startIter() { return idx_startIter_void(); }
    
    static void _call_startIter_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_startIter_void(void* impl_msg, void* impl_obj);
    /* DECLS: void updateDone();
     */
    // Entry point registration at startup
    
    static int reg_updateDone_void();
    // Entry point index lookup
    
    inline static int idx_updateDone_void() {
      static int epidx = reg_updateDone_void();
      return epidx;
    }

    
    inline static int idx_updateDone(void (Main::*)() ) {
      return idx_updateDone_void();
    }


    
    static int updateDone() { return idx_updateDone_void(); }
    // Entry point registration at startup
    
    static int reg_redn_wrapper_updateDone_void();
    // Entry point index lookup
    
    inline static int idx_redn_wrapper_updateDone_void() {
      static int epidx = reg_redn_wrapper_updateDone_void();
      return epidx;
    }
    
    static int redn_wrapper_updateDone(CkReductionMsg* impl_msg) { return idx_redn_wrapper_updateDone_void(); }
    
    static void _call_redn_wrapper_updateDone_void(void* impl_msg, void* impl_obj_void);
    
    static void _call_updateDone_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_updateDone_void(void* impl_msg, void* impl_obj);
    /* DECLS: void commDone();
     */
    // Entry point registration at startup
    
    static int reg_commDone_void();
    // Entry point index lookup
    
    inline static int idx_commDone_void() {
      static int epidx = reg_commDone_void();
      return epidx;
    }

    
    inline static int idx_commDone(void (Main::*)() ) {
      return idx_commDone_void();
    }


    
    static int commDone() { return idx_commDone_void(); }
    // Entry point registration at startup
    
    static int reg_redn_wrapper_commDone_void();
    // Entry point index lookup
    
    inline static int idx_redn_wrapper_commDone_void() {
      static int epidx = reg_redn_wrapper_commDone_void();
      return epidx;
    }
    
    static int redn_wrapper_commDone(CkReductionMsg* impl_msg) { return idx_redn_wrapper_commDone_void(); }
    
    static void _call_redn_wrapper_commDone_void(void* impl_msg, void* impl_obj_void);
    
    static void _call_commDone_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_commDone_void(void* impl_msg, void* impl_obj);
    /* DECLS: void allDone();
     */
    // Entry point registration at startup
    
    static int reg_allDone_void();
    // Entry point index lookup
    
    inline static int idx_allDone_void() {
      static int epidx = reg_allDone_void();
      return epidx;
    }

    
    inline static int idx_allDone(void (Main::*)() ) {
      return idx_allDone_void();
    }


    
    static int allDone() { return idx_allDone_void(); }
    // Entry point registration at startup
    
    static int reg_redn_wrapper_allDone_void();
    // Entry point index lookup
    
    inline static int idx_redn_wrapper_allDone_void() {
      static int epidx = reg_redn_wrapper_allDone_void();
      return epidx;
    }
    
    static int redn_wrapper_allDone(CkReductionMsg* impl_msg) { return idx_redn_wrapper_allDone_void(); }
    
    static void _call_redn_wrapper_allDone_void(void* impl_msg, void* impl_obj_void);
    
    static void _call_allDone_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_allDone_void(void* impl_msg, void* impl_obj);
    /* DECLS: void printDone();
     */
    // Entry point registration at startup
    
    static int reg_printDone_void();
    // Entry point index lookup
    
    inline static int idx_printDone_void() {
      static int epidx = reg_printDone_void();
      return epidx;
    }

    
    inline static int idx_printDone(void (Main::*)() ) {
      return idx_printDone_void();
    }


    
    static int printDone() { return idx_printDone_void(); }
    
    static void _call_printDone_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_printDone_void(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
class CProxy_Main:public CProxy_Chare{
  public:
    typedef Main local_t;
    typedef CkIndex_Main index_t;
    typedef CProxy_Main proxy_t;
    typedef CProxy_Main element_t;

    CProxy_Main(void) {};
    CProxy_Main(CkChareID __cid) : CProxy_Chare(__cid){  }
    CProxy_Main(const Chare *c) : CProxy_Chare(c){  }

    int ckIsDelegated(void) const
    { return CProxy_Chare::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_Chare::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_Chare::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_Chare::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxy_Chare::ckCheck(); }
    const CkChareID &ckGetChareID(void) const
    { return CProxy_Chare::ckGetChareID(); }
    operator const CkChareID &(void) const
    { return ckGetChareID(); }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_Chare::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_Chare::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_Chare::pup(p);
    }

    void ckSetChareID(const CkChareID &c)
    {      CProxy_Chare::ckSetChareID(c); }
    Main *ckLocal(void) const
    { return (Main *)CkLocalChare(&ckGetChareID()); }
/* DECLS: Main(CkArgMsg* impl_msg);
 */
    static CkChareID ckNew(CkArgMsg* impl_msg, int onPE=CK_PE_ANY);
    static void ckNew(CkArgMsg* impl_msg, CkChareID* pcid, int onPE=CK_PE_ANY);

/* DECLS: void initDone();
 */
    
    void initDone(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void startIter();
 */
    
    void startIter(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void updateDone();
 */
    
    void updateDone(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void commDone();
 */
    
    void commDone(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void allDone();
 */
    
    void allDone(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void printDone();
 */
    
    void printDone(const CkEntryOptions *impl_e_opts=NULL);

};
#define Main_SDAG_CODE 
typedef CBaseT1<Chare, CProxy_Main>CBase_Main;

/* DECLS: array Block: ArrayElement{
Block();
void init();
void initDone();
void update();
void updateDone();
void packGhosts();
void packGhostsDone();
void receiveGhostsZC(int ref, int dir, int w, CkDeviceBuffer deviceBuffer_gh);
void receiveGhostsReg(int ref, int dir, int w, const DataType *gh);
void d_send_left_ghost_done();
void d_send_right_ghost_done();
void d_send_top_ghost_done();
void d_send_bottom_ghost_done();
void exchangeGhosts();
void print();
Block(CkMigrateMessage* impl_msg);
};
 */
 class Block;
 class CkIndex_Block;
 class CProxy_Block;
 class CProxyElement_Block;
 class CProxySection_Block;
/* --------------- index object ------------------ */
class CkIndex_Block:public CkIndex_ArrayElement{
  public:
    typedef Block local_t;
    typedef CkIndex_Block index_t;
    typedef CProxy_Block proxy_t;
    typedef CProxyElement_Block element_t;
    typedef CProxySection_Block section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: Block();
     */
    // Entry point registration at startup
    
    static int reg_Block_void();
    // Entry point index lookup
    
    inline static int idx_Block_void() {
      static int epidx = reg_Block_void();
      return epidx;
    }

    
    static int ckNew() { return idx_Block_void(); }
    
    static void _call_Block_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_Block_void(void* impl_msg, void* impl_obj);
    /* DECLS: void init();
     */
    // Entry point registration at startup
    
    static int reg_init_void();
    // Entry point index lookup
    
    inline static int idx_init_void() {
      static int epidx = reg_init_void();
      return epidx;
    }

    
    inline static int idx_init(void (Block::*)() ) {
      return idx_init_void();
    }


    
    static int init() { return idx_init_void(); }
    
    static void _call_init_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_init_void(void* impl_msg, void* impl_obj);
    /* DECLS: void initDone();
     */
    // Entry point registration at startup
    
    static int reg_initDone_void();
    // Entry point index lookup
    
    inline static int idx_initDone_void() {
      static int epidx = reg_initDone_void();
      return epidx;
    }

    
    inline static int idx_initDone(void (Block::*)() ) {
      return idx_initDone_void();
    }


    
    static int initDone() { return idx_initDone_void(); }
    
    static void _call_initDone_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initDone_void(void* impl_msg, void* impl_obj);
    /* DECLS: void update();
     */
    // Entry point registration at startup
    
    static int reg_update_void();
    // Entry point index lookup
    
    inline static int idx_update_void() {
      static int epidx = reg_update_void();
      return epidx;
    }

    
    inline static int idx_update(void (Block::*)() ) {
      return idx_update_void();
    }


    
    static int update() { return idx_update_void(); }
    
    static void _call_update_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_update_void(void* impl_msg, void* impl_obj);
    /* DECLS: void updateDone();
     */
    // Entry point registration at startup
    
    static int reg_updateDone_void();
    // Entry point index lookup
    
    inline static int idx_updateDone_void() {
      static int epidx = reg_updateDone_void();
      return epidx;
    }

    
    inline static int idx_updateDone(void (Block::*)() ) {
      return idx_updateDone_void();
    }


    
    static int updateDone() { return idx_updateDone_void(); }
    
    static void _call_updateDone_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_updateDone_void(void* impl_msg, void* impl_obj);
    /* DECLS: void packGhosts();
     */
    // Entry point registration at startup
    
    static int reg_packGhosts_void();
    // Entry point index lookup
    
    inline static int idx_packGhosts_void() {
      static int epidx = reg_packGhosts_void();
      return epidx;
    }

    
    inline static int idx_packGhosts(void (Block::*)() ) {
      return idx_packGhosts_void();
    }


    
    static int packGhosts() { return idx_packGhosts_void(); }
    
    static void _call_packGhosts_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_packGhosts_void(void* impl_msg, void* impl_obj);
    /* DECLS: void packGhostsDone();
     */
    // Entry point registration at startup
    
    static int reg_packGhostsDone_void();
    // Entry point index lookup
    
    inline static int idx_packGhostsDone_void() {
      static int epidx = reg_packGhostsDone_void();
      return epidx;
    }

    
    inline static int idx_packGhostsDone(void (Block::*)() ) {
      return idx_packGhostsDone_void();
    }


    
    static int packGhostsDone() { return idx_packGhostsDone_void(); }
    
    static void _call_packGhostsDone_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_packGhostsDone_void(void* impl_msg, void* impl_obj);
    /* DECLS: void receiveGhostsZC(int ref, int dir, int w, CkDeviceBuffer deviceBuffer_gh);
     */
    // Entry point registration at startup
    
    static int reg_receiveGhostsZC_marshall8();
    // Entry point index lookup
    
    inline static int idx_receiveGhostsZC_marshall8() {
      static int epidx = reg_receiveGhostsZC_marshall8();
      return epidx;
    }

    
    inline static int idx_receiveGhostsZC(void (Block::*)(int ref, int dir, int w, CkDeviceBuffer deviceBuffer_gh) ) {
      return idx_receiveGhostsZC_marshall8();
    }


    
    static int receiveGhostsZC(int ref, int dir, int w, CkDeviceBuffer deviceBuffer_gh) { return idx_receiveGhostsZC_marshall8(); }
    
    static void _call_receiveGhostsZC_marshall8(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_receiveGhostsZC_marshall8(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_receiveGhostsZC_marshall8(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_receiveGhostsZC_marshall8(PUP::er &p,void *msg);
    /* DECLS: void receiveGhostsReg(int ref, int dir, int w, const DataType *gh);
     */
    // Entry point registration at startup
    
    static int reg_receiveGhostsReg_marshall9();
    // Entry point index lookup
    
    inline static int idx_receiveGhostsReg_marshall9() {
      static int epidx = reg_receiveGhostsReg_marshall9();
      return epidx;
    }

    
    inline static int idx_receiveGhostsReg(void (Block::*)(int ref, int dir, int w, const DataType *gh) ) {
      return idx_receiveGhostsReg_marshall9();
    }


    
    static int receiveGhostsReg(int ref, int dir, int w, const DataType *gh) { return idx_receiveGhostsReg_marshall9(); }
    
    static void _call_receiveGhostsReg_marshall9(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_receiveGhostsReg_marshall9(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_receiveGhostsReg_marshall9(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_receiveGhostsReg_marshall9(PUP::er &p,void *msg);
    /* DECLS: void d_send_left_ghost_done();
     */
    // Entry point registration at startup
    
    static int reg_d_send_left_ghost_done_void();
    // Entry point index lookup
    
    inline static int idx_d_send_left_ghost_done_void() {
      static int epidx = reg_d_send_left_ghost_done_void();
      return epidx;
    }

    
    inline static int idx_d_send_left_ghost_done(void (Block::*)() ) {
      return idx_d_send_left_ghost_done_void();
    }


    
    static int d_send_left_ghost_done() { return idx_d_send_left_ghost_done_void(); }
    
    static void _call_d_send_left_ghost_done_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_d_send_left_ghost_done_void(void* impl_msg, void* impl_obj);
    /* DECLS: void d_send_right_ghost_done();
     */
    // Entry point registration at startup
    
    static int reg_d_send_right_ghost_done_void();
    // Entry point index lookup
    
    inline static int idx_d_send_right_ghost_done_void() {
      static int epidx = reg_d_send_right_ghost_done_void();
      return epidx;
    }

    
    inline static int idx_d_send_right_ghost_done(void (Block::*)() ) {
      return idx_d_send_right_ghost_done_void();
    }


    
    static int d_send_right_ghost_done() { return idx_d_send_right_ghost_done_void(); }
    
    static void _call_d_send_right_ghost_done_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_d_send_right_ghost_done_void(void* impl_msg, void* impl_obj);
    /* DECLS: void d_send_top_ghost_done();
     */
    // Entry point registration at startup
    
    static int reg_d_send_top_ghost_done_void();
    // Entry point index lookup
    
    inline static int idx_d_send_top_ghost_done_void() {
      static int epidx = reg_d_send_top_ghost_done_void();
      return epidx;
    }

    
    inline static int idx_d_send_top_ghost_done(void (Block::*)() ) {
      return idx_d_send_top_ghost_done_void();
    }


    
    static int d_send_top_ghost_done() { return idx_d_send_top_ghost_done_void(); }
    
    static void _call_d_send_top_ghost_done_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_d_send_top_ghost_done_void(void* impl_msg, void* impl_obj);
    /* DECLS: void d_send_bottom_ghost_done();
     */
    // Entry point registration at startup
    
    static int reg_d_send_bottom_ghost_done_void();
    // Entry point index lookup
    
    inline static int idx_d_send_bottom_ghost_done_void() {
      static int epidx = reg_d_send_bottom_ghost_done_void();
      return epidx;
    }

    
    inline static int idx_d_send_bottom_ghost_done(void (Block::*)() ) {
      return idx_d_send_bottom_ghost_done_void();
    }


    
    static int d_send_bottom_ghost_done() { return idx_d_send_bottom_ghost_done_void(); }
    
    static void _call_d_send_bottom_ghost_done_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_d_send_bottom_ghost_done_void(void* impl_msg, void* impl_obj);
    /* DECLS: void exchangeGhosts();
     */
    // Entry point registration at startup
    
    static int reg_exchangeGhosts_void();
    // Entry point index lookup
    
    inline static int idx_exchangeGhosts_void() {
      static int epidx = reg_exchangeGhosts_void();
      return epidx;
    }

    
    inline static int idx_exchangeGhosts(void (Block::*)() ) {
      return idx_exchangeGhosts_void();
    }


    
    static int exchangeGhosts() { return idx_exchangeGhosts_void(); }
    
    static void _call_exchangeGhosts_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_exchangeGhosts_void(void* impl_msg, void* impl_obj);
    /* DECLS: void print();
     */
    // Entry point registration at startup
    
    static int reg_print_void();
    // Entry point index lookup
    
    inline static int idx_print_void() {
      static int epidx = reg_print_void();
      return epidx;
    }

    
    inline static int idx_print(void (Block::*)() ) {
      return idx_print_void();
    }


    
    static int print() { return idx_print_void(); }
    
    static void _call_print_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_print_void(void* impl_msg, void* impl_obj);
    /* DECLS: Block(CkMigrateMessage* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_Block_CkMigrateMessage();
    // Entry point index lookup
    
    inline static int idx_Block_CkMigrateMessage() {
      static int epidx = reg_Block_CkMigrateMessage();
      return epidx;
    }

    
    static int ckNew(CkMigrateMessage* impl_msg) { return idx_Block_CkMigrateMessage(); }
    
    static void _call_Block_CkMigrateMessage(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_Block_CkMigrateMessage(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
 class CProxyElement_Block : public CProxyElement_ArrayElement{
  public:
    typedef Block local_t;
    typedef CkIndex_Block index_t;
    typedef CProxy_Block proxy_t;
    typedef CProxyElement_Block element_t;
    typedef CProxySection_Block section_t;

    using array_index_t = CkArrayIndex2D;

    /* TRAM aggregators */

    CProxyElement_Block(void) {
    }
    CProxyElement_Block(const ArrayElement *e) : CProxyElement_ArrayElement(e){
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxyElement_ArrayElement::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxyElement_ArrayElement::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxyElement_ArrayElement::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxyElement_ArrayElement::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxyElement_ArrayElement::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxyElement_ArrayElement::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxyElement_ArrayElement::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxyElement_ArrayElement::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxyElement_ArrayElement::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxyElement_ArrayElement::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxyElement_ArrayElement::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxyElement_ArrayElement::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxyElement_ArrayElement::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxyElement_ArrayElement::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxyElement_ArrayElement::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxyElement_ArrayElement::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxyElement_ArrayElement::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_ArrayElement::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_ArrayElement::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxyElement_ArrayElement::ckSetReductionClient(cb); }

    inline void ckInsert(CkArrayMessage *m,int ctor,int onPe)
    { CProxyElement_ArrayElement::ckInsert(m,ctor,onPe); }
    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0) const
    { CProxyElement_ArrayElement::ckSend(m,ep,opts); }
    inline void *ckSendSync(CkArrayMessage *m, int ep) const
    { return CProxyElement_ArrayElement::ckSendSync(m,ep); }
    inline const CkArrayIndex &ckGetIndex() const
    { return CProxyElement_ArrayElement::ckGetIndex(); }

    Block *ckLocal(void) const
    { return (Block *)CProxyElement_ArrayElement::ckLocal(); }

    CProxyElement_Block(const CkArrayID &aid,const CkArrayIndex2D &idx,CK_DELCTOR_PARAM)
        :CProxyElement_ArrayElement(aid,idx,CK_DELCTOR_ARGS)
    {
}
    CProxyElement_Block(const CkArrayID &aid,const CkArrayIndex2D &idx)
        :CProxyElement_ArrayElement(aid,idx)
    {
}

    CProxyElement_Block(const CkArrayID &aid,const CkArrayIndex &idx,CK_DELCTOR_PARAM)
        :CProxyElement_ArrayElement(aid,idx,CK_DELCTOR_ARGS)
    {
}
    CProxyElement_Block(const CkArrayID &aid,const CkArrayIndex &idx)
        :CProxyElement_ArrayElement(aid,idx)
    {
}
/* DECLS: Block();
 */
    
    void insert(int onPE=-1, const CkEntryOptions *impl_e_opts=NULL);
/* DECLS: void init();
 */
    
    void init(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void initDone();
 */
    
    void initDone(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void update();
 */
    
    void update(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void updateDone();
 */
    
    void updateDone(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void packGhosts();
 */
    
    void packGhosts(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void packGhostsDone();
 */
    
    void packGhostsDone(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void receiveGhostsZC(int ref, int dir, int w, CkDeviceBuffer deviceBuffer_gh);
 */
    
    void receiveGhostsZC(int ref, int dir, int w, CkDeviceBuffer deviceBuffer_gh, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void receiveGhostsReg(int ref, int dir, int w, const DataType *gh);
 */
    
    void receiveGhostsReg(int ref, int dir, int w, const DataType *gh, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void d_send_left_ghost_done();
 */
    
    void d_send_left_ghost_done(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void d_send_right_ghost_done();
 */
    
    void d_send_right_ghost_done(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void d_send_top_ghost_done();
 */
    
    void d_send_top_ghost_done(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void d_send_bottom_ghost_done();
 */
    
    void d_send_bottom_ghost_done(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void exchangeGhosts();
 */
    
    void exchangeGhosts(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void print();
 */
    
    void print(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: Block(CkMigrateMessage* impl_msg);
 */

};
/* ---------------- collective proxy -------------- */
 class CProxy_Block : public CProxy_ArrayElement{
  public:
    typedef Block local_t;
    typedef CkIndex_Block index_t;
    typedef CProxy_Block proxy_t;
    typedef CProxyElement_Block element_t;
    typedef CProxySection_Block section_t;

    using array_index_t = CkArrayIndex2D;
    CProxy_Block(void) {
    }
    CProxy_Block(const ArrayElement *e) : CProxy_ArrayElement(e){
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_ArrayElement::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_ArrayElement::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_ArrayElement::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxy_ArrayElement::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_ArrayElement::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_ArrayElement::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_ArrayElement::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxy_ArrayElement::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxy_ArrayElement::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxy_ArrayElement::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxy_ArrayElement::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxy_ArrayElement::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxy_ArrayElement::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxy_ArrayElement::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxy_ArrayElement::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxy_ArrayElement::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxy_ArrayElement::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_ArrayElement::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_ArrayElement::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxy_ArrayElement::ckSetReductionClient(cb); }

    // Generalized array indexing:
    CProxyElement_Block operator [] (const CkArrayIndex2D &idx) const
    { return CProxyElement_Block(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_Block operator() (const CkArrayIndex2D &idx) const
    { return CProxyElement_Block(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_Block operator () (int i0,int i1) const 
        {return CProxyElement_Block(ckGetArrayID(), CkArrayIndex2D(i0,i1), CK_DELCTOR_CALL);}
    CProxyElement_Block operator () (CkIndex2D idx) const 
        {return CProxyElement_Block(ckGetArrayID(), CkArrayIndex2D(idx), CK_DELCTOR_CALL);}
    CProxy_Block(const CkArrayID &aid,CK_DELCTOR_PARAM) 
        :CProxy_ArrayElement(aid,CK_DELCTOR_ARGS) {}
    CProxy_Block(const CkArrayID &aid) 
        :CProxy_ArrayElement(aid) {}
/* DECLS: Block();
 */
    
    static CkArrayID ckNew(const CkArrayOptions &opts = CkArrayOptions(), const CkEntryOptions *impl_e_opts=NULL);
    static void      ckNew(const CkArrayOptions &opts, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts=NULL);
    static CkArrayID ckNew(const int s1, const int s2, const CkEntryOptions *impl_e_opts=NULL);
    static void ckNew(const int s1, const int s2, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void init();
 */
    
    void init(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void initDone();
 */
    
    void initDone(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void update();
 */
    
    void update(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void updateDone();
 */
    
    void updateDone(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void packGhosts();
 */
    
    void packGhosts(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void packGhostsDone();
 */
    
    void packGhostsDone(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void receiveGhostsZC(int ref, int dir, int w, CkDeviceBuffer deviceBuffer_gh);
 */
    
    void receiveGhostsZC(int ref, int dir, int w, CkDeviceBuffer deviceBuffer_gh, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void receiveGhostsReg(int ref, int dir, int w, const DataType *gh);
 */
    
    void receiveGhostsReg(int ref, int dir, int w, const DataType *gh, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void d_send_left_ghost_done();
 */
    
    void d_send_left_ghost_done(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void d_send_right_ghost_done();
 */
    
    void d_send_right_ghost_done(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void d_send_top_ghost_done();
 */
    
    void d_send_top_ghost_done(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void d_send_bottom_ghost_done();
 */
    
    void d_send_bottom_ghost_done(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void exchangeGhosts();
 */
    
    void exchangeGhosts(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void print();
 */
    
    void print(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: Block(CkMigrateMessage* impl_msg);
 */

};
/* ---------------- section proxy -------------- */
 class CProxySection_Block : public CProxySection_ArrayElement{
  public:
    typedef Block local_t;
    typedef CkIndex_Block index_t;
    typedef CProxy_Block proxy_t;
    typedef CProxyElement_Block element_t;
    typedef CProxySection_Block section_t;

    using array_index_t = CkArrayIndex2D;
    CProxySection_Block(void) {
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxySection_ArrayElement::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxySection_ArrayElement::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxySection_ArrayElement::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxySection_ArrayElement::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxySection_ArrayElement::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxySection_ArrayElement::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxySection_ArrayElement::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxySection_ArrayElement::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxySection_ArrayElement::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxySection_ArrayElement::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxySection_ArrayElement::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxySection_ArrayElement::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxySection_ArrayElement::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxySection_ArrayElement::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxySection_ArrayElement::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxySection_ArrayElement::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxySection_ArrayElement::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_ArrayElement::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_ArrayElement::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxySection_ArrayElement::ckSetReductionClient(cb); }

    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0)
    { CProxySection_ArrayElement::ckSend(m,ep,opts); }
    inline CkSectionInfo &ckGetSectionInfo()
    { return CProxySection_ArrayElement::ckGetSectionInfo(); }
    inline CkSectionID *ckGetSectionIDs()
    { return CProxySection_ArrayElement::ckGetSectionIDs(); }
    inline CkSectionID &ckGetSectionID()
    { return CProxySection_ArrayElement::ckGetSectionID(); }
    inline CkSectionID &ckGetSectionID(int i)
    { return CProxySection_ArrayElement::ckGetSectionID(i); }
    inline CkArrayID ckGetArrayIDn(int i) const
    { return CProxySection_ArrayElement::ckGetArrayIDn(i); } 
    inline CkArrayIndex *ckGetArrayElements() const
    { return CProxySection_ArrayElement::ckGetArrayElements(); }
    inline CkArrayIndex *ckGetArrayElements(int i) const
    { return CProxySection_ArrayElement::ckGetArrayElements(i); }
    inline int ckGetNumElements() const
    { return CProxySection_ArrayElement::ckGetNumElements(); } 
    inline int ckGetNumElements(int i) const
    { return CProxySection_ArrayElement::ckGetNumElements(i); }    // Generalized array indexing:
    CProxyElement_Block operator [] (const CkArrayIndex2D &idx) const
        {return CProxyElement_Block(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_Block operator() (const CkArrayIndex2D &idx) const
        {return CProxyElement_Block(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_Block operator () (int idx) const 
        {return CProxyElement_Block(ckGetArrayID(), *(CkArrayIndex2D*)&ckGetArrayElements()[idx], CK_DELCTOR_CALL);}
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex2D *elems, int nElems, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      return CkSectionID(aid, elems, nElems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex2D> &elems, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      return CkSectionID(aid, elems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, int l1, int u1, int s1, int l2, int u2, int s2, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      std::vector<CkArrayIndex2D> al;
      for (int i=l1; i<=u1; i+=s1) 
        for (int j=l2; j<=u2; j+=s2) 
          al.emplace_back(i, j);
      return CkSectionID(aid, al, factor);
    } 
    CProxySection_Block(const CkArrayID &aid, CkArrayIndex *elems, int nElems, CK_DELCTOR_PARAM) 
        :CProxySection_ArrayElement(aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_Block(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, CK_DELCTOR_PARAM) 
        :CProxySection_ArrayElement(aid,elems,CK_DELCTOR_ARGS) {}
    CProxySection_Block(const CkArrayID &aid, CkArrayIndex *elems, int nElems, int factor=USE_DEFAULT_BRANCH_FACTOR) 
        :CProxySection_ArrayElement(aid,elems,nElems, factor) {}
    CProxySection_Block(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, int factor=USE_DEFAULT_BRANCH_FACTOR) 
        :CProxySection_ArrayElement(aid,elems, factor) { ckAutoDelegate(); }
    CProxySection_Block(const CkSectionID &sid)  
        :CProxySection_ArrayElement(sid) { ckAutoDelegate(); }
    CProxySection_Block(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, CK_DELCTOR_PARAM) 
        :CProxySection_ArrayElement(n,aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_Block(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems, CK_DELCTOR_PARAM) 
        :CProxySection_ArrayElement(aid,elems,CK_DELCTOR_ARGS) {}
    CProxySection_Block(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems) 
        :CProxySection_ArrayElement(n,aid,elems,nElems) { ckAutoDelegate(); }
    CProxySection_Block(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems) 
        :CProxySection_ArrayElement(aid,elems) { ckAutoDelegate(); }
    CProxySection_Block(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, int factor) 
        :CProxySection_ArrayElement(n,aid,elems,nElems, factor) { ckAutoDelegate(); }
    CProxySection_Block(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems, int factor) 
        :CProxySection_ArrayElement(aid,elems, factor) { ckAutoDelegate(); }
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems) {
      return CkSectionID(aid, elems, nElems);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems) {
       return CkSectionID(aid, elems);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems, int factor) {
      return CkSectionID(aid, elems, nElems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, int factor) {
      return CkSectionID(aid, elems, factor);
    } 
    void ckAutoDelegate(int opts=1) {
      if(ckIsDelegated()) return;
      CProxySection_ArrayElement::ckAutoDelegate(opts);
    } 
    void setReductionClient(CkCallback *cb) {
      CProxySection_ArrayElement::setReductionClient(cb);
    } 
    void resetSection() {
      CProxySection_ArrayElement::resetSection();
    } 
    static void contribute(CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    static void contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    template <typename T>
    static void contribute(std::vector<T> &data, CkReduction::reducerType type, CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    static void contribute(CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
    static void contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
    template <typename T>
    static void contribute(std::vector<T> &data, CkReduction::reducerType type, CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
/* DECLS: Block();
 */
    

/* DECLS: void init();
 */
    
    void init(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void initDone();
 */
    
    void initDone(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void update();
 */
    
    void update(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void updateDone();
 */
    
    void updateDone(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void packGhosts();
 */
    
    void packGhosts(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void packGhostsDone();
 */
    
    void packGhostsDone(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void receiveGhostsZC(int ref, int dir, int w, CkDeviceBuffer deviceBuffer_gh);
 */
    
    void receiveGhostsZC(int ref, int dir, int w, CkDeviceBuffer deviceBuffer_gh, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void receiveGhostsReg(int ref, int dir, int w, const DataType *gh);
 */
    
    void receiveGhostsReg(int ref, int dir, int w, const DataType *gh, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void d_send_left_ghost_done();
 */
    
    void d_send_left_ghost_done(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void d_send_right_ghost_done();
 */
    
    void d_send_right_ghost_done(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void d_send_top_ghost_done();
 */
    
    void d_send_top_ghost_done(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void d_send_bottom_ghost_done();
 */
    
    void d_send_bottom_ghost_done(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void exchangeGhosts();
 */
    
    void exchangeGhosts(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void print();
 */
    
    void print(const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: Block(CkMigrateMessage* impl_msg);
 */

};
#define Block_SDAG_CODE                                                        \
public:                                                                        \
  void exchangeGhosts();                                                       \
  void _sdag_fnc_exchangeGhosts();                                             \
private:                                                                       \
  void exchangeGhosts_end();                                                   \
  void _slist_0();                                                             \
  void _slist_0_end();                                                         \
  void _serial_0();                                                            \
  SDAG::Continuation* _when_0();                                               \
  void _when_0_end();                                                          \
  void _slist_1();                                                             \
  void _slist_1_end();                                                         \
  void _serial_1();                                                            \
  void _for_0();                                                               \
  void _for_0_end();                                                           \
  void _slist_2();                                                             \
  void _slist_2_end();                                                         \
  void _if_0();                                                                \
  void _if_0_end();                                                            \
  void _else_0();                                                              \
  void _else_0_end();                                                          \
  void _slist_3();                                                             \
  void _slist_3_end();                                                         \
  SDAG::Continuation* _when_1();                                               \
  SDAG::Continuation* _when_1(int refnum_0);                                   \
  void _when_1_end(Closure_Block::receiveGhostsReg_9_closure* gen0);           \
  void _slist_4(Closure_Block::receiveGhostsReg_9_closure* gen0);              \
  void _slist_4_end(Closure_Block::receiveGhostsReg_9_closure* gen0);          \
  void _serial_2(Closure_Block::receiveGhostsReg_9_closure* gen0);             \
  void _slist_5();                                                             \
  void _slist_5_end();                                                         \
  SDAG::Continuation* _when_2();                                               \
  SDAG::Continuation* _when_2(int refnum_0);                                   \
  void _when_2_end(Closure_Block::receiveGhostsZC_8_closure* gen0);            \
  void _slist_6(Closure_Block::receiveGhostsZC_8_closure* gen0);               \
  void _slist_6_end(Closure_Block::receiveGhostsZC_8_closure* gen0);           \
  void _serial_3(Closure_Block::receiveGhostsZC_8_closure* gen0);              \
  void _for_1();                                                               \
  void _for_1_end();                                                           \
  void _slist_7();                                                             \
  void _slist_7_end();                                                         \
  void _if_1();                                                                \
  void _if_1_end();                                                            \
  void _slist_8();                                                             \
  void _slist_8_end();                                                         \
  void _if_2();                                                                \
  void _if_2_end();                                                            \
  void _slist_9();                                                             \
  void _slist_9_end();                                                         \
  SDAG::Continuation* _when_3();                                               \
  void _when_3_end();                                                          \
  void _if_3();                                                                \
  void _if_3_end();                                                            \
  void _slist_10();                                                            \
  void _slist_10_end();                                                        \
  SDAG::Continuation* _when_4();                                               \
  void _when_4_end();                                                          \
  void _if_4();                                                                \
  void _if_4_end();                                                            \
  void _slist_11();                                                            \
  void _slist_11_end();                                                        \
  SDAG::Continuation* _when_5();                                               \
  void _when_5_end();                                                          \
  void _if_5();                                                                \
  void _if_5_end();                                                            \
  void _slist_12();                                                            \
  void _slist_12_end();                                                        \
  SDAG::Continuation* _when_6();                                               \
  void _when_6_end();                                                          \
  void _serial_4();                                                            \
public:                                                                        \
  void packGhostsDone(Closure_Block::packGhostsDone_7_closure* genClosure);    \
  void packGhostsDone();                                                       \
  void receiveGhostsReg(Closure_Block::receiveGhostsReg_9_closure* genClosure);\
  void receiveGhostsReg(int ref, int dir, int w, DataType *buf);               \
  void receiveGhostsZC(Closure_Block::receiveGhostsZC_8_closure* genClosure);  \
  void receiveGhostsZC(int ref, int dir, int w, CkDeviceBuffer deviceBuffer_buf);\
  void d_send_left_ghost_done(Closure_Block::d_send_left_ghost_done_10_closure* genClosure);\
  void d_send_left_ghost_done();                                               \
  void d_send_right_ghost_done(Closure_Block::d_send_right_ghost_done_11_closure* genClosure);\
  void d_send_right_ghost_done();                                              \
  void d_send_top_ghost_done(Closure_Block::d_send_top_ghost_done_12_closure* genClosure);\
  void d_send_top_ghost_done();                                                \
  void d_send_bottom_ghost_done(Closure_Block::d_send_bottom_ghost_done_13_closure* genClosure);\
  void d_send_bottom_ghost_done();                                             \
public:                                                                        \
  SDAG::dep_ptr __dep;                                                         \
  void _sdag_init();                                                           \
  void __sdag_init();                                                          \
public:                                                                        \
  void _sdag_pup(PUP::er &p);                                                  \
  void __sdag_pup(PUP::er &p) { }                                              \
  static void __sdag_register();                                               \
  static int _sdag_idx_Block_serial_0();                                       \
  static int _sdag_reg_Block_serial_0();                                       \
  static int _sdag_idx_Block_serial_1();                                       \
  static int _sdag_reg_Block_serial_1();                                       \
  static int _sdag_idx_Block_serial_3();                                       \
  static int _sdag_reg_Block_serial_3();                                       \
  static int _sdag_idx_Block_serial_2();                                       \
  static int _sdag_reg_Block_serial_2();                                       \
  static int _sdag_idx_Block_serial_4();                                       \
  static int _sdag_reg_Block_serial_4();                                       \

typedef CBaseT1<ArrayElementT<CkIndex2D>, CProxy_Block>CBase_Block;

/* DECLS: nodegroup KokkosGroup: NodeGroup{
KokkosGroup();
};
 */
 class KokkosGroup;
 class CkIndex_KokkosGroup;
 class CProxy_KokkosGroup;
 class CProxyElement_KokkosGroup;
 class CProxySection_KokkosGroup;
/* --------------- index object ------------------ */
class CkIndex_KokkosGroup:public CkIndex_NodeGroup{
  public:
    typedef KokkosGroup local_t;
    typedef CkIndex_KokkosGroup index_t;
    typedef CProxy_KokkosGroup proxy_t;
    typedef CProxyElement_KokkosGroup element_t;
    typedef CProxySection_KokkosGroup section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: KokkosGroup();
     */
    // Entry point registration at startup
    
    static int reg_KokkosGroup_void();
    // Entry point index lookup
    
    inline static int idx_KokkosGroup_void() {
      static int epidx = reg_KokkosGroup_void();
      return epidx;
    }

    
    static int ckNew() { return idx_KokkosGroup_void(); }
    
    static void _call_KokkosGroup_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_KokkosGroup_void(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
class CProxyElement_KokkosGroup: public CProxyElement_NodeGroup{
  public:
    typedef KokkosGroup local_t;
    typedef CkIndex_KokkosGroup index_t;
    typedef CProxy_KokkosGroup proxy_t;
    typedef CProxyElement_KokkosGroup element_t;
    typedef CProxySection_KokkosGroup section_t;


    /* TRAM aggregators */

    CProxyElement_KokkosGroup(void) {
    }
    CProxyElement_KokkosGroup(const IrrGroup *g) : CProxyElement_NodeGroup(g){
    }
    CProxyElement_KokkosGroup(CkGroupID _gid,int _onPE,CK_DELCTOR_PARAM) : CProxyElement_NodeGroup(_gid,_onPE,CK_DELCTOR_ARGS){
    }
    CProxyElement_KokkosGroup(CkGroupID _gid,int _onPE) : CProxyElement_NodeGroup(_gid,_onPE){
    }

    int ckIsDelegated(void) const
    { return CProxyElement_NodeGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxyElement_NodeGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxyElement_NodeGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxyElement_NodeGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxyElement_NodeGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxyElement_NodeGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxyElement_NodeGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_NodeGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_NodeGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxyElement_NodeGroup::ckSetReductionClient(cb); }
int ckGetGroupPe(void) const
{return CProxyElement_NodeGroup::ckGetGroupPe();}

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxyElement_NodeGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxyElement_NodeGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxyElement_NodeGroup::pup(p);
    }
    void ckSetGroupID(CkGroupID g) {
      CProxyElement_NodeGroup::ckSetGroupID(g);
    }
    KokkosGroup* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static KokkosGroup* ckLocalBranch(CkGroupID gID) {
      return (KokkosGroup*)CkLocalNodeBranch(gID);
    }
/* DECLS: KokkosGroup();
 */
    

};
/* ---------------- collective proxy -------------- */
class CProxy_KokkosGroup: public CProxy_NodeGroup{
  public:
    typedef KokkosGroup local_t;
    typedef CkIndex_KokkosGroup index_t;
    typedef CProxy_KokkosGroup proxy_t;
    typedef CProxyElement_KokkosGroup element_t;
    typedef CProxySection_KokkosGroup section_t;

    CProxy_KokkosGroup(void) {
    }
    CProxy_KokkosGroup(const IrrGroup *g) : CProxy_NodeGroup(g){
    }
    CProxy_KokkosGroup(CkGroupID _gid,CK_DELCTOR_PARAM) : CProxy_NodeGroup(_gid,CK_DELCTOR_ARGS){  }
    CProxy_KokkosGroup(CkGroupID _gid) : CProxy_NodeGroup(_gid){  }
    CProxyElement_KokkosGroup operator[](int onPE) const
      {return CProxyElement_KokkosGroup(ckGetGroupID(),onPE,CK_DELCTOR_CALL);}

    int ckIsDelegated(void) const
    { return CProxy_NodeGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_NodeGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_NodeGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_NodeGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxy_NodeGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxy_NodeGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxy_NodeGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_NodeGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_NodeGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxy_NodeGroup::ckSetReductionClient(cb); }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_NodeGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_NodeGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_NodeGroup::pup(p);
    }
    void ckSetGroupID(CkGroupID g) {
      CProxy_NodeGroup::ckSetGroupID(g);
    }
    KokkosGroup* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static KokkosGroup* ckLocalBranch(CkGroupID gID) {
      return (KokkosGroup*)CkLocalNodeBranch(gID);
    }
/* DECLS: KokkosGroup();
 */
    
    static CkGroupID ckNew(const CkEntryOptions *impl_e_opts=NULL);

};
/* ---------------- section proxy -------------- */
class CProxySection_KokkosGroup: public CProxySection_NodeGroup{
  public:
    typedef KokkosGroup local_t;
    typedef CkIndex_KokkosGroup index_t;
    typedef CProxy_KokkosGroup proxy_t;
    typedef CProxyElement_KokkosGroup element_t;
    typedef CProxySection_KokkosGroup section_t;

    CProxySection_KokkosGroup(void) {
    }
    CProxySection_KokkosGroup(const IrrGroup *g) : CProxySection_NodeGroup(g){
    }
    CProxySection_KokkosGroup(const CkGroupID &_gid,const int *_pelist,int _npes, CK_DELCTOR_PARAM) : CProxySection_NodeGroup(_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }
    CProxySection_KokkosGroup(const CkGroupID &_gid,const int *_pelist,int _npes, int factor = USE_DEFAULT_BRANCH_FACTOR) : CProxySection_NodeGroup(_gid,_pelist,_npes,factor){  }
    CProxySection_KokkosGroup(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes, int factor = USE_DEFAULT_BRANCH_FACTOR) : CProxySection_NodeGroup(n,_gid,_pelist,_npes,factor){  }
    CProxySection_KokkosGroup(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes, CK_DELCTOR_PARAM) : CProxySection_NodeGroup(n,_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }

    int ckIsDelegated(void) const
    { return CProxySection_NodeGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxySection_NodeGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxySection_NodeGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxySection_NodeGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxySection_NodeGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxySection_NodeGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxySection_NodeGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_NodeGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_NodeGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxySection_NodeGroup::ckSetReductionClient(cb); }
inline int ckGetNumSections() const
{ return CProxySection_NodeGroup::ckGetNumSections(); }
inline CkSectionInfo &ckGetSectionInfo()
{ return CProxySection_NodeGroup::ckGetSectionInfo(); }
inline CkSectionID *ckGetSectionIDs()
{ return CProxySection_NodeGroup::ckGetSectionIDs(); }
inline CkSectionID &ckGetSectionID()
{ return CProxySection_NodeGroup::ckGetSectionID(); }
inline CkSectionID &ckGetSectionID(int i)
{ return CProxySection_NodeGroup::ckGetSectionID(i); }
inline CkGroupID ckGetGroupIDn(int i) const
{ return CProxySection_NodeGroup::ckGetGroupIDn(i); }
inline const int *ckGetElements() const
{ return CProxySection_NodeGroup::ckGetElements(); }
inline const int *ckGetElements(int i) const
{ return CProxySection_NodeGroup::ckGetElements(i); }
inline int ckGetNumElements() const
{ return CProxySection_NodeGroup::ckGetNumElements(); } 
inline int ckGetNumElements(int i) const
{ return CProxySection_NodeGroup::ckGetNumElements(i); }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxySection_NodeGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxySection_NodeGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxySection_NodeGroup::pup(p);
    }
    void ckSetGroupID(CkGroupID g) {
      CProxySection_NodeGroup::ckSetGroupID(g);
    }
    KokkosGroup* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static KokkosGroup* ckLocalBranch(CkGroupID gID) {
      return (KokkosGroup*)CkLocalNodeBranch(gID);
    }
/* DECLS: KokkosGroup();
 */
    

};
#define KokkosGroup_SDAG_CODE 
typedef CBaseT1<NodeGroup, CProxy_KokkosGroup>CBase_KokkosGroup;













/* ---------------- method closures -------------- */
class Closure_Main {
  public:


    struct initDone_2_closure;


    struct startIter_3_closure;


    struct updateDone_4_closure;


    struct commDone_5_closure;


    struct allDone_6_closure;


    struct printDone_7_closure;

};

/* ---------------- method closures -------------- */
class Closure_Block {
  public:


    struct init_2_closure;


    struct initDone_3_closure;


    struct update_4_closure;


    struct updateDone_5_closure;


    struct packGhosts_6_closure;


    struct packGhostsDone_7_closure;


    struct receiveGhostsZC_8_closure;


    struct receiveGhostsReg_9_closure;


    struct d_send_left_ghost_done_10_closure;


    struct d_send_right_ghost_done_11_closure;


    struct d_send_top_ghost_done_12_closure;


    struct d_send_bottom_ghost_done_13_closure;


    struct exchangeGhosts_14_closure;


    struct print_15_closure;


};

/* ---------------- method closures -------------- */
class Closure_KokkosGroup {
  public:

};

extern void _registerjacobi2d(void);
extern "C" void CkRegisterMainModule(void);
#endif
