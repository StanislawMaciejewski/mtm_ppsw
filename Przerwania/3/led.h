enum LedState {LEFT, RIGHT};

void LedOn (unsigned char ucLedIndeks);
void LedStep(enum LedState eLedState);
void LedInit (void);
void LedStepLeft(void);
void LedStepRight(void);