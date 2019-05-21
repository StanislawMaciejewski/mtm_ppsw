enum LedDirection {LEFT, RIGHT};
enum LedState{STATE0, STATE1, STATE2, STATE3, STATE4, STATE5};

void LedOn (unsigned char ucLedIndeks);
void LedStep(enum LedDirection eLedDirection);
void LedInit (void);
