#include "blocks.h"

void random_block_series(uint8_t series[NUM_OF_BLOCKS])
{
    for(int8_t i = 7 - 1; i >= 0; i--)
    {
        randomSeed(analogRead(5));
        uint8_t j = random(i + 1);
            
        uint8_t temp = series[i];
        series[i] = series[j];
        series[j] = temp;
    }
}

blocks_entity convert_series_to_block(uint8_t id)
{
    box_shapes shape = (box_shapes) id;

    blocks_entity output;
    switch (shape)
    {
    case LSHAPE:
        output.update(LSHAPE, COLOUR_ORANGE, L_BLOCK_HIT_BOX, L_BLOCK_MID);
    break;
    case SSHAPE:
        output.update(SSHAPE, COLOUR_GREEN, S_BLOCK_HIT_BOX, S_BLOCK_MID);
    break;
    case ISHAPE:
        output.update(ISHAPE, COLOUR_CYAN, I_BLOCK_HIT_BOX, I_BLOCK_MID);
    break;
    case TSHAPE:
        output.update(TSHAPE, COLOUR_PURPLE, T_BLOCK_HIT_BOX, T_BLOCK_MID);
    break;
    case OSHAPE:
        output.update(OSHAPE, COLOUR_YELLOW, O_BLOCK_HIT_BOX, O_BLOCK_MID);
    break;
    case ZSHAPE:
        output.update(ZSHAPE, COLOUR_RED, Z_BLOCK_HIT_BOX, Z_BLOCK_MID);
    break;
    case JSHAPE:
        output.update(JSHAPE, COLOUR_BLUE, J_BLOCK_HIT_BOX, J_BLOCK_MID);
    break;
    
    default:
        Serial.println(F("ERROR: Randomise Block Failed"));
        break;
    }

    return output;
}

// blocks_entity random_block()
// {
//     pinMode(A5, INPUT);
//     randomSeed(analogRead(5));
//     uint8_t value = random(7);
//     value = random(7);

//     box_shapes shape = (box_shapes) value;

//     blocks_entity output;
//     switch (shape)
//     {
//     case LSHAPE:
//         output.update_type(LSHAPE, COLOUR_ORANGE, L_BLOCK_HIT_BOX, L_BLOCK_MID);
//     break;
//     case SSHAPE:
//         output.update_type(SSHAPE, COLOUR_GREEN, S_BLOCK_HIT_BOX, S_BLOCK_MID);
//     break;
//     case ISHAPE:
//         output.update_type(ISHAPE, COLOUR_CYAN, I_BLOCK_HIT_BOX, I_BLOCK_MID);
//     break;
//     case TSHAPE:
//         output.update_type(TSHAPE, COLOUR_PURPLE, T_BLOCK_HIT_BOX, T_BLOCK_MID);
//     break;
//     case OSHAPE:
//         output.update_type(OSHAPE, COLOUR_YELLOW, O_BLOCK_HIT_BOX, O_BLOCK_MID);
//     break;
//     case ZSHAPE:
//         output.update_type(ZSHAPE, COLOUR_RED, Z_BLOCK_HIT_BOX, Z_BLOCK_MID);
//     break;
//     case JSHAPE:
//         output.update_type(JSHAPE, COLOUR_BLUE, J_BLOCK_HIT_BOX, J_BLOCK_MID);
//     break;
    
//     default:
//         Serial.println(F("ERROR: Randomise Block Failed"));
//         break;
//     }

//     return output;
// }