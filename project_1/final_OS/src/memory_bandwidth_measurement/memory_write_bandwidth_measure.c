#include <stdio.h>
#include <time.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

#define LOOP_OVERHEAD 105620
#define PERFORMANCE_OVERHEAD 34

int main(){
    const int LEN = 1 << 28;    //  256MB

    int *a = (int*)malloc(LEN*sizeof(int)); //1 GB
    unsigned int hi1,lo1,hi2,lo2;
    unsigned int begin, end;
    long long i = 0;
	asm volatile ("cpuid\n\t"
		      "rdtsc\n\t"
		      "mov %%edx, %0\n\t"
		      "mov %%eax, %1\n\t"
		      : "=r" (hi1), "=r" (lo1)
		      :: "%rax", "%rbx", "%rcx", "%rdx"); 
      	
    for (i = 0; i < 1024*256; i++){ //writing 1 GB in the loop 1024x256x1024x4B. Sizeof(int) is 4B
	a[i+0]=0;
	a[i+1]=1;
	a[i+2]=2;
	a[i+3]=3;
	a[i+4]=4;
	a[i+5]=5;
	a[i+6]=6;
	a[i+7]=7;
	a[i+8]=8;
	a[i+9]=9;
	a[i+10]=10;
	a[i+11]=11;
	a[i+12]=12;
	a[i+13]=13;
	a[i+14]=14;
	a[i+15]=15;
	a[i+16]=16;
	a[i+17]=17;
	a[i+18]=18;
	a[i+19]=19;
	a[i+20]=20;
	a[i+21]=21;
	a[i+22]=22;
	a[i+23]=23;
	a[i+24]=24;
	a[i+25]=25;
	a[i+26]=26;
	a[i+27]=27;
	a[i+28]=28;
	a[i+29]=29;
	a[i+30]=30;
	a[i+31]=31;
	a[i+32]=32;
	a[i+33]=33;
	a[i+34]=34;
	a[i+35]=35;
	a[i+36]=36;
	a[i+37]=37;
	a[i+38]=38;
	a[i+39]=39;
	a[i+40]=40;
	a[i+41]=41;
	a[i+42]=42;
	a[i+43]=43;
	a[i+44]=44;
	a[i+45]=45;
	a[i+46]=46;
	a[i+47]=47;
	a[i+48]=48;
	a[i+49]=49;
	a[i+50]=50;
	a[i+51]=51;
	a[i+52]=52;
	a[i+53]=53;
	a[i+54]=54;
	a[i+55]=55;
	a[i+56]=56;
	a[i+57]=57;
	a[i+58]=58;
	a[i+59]=59;
	a[i+60]=60;
	a[i+61]=61;
	a[i+62]=62;
	a[i+63]=63;
	a[i+64]=64;
	a[i+65]=65;
	a[i+66]=66;
	a[i+67]=67;
	a[i+68]=68;
	a[i+69]=69;
	a[i+70]=70;
	a[i+71]=71;
	a[i+72]=72;
	a[i+73]=73;
	a[i+74]=74;
	a[i+75]=75;
	a[i+76]=76;
	a[i+77]=77;
	a[i+78]=78;
	a[i+79]=79;
	a[i+80]=80;
	a[i+81]=81;
	a[i+82]=82;
	a[i+83]=83;
	a[i+84]=84;
	a[i+85]=85;
	a[i+86]=86;
	a[i+87]=87;
	a[i+88]=88;
	a[i+89]=89;
	a[i+90]=90;
	a[i+91]=91;
	a[i+92]=92;
	a[i+93]=93;
	a[i+94]=94;
	a[i+95]=95;
	a[i+96]=96;
	a[i+97]=97;
	a[i+98]=98;
	a[i+99]=99;
	a[i+100]=100;
	a[i+101]=101;
	a[i+102]=102;
	a[i+103]=103;
	a[i+104]=104;
	a[i+105]=105;
	a[i+106]=106;
	a[i+107]=107;
	a[i+108]=108;
	a[i+109]=109;
	a[i+110]=110;
	a[i+111]=111;
	a[i+112]=112;
	a[i+113]=113;
	a[i+114]=114;
	a[i+115]=115;
	a[i+116]=116;
	a[i+117]=117;
	a[i+118]=118;
	a[i+119]=119;
	a[i+120]=120;
	a[i+121]=121;
	a[i+122]=122;
	a[i+123]=123;
	a[i+124]=124;
	a[i+125]=125;
	a[i+126]=126;
	a[i+127]=127;
	a[i+128]=128;
	a[i+129]=129;
	a[i+130]=130;
	a[i+131]=131;
	a[i+132]=132;
	a[i+133]=133;
	a[i+134]=134;
	a[i+135]=135;
	a[i+136]=136;
	a[i+137]=137;
	a[i+138]=138;
	a[i+139]=139;
	a[i+140]=140;
	a[i+141]=141;
	a[i+142]=142;
	a[i+143]=143;
	a[i+144]=144;
	a[i+145]=145;
	a[i+146]=146;
	a[i+147]=147;
	a[i+148]=148;
	a[i+149]=149;
	a[i+150]=150;
	a[i+151]=151;
	a[i+152]=152;
	a[i+153]=153;
	a[i+154]=154;
	a[i+155]=155;
	a[i+156]=156;
	a[i+157]=157;
	a[i+158]=158;
	a[i+159]=159;
	a[i+160]=160;
	a[i+161]=161;
	a[i+162]=162;
	a[i+163]=163;
	a[i+164]=164;
	a[i+165]=165;
	a[i+166]=166;
	a[i+167]=167;
	a[i+168]=168;
	a[i+169]=169;
	a[i+170]=170;
	a[i+171]=171;
	a[i+172]=172;
	a[i+173]=173;
	a[i+174]=174;
	a[i+175]=175;
	a[i+176]=176;
	a[i+177]=177;
	a[i+178]=178;
	a[i+179]=179;
	a[i+180]=180;
	a[i+181]=181;
	a[i+182]=182;
	a[i+183]=183;
	a[i+184]=184;
	a[i+185]=185;
	a[i+186]=186;
	a[i+187]=187;
	a[i+188]=188;
	a[i+189]=189;
	a[i+190]=190;
	a[i+191]=191;
	a[i+192]=192;
	a[i+193]=193;
	a[i+194]=194;
	a[i+195]=195;
	a[i+196]=196;
	a[i+197]=197;
	a[i+198]=198;
	a[i+199]=199;
	a[i+200]=200;
	a[i+201]=201;
	a[i+202]=202;
	a[i+203]=203;
	a[i+204]=204;
	a[i+205]=205;
	a[i+206]=206;
	a[i+207]=207;
	a[i+208]=208;
	a[i+209]=209;
	a[i+210]=210;
	a[i+211]=211;
	a[i+212]=212;
	a[i+213]=213;
	a[i+214]=214;
	a[i+215]=215;
	a[i+216]=216;
	a[i+217]=217;
	a[i+218]=218;
	a[i+219]=219;
	a[i+220]=220;
	a[i+221]=221;
	a[i+222]=222;
	a[i+223]=223;
	a[i+224]=224;
	a[i+225]=225;
	a[i+226]=226;
	a[i+227]=227;
	a[i+228]=228;
	a[i+229]=229;
	a[i+230]=230;
	a[i+231]=231;
	a[i+232]=232;
	a[i+233]=233;
	a[i+234]=234;
	a[i+235]=235;
	a[i+236]=236;
	a[i+237]=237;
	a[i+238]=238;
	a[i+239]=239;
	a[i+240]=240;
	a[i+241]=241;
	a[i+242]=242;
	a[i+243]=243;
	a[i+244]=244;
	a[i+245]=245;
	a[i+246]=246;
	a[i+247]=247;
	a[i+248]=248;
	a[i+249]=249;
	a[i+250]=250;
	a[i+251]=251;
	a[i+252]=252;
	a[i+253]=253;
	a[i+254]=254;
	a[i+255]=255;
	a[i+256]=256;
	a[i+257]=257;
	a[i+258]=258;
	a[i+259]=259;
	a[i+260]=260;
	a[i+261]=261;
	a[i+262]=262;
	a[i+263]=263;
	a[i+264]=264;
	a[i+265]=265;
	a[i+266]=266;
	a[i+267]=267;
	a[i+268]=268;
	a[i+269]=269;
	a[i+270]=270;
	a[i+271]=271;
	a[i+272]=272;
	a[i+273]=273;
	a[i+274]=274;
	a[i+275]=275;
	a[i+276]=276;
	a[i+277]=277;
	a[i+278]=278;
	a[i+279]=279;
	a[i+280]=280;
	a[i+281]=281;
	a[i+282]=282;
	a[i+283]=283;
	a[i+284]=284;
	a[i+285]=285;
	a[i+286]=286;
	a[i+287]=287;
	a[i+288]=288;
	a[i+289]=289;
	a[i+290]=290;
	a[i+291]=291;
	a[i+292]=292;
	a[i+293]=293;
	a[i+294]=294;
	a[i+295]=295;
	a[i+296]=296;
	a[i+297]=297;
	a[i+298]=298;
	a[i+299]=299;
	a[i+300]=300;
	a[i+301]=301;
	a[i+302]=302;
	a[i+303]=303;
	a[i+304]=304;
	a[i+305]=305;
	a[i+306]=306;
	a[i+307]=307;
	a[i+308]=308;
	a[i+309]=309;
	a[i+310]=310;
	a[i+311]=311;
	a[i+312]=312;
	a[i+313]=313;
	a[i+314]=314;
	a[i+315]=315;
	a[i+316]=316;
	a[i+317]=317;
	a[i+318]=318;
	a[i+319]=319;
	a[i+320]=320;
	a[i+321]=321;
	a[i+322]=322;
	a[i+323]=323;
	a[i+324]=324;
	a[i+325]=325;
	a[i+326]=326;
	a[i+327]=327;
	a[i+328]=328;
	a[i+329]=329;
	a[i+330]=330;
	a[i+331]=331;
	a[i+332]=332;
	a[i+333]=333;
	a[i+334]=334;
	a[i+335]=335;
	a[i+336]=336;
	a[i+337]=337;
	a[i+338]=338;
	a[i+339]=339;
	a[i+340]=340;
	a[i+341]=341;
	a[i+342]=342;
	a[i+343]=343;
	a[i+344]=344;
	a[i+345]=345;
	a[i+346]=346;
	a[i+347]=347;
	a[i+348]=348;
	a[i+349]=349;
	a[i+350]=350;
	a[i+351]=351;
	a[i+352]=352;
	a[i+353]=353;
	a[i+354]=354;
	a[i+355]=355;
	a[i+356]=356;
	a[i+357]=357;
	a[i+358]=358;
	a[i+359]=359;
	a[i+360]=360;
	a[i+361]=361;
	a[i+362]=362;
	a[i+363]=363;
	a[i+364]=364;
	a[i+365]=365;
	a[i+366]=366;
	a[i+367]=367;
	a[i+368]=368;
	a[i+369]=369;
	a[i+370]=370;
	a[i+371]=371;
	a[i+372]=372;
	a[i+373]=373;
	a[i+374]=374;
	a[i+375]=375;
	a[i+376]=376;
	a[i+377]=377;
	a[i+378]=378;
	a[i+379]=379;
	a[i+380]=380;
	a[i+381]=381;
	a[i+382]=382;
	a[i+383]=383;
	a[i+384]=384;
	a[i+385]=385;
	a[i+386]=386;
	a[i+387]=387;
	a[i+388]=388;
	a[i+389]=389;
	a[i+390]=390;
	a[i+391]=391;
	a[i+392]=392;
	a[i+393]=393;
	a[i+394]=394;
	a[i+395]=395;
	a[i+396]=396;
	a[i+397]=397;
	a[i+398]=398;
	a[i+399]=399;
	a[i+400]=400;
	a[i+401]=401;
	a[i+402]=402;
	a[i+403]=403;
	a[i+404]=404;
	a[i+405]=405;
	a[i+406]=406;
	a[i+407]=407;
	a[i+408]=408;
	a[i+409]=409;
	a[i+410]=410;
	a[i+411]=411;
	a[i+412]=412;
	a[i+413]=413;
	a[i+414]=414;
	a[i+415]=415;
	a[i+416]=416;
	a[i+417]=417;
	a[i+418]=418;
	a[i+419]=419;
	a[i+420]=420;
	a[i+421]=421;
	a[i+422]=422;
	a[i+423]=423;
	a[i+424]=424;
	a[i+425]=425;
	a[i+426]=426;
	a[i+427]=427;
	a[i+428]=428;
	a[i+429]=429;
	a[i+430]=430;
	a[i+431]=431;
	a[i+432]=432;
	a[i+433]=433;
	a[i+434]=434;
	a[i+435]=435;
	a[i+436]=436;
	a[i+437]=437;
	a[i+438]=438;
	a[i+439]=439;
	a[i+440]=440;
	a[i+441]=441;
	a[i+442]=442;
	a[i+443]=443;
	a[i+444]=444;
	a[i+445]=445;
	a[i+446]=446;
	a[i+447]=447;
	a[i+448]=448;
	a[i+449]=449;
	a[i+450]=450;
	a[i+451]=451;
	a[i+452]=452;
	a[i+453]=453;
	a[i+454]=454;
	a[i+455]=455;
	a[i+456]=456;
	a[i+457]=457;
	a[i+458]=458;
	a[i+459]=459;
	a[i+460]=460;
	a[i+461]=461;
	a[i+462]=462;
	a[i+463]=463;
	a[i+464]=464;
	a[i+465]=465;
	a[i+466]=466;
	a[i+467]=467;
	a[i+468]=468;
	a[i+469]=469;
	a[i+470]=470;
	a[i+471]=471;
	a[i+472]=472;
	a[i+473]=473;
	a[i+474]=474;
	a[i+475]=475;
	a[i+476]=476;
	a[i+477]=477;
	a[i+478]=478;
	a[i+479]=479;
	a[i+480]=480;
	a[i+481]=481;
	a[i+482]=482;
	a[i+483]=483;
	a[i+484]=484;
	a[i+485]=485;
	a[i+486]=486;
	a[i+487]=487;
	a[i+488]=488;
	a[i+489]=489;
	a[i+490]=490;
	a[i+491]=491;
	a[i+492]=492;
	a[i+493]=493;
	a[i+494]=494;
	a[i+495]=495;
	a[i+496]=496;
	a[i+497]=497;
	a[i+498]=498;
	a[i+499]=499;
	a[i+500]=500;
	a[i+501]=501;
	a[i+502]=502;
	a[i+503]=503;
	a[i+504]=504;
	a[i+505]=505;
	a[i+506]=506;
	a[i+507]=507;
	a[i+508]=508;
	a[i+509]=509;
	a[i+510]=510;
	a[i+511]=511;
	a[i+512]=512;
	a[i+513]=513;
	a[i+514]=514;
	a[i+515]=515;
	a[i+516]=516;
	a[i+517]=517;
	a[i+518]=518;
	a[i+519]=519;
	a[i+520]=520;
	a[i+521]=521;
	a[i+522]=522;
	a[i+523]=523;
	a[i+524]=524;
	a[i+525]=525;
	a[i+526]=526;
	a[i+527]=527;
	a[i+528]=528;
	a[i+529]=529;
	a[i+530]=530;
	a[i+531]=531;
	a[i+532]=532;
	a[i+533]=533;
	a[i+534]=534;
	a[i+535]=535;
	a[i+536]=536;
	a[i+537]=537;
	a[i+538]=538;
	a[i+539]=539;
	a[i+540]=540;
	a[i+541]=541;
	a[i+542]=542;
	a[i+543]=543;
	a[i+544]=544;
	a[i+545]=545;
	a[i+546]=546;
	a[i+547]=547;
	a[i+548]=548;
	a[i+549]=549;
	a[i+550]=550;
	a[i+551]=551;
	a[i+552]=552;
	a[i+553]=553;
	a[i+554]=554;
	a[i+555]=555;
	a[i+556]=556;
	a[i+557]=557;
	a[i+558]=558;
	a[i+559]=559;
	a[i+560]=560;
	a[i+561]=561;
	a[i+562]=562;
	a[i+563]=563;
	a[i+564]=564;
	a[i+565]=565;
	a[i+566]=566;
	a[i+567]=567;
	a[i+568]=568;
	a[i+569]=569;
	a[i+570]=570;
	a[i+571]=571;
	a[i+572]=572;
	a[i+573]=573;
	a[i+574]=574;
	a[i+575]=575;
	a[i+576]=576;
	a[i+577]=577;
	a[i+578]=578;
	a[i+579]=579;
	a[i+580]=580;
	a[i+581]=581;
	a[i+582]=582;
	a[i+583]=583;
	a[i+584]=584;
	a[i+585]=585;
	a[i+586]=586;
	a[i+587]=587;
	a[i+588]=588;
	a[i+589]=589;
	a[i+590]=590;
	a[i+591]=591;
	a[i+592]=592;
	a[i+593]=593;
	a[i+594]=594;
	a[i+595]=595;
	a[i+596]=596;
	a[i+597]=597;
	a[i+598]=598;
	a[i+599]=599;
	a[i+600]=600;
	a[i+601]=601;
	a[i+602]=602;
	a[i+603]=603;
	a[i+604]=604;
	a[i+605]=605;
	a[i+606]=606;
	a[i+607]=607;
	a[i+608]=608;
	a[i+609]=609;
	a[i+610]=610;
	a[i+611]=611;
	a[i+612]=612;
	a[i+613]=613;
	a[i+614]=614;
	a[i+615]=615;
	a[i+616]=616;
	a[i+617]=617;
	a[i+618]=618;
	a[i+619]=619;
	a[i+620]=620;
	a[i+621]=621;
	a[i+622]=622;
	a[i+623]=623;
	a[i+624]=624;
	a[i+625]=625;
	a[i+626]=626;
	a[i+627]=627;
	a[i+628]=628;
	a[i+629]=629;
	a[i+630]=630;
	a[i+631]=631;
	a[i+632]=632;
	a[i+633]=633;
	a[i+634]=634;
	a[i+635]=635;
	a[i+636]=636;
	a[i+637]=637;
	a[i+638]=638;
	a[i+639]=639;
	a[i+640]=640;
	a[i+641]=641;
	a[i+642]=642;
	a[i+643]=643;
	a[i+644]=644;
	a[i+645]=645;
	a[i+646]=646;
	a[i+647]=647;
	a[i+648]=648;
	a[i+649]=649;
	a[i+650]=650;
	a[i+651]=651;
	a[i+652]=652;
	a[i+653]=653;
	a[i+654]=654;
	a[i+655]=655;
	a[i+656]=656;
	a[i+657]=657;
	a[i+658]=658;
	a[i+659]=659;
	a[i+660]=660;
	a[i+661]=661;
	a[i+662]=662;
	a[i+663]=663;
	a[i+664]=664;
	a[i+665]=665;
	a[i+666]=666;
	a[i+667]=667;
	a[i+668]=668;
	a[i+669]=669;
	a[i+670]=670;
	a[i+671]=671;
	a[i+672]=672;
	a[i+673]=673;
	a[i+674]=674;
	a[i+675]=675;
	a[i+676]=676;
	a[i+677]=677;
	a[i+678]=678;
	a[i+679]=679;
	a[i+680]=680;
	a[i+681]=681;
	a[i+682]=682;
	a[i+683]=683;
	a[i+684]=684;
	a[i+685]=685;
	a[i+686]=686;
	a[i+687]=687;
	a[i+688]=688;
	a[i+689]=689;
	a[i+690]=690;
	a[i+691]=691;
	a[i+692]=692;
	a[i+693]=693;
	a[i+694]=694;
	a[i+695]=695;
	a[i+696]=696;
	a[i+697]=697;
	a[i+698]=698;
	a[i+699]=699;
	a[i+700]=700;
	a[i+701]=701;
	a[i+702]=702;
	a[i+703]=703;
	a[i+704]=704;
	a[i+705]=705;
	a[i+706]=706;
	a[i+707]=707;
	a[i+708]=708;
	a[i+709]=709;
	a[i+710]=710;
	a[i+711]=711;
	a[i+712]=712;
	a[i+713]=713;
	a[i+714]=714;
	a[i+715]=715;
	a[i+716]=716;
	a[i+717]=717;
	a[i+718]=718;
	a[i+719]=719;
	a[i+720]=720;
	a[i+721]=721;
	a[i+722]=722;
	a[i+723]=723;
	a[i+724]=724;
	a[i+725]=725;
	a[i+726]=726;
	a[i+727]=727;
	a[i+728]=728;
	a[i+729]=729;
	a[i+730]=730;
	a[i+731]=731;
	a[i+732]=732;
	a[i+733]=733;
	a[i+734]=734;
	a[i+735]=735;
	a[i+736]=736;
	a[i+737]=737;
	a[i+738]=738;
	a[i+739]=739;
	a[i+740]=740;
	a[i+741]=741;
	a[i+742]=742;
	a[i+743]=743;
	a[i+744]=744;
	a[i+745]=745;
	a[i+746]=746;
	a[i+747]=747;
	a[i+748]=748;
	a[i+749]=749;
	a[i+750]=750;
	a[i+751]=751;
	a[i+752]=752;
	a[i+753]=753;
	a[i+754]=754;
	a[i+755]=755;
	a[i+756]=756;
	a[i+757]=757;
	a[i+758]=758;
	a[i+759]=759;
	a[i+760]=760;
	a[i+761]=761;
	a[i+762]=762;
	a[i+763]=763;
	a[i+764]=764;
	a[i+765]=765;
	a[i+766]=766;
	a[i+767]=767;
	a[i+768]=768;
	a[i+769]=769;
	a[i+770]=770;
	a[i+771]=771;
	a[i+772]=772;
	a[i+773]=773;
	a[i+774]=774;
	a[i+775]=775;
	a[i+776]=776;
	a[i+777]=777;
	a[i+778]=778;
	a[i+779]=779;
	a[i+780]=780;
	a[i+781]=781;
	a[i+782]=782;
	a[i+783]=783;
	a[i+784]=784;
	a[i+785]=785;
	a[i+786]=786;
	a[i+787]=787;
	a[i+788]=788;
	a[i+789]=789;
	a[i+790]=790;
	a[i+791]=791;
	a[i+792]=792;
	a[i+793]=793;
	a[i+794]=794;
	a[i+795]=795;
	a[i+796]=796;
	a[i+797]=797;
	a[i+798]=798;
	a[i+799]=799;
	a[i+800]=800;
	a[i+801]=801;
	a[i+802]=802;
	a[i+803]=803;
	a[i+804]=804;
	a[i+805]=805;
	a[i+806]=806;
	a[i+807]=807;
	a[i+808]=808;
	a[i+809]=809;
	a[i+810]=810;
	a[i+811]=811;
	a[i+812]=812;
	a[i+813]=813;
	a[i+814]=814;
	a[i+815]=815;
	a[i+816]=816;
	a[i+817]=817;
	a[i+818]=818;
	a[i+819]=819;
	a[i+820]=820;
	a[i+821]=821;
	a[i+822]=822;
	a[i+823]=823;
	a[i+824]=824;
	a[i+825]=825;
	a[i+826]=826;
	a[i+827]=827;
	a[i+828]=828;
	a[i+829]=829;
	a[i+830]=830;
	a[i+831]=831;
	a[i+832]=832;
	a[i+833]=833;
	a[i+834]=834;
	a[i+835]=835;
	a[i+836]=836;
	a[i+837]=837;
	a[i+838]=838;
	a[i+839]=839;
	a[i+840]=840;
	a[i+841]=841;
	a[i+842]=842;
	a[i+843]=843;
	a[i+844]=844;
	a[i+845]=845;
	a[i+846]=846;
	a[i+847]=847;
	a[i+848]=848;
	a[i+849]=849;
	a[i+850]=850;
	a[i+851]=851;
	a[i+852]=852;
	a[i+853]=853;
	a[i+854]=854;
	a[i+855]=855;
	a[i+856]=856;
	a[i+857]=857;
	a[i+858]=858;
	a[i+859]=859;
	a[i+860]=860;
	a[i+861]=861;
	a[i+862]=862;
	a[i+863]=863;
	a[i+864]=864;
	a[i+865]=865;
	a[i+866]=866;
	a[i+867]=867;
	a[i+868]=868;
	a[i+869]=869;
	a[i+870]=870;
	a[i+871]=871;
	a[i+872]=872;
	a[i+873]=873;
	a[i+874]=874;
	a[i+875]=875;
	a[i+876]=876;
	a[i+877]=877;
	a[i+878]=878;
	a[i+879]=879;
	a[i+880]=880;
	a[i+881]=881;
	a[i+882]=882;
	a[i+883]=883;
	a[i+884]=884;
	a[i+885]=885;
	a[i+886]=886;
	a[i+887]=887;
	a[i+888]=888;
	a[i+889]=889;
	a[i+890]=890;
	a[i+891]=891;
	a[i+892]=892;
	a[i+893]=893;
	a[i+894]=894;
	a[i+895]=895;
	a[i+896]=896;
	a[i+897]=897;
	a[i+898]=898;
	a[i+899]=899;
	a[i+900]=900;
	a[i+901]=901;
	a[i+902]=902;
	a[i+903]=903;
	a[i+904]=904;
	a[i+905]=905;
	a[i+906]=906;
	a[i+907]=907;
	a[i+908]=908;
	a[i+909]=909;
	a[i+910]=910;
	a[i+911]=911;
	a[i+912]=912;
	a[i+913]=913;
	a[i+914]=914;
	a[i+915]=915;
	a[i+916]=916;
	a[i+917]=917;
	a[i+918]=918;
	a[i+919]=919;
	a[i+920]=920;
	a[i+921]=921;
	a[i+922]=922;
	a[i+923]=923;
	a[i+924]=924;
	a[i+925]=925;
	a[i+926]=926;
	a[i+927]=927;
	a[i+928]=928;
	a[i+929]=929;
	a[i+930]=930;
	a[i+931]=931;
	a[i+932]=932;
	a[i+933]=933;
	a[i+934]=934;
	a[i+935]=935;
	a[i+936]=936;
	a[i+937]=937;
	a[i+938]=938;
	a[i+939]=939;
	a[i+940]=940;
	a[i+941]=941;
	a[i+942]=942;
	a[i+943]=943;
	a[i+944]=944;
	a[i+945]=945;
	a[i+946]=946;
	a[i+947]=947;
	a[i+948]=948;
	a[i+949]=949;
	a[i+950]=950;
	a[i+951]=951;
	a[i+952]=952;
	a[i+953]=953;
	a[i+954]=954;
	a[i+955]=955;
	a[i+956]=956;
	a[i+957]=957;
	a[i+958]=958;
	a[i+959]=959;
	a[i+960]=960;
	a[i+961]=961;
	a[i+962]=962;
	a[i+963]=963;
	a[i+964]=964;
	a[i+965]=965;
	a[i+966]=966;
	a[i+967]=967;
	a[i+968]=968;
	a[i+969]=969;
	a[i+970]=970;
	a[i+971]=971;
	a[i+972]=972;
	a[i+973]=973;
	a[i+974]=974;
	a[i+975]=975;
	a[i+976]=976;
	a[i+977]=977;
	a[i+978]=978;
	a[i+979]=979;
	a[i+980]=980;
	a[i+981]=981;
	a[i+982]=982;
	a[i+983]=983;
	a[i+984]=984;
	a[i+985]=985;
	a[i+986]=986;
	a[i+987]=987;
	a[i+988]=988;
	a[i+989]=989;
	a[i+990]=990;
	a[i+991]=991;
	a[i+992]=992;
	a[i+993]=993;
	a[i+994]=994;
	a[i+995]=995;
	a[i+996]=996;
	a[i+997]=997;
	a[i+998]=998;
	a[i+999]=999;
	a[i+1000]=1000;
	a[i+1001]=1001;
	a[i+1002]=1002;
	a[i+1003]=1003;
	a[i+1004]=1004;
	a[i+1005]=1005;
	a[i+1006]=1006;
	a[i+1007]=1007;
	a[i+1008]=1008;
	a[i+1009]=1009;
	a[i+1010]=1010;
	a[i+1011]=1011;
	a[i+1012]=1012;
	a[i+1013]=1013;
	a[i+1014]=1014;
	a[i+1015]=1015;
	a[i+1016]=1016;
	a[i+1017]=1017;
	a[i+1018]=1018;
	a[i+1019]=1019;
	a[i+1020]=1020;
	a[i+1021]=1021;
	a[i+1022]=1022;
	a[i+1023]=1023;
		    }
	asm volatile ("rdtscp\n\t"
		  "mov %%edx, %0\n\t"
		  "mov %%eax, %1\n\t"
		  "cpuid\n\t"
		  : "=r" (hi2), "=r" (lo2)
		  :: "%rax", "%rbx", "%rcx", "%rdx");
	begin = (uint64_t)hi1 << 32 | lo1;
	end = (uint64_t)hi2 << 32 | lo2;
	
    printf("\n%lu", (end - begin - LOOP_OVERHEAD - PERFORMANCE_OVERHEAD));
    free(a);
}
