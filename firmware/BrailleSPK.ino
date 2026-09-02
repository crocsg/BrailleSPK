/**
 * \file            BrailleSPK.ino
 * \brief           main control loop
 */

/*
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *                  THE SOFTWARE IS LICENSED UNDER
 *                  GNU GENERAL PUBLIC LICENSE
 *                   Version 3, 29 June 2007
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of BrailleSPK software.
 *
 * SPDX-FileCopyrightText: 2026 Stephane GODIN <stephane@braillerap.org>
 * 
 * SPDX-License-Identifier: GPL-3.0 
 */



#include "AudioTools.h"   // https://github.com/pschatzmann/arduino-audio-tools
#include "espeak.h"       // https://github.com/pschatzmann/arduino-espeak-ng
                          // https://github.com/pschatzmann/arduino-posix-fs
#include "board.h"

#define DEFAULT_VOLUME 120  // default Brialle combination volume level
#define START_VOLUME 120    // Volume level for announcement at start

#define DEFAULT_RATE 95     // Braille combination annouement speed rate
#define START_RATE 80       // speed rate for announcement at start


// TTS init
I2SStream i2s;
ESpeak espeak(i2s, false);



void setup() 
{

  // kerboard matrix init
  pinMode (COL1, OUTPUT);
  pinMode (COL2, OUTPUT);
  pinMode (ROW1, INPUT_PULLDOWN);
  pinMode (ROW2, INPUT_PULLDOWN);
  pinMode (ROW3, INPUT_PULLDOWN);
  pinMode (BTNROW, INPUT_PULLDOWN);
  pinMode (PIN_BTN, INPUT);

  // Serial debug configuration
  //Serial.begin(115200);
  
  //digitalWrite(LED_PIN, HIGH);

  //while(!Serial);
  //AudioLogger::instance().begin(Serial, AudioLogger::Info);

  ////espeak.add("/mem/data/fr_dict", espeak_ng_data_fr_dict, espeak_ng_data_fr_dict_len);
  ////espeak.add("/mem/data/lang/fr", espeak_ng_data_lang_roa_fr, espeak_ng_data_lang_roa_fr_len);
  //espeak.add("/mem/data/voices/!v/whisper", espeak_ng_data_voices__v_whisper, espeak_ng_data_voices__v_whisper_len);
  ////espeak.add("/mem/data/voices/!v/norbert", espeak_ng_data_voices__v_norbert, espeak_ng_data_voices__v_norbert_len);
  //espeak.add("/mem/data/voices/!v/steph", espeak_ng_data_voices__v_steph, espeak_ng_data_voices__v_steph_len);
  //espeak.add("/mem/data/voices/!v/Annie", espeak_ng_data_voices__v_Annie, espeak_ng_data_voices__v_Annie_len);
  //espeak.add("/mem/data/voices/!v/mb-fr6", espeak_ng_data_voices_mb_mb_fr6, espeak_ng_data_voices_mb_mb_fr6_len);
  //espeak.add("/mem/data/voices/!v/mb-fr2", espeak_ng_data_voices_mb_mb_fr2, espeak_ng_data_voices_mb_mb_fr2_len);
  //espeak.add("/mem/data/voices/!v/mb-fr2", espeak_ng_data_voices_mb_mb_fr2, espeak_ng_data_voices_mb_mb_fr2_len);
  //espeak.add("/mem/data/voices/mb/mb-fr2", espeak_ng_data_voices_mb_mb_fr2, espeak_ng_data_voices_mb_mb_fr2_len);
    //espeak.add("/mem/data/voices/!v/mb-fr2", espeak_ng_data_voices_mb_mb_fr2, espeak_ng_data_voices_mb_mb_fr2_len);

#if 1
  espeak.add("/mem/data/en_dict", espeak_ng_data_en_dict, espeak_ng_data_en_dict_len);
  espeak.add("/mem/data/lang/en", espeak_ng_data_lang_gmw_en_US, espeak_ng_data_lang_gmw_en_US_len);
  espeak.add("/mem/data/voices/mb/mb-de1-en", espeak_ng_data_voices_mb_mb_de1_en, espeak_ng_data_voices_mb_mb_de1_en_len);
 //espeak.add("/mem/data/voices/!v/Alicia", espeak_ng_data_voices__v_Alicia, espeak_ng_data_voices__v_Alicia_len);

  // start TTS
  espeak.begin();
  
  // Select a voice suitable for EN language
  espeak.setVoice("en+en-german-1");

  // start I2S hardware
  audio_info espeak_info = espeak.audioInfo();
  auto cfg = i2s.defaultConfig();                     //  CF lib : audio-tools/src/AudioConfig.h
  cfg.channels = espeak_info.channels;                // 1
  cfg.sample_rate = espeak_info.sample_rate;          // 22050
  cfg.bits_per_sample = espeak_info.bits_per_sample;  // 16
  cfg.pin_ws    = PIN_LCBRK;                             //12; // lrck
  cfg.pin_bck   = PIN_BCLK;                             //14; // bclk
  cfg.pin_data  = PIN_DOUT;                            //27; // dout cote esp
  cfg.pin_data_rx = -1;                               // din cote esp
  i2s.begin(cfg);

  // say hello at start
  espeak.setVolume(START_VOLUME); 
  espeak.setRate (START_RATE);

  espeak.say("Hello !");
  espeak.say("You know what ?");
  espeak.say("I'm happy");

#endif
  delay(250);

  // set volume and speed rate to Braille announcement level
  espeak.setVolume(DEFAULT_VOLUME); 
  espeak.setRate (DEFAULT_RATE);
  
}

// Nato letter code
static const char* nato[] = {
    "Alfa",
    "Bravo",
    "Charlie",
    "Delta",
    "Echo",
    "Foxtrot",
    "Golf",
    "Hotel",
    "India",
    "Juliet",
    "Kilo",
    "Lima",
    "Mike",
    "November",
    "Oscar",
    "Papa",
    "Quebec",
    "Romeo",
    "Sierra",
    "Tango",
    "Uniform",
    "Victor",
    "Whiskey",
    "X-ray",
    "Yankee",
    "Zulu"
};

static uint8_t d1, d2, d3, d4, d5, d6,btn, btn1, btn2;
static uint8_t braille = 0;
static uint8_t code_found = 0;

// func: keyboard_read
//
// desc: Use keyboard matrix to read buttons states
// Braille dot are stored in d1->d6
// Side buttons are stored in btn1 and btn2
//

void keyboard_read ()
{
  // select column 1
  digitalWrite(COL1, HIGH);
  digitalWrite(COL2, LOW);
  delay (1);
  // read buttons state
  d1 = (uint8_t) (digitalRead (ROW1) ? 0 : 1);
  d2 = (uint8_t) (digitalRead (ROW2) ? 0 : 1);
  d3 = (uint8_t) (digitalRead (ROW3) ? 0 : 1);
  btn1 = (uint8_t) digitalRead (BTNROW);

  // select column 2
  digitalWrite(COL1, LOW);
  digitalWrite(COL2, HIGH);
  delay (1);
  // read buttons state
  d4 = (uint8_t) (digitalRead (ROW1) ? 0 : 1);
  d5 = (uint8_t) (digitalRead (ROW2) ? 0 : 1);
  d6 = (uint8_t) (digitalRead (ROW3) ? 0 : 1);
  btn2 = (uint8_t) digitalRead (BTNROW);

  // build Braille dots combination
  braille = d1 | (d2 << 1) | (d3 << 2) | (d4 << 3) | (d5 << 4) | (d6 << 5);
}


// basic english Braille code (UEB)
static uint8_t brcode[]= {
  0x01, // a
  0x03, // b
  0x09, // c
  0x19, // d
  0x11, // e
  0x0b, // f
  0x1b, // g
  0x13, // h
  0x0a, // i
  0x1a, // j
  0x05, // k
  0x07, // l
  0x0d, // m
  0x1d, // n
  0x15, // o
  0x0f, // p
  0x1f, // q
  0x17, // r
  0x0e, // s
  0x1e, // t
  0x25, // u
  0x27, // v
  0x3a, // w
  0x2d, // x
  0x3d, // y
  0x35, // z

};

// basic UEB escape sequence in Braille
static uint8_t brescape[] = {
  0x3c, // number indicator
  0x32, // period
  0x16,
  0x02, // comma
  0x04, // apostrophe
  0x12, // colon
  0x06, // a semi colon
  0x26, // opening quotation mark
  0x34,
  0x24, // hyphen
  0x0c, // fraction line
  0x20
};

// Latin letter associated with Braille code 
const char* datastr = "abcdefghijklmnopqrstuvwxyz";

// Escape description associated with Braille code
const char* escapestr[] = {
  "Number indicator",
  "A period or a decimal separator",
  "Exclamation point",
  "A comma",
  "An apostrophe",
  "A colon",
  "A semi colon",
  "Opening quotation mark",
  "Closing quotation mark",
  "Hyphen",
  "Fraction line",
  "Capital"

};

void loop ()
{
  
  // read main button state
  btn = (uint8_t) digitalRead (PIN_BTN);

  if (btn)
  {
    char sentence[256]; 

    // read keyboard
    keyboard_read ();

    // print keyboard state on debug console
    Serial.printf ("%02x | %02x %02x %02x %02x %02x %02x | %02x, %02x |%02x \r\n", btn, d1, d2, d3, d4, d5, d6, btn1, btn2, braille);
    
    code_found = 0;

    // search Braille code
    for (uint8_t i = 0; i < sizeof(brcode); i++)
    {
      if (braille == brcode[i])
      {
        code_found = 1;
        {
          // build a sentence with latin letter associated with Braille
          sprintf (sentence, "%c   ", datastr[i]);
          Serial.printf (sentence);

          // announce the letter via TTS
          espeak.say(sentence);
          
          // Pause a little bit
          delay(200);

          // build a sentence with Nato letter name
          sprintf (sentence, "as in %s", nato[i]);
          Serial.printf (sentence);

          // use TTS to anounce Nato code
          espeak.say(sentence);
          delay(25); 
          break;
        }
      }
    }
    if (code_found == 0)
    {
      // search Braille escape description
      for (uint8_t i = 0; i < sizeof(brescape); i++)
      if (braille == brescape[i])
      {
        Serial.printf (escapestr[i]);

        // use TTS to speak Braille escape description
        espeak.say(escapestr[i]);
        delay(25);
        break;
      }
    }
  }
}

void loopb()
{
  
  
  //digitalWrite(PIN_GAIN, _volume[pitch][1] ? HIGH : LOW);     // gain ampli
  //digitalWrite(LED_PIN, _volume[pitch][1] ? HIGH : LOW);     // gain ampli

  //Serial.printf ("pitch=%d volume=%d gain=%d\r\n",pitch, _volume[pitch][0],_volume[pitch][1] );

  espeak.say("Hello the world.");
  delay(500);
  espeak.say("I'm happy.");
  delay(500);
  const char* datastr = "abcdefghijklmnopqrstuvwxyz";
  char sentence[256]; 
  for (int i = 0; i < strlen(datastr); i++)
  {
    sprintf (sentence, "%c   as in %s", datastr[i], nato[i]);
    espeak.say(sentence);
    delay(1000);
  }
  

  

 
  
   
}

static uint8_t _led = 0;




void loop2 ()
{
  digitalWrite(COL2, LOW);
  digitalWrite(COL1, HIGH);
  delay (1);
  d1 = (uint8_t) digitalRead (ROW1);
  d2 = (uint8_t) digitalRead (ROW2);
  d3 = (uint8_t) digitalRead (ROW3);
  btn1 = (uint8_t) digitalRead (BTNROW);

  digitalWrite(COL1, LOW);
  digitalWrite(COL2, HIGH);
  delay (1);
  d4 = (uint8_t) digitalRead (ROW1);
  d5 = (uint8_t) digitalRead (ROW2);
  d6 = (uint8_t) digitalRead (ROW3);
  btn2 = (uint8_t) digitalRead (BTNROW);

  btn = (uint8_t) digitalRead (PIN_BTN);

  Serial.printf ("%02x | %02x %02x %02x %02x %02x %02x | %02x, %02x \r\n", btn, d1, d2, d3, d4, d5, d6, btn1, btn2);

}
