#ifndef  _BLOCK_ROTATION_H_
#define  _BLOCK_ROTATION_H_

#define ARRAY_SIZE    4  // 4 * 4 array size
#define NUM_ROTATIONS 4
#define BLOCK_TYPE  7

// total 28 blocks of 4*4 array
int blocks[BLOCK_TYPE][NUM_ROTATIONS][ARRAY_SIZE][ARRAY_SIZE] = {
 { // first block type:
    { // first rotation
     {1,1,0,0}, // first array of size 4
     {1,1,0,0}, // second array of size 4
     {0,0,0,0}, // third array of size 4
     {0,0,0,0}, // fourth array of size 4
    },
    { // second rotaion
     {1,1,0,0},
     {1,1,0,0},
     {0,0,0,0},
     {0,0,0,0},
    },
    { // third totation
     {1,1,0,0},
     {1,1,0,0},
     {0,0,0,0},
     {0,0,0,0},
    },
    { // fourth totaion
     {1,1,0,0},
     {1,1,0,0},
     {0,0,0,0},
     {0,0,0,0},
    },
 },

 { // second block type
    { // first rotation
     {1,1,1,1},
     {0,0,0,0},
     {0,0,0,0},
     {0,0,0,0},
    },
    { // second rotation
     {0,1,0,0},
     {0,1,0,0},
     {0,1,0,0},
     {0,1,0,0},
    },
    { // third rotation
     {1,1,1,1},
     {0,0,0,0},
     {0,0,0,0},
     {0,0,0,0},
    },
    { // fourth rotaion
     {0,1,0,0},
     {0,1,0,0},
     {0,1,0,0},
     {0,1,0,0},
    },
 },

 { // 3rd block type
    { // first rotation
     {1,0,0,0},
     {1,1,1,0},
     {0,0,0,0},
     {0,0,0,0},
    },
    { // second rotation
     {1,1,0,0},
     {1,0,0,0},
     {1,0,0,0},
     {0,0,0,0},
    },
    { // third rotation
     {1,1,1,0},
     {0,0,1,0},
     {0,0,0,0},
     {0,0,0,0},
    },
    { // fourth rotaion
     {0,1,0,0},
     {0,1,0,0},
     {1,1,0,0},
     {0,0,0,0},
    },
 },

 { // 4th block type
    { // first rotation
     {0,0,1,0},
     {1,1,1,0},
     {0,0,0,0},
     {0,0,0,0},
    },
    { // second rotation
     {1,0,0,0},
     {1,0,0,0},
     {1,1,0,0},
     {0,0,0,0},
    },
    { // third rotation
     {1,1,1,0},
     {1,0,0,0},
     {0,0,0,0},
     {0,0,0,0},
    },
    { // fourth rotaion
     {1,1,0,0},
     {0,1,0,0},
     {0,1,0,0},
     {0,0,0,0},
    },
 },


 { // 5th block type
    { // first rotation
     {0,1,0,0},
     {1,1,1,0},
     {0,0,0,0},
     {0,0,0,0},
    },
    { // second rotation
     {0,1,0,0},
     {0,1,1,0},
     {0,1,0,0},
     {0,0,0,0},
    },
    { // third rotation
     {1,1,1,0},
     {0,1,0,0},
     {0,0,0,0},
     {0,0,0,0},
    },
    { // fourth rotaion
     {0,1,0,0},
     {1,1,0,0},
     {0,1,0,0},
     {0,0,0,0},
    },
 },

 { // 6th block type
    { // first rotation
     {1,1,0,0},
     {0,1,1,0},
     {0,0,0,0},
     {0,0,0,0},
    },
    { // second rotation
     {0,1,0,0},
     {1,1,0,0},
     {1,0,0,0},
     {0,0,0,0},
    },
    { // third rotation
     {1,1,0,0},
     {0,1,1,0},
     {0,0,0,0},
     {0,0,0,0},
    },
    { // fourth rotaion
     {0,1,0,0},
     {1,1,0,0},
     {1,0,0,0},
     {0,0,0,0},
    },
 },

 {  // 1th block type
    { // first rotation
     {0,1,1,0},
     {1,1,0,0},
     {0,0,0,0},
     {0,0,0,0},
    },
    { // second rotation
     {1,0,0,0},
     {1,1,0,0},
     {0,1,0,0},
     {0,0,0,0},
    },
    {
     {0,1,1,0},
     {1,1,0,0},
     {0,0,0,0},
     {0,0,0,0},
    },
    { // fourth rotaion
     {1,0,0,0},
     {1,1,0,0},
     {0,1,0,0},
     {0,0,0,0},
    },
  },
};

#endif
