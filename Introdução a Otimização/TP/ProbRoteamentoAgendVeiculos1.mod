#CONJUNTOS E PARAMETROS

param p, integer, > 0;/*numero de n�s de oferta*/
set P := {1,2,3};/* conjunto dos n�s oferta*/
param d, integer, > 0;/*numero de n�s de demanda*/
set D := {4,5,6};/*conjunto de n�s de demanda*/
param n, integer, > 0;/* numero de n�s */
set N := {1..8};/*conjunto  total de n�s*/
param k, integer, > 0;/*numero de caminh�es*/
set K := {1..k};/*conjunto de caminh�es*/
param re, integer, > 0;
set R := {7};
param se, integer, > 0;
set S := {8};
param n1, integer, >0;

param b{i in N};/* oferta/demanda do n� */
param M := 99999;/*Constante suficientemente grande*/
param c{i in N,j in N};/*custo nos arcos */
param t{i in N,j in N};/*custo de transporta��o entre os n�s i e j*/
param dem{i in D union P};/*demanda do n� i*/
param a{i in N}; /*limite inferior do tempo */
param bb{i in N}; /*limite superior do tempo */
param T;/*capacidade do caminh�o*/
param F;/*tempo fixo de prepara��o dos caminh�es para o processo de carregamento/descarregamento no cross-dock*/
param V;/*tempo vari�vel para descarregar/recarregar cada unidade de produto*/


#VARI�VEIS BIN�RIAS

var x{i in N, j in N, k1 in K}, binary;/*1 se o veiculo k viaja do n� i ao j, 0 caso contrario*/
var u{i in P,k1 in K}, binary;/*1 se o veiculo k descarregar a demanda i no cross-dock, 0 cc*/
var r{i in P, k1 in K}, binary;/*1 se o veiculo k  recarregar a demanda i no cross-dock, 0 cc*/
var q{k1 in K}, binary;/*1 se o veiculo k parou no cross-dock para o processo de descarga, 0 cc*/
var q2{k1 in K}, binary;/*1 se o veiculo k parou no cross-dock para o processo de recarga, 0 cc*/

#VARI�VEIS CONT�NUAS

var l{i in N,k1 in K};/*tempo de saido do caminhao k para o n� i*/
var f{k1 in K};/*tempo final da opera��o de descarga do caminh�o k no cross-dock*/
var s{k1 in K};/*hora de in�cio da opera��o de recarga do caminh�o k no cross -dock*/
var g{i in P};/*tempo final da opera��o de descarga do pedido i no cross-dock*/

#FUN��O OBJETIVO

minimize Z: sum{i in N,j in N, k1 in K} (c[i,j] * x[i,j,k]);

#RESTRI��ES

s.t. r1 {i in P}: sum{j in P, k1 in K : i!=j} x[i,j,k] = 1;/*assegura que um caminh�o viaje entre os n�s de oferta sem repetir um n�*/
s.t. r2 {i in D}: sum{j in D, k1 in K : i!=j} x[i,j,k] = 1;/*assegura que um caminh�o viaje entre os n�s de demanda sem repetir um n�*/
s.t. r3 {k1 in K}: sum{j in P, ree in R} x[ree,j,k] = 1;/*assegura que cada caminh�o entrante deve come�ar a partir do cross-dock*/
s.t. r4 {k1 in K}: sum{j in D, see in S} x[see,j,k] = 1;/*assegura que cada caminh�o de saida deve come�ar a partir do cross-dock*/
s.t. r5 {k1 in K}: sum{i in P, ree in R} x[i,ree,k] = 1;/*assegura que os ve�culos retornem ao cross-dock no final de suas viagens*/
s.t. r6 {k1 in K}: sum{i in D, see in S} x[i,see,k] = 1;/*Idem*/
s.t. r7 {k1 in K}: sum{i in P, j in P : i!=j} (dem[i] * x[i,j,k]) <= T;/*assegura que o volume total de produtos transportados por caminhos de entrada/sa�da n�o exceder� a capacidade*/
s.t. r8 {k1 in K}: sum{i in D, j in D : i!=j} (dem[i]*x[i,j,k]) <= T;/*Idem*/
s.t. r9 {h in P, k1 in K}: sum{i in P, j in P : i!=j} x[i,h,k] = sum{i in P, j in P: i!=j} x[h,j,k];/*para cada n� se um caminh�o viajar do n� i para o n� j deve deixar o n� j para os passeios de recolha e de entrega*/
s.t. r10 {h in D, k1 in K}: sum{i in D, j in D : i!=j} x[i,h,k] = sum{i in D, j in D} x[h,j,k];/*Idem*/
s.t. r11 {i in N, j in N, k1 in K : i!=j} : l[j,k] >= (l[i,k] + t[i,j] - M*(1-x[i,j,k]));/*determinar o tempo de viagem entre dois n�s se eles forem percorridos consecutivamente pelo mesmo caminh�o*/
s.t. r12 {i in N, j in N, k1 in K : i!=j} : l[j,k] <= M*x[i,j,k];/*Idem*/
s.t. r13 {i in N, k1 in K} : a[i] <= l[i,k];/*Implica que os caminh�es devem visitar os n�s dentro da janela de tempo*/
s.t. r14 {i in N, k1 in K} : l[i,k] <= bb[i];/*Idem*/
s.t. r15 {i in P, k1 in K} : u[i,k] - r[i,k] = sum{j in P union R}x[i,j,k] - sum{j in D union S, n2 in P}x[(i+n1),j,k];
s.t. r16 {i in P, k1 in K} : u[i,k] + r[i,k] = 1;
s.t. r17 {k1 in K} : (1 / M)*(sum{i in P} u[i,k]) <= q[k];
s.t. r18 {k1 in K} : q[k] <= sum{i in P} u[i,k];
s.t. r19 {k1 in K} : f[k] = l[re,k] + F*q[k] + V*sum{i in P} dem[i]*u[i,k];
s.t. r20 {k1 in K} : s[k] >= f[k];
s.t. r21 {i in P, k1 in K} : s[k] >= g[i] - M*(1 - r[i,k]);
s.t. r22 {i in P, k1 in K} : g[i] >= f[k] - M*(1 - u[i,k]);
s.t. r23 {k1 in K} : (1/M)*sum{i in P} r[i,k] <= q2[k];
s.t. r24 {k1 in K} : q2[k] <= sum{i in P} r[i,k];
s.t. r25 {k1 in K} : l[se,k] = s[k] + F*q2[k] + V*sum{i in P} dem[i]*r[i,k];

solve;

printf "Custo total: %4.2f\n\n", Z;

data;

param T := 15;
param F := 1;
param p := 3;
param d := 3;
param n := 6;
param n1 := 3;
param k := 2;
param V := 1;
param re := 1;
param se := 1;
param a := 
    1 2
    2 2
    3 3
    4 3
    5 5
    6 1
    7 2
    8 2;
param bb:= 
    1 10
    2 10
    3 10
    4 10
    5 10
    6 10
    7 10
    8 10;
param dem:=
    1 3
    
    2 3
    3 3
    4 1
    5 2
    6 3;

param c:
            1   2   3   4   5   6   7   8:=
        1   0   12  999 999 999 999 9   999
        2   12  0   15  999 999 999 2   999
        3   999 5   0   999 999 999 8   999
        4   999 999 999 0   11  999 999 13
        5   999 999 999 6   0   12  999 5
        6   999 999 999 999 15  0   999 7
        7   8   7   6   999 999 999 0   0
        8   999 999 999 6   7   8   0   0;
        
param t:
            1   2   3   4   5   6   7   8:=
        1   0   12  999 999 999 999 9   999
        2   12  0   15  999 999 999 2   999
        3   999 5   0   999 999 999 8   999
        4   999 999 999 0   11  999 999 13
        5   999 999 999 6   0   12  999 5
        6   999 999 999 999 15  0   999 7
        7   8   7   6   999 999 999 0   0
        8   999 999 999 6   7   8   0   0;
end;
