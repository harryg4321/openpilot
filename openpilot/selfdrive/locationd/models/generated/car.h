#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_1015606323638202136);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5721650614576311427);
void car_H_mod_fun(double *state, double *out_3022525702426203176);
void car_f_fun(double *state, double dt, double *out_753104935307901453);
void car_F_fun(double *state, double dt, double *out_3017823020467450526);
void car_h_25(double *state, double *unused, double *out_6850265126998408);
void car_H_25(double *state, double *unused, double *out_3527860144626499888);
void car_h_24(double *state, double *unused, double *out_5306963460607314878);
void car_H_24(double *state, double *unused, double *out_3057402662583161164);
void car_h_30(double *state, double *unused, double *out_4105153563406370272);
void car_H_30(double *state, double *unused, double *out_3398521197483259818);
void car_h_26(double *state, double *unused, double *out_9106826831067215917);
void car_H_26(double *state, double *unused, double *out_213643174247556336);
void car_h_27(double *state, double *unused, double *out_8988819437133839173);
void car_H_27(double *state, double *unused, double *out_1223757885682834907);
void car_h_29(double *state, double *unused, double *out_5795601398142051232);
void car_H_29(double *state, double *unused, double *out_3908752541797652002);
void car_h_28(double *state, double *unused, double *out_192509972867842033);
void car_H_28(double *state, double *unused, double *out_1474025430378610125);
void car_h_31(double *state, double *unused, double *out_7888122915881047593);
void car_H_31(double *state, double *unused, double *out_3558506106503460316);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}