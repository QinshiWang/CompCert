#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static const double J2000     = 2451545.0;
static const int TEST_LENGTH  = 36525;

const double amas [8] = { 6023600.0, 408523.5, 328900.5, 3098710.0, 1047.355, 3498.5, 22869.0, 19314.0 };

const double a [8][3] =
    { {   0.3870983098,             0,        0 },
      {   0.7233298200,             0,        0 },
      {   1.0000010178,             0,        0 },
      {   1.5236793419,         3e-10,        0 },
      {   5.2026032092,     19132e-10,  -39e-10 },
      {   9.5549091915, -0.0000213896,  444e-10 },
      {  19.2184460618,     -3716e-10,  979e-10 },
      {  30.1103868694,    -16635e-10,  686e-10 } };
       
const double dlm[8][3] = 
    { { 252.25090552, 5381016286.88982,  -1.92789 },
      { 181.97980085, 2106641364.33548,   0.59381 },
      { 100.46645683, 1295977422.83429,  -2.04411 },
      { 355.43299958,  689050774.93988,   0.94264 },
      {  34.35151874,  109256603.77991, -30.60378 },
      {  50.07744430,   43996098.55732,  75.61614 },
      { 314.05500511,   15424811.93933,  -1.75083 },
      { 304.34866548,    7865503.20744,   0.21103 } };

const double e[8][3] =
    { {   0.2056317526,  0.0002040653,    -28349e-10 },
      {   0.0067719164, -0.0004776521,     98127e-10 },
      {   0.0167086342, -0.0004203654, -0.0000126734 },
      {   0.0934006477,  0.0009048438,    -80641e-10 },
      {   0.0484979255,  0.0016322542, -0.0000471366 },
      {   0.0555481426, -0.0034664062, -0.0000643639 },
      {   0.0463812221, -0.0002729293,  0.0000078913 },
      {   0.0094557470,  0.0000603263,            0  } };

const double pi[8][3] =
    { {  77.45611904,  5719.11590,   -4.83016 },
      { 131.56370300,   175.48640, -498.48184 },
      { 102.93734808, 11612.35290,   53.27577 },
      { 336.06023395, 15980.45908,  -62.32800 },
      {  14.33120687,  7758.75163,  259.95938 },
      {  93.05723748, 20395.49439,  190.25952 },
      { 173.00529106,  3215.56238,  -34.09288 },
      {  48.12027554,  1050.71912,   27.39717 } };

const double dinc[8][3] =
    { {   7.00498625, -214.25629,   0.28977 },
      {   3.39466189,  -30.84437, -11.67836 },
      {            0,  469.97289,  -3.35053 },
      {   1.84972648, -293.31722,  -8.11830 },
      {   1.30326698,  -71.55890,  11.95297 },
      {   2.48887878,   91.85195, -17.66225 },
      {   0.77319689,  -60.72723,   1.25759 },
      {   1.76995259,    8.12333,   0.08135 } };

const double omega[8][3] =
    { {  48.33089304,  -4515.21727,  -31.79892 },
      {  76.67992019, -10008.48154,  -51.32614 },
      { 174.87317577,  -8679.27034,   15.34191 },
      {  49.55809321, -10620.90088, -230.57416 },
      { 100.46440702,   6362.03561,  326.52178 },
      { 113.66550252,  -9240.19942,  -66.23743 },
      {  74.00595701,   2669.15033,  145.93964 },
      { 131.78405702,   -221.94322,   -0.78728 } };

const double kp[8][9] =
    { { 69613.0,  75645.0, 88306.0, 59899.0, 15746.0, 71087.0, 142173.0,  3086.0,    0.0 },
      { 21863.0,  32794.0, 26934.0, 10931.0, 26250.0, 43725.0,  53867.0, 28939.0,    0.0 },
      { 16002.0,  21863.0, 32004.0, 10931.0, 14529.0, 16368.0,  15318.0, 32794.0,    0.0 },
      {  6345.0,   7818.0, 15636.0,  7077.0,  8184.0, 14163.0,   1107.0,  4872.0,    0.0 },
      {  1760.0,   1454.0,  1167.0,   880.0,   287.0,  2640.0,     19.0,  2047.0, 1454.0 },
      {   574.0,      0.0,   880.0,   287.0,    19.0,  1760.0,   1167.0,   306.0,  574.0 },
      {   204.0,      0.0,   177.0,  1265.0,     4.0,   385.0,    200.0,   208.0,  204.0 },
      {     0.0,    102.0,   106.0,     4.0,    98.0,  1367.0,    487.0,   204.0,    0.0 } };

const double ca[8][9] =
    { {       4.0,    -13.0,    11.0,    -9.0,    -9.0,    -3.0,    -1.0,     4.0,    0.0 },
      {    -156.0,     59.0,   -42.0,     6.0,    19.0,   -20.0,   -10.0,   -12.0,    0.0 },
      {      64.0,   -152.0,    62.0,    -8.0,    32.0,   -41.0,    19.0,   -11.0,    0.0 },
      {     124.0,    621.0,  -145.0,   208.0,    54.0,   -57.0,    30.0,    15.0,    0.0 },
      {  -23437.0,  -2634.0,  6601.0,  6259.0, -1507.0, -1821.0,  2620.0, -2115.0,-1489.0 },
      {   62911.0,-119919.0, 79336.0, 17814.0,-24241.0, 12068.0,  8306.0, -4893.0, 8902.0 },
      {  389061.0,-262125.0,-44088.0,  8387.0,-22976.0, -2093.0,  -615.0, -9720.0, 6633.0 },
      { -412235.0,-157046.0,-31430.0, 37817.0, -9740.0,   -13.0, -7449.0,  9644.0,    0.0 } };

const double sa[8][9] =
    { {     -29.0,    -1.0,     9.0,     6.0,    -6.0,     5.0,     4.0,     0.0,    0.0 },
      {     -48.0,  -125.0,   -26.0,   -37.0,    18.0,   -13.0,   -20.0,    -2.0,    0.0 },
      {    -150.0,   -46.0,    68.0,    54.0,    14.0,    24.0,   -28.0,    22.0,    0.0 },
      {    -621.0,   532.0,  -694.0,   -20.0,   192.0,   -94.0,    71.0,   -73.0,    0.0 },
      {  -14614.0,-19828.0, -5869.0,  1881.0, -4372.0, -2255.0,   782.0,   930.0,  913.0 },
      {  139737.0,     0.0, 24667.0, 51123.0, -5102.0,  7429.0, -4095.0, -1976.0,-9566.0 },
      { -138081.0,     0.0, 37205.0,-49039.0,-41901.0,-33872.0,-27037.0,-12474.0,18797.0 },
      {       0.0, 28492.0,133236.0, 69654.0, 52322.0,-49577.0,-26430.0, -3593.0,    0.0 } };

const double kq[8][10] =
    { {  3086.0, 15746.0, 69613.0, 59899.0, 75645.0, 88306.0, 12661.0, 2658.0,  0.0,   0.0 },
      { 21863.0, 32794.0, 10931.0,    73.0,  4387.0, 26934.0,  1473.0, 2157.0,  0.0,   0.0 },
      {    10.0, 16002.0, 21863.0, 10931.0,  1473.0, 32004.0,  4387.0,   73.0,  0.0,   0.0 },
      {    10.0,  6345.0,  7818.0,  1107.0, 15636.0,  7077.0,  8184.0,  532.0, 10.0,   0.0 },
      {    19.0,  1760.0,  1454.0,   287.0,  1167.0,   880.0,   574.0, 2640.0, 19.0,1454.0 },
      {    19.0,   574.0,   287.0,   306.0,  1760.0,    12.0,    31.0,   38.0, 19.0, 574.0 },
      {     4.0,   204.0,   177.0,     8.0,    31.0,   200.0,  1265.0,  102.0,  4.0, 204.0 },
      {     4.0,   102.0,   106.0,     8.0,    98.0,  1367.0,   487.0,  204.0,  4.0, 102.0 } };

const double cl[8][10] =
    { {      21.0,   -95.0, -157.0,   41.0,   -5.0,   42.0,   23.0,   30.0,     0.0,    0.0 },
      {    -160.0,  -313.0, -235.0,   60.0,  -74.0,  -76.0,  -27.0,   34.0,     0.0,    0.0 },
      {    -325.0,  -322.0,  -79.0,  232.0,  -52.0,   97.0,   55.0,  -41.0,     0.0,    0.0 },
      {    2268.0,  -979.0,  802.0,  602.0, -668.0,  -33.0,  345.0,  201.0,   -55.0,    0.0 },
      {    7610.0, -4997.0,-7689.0,-5841.0,-2617.0, 1115.0, -748.0, -607.0,  6074.0,  354.0 },
      {  -18549.0, 30125.0,20012.0, -730.0,  824.0,   23.0, 1289.0, -352.0,-14767.0,-2062.0 },
      { -135245.0,-14594.0, 4197.0,-4030.0,-5630.0,-2898.0, 2540.0, -306.0,  2939.0, 1986.0 },
      {   89948.0,  2103.0, 8963.0, 2695.0, 3682.0, 1648.0,  866.0, -154.0, -1963.0, -283.0 } };

const double sl[8][10] =
    { {   -342.0,   136.0,  -23.0,   62.0,   66.0,  -52.0,  -33.0,   17.0,     0.0,    0.0 },
      {    524.0,  -149.0,  -35.0,  117.0,  151.0,  122.0,  -71.0,  -62.0,     0.0,    0.0 },
      {   -105.0,  -137.0,  258.0,   35.0, -116.0,  -88.0, -112.0,  -80.0,     0.0,    0.0 },
      {    854.0,  -205.0, -936.0, -240.0,  140.0, -341.0,  -97.0, -232.0,   536.0,    0.0 },
      { -56980.0,  8016.0, 1012.0, 1448.0,-3024.0,-3710.0,  318.0,  503.0,  3767.0,  577.0 },
      { 138606.0,-13478.0,-4964.0, 1441.0,-1319.0,-1482.0,  427.0, 1236.0, -9167.0,-1918.0 },
      {  71234.0,-41116.0, 5334.0,-4935.0,-1848.0,   66.0,  434.0,-1748.0,  3780.0, -701.0 },
      { -47645.0, 11647.0, 2166.0, 3194.0,  679.0,    0.0, -244.0, -419.0, -2531.0,   48.0 } };

extern void planetpv (double epoch[2], int np, double pv[2][3]);
extern void radecdist(double state[2][3], double rdd[3]);

static void test(void)
{
    int p;
    double jd[2];
    double pv[2][3];
    double position[3];
    
    jd[0] = J2000;
    jd[1] = 0.0;
    for (p = 0; p < 8; ++p)
      {
        planetpv(jd,p,pv);
        radecdist(pv,position);
        printf("p = %d  position[0] = %g  position[1] = %g\n",
               p, position[0], position[1]);
      }
}


static void bench(int nloops)
{
    int i, n, p;
    double jd[2];
    double pv[2][3];
    double position[3];
    
    for (i = 0; i < nloops; ++i)
    {
        jd[0] = J2000;
        jd[1] = 0.0;

        for (n = 0; n < TEST_LENGTH; ++n)
        {
            jd[0] += 1.0;
            
            for (p = 0; p < 8; ++p)
            {
                planetpv(jd,p,pv);
                radecdist(pv,position);
            }
        }
    }
}

int main(int argc, char ** argv)
{
  if (argc >= 2)
    bench(atoi(argv[1]));
  else
    test();
  return 0;
}
