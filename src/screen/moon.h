const uint32_t moon_width = 75;
const uint32_t moon_height = 75;
const uint8_t moon_data[(76*75)/2] = {
0xEF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFE, 0xFF, 0xFF, 0xEE, 0xBD, 0x89, 0x77, 0x97, 0x89, 0x98, 0xCB, 0xEE, 0xFE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xEF, 0xFE, 0xFF, 0xEF, 0xFE, 0xFF, 0xEF, 0xEE, 0x0F, 
  0xEF, 0xFE, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xEF, 0xFF, 0xEF, 0x9C, 0x67, 0x35, 0x33, 0x32, 0x54, 0x55, 0x65, 0x97, 0xA9, 0xCB, 0xFE, 0xFF, 0xEF, 0xFE, 0xFF, 0xFF, 0xFE, 0xFF, 0xEF, 0xFE, 0xFF, 0xFF, 0xEE, 0x0F, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xDF, 0x69, 0x23, 0x32, 0x33, 0x33, 0x44, 0x34, 0x54, 0x77, 0x98, 0xA9, 0x9A, 0xA9, 0xDC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xEE, 0xFE, 0xFF, 0xEF, 0xFE, 0xFF, 0xEF, 0xFF, 0xCF, 0x38, 0x12, 0x32, 0x23, 0x33, 0x54, 0x77, 0x55, 0x65, 0x87, 0x99, 0xAA, 0xAA, 0x89, 0x88, 0xDA, 0xFF, 0xEF, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0x0E, 
  0xFF, 0xFF, 0xEE, 0xFE, 0xFF, 0xEF, 0xFE, 0xFF, 0xFF, 0xDF, 0x59, 0x12, 0x21, 0x33, 0x33, 0x33, 0x53, 0x77, 0x77, 0x77, 0x87, 0x99, 0x99, 0x99, 0x89, 0x88, 0x88, 0xDB, 0xFE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0x5A, 0x54, 0x23, 0x22, 0x32, 0x33, 0x43, 0x54, 0x87, 0x78, 0x76, 0x88, 0x99, 0x99, 0x89, 0x99, 0x98, 0x9A, 0x89, 0xEB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 
  0xEF, 0xFE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xFF, 0x6A, 0x54, 0x56, 0x22, 0x33, 0x33, 0x33, 0x53, 0x66, 0x98, 0x88, 0x88, 0x77, 0x98, 0x99, 0x99, 0xA9, 0x99, 0xAA, 0xAA, 0xA9, 0xEC, 0xFF, 0xFF, 0xEF, 0xFE, 0xFF, 0xFF, 0xEE, 0x0F, 
  0xEF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0x8E, 0x12, 0x75, 0x47, 0x32, 0x33, 0x33, 0x43, 0x54, 0x97, 0x99, 0xAA, 0x68, 0x87, 0x88, 0x98, 0xB9, 0xAA, 0x9A, 0xA9, 0xBA, 0x9B, 0xB9, 0xFE, 0xFF, 0xEF, 0xFE, 0xFF, 0xEF, 0xEE, 0x0F, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0x16, 0x41, 0x87, 0x46, 0x44, 0x33, 0x33, 0x64, 0x75, 0xA9, 0x79, 0x77, 0x45, 0xA6, 0x9A, 0xA9, 0xA9, 0x9A, 0x9A, 0xAA, 0xAA, 0xBA, 0x99, 0xEB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xFF, 0x4C, 0x21, 0x73, 0x78, 0x55, 0x56, 0x45, 0x54, 0x76, 0x97, 0x9A, 0x68, 0x55, 0x55, 0x86, 0xA9, 0xBA, 0xAA, 0xA9, 0xA9, 0xAA, 0xAB, 0xBA, 0xAA, 0xA9, 0xFD, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xEF, 0xFE, 0xFF, 0xCF, 0x14, 0x42, 0x96, 0x68, 0x55, 0x55, 0x55, 0x76, 0x87, 0xA8, 0x9B, 0x57, 0x55, 0x66, 0x77, 0x98, 0xBA, 0xAB, 0xAA, 0xAA, 0xAA, 0xAA, 0xCA, 0xAB, 0x9A, 0xDB, 0xFF, 0xFF, 0xEE, 0xFE, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x4C, 0x31, 0x75, 0x99, 0x56, 0x55, 0x44, 0x34, 0x75, 0x88, 0x98, 0x99, 0x67, 0x66, 0x66, 0x98, 0xAA, 0xBA, 0xBB, 0xAA, 0xAA, 0xBA, 0xAA, 0xBA, 0xAB, 0xBB, 0xAA, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 
  0xEF, 0xEE, 0xFF, 0xFF, 0xDF, 0x26, 0x54, 0xB8, 0x89, 0x45, 0x54, 0x44, 0x34, 0x84, 0x89, 0x98, 0x99, 0x88, 0x89, 0x87, 0xB9, 0xCB, 0xBC, 0xAB, 0xBB, 0xAB, 0xAA, 0xBB, 0xAA, 0xBB, 0xBA, 0xAA, 0xEB, 0xFF, 0xFF, 0xEF, 0xEE, 0x0F, 
  0xFF, 0xEE, 0xFF, 0xFF, 0x7D, 0x66, 0x86, 0xAA, 0x78, 0x36, 0x33, 0x43, 0x44, 0x95, 0x9A, 0x99, 0x89, 0x87, 0x99, 0xBA, 0xCC, 0xBB, 0xDC, 0xBC, 0xBB, 0xBB, 0xAA, 0xBB, 0xBB, 0xAA, 0xBB, 0xBB, 0xB9, 0xFE, 0xFF, 0xEF, 0xEE, 0x0F, 
  0xEF, 0xFE, 0xFF, 0xFF, 0x58, 0x77, 0x88, 0x99, 0x77, 0x35, 0x33, 0x33, 0x44, 0x85, 0x89, 0x88, 0x67, 0x87, 0xBA, 0xCB, 0xDD, 0xBB, 0xCB, 0xCC, 0xAB, 0xBB, 0xAB, 0xBA, 0xCC, 0xAB, 0xBB, 0xBB, 0xAB, 0xFC, 0xFF, 0xFF, 0xFE, 0x0F, 
  0xFF, 0xFF, 0xFF, 0xBF, 0x76, 0x77, 0x87, 0x89, 0x46, 0x23, 0x33, 0x33, 0x43, 0x45, 0x55, 0x55, 0x66, 0x97, 0xCB, 0xDC, 0xCD, 0xBB, 0xAB, 0xBB, 0xCC, 0xBC, 0xAB, 0xBB, 0xBC, 0xBB, 0xBB, 0xBB, 0xBB, 0xDB, 0xEF, 0xFF, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xFF, 0x8D, 0x87, 0x78, 0x86, 0x69, 0x34, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x54, 0x66, 0x97, 0xCB, 0xDD, 0xBC, 0xBB, 0xAA, 0xAA, 0xCC, 0xDC, 0xBC, 0xCB, 0xCC, 0xBB, 0xBB, 0xBB, 0xCB, 0xBB, 0xEE, 0xFE, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xEF, 0x79, 0xA9, 0x79, 0x98, 0x59, 0x44, 0x34, 0x33, 0x33, 0x43, 0x44, 0x44, 0x85, 0x78, 0x98, 0xCB, 0xCC, 0xBC, 0xBB, 0xAB, 0xAA, 0xBB, 0xCB, 0xCC, 0xBB, 0xDC, 0xBC, 0xCB, 0xBB, 0xBB, 0xBC, 0xEC, 0xFF, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xCF, 0x87, 0xA9, 0x99, 0x89, 0x56, 0x55, 0x34, 0x33, 0x33, 0x33, 0x43, 0x44, 0xA6, 0xAB, 0xAA, 0xDC, 0xBC, 0xBB, 0xBB, 0xBB, 0xBB, 0xAB, 0xBB, 0xDC, 0xBC, 0xCB, 0xBC, 0xCB, 0xCC, 0xCB, 0xCC, 0xEC, 0xFF, 0xFF, 0x0F, 
  0xEF, 0xFE, 0x8E, 0x97, 0xA9, 0x99, 0x8A, 0x66, 0x66, 0x34, 0x44, 0x44, 0x43, 0x43, 0x44, 0xA6, 0xCC, 0xCC, 0xCC, 0xBC, 0xBB, 0xBA, 0xBB, 0xCC, 0xBB, 0xAB, 0xCB, 0xCC, 0xBC, 0xCC, 0xCB, 0xCC, 0xCC, 0xCC, 0xDC, 0xFF, 0xEE, 0x0F, 
  0xEF, 0xFE, 0x7C, 0x98, 0xA9, 0xA9, 0x9A, 0x88, 0x68, 0x34, 0x44, 0x44, 0x44, 0x44, 0x44, 0x96, 0xDC, 0xDD, 0xBC, 0xCD, 0xBC, 0xAB, 0xBB, 0xCC, 0xCC, 0xBB, 0xCB, 0xDC, 0xCD, 0xDC, 0xCD, 0xDD, 0xCC, 0xCC, 0xCC, 0xFE, 0xEE, 0x0F, 
  0xFF, 0xEF, 0x78, 0x99, 0x99, 0xBA, 0x9B, 0x88, 0x57, 0x43, 0x33, 0x34, 0x44, 0x45, 0x54, 0x96, 0xCB, 0xDC, 0xBC, 0xDD, 0xBC, 0xBB, 0xBB, 0xCC, 0xDC, 0xCD, 0xCB, 0xCC, 0xDC, 0xDD, 0xDD, 0xDD, 0xDD, 0xCD, 0xCC, 0xFD, 0xFF, 0x0F, 
  0xFF, 0xBF, 0x87, 0x99, 0xA9, 0xAA, 0x8A, 0x67, 0x44, 0x44, 0x34, 0x33, 0x43, 0x44, 0x65, 0x97, 0xBB, 0xBB, 0xBB, 0xCB, 0xBB, 0xCB, 0xBB, 0xCB, 0xDC, 0xCD, 0xCC, 0xCD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDE, 0xCD, 0xCC, 0xED, 0xFF, 0x0F, 
  0xFF, 0x9F, 0x77, 0x78, 0x98, 0x99, 0x68, 0x45, 0x44, 0x44, 0x44, 0x43, 0x33, 0x44, 0x86, 0xA9, 0xBB, 0xBB, 0xCB, 0xBB, 0xBB, 0xCB, 0xAC, 0xBA, 0xCB, 0xCD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xED, 0xDD, 0xDC, 0xCC, 0xED, 0xFF, 0x0F, 
  0xFF, 0x8D, 0x98, 0x79, 0x87, 0x89, 0x45, 0x44, 0x44, 0x44, 0x44, 0x43, 0x33, 0x65, 0x87, 0xA9, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xCB, 0xBC, 0xAA, 0xBB, 0xCB, 0xDD, 0xED, 0xDD, 0xEE, 0xDD, 0xED, 0xDE, 0xDD, 0xDD, 0xED, 0xFF, 0x0F, 
  0xFF, 0x7B, 0x88, 0x67, 0x85, 0x79, 0x34, 0x54, 0x44, 0x44, 0x65, 0x35, 0x64, 0x87, 0x99, 0xBA, 0xBB, 0xBB, 0xCB, 0xBC, 0xBB, 0xBB, 0xBC, 0xBB, 0xBB, 0xCB, 0xDD, 0xDD, 0xDD, 0xEE, 0xEE, 0xED, 0xEE, 0xDD, 0xED, 0xEE, 0xFE, 0x0F, 
  0xEF, 0x7A, 0x78, 0x56, 0x96, 0x69, 0x43, 0x44, 0x44, 0x54, 0x75, 0x67, 0x76, 0xA8, 0xAA, 0xCB, 0xBC, 0xBB, 0xCB, 0xCD, 0xBB, 0xBB, 0xCB, 0xBC, 0xCB, 0xDD, 0xDD, 0xDD, 0xDD, 0xEE, 0xEE, 0xEE, 0xDE, 0xDD, 0xDD, 0xEE, 0xEE, 0x0F, 
  0xDF, 0x79, 0x78, 0x66, 0x87, 0x47, 0x44, 0x45, 0x55, 0x55, 0x84, 0x88, 0x89, 0xA9, 0xBA, 0xDC, 0xBD, 0xBB, 0xCB, 0xCD, 0xBC, 0xBB, 0xCB, 0xBD, 0xBB, 0xDD, 0xDD, 0xED, 0xFE, 0xEE, 0xEE, 0xDE, 0xEE, 0xEE, 0xDD, 0xEE, 0xED, 0x0F, 
  0xCF, 0x88, 0x87, 0x88, 0x66, 0x55, 0x55, 0x55, 0x55, 0x56, 0x95, 0x78, 0x88, 0x99, 0xB9, 0xDC, 0xCC, 0xCB, 0xBC, 0xCC, 0xAB, 0xBB, 0xBB, 0xBC, 0xBB, 0xCB, 0xDC, 0xDD, 0xFF, 0xEF, 0xEE, 0xDD, 0xED, 0xEE, 0xEE, 0xDE, 0xED, 0x0F, 
  0xBF, 0x89, 0x88, 0x78, 0x56, 0x55, 0x56, 0x55, 0x66, 0x55, 0x65, 0x56, 0x66, 0x77, 0xA8, 0xBB, 0xCB, 0xCC, 0xBC, 0xBB, 0xAB, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xDB, 0xDD, 0xEE, 0xEE, 0xEE, 0xEE, 0xED, 0xEE, 0xDD, 0xDD, 0xED, 0x0E, 
  0xAE, 0x88, 0x98, 0x68, 0x67, 0x56, 0x55, 0x55, 0x55, 0x44, 0x55, 0x66, 0x67, 0x65, 0x87, 0xAA, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAA, 0xBB, 0xCB, 0xCC, 0xCC, 0xCC, 0xED, 0xEE, 0xEE, 0xEE, 0xFE, 0xEE, 0xDE, 0xCD, 0xDC, 0xDD, 0x0E, 
  0xAE, 0x89, 0x98, 0x78, 0x86, 0x57, 0x55, 0x55, 0x55, 0x55, 0x65, 0x96, 0x69, 0x54, 0x86, 0xB9, 0xBB, 0xBB, 0xAB, 0xBB, 0xAB, 0xBA, 0xBB, 0xCB, 0xCC, 0xBC, 0xBB, 0xCB, 0xED, 0xEE, 0xEF, 0xDE, 0xEE, 0xDE, 0xDD, 0xDD, 0xDD, 0x0F, 
  0x8D, 0x88, 0x87, 0x68, 0x87, 0x57, 0x55, 0x55, 0x55, 0x44, 0x65, 0x86, 0x59, 0x44, 0x86, 0xCA, 0xAB, 0xAA, 0xAA, 0xBB, 0xAB, 0xBA, 0xBB, 0xBB, 0xCB, 0xAB, 0x89, 0xA8, 0xDC, 0xDD, 0xEE, 0xEE, 0xEE, 0xDD, 0xDD, 0xDD, 0xDC, 0x0F, 
  0x7C, 0x76, 0x88, 0x77, 0x98, 0x57, 0x55, 0x55, 0x45, 0x44, 0x64, 0x66, 0x56, 0x54, 0x86, 0xAA, 0x9A, 0x88, 0xA9, 0xCB, 0xAC, 0xBA, 0xAB, 0x9A, 0xCB, 0xAA, 0x78, 0x97, 0xCB, 0xDD, 0xED, 0xEE, 0xEE, 0xCD, 0xDD, 0xCC, 0xDC, 0x0F, 
  0x6B, 0x86, 0x88, 0x98, 0xA9, 0x56, 0x56, 0x65, 0x56, 0x44, 0x65, 0x66, 0x55, 0x55, 0x96, 0x9A, 0x9A, 0x67, 0xA7, 0xBB, 0xBC, 0xBB, 0x9B, 0x88, 0x98, 0x78, 0x67, 0x76, 0xA9, 0xDC, 0xDD, 0xDD, 0xDD, 0xDD, 0xCC, 0xCC, 0xDC, 0x0E, 
  0x6B, 0x76, 0x98, 0x9A, 0xAA, 0x57, 0x55, 0x65, 0x55, 0x55, 0x76, 0x77, 0x66, 0x56, 0xA7, 0xAA, 0x99, 0x78, 0xA7, 0xBB, 0xBB, 0xBB, 0x9B, 0x98, 0x66, 0x66, 0x66, 0x76, 0xA8, 0xDB, 0xDE, 0xDD, 0xDD, 0xCD, 0xCC, 0xCC, 0xDD, 0x0E, 
  0x6B, 0x76, 0xA8, 0xAA, 0xAA, 0x68, 0x66, 0x66, 0x76, 0x87, 0x88, 0x88, 0x66, 0x66, 0x97, 0xA9, 0x9A, 0x77, 0xA9, 0xCB, 0xBB, 0xAB, 0x9A, 0x88, 0x67, 0x77, 0x67, 0x66, 0xA7, 0xDB, 0xDE, 0xDC, 0xDD, 0xCC, 0xCC, 0xCC, 0xDC, 0x0E, 
  0x6B, 0x86, 0x99, 0xBA, 0xAA, 0x9A, 0x99, 0x78, 0x97, 0xA9, 0xAA, 0x89, 0x67, 0x66, 0x76, 0xA9, 0x8A, 0x66, 0xA9, 0xBA, 0xBB, 0x8A, 0x78, 0x67, 0x76, 0x67, 0x76, 0x67, 0x87, 0xDB, 0xCE, 0xDD, 0xCC, 0xCC, 0xCD, 0xCC, 0xDC, 0x0E, 
  0x7C, 0x86, 0x99, 0xB9, 0xBB, 0xBC, 0xAB, 0x79, 0x97, 0x99, 0xBA, 0x9A, 0x89, 0x77, 0x55, 0x98, 0x78, 0x76, 0x98, 0xA9, 0xCC, 0x8A, 0x76, 0x77, 0x87, 0x67, 0x86, 0x68, 0x76, 0xDA, 0xCC, 0xDD, 0xCB, 0xCD, 0xCD, 0xCC, 0xCB, 0x0F, 
  0x8C, 0x77, 0xA9, 0xA9, 0xBA, 0xAB, 0x8A, 0x87, 0x98, 0x67, 0xB9, 0xAB, 0x99, 0x79, 0x44, 0x76, 0x66, 0x66, 0x87, 0x98, 0xBB, 0x69, 0x76, 0xA9, 0x78, 0x77, 0x87, 0x77, 0x87, 0xCB, 0xAA, 0xCB, 0xCB, 0xDD, 0xCC, 0xBC, 0xCA, 0x0F, 
  0x9C, 0x88, 0x98, 0xA9, 0xBA, 0x9A, 0x89, 0x87, 0x99, 0x77, 0xA8, 0xAA, 0x9A, 0x89, 0x56, 0x66, 0x56, 0x64, 0x76, 0x87, 0x9A, 0x77, 0x96, 0xAB, 0x78, 0x87, 0x78, 0x87, 0xA8, 0xBA, 0x9A, 0xCA, 0xCB, 0xDC, 0xCC, 0xAB, 0xCA, 0x0E, 
  0x9C, 0x88, 0x98, 0x98, 0xBA, 0x9A, 0x78, 0x99, 0x99, 0x78, 0x99, 0x78, 0x98, 0x8A, 0x76, 0x67, 0x56, 0x65, 0x77, 0x87, 0x89, 0x98, 0xAA, 0x8A, 0x88, 0x88, 0x88, 0x89, 0x99, 0xA8, 0x9B, 0xBA, 0xCC, 0xDD, 0xBC, 0xBB, 0xCB, 0x0E, 
  0xAD, 0x89, 0x98, 0xA9, 0xAB, 0x9A, 0x78, 0x99, 0x98, 0x88, 0x99, 0x57, 0x86, 0x89, 0x76, 0x87, 0x88, 0x77, 0x78, 0x87, 0x99, 0xA9, 0xBB, 0x78, 0x98, 0x78, 0x97, 0x9A, 0x8A, 0x97, 0x89, 0xA8, 0xCC, 0xDD, 0xBC, 0xBA, 0xCC, 0x0E, 
  0xBE, 0x99, 0x99, 0xBA, 0xAB, 0x8A, 0x99, 0x88, 0x87, 0x88, 0x99, 0x68, 0x65, 0x87, 0x87, 0x88, 0x99, 0x78, 0x77, 0x86, 0xA9, 0xAA, 0x9A, 0x77, 0x87, 0x77, 0x87, 0x99, 0x88, 0xAA, 0x88, 0xB9, 0xCB, 0xCC, 0xBC, 0xBB, 0xDC, 0x0E, 
  0xCF, 0x99, 0x88, 0xBA, 0xAA, 0x89, 0x99, 0x78, 0x77, 0x88, 0x99, 0x67, 0x76, 0x87, 0x98, 0x99, 0x9A, 0x68, 0x76, 0x87, 0x9A, 0xAA, 0x89, 0x77, 0x87, 0xA9, 0x99, 0x99, 0x97, 0xAA, 0xBB, 0xCB, 0xCB, 0xCC, 0xBB, 0xCC, 0xDC, 0x0F, 
  0xCF, 0xAA, 0x88, 0xCA, 0x9B, 0x78, 0x88, 0x78, 0x66, 0x76, 0x88, 0x56, 0x76, 0x87, 0x99, 0xAA, 0x9A, 0x78, 0x77, 0xA8, 0x9A, 0x98, 0x89, 0x77, 0x76, 0xBA, 0xAA, 0x9A, 0x98, 0x98, 0xBB, 0xBB, 0xBC, 0xCB, 0xBC, 0xCC, 0xDC, 0x0F, 
  0xDF, 0xAB, 0x99, 0xCB, 0x9B, 0x77, 0x77, 0x77, 0x56, 0x66, 0x76, 0x67, 0x77, 0x77, 0xA8, 0xAA, 0x99, 0x89, 0x88, 0xA9, 0x8A, 0x87, 0x78, 0x77, 0x66, 0xA8, 0x99, 0x99, 0x9A, 0x88, 0x99, 0xBA, 0xAC, 0xCA, 0xCD, 0xCC, 0xDC, 0x0F, 
  0xEF, 0x9C, 0x98, 0xBB, 0x8A, 0x77, 0x76, 0x66, 0x66, 0x66, 0x86, 0x67, 0x66, 0x77, 0x98, 0xA9, 0xAA, 0x9A, 0x99, 0xA9, 0x8A, 0x77, 0x77, 0x66, 0x66, 0x87, 0x77, 0xB9, 0x9B, 0x67, 0x97, 0xBA, 0xAC, 0xCA, 0xCC, 0xCB, 0xED, 0x0F, 
  0xFF, 0xAD, 0x88, 0xAA, 0x8A, 0x77, 0x67, 0x76, 0x67, 0x66, 0x86, 0x68, 0x66, 0x77, 0x98, 0xAA, 0xDB, 0xAD, 0x99, 0xAA, 0x9A, 0x78, 0x87, 0x77, 0x77, 0x78, 0x76, 0x98, 0x79, 0x66, 0x77, 0xB9, 0xBB, 0xCB, 0xBC, 0xCA, 0xFD, 0x0F, 
  0xFF, 0xBE, 0x78, 0xAA, 0x88, 0x88, 0x77, 0x77, 0x67, 0x66, 0x66, 0x66, 0x76, 0x77, 0x87, 0xBA, 0xDC, 0xBE, 0xA9, 0xAA, 0x89, 0x88, 0x88, 0xBA, 0x9A, 0x78, 0x86, 0x77, 0x67, 0x76, 0x77, 0xB9, 0xCC, 0xCD, 0xBB, 0xDC, 0xFE, 0x0F, 
  0xFF, 0xCE, 0x8A, 0xAA, 0x88, 0x88, 0x77, 0x77, 0x66, 0x66, 0x66, 0x66, 0x76, 0x77, 0x87, 0xB9, 0xCB, 0xBC, 0xAA, 0xAA, 0x89, 0x99, 0x88, 0xBA, 0x8A, 0x67, 0x86, 0x78, 0x66, 0x77, 0x87, 0xCA, 0xDD, 0xCD, 0xCC, 0xDD, 0xFE, 0x0F, 
  0xEF, 0xCE, 0x9A, 0xA9, 0xAB, 0x88, 0x77, 0x67, 0x66, 0x66, 0x66, 0x56, 0x76, 0x77, 0x77, 0xB8, 0xAB, 0xBB, 0xAB, 0x9A, 0x99, 0x89, 0x88, 0x98, 0x88, 0x67, 0x97, 0x79, 0x67, 0x76, 0x88, 0xDA, 0xEE, 0xDC, 0xDD, 0xDD, 0xFE, 0x0F, 
  0xEF, 0xEF, 0x9A, 0x98, 0xAC, 0x77, 0x77, 0x66, 0x66, 0x56, 0x65, 0x66, 0x66, 0x77, 0x87, 0xA9, 0xAA, 0xBB, 0x9A, 0x9A, 0x88, 0x78, 0x88, 0x77, 0x78, 0x77, 0x87, 0xA9, 0x7A, 0x76, 0xA8, 0xDB, 0xEE, 0xDC, 0xDD, 0xED, 0xFE, 0x0F, 
  0xFF, 0xFF, 0xAC, 0x88, 0xAA, 0x77, 0x67, 0x66, 0x65, 0x55, 0x66, 0x66, 0x66, 0x77, 0x87, 0xA9, 0xBA, 0xBB, 0x89, 0x9A, 0x88, 0x78, 0x87, 0x87, 0x77, 0x66, 0xA7, 0xCB, 0x9B, 0x88, 0xCA, 0xDC, 0xDE, 0xCC, 0xCD, 0xFD, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xBE, 0x89, 0xAA, 0x89, 0x57, 0x65, 0x56, 0x55, 0x65, 0x66, 0x76, 0x77, 0x87, 0xA8, 0xAA, 0xBB, 0x89, 0x98, 0x89, 0x78, 0x77, 0x77, 0x66, 0x77, 0xB9, 0xBB, 0xBC, 0xBB, 0xCC, 0xEC, 0xDD, 0xCD, 0xCC, 0xFE, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xCF, 0x8A, 0xA9, 0x9A, 0x67, 0x55, 0x55, 0x65, 0x56, 0x76, 0x67, 0x66, 0x88, 0x97, 0xAB, 0x99, 0x88, 0x88, 0x88, 0x78, 0x67, 0x66, 0x77, 0x77, 0xA9, 0xBA, 0xCB, 0xDD, 0xCC, 0xED, 0xDD, 0xDD, 0xDC, 0xFE, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xEF, 0x9B, 0xAA, 0xBA, 0x8A, 0x56, 0x55, 0x65, 0x56, 0x66, 0x67, 0x76, 0x99, 0x87, 0x99, 0x78, 0x87, 0x98, 0x88, 0x88, 0x67, 0x66, 0x77, 0x67, 0x87, 0xAA, 0xBA, 0xCC, 0xDC, 0xDD, 0xDD, 0xDD, 0xED, 0xFF, 0xFF, 0x0F, 
  0xEF, 0xEE, 0xFF, 0xAD, 0xBA, 0xBB, 0x9A, 0x77, 0x55, 0x66, 0x66, 0x66, 0x66, 0x76, 0x88, 0x88, 0x87, 0x78, 0x87, 0xBA, 0xAA, 0x89, 0x67, 0x76, 0x66, 0x66, 0x86, 0xA9, 0xAA, 0xCB, 0xDC, 0xDE, 0xED, 0xDD, 0xFE, 0xEF, 0xEE, 0x0F, 
  0xEF, 0xEE, 0xFF, 0xBF, 0xBA, 0xBB, 0x9A, 0x77, 0x56, 0x66, 0x77, 0x67, 0x76, 0x66, 0x76, 0x77, 0x67, 0x87, 0xA9, 0xCB, 0xAC, 0x88, 0x67, 0x76, 0x66, 0x66, 0x87, 0x98, 0xA9, 0xBB, 0xDC, 0xEE, 0xDE, 0xDC, 0xFF, 0xEF, 0xEE, 0x0F, 
  0xFF, 0xFF, 0xFF, 0xDF, 0x9B, 0xB9, 0xBC, 0x68, 0x66, 0x66, 0x76, 0x77, 0x87, 0x67, 0x76, 0x77, 0x77, 0x87, 0xA9, 0xCB, 0x9B, 0x88, 0x67, 0x66, 0x76, 0x76, 0x77, 0x98, 0xA9, 0xCB, 0xDC, 0xFE, 0xDF, 0xED, 0xFF, 0xFF, 0xFE, 0x0F, 
  0xFF, 0xFF, 0xFE, 0xFF, 0xAD, 0xA8, 0xCC, 0x8A, 0x98, 0x67, 0x66, 0x66, 0x87, 0x77, 0x66, 0x77, 0x87, 0x99, 0x98, 0xAA, 0x9A, 0x78, 0x66, 0x66, 0x66, 0x76, 0x87, 0xAA, 0xCB, 0xCC, 0xED, 0xFF, 0xDE, 0xFE, 0xFF, 0xFF, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xEE, 0xFE, 0xDF, 0x89, 0xCA, 0xCC, 0xBB, 0x89, 0x67, 0x66, 0x77, 0x77, 0x66, 0x77, 0x97, 0x99, 0x88, 0x88, 0x88, 0x67, 0x66, 0x66, 0x66, 0x77, 0x86, 0x99, 0xCB, 0xCC, 0xED, 0xEE, 0xED, 0xFF, 0xEE, 0xFE, 0xFF, 0x0E, 
  0xFF, 0xFF, 0xEF, 0xFE, 0xFF, 0x9C, 0xBA, 0xCB, 0xBB, 0xAA, 0x89, 0x77, 0x78, 0x77, 0x77, 0x77, 0x98, 0x88, 0x77, 0x77, 0x77, 0x67, 0x66, 0x66, 0x77, 0x67, 0x76, 0x87, 0xDC, 0xDC, 0xEE, 0xDE, 0xFD, 0xFF, 0xEE, 0xFF, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xBE, 0x99, 0xB9, 0xAC, 0xAA, 0x99, 0x78, 0x77, 0x87, 0x99, 0x88, 0x78, 0x77, 0x77, 0x67, 0x66, 0x76, 0x67, 0x67, 0x77, 0x66, 0x76, 0xB8, 0xDE, 0xCC, 0xED, 0xEE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 
  0xEF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0x8B, 0x87, 0xBB, 0xBA, 0x9A, 0x78, 0x77, 0x88, 0x88, 0x89, 0x78, 0x76, 0x77, 0x67, 0x66, 0x67, 0x77, 0x67, 0x66, 0x66, 0x97, 0xCB, 0xDD, 0xCC, 0xDC, 0xFE, 0xEF, 0xFE, 0xFF, 0xEF, 0xEE, 0x0F, 
  0xEF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0xBF, 0x67, 0x99, 0x88, 0x88, 0x78, 0x77, 0x88, 0xA9, 0xBA, 0x78, 0x77, 0x67, 0x66, 0x67, 0x77, 0x67, 0x66, 0x66, 0x76, 0xA8, 0xDC, 0xDD, 0xCD, 0xEC, 0xFF, 0xEF, 0xFE, 0xFF, 0xFF, 0xEE, 0x0F, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8B, 0x88, 0x67, 0x76, 0x77, 0x77, 0x88, 0xA9, 0xCC, 0x89, 0x67, 0x66, 0x76, 0x66, 0x77, 0x66, 0x66, 0x66, 0x87, 0xDB, 0xDD, 0xDD, 0xDD, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xEE, 0xFE, 0xFF, 0xEF, 0xFE, 0xCF, 0x89, 0x78, 0x77, 0x77, 0x77, 0x77, 0x88, 0x99, 0x89, 0x67, 0x67, 0x66, 0x66, 0x77, 0x66, 0x66, 0x77, 0xB9, 0xCC, 0xCC, 0xDD, 0xED, 0xFF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFE, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xEE, 0xFE, 0xFF, 0xEF, 0xFE, 0xFF, 0xAD, 0x78, 0x77, 0x77, 0x66, 0x77, 0x77, 0x77, 0x78, 0x77, 0x67, 0x66, 0x66, 0x87, 0x67, 0x76, 0x87, 0xCB, 0x7A, 0xDA, 0xDD, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFE, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0x8C, 0x77, 0x77, 0x67, 0x77, 0x77, 0x67, 0x67, 0x66, 0x66, 0x66, 0x66, 0x77, 0x77, 0x98, 0xBA, 0xDC, 0xAB, 0xDC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 
  0xEF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0xDF, 0x7A, 0x66, 0x77, 0x67, 0x66, 0x66, 0x66, 0x66, 0x66, 0x76, 0x77, 0x66, 0x97, 0xDB, 0xDD, 0xDD, 0xDC, 0xFE, 0xFF, 0xEF, 0xFF, 0xFF, 0xEF, 0xFE, 0xFF, 0xEF, 0xEE, 0x0F, 
  0xEF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xDF, 0x8A, 0x66, 0x66, 0x66, 0x66, 0x76, 0x66, 0x66, 0x76, 0x77, 0x87, 0xB9, 0xED, 0xDD, 0xDD, 0xED, 0xFE, 0xFF, 0xEF, 0xFE, 0xFF, 0xEF, 0xFE, 0xFF, 0xEF, 0xEE, 0x0F, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0x8B, 0x77, 0x66, 0x77, 0x76, 0x87, 0x77, 0x77, 0x77, 0xB9, 0xCC, 0xDD, 0xEE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xEF, 0xFE, 0xFF, 0xEF, 0xFE, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xEF, 0xCE, 0x8A, 0x99, 0x78, 0x78, 0x77, 0x77, 0x98, 0xCA, 0xED, 0xEE, 0xEF, 0xFF, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0x0F, 
  0xFF, 0xFF, 0xEF, 0xFE, 0xFF, 0xEF, 0xFE, 0xFF, 0xEF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xCD, 0xCC, 0xAC, 0x99, 0xBA, 0xCB, 0xED, 0xFE, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0x0F, 
  };
