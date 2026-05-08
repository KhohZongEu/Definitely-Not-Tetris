#include "blocks.h"

blocks_entity random_block()
{
    uint8_t value = (uint8_t) random(6);
    box_shapes shape = (box_shapes) value;

    blocks_entity output;
    switch (shape)
    {
    case LSHAPE:
        output.update_type(LSHAPE, COLOUR_ORANGE, L_BLOCK_HIT_BOX);
    break;
    case SSHAPE:
        output.update_type(SSHAPE, COLOUR_GREEN, S_BLOCK_HIT_BOX);
    break;
    case ISHAPE:
        output.update_type(ISHAPE, COLOUR_CYAN, I_BLOCK_HIT_BOX);
    break;
    case TSHAPE:
        output.update_type(TSHAPE, COLOUR_PURPLE, T_BLOCK_HIT_BOX);
    break;
    case OSHAPE:
        output.update_type(OSHAPE, COLOUR_YELLOW, O_BLOCK_HIT_BOX);
    break;
    case ZSHAPE:
        output.update_type(ZSHAPE, COLOUR_RED, Z_BLOCK_HIT_BOX);
    break;
    case JSHAPE:
        output.update_type(JSHAPE, COLOUR_BLUE, J_BLOCK_HIT_BOX);
    break;
    
    default:
        Serial.println("ERROR: Randomise Block Failed");
        break;
    }

    return output;
}