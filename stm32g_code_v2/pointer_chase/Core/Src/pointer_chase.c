/*
 * pointer_chase.c
 *
 *  Created on: 31 juil. 2023
 *      Author: loict
 */
#include "pointer_chase.h"




#ifdef ROCCM
__attribute__((section(".ccmramdata"))) void*
#endif
#ifdef RORAM
__attribute__((section(".data"))) void*
#endif
#ifdef RORAM2
__attribute__((section(".ram2data"))) void*
#endif
#ifdef ROFLASH
const void* const
#endif
pointers[1000] = {
  &pointers[1], &pointers[2], &pointers[3], &pointers[4], &pointers[5], &pointers[6], &pointers[7], &pointers[8], &pointers[9], &pointers[10], &pointers[11], &pointers[12], &pointers[13], &pointers[14], &pointers[15], &pointers[16], &pointers[17], &pointers[18], &pointers[19], &pointers[20], &pointers[21], &pointers[22], &pointers[23], &pointers[24], &pointers[25], &pointers[26], &pointers[27], &pointers[28], &pointers[29], &pointers[30], &pointers[31], &pointers[32], &pointers[33], &pointers[34], &pointers[35], &pointers[36], &pointers[37], &pointers[38], &pointers[39], &pointers[40], &pointers[41], &pointers[42], &pointers[43], &pointers[44], &pointers[45], &pointers[46], &pointers[47], &pointers[48], &pointers[49], &pointers[50],
  &pointers[51], &pointers[52], &pointers[53], &pointers[54], &pointers[55], &pointers[56], &pointers[57], &pointers[58], &pointers[59], &pointers[60], &pointers[61], &pointers[62], &pointers[63], &pointers[64], &pointers[65], &pointers[66], &pointers[67], &pointers[68], &pointers[69], &pointers[70], &pointers[71], &pointers[72], &pointers[73], &pointers[74], &pointers[75], &pointers[76], &pointers[77], &pointers[78], &pointers[79], &pointers[80], &pointers[81], &pointers[82], &pointers[83], &pointers[84], &pointers[85], &pointers[86], &pointers[87], &pointers[88], &pointers[89], &pointers[90], &pointers[91], &pointers[92], &pointers[93], &pointers[94], &pointers[95], &pointers[96], &pointers[97], &pointers[98], &pointers[99], &pointers[100],
  &pointers[101], &pointers[102], &pointers[103], &pointers[104], &pointers[105], &pointers[106], &pointers[107], &pointers[108], &pointers[109], &pointers[110], &pointers[111], &pointers[112], &pointers[113], &pointers[114], &pointers[115], &pointers[116], &pointers[117], &pointers[118], &pointers[119], &pointers[120], &pointers[121], &pointers[122], &pointers[123], &pointers[124], &pointers[125], &pointers[126], &pointers[127], &pointers[128], &pointers[129], &pointers[130], &pointers[131], &pointers[132], &pointers[133], &pointers[134], &pointers[135], &pointers[136], &pointers[137], &pointers[138], &pointers[139], &pointers[140], &pointers[141], &pointers[142], &pointers[143], &pointers[144], &pointers[145], &pointers[146], &pointers[147], &pointers[148], &pointers[149], &pointers[150],
  &pointers[151], &pointers[152], &pointers[153], &pointers[154], &pointers[155], &pointers[156], &pointers[157], &pointers[158], &pointers[159], &pointers[160], &pointers[161], &pointers[162], &pointers[163], &pointers[164], &pointers[165], &pointers[166], &pointers[167], &pointers[168], &pointers[169], &pointers[170], &pointers[171], &pointers[172], &pointers[173], &pointers[174], &pointers[175], &pointers[176], &pointers[177], &pointers[178], &pointers[179], &pointers[180], &pointers[181], &pointers[182], &pointers[183], &pointers[184], &pointers[185], &pointers[186], &pointers[187], &pointers[188], &pointers[189], &pointers[190], &pointers[191], &pointers[192], &pointers[193], &pointers[194], &pointers[195], &pointers[196], &pointers[197], &pointers[198], &pointers[199], &pointers[200],
  &pointers[201], &pointers[202], &pointers[203], &pointers[204], &pointers[205], &pointers[206], &pointers[207], &pointers[208], &pointers[209], &pointers[210], &pointers[211], &pointers[212], &pointers[213], &pointers[214], &pointers[215], &pointers[216], &pointers[217], &pointers[218], &pointers[219], &pointers[220], &pointers[221], &pointers[222], &pointers[223], &pointers[224], &pointers[225], &pointers[226], &pointers[227], &pointers[228], &pointers[229], &pointers[230], &pointers[231], &pointers[232], &pointers[233], &pointers[234], &pointers[235], &pointers[236], &pointers[237], &pointers[238], &pointers[239], &pointers[240], &pointers[241], &pointers[242], &pointers[243], &pointers[244], &pointers[245], &pointers[246], &pointers[247], &pointers[248], &pointers[249], &pointers[250],
  &pointers[251], &pointers[252], &pointers[253], &pointers[254], &pointers[255], &pointers[256], &pointers[257], &pointers[258], &pointers[259], &pointers[260], &pointers[261], &pointers[262], &pointers[263], &pointers[264], &pointers[265], &pointers[266], &pointers[267], &pointers[268], &pointers[269], &pointers[270], &pointers[271], &pointers[272], &pointers[273], &pointers[274], &pointers[275], &pointers[276], &pointers[277], &pointers[278], &pointers[279], &pointers[280], &pointers[281], &pointers[282], &pointers[283], &pointers[284], &pointers[285], &pointers[286], &pointers[287], &pointers[288], &pointers[289], &pointers[290], &pointers[291], &pointers[292], &pointers[293], &pointers[294], &pointers[295], &pointers[296], &pointers[297], &pointers[298], &pointers[299], &pointers[300],
  &pointers[301], &pointers[302], &pointers[303], &pointers[304], &pointers[305], &pointers[306], &pointers[307], &pointers[308], &pointers[309], &pointers[310], &pointers[311], &pointers[312], &pointers[313], &pointers[314], &pointers[315], &pointers[316], &pointers[317], &pointers[318], &pointers[319], &pointers[320], &pointers[321], &pointers[322], &pointers[323], &pointers[324], &pointers[325], &pointers[326], &pointers[327], &pointers[328], &pointers[329], &pointers[330], &pointers[331], &pointers[332], &pointers[333], &pointers[334], &pointers[335], &pointers[336], &pointers[337], &pointers[338], &pointers[339], &pointers[340], &pointers[341], &pointers[342], &pointers[343], &pointers[344], &pointers[345], &pointers[346], &pointers[347], &pointers[348], &pointers[349], &pointers[350],
  &pointers[351], &pointers[352], &pointers[353], &pointers[354], &pointers[355], &pointers[356], &pointers[357], &pointers[358], &pointers[359], &pointers[360], &pointers[361], &pointers[362], &pointers[363], &pointers[364], &pointers[365], &pointers[366], &pointers[367], &pointers[368], &pointers[369], &pointers[370], &pointers[371], &pointers[372], &pointers[373], &pointers[374], &pointers[375], &pointers[376], &pointers[377], &pointers[378], &pointers[379], &pointers[380], &pointers[381], &pointers[382], &pointers[383], &pointers[384], &pointers[385], &pointers[386], &pointers[387], &pointers[388], &pointers[389], &pointers[390], &pointers[391], &pointers[392], &pointers[393], &pointers[394], &pointers[395], &pointers[396], &pointers[397], &pointers[398], &pointers[399], &pointers[400],
  &pointers[401], &pointers[402], &pointers[403], &pointers[404], &pointers[405], &pointers[406], &pointers[407], &pointers[408], &pointers[409], &pointers[410], &pointers[411], &pointers[412], &pointers[413], &pointers[414], &pointers[415], &pointers[416], &pointers[417], &pointers[418], &pointers[419], &pointers[420], &pointers[421], &pointers[422], &pointers[423], &pointers[424], &pointers[425], &pointers[426], &pointers[427], &pointers[428], &pointers[429], &pointers[430], &pointers[431], &pointers[432], &pointers[433], &pointers[434], &pointers[435], &pointers[436], &pointers[437], &pointers[438], &pointers[439], &pointers[440], &pointers[441], &pointers[442], &pointers[443], &pointers[444], &pointers[445], &pointers[446], &pointers[447], &pointers[448], &pointers[449], &pointers[450],
  &pointers[451], &pointers[452], &pointers[453], &pointers[454], &pointers[455], &pointers[456], &pointers[457], &pointers[458], &pointers[459], &pointers[460], &pointers[461], &pointers[462], &pointers[463], &pointers[464], &pointers[465], &pointers[466], &pointers[467], &pointers[468], &pointers[469], &pointers[470], &pointers[471], &pointers[472], &pointers[473], &pointers[474], &pointers[475], &pointers[476], &pointers[477], &pointers[478], &pointers[479], &pointers[480], &pointers[481], &pointers[482], &pointers[483], &pointers[484], &pointers[485], &pointers[486], &pointers[487], &pointers[488], &pointers[489], &pointers[490], &pointers[491], &pointers[492], &pointers[493], &pointers[494], &pointers[495], &pointers[496], &pointers[497], &pointers[498], &pointers[499], &pointers[500],
  &pointers[501], &pointers[502], &pointers[503], &pointers[504], &pointers[505], &pointers[506], &pointers[507], &pointers[508], &pointers[509], &pointers[510], &pointers[511], &pointers[512], &pointers[513], &pointers[514], &pointers[515], &pointers[516], &pointers[517], &pointers[518], &pointers[519], &pointers[520], &pointers[521], &pointers[522], &pointers[523], &pointers[524], &pointers[525], &pointers[526], &pointers[527], &pointers[528], &pointers[529], &pointers[530], &pointers[531], &pointers[532], &pointers[533], &pointers[534], &pointers[535], &pointers[536], &pointers[537], &pointers[538], &pointers[539], &pointers[540], &pointers[541], &pointers[542], &pointers[543], &pointers[544], &pointers[545], &pointers[546], &pointers[547], &pointers[548], &pointers[549], &pointers[550],
  &pointers[551], &pointers[552], &pointers[553], &pointers[554], &pointers[555], &pointers[556], &pointers[557], &pointers[558], &pointers[559], &pointers[560], &pointers[561], &pointers[562], &pointers[563], &pointers[564], &pointers[565], &pointers[566], &pointers[567], &pointers[568], &pointers[569], &pointers[570], &pointers[571], &pointers[572], &pointers[573], &pointers[574], &pointers[575], &pointers[576], &pointers[577], &pointers[578], &pointers[579], &pointers[580], &pointers[581], &pointers[582], &pointers[583], &pointers[584], &pointers[585], &pointers[586], &pointers[587], &pointers[588], &pointers[589], &pointers[590], &pointers[591], &pointers[592], &pointers[593], &pointers[594], &pointers[595], &pointers[596], &pointers[597], &pointers[598], &pointers[599], &pointers[600],
  &pointers[601], &pointers[602], &pointers[603], &pointers[604], &pointers[605], &pointers[606], &pointers[607], &pointers[608], &pointers[609], &pointers[610], &pointers[611], &pointers[612], &pointers[613], &pointers[614], &pointers[615], &pointers[616], &pointers[617], &pointers[618], &pointers[619], &pointers[620], &pointers[621], &pointers[622], &pointers[623], &pointers[624], &pointers[625], &pointers[626], &pointers[627], &pointers[628], &pointers[629], &pointers[630], &pointers[631], &pointers[632], &pointers[633], &pointers[634], &pointers[635], &pointers[636], &pointers[637], &pointers[638], &pointers[639], &pointers[640], &pointers[641], &pointers[642], &pointers[643], &pointers[644], &pointers[645], &pointers[646], &pointers[647], &pointers[648], &pointers[649], &pointers[650],
  &pointers[651], &pointers[652], &pointers[653], &pointers[654], &pointers[655], &pointers[656], &pointers[657], &pointers[658], &pointers[659], &pointers[660], &pointers[661], &pointers[662], &pointers[663], &pointers[664], &pointers[665], &pointers[666], &pointers[667], &pointers[668], &pointers[669], &pointers[670], &pointers[671], &pointers[672], &pointers[673], &pointers[674], &pointers[675], &pointers[676], &pointers[677], &pointers[678], &pointers[679], &pointers[680], &pointers[681], &pointers[682], &pointers[683], &pointers[684], &pointers[685], &pointers[686], &pointers[687], &pointers[688], &pointers[689], &pointers[690], &pointers[691], &pointers[692], &pointers[693], &pointers[694], &pointers[695], &pointers[696], &pointers[697], &pointers[698], &pointers[699], &pointers[700],
  &pointers[701], &pointers[702], &pointers[703], &pointers[704], &pointers[705], &pointers[706], &pointers[707], &pointers[708], &pointers[709], &pointers[710], &pointers[711], &pointers[712], &pointers[713], &pointers[714], &pointers[715], &pointers[716], &pointers[717], &pointers[718], &pointers[719], &pointers[720], &pointers[721], &pointers[722], &pointers[723], &pointers[724], &pointers[725], &pointers[726], &pointers[727], &pointers[728], &pointers[729], &pointers[730], &pointers[731], &pointers[732], &pointers[733], &pointers[734], &pointers[735], &pointers[736], &pointers[737], &pointers[738], &pointers[739], &pointers[740], &pointers[741], &pointers[742], &pointers[743], &pointers[744], &pointers[745], &pointers[746], &pointers[747], &pointers[748], &pointers[749], &pointers[750],
  &pointers[751], &pointers[752], &pointers[753], &pointers[754], &pointers[755], &pointers[756], &pointers[757], &pointers[758], &pointers[759], &pointers[760], &pointers[761], &pointers[762], &pointers[763], &pointers[764], &pointers[765], &pointers[766], &pointers[767], &pointers[768], &pointers[769], &pointers[770], &pointers[771], &pointers[772], &pointers[773], &pointers[774], &pointers[775], &pointers[776], &pointers[777], &pointers[778], &pointers[779], &pointers[780], &pointers[781], &pointers[782], &pointers[783], &pointers[784], &pointers[785], &pointers[786], &pointers[787], &pointers[788], &pointers[789], &pointers[790], &pointers[791], &pointers[792], &pointers[793], &pointers[794], &pointers[795], &pointers[796], &pointers[797], &pointers[798], &pointers[799], &pointers[800],
  &pointers[801], &pointers[802], &pointers[803], &pointers[804], &pointers[805], &pointers[806], &pointers[807], &pointers[808], &pointers[809], &pointers[810], &pointers[811], &pointers[812], &pointers[813], &pointers[814], &pointers[815], &pointers[816], &pointers[817], &pointers[818], &pointers[819], &pointers[820], &pointers[821], &pointers[822], &pointers[823], &pointers[824], &pointers[825], &pointers[826], &pointers[827], &pointers[828], &pointers[829], &pointers[830], &pointers[831], &pointers[832], &pointers[833], &pointers[834], &pointers[835], &pointers[836], &pointers[837], &pointers[838], &pointers[839], &pointers[840], &pointers[841], &pointers[842], &pointers[843], &pointers[844], &pointers[845], &pointers[846], &pointers[847], &pointers[848], &pointers[849], &pointers[850],
  &pointers[851], &pointers[852], &pointers[853], &pointers[854], &pointers[855], &pointers[856], &pointers[857], &pointers[858], &pointers[859], &pointers[860], &pointers[861], &pointers[862], &pointers[863], &pointers[864], &pointers[865], &pointers[866], &pointers[867], &pointers[868], &pointers[869], &pointers[870], &pointers[871], &pointers[872], &pointers[873], &pointers[874], &pointers[875], &pointers[876], &pointers[877], &pointers[878], &pointers[879], &pointers[880], &pointers[881], &pointers[882], &pointers[883], &pointers[884], &pointers[885], &pointers[886], &pointers[887], &pointers[888], &pointers[889], &pointers[890], &pointers[891], &pointers[892], &pointers[893], &pointers[894], &pointers[895], &pointers[896], &pointers[897], &pointers[898], &pointers[899], &pointers[900],
  &pointers[901], &pointers[902], &pointers[903], &pointers[904], &pointers[905], &pointers[906], &pointers[907], &pointers[908], &pointers[909], &pointers[910], &pointers[911], &pointers[912], &pointers[913], &pointers[914], &pointers[915], &pointers[916], &pointers[917], &pointers[918], &pointers[919], &pointers[920], &pointers[921], &pointers[922], &pointers[923], &pointers[924], &pointers[925], &pointers[926], &pointers[927], &pointers[928], &pointers[929], &pointers[930], &pointers[931], &pointers[932], &pointers[933], &pointers[934], &pointers[935], &pointers[936], &pointers[937], &pointers[938], &pointers[939], &pointers[940], &pointers[941], &pointers[942], &pointers[943], &pointers[944], &pointers[945], &pointers[946], &pointers[947], &pointers[948], &pointers[949], &pointers[950],
  &pointers[951], &pointers[952], &pointers[953], &pointers[954], &pointers[955], &pointers[956], &pointers[957], &pointers[958], &pointers[959], &pointers[960], &pointers[961], &pointers[962], &pointers[963], &pointers[964],
  &pointers[965], &pointers[966], &pointers[967], &pointers[968], &pointers[969],
  &pointers[970], &pointers[971], &pointers[972], &pointers[973], &pointers[974],
  &pointers[975], &pointers[976], &pointers[977], &pointers[978], &pointers[979],
  &pointers[980], &pointers[981], &pointers[982], &pointers[983], &pointers[984],
  &pointers[985], &pointers[986], &pointers[987], &pointers[988], &pointers[989],
  &pointers[990], &pointers[991], &pointers[992], &pointers[993], &pointers[994],
  &pointers[995], &pointers[996], &pointers[997], &pointers[998], &pointers[999], NULL};


void pointer_chase_flash(void ** p0){

    void **this_pp = p0;
    for(int i = 0;i<1000;i++){
      while(this_pp){
        this_pp = *this_pp;
      }
      this_pp = p0;
    }
}

void pointer_chase_ccm(void ** p0){

    void **this_pp = p0;
    for(int i = 0;i<1000;i++){
      while(this_pp){
        this_pp = *this_pp;
      }
      this_pp = p0;
    }
}


void pointer_chase_ram(void ** p0){

    void **this_pp = p0;
    for(int i = 0;i<1000;i++){
      while(this_pp){
        this_pp = *this_pp;
      }
      this_pp = p0;
    }
}

void pointer_chase_ram2(void ** p0){

    void **this_pp = p0;
    for(int i = 0;i<1000;i++){
      while(this_pp){
        this_pp = *this_pp;
      }
      this_pp = p0;
    }
}
void pointer_main()
{
  pointer_chase_flash(&(pointers[0]));
}

void pointer_main_ccm()
{
  pointer_chase_ccm(&(pointers[0]));
}

void pointer_main_ram()
{
  pointer_chase_ram(&(pointers[0]));
}

void pointer_main_ram2()
{
  pointer_chase_ram2(&(pointers[0]));
}
