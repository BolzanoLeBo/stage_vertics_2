/*
 * kalman.c
 *
 *  Created on: 31 juil. 2023
 *      Author: loict
 */
#include "kalman.h"

float position [500] ={
  0.314724, 0.505625, -0.174344,  0.708896, 0.521778, 0.0769659,  0.343141, 0.691099, 1.17486,  1.24822,  0.499084, 1.3618, 1.38921,  0.948934, 1.28573,  0.639381, 0.921335, 1.4074, 1.26605,  1.40579,  1.06504,  0.398921, 1.15763,  1.1797, 0.854198, 0.856212, 0.758634, 0.319607, 0.490466, -0.089564,  0.347166, -0.426586,  -0.281451,  -0.611574,  -0.658409,  -0.0273254, -0.247692,  -0.712737,  -0.161636,  -1.15332, -0.818058,  -0.936719,  -0.606059,  -0.620966,  -1.26473, -0.987766,  -1.0481,  -0.85361, -0.7868,  -0.727766,
-1.1829,  -0.746112,  -0.728357,  -1.16966, -1.15377, -0.707176,  -0.171523,  -0.7103,  -0.379334,  -0.650065,  -0.0281484, -0.427067,  -0.0771324, 0.215891, 0.507452, 0.674411, 0.358757, 0.0434744,  0.143407, 0.335948, 0.997704, 0.483251, 1.10795,  0.593962, 1.32797,  0.787984, 0.664515, 0.739252, 1.11459,  0.97223,  0.841018, 1.30072,  1.02599,  0.951895, 1.27179,  0.584326, 0.991597, 0.916698, 0.465363, 0.568842, -0.0120272, -0.126952,  0.253687, 0.403622, 0.458786, -0.445245,  -0.105503,  -0.30237, -0.854577,  -0.620413,
-0.881839,  -0.330786,  -0.88866, -0.739153,  -1.16218, -0.777714,  -1.1598,  -0.802556,  -0.791722,  -0.747285,  -1.04945, -1.41073, -1.2502,  -0.540682,  -1.26695, -0.549635,  -0.784486,  -0.265849,  -1.11535, -0.675459,  -0.92992, 0.0122506,  -0.853595,  0.0116787,  0.151699, 0.302373, -0.381941,  0.0330147,  -0.00861977,  0.627543, 0.351581, 0.919309, 0.273921, 0.433373, 0.385915, 0.439853, 1.22845,  0.985659, 0.993556, 0.616962, 1.34364,  1.12136,  0.848979, 1.00002,  0.867466, 0.510862, 0.634707, 0.469066, 0.47216,  0.462834,
0.567555, 0.120851, 0.889115, 0.841528, 0.293982, 0.19572,  -0.0545269, 0.408017, -0.22266, -0.579656,  -0.00765125,  -0.492333,  -0.730731,  -0.65414, -1.04165, -1.07981, -0.336301,  -0.381007,  -0.812358,  -1.36934, -1.22662, -1.13091, -0.675706,  -1.48437, -1.44964, -1.30664, -0.799729,  -0.68086, -0.719456,  -0.862233,  -0.703978,  -0.884993,  -0.36014, -0.833354,  -0.24779, -0.658969,  -0.378489,  -0.0233805, 0.230692, -0.368452,  0.579263, 0.523547, 0.330107, 0.371224, 0.46985,  0.411889, 0.690472, 0.762345, 1.1313, 1.16248,
1.05726,  0.827734, 1.2874, 1.02559,  0.85052,  1.43583,  1.35985,  1.01131,  1.05127,  0.974202, 0.544398, 0.57904,  0.682085, 0.367911, 0.901624, 0.166403, 0.107172, -0.0422393, -0.082349,  0.0267211,  -0.197749,  0.314743, -0.277129,  -0.619148,  0.00732529, -0.00742613,  -0.633056,  -1.03984, -0.96543, -0.880078,  -0.751324,  -1.13298, -0.832367,  -0.754672,  -1.26517, -1.38066, -1.2026,  -1.17171, -1.04763, -0.935543,  -1.32006, -1.09622, -0.502241,  -1.21056, -0.240056,  -0.361027,  -0.519288,  -0.340836,  -0.589352,  -0.271797,
0.330737, 0.0140703,  0.0883439,  -0.101926,  0.252986, 0.483118, 0.629576, 0.432837, 0.486272, 1.18215,  0.300297, 1.2085, 1.28917,  1.21586,  0.552997, 0.741229, 0.830002, 1.17972,  0.631904, 1.20199,  0.563138, 1.07619,  0.873447, 1.10638,  0.982153, 1.10296,  1.0153, 0.377439, 0.655492, 0.0634624,  -0.198553,  0.417526, 0.0742879,  -0.0457412, 0.279387, -0.113889,  -0.202274,  -0.0534852, -0.1963,  -0.508916,  -0.980711,  -0.995068,  -0.41251, -1.32639, -0.912653,  -1.2731,  -0.491425,  -0.776793,  -0.99851, -1.02741,
-1.42841, -0.785724,  -1.39526, -1.32687, -0.828319,  -1.1964,  -0.410212,  -0.33877, -0.355275,  -0.843476,  -0.244432,  -0.292102,  0.258722, 0.0333244,  0.284405, 0.0377722,  0.115427, 0.605582, -0.0418299, 0.0985595,  0.224815, 0.522893, 1.03755,  1.07669,  0.393231, 0.783128, 0.953026, 0.875975, 1.13948,  1.12422,  0.791896, 0.925242, 0.49283,  1.43539,  0.582978, 0.477356, 0.690176, 0.45434,  0.676809, 0.450649, 0.980713, 0.862056, -0.0973716, 0.49254,  -0.074012,  -0.0196769, 0.00540287, 0.300738, -0.322367,  0.147228,
-0.626728,  -0.315163,  -0.432845,  -0.636991,  -0.548191,  -0.642491,  -1.18552, -1.28165, -0.447506,  -1.30293, -1.45918, -0.938399,  -0.615565,  -0.816123,  -1.27289, -1.0628,  -0.930078,  -0.359353,  -1.12637, -0.361214,  -0.498774,  -0.687637,  -0.787722,  -0.460347,  -0.31265, -0.577187,  -0.00944217,  -0.272924,  -0.0146638, 0.282526, 0.0481747,  0.180677, 0.597296, 0.330656, 0.969273, 1.20064,  1.01413,  0.685828, 0.975679, 0.54013,  1.3701, 1.36525,  1.31532,  0.760275, 1.08591,  0.496158, 0.871272, 0.721646, 0.524245, 0.48674,
0.667999, 0.269037, 0.696284, 0.485664, 0.622526, 0.534039, 0.376918, -0.326155,  -0.390501,  -0.239661,  -0.127758,  -0.101954,  -0.443996,  -0.123336,  -0.31223, -0.143911,  -0.657077,  -0.932237,  -1.21316, -0.761052,  -0.637719,  -1.02842, -1.38689, -1.22732, -1.34628, -1.21508, -1.0422,  -0.931529,  -0.968054,  -0.507667,  -0.813723,  -0.328578,  -0.567202,  -0.172884,  -0.809237,  -0.287693,  -0.583988,  -0.106754,  0.0138514,  -0.514212,  -0.227508,  -0.158529,  0.38382,  0.656777, 0.250124, 0.775405, 0.754496, 0.164371, 0.831747, 0.680979,
1.26689,  0.400248, 0.900757, 0.892491, 0.94922,  1.26875,  0.821372, 1.27397,  0.94103,  0.476192, 0.577663, 1.0759, 0.771438, 0.386515, 0.503429, 0.691586, 0.191997, 0.649736, 0.0611061,  0.639448, -0.107365,  0.289388, -0.387375,  -0.387703,  -0.681502,  -0.291096,  -0.274962,  -0.498173,  -0.700035,  -0.556066,  -0.620637,  -0.649308,  -0.744331,  -0.477943,  -1.24796, -0.771827,  -1.25929, -1.38059, -0.887156,  -1.02886, -0.995027,  -0.757034,  -0.604737,  -0.972106,  -0.599399,  -0.776726,  -0.27551, -0.202906,  -0.692413,  -0.243939


          };

float velocity [500] ={
1.08225,  1.03574,  1.35001,  0.720116, 0.739135, 0.496797, 1.26517,  0.910394, 0.67617,  0.760927, 0.585018, 0.600908, 0.406244, 0.488545, 0.192462, 0.564442, -0.310523,  -0.523046,  -0.617505,  -0.759698,  -0.511567,  -0.556473,  -0.722685,  -0.402771,  -0.609497,  -0.529163,  -0.424035,  -0.431331,  -1.25019, -1.33208, -0.793726,  -1.40532, -0.97289, -0.957136,  -0.605658,  -0.951603,  -1.0033,  -0.676669,  -0.54971, -0.70588, -0.805931,  -0.924827,  -0.404169,  -0.638654,  -0.762879,  0.0441375,  -0.369367,  -0.0699864, 0.275295, 0.0457406,
0.520002, 0.272685, 0.651933, 0.758422, 0.576998, 0.228247, 0.606424, 0.759022, 0.65579,  0.624532, 1.28189,  0.91319,  1.38431,  0.891042, 1.2623, 0.873379, 1.25875,  1.16946,  0.746793, 0.531744, 1.04431,  1.13385,  0.435917, 0.697342, 0.377192, 0.680136, 0.520114, -0.179373,  0.415936, 0.44387,  -0.131077,  0.140737, -0.251129,  -0.776624,  -0.819426,  -0.695057,  -0.430014,  -0.423063,  -0.52113, -1.04691, -0.877066,  -1.35777, -1.36314, -1.35593, -0.821041,  -1.002, -1.29498, -0.967359,  -1.28282, -1.33422,
-0.488359,  -0.720009,  -0.284657,  -0.444159,  -0.478193,  -0.16014, -0.00632429,  0.197622, -0.693808,  0.27001,  0.116992, 0.594186, 0.230685, 0.279269, 0.694838, 0.211148, 0.566384, 1.04845,  0.795094, 1.13125,  1.08249,  0.979193, 0.680368, 1.13115,  0.569675, 1.12376,  1.16038,  1.22084,  1.36358,  1.42716,  1.17648,  0.942413, 1.2342, 0.82284,  0.189176, 0.21578,  0.874415, 0.407671, 0.675671, -0.0556451, 0.189029, 0.167042, -0.530801,  -0.047401,  -0.397406,  -0.805392,  -0.456915,  -0.841074,  -0.992269,  -0.985478,
-1.11317, -1.13174, -1.33108, -0.782733,  -1.17109, -0.939857,  -0.799015,  -1.00085, -0.959967,  -1.03643, -1.33373, -0.933776,  -0.528374,  -0.455878,  -0.999654,  -0.993936,  -0.562848,  -0.406674,  -0.54365, -0.663793,  0.17277,  -0.595738,  -0.472969,  -0.33672, -0.212596,  0.340399, 0.389454, -0.0390294, 0.929158, 0.810706, 0.898158, 0.295396, 1.15679,  1.28716,  1.38504,  1.29846,  1.25458,  1.00221,  0.676375, 0.897317, 0.622636, 0.499692, 1.37836,  0.70156,  0.647826, 0.628751, 0.698454, 0.807848, 0.10655,  0.839392,
0.467115, 0.669001, 0.0664526,  0.0660886,  -0.42541, -0.402456,  -0.0158749, -0.445188,  0.0278928,  -0.843312,  -0.0593113, -0.588537,  -0.496112,  -0.271023,  -1.04245, -0.967269,  -0.959632,  -0.693958,  -0.663583,  -1.39563, -1.32184, -1.13445, -1.42157, -0.930798,  -1.08173, -1.19764, -1.11136, -0.353956,  -0.514939,  -0.646184,  -0.120701,  -0.841678,  -0.108548,  -0.0226921, -0.0993765, -0.377711,  0.135257, -0.062446,  -0.130064,  0.0442544,  0.819121, 0.0839197,  0.338121, 0.226605, 0.685066, 0.319693, 1.25861,  0.604478, 0.538521, 0.780405,
0.94726,  0.601133, 1.49313,  0.818138, 0.761845, 0.49536,  0.69105,  0.389728, 0.790949, 0.981242, 0.777989, 0.15745,  0.0633895,  0.669915, 0.704033, 0.235907, -0.287493,  0.329346, -0.258215,  -0.401228,  -0.0458254, -0.875821,  -0.927871,  -0.393803,  -0.53804, -0.688785,  -0.551414,  -0.632301,  -0.60822, -1.14277, -0.770074,  -0.928172,  -1.10072, -1.43808, -0.711939,  -1.13706, -0.839572,  -0.66951, -1.26018, -1.18268, -0.698517,  -0.692838,  -0.210827,  -0.219569,  -0.196234,  -0.786987,  -0.669797,  -0.556094,  0.253236, 0.49785,
0.337967, -0.115798,  0.570193, 0.0496988,  0.144325, 0.749774, 0.514008, 0.908297, 1.06537,  0.953022, 1.15477,  0.685336, 1.21174,  1.46389,  1.3668, 0.582702, 0.849543, 0.829121, 1.11217,  0.983048, 1.12359,  0.642658, 0.414071, 0.220673, 0.825569, 0.173406, 0.265427, 0.334589, -0.085407,  0.228555, -0.0287964, -0.46119, 0.0702681,  -0.707572,  -0.607546,  -0.753662,  -0.544678,  -1.06282, -0.821227,  -1.18666, -1.23629, -0.612723,  -1.1452,  -0.863491,  -0.523197,  -1.06586, -0.804346,  -0.731767,  -1.0381,  -0.786426,
-1.29394, -0.422671,  -1.11315, -0.970615,  -0.367783,  -0.600179,  -0.235121,  -0.519332,  -0.54951, -0.689102,  0.0453312,  -0.0987473, 0.0233623,  0.280699, -0.172242,  0.178997, 0.72711,  0.737482, 0.247638, 0.327495, 0.357766, 0.333657, 0.801117, 1.07698,  1.17852,  1.01145,  0.60391,  1.13177,  0.621415, 0.614193, 0.553668, 0.562742, 0.545408, 0.521083, 0.581749, 0.512498, 0.338477, 0.290597, 0.845727, 0.564753, 0.322381, -0.146474,  -0.218118,  -0.45274, 0.284075, -0.0213517, -0.266341,  -0.603525,  -0.839409,  -0.466722,
-0.179003,  -1.06756, -1.04388, -0.960547,  -1.33046, -0.758423,  -1.06878, -0.507282,  -1.09699, -0.877571,  -1.33297, -1.08523, -1.27501, -0.638253,  -0.476518,  -0.939647,  -0.539785,  -0.858823,  -0.543468,  -0.157063,  -0.302495,  -0.471176,  -0.410702,  -0.158677,  -0.0888549, -0.05201, 0.245704, 0.527059, 0.303135, 0.398657, 0.179986, 0.159813, 0.499481, 0.593647, 0.988892, 1.34287,  1.36354,  0.918304, 0.723908, 1.26051,  1.25917,  1.23373,  1.22008,  0.555876, 1.09558,  0.832219, 0.527374, 0.351837, 1.00747,  0.282656,
0.188892, 0.603736, 0.740191, 0.266958, 0.355198, -0.293341,  0.406568, -0.105495,  -0.0646716, -0.803427,  -0.122974,  -0.271429,  -0.982534,  -0.654327,  -0.923402,  -0.765163,  -0.966999,  -0.996403,  -1.26727, -1.21965, -1.4718,  -0.576039,  -0.843405,  -0.551919,  -1.29861, -0.509003,  -0.594127,  -0.761194,  -0.839977,  -0.95603, -0.388198,  -0.831579,  -0.910568,  -0.117189,  -0.119237,  0.0217539,  0.0475161,  -0.0756379, -0.00411861,  0.520015, 0.11802,  0.708847, 0.773156, 0.921284, 0.653909, 0.85671,  1.23751,  0.788294, 0.453624, 1.3007
           };


#ifdef INPUT_RAM2
__attribute__((section(".ram2data")))
#endif
int n = sizeof(position)/sizeof(position[0]);

// This can not be const because the kalman_parameters have to be modified!!!
#ifdef INPUT_RAM2
__attribute__((section(".ram2data")))
#endif
kalman_filter_param kalman_parameters = {
    /* A_mat2f[4]; */
    {1.0, 0.0001,
     0.0, 1.0},
    /* float Q_mat2f[4]; */
    {0.002, 0.00,
    0.00, 0.002},
    /* float H_vec2f[2]; */
    {1.0, 1},
    /*R_mat1f; */
    0.04,
    /* float P_plus_mat2f[4]; */
    {0.1, 0,
     0, 1},
    /* float x_plus_vec2f[2]; */
    {0.0, 0.0},
  };


float* KalmanFilterStep(float z_plus_0, float z_plus_1, kalman_filter_param* kalman_param)
{

  /*0x2000000 +1  movs #48*/
  float P_estimate_mat2f[4]; /* matrix 2x2 */
  float x_estimate_vec2f[2]; /* vector 2x1 */
  static float x_plus_vec2f_return[2];
  float K_gain_vec2f[2];  /* matrix 2x1 */
  float denominator_help;/* 0x20000001*/


  /* Prediction Step 1 */
  x_estimate_vec2f[0] = kalman_param->A_mat2f[0]*kalman_param->x_plus_vec2f[0] + kalman_param->A_mat2f[1]*kalman_param->x_plus_vec2f[1];
  x_estimate_vec2f[1] = kalman_param->A_mat2f[2]*kalman_param->x_plus_vec2f[0] + kalman_param->A_mat2f[3]*kalman_param->x_plus_vec2f[1];

  /* Prediction Step 2 */
  P_estimate_mat2f[0] = (kalman_param->A_mat2f[0]*kalman_param->P_plus_mat2f[0] +
               kalman_param->A_mat2f[1]*kalman_param->P_plus_mat2f[2])*kalman_param->A_mat2f[0];

  P_estimate_mat2f[0] += (kalman_param->A_mat2f[0]*kalman_param->P_plus_mat2f[1] +
              kalman_param->A_mat2f[1]*kalman_param->P_plus_mat2f[3])*kalman_param->A_mat2f[1];

  P_estimate_mat2f[0] += kalman_param->Q_mat2f[0];




  P_estimate_mat2f[1] = (kalman_param->A_mat2f[0]*kalman_param->P_plus_mat2f[0] +
              kalman_param->A_mat2f[1]*kalman_param->P_plus_mat2f[2])*kalman_param->A_mat2f[2];

  P_estimate_mat2f[1] += (kalman_param->A_mat2f[0]*kalman_param->P_plus_mat2f[1] +
              kalman_param->A_mat2f[1]*kalman_param->P_plus_mat2f[3])*kalman_param->A_mat2f[3];

  P_estimate_mat2f[1] += kalman_param->Q_mat2f[1];




  P_estimate_mat2f[2] = (kalman_param->A_mat2f[2]*kalman_param->P_plus_mat2f[0] +
              kalman_param->A_mat2f[3]*kalman_param->P_plus_mat2f[2])*kalman_param->A_mat2f[0];

  P_estimate_mat2f[2] += (kalman_param->A_mat2f[2]*kalman_param->P_plus_mat2f[1] +
              kalman_param->A_mat2f[3]*kalman_param->P_plus_mat2f[3])*kalman_param->A_mat2f[1];

  P_estimate_mat2f[2] += kalman_param->Q_mat2f[2];




  P_estimate_mat2f[3] = (kalman_param->A_mat2f[2]*kalman_param->P_plus_mat2f[0] +
              kalman_param->A_mat2f[3]*kalman_param->P_plus_mat2f[2])*kalman_param->A_mat2f[2];

  P_estimate_mat2f[3] += (kalman_param->A_mat2f[2]*kalman_param->P_plus_mat2f[1] +
              kalman_param->A_mat2f[3]*kalman_param->P_plus_mat2f[3])*kalman_param->A_mat2f[3];

  P_estimate_mat2f[3] += kalman_param->Q_mat2f[3];



  /* Correction Step */
  /* Kalman Gain 3 */
  denominator_help = (kalman_param->H_vec2f[0]*P_estimate_mat2f[0] + kalman_param->H_vec2f[1]*P_estimate_mat2f[2])*kalman_param->H_vec2f[0];
  denominator_help += (kalman_param->H_vec2f[0]*P_estimate_mat2f[1] + kalman_param->H_vec2f[1]*P_estimate_mat2f[3])*kalman_param->H_vec2f[1];
  denominator_help += kalman_param->R_mat1f;

  K_gain_vec2f[0] = (kalman_param->H_vec2f[0]*P_estimate_mat2f[0] + kalman_param->H_vec2f[1]*P_estimate_mat2f[1])/denominator_help; /* temp_help shall be !=0 */
  K_gain_vec2f[1] = (kalman_param->H_vec2f[0]*P_estimate_mat2f[2] + kalman_param->H_vec2f[1]*P_estimate_mat2f[3])/denominator_help;


  /* Correction Step 4.*/
  /* updated state */
  kalman_param->x_plus_vec2f[0] = x_estimate_vec2f[0] + K_gain_vec2f[0]*(z_plus_0 - x_estimate_vec2f[0]);
  kalman_param->x_plus_vec2f[1] = x_estimate_vec2f[1] + K_gain_vec2f[1]*(z_plus_1 - x_estimate_vec2f[1]);


  /* updated covariance matrix */
  /* Correction Step 5.*/
  kalman_param->P_plus_mat2f[0] = (1.0 - K_gain_vec2f[0]*kalman_param->H_vec2f[0])*P_estimate_mat2f[0] - K_gain_vec2f[0]*kalman_param->H_vec2f[1]*P_estimate_mat2f[2];
  kalman_param->P_plus_mat2f[1] = (1.0 - K_gain_vec2f[0]*kalman_param->H_vec2f[0])*P_estimate_mat2f[1] - K_gain_vec2f[0]*kalman_param->H_vec2f[1]*P_estimate_mat2f[3];
  kalman_param->P_plus_mat2f[2] = -K_gain_vec2f[1]*kalman_param->H_vec2f[0]*P_estimate_mat2f[0] + (1.0 - K_gain_vec2f[1]*kalman_param->H_vec2f[1])*P_estimate_mat2f[2];
  kalman_param->P_plus_mat2f[3] = -K_gain_vec2f[1]*kalman_param->H_vec2f[0]*P_estimate_mat2f[1] + (1.0 - K_gain_vec2f[1]*kalman_param->H_vec2f[1])*P_estimate_mat2f[3];

  //pass the value to our return value
  x_plus_vec2f_return[0] = (kalman_param->x_plus_vec2f[0]);
  x_plus_vec2f_return[1] = (kalman_param->x_plus_vec2f[1]);
  return x_plus_vec2f_return;
}


void KalmanFiltermain( float* posi, float* velo, kalman_filter_param* kalman_param, int n){
  /* loop the position and velocity array*/
  for(int i = 0; i < n; i++)
  {
    position[i] = *(KalmanFilterStep(*(posi+i),*(velo+i), kalman_param)+0);
    velocity[i] = *(KalmanFilterStep(*(posi+i),*(velo+i), kalman_param)+1);
  }

}



float* KalmanFilterStep_ccm(float z_plus_0, float z_plus_1, kalman_filter_param* kalman_param)
{

  /*0x2000000 +1  movs #48*/
  float P_estimate_mat2f[4]; /* matrix 2x2 */
  float x_estimate_vec2f[2]; /* vector 2x1 */
  static float x_plus_vec2f_return[2];
  float K_gain_vec2f[2];  /* matrix 2x1 */
  float denominator_help;/* 0x20000001*/


  /* Prediction Step 1 */
  x_estimate_vec2f[0] = kalman_param->A_mat2f[0]*kalman_param->x_plus_vec2f[0] + kalman_param->A_mat2f[1]*kalman_param->x_plus_vec2f[1];
  x_estimate_vec2f[1] = kalman_param->A_mat2f[2]*kalman_param->x_plus_vec2f[0] + kalman_param->A_mat2f[3]*kalman_param->x_plus_vec2f[1];

  /* Prediction Step 2 */
  P_estimate_mat2f[0] = (kalman_param->A_mat2f[0]*kalman_param->P_plus_mat2f[0] +
               kalman_param->A_mat2f[1]*kalman_param->P_plus_mat2f[2])*kalman_param->A_mat2f[0];

  P_estimate_mat2f[0] += (kalman_param->A_mat2f[0]*kalman_param->P_plus_mat2f[1] +
              kalman_param->A_mat2f[1]*kalman_param->P_plus_mat2f[3])*kalman_param->A_mat2f[1];

  P_estimate_mat2f[0] += kalman_param->Q_mat2f[0];




  P_estimate_mat2f[1] = (kalman_param->A_mat2f[0]*kalman_param->P_plus_mat2f[0] +
              kalman_param->A_mat2f[1]*kalman_param->P_plus_mat2f[2])*kalman_param->A_mat2f[2];

  P_estimate_mat2f[1] += (kalman_param->A_mat2f[0]*kalman_param->P_plus_mat2f[1] +
              kalman_param->A_mat2f[1]*kalman_param->P_plus_mat2f[3])*kalman_param->A_mat2f[3];

  P_estimate_mat2f[1] += kalman_param->Q_mat2f[1];




  P_estimate_mat2f[2] = (kalman_param->A_mat2f[2]*kalman_param->P_plus_mat2f[0] +
              kalman_param->A_mat2f[3]*kalman_param->P_plus_mat2f[2])*kalman_param->A_mat2f[0];

  P_estimate_mat2f[2] += (kalman_param->A_mat2f[2]*kalman_param->P_plus_mat2f[1] +
              kalman_param->A_mat2f[3]*kalman_param->P_plus_mat2f[3])*kalman_param->A_mat2f[1];

  P_estimate_mat2f[2] += kalman_param->Q_mat2f[2];




  P_estimate_mat2f[3] = (kalman_param->A_mat2f[2]*kalman_param->P_plus_mat2f[0] +
              kalman_param->A_mat2f[3]*kalman_param->P_plus_mat2f[2])*kalman_param->A_mat2f[2];

  P_estimate_mat2f[3] += (kalman_param->A_mat2f[2]*kalman_param->P_plus_mat2f[1] +
              kalman_param->A_mat2f[3]*kalman_param->P_plus_mat2f[3])*kalman_param->A_mat2f[3];

  P_estimate_mat2f[3] += kalman_param->Q_mat2f[3];



  /* Correction Step */
  /* Kalman Gain 3 */
  denominator_help = (kalman_param->H_vec2f[0]*P_estimate_mat2f[0] + kalman_param->H_vec2f[1]*P_estimate_mat2f[2])*kalman_param->H_vec2f[0];
  denominator_help += (kalman_param->H_vec2f[0]*P_estimate_mat2f[1] + kalman_param->H_vec2f[1]*P_estimate_mat2f[3])*kalman_param->H_vec2f[1];
  denominator_help += kalman_param->R_mat1f;

  K_gain_vec2f[0] = (kalman_param->H_vec2f[0]*P_estimate_mat2f[0] + kalman_param->H_vec2f[1]*P_estimate_mat2f[1])/denominator_help; /* temp_help shall be !=0 */
  K_gain_vec2f[1] = (kalman_param->H_vec2f[0]*P_estimate_mat2f[2] + kalman_param->H_vec2f[1]*P_estimate_mat2f[3])/denominator_help;


  /* Correction Step 4.*/
  /* updated state */
  kalman_param->x_plus_vec2f[0] = x_estimate_vec2f[0] + K_gain_vec2f[0]*(z_plus_0 - x_estimate_vec2f[0]);
  kalman_param->x_plus_vec2f[1] = x_estimate_vec2f[1] + K_gain_vec2f[1]*(z_plus_1 - x_estimate_vec2f[1]);


  /* updated covariance matrix */
  /* Correction Step 5.*/
  kalman_param->P_plus_mat2f[0] = (1.0 - K_gain_vec2f[0]*kalman_param->H_vec2f[0])*P_estimate_mat2f[0] - K_gain_vec2f[0]*kalman_param->H_vec2f[1]*P_estimate_mat2f[2];
  kalman_param->P_plus_mat2f[1] = (1.0 - K_gain_vec2f[0]*kalman_param->H_vec2f[0])*P_estimate_mat2f[1] - K_gain_vec2f[0]*kalman_param->H_vec2f[1]*P_estimate_mat2f[3];
  kalman_param->P_plus_mat2f[2] = -K_gain_vec2f[1]*kalman_param->H_vec2f[0]*P_estimate_mat2f[0] + (1.0 - K_gain_vec2f[1]*kalman_param->H_vec2f[1])*P_estimate_mat2f[2];
  kalman_param->P_plus_mat2f[3] = -K_gain_vec2f[1]*kalman_param->H_vec2f[0]*P_estimate_mat2f[1] + (1.0 - K_gain_vec2f[1]*kalman_param->H_vec2f[1])*P_estimate_mat2f[3];

  //pass the value to our return value
  x_plus_vec2f_return[0] = (kalman_param->x_plus_vec2f[0]);
  x_plus_vec2f_return[1] = (kalman_param->x_plus_vec2f[1]);
  return x_plus_vec2f_return;
}


void KalmanFiltermain_ccm( float* posi, float* velo, kalman_filter_param* kalman_param, int n){
  /* loop the position and velocity array*/
  for(int i = 0; i < n; i++)
  {
    position[i] = *(KalmanFilterStep_ccm(*(posi+i),*(velo+i), kalman_param)+0);
    velocity[i] = *(KalmanFilterStep_ccm(*(posi+i),*(velo+i), kalman_param)+1);
  }

}


float* KalmanFilterStep_ram(float z_plus_0, float z_plus_1, kalman_filter_param* kalman_param)
{

  /*0x2000000 +1  movs #48*/
  float P_estimate_mat2f[4]; /* matrix 2x2 */
  float x_estimate_vec2f[2]; /* vector 2x1 */
  static float x_plus_vec2f_return[2];
  float K_gain_vec2f[2];  /* matrix 2x1 */
  float denominator_help;/* 0x20000001*/


  /* Prediction Step 1 */
  x_estimate_vec2f[0] = kalman_param->A_mat2f[0]*kalman_param->x_plus_vec2f[0] + kalman_param->A_mat2f[1]*kalman_param->x_plus_vec2f[1];
  x_estimate_vec2f[1] = kalman_param->A_mat2f[2]*kalman_param->x_plus_vec2f[0] + kalman_param->A_mat2f[3]*kalman_param->x_plus_vec2f[1];

  /* Prediction Step 2 */
  P_estimate_mat2f[0] = (kalman_param->A_mat2f[0]*kalman_param->P_plus_mat2f[0] +
               kalman_param->A_mat2f[1]*kalman_param->P_plus_mat2f[2])*kalman_param->A_mat2f[0];

  P_estimate_mat2f[0] += (kalman_param->A_mat2f[0]*kalman_param->P_plus_mat2f[1] +
              kalman_param->A_mat2f[1]*kalman_param->P_plus_mat2f[3])*kalman_param->A_mat2f[1];

  P_estimate_mat2f[0] += kalman_param->Q_mat2f[0];




  P_estimate_mat2f[1] = (kalman_param->A_mat2f[0]*kalman_param->P_plus_mat2f[0] +
              kalman_param->A_mat2f[1]*kalman_param->P_plus_mat2f[2])*kalman_param->A_mat2f[2];

  P_estimate_mat2f[1] += (kalman_param->A_mat2f[0]*kalman_param->P_plus_mat2f[1] +
              kalman_param->A_mat2f[1]*kalman_param->P_plus_mat2f[3])*kalman_param->A_mat2f[3];

  P_estimate_mat2f[1] += kalman_param->Q_mat2f[1];




  P_estimate_mat2f[2] = (kalman_param->A_mat2f[2]*kalman_param->P_plus_mat2f[0] +
              kalman_param->A_mat2f[3]*kalman_param->P_plus_mat2f[2])*kalman_param->A_mat2f[0];

  P_estimate_mat2f[2] += (kalman_param->A_mat2f[2]*kalman_param->P_plus_mat2f[1] +
              kalman_param->A_mat2f[3]*kalman_param->P_plus_mat2f[3])*kalman_param->A_mat2f[1];

  P_estimate_mat2f[2] += kalman_param->Q_mat2f[2];




  P_estimate_mat2f[3] = (kalman_param->A_mat2f[2]*kalman_param->P_plus_mat2f[0] +
              kalman_param->A_mat2f[3]*kalman_param->P_plus_mat2f[2])*kalman_param->A_mat2f[2];

  P_estimate_mat2f[3] += (kalman_param->A_mat2f[2]*kalman_param->P_plus_mat2f[1] +
              kalman_param->A_mat2f[3]*kalman_param->P_plus_mat2f[3])*kalman_param->A_mat2f[3];

  P_estimate_mat2f[3] += kalman_param->Q_mat2f[3];



  /* Correction Step */
  /* Kalman Gain 3 */
  denominator_help = (kalman_param->H_vec2f[0]*P_estimate_mat2f[0] + kalman_param->H_vec2f[1]*P_estimate_mat2f[2])*kalman_param->H_vec2f[0];
  denominator_help += (kalman_param->H_vec2f[0]*P_estimate_mat2f[1] + kalman_param->H_vec2f[1]*P_estimate_mat2f[3])*kalman_param->H_vec2f[1];
  denominator_help += kalman_param->R_mat1f;

  K_gain_vec2f[0] = (kalman_param->H_vec2f[0]*P_estimate_mat2f[0] + kalman_param->H_vec2f[1]*P_estimate_mat2f[1])/denominator_help; /* temp_help shall be !=0 */
  K_gain_vec2f[1] = (kalman_param->H_vec2f[0]*P_estimate_mat2f[2] + kalman_param->H_vec2f[1]*P_estimate_mat2f[3])/denominator_help;


  /* Correction Step 4.*/
  /* updated state */
  kalman_param->x_plus_vec2f[0] = x_estimate_vec2f[0] + K_gain_vec2f[0]*(z_plus_0 - x_estimate_vec2f[0]);
  kalman_param->x_plus_vec2f[1] = x_estimate_vec2f[1] + K_gain_vec2f[1]*(z_plus_1 - x_estimate_vec2f[1]);


  /* updated covariance matrix */
  /* Correction Step 5.*/
  kalman_param->P_plus_mat2f[0] = (1.0 - K_gain_vec2f[0]*kalman_param->H_vec2f[0])*P_estimate_mat2f[0] - K_gain_vec2f[0]*kalman_param->H_vec2f[1]*P_estimate_mat2f[2];
  kalman_param->P_plus_mat2f[1] = (1.0 - K_gain_vec2f[0]*kalman_param->H_vec2f[0])*P_estimate_mat2f[1] - K_gain_vec2f[0]*kalman_param->H_vec2f[1]*P_estimate_mat2f[3];
  kalman_param->P_plus_mat2f[2] = -K_gain_vec2f[1]*kalman_param->H_vec2f[0]*P_estimate_mat2f[0] + (1.0 - K_gain_vec2f[1]*kalman_param->H_vec2f[1])*P_estimate_mat2f[2];
  kalman_param->P_plus_mat2f[3] = -K_gain_vec2f[1]*kalman_param->H_vec2f[0]*P_estimate_mat2f[1] + (1.0 - K_gain_vec2f[1]*kalman_param->H_vec2f[1])*P_estimate_mat2f[3];

  //pass the value to our return value
  x_plus_vec2f_return[0] = (kalman_param->x_plus_vec2f[0]);
  x_plus_vec2f_return[1] = (kalman_param->x_plus_vec2f[1]);
  return x_plus_vec2f_return;
}


void KalmanFiltermain_ram( float* posi, float* velo, kalman_filter_param* kalman_param, int n){
  /* loop the position and velocity array*/
  for(int i = 0; i < n; i++)
  {
    position[i] = *(KalmanFilterStep_ram(*(posi+i),*(velo+i), kalman_param)+0);
    velocity[i] = *(KalmanFilterStep_ram(*(posi+i),*(velo+i), kalman_param)+1);
  }

}




void kal_main()
{
  KalmanFiltermain( &position[0], &velocity[0], &kalman_parameters, n);
}

void kal_main_ccm()
{
  KalmanFiltermain_ccm( &position[0], &velocity[0], &kalman_parameters, n);
}

void kal_main_ram()
{
  KalmanFiltermain_ram( &position[0], &velocity[0], &kalman_parameters, n);
}

