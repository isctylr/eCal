// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t Roboto_Bold_20Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xFF,0xFF,0xFF,0xE0,0x7F,0xC0, // '!'
	0xCF,0x3C,0xB2,0xC8, // '"'
	0x09,0x83,0x30,0x66,0x0C,0xCF,0xFF,0xFF,0xC4,0xC1,0x98,0xFF,0xDF,0xF8,0xD8,0x13,0x06,0x60,0xCC,0x00, // '#'
	0x0C,0x06,0x0F,0x8F,0xEE,0x3F,0x1F,0x80,0xE0,0x7C,0x0F,0x81,0xE0,0x7E,0x3F,0x1D,0xFE,0x7C,0x08,0x04,0x00, // '$'
	0x78,0x07,0xE2,0x33,0x39,0x99,0x8C,0xD8,0x7E,0x81,0xEC,0x00,0xDE,0x07,0xF8,0x6C,0xC6,0x66,0x33,0x33,0x1F,0x80,0x78, // '%'
	0x1E,0x07,0xF0,0x73,0x06,0x30,0x77,0x07,0xE0,0x3C,0x07,0xC6,0xEE,0xEE,0x7E,0xC7,0xCE,0x3C,0xFF,0xE3,0xEF, // '&'
	0xFF,0x6C, // '''
	0x08,0x73,0x8C,0x61,0x86,0x38,0xE3,0x8E,0x38,0xE1,0x86,0x18,0x30,0xE1,0xC2, // '('
	0x43,0x87,0x0C,0x38,0x61,0xC7,0x1C,0x71,0xC7,0x1C,0x71,0x8E,0x31,0xCE,0x10, // ')'
	0x0C,0x06,0x12,0x7F,0xF1,0xC1,0xB0,0xD8,0xC6, // '*'
	0x1C,0x0E,0x07,0x03,0x8F,0xFF,0xFC,0x70,0x38,0x1C,0x0E,0x00, // '+'
	0x77,0x77,0x6C, // ','
	0xFF,0xF0, // '-'
	0x6F,0x60, // '.'
	0x06,0x0C,0x30,0x60,0xC3,0x06,0x1C,0x30,0x61,0xC3,0x06,0x18,0x30,0x00, // '/'
	0x3E,0x3F,0xB8,0xFC,0x7E,0x3F,0x1F,0x8F,0xC7,0xE3,0xF1,0xF8,0xFC,0x77,0xF1,0xF0, // '0'
	0x0D,0xFF,0xE7,0x1C,0x71,0xC7,0x1C,0x71,0xC7,0x1C,0x70, // '1'
	0x1F,0x0F,0xE7,0x1D,0x87,0xE1,0xC0,0x70,0x38,0x1C,0x0F,0x07,0x83,0xC1,0xE0,0x7F,0xDF,0xF0, // '2'
	0x1F,0x1F,0xE7,0x1D,0x87,0x01,0xC0,0x70,0xF8,0x3E,0x01,0xC0,0x7E,0x1D,0xC7,0x7F,0x87,0xC0, // '3'
	0x07,0x01,0xC0,0xF0,0x7C,0x1F,0x0D,0xC7,0x71,0x9C,0xE7,0x3F,0xFF,0xFC,0x1C,0x07,0x01,0xC0, // '4'
	0x7F,0xBF,0xD8,0x0C,0x0E,0x07,0xF3,0xFE,0xC7,0x03,0x80,0xF8,0xFC,0x77,0xF1,0xF0, // '5'
	0x0E,0x0F,0x87,0x81,0xC0,0xE0,0x3F,0xCF,0xFB,0x8E,0xE1,0xB8,0x7E,0x1B,0x8E,0x7F,0x0F,0x80, // '6'
	0xFF,0xFF,0xF0,0x38,0x0E,0x03,0x01,0xC0,0x60,0x38,0x0E,0x07,0x01,0xC0,0xE0,0x38,0x1C,0x00, // '7'
	0x3E,0x3F,0xB8,0xFC,0x7E,0x3F,0x1D,0xFC,0xFE,0xE3,0xF1,0xF8,0xFC,0x7F,0xF9,0xF0, // '8'
	0x3E,0x3F,0xB8,0xFC,0x7C,0x3F,0x1F,0x8F,0xFF,0x3F,0x81,0xC0,0xC1,0xE3,0xE1,0xC0, // '9'
	0x6F,0x60,0x00,0x00,0x6F,0x60, // ':'
	0x33,0xCC,0x00,0x00,0x00,0x73,0x9C,0xE6,0x60, // ';'
	0x01,0x0F,0x3F,0xF8,0xC0,0xF8,0x3F,0x0F,0x01, // '<'
	0xFF,0xFF,0xC0,0x00,0x0F,0xFF,0xFC, // '='
	0x80,0x78,0x3F,0x03,0xF0,0x38,0xFF,0xF1,0xE0,0x80,0x00, // '>'
	0x3E,0x3F,0xDC,0xFC,0x70,0x38,0x38,0x38,0x18,0x1C,0x00,0x00,0x01,0x81,0xC0,0xE0, // '?'
	0x03,0xF0,0x0F,0xF8,0x3C,0x1C,0x30,0x06,0x61,0xE3,0x63,0xF3,0xC6,0x33,0xC6,0x23,0xCC,0x63,0xCC,0x63,0xCC,0x63,0xCE,0x63,0xC7,0xBE,0xE7,0xBC,0x60,0x00,0x38,0x20,0x1F,0xE0,0x07,0xC0, // '@'
	0x07,0x00,0x3C,0x03,0xE0,0x1F,0x00,0xDC,0x0E,0xE0,0x73,0x83,0x1C,0x38,0xE1,0xFF,0x9F,0xFC,0xE0,0xE7,0x03,0xF0,0x1C, // 'A'
	0xFF,0x1F,0xFB,0x87,0x70,0x7E,0x0F,0xC3,0xBF,0xE7,0xFE,0xE1,0xFC,0x1F,0x83,0xF0,0xFF,0xFD,0xFF,0x00, // 'B'
	0x1F,0x07,0xF9,0xC3,0xF0,0x7E,0x0F,0xC0,0x38,0x07,0x00,0xE0,0x1C,0x1F,0x83,0xB8,0xF3,0xFC,0x3E,0x00, // 'C'
	0xFE,0x1F,0xF3,0x87,0x70,0xEE,0x0F,0xC1,0xF8,0x3F,0x07,0xE0,0xFC,0x1F,0x87,0x70,0xEF,0xF9,0xFC,0x00, // 'D'
	0xFF,0xFF,0xFE,0x03,0x80,0xE0,0x38,0x0F,0xFB,0xFE,0xE0,0x38,0x0E,0x03,0x80,0xFF,0xFF,0xF0, // 'E'
	0xFF,0xFF,0xFE,0x03,0x80,0xE0,0x38,0x0F,0xFB,0xFE,0xE0,0x38,0x0E,0x03,0x80,0xE0,0x38,0x00, // 'F'
	0x1F,0x83,0xFC,0x70,0xE7,0x06,0xE0,0x7E,0x00,0xE0,0x0E,0x3F,0xE3,0xFE,0x07,0x70,0x77,0x87,0x3F,0xE0,0xFC, // 'G'
	0xE0,0x7E,0x07,0xE0,0x7E,0x07,0xE0,0x7E,0x07,0xFF,0xFF,0xFF,0xE0,0x7E,0x07,0xE0,0x7E,0x07,0xE0,0x7E,0x07, // 'H'
	0xFF,0xFF,0xFF,0xFF,0xFF,0xC0, // 'I'
	0x01,0xC0,0x70,0x1C,0x07,0x01,0xC0,0x70,0x1C,0x07,0x01,0xC0,0x7E,0x1D,0xCE,0x7F,0x8F,0x80, // 'J'
	0xE0,0xFE,0x1E,0xE3,0xCE,0x78,0xE7,0x0E,0xE0,0xFE,0x0F,0xF0,0xFF,0x0F,0x38,0xE3,0xCE,0x1C,0xE0,0xEE,0x0F, // 'K'
	0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03,0x81,0xC0,0xE0,0x70,0x38,0x1C,0x0F,0xFF,0xFC, // 'L'
	0xF0,0x1F,0xF0,0x3F,0xE0,0xFF,0xC1,0xFF,0xC3,0x7D,0x8F,0xFB,0x1F,0xF7,0x37,0xE6,0xEF,0xCF,0x9F,0x9F,0x3F,0x1E,0x7E,0x38,0xFC,0x31,0xC0, // 'M'
	0xE0,0x7F,0x07,0xF8,0x7F,0x87,0xFC,0x7E,0xE7,0xEE,0x7E,0x77,0xE7,0x7E,0x3F,0xE1,0xFE,0x1F,0xE0,0xFE,0x07, // 'N'
	0x1F,0x83,0xFC,0x70,0xE7,0x0E,0xE0,0x7E,0x07,0xE0,0x7E,0x07,0xE0,0x7E,0x07,0x70,0xE7,0x0E,0x3F,0xC1,0xF8, // 'O'
	0xFF,0x9F,0xFB,0x87,0xF0,0x7E,0x0F,0xC1,0xF8,0x3F,0xFE,0xFF,0x9C,0x03,0x80,0x70,0x0E,0x01,0xC0,0x00, // 'P'
	0x1F,0x83,0xFC,0x70,0xE6,0x0E,0xE0,0x7E,0x07,0xE0,0x7E,0x07,0xE0,0x7E,0x07,0x70,0xE7,0x0E,0x3F,0xC1,0xFC,0x00,0xF0,0x06, // 'Q'
	0xFF,0x9F,0xFB,0x87,0xF0,0x7E,0x0F,0xC1,0xF8,0x77,0xFE,0xFF,0x9C,0x73,0x8F,0x70,0xEE,0x0F,0xC1,0xC0, // 'R'
	0x3F,0x1F,0xEE,0x1F,0x87,0xE0,0x3C,0x07,0xE0,0x7E,0x03,0xC0,0x7E,0x1F,0x87,0x7F,0xCF,0xC0, // 'S'
	0xFF,0xFF,0xFF,0x07,0x00,0x70,0x07,0x00,0x70,0x07,0x00,0x70,0x07,0x00,0x70,0x07,0x00,0x70,0x07,0x00,0x70, // 'T'
	0xE0,0xFC,0x1F,0x83,0xF0,0x7E,0x0F,0xC1,0xF8,0x3F,0x07,0xE0,0xFC,0x1F,0x83,0xB8,0xE7,0xFC,0x3E,0x00, // 'U'
	0xE0,0x3B,0x83,0x9C,0x1C,0xE0,0xE3,0x8E,0x1C,0x70,0xE3,0x83,0xB8,0x1D,0xC0,0xEE,0x03,0xE0,0x1F,0x00,0xF8,0x03,0x80, // 'V'
	0xE1,0xC3,0xF0,0xE1,0xD8,0x70,0xCE,0x7C,0xE7,0x3E,0x73,0x9B,0x38,0xCD,0x98,0x66,0xEC,0x3F,0x7E,0x1F,0x1F,0x0F,0x8F,0x83,0xC7,0x81,0xE3,0xC0,0xE0,0xE0, // 'W'
	0xF0,0x73,0xC7,0x0E,0x38,0x7B,0x81,0xDC,0x07,0xC0,0x3E,0x01,0xF0,0x0F,0x80,0xEE,0x0F,0x70,0x71,0xC7,0x0F,0x78,0x3C, // 'X'
	0xE0,0x77,0x0F,0x70,0xE3,0x9E,0x39,0xC1,0xD8,0x1F,0x80,0xF0,0x0F,0x00,0x70,0x07,0x00,0x70,0x07,0x00,0x70, // 'Y'
	0xFF,0xDF,0xF8,0x0F,0x01,0xC0,0x70,0x1E,0x03,0x80,0xE0,0x3C,0x07,0x01,0xC0,0x78,0x0F,0xFF,0xFF,0xC0, // 'Z'
	0xFF,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xFF, // '['
	0xE0,0x30,0x1C,0x0E,0x03,0x81,0xC0,0x60,0x38,0x1C,0x07,0x03,0x80,0xC0,0x70,0x38,0x0E, // '\'
	0xFF,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0xFF, // ']'
	0x38,0x71,0xF3,0x66,0xD8,0xF1,0x80, // '^'
	0xFF,0xFF,0xC0, // '_'
	0xE3,0x8E, // '`'
	0x3E,0x7F,0xB8,0xC0,0x73,0xFF,0xFF,0x8F,0xC7,0xE7,0xFF,0xDE,0xE0, // 'a'
	0xE0,0x70,0x38,0x1C,0x0E,0xE7,0xFB,0x8F,0xC7,0xE1,0xF0,0xF8,0x7C,0x7E,0x3F,0xFB,0xF8, // 'b'
	0x1F,0x0F,0xE7,0x39,0x87,0xE0,0x38,0x0E,0x01,0x87,0x71,0x8F,0xE1,0xF0, // 'c'
	0x03,0x81,0xC0,0xE0,0x73,0xBB,0xFF,0x8F,0xC7,0xC3,0xE1,0xF0,0xFC,0x7E,0x3B,0xFC,0xFE, // 'd'
	0x3E,0x3F,0xB8,0xFC,0x3F,0xFF,0xFF,0x81,0xC2,0xF1,0xBF,0xC7,0x80, // 'e'
	0x1E,0x7C,0xE1,0xCF,0xFF,0xCE,0x1C,0x38,0x70,0xE1,0xC3,0x87,0x0E,0x00, // 'f'
	0x1E,0xCF,0xF7,0x1D,0xC7,0x61,0xF8,0x76,0x1D,0xC7,0x71,0xCF,0xF1,0xFC,0x07,0x21,0xDF,0xE1,0xF0, // 'g'
	0xE0,0x70,0x38,0x1C,0x0E,0xF7,0xFB,0x8F,0xC7,0xE3,0xF1,0xF8,0xFC,0x7E,0x3F,0x1F,0x8E, // 'h'
	0xFF,0x8F,0xFF,0xFF,0xFF,0xF8, // 'i'
	0x39,0xCE,0x03,0x9C,0xE7,0x39,0xCE,0x73,0x9C,0xE7,0x3F,0xB8, // 'j'
	0xE0,0x38,0x0E,0x03,0x80,0xE3,0xF9,0xCE,0xE3,0xF8,0xFC,0x3F,0x0F,0xE3,0xBC,0xE7,0x38,0xEE,0x3C, // 'k'
	0xFF,0xFF,0xFF,0xFF,0xFF,0xF8, // 'l'
	0xEF,0x3D,0xFE,0xFF,0x8E,0x3F,0x1C,0x7E,0x38,0xFC,0x71,0xF8,0xE3,0xF1,0xC7,0xE3,0x8F,0xC7,0x1F,0x8E,0x38, // 'm'
	0xEF,0x7F,0xF8,0xFC,0x7E,0x3F,0x1F,0x8F,0xC7,0xE3,0xF1,0xF8,0xE0, // 'n'
	0x1F,0x07,0xF1,0xC7,0x38,0xE6,0x0D,0xC1,0x98,0x3B,0x8E,0x71,0xC7,0xF0,0x7C,0x00, // 'o'
	0xFE,0x7F,0xB8,0xFC,0x7E,0x1F,0x0F,0x87,0xC7,0xE3,0xFF,0xBB,0x9C,0x0E,0x07,0x03,0x80, // 'p'
	0x1F,0xCF,0xF7,0x1D,0xC7,0x61,0xF8,0x76,0x1D,0xC7,0x71,0xCF,0xF1,0xDC,0x07,0x01,0xC0,0x70,0x1C, // 'q'
	0xFF,0xFE,0x38,0xE3,0x8E,0x38,0xE3,0x8E,0x00, // 'r'
	0x1E,0x3F,0xDC,0xEE,0x07,0xC1,0xF8,0x3F,0xC3,0x73,0xBF,0xC7,0x80, // 's'
	0x38,0x70,0xE7,0xEF,0xC7,0x0E,0x1C,0x38,0x70,0xE1,0xC3,0xE3,0xC0, // 't'
	0xE3,0xF1,0xF8,0xFC,0x7E,0x3F,0x1F,0x8F,0xC7,0xE3,0xFF,0xDE,0xE0, // 'u'
	0xE1,0xD8,0x67,0x39,0xCE,0x33,0x0D,0xC3,0xF0,0xF8,0x1E,0x07,0x81,0xC0, // 'v'
	0xE3,0x8E,0xC7,0x19,0xCE,0x73,0xBC,0xE3,0x6D,0x86,0xDB,0x0D,0xB6,0x1E,0x7C,0x3C,0x70,0x38,0xE0,0x71,0xC0, // 'w'
	0xF1,0xDC,0xE3,0xB8,0xFC,0x1E,0x07,0x81,0xF0,0xFC,0x3B,0x9C,0xEF,0x1C, // 'x'
	0xE1,0xD8,0x67,0x39,0xCE,0x33,0x0F,0xC3,0xF0,0x78,0x1E,0x07,0x80,0xC0,0x30,0x1C,0x1E,0x07,0x00, // 'y'
	0xFF,0x7F,0x83,0xC1,0xC1,0xC1,0xE0,0xE0,0xE0,0xF0,0x7F,0xFF,0xE0, // 'z'
	0x09,0xCC,0xE7,0x39,0xCE,0x77,0x38,0xE7,0x39,0xCE,0x71,0x8E,0x10, // '{'
	0xFF,0xFF,0x80, // '|'
	0x87,0x18,0xE7,0x39,0xCE,0x71,0xCE,0xE7,0x39,0xCE,0x63,0x39,0x00 // '}'
};
const GFXglyph Roboto_Bold_20Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   1,   1,   6,    0,   -1 }, // ' '
	  {     1,   3,  14,   6,    1,  -14 }, // '!'
	  {     7,   6,   5,   7,    0,  -15 }, // '"'
	  {    11,  11,  14,  13,    1,  -14 }, // '#'
	  {    31,   9,  18,  12,    1,  -16 }, // '$'
	  {    52,  13,  14,  16,    1,  -14 }, // '%'
	  {    75,  12,  14,  14,    1,  -14 }, // '&'
	  {    96,   3,   5,   4,    0,  -15 }, // '''
	  {    98,   6,  20,   8,    1,  -16 }, // '('
	  {   113,   6,  20,   8,    0,  -16 }, // ')'
	  {   128,   9,   8,  10,    0,  -14 }, // '*'
	  {   137,   9,  10,  12,    1,  -12 }, // '+'
	  {   149,   4,   6,   6,    0,   -3 }, // ','
	  {   152,   6,   2,   9,    1,   -7 }, // '-'
	  {   154,   4,   3,   7,    1,   -3 }, // '.'
	  {   156,   7,  15,   8,    0,  -14 }, // '/'
	  {   170,   9,  14,  12,    1,  -14 }, // '0'
	  {   186,   6,  14,  12,    2,  -14 }, // '1'
	  {   197,  10,  14,  12,    0,  -14 }, // '2'
	  {   215,  10,  14,  12,    0,  -14 }, // '3'
	  {   233,  10,  14,  12,    1,  -14 }, // '4'
	  {   251,   9,  14,  12,    1,  -14 }, // '5'
	  {   267,  10,  14,  12,    1,  -14 }, // '6'
	  {   285,  10,  14,  12,    1,  -14 }, // '7'
	  {   303,   9,  14,  12,    1,  -14 }, // '8'
	  {   319,   9,  14,  12,    1,  -14 }, // '9'
	  {   335,   4,  11,   7,    1,  -11 }, // ':'
	  {   341,   5,  14,   6,    0,  -11 }, // ';'
	  {   350,   8,   9,  11,    1,  -11 }, // '<'
	  {   359,   9,   6,  12,    1,   -9 }, // '='
	  {   366,   9,   9,  11,    1,  -11 }, // '>'
	  {   377,   9,  14,  11,    0,  -14 }, // '?'
	  {   393,  16,  18,  19,    1,  -14 }, // '@'
	  {   429,  13,  14,  14,    0,  -14 }, // 'A'
	  {   452,  11,  14,  14,    1,  -14 }, // 'B'
	  {   472,  11,  14,  14,    1,  -14 }, // 'C'
	  {   492,  11,  14,  14,    1,  -14 }, // 'D'
	  {   512,  10,  14,  12,    1,  -14 }, // 'E'
	  {   530,  10,  14,  12,    1,  -14 }, // 'F'
	  {   548,  12,  14,  15,    1,  -14 }, // 'G'
	  {   569,  12,  14,  15,    1,  -14 }, // 'H'
	  {   590,   3,  14,   7,    1,  -14 }, // 'I'
	  {   596,  10,  14,  12,    0,  -14 }, // 'J'
	  {   614,  12,  14,  14,    1,  -14 }, // 'K'
	  {   635,   9,  14,  12,    1,  -14 }, // 'L'
	  {   651,  15,  14,  19,    1,  -14 }, // 'M'
	  {   678,  12,  14,  15,    1,  -14 }, // 'N'
	  {   699,  12,  14,  15,    1,  -14 }, // 'O'
	  {   720,  11,  14,  14,    1,  -14 }, // 'P'
	  {   740,  12,  16,  15,    1,  -14 }, // 'Q'
	  {   764,  11,  14,  14,    1,  -14 }, // 'R'
	  {   784,  10,  14,  13,    1,  -14 }, // 'S'
	  {   802,  12,  14,  13,    0,  -14 }, // 'T'
	  {   823,  11,  14,  14,    1,  -14 }, // 'U'
	  {   843,  13,  14,  14,    0,  -14 }, // 'V'
	  {   866,  17,  14,  18,    0,  -14 }, // 'W'
	  {   896,  13,  14,  14,    0,  -14 }, // 'X'
	  {   919,  12,  14,  13,    0,  -14 }, // 'Y'
	  {   940,  11,  14,  13,    1,  -14 }, // 'Z'
	  {   960,   4,  20,   7,    1,  -17 }, // '['
	  {   970,   9,  15,   9,    0,  -14 }, // '\'
	  {   987,   4,  20,   7,    0,  -17 }, // ']'
	  {   997,   7,   7,  10,    1,  -14 }, // '^'
	  {  1004,   9,   2,  10,    0,    0 }, // '_'
	  {  1007,   5,   3,   8,    1,  -15 }, // '`'
	  {  1009,   9,  11,  12,    1,  -11 }, // 'a'
	  {  1022,   9,  15,  12,    1,  -15 }, // 'b'
	  {  1039,  10,  11,  11,    0,  -11 }, // 'c'
	  {  1053,   9,  15,  12,    1,  -15 }, // 'd'
	  {  1070,   9,  11,  12,    1,  -11 }, // 'e'
	  {  1083,   7,  15,   8,    0,  -15 }, // 'f'
	  {  1097,  10,  15,  12,    0,  -11 }, // 'g'
	  {  1116,   9,  15,  12,    1,  -15 }, // 'h'
	  {  1133,   3,  15,   6,    1,  -15 }, // 'i'
	  {  1139,   5,  19,   6,   -1,  -15 }, // 'j'
	  {  1151,  10,  15,  12,    1,  -15 }, // 'k'
	  {  1170,   3,  15,   6,    1,  -15 }, // 'l'
	  {  1176,  15,  11,  18,    1,  -11 }, // 'm'
	  {  1197,   9,  11,  12,    1,  -11 }, // 'n'
	  {  1210,  11,  11,  12,    0,  -11 }, // 'o'
	  {  1226,   9,  15,  12,    1,  -11 }, // 'p'
	  {  1243,  10,  15,  12,    0,  -11 }, // 'q'
	  {  1262,   6,  11,   8,    1,  -11 }, // 'r'
	  {  1271,   9,  11,  11,    0,  -11 }, // 's'
	  {  1284,   7,  14,   8,    0,  -14 }, // 't'
	  {  1297,   9,  11,  12,    1,  -11 }, // 'u'
	  {  1310,  10,  11,  11,    0,  -11 }, // 'v'
	  {  1324,  15,  11,  16,    0,  -11 }, // 'w'
	  {  1345,  10,  11,  11,    0,  -11 }, // 'x'
	  {  1359,  10,  15,  11,    0,  -11 }, // 'y'
	  {  1378,   9,  11,  11,    1,  -11 }, // 'z'
	  {  1391,   5,  20,   8,    1,  -16 }, // '{'
	  {  1404,   1,  17,   6,    2,  -14 }, // '|'
	  {  1407,   5,  20,   8,    1,  -16 } // '}'
};
const GFXfont Roboto_Bold_20 PROGMEM = {
(uint8_t  *)Roboto_Bold_20Bitmaps,(GFXglyph *)Roboto_Bold_20Glyphs,0x20, 0x7E, 24};