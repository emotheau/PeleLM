#include <AMReX_FArrayBox.H>
#include <AMReX_Geometry.H>
#include <AMReX_PhysBCFunct.H>
#include <IndexDefines.H>
#include <pelelm_prob.H>


using namespace amrex;

struct PeleLMNodalFillExtDir
{
  AMREX_GPU_DEVICE
  void operator()(
    const amrex::IntVect& iv,
    amrex::Array4<amrex::Real> const& dest,
    const int dcomp,
    const int numcomp,
    amrex::GeometryData const& geom,
    const amrex::Real time,
    const amrex::BCRec* bcr,
    const int bcomp,
    const int orig_comp) const
  {
           // do something for external Dirichlet (BCType::ext_dir)
  }
};

struct PeleLMEdgeFillExtDir
{
  AMREX_GPU_DEVICE
  void operator()(
    const amrex::IntVect& iv,
    amrex::Array4<amrex::Real> const& dest,
    const int dcomp,
    const int numcomp,
    amrex::GeometryData const& geom,
    const amrex::Real time,
    const amrex::BCRec* bcr,
    const int bcomp,
    const int orig_comp) const
  {
           // do something for external Dirichlet (BCType::ext_dir)
  }
};

struct PeleLMCCFillExtDir
{
  AMREX_GPU_DEVICE
  void operator()(
    const amrex::IntVect& iv,
    amrex::Array4<amrex::Real> const& dest,
    const int dcomp,
    const int numcomp,
    amrex::GeometryData const& geom,
    const amrex::Real time,
    const amrex::BCRec* bcr,
    const int bcomp,
    const int orig_comp) const
  {
            // do something for external Dirichlet (BCType::ext_dir)

    const int* domlo = geom.Domain().loVect();
    const int* domhi = geom.Domain().hiVect();
    const amrex::Real* prob_lo = geom.ProbLo();
    const amrex::Real* prob_hi = geom.ProbHi();
    const amrex::Real* dx = geom.CellSize();
    const amrex::Real x[AMREX_SPACEDIM] = {AMREX_D_DECL(
    prob_lo[0] + (iv[0] + 0.5) * dx[0], prob_lo[1] + (iv[1] + 0.5) * dx[1],
    prob_lo[2] + (iv[2] + 0.5) * dx[2])};

    const int* bc = bcr->data();

    amrex::Real s_ext[DEF_NUM_STATE] = {0.0};

    // xlo and xhi
    int idir = 0;
    if ((bc[idir] == amrex::BCType::ext_dir) and (iv[idir] < domlo[idir])) {

         bcnormal(x, s_ext, idir, 1, time, geom);

         if (orig_comp == Xvel){
           for (int n = 0; n < AMREX_SPACEDIM; n++) {
             dest(iv, dcomp + n) = s_ext[Xvel+n];
           }
         }
         else if (orig_comp == Density){
             dest(iv, dcomp) = s_ext[Density];
         }
         else if (orig_comp == DEF_first_spec){
           for (int n = 0; n < NUM_SPECIES; n++) {
             dest(iv, dcomp + n) = s_ext[DEF_first_spec+n];
           }
         }
         else if (orig_comp == DEF_RhoH){
            dest(iv, dcomp) = s_ext[DEF_RhoH];
         }
         else if (orig_comp == DEF_Temp){
            dest(iv, dcomp) = s_ext[DEF_Temp];
         }
         else if (orig_comp == DEF_RhoRT){
            dest(iv, dcomp) = 0.0;
         }
         else if (orig_comp == DEF_nE){
            dest(iv, dcomp) = s_ext[DEF_nE];
         }
         else if (orig_comp == DEF_PhiV){
            dest(iv, dcomp) = s_ext[DEF_PhiV];
         }

    } else if (
       (bc[idir + AMREX_SPACEDIM] == amrex::BCType::ext_dir) and
       (iv[idir] > domhi[idir])) {

         bcnormal(x, s_ext, idir, -1, time, geom);

         if (orig_comp == Xvel){
           for (int n = 0; n < AMREX_SPACEDIM; n++) {
             dest(iv, dcomp + n) = s_ext[Xvel+n];
           }
         }
         else if (orig_comp == Density){
             dest(iv, dcomp) = s_ext[Density];
         }
         else if (orig_comp == DEF_first_spec){
           for (int n = 0; n < NUM_SPECIES; n++) {
             dest(iv, dcomp + n) = s_ext[DEF_first_spec+n];
           }
         }
         else if (orig_comp == DEF_RhoH){
            dest(iv, dcomp) = s_ext[DEF_RhoH];
         }
         else if (orig_comp == DEF_Temp){
            dest(iv, dcomp) = s_ext[DEF_Temp];
         }
         else if (orig_comp == DEF_RhoRT){
            dest(iv, dcomp) = 0.0;
         }
         else if (orig_comp == DEF_nE){
            dest(iv, dcomp) = s_ext[DEF_nE];
         }
         else if (orig_comp == DEF_PhiV){
            dest(iv, dcomp) = s_ext[DEF_PhiV];
         }
    }


    // ylo and yhi
    idir = 1;
    if ((bc[idir] == amrex::BCType::ext_dir) and (iv[idir] < domlo[idir])) {

         bcnormal(x, s_ext, idir, +1, time, geom);

         if (orig_comp == Xvel){
           for (int n = 0; n < AMREX_SPACEDIM; n++) {
             dest(iv, dcomp + n) = s_ext[Xvel+n];
           }
         }
         else if (orig_comp == Density){
             dest(iv, dcomp) = s_ext[Density];
         }
         else if (orig_comp == DEF_first_spec){
           for (int n = 0; n < NUM_SPECIES; n++) {
             dest(iv, dcomp + n) = s_ext[DEF_first_spec+n];
           }
         }
         else if (orig_comp == DEF_RhoH){
            dest(iv, dcomp) = s_ext[DEF_RhoH];
         }
         else if (orig_comp == DEF_Temp){
            dest(iv, dcomp) = s_ext[DEF_Temp];
         }
         else if (orig_comp == DEF_RhoRT){
            dest(iv, dcomp) = 0.0;
         }
         else if (orig_comp == DEF_nE){
            dest(iv, dcomp) = s_ext[DEF_nE];
         }
         else if (orig_comp == DEF_PhiV){
            dest(iv, dcomp) = s_ext[DEF_PhiV];
         }

    } else if (
       (bc[idir + AMREX_SPACEDIM] == amrex::BCType::ext_dir) and
       (iv[idir] > domhi[idir])) {

         bcnormal(x, s_ext, idir, -1, time, geom);

         if (orig_comp == Xvel){
           for (int n = 0; n < AMREX_SPACEDIM; n++) {
             dest(iv, dcomp + n) = s_ext[Xvel+n];
           }
         }
         else if (orig_comp == Density){
             dest(iv, dcomp) = s_ext[Density];
         }
         else if (orig_comp == DEF_first_spec){
           for (int n = 0; n < NUM_SPECIES; n++) {
             dest(iv, dcomp + n) = s_ext[DEF_first_spec+n];
           }
         }
         else if (orig_comp == DEF_RhoH){
            dest(iv, dcomp) = s_ext[DEF_RhoH];
         }
         else if (orig_comp == DEF_Temp){
            dest(iv, dcomp) = s_ext[DEF_Temp];
         }
         else if (orig_comp == DEF_RhoRT){
            dest(iv, dcomp) = 0.0;
         }
         else if (orig_comp == DEF_nE){
            dest(iv, dcomp) = s_ext[DEF_nE];
         }
         else if (orig_comp == DEF_PhiV){
            dest(iv, dcomp) = s_ext[DEF_PhiV];
         }

    }

#if AMREX_SPACEDIM == 3
    // zlo and zhi
    idir = 2;
    if ((bc[idir] == amrex::BCType::ext_dir) and (iv[idir] < domlo[idir])) {

         bcnormal(x, s_ext, idir, +1, time, geom);

         if (orig_comp == Xvel){
           for (int n = 0; n < AMREX_SPACEDIM; n++) {
             dest(iv, dcomp + n) = s_ext[Xvel+n];
           }
         }
         else if (orig_comp == Density){
             dest(iv, dcomp) = s_ext[Density];
         }
         else if (orig_comp == DEF_first_spec){
           for (int n = 0; n < NUM_SPECIES; n++) {
             dest(iv, dcomp + n) = s_ext[DEF_first_spec+n];
           }
         }
         else if (orig_comp == DEF_RhoH){
            dest(iv, dcomp) = s_ext[DEF_RhoH];
         }
         else if (orig_comp == DEF_Temp){
            dest(iv, dcomp) = s_ext[DEF_Temp];
         }
         else if (orig_comp == DEF_RhoRT){
            dest(iv, dcomp) = 0.0;
         }
         else if (orig_comp == DEF_nE){
            dest(iv, dcomp) = s_ext[DEF_nE];
         }
         else if (orig_comp == DEF_PhiV){
            dest(iv, dcomp) = s_ext[DEF_PhiV];
         }

    } else if (
       (bc[idir + AMREX_SPACEDIM] == amrex::BCType::ext_dir) and
       (iv[idir] > domhi[idir])) {

         bcnormal(x, s_ext, idir, -1, time, geom);

         if (orig_comp == Xvel){
           for (int n = 0; n < AMREX_SPACEDIM; n++) {
             dest(iv, dcomp + n) = s_ext[Xvel+n];
           }
         }
         else if (orig_comp == Density){
             dest(iv, dcomp) = s_ext[Density];
         }
         else if (orig_comp == DEF_first_spec){
           for (int n = 0; n < NUM_SPECIES; n++) {
             dest(iv, dcomp + n) = s_ext[DEF_first_spec+n];
           }
         }
         else if (orig_comp == DEF_RhoH){
            dest(iv, dcomp) = s_ext[DEF_RhoH];
         }
         else if (orig_comp == DEF_Temp){
            dest(iv, dcomp) = s_ext[DEF_Temp];
         }
         else if (orig_comp == DEF_RhoRT){
            dest(iv, dcomp) = 0.0;
         }
         else if (orig_comp == DEF_nE){
            dest(iv, dcomp) = s_ext[DEF_nE];
         }
         else if (orig_comp == DEF_PhiV){
            dest(iv, dcomp) = s_ext[DEF_PhiV];
         }

    }
#endif
 }
};

// bx                  : Cells outside physical domain and inside bx are filled.
// data, dcomp, numcomp: Fill numcomp components of data starting from dcomp.
// bcr, bcomp          : bcr[bcomp] specifies BC for component dcomp and so on.
// scomp               : component index for dcomp as in the desciptor set up in CNS::variableSetUp.

void pelelm_cc_ext_fill (Box const& bx, FArrayBox& data,
                 const int dcomp, const int numcomp,
                 Geometry const& geom, const Real time,
                 const Vector<BCRec>& bcr, const int bcomp,
                 const int scomp)
{

        GpuBndryFuncFab<PeleLMCCFillExtDir> gpu_bndry_func(PeleLMCCFillExtDir{});
        gpu_bndry_func(bx,data,dcomp,numcomp,geom,time,bcr,bcomp,scomp);

}


void pelelm_fillEdges (Box const& bx, FArrayBox& data,
                 const int dcomp, const int numcomp,
                 Geometry const& geom, const Real time,
                 const Vector<BCRec>& bcr, const int bcomp,
                 const int scomp)
{

// The GpuBndryFuncFab routine is not yet supporting Edge Face data
// but it is called here so that it will automatically work when amrex support will be ok

        GpuBndryFuncFab<PeleLMEdgeFillExtDir> gpu_bndry_func(PeleLMEdgeFillExtDir{});
        gpu_bndry_func(bx,data,dcomp,numcomp,geom,time,bcr,bcomp,scomp);

}


void pelelm_press_fill (Box const& bx, FArrayBox& data,
                 const int dcomp, const int numcomp,
                 Geometry const& geom, const Real time,
                 const Vector<BCRec>& bcr, const int bcomp,
                 const int scomp)
{

        GpuBndryFuncFab<PeleLMNodalFillExtDir> gpu_bndry_func(PeleLMNodalFillExtDir{});
        gpu_bndry_func(bx,data,dcomp,numcomp,geom,time,bcr,bcomp,scomp);

}
