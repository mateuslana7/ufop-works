#CONJUNTOS E PARAMETROS

param p, integer, > 0;/*numero de n�s de oferta*/
set P := {1..p};/* conjunto dos n�s oferta*/
param d, integer, > 0;/*numero de n�s de demanda*/
set D := {1..d};/*conjunto de n�s de demanda*/
param n, integer, > 0;/* numero de n�s */
set N := {1..n};/*conjunto  total de n�s*/
param k, integer, > 0;/*numero de caminh�es*/
set K := {1..k};/*conjunto de caminh�es*/
set A, within N cross N; /*conjunto de arcos*/

param b{i in N};/* oferta/demanda do n� */
param M := 99999;/*Constante suficientemente grande*/
param c{(i,j) in A};/*custo nos arcos */
param t{(i,j) in A};/*custo de transporta��o entre os n�s i e j*/
param dem{i in D};/*demanda do n� i*/
param T;/*capacidade do caminh�o*/
param F;/*tempo fixo de prepara��o dos caminh�es para o processo de carregamento/descarregamento no cross-dock*/
param V;/*tempo vari�vel para descarregar/recarregar cada unidade de produto*/


#VARI�VEIS BIN�RIAS

var x{(i,j) in A, k in K};/*1 se o veiculo k viaja do n� i ao j, 0 caso contrario*/
var u{(i in P,k in K};/*1 se o veiculo k descarregar a demanda i no cross-dock, 0 cc*/
var r{(i in P, k in K};/*1 se o veiculo k  recarregar a demanda i no cross-dock, 0 cc*/
var q{k in K};/*1 se o veiculo k parou no cross-dock para o processo de descarga, 0 cc*/
var q2{k in K};/*1 se o veiculo k parou no cross-dock para o processo de recarga, 0 cc*/

#VARI�VEIS CONT�NUAS

var l{(i in N,k in K)}/*tempo de saido do caminhao k para o n� i*/
var f{k in K}/*tempo final da opera��o de descarga do caminh�o k no cross-dock*/
var s{k in K}/*hora de in�cio da opera��o de recarga do caminh�o k no cross -dock*/
var g{i in P}/*tempo final da opera��o de descarga do pedido i no cross-dock*/

#FUN��O OBJETIVO

minimize Z: sum{(i,j) in A, k in K} (c[i,j] * x[i,j,k]))};

#RESTRI��ES

s.t. r1 {i in P}: sum{j in P, k in K : i!=j} x[i,j,k] = 1;/*assegura que um caminh�o viaje entre os n�s de oferta sem repetir um n�*/
s.t. r2 {i in D}: sum{j in D, k in K : i!=j} x[i,j,k] = 1;/*assegura que um caminh�o viaje entre os n�s de demanda sem repetir um n�*/
s.t. r3 {k in K}: sum{j in P, R in N} x[R,j,k] = 1;/*assegura que cada caminh�o entrante deve come�ar a partir do cross-dock*/#VERIFICAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAR
s.t. r4 {k in K}: sum{j in D, S in N} x[S,j,k] = 1;/*assegura que cada caminh�o de saida deve come�ar a partir do cross-dock*/#VERIFICAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAR
s.t. r5 {k in K}: sum{i in P, R in N} x[i,R,k] = 1;/*assegura que os ve�culos retornem ao cross-dock no final de suas viagens*/
s.t. r6 {k in K}: sum{i in D, S in N} x[i,S,k] = 1;/*Idem*/
s.t. r7 {k in K}: sum{i in P, j in P : i!=j} (d[i]*x[i,j,k]) <= T;/*assegura que o volume total de produtos transportados por caminhos de entrada/sa�da n�o exceder� a capacidade*/
s.t. r8 {k in K}: sum{i in D, j in D : i!=j} (d[i]*x[i,j,k]);/*Idem*/
s.t. r9 {h in P, k in K}: sum{i in P : i!=j} x[i,h,k] = sum{j in P} x[h,j,k];/*para cada n� se um caminh�o viajar do n� i para o n� j deve deixar o n� j para os passeios de recolha e de entrega*/
s.t. r10 {h in D, k in K}: sum{i in D : i!=j} x[i,h,k] = sum{j in D} x[h,j,k];/*Idem*/
s.t. r11 {i in N, j in N, k in K : i!=j} : l[j,k] >= (l[i,k] + t[i,j] - M*(1-x[i,j,k]);/*determinar o tempo de viagem entre dois n�s se eles forem percorridos consecutivamente pelo mesmo caminh�o*/
s.t. r12 {i in N, j in N, k in K : i!=j} : l[i,j,k] <= M*x[i,j,k];/*Idem*/
s.t. r13 {i in N, k in K} : a[i] <= l[i,k];/*Implica que os caminh�es devem visitar os n�s dentro da janela de tempo*/
s.t. r14 {i in N, k in K} : l[i,k] <= b[i];/*Idem*/
s.t. r15 {i in P, k in K} : u[i,k] - r[i,k] = sum{j in P union R}x[i,j,k] - sum{j in D union S}x[i+n,j,k];
s.t. r16 {i in P, k in K} : u[i,k] + r[i,k] = 1;
s.t. r17`{k in K} : (1/M)*sum{i in P} u[i,k] <= q[k];
s.t. r18`{k in K} : q[k] <= sum{i in P} u[i,k];
s.t. r19 {k in K} : f[k] = l[R,k] + F[q,k] + V*sum{i in P} d[i]*u[i,k];
s.t. r20`{k in K} : s[k] >= f[k];
s.t. r21 {i in P, k in K} : s[k] >= g[i] - M*(1 - r[i,k]);
s.t. r22 {i in P, k in K} : g[i] >= f[k] - M*(1 - u[i,k]);
s.t. r23 {k in K} : (1/M)*sum{i in P} r[i,k] <= q2[k];
s.t. r24 {k in K} : q2[k] <= sum{i in P} r[i,k];
s.t. r25 {k in K} : l[s,k] = s[k] + F*q2[k] + V*sum{i in P} d[i]*r[i,k];


data;

param T := 15;
param F := 