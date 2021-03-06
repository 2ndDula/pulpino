// Copyright 2017 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.
/////////////////////////////////////////////////////////
// includes
/////////////////////////////////////////////////////////
#include "mlHom.h"
#include "math_fns.h"
#include "bar.h"
#include "utils.h"
#include "bench.h"

/////////////////////////////////////////////////////////
// shared globals
/////////////////////////////////////////////////////////

  __attribute__ ((section(".heapsram"))) static const float fv1[400] = { 3.72083259F, 4.24274635F, 7.43126869F,
    3.60080481F, 6.26489258F, 8.52869701F, 1.20024753F, 1.74342656F, 9.50627804F,
    9.77501488F, 2.52004886F, 2.84620476F, 8.38286304F, 8.02100754F, 3.69961333F,
    3.62810969F, 2.71741271F, 2.59469318F, 9.94394398F, 0.462633222F,
    6.76333141F, 5.01684666F, 1.13288009F, 4.61314678F, 7.18630505F, 9.6060276F,
    5.28900099F, 9.35416698F, 9.89586926F, 4.65715885F, 3.63796473F,
    0.903358579F, 8.44203758F, 4.13706064F, 7.57358456F, 5.54033375F,
    4.76240253F, 2.66590452F, 1.35277474F, 0.777007818F, 8.46593475F,
    3.37042975F, 6.73993826F, 1.0443275F, 5.87365866F, 1.14802921F, 2.4934535F,
    4.14172697F, 7.15466738F, 8.69670582F, 8.15427876F, 2.32449222F, 3.4633522F,
    9.60612392F, 3.01312804F, 1.54196274F, 7.44436502F, 2.82894826F, 3.28839445F,
    0.0133189932F, 5.63913488F, 4.44133663F, 1.6136297F, 7.03462076F,
    5.44031096F, 2.54619718F, 3.93110847F, 2.44619083F, 5.82689F, 0.527434707F,
    6.02292681F, 0.399708092F, 8.62410164F, 3.4310987F, 1.12233472F, 5.93426561F,
    6.30076742F, 7.81380415F, 7.36514139F, 7.91597128F, 6.48711348F, 9.1190834F,
    6.06076097F, 7.3644557F, 7.13251543F, 6.89987183F, 9.198699F, 9.69545937F,
    3.28926063F, 0.94815737F, 8.06532764F, 6.82734823F, 1.7324698F, 4.8100996F,
    9.39338493F, 1.38072348F, 6.5965395F, 1.94039249F, 6.26483965F, 6.20735073F,
    9.93604469F, 7.28353786F, 5.05822754F, 0.489289761F, 1.08218634F,
    8.58296299F, 9.15944481F, 6.71659851F, 4.62335587F, 9.61389732F,
    0.799172401F, 3.85913467F, 0.164362103F, 5.91907167F, 5.68236303F,
    0.122706905F, 5.89805317F, 3.60216522F, 0.254346699F, 9.78579807F,
    1.32194078F, 5.50576544F, 8.63438129F, 6.82540703F, 0.349691957F,
    4.40197897F, 4.39827108F, 7.66111708F, 9.99839306F, 2.57465982F, 8.85814285F,
    0.497215718F, 3.31655765F, 7.29553699F, 4.98701763F, 5.46659613F,
    2.24639368F, 1.22980666F, 4.85212F, 8.7404232F, 6.41425228F, 4.48237276F,
    1.37143755F, 1.4115926F, 9.82595825F, 9.71884251F, 4.28892565F, 7.56038523F,
    5.58590651F, 7.56654406F, 9.75920105F, 0.418740481F, 3.51003504F,
    4.76647949F, 1.74935329F, 3.55904555F, 8.88469505F, 0.691530466F,
    0.92747432F, 2.05804181F, 6.15199F, 2.7343204F, 7.47785378F, 3.05726337F,
    7.65444374F, 2.52885723F, 6.71016F, 1.31914103F, 9.42448425F, 4.44583178F,
    3.57995343F, 1.69800961F, 4.99074078F, 4.52166224F, 0.662159801F, 8.8788166F,
    9.07784081F, 7.82654333F, 4.71943569F, 7.96142292F, 8.75647354F, 6.72251558F,
    0.703827381F, 1.24471903F, 4.25366163F, 7.82665777F, 5.89146566F,
    4.72135925F, 0.337884724F, 1.80073535F, 9.3181963F, 5.90764F, 5.06335497F,
    2.18438864F, 9.52051067F, 3.62259507F, 4.58546734F, 8.30810165F, 7.90665F,
    4.4102273F, 2.8395412F, 0.742080033F, 1.11397183F, 0.753069341F, 9.96192074F,
    5.99597692F, 7.88968F, 8.61268616F, 8.27068233F, 9.36923695F, 0.358534604F,
    1.39710784F, 7.25442076F, 8.72094154F, 3.7410326F, 2.16187525F, 5.76010084F,
    0.256467551F, 0.435049236F, 9.33449268F, 4.01651907F, 7.84920788F,
    2.42628574F, 6.08542728F, 8.93183899F, 6.29419851F, 9.24146843F, 9.95804596F,
    1.50089872F, 0.247969F, 9.11264133F, 1.47997463F, 0.899430573F, 7.15693617F,
    1.75014412F, 1.59721589F, 4.78932142F, 9.48731613F, 7.41070127F, 6.72333479F,
    0.703452468F, 3.06105494F, 9.36833096F, 8.56937F, 8.90847397F, 5.88586903F,
    1.62586331F, 1.7604512F, 7.47563601F, 9.45285797F, 6.57979774F, 5.43831968F,
    5.97653103F, 2.3460288F, 8.19767761F, 7.88495541F, 5.89059591F, 4.36259794F,
    5.49739408F, 3.52968717F, 9.95791149F, 3.64963603F, 9.66174507F,
    0.247408733F, 7.77839136F, 4.40182114F, 6.30499935F, 3.14024687F, 9.218153F,
    2.23324609F, 3.74486279F, 3.08144379F, 0.37822473F, 6.05169678F, 8.35864353F,
    5.88252211F, 3.63454795F, 1.39885187F, 1.1653372F, 9.8121748F, 5.41692352F,
    0.865099072F, 2.5609622F, 2.09775019F, 3.14609814F, 9.03751564F, 5.20696306F,
    1.62236011F, 1.43612206F, 0.640530765F, 8.54645443F, 9.74456787F,
    9.29025078F, 4.09520245F, 9.01611233F, 4.84497213F, 4.69673824F, 1.67828202F,
    0.828584731F, 6.33161259F, 6.8871727F, 2.46007228F, 2.66084862F, 1.32070827F,
    3.44210339F, 7.5439F, 8.89238644F, 7.10436392F, 2.46475029F, 4.5138936F,
    9.31224251F, 6.15667582F, 2.58289981F, 6.31103182F, 6.95532179F, 4.03659868F,
    1.93481863F, 3.07074213F, 6.92954493F, 6.30359554F, 2.49824F, 0.434220165F,
    5.31451464F, 1.76201451F, 5.21902037F, 8.71282101F, 6.13612843F, 2.71432114F,
    8.54539585F, 1.57460141F, 2.59418631F, 6.70580482F, 2.25957394F, 8.25966549F,
    3.24096274F, 4.88386583F, 7.63723755F, 7.37675524F, 6.36025953F, 2.4914093F,
    7.34316826F, 3.39505148F, 3.02767849F, 1.27141988F, 0.101402991F,
    9.24928761F, 9.10006237F, 3.82147908F, 7.01392078F, 6.72341919F, 1.27674127F,
    2.00969028F, 9.028265F, 8.91836262F, 3.77681732F, 2.50192904F, 6.02701473F,
    6.25450563F, 0.196828902F, 8.19732571F, 5.17944574F, 9.09434223F,
    1.18624973F, 9.46149063F, 9.27044773F, 0.948050141F, 4.15257406F,
    3.22862315F, 8.46253586F, 9.47950363F, 7.29220581F, 6.83849716F, 6.41411924F,
    3.15882611F, 7.32146788F, 1.57648408F, 7.60070705F, 0.919099033F, 9.67654F,
    6.08966351F, 8.94952488F, 1.94146526F, 9.88057899F, 2.41314864F, 2.23420954F,
    4.01997948F, 7.80906343F, 8.39212F, 4.09499788F, 4.02400541F, 7.7175F,
    2.49124694F, 8.65741062F, 6.82186079F, 9.77393F, 1.85523903F, 2.16182756F,
    3.12921858F, 7.52012F, 3.67736602F };

  __attribute__ ((section(".heapsram"))) static const float fv2[36] = { 3.51056075F, 4.4100275F, 3.29407024F,
    5.72097254F, 9.92353249F, 7.17850828F, 3.60995555F, 5.72728539F, 3.80334616F,
    4.40977192F, 6.58947325F, 4.47152233F, 8.51604366F, 7.07325172F, 4.28546095F,
    6.20197F, 6.41192293F, 8.87750149F, 6.24033785F, 9.55508232F, 6.63478661F,
    2.66490936F, 7.23154831F, 5.61077881F, 9.7298069F, 3.00872636F, 4.97020483F,
    3.10978913F, 4.66354036F, 2.11069417F, 0.014457196F, 7.97611284F,
    3.68047428F, 0.151375726F, 7.14978456F, 2.18578768F };


  __attribute__ ((section(".heapsram"))) static const float fv3[32] = { 45.6040497F, 45.6031342F, 68.8497696F, 68.8484F,
    0.00281180278F, 0.00281174644F, 6.72560127E-5F, 6.72546739E-5F, 65.7280731F,
    65.7267609F, 69.6350555F, 69.633667F, 0.0401070118F, 0.0401062071F,
    0.00692975521F, 0.00692961644F, 43.2343674F, 43.2335052F, 64.8624954F,
    64.8612F, 0.017073391F, 0.0170730483F, 0.00403644936F, 0.00403636834F,
    29.7216339F, 29.7210388F, 113.690094F, 113.68782F, 0.0774217844F,
    0.0774202347F, 0.00209318195F, 0.00209314F };


/////////////////////////////////////////////////////////
// subfunctions
/////////////////////////////////////////////////////////

/*
 * Arguments    : const float x[50]
 * Return Type  : float
 */
float var(const float x[50])
{
  float y;
  int ix;
  float xbar;
  int k;
  float r;
  ix = 0;
  xbar = x[0];
  for (k = 0; k < 49; k++) {
    ix++;
    xbar += x[ix];
  }

  xbar *= 1.0F/50.0F;
  ix = 0;
  r = x[0] - xbar;
  y = r * r;
  for (k = 0; k < 49; k++) {
    ix++;
    r = x[ix] - xbar;
    y += r * r;
}

  y *= 1.0F/49.0F;
  return y;
}

/////////////////////////////////////////////////////////
// main testing function 
/////////////////////////////////////////////////////////
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  int it;


  boolean_T pass, flag;
  int coreid;
  float fv0[150];
  int jcol;
  int ibmat;
  
  float tmp[150];
  int itilerow;
  
  float scale[50];
  float y[100];
  float b_y;
  float c_y;
  float d_y[50];
  float e_y[50];
  float b_tmp[4];
  float golden[8];


  /////////////////////////////////////////////////////////
  // main test loop 
  // each core loops over a kernel instance
  /////////////////////////////////////////////////////////
  
  coreid = get_core_id();

  printf("starting %d kernel iterations... (coreid = %d)\n",KERNEL_ITS,coreid);

  if (coreid>3)
    coreid=coreid-4;

  synch_barrier();

  perf_begin();

  for(it = 0; it < KERNEL_ITS; it++)
  {

    /*  mlHom */
    for (jcol = 0; jcol < 50; jcol++) {
      for (ibmat = 0; ibmat < 2; ibmat++) {
        fv0[ibmat + 3 * jcol] = fv1[(ibmat + (jcol << 1)) + 100 * coreid];
      }

      fv0[2 + 3 * jcol] = 1.0F;
    }

    for (jcol = 0; jcol < 3; jcol++) {
      for (ibmat = 0; ibmat < 50; ibmat++) {
        tmp[jcol + 3 * ibmat] = 0.0F;
        for (itilerow = 0; itilerow < 3; itilerow++) {
          tmp[jcol + 3 * ibmat] += fv2[(jcol + 3 * itilerow) + 9 * coreid] *
            fv0[itilerow + 3 * ibmat];
        }
      }
    }

    for (jcol = 0; jcol < 50; jcol++) {
      scale[jcol] = fDiv(1.0F, tmp[2 + 3 * jcol]);
    }

    for (jcol = 0; jcol < 50; jcol++) {
      ibmat = jcol << 1;
      for (itilerow = 0; itilerow < 2; itilerow++) {
        y[ibmat + itilerow] = scale[jcol];
      }
    }

    for (jcol = 0; jcol < 50; jcol++) {
      for (ibmat = 0; ibmat < 2; ibmat++) {
        y[ibmat + (jcol << 1)] *= tmp[ibmat + 3 * jcol];
      }
    }

    b_y = y[0];
    c_y = y[1];
    for (jcol = 0; jcol < 49; jcol++) {
      b_y += y[(jcol + 1) << 1];
      c_y += y[1 + ((jcol + 1) << 1)];
    }

    for (jcol = 0; jcol < 50; jcol++) {
      d_y[jcol] = y[jcol << 1];
      e_y[jcol] = y[1 + (jcol << 1)];
    }

  }  

  synch_barrier();
  
  perf_end();

  /////////////////////////////////////////////////////////
  // check results
  /////////////////////////////////////////////////////////

  b_tmp[0] = b_y;
  b_tmp[1] = c_y;
  b_tmp[2] = var(d_y);
  b_tmp[3] = var(e_y);
  pass = true;
  for (jcol = 0; jcol < 4; jcol++) {
    for (ibmat = 0; ibmat < 2; ibmat++) {
      golden[ibmat + (jcol << 1)] = fv3[(ibmat + (jcol << 1)) + (coreid << 3)];
    }
    flag = true;
    flag = flag && (b_tmp[jcol] <= golden[jcol << 1]);
    flag = flag && (b_tmp[jcol] >= golden[1 + (jcol << 1)]);
    printErrors(!pass, jcol, b_tmp[jcol] ,golden[jcol << 1] ,golden[1 + (jcol << 1)]);
    pass = flag && pass;
  }
  flagPassFail(pass, get_core_id());

  synch_barrier();

/////////////////////////////////////////////////////////
// synchronize and exit
/////////////////////////////////////////////////////////

  return !pass;
}

