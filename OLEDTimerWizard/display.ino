// beans
#define beans_width 40
#define beans_height 48
static unsigned char beans_bits[] U8G_PROGMEM= {
   0x00, 0x80, 0x07, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0x00, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00 };

  
// cup
#define cup_width 48
#define cup_height 28
static unsigned char cup_bits[] U8G_PROGMEM = {
  0xf8, 0xff, 0xff, 0xff, 0x1f, 0x00, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0x00,
  0x00, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x3f, 0x00, 0x00 };
  
// big cup
#define cup_big_width 63
#define cup_big_height 36
static unsigned char cup_big_bits[] U8G_PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff,
   0x1e, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x3f, 0x1e, 0x00, 0x00, 0x00, };

void DisplayNumber(char* display_unit){
  hundred = doseTime[doseIdx] / 100;                // calculating digit hundred
  ten     = (doseTime[doseIdx]-(hundred*100)) / 10; // calculating digit ten
  one     = doseTime[doseIdx] % 10;                 // calculating digit one
  if (setupStateIdx == STEP5) {
   u8g.print(hundred);
   u8g.print(".");
  } else if (hundred > 0) u8g.print(hundred);  
  u8g.print(ten); 
  if (setupStateIdx != STEP5) u8g.print(".");
  u8g.print(one);
  u8g.setFont(u8g_font_fub11);  
  u8g.print(display_unit);
  u8g.setFont(u8g_font_fub20);
}

/* draw display */
void drawDisplay() {
  Serial.println("drawDisplay");
    u8g.firstPage();  
    Serial.println("prut");
    do {
      draw();
      Serial.println("DRAW");
    } 
    while( u8g.nextPage() );
    Serial.println("drawDisplay end");
}
  
/* draw display */
void draw() {
  #ifdef DEBUG
Serial.println("draw1234567890:");
  Serial.println(stateIdx);
#endif
  // draw frame and box
  byte boxWidth = 0;
  if ( stateIdx == SJSET ) boxWidth = display_width;
  if ( stateIdx == SJOFF ) boxWidth = 0;
  if ( stateIdx == SJON ) { 
      u8g.drawFrame(0,0,display_width,10); 
      boxWidth = display_width * ( 1 - float(currentTime)/float(doseTime[doseIdx]) );
  }
  
  if ( stateIdx != WIZARD || stateIdx != PAUSE) { 
  //  u8g.drawFrame(0,0,display_width,10);
    u8g.drawBox(0,0,boxWidth,10);
  }
  
  switch (stateIdx) {

    case PAUSE:
      u8g.setFont(u8g_font_fub11); 
      u8g.setPrintPos(40, 45);
      u8g.print("Pause");

    
//    if (doseIdx != DOSEM) {
//    u8g.drawXBMP( 0, 25, cup_width, cup_height, cup_bits);  // small cup icon
//    u8g.setColorIndex(0);
//    u8g.setPrintPos(12, 48);
//    u8g.print(doseIdx);
//    u8g.setColorIndex(1);
//    // show coffee portion
//    u8g.setFont(u8g_font_fub11); 
//    u8g.setPrintPos(64, 30);
//    u8g.print(portion_name[doseIdx-1]);
//    u8g.setFont(u8g_font_fub20);     
//    // dose time
//    u8g.setFont(u8g_font_fub20);
//    u8g.setPrintPos( 64, 64); 
//    DisplayNumber("s");
//    break;
//
break;



  
  case SJSET:
    if (doseIdx != DOSEM) {
    u8g.drawXBMP( 0, 25, cup_width, cup_height, cup_bits);  // small cup icon
    u8g.setColorIndex(0);
    u8g.setPrintPos(12, 48);
    u8g.print(doseIdx);
    u8g.setColorIndex(1);
    // show coffee portion
    u8g.setFont(u8g_font_fub11); 
    u8g.setPrintPos(64, 30);
    u8g.print(portion_name[doseIdx-1]);
    u8g.setFont(u8g_font_fub20);     
    // dose time
    u8g.setFont(u8g_font_fub20);
    u8g.setPrintPos( 64, 64); 
    DisplayNumber("s");
    break;
  }
  
  case QB1SET:
    if (doseIdx != DOSEM) {    
    u8g.setColorIndex(1);
    u8g.setFont(u8g_font_fub11);
    u8g.setPrintPos( 2, 25); 
    u8g.print("Definer knap 1");
    u8g.setFont(u8g_font_fub20);
    u8g.setPrintPos( 44, 54); 
    u8g.print(portion_name[doseIdx-1]);
    break; 
    } 
    
   case QB2SET:
    if (doseIdx != DOSEM) {    
    u8g.setColorIndex(1);
    u8g.setFont(u8g_font_fub11);
    u8g.setPrintPos( 2, 25); 
    u8g.print("Definer knap 2");    
    u8g.setFont(u8g_font_fub20);
    u8g.setPrintPos( 44, 54); 
    u8g.print(portion_name[doseIdx-1]);
    break;     
    }
   
    case WIZARD:                      // Setup Wizard *******************************
      if (setupStateIdx == INIT) { 
        u8g.setColorIndex(1);
        u8g.setFont(u8g_font_fub11);
        u8g.setPrintPos( 2, 15); 
        u8g.print("Antal dosisvalg");    
        u8g.setFont(u8g_font_fub20);
        u8g.setPrintPos( 54, 54); 
        u8g.print(doseIdx);
        break; 
      } else 
      
      if (setupStateIdx == STEP1) { 
        u8g.setColorIndex(1);
        u8g.setFont(u8g_font_fub11);
        u8g.setPrintPos( 2, 15); 
        u8g.print("V""\xe6""gt af nr.");
        u8g.setPrintPos( 100, 15); 
        u8g.print(portion);    
        u8g.setFont(u8g_font_fub20);
        u8g.setPrintPos( 40, 54); 
        DisplayNumber("g");
        break; 
      } else

      if (setupStateIdx == STEP2) { 
        u8g.setColorIndex(1);
        u8g.setFont(u8g_font_fub11);
        u8g.setPrintPos( 2, 15); 
        u8g.print("Kv""\xe6""rnpr""\xf8""ve?");    
        u8g.setFont(u8g_font_fub20);
        u8g.setPrintPos( 40, 54); 
        if ( (doseIdx+1) % 2 == 0 ) u8g.print("Ja"); else u8g.print("Nej");
        break;  
      } else
      
      if (setupStateIdx == STEP2_1) { 
        u8g.setColorIndex(1);
        u8g.setFont(u8g_font_fub11);
        u8g.setPrintPos( 2, 15); 
        u8g.print("Kv""\xe6""rntid");
        u8g.setFont(u8g_font_fub20);
        u8g.setPrintPos( 40, 54); 
        DisplayNumber("s");
        break; 
      } else
      
      if (setupStateIdx == STEP2_2) { 
        u8g.setColorIndex(1);
        u8g.setFont(u8g_font_fub11);
        u8g.setPrintPos( 2, 15); 
        u8g.print("Flere pr""\xf8""ver?");    
        u8g.setFont(u8g_font_fub20);
        u8g.setPrintPos( 40, 54); 
        if ( (doseIdx+1) % 2 == 0 ) u8g.print("Ja"); else u8g.print("Nej");
        break;  
      } else
      
      if (setupStateIdx == STEP3) { 
        u8g.setColorIndex(1);
        u8g.setFont(u8g_font_fub11);
        u8g.setPrintPos( 2, 15); 
        u8g.print("V""\xe6""gt p""\xe5"" "); u8g.print(probeGrindTime/10); u8g.print("s er:");   
        u8g.setFont(u8g_font_fub20);
        u8g.setPrintPos( 40, 54); 
        DisplayNumber("g");
        break; 
      } else
      
      if (setupStateIdx == STEP4) { 
        u8g.setColorIndex(1);
        u8g.setFont(u8g_font_fub11);
        u8g.setPrintPos( 2, 15); 
        u8g.print("Brug autofaktor?");    
        u8g.setFont(u8g_font_fub20);
        u8g.setPrintPos( 40, 54); 
        if ( (doseIdx+1) % 2 == 0 ) u8g.print("Ja"); else u8g.print("Nej");
        break;  
      } else      
      
      if (setupStateIdx == STEP5) { 
        u8g.setColorIndex(1);
        u8g.setFont(u8g_font_fub11);
        u8g.setPrintPos( 2, 15); 
        u8g.print("Faktor ");    
        u8g.setPrintPos(60, 15); 
        u8g.print(portion); u8g.print(" <-> "); u8g.print(portion+1);        
        u8g.setFont(u8g_font_fub20);
        u8g.setPrintPos( 40, 54); 
        DisplayNumber("");
        break; 
      } 
      
  // draw icon, number and dose time
  default:  
    if (doseIdx != DOSEM) {
      if ((setupStateIdx == STEP2) || (setupStateIdx == STEP2_1 )) u8g.drawXBMP( 43, 16, beans_width, beans_height, beans_bits); else //  manual grinding = beans icon 
          u8g.drawXBMP( 37, 20, cup_big_width, cup_big_height, cup_big_bits); // fixed grinding = large cup icon
    u8g.setColorIndex(0);
    u8g.setPrintPos(55, 55);
    if ((setupStateIdx != STEP2) && (setupStateIdx != STEP2_1) ) u8g.print(doseIdx);  // check wizard to print number in cup
    // show coffee dose
    u8g.setColorIndex(1);  
    u8g.setFont(u8g_font_fub11); 
    u8g.setPrintPos(90, 60);
    if ((setupStateIdx == STEP2) || (setupStateIdx == STEP2_1 )) { u8g.print(probeGrindTime/10); u8g.print("s");} else { 
       u8g.print(portion_name[doseIdx-1]);
    }
    u8g.setColorIndex(1);  
    u8g.setFont(u8g_font_fub20); 
    break;  
  } else if (doseIdx == DOSEM) {
    u8g.drawXBMP( 43, 16, beans_width, beans_height, beans_bits); // beans icon      
    break;  
  }     
 }  
}
