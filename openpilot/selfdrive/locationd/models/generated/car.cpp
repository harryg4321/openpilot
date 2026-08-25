#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_1015606323638202136) {
   out_1015606323638202136[0] = delta_x[0] + nom_x[0];
   out_1015606323638202136[1] = delta_x[1] + nom_x[1];
   out_1015606323638202136[2] = delta_x[2] + nom_x[2];
   out_1015606323638202136[3] = delta_x[3] + nom_x[3];
   out_1015606323638202136[4] = delta_x[4] + nom_x[4];
   out_1015606323638202136[5] = delta_x[5] + nom_x[5];
   out_1015606323638202136[6] = delta_x[6] + nom_x[6];
   out_1015606323638202136[7] = delta_x[7] + nom_x[7];
   out_1015606323638202136[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5721650614576311427) {
   out_5721650614576311427[0] = -nom_x[0] + true_x[0];
   out_5721650614576311427[1] = -nom_x[1] + true_x[1];
   out_5721650614576311427[2] = -nom_x[2] + true_x[2];
   out_5721650614576311427[3] = -nom_x[3] + true_x[3];
   out_5721650614576311427[4] = -nom_x[4] + true_x[4];
   out_5721650614576311427[5] = -nom_x[5] + true_x[5];
   out_5721650614576311427[6] = -nom_x[6] + true_x[6];
   out_5721650614576311427[7] = -nom_x[7] + true_x[7];
   out_5721650614576311427[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3022525702426203176) {
   out_3022525702426203176[0] = 1.0;
   out_3022525702426203176[1] = 0.0;
   out_3022525702426203176[2] = 0.0;
   out_3022525702426203176[3] = 0.0;
   out_3022525702426203176[4] = 0.0;
   out_3022525702426203176[5] = 0.0;
   out_3022525702426203176[6] = 0.0;
   out_3022525702426203176[7] = 0.0;
   out_3022525702426203176[8] = 0.0;
   out_3022525702426203176[9] = 0.0;
   out_3022525702426203176[10] = 1.0;
   out_3022525702426203176[11] = 0.0;
   out_3022525702426203176[12] = 0.0;
   out_3022525702426203176[13] = 0.0;
   out_3022525702426203176[14] = 0.0;
   out_3022525702426203176[15] = 0.0;
   out_3022525702426203176[16] = 0.0;
   out_3022525702426203176[17] = 0.0;
   out_3022525702426203176[18] = 0.0;
   out_3022525702426203176[19] = 0.0;
   out_3022525702426203176[20] = 1.0;
   out_3022525702426203176[21] = 0.0;
   out_3022525702426203176[22] = 0.0;
   out_3022525702426203176[23] = 0.0;
   out_3022525702426203176[24] = 0.0;
   out_3022525702426203176[25] = 0.0;
   out_3022525702426203176[26] = 0.0;
   out_3022525702426203176[27] = 0.0;
   out_3022525702426203176[28] = 0.0;
   out_3022525702426203176[29] = 0.0;
   out_3022525702426203176[30] = 1.0;
   out_3022525702426203176[31] = 0.0;
   out_3022525702426203176[32] = 0.0;
   out_3022525702426203176[33] = 0.0;
   out_3022525702426203176[34] = 0.0;
   out_3022525702426203176[35] = 0.0;
   out_3022525702426203176[36] = 0.0;
   out_3022525702426203176[37] = 0.0;
   out_3022525702426203176[38] = 0.0;
   out_3022525702426203176[39] = 0.0;
   out_3022525702426203176[40] = 1.0;
   out_3022525702426203176[41] = 0.0;
   out_3022525702426203176[42] = 0.0;
   out_3022525702426203176[43] = 0.0;
   out_3022525702426203176[44] = 0.0;
   out_3022525702426203176[45] = 0.0;
   out_3022525702426203176[46] = 0.0;
   out_3022525702426203176[47] = 0.0;
   out_3022525702426203176[48] = 0.0;
   out_3022525702426203176[49] = 0.0;
   out_3022525702426203176[50] = 1.0;
   out_3022525702426203176[51] = 0.0;
   out_3022525702426203176[52] = 0.0;
   out_3022525702426203176[53] = 0.0;
   out_3022525702426203176[54] = 0.0;
   out_3022525702426203176[55] = 0.0;
   out_3022525702426203176[56] = 0.0;
   out_3022525702426203176[57] = 0.0;
   out_3022525702426203176[58] = 0.0;
   out_3022525702426203176[59] = 0.0;
   out_3022525702426203176[60] = 1.0;
   out_3022525702426203176[61] = 0.0;
   out_3022525702426203176[62] = 0.0;
   out_3022525702426203176[63] = 0.0;
   out_3022525702426203176[64] = 0.0;
   out_3022525702426203176[65] = 0.0;
   out_3022525702426203176[66] = 0.0;
   out_3022525702426203176[67] = 0.0;
   out_3022525702426203176[68] = 0.0;
   out_3022525702426203176[69] = 0.0;
   out_3022525702426203176[70] = 1.0;
   out_3022525702426203176[71] = 0.0;
   out_3022525702426203176[72] = 0.0;
   out_3022525702426203176[73] = 0.0;
   out_3022525702426203176[74] = 0.0;
   out_3022525702426203176[75] = 0.0;
   out_3022525702426203176[76] = 0.0;
   out_3022525702426203176[77] = 0.0;
   out_3022525702426203176[78] = 0.0;
   out_3022525702426203176[79] = 0.0;
   out_3022525702426203176[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_753104935307901453) {
   out_753104935307901453[0] = state[0];
   out_753104935307901453[1] = state[1];
   out_753104935307901453[2] = state[2];
   out_753104935307901453[3] = state[3];
   out_753104935307901453[4] = state[4];
   out_753104935307901453[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_753104935307901453[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_753104935307901453[7] = state[7];
   out_753104935307901453[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3017823020467450526) {
   out_3017823020467450526[0] = 1;
   out_3017823020467450526[1] = 0;
   out_3017823020467450526[2] = 0;
   out_3017823020467450526[3] = 0;
   out_3017823020467450526[4] = 0;
   out_3017823020467450526[5] = 0;
   out_3017823020467450526[6] = 0;
   out_3017823020467450526[7] = 0;
   out_3017823020467450526[8] = 0;
   out_3017823020467450526[9] = 0;
   out_3017823020467450526[10] = 1;
   out_3017823020467450526[11] = 0;
   out_3017823020467450526[12] = 0;
   out_3017823020467450526[13] = 0;
   out_3017823020467450526[14] = 0;
   out_3017823020467450526[15] = 0;
   out_3017823020467450526[16] = 0;
   out_3017823020467450526[17] = 0;
   out_3017823020467450526[18] = 0;
   out_3017823020467450526[19] = 0;
   out_3017823020467450526[20] = 1;
   out_3017823020467450526[21] = 0;
   out_3017823020467450526[22] = 0;
   out_3017823020467450526[23] = 0;
   out_3017823020467450526[24] = 0;
   out_3017823020467450526[25] = 0;
   out_3017823020467450526[26] = 0;
   out_3017823020467450526[27] = 0;
   out_3017823020467450526[28] = 0;
   out_3017823020467450526[29] = 0;
   out_3017823020467450526[30] = 1;
   out_3017823020467450526[31] = 0;
   out_3017823020467450526[32] = 0;
   out_3017823020467450526[33] = 0;
   out_3017823020467450526[34] = 0;
   out_3017823020467450526[35] = 0;
   out_3017823020467450526[36] = 0;
   out_3017823020467450526[37] = 0;
   out_3017823020467450526[38] = 0;
   out_3017823020467450526[39] = 0;
   out_3017823020467450526[40] = 1;
   out_3017823020467450526[41] = 0;
   out_3017823020467450526[42] = 0;
   out_3017823020467450526[43] = 0;
   out_3017823020467450526[44] = 0;
   out_3017823020467450526[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3017823020467450526[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3017823020467450526[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3017823020467450526[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3017823020467450526[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3017823020467450526[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3017823020467450526[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3017823020467450526[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3017823020467450526[53] = -9.8100000000000005*dt;
   out_3017823020467450526[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3017823020467450526[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3017823020467450526[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3017823020467450526[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3017823020467450526[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3017823020467450526[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3017823020467450526[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3017823020467450526[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3017823020467450526[62] = 0;
   out_3017823020467450526[63] = 0;
   out_3017823020467450526[64] = 0;
   out_3017823020467450526[65] = 0;
   out_3017823020467450526[66] = 0;
   out_3017823020467450526[67] = 0;
   out_3017823020467450526[68] = 0;
   out_3017823020467450526[69] = 0;
   out_3017823020467450526[70] = 1;
   out_3017823020467450526[71] = 0;
   out_3017823020467450526[72] = 0;
   out_3017823020467450526[73] = 0;
   out_3017823020467450526[74] = 0;
   out_3017823020467450526[75] = 0;
   out_3017823020467450526[76] = 0;
   out_3017823020467450526[77] = 0;
   out_3017823020467450526[78] = 0;
   out_3017823020467450526[79] = 0;
   out_3017823020467450526[80] = 1;
}
void h_25(double *state, double *unused, double *out_6850265126998408) {
   out_6850265126998408[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3527860144626499888) {
   out_3527860144626499888[0] = 0;
   out_3527860144626499888[1] = 0;
   out_3527860144626499888[2] = 0;
   out_3527860144626499888[3] = 0;
   out_3527860144626499888[4] = 0;
   out_3527860144626499888[5] = 0;
   out_3527860144626499888[6] = 1;
   out_3527860144626499888[7] = 0;
   out_3527860144626499888[8] = 0;
}
void h_24(double *state, double *unused, double *out_5306963460607314878) {
   out_5306963460607314878[0] = state[4];
   out_5306963460607314878[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3057402662583161164) {
   out_3057402662583161164[0] = 0;
   out_3057402662583161164[1] = 0;
   out_3057402662583161164[2] = 0;
   out_3057402662583161164[3] = 0;
   out_3057402662583161164[4] = 1;
   out_3057402662583161164[5] = 0;
   out_3057402662583161164[6] = 0;
   out_3057402662583161164[7] = 0;
   out_3057402662583161164[8] = 0;
   out_3057402662583161164[9] = 0;
   out_3057402662583161164[10] = 0;
   out_3057402662583161164[11] = 0;
   out_3057402662583161164[12] = 0;
   out_3057402662583161164[13] = 0;
   out_3057402662583161164[14] = 1;
   out_3057402662583161164[15] = 0;
   out_3057402662583161164[16] = 0;
   out_3057402662583161164[17] = 0;
}
void h_30(double *state, double *unused, double *out_4105153563406370272) {
   out_4105153563406370272[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3398521197483259818) {
   out_3398521197483259818[0] = 0;
   out_3398521197483259818[1] = 0;
   out_3398521197483259818[2] = 0;
   out_3398521197483259818[3] = 0;
   out_3398521197483259818[4] = 1;
   out_3398521197483259818[5] = 0;
   out_3398521197483259818[6] = 0;
   out_3398521197483259818[7] = 0;
   out_3398521197483259818[8] = 0;
}
void h_26(double *state, double *unused, double *out_9106826831067215917) {
   out_9106826831067215917[0] = state[7];
}
void H_26(double *state, double *unused, double *out_213643174247556336) {
   out_213643174247556336[0] = 0;
   out_213643174247556336[1] = 0;
   out_213643174247556336[2] = 0;
   out_213643174247556336[3] = 0;
   out_213643174247556336[4] = 0;
   out_213643174247556336[5] = 0;
   out_213643174247556336[6] = 0;
   out_213643174247556336[7] = 1;
   out_213643174247556336[8] = 0;
}
void h_27(double *state, double *unused, double *out_8988819437133839173) {
   out_8988819437133839173[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1223757885682834907) {
   out_1223757885682834907[0] = 0;
   out_1223757885682834907[1] = 0;
   out_1223757885682834907[2] = 0;
   out_1223757885682834907[3] = 1;
   out_1223757885682834907[4] = 0;
   out_1223757885682834907[5] = 0;
   out_1223757885682834907[6] = 0;
   out_1223757885682834907[7] = 0;
   out_1223757885682834907[8] = 0;
}
void h_29(double *state, double *unused, double *out_5795601398142051232) {
   out_5795601398142051232[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3908752541797652002) {
   out_3908752541797652002[0] = 0;
   out_3908752541797652002[1] = 1;
   out_3908752541797652002[2] = 0;
   out_3908752541797652002[3] = 0;
   out_3908752541797652002[4] = 0;
   out_3908752541797652002[5] = 0;
   out_3908752541797652002[6] = 0;
   out_3908752541797652002[7] = 0;
   out_3908752541797652002[8] = 0;
}
void h_28(double *state, double *unused, double *out_192509972867842033) {
   out_192509972867842033[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1474025430378610125) {
   out_1474025430378610125[0] = 1;
   out_1474025430378610125[1] = 0;
   out_1474025430378610125[2] = 0;
   out_1474025430378610125[3] = 0;
   out_1474025430378610125[4] = 0;
   out_1474025430378610125[5] = 0;
   out_1474025430378610125[6] = 0;
   out_1474025430378610125[7] = 0;
   out_1474025430378610125[8] = 0;
}
void h_31(double *state, double *unused, double *out_7888122915881047593) {
   out_7888122915881047593[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3558506106503460316) {
   out_3558506106503460316[0] = 0;
   out_3558506106503460316[1] = 0;
   out_3558506106503460316[2] = 0;
   out_3558506106503460316[3] = 0;
   out_3558506106503460316[4] = 0;
   out_3558506106503460316[5] = 0;
   out_3558506106503460316[6] = 0;
   out_3558506106503460316[7] = 0;
   out_3558506106503460316[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_1015606323638202136) {
  err_fun(nom_x, delta_x, out_1015606323638202136);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5721650614576311427) {
  inv_err_fun(nom_x, true_x, out_5721650614576311427);
}
void car_H_mod_fun(double *state, double *out_3022525702426203176) {
  H_mod_fun(state, out_3022525702426203176);
}
void car_f_fun(double *state, double dt, double *out_753104935307901453) {
  f_fun(state,  dt, out_753104935307901453);
}
void car_F_fun(double *state, double dt, double *out_3017823020467450526) {
  F_fun(state,  dt, out_3017823020467450526);
}
void car_h_25(double *state, double *unused, double *out_6850265126998408) {
  h_25(state, unused, out_6850265126998408);
}
void car_H_25(double *state, double *unused, double *out_3527860144626499888) {
  H_25(state, unused, out_3527860144626499888);
}
void car_h_24(double *state, double *unused, double *out_5306963460607314878) {
  h_24(state, unused, out_5306963460607314878);
}
void car_H_24(double *state, double *unused, double *out_3057402662583161164) {
  H_24(state, unused, out_3057402662583161164);
}
void car_h_30(double *state, double *unused, double *out_4105153563406370272) {
  h_30(state, unused, out_4105153563406370272);
}
void car_H_30(double *state, double *unused, double *out_3398521197483259818) {
  H_30(state, unused, out_3398521197483259818);
}
void car_h_26(double *state, double *unused, double *out_9106826831067215917) {
  h_26(state, unused, out_9106826831067215917);
}
void car_H_26(double *state, double *unused, double *out_213643174247556336) {
  H_26(state, unused, out_213643174247556336);
}
void car_h_27(double *state, double *unused, double *out_8988819437133839173) {
  h_27(state, unused, out_8988819437133839173);
}
void car_H_27(double *state, double *unused, double *out_1223757885682834907) {
  H_27(state, unused, out_1223757885682834907);
}
void car_h_29(double *state, double *unused, double *out_5795601398142051232) {
  h_29(state, unused, out_5795601398142051232);
}
void car_H_29(double *state, double *unused, double *out_3908752541797652002) {
  H_29(state, unused, out_3908752541797652002);
}
void car_h_28(double *state, double *unused, double *out_192509972867842033) {
  h_28(state, unused, out_192509972867842033);
}
void car_H_28(double *state, double *unused, double *out_1474025430378610125) {
  H_28(state, unused, out_1474025430378610125);
}
void car_h_31(double *state, double *unused, double *out_7888122915881047593) {
  h_31(state, unused, out_7888122915881047593);
}
void car_H_31(double *state, double *unused, double *out_3558506106503460316) {
  H_31(state, unused, out_3558506106503460316);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
