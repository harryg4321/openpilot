#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_9103637474570468531) {
   out_9103637474570468531[0] = delta_x[0] + nom_x[0];
   out_9103637474570468531[1] = delta_x[1] + nom_x[1];
   out_9103637474570468531[2] = delta_x[2] + nom_x[2];
   out_9103637474570468531[3] = delta_x[3] + nom_x[3];
   out_9103637474570468531[4] = delta_x[4] + nom_x[4];
   out_9103637474570468531[5] = delta_x[5] + nom_x[5];
   out_9103637474570468531[6] = delta_x[6] + nom_x[6];
   out_9103637474570468531[7] = delta_x[7] + nom_x[7];
   out_9103637474570468531[8] = delta_x[8] + nom_x[8];
   out_9103637474570468531[9] = delta_x[9] + nom_x[9];
   out_9103637474570468531[10] = delta_x[10] + nom_x[10];
   out_9103637474570468531[11] = delta_x[11] + nom_x[11];
   out_9103637474570468531[12] = delta_x[12] + nom_x[12];
   out_9103637474570468531[13] = delta_x[13] + nom_x[13];
   out_9103637474570468531[14] = delta_x[14] + nom_x[14];
   out_9103637474570468531[15] = delta_x[15] + nom_x[15];
   out_9103637474570468531[16] = delta_x[16] + nom_x[16];
   out_9103637474570468531[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4937747272762285736) {
   out_4937747272762285736[0] = -nom_x[0] + true_x[0];
   out_4937747272762285736[1] = -nom_x[1] + true_x[1];
   out_4937747272762285736[2] = -nom_x[2] + true_x[2];
   out_4937747272762285736[3] = -nom_x[3] + true_x[3];
   out_4937747272762285736[4] = -nom_x[4] + true_x[4];
   out_4937747272762285736[5] = -nom_x[5] + true_x[5];
   out_4937747272762285736[6] = -nom_x[6] + true_x[6];
   out_4937747272762285736[7] = -nom_x[7] + true_x[7];
   out_4937747272762285736[8] = -nom_x[8] + true_x[8];
   out_4937747272762285736[9] = -nom_x[9] + true_x[9];
   out_4937747272762285736[10] = -nom_x[10] + true_x[10];
   out_4937747272762285736[11] = -nom_x[11] + true_x[11];
   out_4937747272762285736[12] = -nom_x[12] + true_x[12];
   out_4937747272762285736[13] = -nom_x[13] + true_x[13];
   out_4937747272762285736[14] = -nom_x[14] + true_x[14];
   out_4937747272762285736[15] = -nom_x[15] + true_x[15];
   out_4937747272762285736[16] = -nom_x[16] + true_x[16];
   out_4937747272762285736[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3491645730968939665) {
   out_3491645730968939665[0] = 1.0;
   out_3491645730968939665[1] = 0.0;
   out_3491645730968939665[2] = 0.0;
   out_3491645730968939665[3] = 0.0;
   out_3491645730968939665[4] = 0.0;
   out_3491645730968939665[5] = 0.0;
   out_3491645730968939665[6] = 0.0;
   out_3491645730968939665[7] = 0.0;
   out_3491645730968939665[8] = 0.0;
   out_3491645730968939665[9] = 0.0;
   out_3491645730968939665[10] = 0.0;
   out_3491645730968939665[11] = 0.0;
   out_3491645730968939665[12] = 0.0;
   out_3491645730968939665[13] = 0.0;
   out_3491645730968939665[14] = 0.0;
   out_3491645730968939665[15] = 0.0;
   out_3491645730968939665[16] = 0.0;
   out_3491645730968939665[17] = 0.0;
   out_3491645730968939665[18] = 0.0;
   out_3491645730968939665[19] = 1.0;
   out_3491645730968939665[20] = 0.0;
   out_3491645730968939665[21] = 0.0;
   out_3491645730968939665[22] = 0.0;
   out_3491645730968939665[23] = 0.0;
   out_3491645730968939665[24] = 0.0;
   out_3491645730968939665[25] = 0.0;
   out_3491645730968939665[26] = 0.0;
   out_3491645730968939665[27] = 0.0;
   out_3491645730968939665[28] = 0.0;
   out_3491645730968939665[29] = 0.0;
   out_3491645730968939665[30] = 0.0;
   out_3491645730968939665[31] = 0.0;
   out_3491645730968939665[32] = 0.0;
   out_3491645730968939665[33] = 0.0;
   out_3491645730968939665[34] = 0.0;
   out_3491645730968939665[35] = 0.0;
   out_3491645730968939665[36] = 0.0;
   out_3491645730968939665[37] = 0.0;
   out_3491645730968939665[38] = 1.0;
   out_3491645730968939665[39] = 0.0;
   out_3491645730968939665[40] = 0.0;
   out_3491645730968939665[41] = 0.0;
   out_3491645730968939665[42] = 0.0;
   out_3491645730968939665[43] = 0.0;
   out_3491645730968939665[44] = 0.0;
   out_3491645730968939665[45] = 0.0;
   out_3491645730968939665[46] = 0.0;
   out_3491645730968939665[47] = 0.0;
   out_3491645730968939665[48] = 0.0;
   out_3491645730968939665[49] = 0.0;
   out_3491645730968939665[50] = 0.0;
   out_3491645730968939665[51] = 0.0;
   out_3491645730968939665[52] = 0.0;
   out_3491645730968939665[53] = 0.0;
   out_3491645730968939665[54] = 0.0;
   out_3491645730968939665[55] = 0.0;
   out_3491645730968939665[56] = 0.0;
   out_3491645730968939665[57] = 1.0;
   out_3491645730968939665[58] = 0.0;
   out_3491645730968939665[59] = 0.0;
   out_3491645730968939665[60] = 0.0;
   out_3491645730968939665[61] = 0.0;
   out_3491645730968939665[62] = 0.0;
   out_3491645730968939665[63] = 0.0;
   out_3491645730968939665[64] = 0.0;
   out_3491645730968939665[65] = 0.0;
   out_3491645730968939665[66] = 0.0;
   out_3491645730968939665[67] = 0.0;
   out_3491645730968939665[68] = 0.0;
   out_3491645730968939665[69] = 0.0;
   out_3491645730968939665[70] = 0.0;
   out_3491645730968939665[71] = 0.0;
   out_3491645730968939665[72] = 0.0;
   out_3491645730968939665[73] = 0.0;
   out_3491645730968939665[74] = 0.0;
   out_3491645730968939665[75] = 0.0;
   out_3491645730968939665[76] = 1.0;
   out_3491645730968939665[77] = 0.0;
   out_3491645730968939665[78] = 0.0;
   out_3491645730968939665[79] = 0.0;
   out_3491645730968939665[80] = 0.0;
   out_3491645730968939665[81] = 0.0;
   out_3491645730968939665[82] = 0.0;
   out_3491645730968939665[83] = 0.0;
   out_3491645730968939665[84] = 0.0;
   out_3491645730968939665[85] = 0.0;
   out_3491645730968939665[86] = 0.0;
   out_3491645730968939665[87] = 0.0;
   out_3491645730968939665[88] = 0.0;
   out_3491645730968939665[89] = 0.0;
   out_3491645730968939665[90] = 0.0;
   out_3491645730968939665[91] = 0.0;
   out_3491645730968939665[92] = 0.0;
   out_3491645730968939665[93] = 0.0;
   out_3491645730968939665[94] = 0.0;
   out_3491645730968939665[95] = 1.0;
   out_3491645730968939665[96] = 0.0;
   out_3491645730968939665[97] = 0.0;
   out_3491645730968939665[98] = 0.0;
   out_3491645730968939665[99] = 0.0;
   out_3491645730968939665[100] = 0.0;
   out_3491645730968939665[101] = 0.0;
   out_3491645730968939665[102] = 0.0;
   out_3491645730968939665[103] = 0.0;
   out_3491645730968939665[104] = 0.0;
   out_3491645730968939665[105] = 0.0;
   out_3491645730968939665[106] = 0.0;
   out_3491645730968939665[107] = 0.0;
   out_3491645730968939665[108] = 0.0;
   out_3491645730968939665[109] = 0.0;
   out_3491645730968939665[110] = 0.0;
   out_3491645730968939665[111] = 0.0;
   out_3491645730968939665[112] = 0.0;
   out_3491645730968939665[113] = 0.0;
   out_3491645730968939665[114] = 1.0;
   out_3491645730968939665[115] = 0.0;
   out_3491645730968939665[116] = 0.0;
   out_3491645730968939665[117] = 0.0;
   out_3491645730968939665[118] = 0.0;
   out_3491645730968939665[119] = 0.0;
   out_3491645730968939665[120] = 0.0;
   out_3491645730968939665[121] = 0.0;
   out_3491645730968939665[122] = 0.0;
   out_3491645730968939665[123] = 0.0;
   out_3491645730968939665[124] = 0.0;
   out_3491645730968939665[125] = 0.0;
   out_3491645730968939665[126] = 0.0;
   out_3491645730968939665[127] = 0.0;
   out_3491645730968939665[128] = 0.0;
   out_3491645730968939665[129] = 0.0;
   out_3491645730968939665[130] = 0.0;
   out_3491645730968939665[131] = 0.0;
   out_3491645730968939665[132] = 0.0;
   out_3491645730968939665[133] = 1.0;
   out_3491645730968939665[134] = 0.0;
   out_3491645730968939665[135] = 0.0;
   out_3491645730968939665[136] = 0.0;
   out_3491645730968939665[137] = 0.0;
   out_3491645730968939665[138] = 0.0;
   out_3491645730968939665[139] = 0.0;
   out_3491645730968939665[140] = 0.0;
   out_3491645730968939665[141] = 0.0;
   out_3491645730968939665[142] = 0.0;
   out_3491645730968939665[143] = 0.0;
   out_3491645730968939665[144] = 0.0;
   out_3491645730968939665[145] = 0.0;
   out_3491645730968939665[146] = 0.0;
   out_3491645730968939665[147] = 0.0;
   out_3491645730968939665[148] = 0.0;
   out_3491645730968939665[149] = 0.0;
   out_3491645730968939665[150] = 0.0;
   out_3491645730968939665[151] = 0.0;
   out_3491645730968939665[152] = 1.0;
   out_3491645730968939665[153] = 0.0;
   out_3491645730968939665[154] = 0.0;
   out_3491645730968939665[155] = 0.0;
   out_3491645730968939665[156] = 0.0;
   out_3491645730968939665[157] = 0.0;
   out_3491645730968939665[158] = 0.0;
   out_3491645730968939665[159] = 0.0;
   out_3491645730968939665[160] = 0.0;
   out_3491645730968939665[161] = 0.0;
   out_3491645730968939665[162] = 0.0;
   out_3491645730968939665[163] = 0.0;
   out_3491645730968939665[164] = 0.0;
   out_3491645730968939665[165] = 0.0;
   out_3491645730968939665[166] = 0.0;
   out_3491645730968939665[167] = 0.0;
   out_3491645730968939665[168] = 0.0;
   out_3491645730968939665[169] = 0.0;
   out_3491645730968939665[170] = 0.0;
   out_3491645730968939665[171] = 1.0;
   out_3491645730968939665[172] = 0.0;
   out_3491645730968939665[173] = 0.0;
   out_3491645730968939665[174] = 0.0;
   out_3491645730968939665[175] = 0.0;
   out_3491645730968939665[176] = 0.0;
   out_3491645730968939665[177] = 0.0;
   out_3491645730968939665[178] = 0.0;
   out_3491645730968939665[179] = 0.0;
   out_3491645730968939665[180] = 0.0;
   out_3491645730968939665[181] = 0.0;
   out_3491645730968939665[182] = 0.0;
   out_3491645730968939665[183] = 0.0;
   out_3491645730968939665[184] = 0.0;
   out_3491645730968939665[185] = 0.0;
   out_3491645730968939665[186] = 0.0;
   out_3491645730968939665[187] = 0.0;
   out_3491645730968939665[188] = 0.0;
   out_3491645730968939665[189] = 0.0;
   out_3491645730968939665[190] = 1.0;
   out_3491645730968939665[191] = 0.0;
   out_3491645730968939665[192] = 0.0;
   out_3491645730968939665[193] = 0.0;
   out_3491645730968939665[194] = 0.0;
   out_3491645730968939665[195] = 0.0;
   out_3491645730968939665[196] = 0.0;
   out_3491645730968939665[197] = 0.0;
   out_3491645730968939665[198] = 0.0;
   out_3491645730968939665[199] = 0.0;
   out_3491645730968939665[200] = 0.0;
   out_3491645730968939665[201] = 0.0;
   out_3491645730968939665[202] = 0.0;
   out_3491645730968939665[203] = 0.0;
   out_3491645730968939665[204] = 0.0;
   out_3491645730968939665[205] = 0.0;
   out_3491645730968939665[206] = 0.0;
   out_3491645730968939665[207] = 0.0;
   out_3491645730968939665[208] = 0.0;
   out_3491645730968939665[209] = 1.0;
   out_3491645730968939665[210] = 0.0;
   out_3491645730968939665[211] = 0.0;
   out_3491645730968939665[212] = 0.0;
   out_3491645730968939665[213] = 0.0;
   out_3491645730968939665[214] = 0.0;
   out_3491645730968939665[215] = 0.0;
   out_3491645730968939665[216] = 0.0;
   out_3491645730968939665[217] = 0.0;
   out_3491645730968939665[218] = 0.0;
   out_3491645730968939665[219] = 0.0;
   out_3491645730968939665[220] = 0.0;
   out_3491645730968939665[221] = 0.0;
   out_3491645730968939665[222] = 0.0;
   out_3491645730968939665[223] = 0.0;
   out_3491645730968939665[224] = 0.0;
   out_3491645730968939665[225] = 0.0;
   out_3491645730968939665[226] = 0.0;
   out_3491645730968939665[227] = 0.0;
   out_3491645730968939665[228] = 1.0;
   out_3491645730968939665[229] = 0.0;
   out_3491645730968939665[230] = 0.0;
   out_3491645730968939665[231] = 0.0;
   out_3491645730968939665[232] = 0.0;
   out_3491645730968939665[233] = 0.0;
   out_3491645730968939665[234] = 0.0;
   out_3491645730968939665[235] = 0.0;
   out_3491645730968939665[236] = 0.0;
   out_3491645730968939665[237] = 0.0;
   out_3491645730968939665[238] = 0.0;
   out_3491645730968939665[239] = 0.0;
   out_3491645730968939665[240] = 0.0;
   out_3491645730968939665[241] = 0.0;
   out_3491645730968939665[242] = 0.0;
   out_3491645730968939665[243] = 0.0;
   out_3491645730968939665[244] = 0.0;
   out_3491645730968939665[245] = 0.0;
   out_3491645730968939665[246] = 0.0;
   out_3491645730968939665[247] = 1.0;
   out_3491645730968939665[248] = 0.0;
   out_3491645730968939665[249] = 0.0;
   out_3491645730968939665[250] = 0.0;
   out_3491645730968939665[251] = 0.0;
   out_3491645730968939665[252] = 0.0;
   out_3491645730968939665[253] = 0.0;
   out_3491645730968939665[254] = 0.0;
   out_3491645730968939665[255] = 0.0;
   out_3491645730968939665[256] = 0.0;
   out_3491645730968939665[257] = 0.0;
   out_3491645730968939665[258] = 0.0;
   out_3491645730968939665[259] = 0.0;
   out_3491645730968939665[260] = 0.0;
   out_3491645730968939665[261] = 0.0;
   out_3491645730968939665[262] = 0.0;
   out_3491645730968939665[263] = 0.0;
   out_3491645730968939665[264] = 0.0;
   out_3491645730968939665[265] = 0.0;
   out_3491645730968939665[266] = 1.0;
   out_3491645730968939665[267] = 0.0;
   out_3491645730968939665[268] = 0.0;
   out_3491645730968939665[269] = 0.0;
   out_3491645730968939665[270] = 0.0;
   out_3491645730968939665[271] = 0.0;
   out_3491645730968939665[272] = 0.0;
   out_3491645730968939665[273] = 0.0;
   out_3491645730968939665[274] = 0.0;
   out_3491645730968939665[275] = 0.0;
   out_3491645730968939665[276] = 0.0;
   out_3491645730968939665[277] = 0.0;
   out_3491645730968939665[278] = 0.0;
   out_3491645730968939665[279] = 0.0;
   out_3491645730968939665[280] = 0.0;
   out_3491645730968939665[281] = 0.0;
   out_3491645730968939665[282] = 0.0;
   out_3491645730968939665[283] = 0.0;
   out_3491645730968939665[284] = 0.0;
   out_3491645730968939665[285] = 1.0;
   out_3491645730968939665[286] = 0.0;
   out_3491645730968939665[287] = 0.0;
   out_3491645730968939665[288] = 0.0;
   out_3491645730968939665[289] = 0.0;
   out_3491645730968939665[290] = 0.0;
   out_3491645730968939665[291] = 0.0;
   out_3491645730968939665[292] = 0.0;
   out_3491645730968939665[293] = 0.0;
   out_3491645730968939665[294] = 0.0;
   out_3491645730968939665[295] = 0.0;
   out_3491645730968939665[296] = 0.0;
   out_3491645730968939665[297] = 0.0;
   out_3491645730968939665[298] = 0.0;
   out_3491645730968939665[299] = 0.0;
   out_3491645730968939665[300] = 0.0;
   out_3491645730968939665[301] = 0.0;
   out_3491645730968939665[302] = 0.0;
   out_3491645730968939665[303] = 0.0;
   out_3491645730968939665[304] = 1.0;
   out_3491645730968939665[305] = 0.0;
   out_3491645730968939665[306] = 0.0;
   out_3491645730968939665[307] = 0.0;
   out_3491645730968939665[308] = 0.0;
   out_3491645730968939665[309] = 0.0;
   out_3491645730968939665[310] = 0.0;
   out_3491645730968939665[311] = 0.0;
   out_3491645730968939665[312] = 0.0;
   out_3491645730968939665[313] = 0.0;
   out_3491645730968939665[314] = 0.0;
   out_3491645730968939665[315] = 0.0;
   out_3491645730968939665[316] = 0.0;
   out_3491645730968939665[317] = 0.0;
   out_3491645730968939665[318] = 0.0;
   out_3491645730968939665[319] = 0.0;
   out_3491645730968939665[320] = 0.0;
   out_3491645730968939665[321] = 0.0;
   out_3491645730968939665[322] = 0.0;
   out_3491645730968939665[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_6190642828546855084) {
   out_6190642828546855084[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_6190642828546855084[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_6190642828546855084[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_6190642828546855084[3] = dt*state[12] + state[3];
   out_6190642828546855084[4] = dt*state[13] + state[4];
   out_6190642828546855084[5] = dt*state[14] + state[5];
   out_6190642828546855084[6] = state[6];
   out_6190642828546855084[7] = state[7];
   out_6190642828546855084[8] = state[8];
   out_6190642828546855084[9] = state[9];
   out_6190642828546855084[10] = state[10];
   out_6190642828546855084[11] = state[11];
   out_6190642828546855084[12] = state[12];
   out_6190642828546855084[13] = state[13];
   out_6190642828546855084[14] = state[14];
   out_6190642828546855084[15] = state[15];
   out_6190642828546855084[16] = state[16];
   out_6190642828546855084[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3436574488360553782) {
   out_3436574488360553782[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3436574488360553782[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3436574488360553782[2] = 0;
   out_3436574488360553782[3] = 0;
   out_3436574488360553782[4] = 0;
   out_3436574488360553782[5] = 0;
   out_3436574488360553782[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3436574488360553782[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3436574488360553782[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3436574488360553782[9] = 0;
   out_3436574488360553782[10] = 0;
   out_3436574488360553782[11] = 0;
   out_3436574488360553782[12] = 0;
   out_3436574488360553782[13] = 0;
   out_3436574488360553782[14] = 0;
   out_3436574488360553782[15] = 0;
   out_3436574488360553782[16] = 0;
   out_3436574488360553782[17] = 0;
   out_3436574488360553782[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3436574488360553782[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3436574488360553782[20] = 0;
   out_3436574488360553782[21] = 0;
   out_3436574488360553782[22] = 0;
   out_3436574488360553782[23] = 0;
   out_3436574488360553782[24] = 0;
   out_3436574488360553782[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3436574488360553782[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3436574488360553782[27] = 0;
   out_3436574488360553782[28] = 0;
   out_3436574488360553782[29] = 0;
   out_3436574488360553782[30] = 0;
   out_3436574488360553782[31] = 0;
   out_3436574488360553782[32] = 0;
   out_3436574488360553782[33] = 0;
   out_3436574488360553782[34] = 0;
   out_3436574488360553782[35] = 0;
   out_3436574488360553782[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3436574488360553782[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3436574488360553782[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3436574488360553782[39] = 0;
   out_3436574488360553782[40] = 0;
   out_3436574488360553782[41] = 0;
   out_3436574488360553782[42] = 0;
   out_3436574488360553782[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3436574488360553782[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3436574488360553782[45] = 0;
   out_3436574488360553782[46] = 0;
   out_3436574488360553782[47] = 0;
   out_3436574488360553782[48] = 0;
   out_3436574488360553782[49] = 0;
   out_3436574488360553782[50] = 0;
   out_3436574488360553782[51] = 0;
   out_3436574488360553782[52] = 0;
   out_3436574488360553782[53] = 0;
   out_3436574488360553782[54] = 0;
   out_3436574488360553782[55] = 0;
   out_3436574488360553782[56] = 0;
   out_3436574488360553782[57] = 1;
   out_3436574488360553782[58] = 0;
   out_3436574488360553782[59] = 0;
   out_3436574488360553782[60] = 0;
   out_3436574488360553782[61] = 0;
   out_3436574488360553782[62] = 0;
   out_3436574488360553782[63] = 0;
   out_3436574488360553782[64] = 0;
   out_3436574488360553782[65] = 0;
   out_3436574488360553782[66] = dt;
   out_3436574488360553782[67] = 0;
   out_3436574488360553782[68] = 0;
   out_3436574488360553782[69] = 0;
   out_3436574488360553782[70] = 0;
   out_3436574488360553782[71] = 0;
   out_3436574488360553782[72] = 0;
   out_3436574488360553782[73] = 0;
   out_3436574488360553782[74] = 0;
   out_3436574488360553782[75] = 0;
   out_3436574488360553782[76] = 1;
   out_3436574488360553782[77] = 0;
   out_3436574488360553782[78] = 0;
   out_3436574488360553782[79] = 0;
   out_3436574488360553782[80] = 0;
   out_3436574488360553782[81] = 0;
   out_3436574488360553782[82] = 0;
   out_3436574488360553782[83] = 0;
   out_3436574488360553782[84] = 0;
   out_3436574488360553782[85] = dt;
   out_3436574488360553782[86] = 0;
   out_3436574488360553782[87] = 0;
   out_3436574488360553782[88] = 0;
   out_3436574488360553782[89] = 0;
   out_3436574488360553782[90] = 0;
   out_3436574488360553782[91] = 0;
   out_3436574488360553782[92] = 0;
   out_3436574488360553782[93] = 0;
   out_3436574488360553782[94] = 0;
   out_3436574488360553782[95] = 1;
   out_3436574488360553782[96] = 0;
   out_3436574488360553782[97] = 0;
   out_3436574488360553782[98] = 0;
   out_3436574488360553782[99] = 0;
   out_3436574488360553782[100] = 0;
   out_3436574488360553782[101] = 0;
   out_3436574488360553782[102] = 0;
   out_3436574488360553782[103] = 0;
   out_3436574488360553782[104] = dt;
   out_3436574488360553782[105] = 0;
   out_3436574488360553782[106] = 0;
   out_3436574488360553782[107] = 0;
   out_3436574488360553782[108] = 0;
   out_3436574488360553782[109] = 0;
   out_3436574488360553782[110] = 0;
   out_3436574488360553782[111] = 0;
   out_3436574488360553782[112] = 0;
   out_3436574488360553782[113] = 0;
   out_3436574488360553782[114] = 1;
   out_3436574488360553782[115] = 0;
   out_3436574488360553782[116] = 0;
   out_3436574488360553782[117] = 0;
   out_3436574488360553782[118] = 0;
   out_3436574488360553782[119] = 0;
   out_3436574488360553782[120] = 0;
   out_3436574488360553782[121] = 0;
   out_3436574488360553782[122] = 0;
   out_3436574488360553782[123] = 0;
   out_3436574488360553782[124] = 0;
   out_3436574488360553782[125] = 0;
   out_3436574488360553782[126] = 0;
   out_3436574488360553782[127] = 0;
   out_3436574488360553782[128] = 0;
   out_3436574488360553782[129] = 0;
   out_3436574488360553782[130] = 0;
   out_3436574488360553782[131] = 0;
   out_3436574488360553782[132] = 0;
   out_3436574488360553782[133] = 1;
   out_3436574488360553782[134] = 0;
   out_3436574488360553782[135] = 0;
   out_3436574488360553782[136] = 0;
   out_3436574488360553782[137] = 0;
   out_3436574488360553782[138] = 0;
   out_3436574488360553782[139] = 0;
   out_3436574488360553782[140] = 0;
   out_3436574488360553782[141] = 0;
   out_3436574488360553782[142] = 0;
   out_3436574488360553782[143] = 0;
   out_3436574488360553782[144] = 0;
   out_3436574488360553782[145] = 0;
   out_3436574488360553782[146] = 0;
   out_3436574488360553782[147] = 0;
   out_3436574488360553782[148] = 0;
   out_3436574488360553782[149] = 0;
   out_3436574488360553782[150] = 0;
   out_3436574488360553782[151] = 0;
   out_3436574488360553782[152] = 1;
   out_3436574488360553782[153] = 0;
   out_3436574488360553782[154] = 0;
   out_3436574488360553782[155] = 0;
   out_3436574488360553782[156] = 0;
   out_3436574488360553782[157] = 0;
   out_3436574488360553782[158] = 0;
   out_3436574488360553782[159] = 0;
   out_3436574488360553782[160] = 0;
   out_3436574488360553782[161] = 0;
   out_3436574488360553782[162] = 0;
   out_3436574488360553782[163] = 0;
   out_3436574488360553782[164] = 0;
   out_3436574488360553782[165] = 0;
   out_3436574488360553782[166] = 0;
   out_3436574488360553782[167] = 0;
   out_3436574488360553782[168] = 0;
   out_3436574488360553782[169] = 0;
   out_3436574488360553782[170] = 0;
   out_3436574488360553782[171] = 1;
   out_3436574488360553782[172] = 0;
   out_3436574488360553782[173] = 0;
   out_3436574488360553782[174] = 0;
   out_3436574488360553782[175] = 0;
   out_3436574488360553782[176] = 0;
   out_3436574488360553782[177] = 0;
   out_3436574488360553782[178] = 0;
   out_3436574488360553782[179] = 0;
   out_3436574488360553782[180] = 0;
   out_3436574488360553782[181] = 0;
   out_3436574488360553782[182] = 0;
   out_3436574488360553782[183] = 0;
   out_3436574488360553782[184] = 0;
   out_3436574488360553782[185] = 0;
   out_3436574488360553782[186] = 0;
   out_3436574488360553782[187] = 0;
   out_3436574488360553782[188] = 0;
   out_3436574488360553782[189] = 0;
   out_3436574488360553782[190] = 1;
   out_3436574488360553782[191] = 0;
   out_3436574488360553782[192] = 0;
   out_3436574488360553782[193] = 0;
   out_3436574488360553782[194] = 0;
   out_3436574488360553782[195] = 0;
   out_3436574488360553782[196] = 0;
   out_3436574488360553782[197] = 0;
   out_3436574488360553782[198] = 0;
   out_3436574488360553782[199] = 0;
   out_3436574488360553782[200] = 0;
   out_3436574488360553782[201] = 0;
   out_3436574488360553782[202] = 0;
   out_3436574488360553782[203] = 0;
   out_3436574488360553782[204] = 0;
   out_3436574488360553782[205] = 0;
   out_3436574488360553782[206] = 0;
   out_3436574488360553782[207] = 0;
   out_3436574488360553782[208] = 0;
   out_3436574488360553782[209] = 1;
   out_3436574488360553782[210] = 0;
   out_3436574488360553782[211] = 0;
   out_3436574488360553782[212] = 0;
   out_3436574488360553782[213] = 0;
   out_3436574488360553782[214] = 0;
   out_3436574488360553782[215] = 0;
   out_3436574488360553782[216] = 0;
   out_3436574488360553782[217] = 0;
   out_3436574488360553782[218] = 0;
   out_3436574488360553782[219] = 0;
   out_3436574488360553782[220] = 0;
   out_3436574488360553782[221] = 0;
   out_3436574488360553782[222] = 0;
   out_3436574488360553782[223] = 0;
   out_3436574488360553782[224] = 0;
   out_3436574488360553782[225] = 0;
   out_3436574488360553782[226] = 0;
   out_3436574488360553782[227] = 0;
   out_3436574488360553782[228] = 1;
   out_3436574488360553782[229] = 0;
   out_3436574488360553782[230] = 0;
   out_3436574488360553782[231] = 0;
   out_3436574488360553782[232] = 0;
   out_3436574488360553782[233] = 0;
   out_3436574488360553782[234] = 0;
   out_3436574488360553782[235] = 0;
   out_3436574488360553782[236] = 0;
   out_3436574488360553782[237] = 0;
   out_3436574488360553782[238] = 0;
   out_3436574488360553782[239] = 0;
   out_3436574488360553782[240] = 0;
   out_3436574488360553782[241] = 0;
   out_3436574488360553782[242] = 0;
   out_3436574488360553782[243] = 0;
   out_3436574488360553782[244] = 0;
   out_3436574488360553782[245] = 0;
   out_3436574488360553782[246] = 0;
   out_3436574488360553782[247] = 1;
   out_3436574488360553782[248] = 0;
   out_3436574488360553782[249] = 0;
   out_3436574488360553782[250] = 0;
   out_3436574488360553782[251] = 0;
   out_3436574488360553782[252] = 0;
   out_3436574488360553782[253] = 0;
   out_3436574488360553782[254] = 0;
   out_3436574488360553782[255] = 0;
   out_3436574488360553782[256] = 0;
   out_3436574488360553782[257] = 0;
   out_3436574488360553782[258] = 0;
   out_3436574488360553782[259] = 0;
   out_3436574488360553782[260] = 0;
   out_3436574488360553782[261] = 0;
   out_3436574488360553782[262] = 0;
   out_3436574488360553782[263] = 0;
   out_3436574488360553782[264] = 0;
   out_3436574488360553782[265] = 0;
   out_3436574488360553782[266] = 1;
   out_3436574488360553782[267] = 0;
   out_3436574488360553782[268] = 0;
   out_3436574488360553782[269] = 0;
   out_3436574488360553782[270] = 0;
   out_3436574488360553782[271] = 0;
   out_3436574488360553782[272] = 0;
   out_3436574488360553782[273] = 0;
   out_3436574488360553782[274] = 0;
   out_3436574488360553782[275] = 0;
   out_3436574488360553782[276] = 0;
   out_3436574488360553782[277] = 0;
   out_3436574488360553782[278] = 0;
   out_3436574488360553782[279] = 0;
   out_3436574488360553782[280] = 0;
   out_3436574488360553782[281] = 0;
   out_3436574488360553782[282] = 0;
   out_3436574488360553782[283] = 0;
   out_3436574488360553782[284] = 0;
   out_3436574488360553782[285] = 1;
   out_3436574488360553782[286] = 0;
   out_3436574488360553782[287] = 0;
   out_3436574488360553782[288] = 0;
   out_3436574488360553782[289] = 0;
   out_3436574488360553782[290] = 0;
   out_3436574488360553782[291] = 0;
   out_3436574488360553782[292] = 0;
   out_3436574488360553782[293] = 0;
   out_3436574488360553782[294] = 0;
   out_3436574488360553782[295] = 0;
   out_3436574488360553782[296] = 0;
   out_3436574488360553782[297] = 0;
   out_3436574488360553782[298] = 0;
   out_3436574488360553782[299] = 0;
   out_3436574488360553782[300] = 0;
   out_3436574488360553782[301] = 0;
   out_3436574488360553782[302] = 0;
   out_3436574488360553782[303] = 0;
   out_3436574488360553782[304] = 1;
   out_3436574488360553782[305] = 0;
   out_3436574488360553782[306] = 0;
   out_3436574488360553782[307] = 0;
   out_3436574488360553782[308] = 0;
   out_3436574488360553782[309] = 0;
   out_3436574488360553782[310] = 0;
   out_3436574488360553782[311] = 0;
   out_3436574488360553782[312] = 0;
   out_3436574488360553782[313] = 0;
   out_3436574488360553782[314] = 0;
   out_3436574488360553782[315] = 0;
   out_3436574488360553782[316] = 0;
   out_3436574488360553782[317] = 0;
   out_3436574488360553782[318] = 0;
   out_3436574488360553782[319] = 0;
   out_3436574488360553782[320] = 0;
   out_3436574488360553782[321] = 0;
   out_3436574488360553782[322] = 0;
   out_3436574488360553782[323] = 1;
}
void h_4(double *state, double *unused, double *out_2259744882569505152) {
   out_2259744882569505152[0] = state[6] + state[9];
   out_2259744882569505152[1] = state[7] + state[10];
   out_2259744882569505152[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4245806733023652272) {
   out_4245806733023652272[0] = 0;
   out_4245806733023652272[1] = 0;
   out_4245806733023652272[2] = 0;
   out_4245806733023652272[3] = 0;
   out_4245806733023652272[4] = 0;
   out_4245806733023652272[5] = 0;
   out_4245806733023652272[6] = 1;
   out_4245806733023652272[7] = 0;
   out_4245806733023652272[8] = 0;
   out_4245806733023652272[9] = 1;
   out_4245806733023652272[10] = 0;
   out_4245806733023652272[11] = 0;
   out_4245806733023652272[12] = 0;
   out_4245806733023652272[13] = 0;
   out_4245806733023652272[14] = 0;
   out_4245806733023652272[15] = 0;
   out_4245806733023652272[16] = 0;
   out_4245806733023652272[17] = 0;
   out_4245806733023652272[18] = 0;
   out_4245806733023652272[19] = 0;
   out_4245806733023652272[20] = 0;
   out_4245806733023652272[21] = 0;
   out_4245806733023652272[22] = 0;
   out_4245806733023652272[23] = 0;
   out_4245806733023652272[24] = 0;
   out_4245806733023652272[25] = 1;
   out_4245806733023652272[26] = 0;
   out_4245806733023652272[27] = 0;
   out_4245806733023652272[28] = 1;
   out_4245806733023652272[29] = 0;
   out_4245806733023652272[30] = 0;
   out_4245806733023652272[31] = 0;
   out_4245806733023652272[32] = 0;
   out_4245806733023652272[33] = 0;
   out_4245806733023652272[34] = 0;
   out_4245806733023652272[35] = 0;
   out_4245806733023652272[36] = 0;
   out_4245806733023652272[37] = 0;
   out_4245806733023652272[38] = 0;
   out_4245806733023652272[39] = 0;
   out_4245806733023652272[40] = 0;
   out_4245806733023652272[41] = 0;
   out_4245806733023652272[42] = 0;
   out_4245806733023652272[43] = 0;
   out_4245806733023652272[44] = 1;
   out_4245806733023652272[45] = 0;
   out_4245806733023652272[46] = 0;
   out_4245806733023652272[47] = 1;
   out_4245806733023652272[48] = 0;
   out_4245806733023652272[49] = 0;
   out_4245806733023652272[50] = 0;
   out_4245806733023652272[51] = 0;
   out_4245806733023652272[52] = 0;
   out_4245806733023652272[53] = 0;
}
void h_10(double *state, double *unused, double *out_4827641738845025607) {
   out_4827641738845025607[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_4827641738845025607[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_4827641738845025607[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2777322440466673360) {
   out_2777322440466673360[0] = 0;
   out_2777322440466673360[1] = 9.8100000000000005*cos(state[1]);
   out_2777322440466673360[2] = 0;
   out_2777322440466673360[3] = 0;
   out_2777322440466673360[4] = -state[8];
   out_2777322440466673360[5] = state[7];
   out_2777322440466673360[6] = 0;
   out_2777322440466673360[7] = state[5];
   out_2777322440466673360[8] = -state[4];
   out_2777322440466673360[9] = 0;
   out_2777322440466673360[10] = 0;
   out_2777322440466673360[11] = 0;
   out_2777322440466673360[12] = 1;
   out_2777322440466673360[13] = 0;
   out_2777322440466673360[14] = 0;
   out_2777322440466673360[15] = 1;
   out_2777322440466673360[16] = 0;
   out_2777322440466673360[17] = 0;
   out_2777322440466673360[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2777322440466673360[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2777322440466673360[20] = 0;
   out_2777322440466673360[21] = state[8];
   out_2777322440466673360[22] = 0;
   out_2777322440466673360[23] = -state[6];
   out_2777322440466673360[24] = -state[5];
   out_2777322440466673360[25] = 0;
   out_2777322440466673360[26] = state[3];
   out_2777322440466673360[27] = 0;
   out_2777322440466673360[28] = 0;
   out_2777322440466673360[29] = 0;
   out_2777322440466673360[30] = 0;
   out_2777322440466673360[31] = 1;
   out_2777322440466673360[32] = 0;
   out_2777322440466673360[33] = 0;
   out_2777322440466673360[34] = 1;
   out_2777322440466673360[35] = 0;
   out_2777322440466673360[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2777322440466673360[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2777322440466673360[38] = 0;
   out_2777322440466673360[39] = -state[7];
   out_2777322440466673360[40] = state[6];
   out_2777322440466673360[41] = 0;
   out_2777322440466673360[42] = state[4];
   out_2777322440466673360[43] = -state[3];
   out_2777322440466673360[44] = 0;
   out_2777322440466673360[45] = 0;
   out_2777322440466673360[46] = 0;
   out_2777322440466673360[47] = 0;
   out_2777322440466673360[48] = 0;
   out_2777322440466673360[49] = 0;
   out_2777322440466673360[50] = 1;
   out_2777322440466673360[51] = 0;
   out_2777322440466673360[52] = 0;
   out_2777322440466673360[53] = 1;
}
void h_13(double *state, double *unused, double *out_1423828173399503395) {
   out_1423828173399503395[0] = state[3];
   out_1423828173399503395[1] = state[4];
   out_1423828173399503395[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6590306132369198415) {
   out_6590306132369198415[0] = 0;
   out_6590306132369198415[1] = 0;
   out_6590306132369198415[2] = 0;
   out_6590306132369198415[3] = 1;
   out_6590306132369198415[4] = 0;
   out_6590306132369198415[5] = 0;
   out_6590306132369198415[6] = 0;
   out_6590306132369198415[7] = 0;
   out_6590306132369198415[8] = 0;
   out_6590306132369198415[9] = 0;
   out_6590306132369198415[10] = 0;
   out_6590306132369198415[11] = 0;
   out_6590306132369198415[12] = 0;
   out_6590306132369198415[13] = 0;
   out_6590306132369198415[14] = 0;
   out_6590306132369198415[15] = 0;
   out_6590306132369198415[16] = 0;
   out_6590306132369198415[17] = 0;
   out_6590306132369198415[18] = 0;
   out_6590306132369198415[19] = 0;
   out_6590306132369198415[20] = 0;
   out_6590306132369198415[21] = 0;
   out_6590306132369198415[22] = 1;
   out_6590306132369198415[23] = 0;
   out_6590306132369198415[24] = 0;
   out_6590306132369198415[25] = 0;
   out_6590306132369198415[26] = 0;
   out_6590306132369198415[27] = 0;
   out_6590306132369198415[28] = 0;
   out_6590306132369198415[29] = 0;
   out_6590306132369198415[30] = 0;
   out_6590306132369198415[31] = 0;
   out_6590306132369198415[32] = 0;
   out_6590306132369198415[33] = 0;
   out_6590306132369198415[34] = 0;
   out_6590306132369198415[35] = 0;
   out_6590306132369198415[36] = 0;
   out_6590306132369198415[37] = 0;
   out_6590306132369198415[38] = 0;
   out_6590306132369198415[39] = 0;
   out_6590306132369198415[40] = 0;
   out_6590306132369198415[41] = 1;
   out_6590306132369198415[42] = 0;
   out_6590306132369198415[43] = 0;
   out_6590306132369198415[44] = 0;
   out_6590306132369198415[45] = 0;
   out_6590306132369198415[46] = 0;
   out_6590306132369198415[47] = 0;
   out_6590306132369198415[48] = 0;
   out_6590306132369198415[49] = 0;
   out_6590306132369198415[50] = 0;
   out_6590306132369198415[51] = 0;
   out_6590306132369198415[52] = 0;
   out_6590306132369198415[53] = 0;
}
void h_14(double *state, double *unused, double *out_3030816551272021487) {
   out_3030816551272021487[0] = state[6];
   out_3030816551272021487[1] = state[7];
   out_3030816551272021487[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8209047589363136801) {
   out_8209047589363136801[0] = 0;
   out_8209047589363136801[1] = 0;
   out_8209047589363136801[2] = 0;
   out_8209047589363136801[3] = 0;
   out_8209047589363136801[4] = 0;
   out_8209047589363136801[5] = 0;
   out_8209047589363136801[6] = 1;
   out_8209047589363136801[7] = 0;
   out_8209047589363136801[8] = 0;
   out_8209047589363136801[9] = 0;
   out_8209047589363136801[10] = 0;
   out_8209047589363136801[11] = 0;
   out_8209047589363136801[12] = 0;
   out_8209047589363136801[13] = 0;
   out_8209047589363136801[14] = 0;
   out_8209047589363136801[15] = 0;
   out_8209047589363136801[16] = 0;
   out_8209047589363136801[17] = 0;
   out_8209047589363136801[18] = 0;
   out_8209047589363136801[19] = 0;
   out_8209047589363136801[20] = 0;
   out_8209047589363136801[21] = 0;
   out_8209047589363136801[22] = 0;
   out_8209047589363136801[23] = 0;
   out_8209047589363136801[24] = 0;
   out_8209047589363136801[25] = 1;
   out_8209047589363136801[26] = 0;
   out_8209047589363136801[27] = 0;
   out_8209047589363136801[28] = 0;
   out_8209047589363136801[29] = 0;
   out_8209047589363136801[30] = 0;
   out_8209047589363136801[31] = 0;
   out_8209047589363136801[32] = 0;
   out_8209047589363136801[33] = 0;
   out_8209047589363136801[34] = 0;
   out_8209047589363136801[35] = 0;
   out_8209047589363136801[36] = 0;
   out_8209047589363136801[37] = 0;
   out_8209047589363136801[38] = 0;
   out_8209047589363136801[39] = 0;
   out_8209047589363136801[40] = 0;
   out_8209047589363136801[41] = 0;
   out_8209047589363136801[42] = 0;
   out_8209047589363136801[43] = 0;
   out_8209047589363136801[44] = 1;
   out_8209047589363136801[45] = 0;
   out_8209047589363136801[46] = 0;
   out_8209047589363136801[47] = 0;
   out_8209047589363136801[48] = 0;
   out_8209047589363136801[49] = 0;
   out_8209047589363136801[50] = 0;
   out_8209047589363136801[51] = 0;
   out_8209047589363136801[52] = 0;
   out_8209047589363136801[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_9103637474570468531) {
  err_fun(nom_x, delta_x, out_9103637474570468531);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4937747272762285736) {
  inv_err_fun(nom_x, true_x, out_4937747272762285736);
}
void pose_H_mod_fun(double *state, double *out_3491645730968939665) {
  H_mod_fun(state, out_3491645730968939665);
}
void pose_f_fun(double *state, double dt, double *out_6190642828546855084) {
  f_fun(state,  dt, out_6190642828546855084);
}
void pose_F_fun(double *state, double dt, double *out_3436574488360553782) {
  F_fun(state,  dt, out_3436574488360553782);
}
void pose_h_4(double *state, double *unused, double *out_2259744882569505152) {
  h_4(state, unused, out_2259744882569505152);
}
void pose_H_4(double *state, double *unused, double *out_4245806733023652272) {
  H_4(state, unused, out_4245806733023652272);
}
void pose_h_10(double *state, double *unused, double *out_4827641738845025607) {
  h_10(state, unused, out_4827641738845025607);
}
void pose_H_10(double *state, double *unused, double *out_2777322440466673360) {
  H_10(state, unused, out_2777322440466673360);
}
void pose_h_13(double *state, double *unused, double *out_1423828173399503395) {
  h_13(state, unused, out_1423828173399503395);
}
void pose_H_13(double *state, double *unused, double *out_6590306132369198415) {
  H_13(state, unused, out_6590306132369198415);
}
void pose_h_14(double *state, double *unused, double *out_3030816551272021487) {
  h_14(state, unused, out_3030816551272021487);
}
void pose_H_14(double *state, double *unused, double *out_8209047589363136801) {
  H_14(state, unused, out_8209047589363136801);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
