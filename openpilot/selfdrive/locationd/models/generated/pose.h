#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_9103637474570468531);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4937747272762285736);
void pose_H_mod_fun(double *state, double *out_3491645730968939665);
void pose_f_fun(double *state, double dt, double *out_6190642828546855084);
void pose_F_fun(double *state, double dt, double *out_3436574488360553782);
void pose_h_4(double *state, double *unused, double *out_2259744882569505152);
void pose_H_4(double *state, double *unused, double *out_4245806733023652272);
void pose_h_10(double *state, double *unused, double *out_4827641738845025607);
void pose_H_10(double *state, double *unused, double *out_2777322440466673360);
void pose_h_13(double *state, double *unused, double *out_1423828173399503395);
void pose_H_13(double *state, double *unused, double *out_6590306132369198415);
void pose_h_14(double *state, double *unused, double *out_3030816551272021487);
void pose_H_14(double *state, double *unused, double *out_8209047589363136801);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}