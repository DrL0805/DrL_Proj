#include "ui_display_common.h"

const uint8_t image_bw_battery_h[] = {
24,24,
0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x00, 0x00, /* scanline 2 */
0x00, 0x00, 0x00, /* scanline 3 */
0x00, 0x00, 0x00, /* scanline 4 */
0x00, 0x00, 0x00, /* scanline 5 */
0x00, 0x00, 0x00, /* scanline 6 */
0x00, 0x00, 0x00, /* scanline 7 */
0x1F, 0xFF, 0xE0, /* scanline 8 */
0x3F, 0xFF, 0xF0, /* scanline 9 */
0x30, 0x00, 0x30, /* scanline 10 */
0x30, 0x00, 0x3C, /* scanline 11 */
0x30, 0x00, 0x3C, /* scanline 12 */
0x30, 0x00, 0x3C, /* scanline 13 */
0x30, 0x00, 0x3C, /* scanline 14 */
0x30, 0x00, 0x30, /* scanline 15 */
0x3F, 0xFF, 0xF0, /* scanline 16 */
0x1F, 0xFF, 0xE0, /* scanline 17 */
0x00, 0x00, 0x00, /* scanline 18 */
0x00, 0x00, 0x00, /* scanline 19 */
0x00, 0x00, 0x00, /* scanline 20 */
0x00, 0x00, 0x00, /* scanline 21 */
0x00, 0x00, 0x00, /* scanline 22 */
0x00, 0x00, 0x00, /* scanline 23 */
0x00, 0x00, 0x00, /* scanline 24 */
};

const uint8_t image_bw_battery_s[] = {
24,24,
0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x00, 0x00, /* scanline 2 */
0x00, 0x3C, 0x00, /* scanline 3 */
0x00, 0x3C, 0x00, /* scanline 4 */
0x00, 0xFF, 0x00, /* scanline 5 */
0x01, 0xFF, 0x80, /* scanline 6 */
0x01, 0x81, 0x80, /* scanline 7 */
0x01, 0x81, 0x80, /* scanline 8 */
0x01, 0x81, 0x80, /* scanline 9 */
0x01, 0x81, 0x80, /* scanline 10 */
0x01, 0x81, 0x80, /* scanline 11 */
0x01, 0x81, 0x80, /* scanline 12 */
0x01, 0x81, 0x80, /* scanline 13 */
0x01, 0x81, 0x80, /* scanline 14 */
0x01, 0x81, 0x80, /* scanline 15 */
0x01, 0x81, 0x80, /* scanline 16 */
0x01, 0x81, 0x80, /* scanline 17 */
0x01, 0x81, 0x80, /* scanline 18 */
0x01, 0x81, 0x80, /* scanline 19 */
0x01, 0x81, 0x80, /* scanline 20 */
0x01, 0xFF, 0x80, /* scanline 21 */
0x00, 0xFF, 0x00, /* scanline 22 */
0x00, 0x00, 0x00, /* scanline 23 */
0x00, 0x00, 0x00, /* scanline 24 */
};




uint8_t UI_Common_GetPixelValue(uint8_t* picinfo,uint8_t info_x,uint8_t info_y)
{
	uint8_t TmpPixelValue;

    uint8_t x;
    uint8_t y;
    uint8_t image_length;
    uint8_t image_height;

    int pos = 0;
    
    x = info_x;
    y = info_y;
    image_length = picinfo[0];
    image_height = picinfo[1];

    pos=x+y*image_length;
    
    TmpPixelValue = picinfo[2+pos/2];
    
    if(pos%2==0)
    {
        TmpPixelValue = TmpPixelValue>>4;
    
    }
    else
    {
        TmpPixelValue =TmpPixelValue&0x0F;
    }
    
    
	return TmpPixelValue;
    
}


//返回低位有效数据 获取黑白图的点阵信息，并把白色指定为image_color,黑色指定为bg_color
uint8_t UI_Common_GetBWPixelValue(uint8_t* picinfo,uint8_t info_x,uint8_t info_y,uint8_t bg_color,uint8_t image_color)
{
	uint8_t TmpPixelValue;

    uint8_t x;
    uint8_t y;
    uint8_t image_length;
    uint8_t image_height;

    int pos = 0;
    int bit_pos = 0;

    
    x = info_x;
    y = info_y;
    image_length = picinfo[0];
    image_height = picinfo[1];


    pos=x+y*image_length;

    TmpPixelValue = picinfo[2+pos/8];
		
	bit_pos = pos%8;
    
    
    switch(bit_pos)
    {
        case 0:
            TmpPixelValue =TmpPixelValue&0x80;
            TmpPixelValue =TmpPixelValue>>7;
            break;
        case 1:
            TmpPixelValue =TmpPixelValue&0x40;
            TmpPixelValue =TmpPixelValue>>6;
            break;
        case 2:
            TmpPixelValue =TmpPixelValue&0x20;
            TmpPixelValue =TmpPixelValue>>5;
            break;
        case 3:
            TmpPixelValue =TmpPixelValue&0x10;
            TmpPixelValue =TmpPixelValue>>4;
            break;
        case 4:
            TmpPixelValue =TmpPixelValue&0x08;
            TmpPixelValue =TmpPixelValue>>3;
            break;
        case 5:
            TmpPixelValue =TmpPixelValue&0x04;
            TmpPixelValue =TmpPixelValue>>2;
            break;
        case 6:
            TmpPixelValue =TmpPixelValue&0x02;
            TmpPixelValue =TmpPixelValue>>1;
            break;
        case 7:
            TmpPixelValue =TmpPixelValue&0x01;
            //TmpPixelValue =TmpPixelValue;
            break;
        default:
            TmpPixelValue = 0;
            break;
    }

    if(TmpPixelValue==1)
        TmpPixelValue = image_color;
    else
        TmpPixelValue = bg_color;
        
    
	return TmpPixelValue;
    
}


/* 往某个像素点设置值 */
void UI_Common_SetPixelValue(uint8_t *lcdram,uint8_t info_x,uint8_t info_y, uint8_t PixelValue)
{

    uint8_t x;
    uint8_t y;
    uint8_t temp_value;
    uint8_t pos_value;

    int pos = 0;

    //如果为透明色不需要设置 返回
    if(PixelValue == APP_COLOR_TRANSLUCENT||info_x>=LCD_WIDTH||info_y>=LCD_HEIGHT)
        return;

    x = info_x;
    y = info_y;
    //取出原本位置的点，2个

    pos =x+y*176;
    temp_value=lcdram[pos/2];
    
    if(pos%2==0)
    {
        pos_value = PixelValue<<4;
        temp_value = temp_value&0x0F|pos_value;
    
    }
    else
    {
        pos_value = PixelValue;
        temp_value = temp_value&0xF0|pos_value;
    }

    lcdram[pos/2]=temp_value;

}



/*整屏画图      参数x，y没有使用 */
void UI_Common_AddFullPic(uint8_t *lcdram,uint8_t pic_x,uint8_t pic_y,uint8_t* picinfo)
{

    //uint8_t x;
    //uint8_t y;
    
	//RTT_DEBUG_printf(0,"Mid_Screen_AddFullPic\n");
	memcpy(lcdram, picinfo+2, RGB_LCD_RAM_LEN);
    
}



//图片信息加入到显示区域
void UI_Common_AddPic(uint8_t *lcdram,uint8_t pic_x,uint8_t pic_y,uint8_t* picinfo)
{
    ui_common_pic_info_s image_info;
    int i=0;
    int j=0;


    image_info.offset_x = pic_x;
    image_info.offset_y = pic_y;
    image_info.width = picinfo[0];
    image_info.height = picinfo[1];
    

    for(i=0;i<image_info.width;i++)
    {
        for(j=0;j<image_info.height;j++)
        {
             UI_Common_SetPixelValue(lcdram,image_info.offset_x+i,image_info.offset_y+j,UI_Common_GetPixelValue(picinfo,i,j));
        }
    }

    
}



//图片信息加入到显示区域
void UI_Common_AddBWsourcePic(uint8_t *lcdram,int pic_x,int pic_y,uint8_t* picinfo,int8_t bg_color,int8_t image_color)
{
    ui_common_pic_info_s image_info;
    int i=0;
    int j=0;


    image_info.offset_x = pic_x;
    image_info.offset_y = pic_y;
    image_info.width = picinfo[0];
    image_info.height = picinfo[1];
    
    //RTT_DEBUG_printf(0,"App_AddPic:  x=%d,y=%d,w=%d,h=%d\n", pic_x,pic_y,image_info.length,image_info.height);
    
    for(j=0;j<image_info.height;j++)
    {
        for(i=0;i<image_info.width;i++)
        {
              if(image_info.offset_x+i<LCD_WIDTH && image_info.offset_y+j<LCD_HEIGHT&&image_info.offset_x+i>=0&& image_info.offset_y+j>=0)
             {
                 UI_Common_SetPixelValue(lcdram,image_info.offset_x+i,image_info.offset_y+j,UI_Common_GetBWPixelValue(picinfo,i,j,bg_color,image_color));
             }
        }
    }

    
}

void UI_Common_AddBWsourcePic_withoffsetx(uint8_t *lcdram,uint8_t pic_x,uint8_t pic_y,uint8_t* picinfo,uint8_t bg_color,uint8_t image_color,int offset)
{
    ui_common_pic_info_s image_info;
    int i=0;
    int j=0;


    image_info.offset_x = pic_x;
    image_info.offset_y = pic_y;
    image_info.width = picinfo[0];
    image_info.height = picinfo[1];
    
    //RTT_DEBUG_printf(0,"App_AddPic:  x=%d,y=%d,w=%d,h=%d\n", pic_x,pic_y,image_info.length,image_info.height);
    
    for(j=0;j<image_info.height;j++)
    {
        for(i=0;i<image_info.width-offset;i++)
        {
            if(image_info.offset_x+i<LCD_WIDTH && image_info.offset_y+j<LCD_HEIGHT)
            {
                UI_Common_SetPixelValue(lcdram,image_info.offset_x+i,image_info.offset_y+j,UI_Common_GetBWPixelValue(picinfo,i+offset,j,bg_color,image_color));
            }
        }
    }

    
}



//返回低位有效数据 获取黑白图的点阵信息，并把白色改为指定颜色（0-7）（0黑色 7白色）

uint8_t UI_Common_GetFontPixelValue(uint8_t* fontinfo,uint8_t info_x,uint8_t info_y,uint8_t bg_color,uint8_t font_color)
{
	uint8_t TmpPixelValue;

    uint8_t x;
    uint8_t y;
    uint8_t font_width;
    uint8_t font_height;

    int pos = 0;
    int bit_pos = 0;
    
    x = info_x;
    y = info_y;
    font_width = fontinfo[0];
    font_height = fontinfo[1];

    pos=x+y/8*font_width;

    TmpPixelValue = fontinfo[4+pos];

    bit_pos=y%8;
    
    switch(bit_pos)
    {
        case 0:
            TmpPixelValue =TmpPixelValue&0x01;
            //TmpPixelValue =TmpPixelValue;
            break;
        case 1:
            TmpPixelValue =TmpPixelValue&0x02;
            TmpPixelValue =TmpPixelValue>>1;
            break;
        case 2:
            TmpPixelValue =TmpPixelValue&0x04;
            TmpPixelValue =TmpPixelValue>>2;
            break;
        case 3:
            TmpPixelValue =TmpPixelValue&0x08;
            TmpPixelValue =TmpPixelValue>>3;
            break;
        case 4:
            TmpPixelValue =TmpPixelValue&0x10;
            TmpPixelValue =TmpPixelValue>>4;
            break;
        case 5:
            TmpPixelValue =TmpPixelValue&0x20;
            TmpPixelValue =TmpPixelValue>>5;
            break;
        case 6:
            TmpPixelValue =TmpPixelValue&0x40;
            TmpPixelValue =TmpPixelValue>>6;
            break;
        case 7:
            TmpPixelValue =TmpPixelValue&0x80;
            TmpPixelValue =TmpPixelValue>>7;
            break;
        default:
            TmpPixelValue = 0;
            break;
    }

    if(TmpPixelValue==1)
        TmpPixelValue = font_color;
    else
        TmpPixelValue = bg_color;
        
	return TmpPixelValue;
    
}


//字符信息加入到显示区域
void UI_Common_AddAsc2Font(uint8_t *lcdram,uint8_t pic_x,uint8_t pic_y,uint8_t* fontinfo,uint8_t bg_color,uint8_t font_color)
{
    ui_common_pic_info_s image_info;

    int i=0;
    int j=0;


    image_info.offset_x = pic_x;
    image_info.offset_y = pic_y;
    image_info.width = fontinfo[0];
    image_info.height = fontinfo[1];
    
    //RTT_DEBUG_printf(0,"App_AddPic:  x=%d,y=%d,w=%d,h=%d\n", pic_x,pic_y,image_info.length,image_info.height);
    for(j=0;j<image_info.height;j++)
    {
        for(i=0;i<image_info.width;i++)
        {
          UI_Common_SetPixelValue(lcdram,image_info.offset_x+i,image_info.offset_y+j,UI_Common_GetFontPixelValue(fontinfo,i,j,bg_color,font_color));
        }
    }

    
}


//图片信息加入到显示区域
void UI_Common_AddAsc2Str(uint8_t *lcdram,uint8_t pic_x,uint8_t pic_y,int8_t* string,int strlen,int font_size,uint8_t bg_color,uint8_t font_color)
{

    int i=0;
    //int j=0;
    int len=strlen;

    int x =pic_x;

    int asccode =0;
    
    uint8_t* fontinfo;
    

    for(i=0;i<len;i++)
    {
        asccode = string[i]-32;
        
        //RTT_DEBUG_printf(0,"App_AddAsc2Str---asccode=%d\n",asccode);
        
        if(font_size == 12)
        {
            fontinfo = (uint8_t*)AsciiInfo12BA_array[asccode];
        }
        else 
        {
            fontinfo = (uint8_t*)AsciiInfo16A_array[asccode];
        }
         
         UI_Common_AddAsc2Font(lcdram,x,pic_y, (uint8_t*)fontinfo,bg_color,font_color);
         x= x+fontinfo[2];
    }

    
}

//图片信息加入到显示区域
void UI_Common_GetAsc2Str_info(int8_t* string,int strlen,int font_size,int *str_width,int *str_height)
{

    int i=0;
    int len=strlen;
    int asccode =0;
    uint8_t* fontinfo;
    int x=0;//y=0;
    

    for(i=0;i<len;i++)
    {
        asccode = string[i]-32;
        
        if(font_size == 12)
        {
            fontinfo = (uint8_t*)AsciiInfo12BA_array[asccode];
        }
        else 
        {
            fontinfo = (uint8_t*)AsciiInfo16A_array[asccode];
        }
         
         x= x+fontinfo[2];
    }

    *str_width = x;
    if(font_size == 12)
    {
        *str_height=12;
    }
    else 
    {
        *str_height=16;
    }

}



//annulus 圆环 指定颜色或不改变原本底色 如果指定颜色为黑色，则不改变底色 暂定
void UI_Common_Draw_Annulus(uint8_t *lcdram,float x,float y,float Lr,float Sr,uint8_t color,bool is_solid)
{
    int i,j;

    float Lr2,Sr2,Sq;

    if(Sr>=Lr)
    {
        RTT_DEBUG_printf(0,"ERROR 0\n");
    }
    
    Lr2=Lr*Lr;
    Sr2=Sr*Sr;

    for(i=x-Lr;i<x+Lr;i++)
    {
        for(j=y-Lr;j<y+Lr;j++)
        {
            Sq= (i-x)*(i-x)+(j-y)*(j-y);

            if(Sq>Sr2&&Sq<=Lr2)
            {
                if(is_solid== FALSE&&!(j%2==0&&(i+j)%2==0))
                {
                    
                }
                else
                {
                    UI_Common_SetPixelValue(lcdram,i,j,color);
                }
            }
            else
            {
            }
        }
    }



}

void UI_Common_Draw_Circle(uint8_t *lcdram,float x,float y,float Lr,uint8_t color)
{

        int i,j;
        float Lr2,Sq;
    
        Lr2=Lr*Lr;
    
        for(i=x-Lr;i<x+Lr;i++)
        {
            for(j=y-Lr;j<y+Lr;j++)
                {
                    Sq= (i-x)*(i-x)+(j-y)*(j-y);
    
                    if(Sq<Lr2)
                    {
                        UI_Common_SetPixelValue(lcdram,i,j,color);
                    }
                    else
                    {
                        UI_Common_SetPixelValue(lcdram,i,j,APP_COLOR_TRANSLUCENT);
                    }
                }
        }
    
}



int ui_abs(int x)
{
	int x_temp = x;

	if (x < 0)
	{
		x_temp = 0- x;
	}
	return x_temp;
}

void UI_Common_Draw_Annulus_Byangle(uint8_t *lcdram,int x,int y,int Lr,int Sr,double s_angle,double e_angle,uint8_t color,bool is_solid)
{

    double a;
    double b;
    int i,j;
    int abs_a;
    int abs_b;
    float Lr2,Sr2,Sq;

    double tan;
    double temp_angle =0;
    double angle =0;

    int range = 0;
    

    if(Sr>=Lr)
    {
        RTT_DEBUG_printf(0,"ERROR 0\n");
        return;
    }
    
    if(s_angle>=e_angle)
    {
//        RTT_DEBUG_printf(0,"ERROR 1\n");
        return;
    }
    
    Lr2=Lr*Lr;
    Sr2=Sr*Sr;

    for(i=x-Lr;i<x+Lr;i++)
    {
        for(j=y-Lr;j<y+Lr;j++)
        {
            Sq= (i-x)*(i-x)+(j-y)*(j-y);

            if(Sq>Sr2&&Sq<Lr2)
            {
                if(is_solid== FALSE&&!(j%2==0&&(i+j)%2==0))
                {
                    //空心点，不需要处理
                }
                else
                {
                        a= i-x;
                        b= j-y;
                        abs_a=ui_abs(a);
                        abs_b=ui_abs(b);
                        
        
                        if(a<=0&&b>0)
                        {
                            range = 0;
                        }
                        else if(a<0&&b<=0)
                        {
                            range = 1;
                        }
                        else if(a>=0&&b<0)
                        {
                            range = 2;
                        }
                        else if(a>0&&b>=0)
                        {
                            range = 3;
                        }
                        
                        if(a == 0)
                        {
                            if(b>0)
                            {
                                angle = 0;
                            }
                            else 
                            {
                                angle = PI;
                            }
                        
                        }
                        else
                        {
        
                                if(abs_a>=abs_b)
                                {
                                    tan = (float)abs_b/(float)abs_a;
                                }
                                else
                                {
                                    tan = (float)abs_a/(float)abs_b;
                                }

                                
                                temp_angle = (float)Algorithm_arctan(tan);
        
                                angle = temp_angle;
                                
                                switch(range)
                                {
                                    case 0:
                                        if(abs_a>=abs_b)
                                        {
                                        angle = PI/2-temp_angle;
                                        }
                                        else
                                        {
                                        angle = temp_angle;
                                        }
                                        break;
                                    case 1:
                                        if(abs_a>=abs_b)
                                        {
                                        angle = PI/2+temp_angle;
                                        }
                                        else
                                        {
                                        angle = PI-temp_angle;
                                        }
                                        break;
                                    case 2:
                                        if(abs_a>=abs_b)
                                        {
                                        angle = PI+PI/2-temp_angle;
                                        }
                                        else
                                        {
                                        angle = PI+temp_angle;
                                        }
                                        break;
                                    case 3:
                                        if(abs_a>=abs_b)
                                        {
                                        angle = PI+PI/2+temp_angle;
                                        }
                                        else
                                        {
                                        angle = 2*PI-temp_angle;
                                        }
                                        break;
                                    default:
                                        angle = 0;
                                        break;
                                }
                                                                    }
                                //染色
                            if(angle>=s_angle&&angle<=e_angle)
                            {
                                UI_Common_SetPixelValue(lcdram,i,j,color);
                            }
                                
                     }
                }
            
            }
        }

}


//画横线 起点 长度 厚度 颜色 
void UI_Common_Draw_Hline(uint8_t *lcdram,int x,int y,int len,int breadth,uint8_t color,bool is_solid)
{
    int i,j;
    
    for(i=x;i<x+len;i++)
    {
        for(j=y;j<y+breadth;j++)
        {
            if(is_solid == FALSE)
            {
                if(breadth == 1)
                {
                    if(i%2==0)
                    UI_Common_SetPixelValue(lcdram,i,j,color);
                }
                else
                {
                    if(j%2==0&&i%2==0)
                    UI_Common_SetPixelValue(lcdram,i,j,color);
                }
                
            }
            else
            {
                UI_Common_SetPixelValue(lcdram,i,j,color);
            }
         }
    }


}
//画竖线 起点 长度 厚度 颜色 
void UI_Common_Draw_Vline(uint8_t *lcdram,int x,int y,int len,int breadth,uint8_t color,bool is_solid)
{
    int i,j;
    
    for(i=x;i<x+breadth;i++)
    {
        for(j=y;j<y+len;j++)
        {
            if(is_solid == FALSE)
            {
                if(j%2==0&&i%2==0)
                UI_Common_SetPixelValue(lcdram,i,j,color);
            }
            else
            {
                UI_Common_SetPixelValue(lcdram,i,j,color);
            }
         }
    }
}


uint8_t*  UI_Common_GetNumberImageInfo(int number,int type)
{

    uint8_t* fontinfo = NULL;

    if(type == 0)
    {
        switch(number)
        {
            case 0:
                fontinfo = (uint8_t*)font_tgl_32_0_h;
                break;
            case 1:
                fontinfo = (uint8_t*)font_tgl_32_1_h;
                break;
            case 2:
                fontinfo = (uint8_t*)font_tgl_32_2_h;
                break;
            case 3:
                fontinfo = (uint8_t*)font_tgl_32_3_h;
                break;
            case 4:
                fontinfo = (uint8_t*)font_tgl_32_4_h;
                break;
            case 5:
                fontinfo = (uint8_t*)font_tgl_32_5_h;
                break;
            case 6:
                fontinfo = (uint8_t*)font_tgl_32_6_h;
                break;
            case 7:
                fontinfo = (uint8_t*)font_tgl_32_7_h;
                break;
            case 8:
                fontinfo = (uint8_t*)font_tgl_32_8_h;
                break;
            case 9:
                fontinfo = (uint8_t*)font_tgl_32_9_h;
                break;
            default:
                break;
        }
    }
    else
    {
        switch(number)
        {
            case 0:
                fontinfo = (uint8_t*)font_tgl_48_0_h;
                break;
            case 1:
                fontinfo = (uint8_t*)font_tgl_48_1_h;
                break;
            case 2:
                fontinfo = (uint8_t*)font_tgl_48_2_h;
                break;
            case 3:
                fontinfo = (uint8_t*)font_tgl_48_3_h;
                break;
            case 4:
                fontinfo = (uint8_t*)font_tgl_48_4_h;
                break;
            case 5:
                fontinfo = (uint8_t*)font_tgl_48_5_h;
                break;
            case 6:
                fontinfo = (uint8_t*)font_tgl_48_6_h;
                break;
            case 7:
                fontinfo = (uint8_t*)font_tgl_48_7_h;
                break;
            case 8:
                fontinfo = (uint8_t*)font_tgl_48_8_h;
                break;
            case 9:
                fontinfo = (uint8_t*)font_tgl_48_9_h;
                break;
            default:
                break;
        }

    
    }
    
    return fontinfo;
    
}

void  UI_Common_GetNumberImageInfo_Bytype(int type,int* fontwidth,int* fontheight)
{
    
        switch(type)
        {
            case 0:
                *fontwidth=12;
                *fontheight=26;
                break;
            case 1:
                *fontwidth=24;
                *fontheight=48;
                break;
            default:
                *fontwidth=12;
                *fontheight=26;
                break;
        }
        
}


void UI_Common_Draw_Annulus_Progress(uint8_t *lcdram,int x,int y,int Lr,int Sr,uint8_t bg_color,uint8_t progress_color,int percent)
{
    float progress_angle;

    if(percent>100)
        percent = 100;

    progress_angle = ANNULUS_PROGRESS_MINANGLE + (4*percent*PI)/(3*100);

    UI_Common_Draw_Annulus_Byangle(lcdram,ANNULUS_PROGRESS_CENTERX,ANNULUS_PROGRESS_CENTERY,ANNULUS_PROGRESS_LR,ANNULUS_PROGRESS_SR,ANNULUS_PROGRESS_MINANGLE,ANNULUS_PROGRESS_MAXANGLE,bg_color,FALSE);
    UI_Common_Draw_Annulus_Byangle(lcdram,ANNULUS_PROGRESS_CENTERX,ANNULUS_PROGRESS_CENTERY,ANNULUS_PROGRESS_LR,ANNULUS_PROGRESS_SR,ANNULUS_PROGRESS_MINANGLE,progress_angle,progress_color,TRUE);

}


void UI_Common_Draw_NumberImage_textbox(uint8_t *lcdram,int box_x,int box_y,int box_w,int box_h,int type,uint8_t image_color,int number)
{
    int image_w=0,image_h=0;
    int offsetx =0,offsety =0;
    int image_count =0;
    int data[5];
    int i;
    uint8_t* fontinfo;

    UI_Common_GetNumberImageInfo_Bytype(0,&image_w,&image_h);
    if(image_w == 0||image_h == 0)
    {
        return;
    }
    
    if(number>=10000)
    {
        image_count = 5;
        data[0] = number/10000;
        data[1] = number%10000/1000;
        data[2] = number%1000/100;
        data[3] = number%100/10;
        data[4] = number%10;
    }
    else if(number>=1000)
    {

        image_count = 4;
        data[0] = number/1000;
        data[1] = number%1000/100;
        data[2] = number%100/10;
        data[3] = number%10;
        
    }
    else if(number>=100)
    {

        image_count = 3;
        data[0] = number/100;
        data[1] = number%100/10;
        data[2] = number%10;
    }
    else if(number>=10)
    {

        image_count = 2;
        data[0] = number/10;
        data[1] = number%10;
    }
    else
    {
        image_count = 1;
        data[0] = number;
    }

    offsetx =(box_w - image_w*image_count)/2;
    offsety =(box_h - image_h)/2;

    for(i=0;i<image_count;i++)
    {
        fontinfo = UI_Common_GetNumberImageInfo(data[i],type);
        UI_Common_AddBWsourcePic(lcdram,box_x+offsetx+image_w*i,box_y+offsety,(uint8_t*)fontinfo,APP_COLOR_BLACK,image_color);
    }


}

//void UI_Common_AddAsc2Str(uint8_t *lcdram,uint8_t pic_x,uint8_t pic_y,char* string,int strlen,int font_size,uint8_t bg_color,uint8_t font_color)

void UI_Common_Draw_AscStr_textbox(uint8_t *lcdram,int box_x,int box_y,int box_w,int box_h,int font_size,uint8_t font_color,char* string,int strlen,enum_textbox_display_type display_type)
{

    int offsetx =0,offsety =0;
    int str_width=0,str_height=0;

    
    //am_util_string_strcat
    UI_Common_GetAsc2Str_info((int8_t*)string,strlen,16,&str_width,&str_height);


    switch(display_type)
    {
        case ENUM_TEXTBOX_LEFT:
        {
            offsetx =0;
            offsety =(box_h - str_height)/2;
        }
        break;
        case ENUM_TEXTBOX_CENTER:
        {
            offsetx =(box_w - str_width)/2;
            offsety =(box_h - str_height)/2;
         }
        break;
        case ENUM_TEXTBOX_RIGHT:
        {
            offsetx = box_w - str_width;
            offsety =(box_h - str_height)/2;
         }
        break;
        default:
        break;
    }
    

    UI_Common_AddAsc2Str(lcdram,box_x+offsetx,box_y+offsety,(int8_t*)string,strlen,font_size,APP_COLOR_BLACK,font_color);

}

void UI_Common_Draw_FontStr_textbox(uint8_t *lcdram,int box_x,int box_y,int box_w,int box_h,uint8_t *fontinfo,uint8_t font_color,uint8_t bg_color)
{

    int offsetx =0,offsety =0;
    int font_width=0,font_height=0;

    font_width = fontinfo[0];
    font_height = fontinfo[1];
    offsetx =(box_w - font_width)/2;
    offsety =(box_h - font_height)/2;

    UI_Common_AddBWsourcePic(lcdram,box_x+offsetx,box_y+offsety,(uint8_t*)fontinfo,bg_color,font_color);

}

uint8_t* UI_Common_GetNumberImageInfo_Bychar(char data,int *width, int *height,int number_size)
{

    uint8_t* fontinfo = NULL;

    if(number_size == 26)
    {
        switch(data)
        {
            case '0':
                fontinfo = (uint8_t*)font_tgl_32_0_h;
                break;
            case '1':
                fontinfo = (uint8_t*)font_tgl_32_1_h;
                break;
            case '2':
                fontinfo = (uint8_t*)font_tgl_32_2_h;
                break;
            case '3':
                fontinfo = (uint8_t*)font_tgl_32_3_h;
                break;
            case '4':
                fontinfo = (uint8_t*)font_tgl_32_4_h;
                break;
            case '5':
                fontinfo = (uint8_t*)font_tgl_32_5_h;
                break;
            case '6':
                fontinfo = (uint8_t*)font_tgl_32_6_h;
                break;
            case '7':
                fontinfo = (uint8_t*)font_tgl_32_7_h;
                break;
            case '8':
                fontinfo = (uint8_t*)font_tgl_32_8_h;
                break;
            case '9':
                fontinfo = (uint8_t*)font_tgl_32_9_h;
                break;
            case '-':
                fontinfo = (uint8_t*)font_tgl_32_hyphen_h;
                break;
            case 'D':
                fontinfo = (uint8_t*)font_tgl_32_degree_h;
                break;                
            case 'C':
                fontinfo = (uint8_t*)font_tgl_32_celsius_h;
                break;                
            case 'h':
                fontinfo = (uint8_t*)font_tgl_32_h_h;
                break;                
            case 'm':
                fontinfo = (uint8_t*)font_tgl_32_m_h;
                break;                
            case 'A':
                fontinfo = (uint8_t*)font_tgl_32_a_cap_h;
                break;                
            case 'M':
                fontinfo = (uint8_t*)font_tgl_32_m_cap_h;
                break;                
            case 'P':
                fontinfo = (uint8_t*)font_tgl_32_p_cap_h;
                break;                
            case '.':
                fontinfo = (uint8_t*)font_tgl_32_conclusion_h;
                break;                
            case ' ':
                fontinfo = (uint8_t*)font_tgl_32_blank_h;
                break;                
            case ':':
                fontinfo = (uint8_t*)font_tgl_32_colon_h;
                break;                
            default:
                fontinfo = (uint8_t*)font_tgl_32_0_h;
                break;
        }
        }
        else if(number_size == 20)
        {
        switch(data)
        {
            case '0':
                fontinfo = (uint8_t*)font_tgl_24_0_h;
                break;
            case '1':
                fontinfo = (uint8_t*)font_tgl_24_1_h;
                break;
            case '2':
                fontinfo = (uint8_t*)font_tgl_24_2_h;
                break;
            case '3':
                fontinfo = (uint8_t*)font_tgl_24_3_h;
                break;
            case '4':
                fontinfo = (uint8_t*)font_tgl_24_4_h;
                break;
            case '5':
                fontinfo = (uint8_t*)font_tgl_24_5_h;
                break;
            case '6':
                fontinfo = (uint8_t*)font_tgl_24_6_h;
                break;
            case '7':
                fontinfo = (uint8_t*)font_tgl_24_7_h;
                break;
            case '8':
                fontinfo = (uint8_t*)font_tgl_24_8_h;
                break;
            case '9':
                fontinfo = (uint8_t*)font_tgl_24_9_h;
                break;
            case '-':
                fontinfo = (uint8_t*)font_tgl_24_hyphen_h;
                break;
            case '°':
                fontinfo = (uint8_t*)font_tgl_24_degree_h;
                break;                
            case 'C':
                fontinfo = (uint8_t*)font_tgl_24_celsius_h;
                break;                
            case 'h':
                fontinfo = (uint8_t*)font_tgl_24_h_h;
                break;                
            case 'm':
                fontinfo = (uint8_t*)font_tgl_24_m_h;
                break;                
            case 'A':
                fontinfo = (uint8_t*)font_tgl_24_a_cap_h;
                break;                
            case 'M':
                fontinfo = (uint8_t*)font_tgl_24_m_cap_h;
                break;                
            case 'P':
                fontinfo = (uint8_t*)font_tgl_24_p_cap_h;
                break;                
            case '.':
                fontinfo = (uint8_t*)font_tgl_24_conclusion_h;
                break;                
            case ':':
                fontinfo = (uint8_t*)font_tgl_24_colon_h;
                break;                
            case '\'':
                fontinfo = (uint8_t*)font_tgl_24_prime_h;
                break;                
            case '"':
                fontinfo = (uint8_t*)font_tgl_24_double_prime_h;
                break;                
            case ' ':
                fontinfo = (uint8_t*)font_tgl_24_blank_h;
                break;                
            default:
                fontinfo = (uint8_t*)font_tgl_24_0_h;
                break;
        }
        
     }
     else if(number_size == 36)
     {
            switch(data)
            {
                case '0':
                    fontinfo = (uint8_t*)font_tgl_36_0_h;
                    break;
                case '1':
                    fontinfo = (uint8_t*)font_tgl_36_1_h;
                    break;
                case '2':
                    fontinfo = (uint8_t*)font_tgl_36_2_h;
                    break;
                case '3':
                    fontinfo = (uint8_t*)font_tgl_36_3_h;
                    break;
                case '4':
                    fontinfo = (uint8_t*)font_tgl_36_4_h;
                    break;
                case '5':
                    fontinfo = (uint8_t*)font_tgl_36_5_h;
                    break;
                case '6':
                    fontinfo = (uint8_t*)font_tgl_36_6_h;
                    break;
                case '7':
                    fontinfo = (uint8_t*)font_tgl_36_7_h;
                    break;
                case '8':
                    fontinfo = (uint8_t*)font_tgl_36_8_h;
                    break;
                case '9':
                    fontinfo = (uint8_t*)font_tgl_36_9_h;
                    break;
                case '.':
                    fontinfo = (uint8_t*)font_tgl_36_conclusion_h;
                    break;                
                case ':':
                    fontinfo = (uint8_t*)font_tgl_36_colon_h;
                    break;                
                case '\'':
                    fontinfo = (uint8_t*)font_tgl_36_prime_h;
                    break;                
                case '"':
                    fontinfo = (uint8_t*)font_tgl_36_double_prime_h;
                    break;                
                default:
                    fontinfo = (uint8_t*)font_tgl_36_0_h;
                    break;
            }
        
    }
    else if(number_size == 48)
       {
           switch(data)
           {
               case '0':
                   fontinfo = (uint8_t*)font_tgl_48_0_h;
                   break;
               case '1':
                   fontinfo = (uint8_t*)font_tgl_48_1_h;
                   break;
               case '2':
                   fontinfo = (uint8_t*)font_tgl_48_2_h;
                   break;
               case '3':
                   fontinfo = (uint8_t*)font_tgl_48_3_h;
                   break;
               case '4':
                   fontinfo = (uint8_t*)font_tgl_48_4_h;
                   break;
               case '5':
                   fontinfo = (uint8_t*)font_tgl_48_5_h;
                   break;
               case '6':
                   fontinfo = (uint8_t*)font_tgl_48_6_h;
                   break;
               case '7':
                   fontinfo = (uint8_t*)font_tgl_48_7_h;
                   break;
               case '8':
                   fontinfo = (uint8_t*)font_tgl_48_8_h;
                   break;
               case '9':
                   fontinfo = (uint8_t*)font_tgl_48_9_h;
                   break;
               case '.':
                   fontinfo = (uint8_t*)font_tgl_48_conclusion_h;
                   break;                
               case ':':
                   fontinfo = (uint8_t*)font_tgl_48_colon_h;
                   break;                
               default:
                   fontinfo = (uint8_t*)font_tgl_48_0_h;
                   break;
           }
       
    }
     
        
    *width = fontinfo[0];
    *height = fontinfo[1];
    
    return fontinfo;
    
}


void UI_Common_Draw_NumberImage_textbox_Bystringinfo(uint8_t *lcdram,int box_x,int box_y,int box_w,int box_h,uint8_t image_color,char *string,int len,int number_size,enum_textbox_display_type display_type)
{
    int image_w=0,image_h=0;
    int offsetx =0,offsety =0;
    //int image_count =0;
    int i=0;
    uint8_t* fontinfo;
    int string_w = 0;

    for(i=0;i<len;i++)
    {
        fontinfo = UI_Common_GetNumberImageInfo_Bychar(string[i],&image_w,&image_h,number_size);
        string_w=string_w+image_w;
    }
    

    offsetx =(box_w - string_w)/2;
    offsety =(box_h - image_h)/2;

    switch(display_type)
    {
        case ENUM_TEXTBOX_LEFT:
        {
            offsetx =0;
            offsety =(box_h - image_h)/2;
        }
        break;
        case ENUM_TEXTBOX_CENTER:
        {
            offsetx =(box_w - string_w)/2;
            offsety =(box_h - image_h)/2;
         }
        break;
        case ENUM_TEXTBOX_RIGHT:
        {
            offsetx = box_w - string_w;
            offsety =(box_h - image_h)/2;
         }
        break;
        default:
        break;
    }
    
    for(i=0;i<len;i++)
    {
        fontinfo = UI_Common_GetNumberImageInfo_Bychar(string[i],&image_w,&image_h,number_size);
        UI_Common_AddBWsourcePic(lcdram,box_x+offsetx,box_y+offsety,(uint8_t*)fontinfo,APP_COLOR_BLACK,image_color);
        offsetx = offsetx+fontinfo[0];
    }


}


uint8_t*  UI_Common_GetweekfontInfo(int day)
{

    uint8_t* fontinfo = NULL;

        switch(day)
        {
            case 0:
                fontinfo = (uint8_t*)gchinesestr_sunday;
                break;
            case 1:
                fontinfo = (uint8_t*)gchinesestr_monday;
                break;
            case 2:
                fontinfo = (uint8_t*)gchinesefont_tuesday;
                break;
            case 3:
                fontinfo = (uint8_t*)gchinesefont_wednesday;
                break;
            case 4:
                fontinfo = (uint8_t*)gchinesefont_thursday;
                break;
            case 5:
                fontinfo = (uint8_t*)gchinesefont_friday;
                break;
            case 6:
                fontinfo = (uint8_t*)gchinesefont_saturday;
                break;
            default:
                fontinfo = (uint8_t*)gchinesestr_sunday;
                break;
        }
    
    return fontinfo;
    
}


UI_Common_list_s curr_list = {0x00};

void UI_Common_ScreenCleanListInfo(void)
{

    curr_list.curr_list_page = 0;
    curr_list.curr_list_highlight = 0;
    curr_list.total_count = 0;
    memset(curr_list.icon_list,0x00,sizeof(curr_list.icon_list));
    memset(curr_list.string_list,0x00,sizeof(curr_list.string_list));
    memset(curr_list.line2_content,0x00,sizeof(curr_list.line2_content));
    
}


void UI_Common_ShowIconList(uint8_t *lcdram)
{
    int len = 0;

    if(curr_list.curr_list_page*3<curr_list.total_count)
    {
        if(curr_list.line2_content[curr_list.curr_list_page*3+0][0] != 0)
        {

            UI_Common_AddPic(lcdram,8,11,(uint8_t*)curr_list.icon_list[curr_list.curr_list_page*3+0]);
            UI_Common_AddBWsourcePic(lcdram,52,8,(uint8_t*)curr_list.string_list[curr_list.curr_list_page*3+0],APP_COLOR_BLACK,APP_COLOR_WHITE);

            len = strlen(curr_list.line2_content[curr_list.curr_list_page*3+0]);
            UI_Common_Draw_AscStr_textbox(lcdram,52,34,80,16,16,APP_COLOR_WHITE,curr_list.line2_content[curr_list.curr_list_page*3+0],len,ENUM_TEXTBOX_LEFT);

        }
        else
        {
            UI_Common_AddPic(lcdram,8,11,(uint8_t*)curr_list.icon_list[curr_list.curr_list_page*3+0]);
            UI_Common_AddBWsourcePic(lcdram,52,17,(uint8_t*)curr_list.string_list[curr_list.curr_list_page*3+0],APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
        
    }
    if(curr_list.curr_list_page*3+1<curr_list.total_count)
    {
        
        if(curr_list.line2_content[curr_list.curr_list_page*3+1][0] != 0)
        {

            UI_Common_AddPic(lcdram,8,70,(uint8_t*)curr_list.icon_list[curr_list.curr_list_page*3+1]);
            UI_Common_AddBWsourcePic(lcdram,52,8+59,(uint8_t*)curr_list.string_list[curr_list.curr_list_page*3+1],APP_COLOR_BLACK,APP_COLOR_WHITE);

            len = strlen(curr_list.line2_content[curr_list.curr_list_page*3+1]);
            UI_Common_Draw_AscStr_textbox(lcdram,52,34+59,80,16,16,APP_COLOR_WHITE,curr_list.line2_content[curr_list.curr_list_page*3+1],len,ENUM_TEXTBOX_LEFT);

        }
        else
        {
            UI_Common_AddPic(lcdram,8,70,(uint8_t*)curr_list.icon_list[curr_list.curr_list_page*3+1]);
            UI_Common_AddBWsourcePic(lcdram,52,76,(uint8_t*)curr_list.string_list[curr_list.curr_list_page*3+1],APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
    }
    
    if(curr_list.curr_list_page*3+2<curr_list.total_count)
    {

        if(curr_list.line2_content[curr_list.curr_list_page*3+2][0] != 0)
        {

            UI_Common_AddPic(lcdram,8,129,(uint8_t*)curr_list.icon_list[curr_list.curr_list_page*3+2]);
            UI_Common_AddBWsourcePic(lcdram,52,8+59+59,(uint8_t*)curr_list.string_list[curr_list.curr_list_page*3+2],APP_COLOR_BLACK,APP_COLOR_WHITE);

            len = strlen(curr_list.line2_content[curr_list.curr_list_page*3+2]);
            UI_Common_Draw_AscStr_textbox(lcdram,52,34+59+59,80,16,16,APP_COLOR_WHITE,curr_list.line2_content[curr_list.curr_list_page*3+2],len,ENUM_TEXTBOX_LEFT);

        }
        else
        {
            UI_Common_AddPic(lcdram,8,129,(uint8_t*)curr_list.icon_list[curr_list.curr_list_page*3+2]);
            UI_Common_AddBWsourcePic(lcdram,52,135,(uint8_t*)curr_list.string_list[curr_list.curr_list_page*3+2],APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
    }
    
}


struct_run_screen_info curr_run_screen_info;


extern uint8_t * UI_Display_Get_MainRam(void);

void UI_Common_Show_RunScreen_Prepare(enum_run_screen_type run_type)
{

    uint8_t *mainram;
    uint8_t *oldram;

    
    curr_run_screen_info.run_type = run_type;

    mainram = UI_Display_Get_MainRam();
    oldram = UI_Display_Get_Runoldram();
    

    memcpy(oldram, mainram, RGB_LCD_RAM_LEN);
    

}


void UI_Common_Show_RunScreen_timehandle(void)
{


    curr_run_screen_info.is_run = 1;
    
    if(curr_run_screen_info.curr_segment_count*curr_run_screen_info.segment_size<=LCD_WIDTH)
    {
        memset(curr_run_screen_info.ram_temp,0x00, RGB_LCD_RAM_LEN);
        UI_Common_Show_RunScreen_Internal(curr_run_screen_info.run_type, curr_run_screen_info.segment_size*curr_run_screen_info.curr_segment_count, 200);
        curr_run_screen_info.curr_segment_count++;
    }
    else
    {

        UI_Common_set_timer_handle(NULL);
        App_Lcd_HardTimerStop();
    
        curr_run_screen_info.is_run = 0;
        curr_run_screen_info.curr_segment_count=1;
        curr_run_screen_info.run_type = ENUM_ROUND_NON;

        UI_Screen_draw_Screen();
    }
    
    

}


void UI_Common_Show_RunScreen(enum_run_screen_type runDiret,uint8 *ram_new,uint8 *ram_old,uint8 *ram_temp)
{

    curr_run_screen_info.is_ready = 0;
    curr_run_screen_info.run_type = runDiret;
    curr_run_screen_info.ram_new = ram_new;
    curr_run_screen_info.ram_old = ram_old;
    curr_run_screen_info.ram_temp = ram_temp;
    curr_run_screen_info.segment_size = 88;
    curr_run_screen_info.curr_segment_count = 1;
    curr_run_screen_info.duration_per_frame = 100;
    
    UI_Common_Show_RunScreen_timehandle();
    UI_Common_set_timer_handle(UI_Common_Show_RunScreen_timehandle);
    App_Lcd_HardTimerStart(curr_run_screen_info.duration_per_frame);

}

//不能滚动单数
void UI_Common_Show_RunScreen_Internal(enum_run_screen_type runDiret, uint8 runPixel, uint8 runTime)
{
	int i,j;

    switch(runDiret)
    {
        case ENUM_ROUND_UP:
            memcpy(curr_run_screen_info.ram_temp,curr_run_screen_info.ram_old+runPixel*88,RGB_LCD_RAM_LEN-runPixel*88);
            memcpy(curr_run_screen_info.ram_temp+RGB_LCD_RAM_LEN-runPixel*88,curr_run_screen_info.ram_new,runPixel*88);
			break;
        case ENUM_ROUND_DOWN:
            memcpy(curr_run_screen_info.ram_temp,curr_run_screen_info.ram_new+(LCD_HEIGHT-runPixel)*88,runPixel*88);
            memcpy(curr_run_screen_info.ram_temp+runPixel*88,curr_run_screen_info.ram_old,(LCD_HEIGHT-runPixel)*88);
			break;
        case ENUM_ROUND_RIGHT:
             for(i=0;i<LCD_WIDTH/2;i++)
            {
                for(j=0;j<LCD_HEIGHT;j++)
                {
                    if(i<runPixel/2)
                    {
                        curr_run_screen_info.ram_temp[j*88+i]=curr_run_screen_info.ram_new[j*88+i+(LCD_WIDTH-runPixel)/2];
                    }
                    else
                    {
                        curr_run_screen_info.ram_temp[j*88+i]=curr_run_screen_info.ram_old[j*88+i-runPixel/2];
                    }
                }
            }
			break;
        case ENUM_ROUND_LEFT:
             for(i=0;i<LCD_WIDTH/2;i++)
            {
                for(j=0;j<LCD_HEIGHT;j++)
                {
                    if(i<runPixel/2)
                    {
                        curr_run_screen_info.ram_temp[j*88+i]=curr_run_screen_info.ram_old[j*88+i+(LCD_WIDTH-runPixel)/2];
                    }
                    else
                    {
                        curr_run_screen_info.ram_temp[j*88+i]=curr_run_screen_info.ram_new[j*88+i-runPixel/2];
                    }
                }
            }
			break;
        //次级界面显示过场动画
        case ENUM_MOVE_IN:
             for(i=0;i<LCD_WIDTH/2;i++)
            {
                for(j=0;j<LCD_HEIGHT;j++)
                {
                    if(i<(LCD_WIDTH-runPixel)/2)
                    {
                        curr_run_screen_info.ram_temp[j*88+i]=curr_run_screen_info.ram_old[j*88+i];
                    }
                    else
                    {
                        curr_run_screen_info.ram_temp[j*88+i]=curr_run_screen_info.ram_new[j*88+i-(LCD_WIDTH-runPixel)/2];
                    }
                }
            }
			break;
        //次级界面退出过场动画
        case ENUM_MOVE_OUT:
             for(i=0;i<LCD_WIDTH/2;i++)
            {
                for(j=0;j<LCD_HEIGHT;j++)
                {
                    if(i<runPixel/2)
                    {
                        curr_run_screen_info.ram_temp[j*88+i]=curr_run_screen_info.ram_new[j*88+i];
                    }
                    else
                    {
                        curr_run_screen_info.ram_temp[j*88+i]=curr_run_screen_info.ram_old[j*88+i-runPixel/2];
                    }
                }
            }
			break;
            
		default:
			break;
    }

    //memcpy(TempLcdRam, curr_run_screen_info.ram_temp, RGB_LCD_RAM_LEN);

    UI_Display_Prepare(curr_run_screen_info.ram_temp);
    
}


void UI_Common_Show_PlayPause(uint8_t *lcdram,int type)
{

    if(type == 0) //PALY
    {
        UI_Common_Draw_Annulus(lcdram,87,87,87,79,APP_COLOR_CYAN,FALSE);
        UI_Common_AddBWsourcePic(lcdram,40,40,(uint8_t *)image_sportmode_play_96_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
    }
    else   //PAUSE
    {
        UI_Common_Draw_Annulus(lcdram,87,87,87,79,APP_COLOR_YELLOW,FALSE);
        UI_Common_AddBWsourcePic(lcdram,40,40,(uint8_t *)image_sportmode_pause_96_h,APP_COLOR_BLACK,APP_COLOR_YELLOW);
    }


}

void UI_Common_Show_SportModeDataDetailBG(uint8_t *lcdram,int type_line0,int type_line1,int type_line2)
{

    UI_Common_Draw_Hline(lcdram,0,58,176,1,APP_COLOR_WHITE,TRUE);
    UI_Common_Draw_Hline(lcdram,0,117,176,1,APP_COLOR_WHITE,TRUE);

    if(type_line0 == 1)
    {
        UI_Common_Draw_Vline(lcdram,87,4,50,2,APP_COLOR_WHITE,TRUE);
    }
    if(type_line1 == 1)
    {
        UI_Common_Draw_Vline(lcdram,87,63,50,2,APP_COLOR_WHITE,TRUE);
    }
    if(type_line2 == 1)
    {
        UI_Common_Draw_Vline(lcdram,87,122,50,2,APP_COLOR_WHITE,TRUE);
    }

}


void UI_Common_Show_SportModeDataDetail_CommonData(uint8_t *lcdram,int x,int y,int width,int height,const uint8_t *title,char* data,int datalen,uint8_t font_color)
{

    UI_Common_Draw_FontStr_textbox(lcdram,x,y,width,height/2,(uint8_t *)title,font_color,APP_COLOR_BLACK);
    
    UI_Common_Draw_NumberImage_textbox_Bystringinfo(lcdram,x,y+height/2,width,height/2,font_color,data,datalen,20,ENUM_TEXTBOX_CENTER);
    
}


//0
void UI_Common_Show_SportModeDataDetail_HrData(uint8_t *lcdram,int x,int y,int width,int height,uint8_t *title,char* data,int datalen,uint8_t font_color,hrZone_e hrZone)
{

    UI_Common_AddBWsourcePic(lcdram,x+8,y+8,(uint8_t *)image_sportmode_hr_32_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
    
    UI_Common_Draw_NumberImage_textbox_Bystringinfo(lcdram,x,y,width,height/2,font_color,data,datalen,20,ENUM_TEXTBOX_CENTER);
    UI_Common_Draw_FontStr_textbox(lcdram,x,y+height/2,width,height/2,title,font_color,APP_COLOR_BLACK);

    UI_Common_Draw_Hline(lcdram,148,123,24,8,APP_COLOR_RED,TRUE);
    UI_Common_Draw_Hline(lcdram,148,133,24,8,APP_COLOR_PINK,TRUE);
    UI_Common_Draw_Hline(lcdram,148,143,24,8,APP_COLOR_YELLOW,TRUE);
    UI_Common_Draw_Hline(lcdram,148,153,24,8,APP_COLOR_GREEN,TRUE);
    UI_Common_Draw_Hline(lcdram,148,163,24,8,APP_COLOR_CYAN,TRUE);
    
    switch(hrZone)
    {
        case HR_ZONE_0:
            break;
        case HR_ZONE_1:
            UI_Common_Draw_Hline(lcdram,140,163,8,8,APP_COLOR_CYAN,TRUE);
        break;
        case HR_ZONE_2:
            UI_Common_Draw_Hline(lcdram,140,153,8,8,APP_COLOR_GREEN,TRUE);
        break;
        case HR_ZONE_3:
            UI_Common_Draw_Hline(lcdram,140,143,8,8,APP_COLOR_YELLOW,TRUE);
        break;
        case HR_ZONE_4:
            UI_Common_Draw_Hline(lcdram,140,133,8,8,APP_COLOR_PINK,TRUE);
        break;
        case HR_ZONE_5:
            UI_Common_Draw_Hline(lcdram,140,123,8,8,APP_COLOR_RED,TRUE);
        break;
        default:
            break;
        
    }
    

}


/*icon0 icon 1 icon2*/
void UI_Common_Show_ThreeIconBar(uint8_t *lcdram,int x,int y,uint8_t* icon0,uint8_t* icon1,uint8_t*icon2)
{

    if(icon0!=NULL)
    {
        UI_Common_AddBWsourcePic(lcdram,x+28,y+17,(uint8_t*)icon0,APP_COLOR_BLACK,APP_COLOR_WHITE);
    }
    
    if(icon1!=NULL)
    {
        UI_Common_AddBWsourcePic(lcdram,x+76,y+17,(uint8_t*)icon1,APP_COLOR_BLACK,APP_COLOR_WHITE);
    }
    
    if(icon2!=NULL)
    {
        UI_Common_AddBWsourcePic(lcdram,x+124,y+17,(uint8_t*)icon2,APP_COLOR_BLACK,APP_COLOR_WHITE);
    }
    
}

/*licon stringinfo ricon*/
void UI_Common_Show_ModeListIconStringBar(uint8_t *lcdram,int x,int y,uint8_t* l_icon,uint8_t* r_icon,uint8_t* bg_image,uint8_t* stringinfo,uint8_t bg_color,uint8_t image_color)
{

    if(bg_image!=NULL)
    {
        UI_Common_AddPic(lcdram,x,y,(uint8_t*)bg_image);
    }
    
    if(l_icon!=NULL)
    {
        UI_Common_AddBWsourcePic(lcdram,x+16,y+17,(uint8_t*)l_icon,bg_color,image_color);
    }
    if(r_icon!=NULL)
    {
        UI_Common_AddBWsourcePic(lcdram,x+140,y+17,(uint8_t*)r_icon,bg_color,image_color);
    }    
    if(stringinfo!=NULL)
    {
        UI_Common_AddBWsourcePic(lcdram,x+64,y+17,(uint8_t*)stringinfo,bg_color,image_color);
    }
    
}



void UI_Common_Show_ModeMenuHeadBar(uint8_t *lcdram,int x,int y,char* data1,int data1_len,char* data2,int data2_len)
{
    char string_content[16];
    int string_len;
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();

    SysTimeType_e curr_type = App_Var_SysTimeTypeGet();
    ui_common_time_12hour_s curr_12hour_time = {0};
    
    uint8 percent = 0;
    int len = 0;
    
    
    UI_Common_Draw_NumberImage_textbox_Bystringinfo(lcdram,x,y,88,29,APP_COLOR_WHITE,data1,data1_len,20,ENUM_TEXTBOX_CENTER);
    UI_Common_Draw_NumberImage_textbox_Bystringinfo(lcdram,x,y+29,88,29,APP_COLOR_WHITE,data2,data2_len,20,ENUM_TEXTBOX_CENTER);

    if(curr_type == SYS_TIME_24_TYPE)
    {
        sprintf(string_content,"%d:%2d",lMidRTC->RTC.hour,lMidRTC->RTC.min);
        string_len = strlen(string_content);
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(lcdram,x+88,y,88,29,APP_COLOR_WHITE,string_content,string_len,20,ENUM_TEXTBOX_CENTER);
    }
    else
    {

        UI_Common_Get_Time_12hour(&curr_12hour_time);
        
        //14-80
        if(curr_12hour_time.is_am ==1)
        {

            sprintf(string_content,"%d:%02d AM",curr_12hour_time.hour,curr_12hour_time.min);
        }
        else
        {
            sprintf(string_content,"%d:%02d PM",curr_12hour_time.hour,curr_12hour_time.min);
        }
        string_len = strlen(string_content);
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(lcdram,x+88,y,88,29,APP_COLOR_WHITE,string_content,string_len,20,ENUM_TEXTBOX_CENTER);
    }

    
    Mid_Bat_SocRead(&percent);
    sprintf(string_content,"%d%%",percent);
    string_len = strlen(string_content);
    UI_Common_Draw_AscStr_textbox(lcdram,88,33,56,16,16,APP_COLOR_WHITE,string_content,string_len,ENUM_TEXTBOX_RIGHT);

    len = 14*percent/100;
    UI_Common_AddBWsourcePic(lcdram,144,29,(uint8_t*)image_bw_battery_s,APP_COLOR_BLACK,APP_COLOR_WHITE);
    UI_Common_Draw_Hline(lcdram,144+9,29+5+1+(14-len),6,len,APP_COLOR_CYAN,true);

    UI_Common_Draw_Hline(lcdram,4,59,168,1,APP_COLOR_WHITE,true);
    
}




UI_Common_sportmode_countdown_s sportmode_countdown;

void UI_Common_SportModeCountDownInfoDefault(void)
{
    sportmode_countdown.segment_time = 1000;
    sportmode_countdown.curr_time = 0;
    sportmode_countdown.total_time = 3000;
}


void UI_Common_DispRuningModeCountDownRound(uint8_t *lcdram,double angle)
{
        
        if(angle<=PI)
        {

            UI_Common_Draw_Annulus_Byangle(lcdram,87,87,87,79,PI,PI+angle,APP_COLOR_WHITE,FALSE);
            UI_Common_Draw_Annulus_Byangle(lcdram,87,87,87,79,0,PI,APP_COLOR_WHITE,TRUE);
            UI_Common_Draw_Annulus_Byangle(lcdram,87,87,87,79,PI+angle,2*PI,APP_COLOR_WHITE,TRUE);
            
        }
        else
        {
            UI_Common_Draw_Annulus_Byangle(lcdram,87,87,87,79,PI,2*PI,APP_COLOR_WHITE,FALSE);
            UI_Common_Draw_Annulus_Byangle(lcdram,87,87,87,79,0,angle-PI,APP_COLOR_WHITE,FALSE);
            UI_Common_Draw_Annulus_Byangle(lcdram,87,87,87,79,angle-PI,PI,APP_COLOR_WHITE,TRUE);
        }
        //背景图
}



//line1_type 0:image 1:string 2:image + string
void UI_Common_List_RarrowDoubleline(uint8_t *lcdram,int x,int y,uint8_t *line0_info0,uint8_t* line1_info0,uint8_t* line1_info1,int line1_type)
{

    if(line1_info0 == NULL)
    {
        // x+8,y+17
        UI_Common_AddBWsourcePic(lcdram,x+8,y+17,(uint8_t*)line0_info0,APP_COLOR_BLACK,APP_COLOR_WHITE);
    
    }
    else
    {
        // x+8,y+8
        // x+8,y+34
        UI_Common_AddBWsourcePic(lcdram,x+8,y+8,(uint8_t*)line0_info0,APP_COLOR_BLACK,APP_COLOR_WHITE);


        if(line1_type == 0)
        {
            UI_Common_AddBWsourcePic(lcdram,x+8,y+34,(uint8_t*)line1_info0,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
        else if(line1_type == 1)
        {
            UI_Common_AddAsc2Str(lcdram,x+8,y+34,(int8_t*)line1_info0,strlen(line1_info0),16,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
        else if(line1_type == 2)
        {
            UI_Common_AddBWsourcePic(lcdram,x+8,y+34,(uint8_t*)line1_info0,APP_COLOR_BLACK,APP_COLOR_WHITE);
            UI_Common_AddAsc2Str(lcdram,x+8+line1_info0[0],y+34,(int8_t*)line1_info1,strlen(line1_info1),16,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }

        
      
    }
        UI_Common_AddPic(lcdram,x+144,y+17,(uint8_t*)_ic_arrow_right_24_h);
    
}



//中文文本框
void UI_Common_Drawtextbox_byfontic(uint8_t *lcdram, int text_x, int text_y,int text_width,int text_height, uint16* string, int strlen, Wordstock_size_s font_size_type, uint8_t bg_color, uint8_t font_color)
{


#if 1
    int len = strlen;
    uint16 asccode =0;

    int i = 0;

    
    int font_size = 0;
    //int font_count_max = 0;
    //row and column
    //int row_max = 0;
    int column_max = 0;
    //列间距
    int column_gap = 1;
    
	uint8_t fontdata[256];
	font_para_t fontinfo;
    
    int x =text_x;
    int y =text_y;
    int width = 0;
    int height = text_height;

    //int curr_row = 0;
    int curr_column = 0;


    if(font_size_type == GB_SIZE_16X16)
    {
        font_size = 16;
    }
    else if(font_size_type == GB_SIZE_24X24)
    {		
        font_size = 24;
    }

    column_max = height/font_size;
    curr_column = 1;
    
    for(i=0;i<len;i++)
    {

        asccode = string[i];
        
        RTT_DEBUG_printf(0,"asccode=%x--%d\n",asccode,i);
        
        fontinfo.dataAddr = fontdata;
        fontinfo.sizeKind = font_size_type;
        fontinfo.code.codeUnicode = asccode;
        memset(fontdata, 0x00, 256);
        Mid_Font_ReadUnicode(&fontinfo);
        
        width = width+fontinfo.wordSize.wordWidth;
        
        if((width + 16) > text_width && curr_column == column_max && i!=len-1)
        {
            UI_Common_AddBWsourcePic(lcdram,x,y,(uint8_t*)iamge_bw_history_ellipsis_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            break;
        }

        UI_Common_AddFont_Byfontic(lcdram,x,y,fontinfo.wordSize.wordWidth,fontinfo.wordSize.wordHeight,fontdata,APP_COLOR_BLACK,APP_COLOR_WHITE);

        x= x+fontinfo.wordSize.wordWidth;

        if( x >= (text_x+text_width) )
        {
            x = text_x;
            width = 0;
            curr_column = curr_column + 1;
            y = y + font_size+column_gap;
        }

        
            
    }
#endif
    
}


uint8_t UI_Common_GetFontPixelValue_Byfontic(uint8_t* fontinfo,uint8_t info_x,uint8_t info_y,int width,int height,uint8_t bg_color,uint8_t font_color)
{
	uint8_t TmpPixelValue;

    uint8_t x;
    uint8_t y;
    uint8_t font_width;
    //uint8_t font_height;

    int pos = 0;
    int bit_pos = 0;
    
    x = info_x;
    y = info_y;
    font_width = width;
    //font_height = height;

    pos=x+y/8*font_width;

    TmpPixelValue = fontinfo[pos];

    bit_pos=y%8;
    
    switch(bit_pos)
    {
        case 0:
            TmpPixelValue =TmpPixelValue&0x01;
            //TmpPixelValue =TmpPixelValue;
            break;
        case 1:
            TmpPixelValue =TmpPixelValue&0x02;
            TmpPixelValue =TmpPixelValue>>1;
            break;
        case 2:
            TmpPixelValue =TmpPixelValue&0x04;
            TmpPixelValue =TmpPixelValue>>2;
            break;
        case 3:
            TmpPixelValue =TmpPixelValue&0x08;
            TmpPixelValue =TmpPixelValue>>3;
            break;
        case 4:
            TmpPixelValue =TmpPixelValue&0x10;
            TmpPixelValue =TmpPixelValue>>4;
            break;
        case 5:
            TmpPixelValue =TmpPixelValue&0x20;
            TmpPixelValue =TmpPixelValue>>5;
            break;
        case 6:
            TmpPixelValue =TmpPixelValue&0x40;
            TmpPixelValue =TmpPixelValue>>6;
            break;
        case 7:
            TmpPixelValue =TmpPixelValue&0x80;
            TmpPixelValue =TmpPixelValue>>7;
            break;
        default:
            TmpPixelValue = 0;
            break;
    }

    if(TmpPixelValue==1)
        TmpPixelValue = font_color;
    else
        TmpPixelValue = bg_color;
        
	return TmpPixelValue;
    
}


//字符信息加入到显示区域
void UI_Common_AddFont_Byfontic(uint8_t *lcdram,uint8_t x,uint8_t y,int width,int height,uint8_t* fontinfo,uint8_t bg_color,uint8_t font_color)
{
    ui_common_pic_info_s image_info;

    int i=0;
    int j=0;


    image_info.offset_x = x;
    image_info.offset_y = y;
    image_info.width = width;
    image_info.height = height;
    
    //RTT_DEBUG_printf(0,"App_AddPic:  x=%d,y=%d,w=%d,h=%d\n", pic_x,pic_y,image_info.length,image_info.height);
    for(j=0;j<image_info.height;j++)
    {
        for(i=0;i<image_info.width;i++)
        {
          UI_Common_SetPixelValue(lcdram,image_info.offset_x+i,image_info.offset_y+j,UI_Common_GetFontPixelValue_Byfontic(fontinfo,i,j,image_info.width,image_info.height,bg_color,font_color));
        }
    }

    
}



// 0 横 1 竖
void UI_Common_Add_Battery(uint8_t *lcdram,uint8_t x,uint8_t y,int type)
{

    uint8 percent = 0;

    int len = 0;


    Mid_Bat_SocRead(&percent);
    len = 14*percent/100;

    if(type == 0)
    {

        if(percent<=10)
        {
            UI_Common_AddBWsourcePic(lcdram,x,y,(uint8_t*)image_bw_battery_h,APP_COLOR_BLACK,APP_COLOR_RED);
        }
        else
        {
            UI_Common_AddBWsourcePic(lcdram,x,y,(uint8_t*)image_bw_battery_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
        UI_Common_Draw_Hline(lcdram,x+4,y+9,len,6,APP_COLOR_CYAN,true);
        
    }
    else if(type == 1)
    {
        if(percent<=10)
        {
            UI_Common_AddBWsourcePic(lcdram,x,y,(uint8_t*)image_bw_battery_s,APP_COLOR_BLACK,APP_COLOR_RED);
        }
        else
        {
            UI_Common_AddBWsourcePic(lcdram,x,y,(uint8_t*)image_bw_battery_s,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
        UI_Common_Draw_Hline(lcdram,x+9,y+6+14-len,6,len,APP_COLOR_CYAN,true);
        
    }



}



ui_common_page_info_s curr_page_info = {0};

ui_common_page_info_s detail_page_info = {0};


void UI_Common_Next_Page(void)
{

    if(curr_page_info.curr_page_number ==curr_page_info.total_page_number-1)
        return;

    curr_page_info.curr_page_number++;


}

void UI_Common_Pre_Page(void)
{
    if(curr_page_info.curr_page_number ==0)
        return;
    curr_page_info.curr_page_number--;

}


void UI_Common_Detail_Next_Page(void)
{

    if(detail_page_info.curr_page_number ==detail_page_info.total_page_number-1)
        return;
    detail_page_info.curr_page_number++;


}

void UI_Common_Detail_Pre_Page(void)
{
    if(detail_page_info.curr_page_number ==0)
        return;
    detail_page_info.curr_page_number--;

}

void UI_Common_Get_Time_12hour(ui_common_time_12hour_s *timeTemp)
{

        MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();

        
        if(lMidRTC->RTC.hour <12)
        {
            timeTemp->is_am = 1;
        }
        else
        {
            timeTemp->is_am = 0;
        }

        if(lMidRTC->RTC.hour%12 == 0)
        {
            timeTemp->hour	= 12;
        }
        else
        {
            timeTemp->hour   = lMidRTC->RTC.hour%12;
        }

        timeTemp->min     = lMidRTC->RTC.min; 
        timeTemp->sec     = lMidRTC->RTC.sec;

}


