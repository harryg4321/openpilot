#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_8103323071732125497);
void live_err_fun(double *nom_x, double *delta_x, double *out_8250015531126003738);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_633884205805834957);
void live_H_mod_fun(double *state, double *out_2624924813718959693);
void live_f_fun(double *state, double dt, double *out_9059925282364469503);
void live_F_fun(double *state, double dt, double *out_2782981214434877028);
void live_h_4(double *state, double *unused, double *out_2472850896661522245);
void live_H_4(double *state, double *unused, double *out_2909281708661760381);
void live_h_9(double *state, double *unused, double *out_6989834929130913681);
void live_H_9(double *state, double *unused, double *out_3150471355291351026);
void live_h_10(double *state, double *unused, double *out_3952974057894277182);
void live_H_10(double *state, double *unused, double *out_7389294257848174465);
void live_h_12(double *state, double *unused, double *out_8084619591144893636);
void live_H_12(double *state, double *unused, double *out_7928738116693722176);
void live_h_35(double *state, double *unused, double *out_6998445815847688543);
void live_H_35(double *state, double *unused, double *out_6275943766034367757);
void live_h_32(double *state, double *unused, double *out_7343010107840295451);
void live_H_32(double *state, double *unused, double *out_8216782103367376558);
void live_h_13(double *state, double *unused, double *out_6637028168648099608);
void live_H_13(double *state, double *unused, double *out_556235881842754979);
void live_h_14(double *state, double *unused, double *out_6989834929130913681);
void live_H_14(double *state, double *unused, double *out_3150471355291351026);
void live_h_33(double *state, double *unused, double *out_8648904827452516106);
void live_H_33(double *state, double *unused, double *out_9020243303036326255);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}