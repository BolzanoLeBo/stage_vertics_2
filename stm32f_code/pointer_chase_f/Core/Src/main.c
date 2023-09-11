/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */


/*data size*/
#define POINTER_SIZE_1000


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN PV */



void pointer_chase_flash(void ** p0){
    void **this_pp = p0;
    for(int i = 0;i<1000;i++){
      while(this_pp){
        this_pp = *this_pp;
      }
      this_pp = p0;
    }
}
void pointer_chase_ccm(void ** p0) __attribute__((section(".ccmram"))) ;

void pointer_chase_ccm(void ** p0){
    void **this_pp = p0;
    for(int i = 0;i<1000;i++){
      while(this_pp){
        this_pp = *this_pp;
      }
      this_pp = p0;
    }
}







/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */
//change SYSCLK source to PLL
void change_to_PLL();
//used to seperate code executions
void Sleep(int time);
//change the PLL output frequency
void change_freq(int mul);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */




__attribute__((section(".ccmramdata")))void * pointers_ccm[1000] = {
  &pointers_ccm[1], &pointers_ccm[2], &pointers_ccm[3], &pointers_ccm[4], &pointers_ccm[5], &pointers_ccm[6], &pointers_ccm[7], &pointers_ccm[8], &pointers_ccm[9], &pointers_ccm[10], &pointers_ccm[11], &pointers_ccm[12], &pointers_ccm[13], &pointers_ccm[14], &pointers_ccm[15], &pointers_ccm[16], &pointers_ccm[17], &pointers_ccm[18], &pointers_ccm[19], &pointers_ccm[20], &pointers_ccm[21], &pointers_ccm[22], &pointers_ccm[23], &pointers_ccm[24], &pointers_ccm[25], &pointers_ccm[26], &pointers_ccm[27], &pointers_ccm[28], &pointers_ccm[29], &pointers_ccm[30], &pointers_ccm[31], &pointers_ccm[32], &pointers_ccm[33], &pointers_ccm[34], &pointers_ccm[35], &pointers_ccm[36], &pointers_ccm[37], &pointers_ccm[38], &pointers_ccm[39], &pointers_ccm[40], &pointers_ccm[41], &pointers_ccm[42], &pointers_ccm[43], &pointers_ccm[44], &pointers_ccm[45], &pointers_ccm[46], &pointers_ccm[47], &pointers_ccm[48], &pointers_ccm[49], &pointers_ccm[50],
  &pointers_ccm[51], &pointers_ccm[52], &pointers_ccm[53], &pointers_ccm[54], &pointers_ccm[55], &pointers_ccm[56], &pointers_ccm[57], &pointers_ccm[58], &pointers_ccm[59], &pointers_ccm[60], &pointers_ccm[61], &pointers_ccm[62], &pointers_ccm[63], &pointers_ccm[64], &pointers_ccm[65], &pointers_ccm[66], &pointers_ccm[67], &pointers_ccm[68], &pointers_ccm[69], &pointers_ccm[70], &pointers_ccm[71], &pointers_ccm[72], &pointers_ccm[73], &pointers_ccm[74], &pointers_ccm[75], &pointers_ccm[76], &pointers_ccm[77], &pointers_ccm[78], &pointers_ccm[79], &pointers_ccm[80], &pointers_ccm[81], &pointers_ccm[82], &pointers_ccm[83], &pointers_ccm[84], &pointers_ccm[85], &pointers_ccm[86], &pointers_ccm[87], &pointers_ccm[88], &pointers_ccm[89], &pointers_ccm[90], &pointers_ccm[91], &pointers_ccm[92], &pointers_ccm[93], &pointers_ccm[94], &pointers_ccm[95], &pointers_ccm[96], &pointers_ccm[97], &pointers_ccm[98], &pointers_ccm[99], &pointers_ccm[100],
  &pointers_ccm[101], &pointers_ccm[102], &pointers_ccm[103], &pointers_ccm[104], &pointers_ccm[105], &pointers_ccm[106], &pointers_ccm[107], &pointers_ccm[108], &pointers_ccm[109], &pointers_ccm[110], &pointers_ccm[111], &pointers_ccm[112], &pointers_ccm[113], &pointers_ccm[114], &pointers_ccm[115], &pointers_ccm[116], &pointers_ccm[117], &pointers_ccm[118], &pointers_ccm[119], &pointers_ccm[120], &pointers_ccm[121], &pointers_ccm[122], &pointers_ccm[123], &pointers_ccm[124], &pointers_ccm[125], &pointers_ccm[126], &pointers_ccm[127], &pointers_ccm[128], &pointers_ccm[129], &pointers_ccm[130], &pointers_ccm[131], &pointers_ccm[132], &pointers_ccm[133], &pointers_ccm[134], &pointers_ccm[135], &pointers_ccm[136], &pointers_ccm[137], &pointers_ccm[138], &pointers_ccm[139], &pointers_ccm[140], &pointers_ccm[141], &pointers_ccm[142], &pointers_ccm[143], &pointers_ccm[144], &pointers_ccm[145], &pointers_ccm[146], &pointers_ccm[147], &pointers_ccm[148], &pointers_ccm[149], &pointers_ccm[150],
  &pointers_ccm[151], &pointers_ccm[152], &pointers_ccm[153], &pointers_ccm[154], &pointers_ccm[155], &pointers_ccm[156], &pointers_ccm[157], &pointers_ccm[158], &pointers_ccm[159], &pointers_ccm[160], &pointers_ccm[161], &pointers_ccm[162], &pointers_ccm[163], &pointers_ccm[164], &pointers_ccm[165], &pointers_ccm[166], &pointers_ccm[167], &pointers_ccm[168], &pointers_ccm[169], &pointers_ccm[170], &pointers_ccm[171], &pointers_ccm[172], &pointers_ccm[173], &pointers_ccm[174], &pointers_ccm[175], &pointers_ccm[176], &pointers_ccm[177], &pointers_ccm[178], &pointers_ccm[179], &pointers_ccm[180], &pointers_ccm[181], &pointers_ccm[182], &pointers_ccm[183], &pointers_ccm[184], &pointers_ccm[185], &pointers_ccm[186], &pointers_ccm[187], &pointers_ccm[188], &pointers_ccm[189], &pointers_ccm[190], &pointers_ccm[191], &pointers_ccm[192], &pointers_ccm[193], &pointers_ccm[194], &pointers_ccm[195], &pointers_ccm[196], &pointers_ccm[197], &pointers_ccm[198], &pointers_ccm[199], &pointers_ccm[200],
  &pointers_ccm[201], &pointers_ccm[202], &pointers_ccm[203], &pointers_ccm[204], &pointers_ccm[205], &pointers_ccm[206], &pointers_ccm[207], &pointers_ccm[208], &pointers_ccm[209], &pointers_ccm[210], &pointers_ccm[211], &pointers_ccm[212], &pointers_ccm[213], &pointers_ccm[214], &pointers_ccm[215], &pointers_ccm[216], &pointers_ccm[217], &pointers_ccm[218], &pointers_ccm[219], &pointers_ccm[220], &pointers_ccm[221], &pointers_ccm[222], &pointers_ccm[223], &pointers_ccm[224], &pointers_ccm[225], &pointers_ccm[226], &pointers_ccm[227], &pointers_ccm[228], &pointers_ccm[229], &pointers_ccm[230], &pointers_ccm[231], &pointers_ccm[232], &pointers_ccm[233], &pointers_ccm[234], &pointers_ccm[235], &pointers_ccm[236], &pointers_ccm[237], &pointers_ccm[238], &pointers_ccm[239], &pointers_ccm[240], &pointers_ccm[241], &pointers_ccm[242], &pointers_ccm[243], &pointers_ccm[244], &pointers_ccm[245], &pointers_ccm[246], &pointers_ccm[247], &pointers_ccm[248], &pointers_ccm[249], &pointers_ccm[250],
  &pointers_ccm[251], &pointers_ccm[252], &pointers_ccm[253], &pointers_ccm[254], &pointers_ccm[255], &pointers_ccm[256], &pointers_ccm[257], &pointers_ccm[258], &pointers_ccm[259], &pointers_ccm[260], &pointers_ccm[261], &pointers_ccm[262], &pointers_ccm[263], &pointers_ccm[264], &pointers_ccm[265], &pointers_ccm[266], &pointers_ccm[267], &pointers_ccm[268], &pointers_ccm[269], &pointers_ccm[270], &pointers_ccm[271], &pointers_ccm[272], &pointers_ccm[273], &pointers_ccm[274], &pointers_ccm[275], &pointers_ccm[276], &pointers_ccm[277], &pointers_ccm[278], &pointers_ccm[279], &pointers_ccm[280], &pointers_ccm[281], &pointers_ccm[282], &pointers_ccm[283], &pointers_ccm[284], &pointers_ccm[285], &pointers_ccm[286], &pointers_ccm[287], &pointers_ccm[288], &pointers_ccm[289], &pointers_ccm[290], &pointers_ccm[291], &pointers_ccm[292], &pointers_ccm[293], &pointers_ccm[294], &pointers_ccm[295], &pointers_ccm[296], &pointers_ccm[297], &pointers_ccm[298], &pointers_ccm[299], &pointers_ccm[300],
  &pointers_ccm[301], &pointers_ccm[302], &pointers_ccm[303], &pointers_ccm[304], &pointers_ccm[305], &pointers_ccm[306], &pointers_ccm[307], &pointers_ccm[308], &pointers_ccm[309], &pointers_ccm[310], &pointers_ccm[311], &pointers_ccm[312], &pointers_ccm[313], &pointers_ccm[314], &pointers_ccm[315], &pointers_ccm[316], &pointers_ccm[317], &pointers_ccm[318], &pointers_ccm[319], &pointers_ccm[320], &pointers_ccm[321], &pointers_ccm[322], &pointers_ccm[323], &pointers_ccm[324], &pointers_ccm[325], &pointers_ccm[326], &pointers_ccm[327], &pointers_ccm[328], &pointers_ccm[329], &pointers_ccm[330], &pointers_ccm[331], &pointers_ccm[332], &pointers_ccm[333], &pointers_ccm[334], &pointers_ccm[335], &pointers_ccm[336], &pointers_ccm[337], &pointers_ccm[338], &pointers_ccm[339], &pointers_ccm[340], &pointers_ccm[341], &pointers_ccm[342], &pointers_ccm[343], &pointers_ccm[344], &pointers_ccm[345], &pointers_ccm[346], &pointers_ccm[347], &pointers_ccm[348], &pointers_ccm[349], &pointers_ccm[350],
  &pointers_ccm[351], &pointers_ccm[352], &pointers_ccm[353], &pointers_ccm[354], &pointers_ccm[355], &pointers_ccm[356], &pointers_ccm[357], &pointers_ccm[358], &pointers_ccm[359], &pointers_ccm[360], &pointers_ccm[361], &pointers_ccm[362], &pointers_ccm[363], &pointers_ccm[364], &pointers_ccm[365], &pointers_ccm[366], &pointers_ccm[367], &pointers_ccm[368], &pointers_ccm[369], &pointers_ccm[370], &pointers_ccm[371], &pointers_ccm[372], &pointers_ccm[373], &pointers_ccm[374], &pointers_ccm[375], &pointers_ccm[376], &pointers_ccm[377], &pointers_ccm[378], &pointers_ccm[379], &pointers_ccm[380], &pointers_ccm[381], &pointers_ccm[382], &pointers_ccm[383], &pointers_ccm[384], &pointers_ccm[385], &pointers_ccm[386], &pointers_ccm[387], &pointers_ccm[388], &pointers_ccm[389], &pointers_ccm[390], &pointers_ccm[391], &pointers_ccm[392], &pointers_ccm[393], &pointers_ccm[394], &pointers_ccm[395], &pointers_ccm[396], &pointers_ccm[397], &pointers_ccm[398], &pointers_ccm[399], &pointers_ccm[400],
  &pointers_ccm[401], &pointers_ccm[402], &pointers_ccm[403], &pointers_ccm[404], &pointers_ccm[405], &pointers_ccm[406], &pointers_ccm[407], &pointers_ccm[408], &pointers_ccm[409], &pointers_ccm[410], &pointers_ccm[411], &pointers_ccm[412], &pointers_ccm[413], &pointers_ccm[414], &pointers_ccm[415], &pointers_ccm[416], &pointers_ccm[417], &pointers_ccm[418], &pointers_ccm[419], &pointers_ccm[420], &pointers_ccm[421], &pointers_ccm[422], &pointers_ccm[423], &pointers_ccm[424], &pointers_ccm[425], &pointers_ccm[426], &pointers_ccm[427], &pointers_ccm[428], &pointers_ccm[429], &pointers_ccm[430], &pointers_ccm[431], &pointers_ccm[432], &pointers_ccm[433], &pointers_ccm[434], &pointers_ccm[435], &pointers_ccm[436], &pointers_ccm[437], &pointers_ccm[438], &pointers_ccm[439], &pointers_ccm[440], &pointers_ccm[441], &pointers_ccm[442], &pointers_ccm[443], &pointers_ccm[444], &pointers_ccm[445], &pointers_ccm[446], &pointers_ccm[447], &pointers_ccm[448], &pointers_ccm[449], &pointers_ccm[450],
  &pointers_ccm[451], &pointers_ccm[452], &pointers_ccm[453], &pointers_ccm[454], &pointers_ccm[455], &pointers_ccm[456], &pointers_ccm[457], &pointers_ccm[458], &pointers_ccm[459], &pointers_ccm[460], &pointers_ccm[461], &pointers_ccm[462], &pointers_ccm[463], &pointers_ccm[464], &pointers_ccm[465], &pointers_ccm[466], &pointers_ccm[467], &pointers_ccm[468], &pointers_ccm[469], &pointers_ccm[470], &pointers_ccm[471], &pointers_ccm[472], &pointers_ccm[473], &pointers_ccm[474], &pointers_ccm[475], &pointers_ccm[476], &pointers_ccm[477], &pointers_ccm[478], &pointers_ccm[479], &pointers_ccm[480], &pointers_ccm[481], &pointers_ccm[482], &pointers_ccm[483], &pointers_ccm[484], &pointers_ccm[485], &pointers_ccm[486], &pointers_ccm[487], &pointers_ccm[488], &pointers_ccm[489], &pointers_ccm[490], &pointers_ccm[491], &pointers_ccm[492], &pointers_ccm[493], &pointers_ccm[494], &pointers_ccm[495], &pointers_ccm[496], &pointers_ccm[497], &pointers_ccm[498], &pointers_ccm[499], &pointers_ccm[500],
  &pointers_ccm[501], &pointers_ccm[502], &pointers_ccm[503], &pointers_ccm[504], &pointers_ccm[505], &pointers_ccm[506], &pointers_ccm[507], &pointers_ccm[508], &pointers_ccm[509], &pointers_ccm[510], &pointers_ccm[511], &pointers_ccm[512], &pointers_ccm[513], &pointers_ccm[514], &pointers_ccm[515], &pointers_ccm[516], &pointers_ccm[517], &pointers_ccm[518], &pointers_ccm[519], &pointers_ccm[520], &pointers_ccm[521], &pointers_ccm[522], &pointers_ccm[523], &pointers_ccm[524], &pointers_ccm[525], &pointers_ccm[526], &pointers_ccm[527], &pointers_ccm[528], &pointers_ccm[529], &pointers_ccm[530], &pointers_ccm[531], &pointers_ccm[532], &pointers_ccm[533], &pointers_ccm[534], &pointers_ccm[535], &pointers_ccm[536], &pointers_ccm[537], &pointers_ccm[538], &pointers_ccm[539], &pointers_ccm[540], &pointers_ccm[541], &pointers_ccm[542], &pointers_ccm[543], &pointers_ccm[544], &pointers_ccm[545], &pointers_ccm[546], &pointers_ccm[547], &pointers_ccm[548], &pointers_ccm[549], &pointers_ccm[550],
  &pointers_ccm[551], &pointers_ccm[552], &pointers_ccm[553], &pointers_ccm[554], &pointers_ccm[555], &pointers_ccm[556], &pointers_ccm[557], &pointers_ccm[558], &pointers_ccm[559], &pointers_ccm[560], &pointers_ccm[561], &pointers_ccm[562], &pointers_ccm[563], &pointers_ccm[564], &pointers_ccm[565], &pointers_ccm[566], &pointers_ccm[567], &pointers_ccm[568], &pointers_ccm[569], &pointers_ccm[570], &pointers_ccm[571], &pointers_ccm[572], &pointers_ccm[573], &pointers_ccm[574], &pointers_ccm[575], &pointers_ccm[576], &pointers_ccm[577], &pointers_ccm[578], &pointers_ccm[579], &pointers_ccm[580], &pointers_ccm[581], &pointers_ccm[582], &pointers_ccm[583], &pointers_ccm[584], &pointers_ccm[585], &pointers_ccm[586], &pointers_ccm[587], &pointers_ccm[588], &pointers_ccm[589], &pointers_ccm[590], &pointers_ccm[591], &pointers_ccm[592], &pointers_ccm[593], &pointers_ccm[594], &pointers_ccm[595], &pointers_ccm[596], &pointers_ccm[597], &pointers_ccm[598], &pointers_ccm[599], &pointers_ccm[600],
  &pointers_ccm[601], &pointers_ccm[602], &pointers_ccm[603], &pointers_ccm[604], &pointers_ccm[605], &pointers_ccm[606], &pointers_ccm[607], &pointers_ccm[608], &pointers_ccm[609], &pointers_ccm[610], &pointers_ccm[611], &pointers_ccm[612], &pointers_ccm[613], &pointers_ccm[614], &pointers_ccm[615], &pointers_ccm[616], &pointers_ccm[617], &pointers_ccm[618], &pointers_ccm[619], &pointers_ccm[620], &pointers_ccm[621], &pointers_ccm[622], &pointers_ccm[623], &pointers_ccm[624], &pointers_ccm[625], &pointers_ccm[626], &pointers_ccm[627], &pointers_ccm[628], &pointers_ccm[629], &pointers_ccm[630], &pointers_ccm[631], &pointers_ccm[632], &pointers_ccm[633], &pointers_ccm[634], &pointers_ccm[635], &pointers_ccm[636], &pointers_ccm[637], &pointers_ccm[638], &pointers_ccm[639], &pointers_ccm[640], &pointers_ccm[641], &pointers_ccm[642], &pointers_ccm[643], &pointers_ccm[644], &pointers_ccm[645], &pointers_ccm[646], &pointers_ccm[647], &pointers_ccm[648], &pointers_ccm[649], &pointers_ccm[650],
  &pointers_ccm[651], &pointers_ccm[652], &pointers_ccm[653], &pointers_ccm[654], &pointers_ccm[655], &pointers_ccm[656], &pointers_ccm[657], &pointers_ccm[658], &pointers_ccm[659], &pointers_ccm[660], &pointers_ccm[661], &pointers_ccm[662], &pointers_ccm[663], &pointers_ccm[664], &pointers_ccm[665], &pointers_ccm[666], &pointers_ccm[667], &pointers_ccm[668], &pointers_ccm[669], &pointers_ccm[670], &pointers_ccm[671], &pointers_ccm[672], &pointers_ccm[673], &pointers_ccm[674], &pointers_ccm[675], &pointers_ccm[676], &pointers_ccm[677], &pointers_ccm[678], &pointers_ccm[679], &pointers_ccm[680], &pointers_ccm[681], &pointers_ccm[682], &pointers_ccm[683], &pointers_ccm[684], &pointers_ccm[685], &pointers_ccm[686], &pointers_ccm[687], &pointers_ccm[688], &pointers_ccm[689], &pointers_ccm[690], &pointers_ccm[691], &pointers_ccm[692], &pointers_ccm[693], &pointers_ccm[694], &pointers_ccm[695], &pointers_ccm[696], &pointers_ccm[697], &pointers_ccm[698], &pointers_ccm[699], &pointers_ccm[700],
  &pointers_ccm[701], &pointers_ccm[702], &pointers_ccm[703], &pointers_ccm[704], &pointers_ccm[705], &pointers_ccm[706], &pointers_ccm[707], &pointers_ccm[708], &pointers_ccm[709], &pointers_ccm[710], &pointers_ccm[711], &pointers_ccm[712], &pointers_ccm[713], &pointers_ccm[714], &pointers_ccm[715], &pointers_ccm[716], &pointers_ccm[717], &pointers_ccm[718], &pointers_ccm[719], &pointers_ccm[720], &pointers_ccm[721], &pointers_ccm[722], &pointers_ccm[723], &pointers_ccm[724], &pointers_ccm[725], &pointers_ccm[726], &pointers_ccm[727], &pointers_ccm[728], &pointers_ccm[729], &pointers_ccm[730], &pointers_ccm[731], &pointers_ccm[732], &pointers_ccm[733], &pointers_ccm[734], &pointers_ccm[735], &pointers_ccm[736], &pointers_ccm[737], &pointers_ccm[738], &pointers_ccm[739], &pointers_ccm[740], &pointers_ccm[741], &pointers_ccm[742], &pointers_ccm[743], &pointers_ccm[744], &pointers_ccm[745], &pointers_ccm[746], &pointers_ccm[747], &pointers_ccm[748], &pointers_ccm[749], &pointers_ccm[750],
  &pointers_ccm[751], &pointers_ccm[752], &pointers_ccm[753], &pointers_ccm[754], &pointers_ccm[755], &pointers_ccm[756], &pointers_ccm[757], &pointers_ccm[758], &pointers_ccm[759], &pointers_ccm[760], &pointers_ccm[761], &pointers_ccm[762], &pointers_ccm[763], &pointers_ccm[764], &pointers_ccm[765], &pointers_ccm[766], &pointers_ccm[767], &pointers_ccm[768], &pointers_ccm[769], &pointers_ccm[770], &pointers_ccm[771], &pointers_ccm[772], &pointers_ccm[773], &pointers_ccm[774], &pointers_ccm[775], &pointers_ccm[776], &pointers_ccm[777], &pointers_ccm[778], &pointers_ccm[779], &pointers_ccm[780], &pointers_ccm[781], &pointers_ccm[782], &pointers_ccm[783], &pointers_ccm[784], &pointers_ccm[785], &pointers_ccm[786], &pointers_ccm[787], &pointers_ccm[788], &pointers_ccm[789], &pointers_ccm[790], &pointers_ccm[791], &pointers_ccm[792], &pointers_ccm[793], &pointers_ccm[794], &pointers_ccm[795], &pointers_ccm[796], &pointers_ccm[797], &pointers_ccm[798], &pointers_ccm[799], &pointers_ccm[800],
  &pointers_ccm[801], &pointers_ccm[802], &pointers_ccm[803], &pointers_ccm[804], &pointers_ccm[805], &pointers_ccm[806], &pointers_ccm[807], &pointers_ccm[808], &pointers_ccm[809], &pointers_ccm[810], &pointers_ccm[811], &pointers_ccm[812], &pointers_ccm[813], &pointers_ccm[814], &pointers_ccm[815], &pointers_ccm[816], &pointers_ccm[817], &pointers_ccm[818], &pointers_ccm[819], &pointers_ccm[820], &pointers_ccm[821], &pointers_ccm[822], &pointers_ccm[823], &pointers_ccm[824], &pointers_ccm[825], &pointers_ccm[826], &pointers_ccm[827], &pointers_ccm[828], &pointers_ccm[829], &pointers_ccm[830], &pointers_ccm[831], &pointers_ccm[832], &pointers_ccm[833], &pointers_ccm[834], &pointers_ccm[835], &pointers_ccm[836], &pointers_ccm[837], &pointers_ccm[838], &pointers_ccm[839], &pointers_ccm[840], &pointers_ccm[841], &pointers_ccm[842], &pointers_ccm[843], &pointers_ccm[844], &pointers_ccm[845], &pointers_ccm[846], &pointers_ccm[847], &pointers_ccm[848], &pointers_ccm[849], &pointers_ccm[850],
  &pointers_ccm[851], &pointers_ccm[852], &pointers_ccm[853], &pointers_ccm[854], &pointers_ccm[855], &pointers_ccm[856], &pointers_ccm[857], &pointers_ccm[858], &pointers_ccm[859], &pointers_ccm[860], &pointers_ccm[861], &pointers_ccm[862], &pointers_ccm[863], &pointers_ccm[864], &pointers_ccm[865], &pointers_ccm[866], &pointers_ccm[867], &pointers_ccm[868], &pointers_ccm[869], &pointers_ccm[870], &pointers_ccm[871], &pointers_ccm[872], &pointers_ccm[873], &pointers_ccm[874], &pointers_ccm[875], &pointers_ccm[876], &pointers_ccm[877], &pointers_ccm[878], &pointers_ccm[879], &pointers_ccm[880], &pointers_ccm[881], &pointers_ccm[882], &pointers_ccm[883], &pointers_ccm[884], &pointers_ccm[885], &pointers_ccm[886], &pointers_ccm[887], &pointers_ccm[888], &pointers_ccm[889], &pointers_ccm[890], &pointers_ccm[891], &pointers_ccm[892], &pointers_ccm[893], &pointers_ccm[894], &pointers_ccm[895], &pointers_ccm[896], &pointers_ccm[897], &pointers_ccm[898], &pointers_ccm[899], &pointers_ccm[900],
  &pointers_ccm[901], &pointers_ccm[902], &pointers_ccm[903], &pointers_ccm[904], &pointers_ccm[905], &pointers_ccm[906], &pointers_ccm[907], &pointers_ccm[908], &pointers_ccm[909], &pointers_ccm[910], &pointers_ccm[911], &pointers_ccm[912], &pointers_ccm[913], &pointers_ccm[914], &pointers_ccm[915], &pointers_ccm[916], &pointers_ccm[917], &pointers_ccm[918], &pointers_ccm[919], &pointers_ccm[920], &pointers_ccm[921], &pointers_ccm[922], &pointers_ccm[923], &pointers_ccm[924], &pointers_ccm[925], &pointers_ccm[926], &pointers_ccm[927], &pointers_ccm[928], &pointers_ccm[929], &pointers_ccm[930], &pointers_ccm[931], &pointers_ccm[932], &pointers_ccm[933], &pointers_ccm[934], &pointers_ccm[935], &pointers_ccm[936], &pointers_ccm[937], &pointers_ccm[938], &pointers_ccm[939], &pointers_ccm[940], &pointers_ccm[941], &pointers_ccm[942], &pointers_ccm[943], &pointers_ccm[944], &pointers_ccm[945], &pointers_ccm[946], &pointers_ccm[947], &pointers_ccm[948], &pointers_ccm[949], &pointers_ccm[950],
  &pointers_ccm[951], &pointers_ccm[952], &pointers_ccm[953], &pointers_ccm[954], &pointers_ccm[955], &pointers_ccm[956], &pointers_ccm[957], &pointers_ccm[958], &pointers_ccm[959], &pointers_ccm[960], &pointers_ccm[961], &pointers_ccm[962], &pointers_ccm[963], &pointers_ccm[964], &pointers_ccm[965], &pointers_ccm[966], &pointers_ccm[967], &pointers_ccm[968], &pointers_ccm[969], &pointers_ccm[970], &pointers_ccm[971], &pointers_ccm[972], &pointers_ccm[973], &pointers_ccm[974], &pointers_ccm[975], &pointers_ccm[976], &pointers_ccm[977], &pointers_ccm[978], &pointers_ccm[979], &pointers_ccm[980], &pointers_ccm[981], &pointers_ccm[982], &pointers_ccm[983], &pointers_ccm[984], &pointers_ccm[985], &pointers_ccm[986], &pointers_ccm[987], &pointers_ccm[988], &pointers_ccm[989], &pointers_ccm[990], &pointers_ccm[991], &pointers_ccm[992], &pointers_ccm[993], &pointers_ccm[994], &pointers_ccm[995], &pointers_ccm[996], &pointers_ccm[997], &pointers_ccm[998], &pointers_ccm[999],
   NULL };

__attribute__((section(".data")))
void * pointers_ram[1000] = {
    &pointers_ram[1], &pointers_ram[2], &pointers_ram[3], &pointers_ram[4], &pointers_ram[5], &pointers_ram[6], &pointers_ram[7], &pointers_ram[8], &pointers_ram[9], &pointers_ram[10], &pointers_ram[11], &pointers_ram[12], &pointers_ram[13], &pointers_ram[14], &pointers_ram[15], &pointers_ram[16], &pointers_ram[17], &pointers_ram[18], &pointers_ram[19], &pointers_ram[20], &pointers_ram[21], &pointers_ram[22], &pointers_ram[23], &pointers_ram[24], &pointers_ram[25], &pointers_ram[26], &pointers_ram[27], &pointers_ram[28], &pointers_ram[29], &pointers_ram[30], &pointers_ram[31], &pointers_ram[32], &pointers_ram[33], &pointers_ram[34], &pointers_ram[35], &pointers_ram[36], &pointers_ram[37], &pointers_ram[38], &pointers_ram[39], &pointers_ram[40], &pointers_ram[41], &pointers_ram[42], &pointers_ram[43], &pointers_ram[44], &pointers_ram[45], &pointers_ram[46], &pointers_ram[47], &pointers_ram[48], &pointers_ram[49], &pointers_ram[50],
    &pointers_ram[51], &pointers_ram[52], &pointers_ram[53], &pointers_ram[54], &pointers_ram[55], &pointers_ram[56], &pointers_ram[57], &pointers_ram[58], &pointers_ram[59], &pointers_ram[60], &pointers_ram[61], &pointers_ram[62], &pointers_ram[63], &pointers_ram[64], &pointers_ram[65], &pointers_ram[66], &pointers_ram[67], &pointers_ram[68], &pointers_ram[69], &pointers_ram[70], &pointers_ram[71], &pointers_ram[72], &pointers_ram[73], &pointers_ram[74], &pointers_ram[75], &pointers_ram[76], &pointers_ram[77], &pointers_ram[78], &pointers_ram[79], &pointers_ram[80], &pointers_ram[81], &pointers_ram[82], &pointers_ram[83], &pointers_ram[84], &pointers_ram[85], &pointers_ram[86], &pointers_ram[87], &pointers_ram[88], &pointers_ram[89], &pointers_ram[90], &pointers_ram[91], &pointers_ram[92], &pointers_ram[93], &pointers_ram[94], &pointers_ram[95], &pointers_ram[96], &pointers_ram[97], &pointers_ram[98], &pointers_ram[99], &pointers_ram[100],
    &pointers_ram[101], &pointers_ram[102], &pointers_ram[103], &pointers_ram[104], &pointers_ram[105], &pointers_ram[106], &pointers_ram[107], &pointers_ram[108], &pointers_ram[109], &pointers_ram[110], &pointers_ram[111], &pointers_ram[112], &pointers_ram[113], &pointers_ram[114], &pointers_ram[115], &pointers_ram[116], &pointers_ram[117], &pointers_ram[118], &pointers_ram[119], &pointers_ram[120], &pointers_ram[121], &pointers_ram[122], &pointers_ram[123], &pointers_ram[124], &pointers_ram[125], &pointers_ram[126], &pointers_ram[127], &pointers_ram[128], &pointers_ram[129], &pointers_ram[130], &pointers_ram[131], &pointers_ram[132], &pointers_ram[133], &pointers_ram[134], &pointers_ram[135], &pointers_ram[136], &pointers_ram[137], &pointers_ram[138], &pointers_ram[139], &pointers_ram[140], &pointers_ram[141], &pointers_ram[142], &pointers_ram[143], &pointers_ram[144], &pointers_ram[145], &pointers_ram[146], &pointers_ram[147], &pointers_ram[148], &pointers_ram[149], &pointers_ram[150],
    &pointers_ram[151], &pointers_ram[152], &pointers_ram[153], &pointers_ram[154], &pointers_ram[155], &pointers_ram[156], &pointers_ram[157], &pointers_ram[158], &pointers_ram[159], &pointers_ram[160], &pointers_ram[161], &pointers_ram[162], &pointers_ram[163], &pointers_ram[164], &pointers_ram[165], &pointers_ram[166], &pointers_ram[167], &pointers_ram[168], &pointers_ram[169], &pointers_ram[170], &pointers_ram[171], &pointers_ram[172], &pointers_ram[173], &pointers_ram[174], &pointers_ram[175], &pointers_ram[176], &pointers_ram[177], &pointers_ram[178], &pointers_ram[179], &pointers_ram[180], &pointers_ram[181], &pointers_ram[182], &pointers_ram[183], &pointers_ram[184], &pointers_ram[185], &pointers_ram[186], &pointers_ram[187], &pointers_ram[188], &pointers_ram[189], &pointers_ram[190], &pointers_ram[191], &pointers_ram[192], &pointers_ram[193], &pointers_ram[194], &pointers_ram[195], &pointers_ram[196], &pointers_ram[197], &pointers_ram[198], &pointers_ram[199], &pointers_ram[200],
    &pointers_ram[201], &pointers_ram[202], &pointers_ram[203], &pointers_ram[204], &pointers_ram[205], &pointers_ram[206], &pointers_ram[207], &pointers_ram[208], &pointers_ram[209], &pointers_ram[210], &pointers_ram[211], &pointers_ram[212], &pointers_ram[213], &pointers_ram[214], &pointers_ram[215], &pointers_ram[216], &pointers_ram[217], &pointers_ram[218], &pointers_ram[219], &pointers_ram[220], &pointers_ram[221], &pointers_ram[222], &pointers_ram[223], &pointers_ram[224], &pointers_ram[225], &pointers_ram[226], &pointers_ram[227], &pointers_ram[228], &pointers_ram[229], &pointers_ram[230], &pointers_ram[231], &pointers_ram[232], &pointers_ram[233], &pointers_ram[234], &pointers_ram[235], &pointers_ram[236], &pointers_ram[237], &pointers_ram[238], &pointers_ram[239], &pointers_ram[240], &pointers_ram[241], &pointers_ram[242], &pointers_ram[243], &pointers_ram[244], &pointers_ram[245], &pointers_ram[246], &pointers_ram[247], &pointers_ram[248], &pointers_ram[249], &pointers_ram[250],
    &pointers_ram[251], &pointers_ram[252], &pointers_ram[253], &pointers_ram[254], &pointers_ram[255], &pointers_ram[256], &pointers_ram[257], &pointers_ram[258], &pointers_ram[259], &pointers_ram[260], &pointers_ram[261], &pointers_ram[262], &pointers_ram[263], &pointers_ram[264], &pointers_ram[265], &pointers_ram[266], &pointers_ram[267], &pointers_ram[268], &pointers_ram[269], &pointers_ram[270], &pointers_ram[271], &pointers_ram[272], &pointers_ram[273], &pointers_ram[274], &pointers_ram[275], &pointers_ram[276], &pointers_ram[277], &pointers_ram[278], &pointers_ram[279], &pointers_ram[280], &pointers_ram[281], &pointers_ram[282], &pointers_ram[283], &pointers_ram[284], &pointers_ram[285], &pointers_ram[286], &pointers_ram[287], &pointers_ram[288], &pointers_ram[289], &pointers_ram[290], &pointers_ram[291], &pointers_ram[292], &pointers_ram[293], &pointers_ram[294], &pointers_ram[295], &pointers_ram[296], &pointers_ram[297], &pointers_ram[298], &pointers_ram[299], &pointers_ram[300],
    &pointers_ram[301], &pointers_ram[302], &pointers_ram[303], &pointers_ram[304], &pointers_ram[305], &pointers_ram[306], &pointers_ram[307], &pointers_ram[308], &pointers_ram[309], &pointers_ram[310], &pointers_ram[311], &pointers_ram[312], &pointers_ram[313], &pointers_ram[314], &pointers_ram[315], &pointers_ram[316], &pointers_ram[317], &pointers_ram[318], &pointers_ram[319], &pointers_ram[320], &pointers_ram[321], &pointers_ram[322], &pointers_ram[323], &pointers_ram[324], &pointers_ram[325], &pointers_ram[326], &pointers_ram[327], &pointers_ram[328], &pointers_ram[329], &pointers_ram[330], &pointers_ram[331], &pointers_ram[332], &pointers_ram[333], &pointers_ram[334], &pointers_ram[335], &pointers_ram[336], &pointers_ram[337], &pointers_ram[338], &pointers_ram[339], &pointers_ram[340], &pointers_ram[341], &pointers_ram[342], &pointers_ram[343], &pointers_ram[344], &pointers_ram[345], &pointers_ram[346], &pointers_ram[347], &pointers_ram[348], &pointers_ram[349], &pointers_ram[350],
    &pointers_ram[351], &pointers_ram[352], &pointers_ram[353], &pointers_ram[354], &pointers_ram[355], &pointers_ram[356], &pointers_ram[357], &pointers_ram[358], &pointers_ram[359], &pointers_ram[360], &pointers_ram[361], &pointers_ram[362], &pointers_ram[363], &pointers_ram[364], &pointers_ram[365], &pointers_ram[366], &pointers_ram[367], &pointers_ram[368], &pointers_ram[369], &pointers_ram[370], &pointers_ram[371], &pointers_ram[372], &pointers_ram[373], &pointers_ram[374], &pointers_ram[375], &pointers_ram[376], &pointers_ram[377], &pointers_ram[378], &pointers_ram[379], &pointers_ram[380], &pointers_ram[381], &pointers_ram[382], &pointers_ram[383], &pointers_ram[384], &pointers_ram[385], &pointers_ram[386], &pointers_ram[387], &pointers_ram[388], &pointers_ram[389], &pointers_ram[390], &pointers_ram[391], &pointers_ram[392], &pointers_ram[393], &pointers_ram[394], &pointers_ram[395], &pointers_ram[396], &pointers_ram[397], &pointers_ram[398], &pointers_ram[399], &pointers_ram[400],
    &pointers_ram[401], &pointers_ram[402], &pointers_ram[403], &pointers_ram[404], &pointers_ram[405], &pointers_ram[406], &pointers_ram[407], &pointers_ram[408], &pointers_ram[409], &pointers_ram[410], &pointers_ram[411], &pointers_ram[412], &pointers_ram[413], &pointers_ram[414], &pointers_ram[415], &pointers_ram[416], &pointers_ram[417], &pointers_ram[418], &pointers_ram[419], &pointers_ram[420], &pointers_ram[421], &pointers_ram[422], &pointers_ram[423], &pointers_ram[424], &pointers_ram[425], &pointers_ram[426], &pointers_ram[427], &pointers_ram[428], &pointers_ram[429], &pointers_ram[430], &pointers_ram[431], &pointers_ram[432], &pointers_ram[433], &pointers_ram[434], &pointers_ram[435], &pointers_ram[436], &pointers_ram[437], &pointers_ram[438], &pointers_ram[439], &pointers_ram[440], &pointers_ram[441], &pointers_ram[442], &pointers_ram[443], &pointers_ram[444], &pointers_ram[445], &pointers_ram[446], &pointers_ram[447], &pointers_ram[448], &pointers_ram[449], &pointers_ram[450],
    &pointers_ram[451], &pointers_ram[452], &pointers_ram[453], &pointers_ram[454], &pointers_ram[455], &pointers_ram[456], &pointers_ram[457], &pointers_ram[458], &pointers_ram[459], &pointers_ram[460], &pointers_ram[461], &pointers_ram[462], &pointers_ram[463], &pointers_ram[464], &pointers_ram[465], &pointers_ram[466], &pointers_ram[467], &pointers_ram[468], &pointers_ram[469], &pointers_ram[470], &pointers_ram[471], &pointers_ram[472], &pointers_ram[473], &pointers_ram[474], &pointers_ram[475], &pointers_ram[476], &pointers_ram[477], &pointers_ram[478], &pointers_ram[479], &pointers_ram[480], &pointers_ram[481], &pointers_ram[482], &pointers_ram[483], &pointers_ram[484], &pointers_ram[485], &pointers_ram[486], &pointers_ram[487], &pointers_ram[488], &pointers_ram[489], &pointers_ram[490], &pointers_ram[491], &pointers_ram[492], &pointers_ram[493], &pointers_ram[494], &pointers_ram[495], &pointers_ram[496], &pointers_ram[497], &pointers_ram[498], &pointers_ram[499], &pointers_ram[500],
    &pointers_ram[501], &pointers_ram[502], &pointers_ram[503], &pointers_ram[504], &pointers_ram[505], &pointers_ram[506], &pointers_ram[507], &pointers_ram[508], &pointers_ram[509], &pointers_ram[510], &pointers_ram[511], &pointers_ram[512], &pointers_ram[513], &pointers_ram[514], &pointers_ram[515], &pointers_ram[516], &pointers_ram[517], &pointers_ram[518], &pointers_ram[519], &pointers_ram[520], &pointers_ram[521], &pointers_ram[522], &pointers_ram[523], &pointers_ram[524], &pointers_ram[525], &pointers_ram[526], &pointers_ram[527], &pointers_ram[528], &pointers_ram[529], &pointers_ram[530], &pointers_ram[531], &pointers_ram[532], &pointers_ram[533], &pointers_ram[534], &pointers_ram[535], &pointers_ram[536], &pointers_ram[537], &pointers_ram[538], &pointers_ram[539], &pointers_ram[540], &pointers_ram[541], &pointers_ram[542], &pointers_ram[543], &pointers_ram[544], &pointers_ram[545], &pointers_ram[546], &pointers_ram[547], &pointers_ram[548], &pointers_ram[549], &pointers_ram[550],
    &pointers_ram[551], &pointers_ram[552], &pointers_ram[553], &pointers_ram[554], &pointers_ram[555], &pointers_ram[556], &pointers_ram[557], &pointers_ram[558], &pointers_ram[559], &pointers_ram[560], &pointers_ram[561], &pointers_ram[562], &pointers_ram[563], &pointers_ram[564], &pointers_ram[565], &pointers_ram[566], &pointers_ram[567], &pointers_ram[568], &pointers_ram[569], &pointers_ram[570], &pointers_ram[571], &pointers_ram[572], &pointers_ram[573], &pointers_ram[574], &pointers_ram[575], &pointers_ram[576], &pointers_ram[577], &pointers_ram[578], &pointers_ram[579], &pointers_ram[580], &pointers_ram[581], &pointers_ram[582], &pointers_ram[583], &pointers_ram[584], &pointers_ram[585], &pointers_ram[586], &pointers_ram[587], &pointers_ram[588], &pointers_ram[589], &pointers_ram[590], &pointers_ram[591], &pointers_ram[592], &pointers_ram[593], &pointers_ram[594], &pointers_ram[595], &pointers_ram[596], &pointers_ram[597], &pointers_ram[598], &pointers_ram[599], &pointers_ram[600],
    &pointers_ram[601], &pointers_ram[602], &pointers_ram[603], &pointers_ram[604], &pointers_ram[605], &pointers_ram[606], &pointers_ram[607], &pointers_ram[608], &pointers_ram[609], &pointers_ram[610], &pointers_ram[611], &pointers_ram[612], &pointers_ram[613], &pointers_ram[614], &pointers_ram[615], &pointers_ram[616], &pointers_ram[617], &pointers_ram[618], &pointers_ram[619], &pointers_ram[620], &pointers_ram[621], &pointers_ram[622], &pointers_ram[623], &pointers_ram[624], &pointers_ram[625], &pointers_ram[626], &pointers_ram[627], &pointers_ram[628], &pointers_ram[629], &pointers_ram[630], &pointers_ram[631], &pointers_ram[632], &pointers_ram[633], &pointers_ram[634], &pointers_ram[635], &pointers_ram[636], &pointers_ram[637], &pointers_ram[638], &pointers_ram[639], &pointers_ram[640], &pointers_ram[641], &pointers_ram[642], &pointers_ram[643], &pointers_ram[644], &pointers_ram[645], &pointers_ram[646], &pointers_ram[647], &pointers_ram[648], &pointers_ram[649], &pointers_ram[650],
    &pointers_ram[651], &pointers_ram[652], &pointers_ram[653], &pointers_ram[654], &pointers_ram[655], &pointers_ram[656], &pointers_ram[657], &pointers_ram[658], &pointers_ram[659], &pointers_ram[660], &pointers_ram[661], &pointers_ram[662], &pointers_ram[663], &pointers_ram[664], &pointers_ram[665], &pointers_ram[666], &pointers_ram[667], &pointers_ram[668], &pointers_ram[669], &pointers_ram[670], &pointers_ram[671], &pointers_ram[672], &pointers_ram[673], &pointers_ram[674], &pointers_ram[675], &pointers_ram[676], &pointers_ram[677], &pointers_ram[678], &pointers_ram[679], &pointers_ram[680], &pointers_ram[681], &pointers_ram[682], &pointers_ram[683], &pointers_ram[684], &pointers_ram[685], &pointers_ram[686], &pointers_ram[687], &pointers_ram[688], &pointers_ram[689], &pointers_ram[690], &pointers_ram[691], &pointers_ram[692], &pointers_ram[693], &pointers_ram[694], &pointers_ram[695], &pointers_ram[696], &pointers_ram[697], &pointers_ram[698], &pointers_ram[699], &pointers_ram[700],
    &pointers_ram[701], &pointers_ram[702], &pointers_ram[703], &pointers_ram[704], &pointers_ram[705], &pointers_ram[706], &pointers_ram[707], &pointers_ram[708], &pointers_ram[709], &pointers_ram[710], &pointers_ram[711], &pointers_ram[712], &pointers_ram[713], &pointers_ram[714], &pointers_ram[715], &pointers_ram[716], &pointers_ram[717], &pointers_ram[718], &pointers_ram[719], &pointers_ram[720], &pointers_ram[721], &pointers_ram[722], &pointers_ram[723], &pointers_ram[724], &pointers_ram[725], &pointers_ram[726], &pointers_ram[727], &pointers_ram[728], &pointers_ram[729], &pointers_ram[730], &pointers_ram[731], &pointers_ram[732], &pointers_ram[733], &pointers_ram[734], &pointers_ram[735], &pointers_ram[736], &pointers_ram[737], &pointers_ram[738], &pointers_ram[739], &pointers_ram[740], &pointers_ram[741], &pointers_ram[742], &pointers_ram[743], &pointers_ram[744], &pointers_ram[745], &pointers_ram[746], &pointers_ram[747], &pointers_ram[748], &pointers_ram[749], &pointers_ram[750],
    &pointers_ram[751], &pointers_ram[752], &pointers_ram[753], &pointers_ram[754], &pointers_ram[755], &pointers_ram[756], &pointers_ram[757], &pointers_ram[758], &pointers_ram[759], &pointers_ram[760], &pointers_ram[761], &pointers_ram[762], &pointers_ram[763], &pointers_ram[764], &pointers_ram[765], &pointers_ram[766], &pointers_ram[767], &pointers_ram[768], &pointers_ram[769], &pointers_ram[770], &pointers_ram[771], &pointers_ram[772], &pointers_ram[773], &pointers_ram[774], &pointers_ram[775], &pointers_ram[776], &pointers_ram[777], &pointers_ram[778], &pointers_ram[779], &pointers_ram[780], &pointers_ram[781], &pointers_ram[782], &pointers_ram[783], &pointers_ram[784], &pointers_ram[785], &pointers_ram[786], &pointers_ram[787], &pointers_ram[788], &pointers_ram[789], &pointers_ram[790], &pointers_ram[791], &pointers_ram[792], &pointers_ram[793], &pointers_ram[794], &pointers_ram[795], &pointers_ram[796], &pointers_ram[797], &pointers_ram[798], &pointers_ram[799], &pointers_ram[800],
    &pointers_ram[801], &pointers_ram[802], &pointers_ram[803], &pointers_ram[804], &pointers_ram[805], &pointers_ram[806], &pointers_ram[807], &pointers_ram[808], &pointers_ram[809], &pointers_ram[810], &pointers_ram[811], &pointers_ram[812], &pointers_ram[813], &pointers_ram[814], &pointers_ram[815], &pointers_ram[816], &pointers_ram[817], &pointers_ram[818], &pointers_ram[819], &pointers_ram[820], &pointers_ram[821], &pointers_ram[822], &pointers_ram[823], &pointers_ram[824], &pointers_ram[825], &pointers_ram[826], &pointers_ram[827], &pointers_ram[828], &pointers_ram[829], &pointers_ram[830], &pointers_ram[831], &pointers_ram[832], &pointers_ram[833], &pointers_ram[834], &pointers_ram[835], &pointers_ram[836], &pointers_ram[837], &pointers_ram[838], &pointers_ram[839], &pointers_ram[840], &pointers_ram[841], &pointers_ram[842], &pointers_ram[843], &pointers_ram[844], &pointers_ram[845], &pointers_ram[846], &pointers_ram[847], &pointers_ram[848], &pointers_ram[849], &pointers_ram[850],
    &pointers_ram[851], &pointers_ram[852], &pointers_ram[853], &pointers_ram[854], &pointers_ram[855], &pointers_ram[856], &pointers_ram[857], &pointers_ram[858], &pointers_ram[859], &pointers_ram[860], &pointers_ram[861], &pointers_ram[862], &pointers_ram[863], &pointers_ram[864], &pointers_ram[865], &pointers_ram[866], &pointers_ram[867], &pointers_ram[868], &pointers_ram[869], &pointers_ram[870], &pointers_ram[871], &pointers_ram[872], &pointers_ram[873], &pointers_ram[874], &pointers_ram[875], &pointers_ram[876], &pointers_ram[877], &pointers_ram[878], &pointers_ram[879], &pointers_ram[880], &pointers_ram[881], &pointers_ram[882], &pointers_ram[883], &pointers_ram[884], &pointers_ram[885], &pointers_ram[886], &pointers_ram[887], &pointers_ram[888], &pointers_ram[889], &pointers_ram[890], &pointers_ram[891], &pointers_ram[892], &pointers_ram[893], &pointers_ram[894], &pointers_ram[895], &pointers_ram[896], &pointers_ram[897], &pointers_ram[898], &pointers_ram[899], &pointers_ram[900],
    &pointers_ram[901], &pointers_ram[902], &pointers_ram[903], &pointers_ram[904], &pointers_ram[905], &pointers_ram[906], &pointers_ram[907], &pointers_ram[908], &pointers_ram[909], &pointers_ram[910], &pointers_ram[911], &pointers_ram[912], &pointers_ram[913], &pointers_ram[914], &pointers_ram[915], &pointers_ram[916], &pointers_ram[917], &pointers_ram[918], &pointers_ram[919], &pointers_ram[920], &pointers_ram[921], &pointers_ram[922], &pointers_ram[923], &pointers_ram[924], &pointers_ram[925], &pointers_ram[926], &pointers_ram[927], &pointers_ram[928], &pointers_ram[929], &pointers_ram[930], &pointers_ram[931], &pointers_ram[932], &pointers_ram[933], &pointers_ram[934], &pointers_ram[935], &pointers_ram[936], &pointers_ram[937], &pointers_ram[938], &pointers_ram[939], &pointers_ram[940], &pointers_ram[941], &pointers_ram[942], &pointers_ram[943], &pointers_ram[944], &pointers_ram[945], &pointers_ram[946], &pointers_ram[947], &pointers_ram[948], &pointers_ram[949], &pointers_ram[950],
    &pointers_ram[951], &pointers_ram[952], &pointers_ram[953], &pointers_ram[954], &pointers_ram[955], &pointers_ram[956], &pointers_ram[957], &pointers_ram[958], &pointers_ram[959], &pointers_ram[960], &pointers_ram[961], &pointers_ram[962], &pointers_ram[963], &pointers_ram[964],
    &pointers_ram[965], &pointers_ram[966], &pointers_ram[967], &pointers_ram[968], &pointers_ram[969],
    &pointers_ram[970], &pointers_ram[971], &pointers_ram[972], &pointers_ram[973], &pointers_ram[974],
    &pointers_ram[975], &pointers_ram[976], &pointers_ram[977], &pointers_ram[978], &pointers_ram[979],
    &pointers_ram[980], &pointers_ram[981], &pointers_ram[982], &pointers_ram[983], &pointers_ram[984],
    &pointers_ram[985], &pointers_ram[986], &pointers_ram[987], &pointers_ram[988], &pointers_ram[989],
    &pointers_ram[990], &pointers_ram[991], &pointers_ram[992], &pointers_ram[993], &pointers_ram[994],
    &pointers_ram[995], &pointers_ram[996], &pointers_ram[997], &pointers_ram[998], &pointers_ram[999], NULL};


const void * const pointers[1000] = {
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


void tested_code()
{
  //code flash data flash
  pointer_chase_flash(&(pointers[0]));
  Sleep(200);
  //code ccm data flash
  pointer_chase_ccm(&(pointers[0]));
  Sleep(200);
  //code flash data ccm
  pointer_chase_flash(&(pointers_ccm[0]));
  Sleep(200);
  //code ccm data ccm
  pointer_chase_ccm(&(pointers_ccm[0]));
  Sleep(200);
  //code flash data ram
  pointer_chase_flash(&(pointers_ram[0]));
  Sleep(200);
  //code CCM data ram
  pointer_chase_ccm(&(pointers_ram[0]));
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /*Multiplicators for 24         48           72     MHz*/
  int mul[3] = {RCC_PLL_MUL3,RCC_PLL_MUL6,RCC_PLL_MUL9};
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  //wait for rtc ready
  while(HAL_RTC_GetState(&hrtc) != HAL_RTC_STATE_READY )
  {
    ;
  }
  for (int i = 0; i<3; i++)
  {
    change_freq(mul[i]);
    Sleep(500);

    tested_code();

    Sleep(500);
  }
  //Enter Stop mode
  HAL_SuspendTick();
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


  return 0;
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the WakeUp
  */
  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pins : PE2 PE3 PE4 PE5
                           PE6 PE7 PE8 PE9
                           PE10 PE11 PE12 PE13
                           PE14 PE15 PE0 PE1 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PC13 PC14 PC15 PC0
                           PC1 PC2 PC3 PC4
                           PC5 PC6 PC7 PC8
                           PC9 PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0
                          |GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PF9 PF10 PF2 PF4
                           PF6 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_2|GPIO_PIN_4
                          |GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7
                           PA8 PA9 PA10 PA11
                           PA12 PA13 PA14 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB12 PB13 PB14
                           PB15 PB3 PB4 PB5
                           PB6 PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD8 PD9 PD10 PD11
                           PD12 PD13 PD14 PD15
                           PD0 PD1 PD2 PD3
                           PD4 PD5 PD6 PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void change_to_PLL()
{
  int latency;
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  HAL_RCC_GetOscConfig(&RCC_OscInitStruct);

  //Re-enable HSE oscillator on PLL
  RCC_OscInitStruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState        = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLState    = RCC_PLL_ON;
  //RCC_OscInitStruct.PLL.PLLMUL      = RCC_PLL_MUL9;

  switch(RCC_OscInitStruct.PLL.PLLMUL)
  {
  case RCC_PLL_MUL3:
    latency = FLASH_LATENCY_0;
    break;
  case RCC_PLL_MUL6:
    latency = FLASH_LATENCY_1;
    break;
  case RCC_PLL_MUL9:
    latency = FLASH_LATENCY_2;
    break;
  default:
    latency = FLASH_LATENCY_0;
  }
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
  /* Initialization Error */
  Error_Handler();
  }

  //Select the PLL as SYSCLK source
  RCC_ClkInitStruct.ClockType       = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource    = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider  = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider  = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, latency) != HAL_OK)
  {

  /* Initialization Error */
  Error_Handler();
  }
  //Disable the HSI (not used)
  RCC_OscInitStruct.OscillatorType  = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState        = RCC_HSI_OFF;
  RCC_OscInitStruct.PLL.PLLState    = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
  //Initialization Error
  Error_Handler();
  }
}

void Sleep(int time)
{
  uint32_t counter = (uint32_t) ((float) time*2.5);/*divide by (16/40)*/

  HAL_SuspendTick();

  HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, counter, RTC_WAKEUPCLOCK_RTCCLK_DIV16);
  /* Enter sleep or stop mode */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  //HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
  /* Wake up*/
  HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
  HAL_ResumeTick();
  //When wake up from STOP Sysclk source is HSI
  change_to_PLL();
  /*int r = __HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK;
  int f = HAL_RCC_GetSysClockFreq();*/
}

void change_freq(int mul)
{
  int latency;
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* -1- Select HSE as system clock source to allow modification of the PLL configuration */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  switch(mul)
  {
  case RCC_PLL_MUL3:
    latency = FLASH_LATENCY_0;
    break;
  case RCC_PLL_MUL6:
    latency = FLASH_LATENCY_1;
    break;
  case RCC_PLL_MUL9:
    latency = FLASH_LATENCY_2;
    break;
  default:
    latency = FLASH_LATENCY_0;
  }
  /* -2- Enable HSE  Oscillator, select it as PLL source and finally activate the PLL */
  RCC_OscInitStruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState        = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLState    = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLMUL      = mul;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* -3- Select the PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType       = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource    = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider  = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider  = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, latency) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
