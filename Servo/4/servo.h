void DetectorInit(void);

enum DetectorState {ACTIVE, INACTIVE};
enum DetectorState eReadDetector(void);

enum ServoState {CALLIB, CALLIB12, IDLE, IN_PROGRESS};

//unsigned int uiCallibPosition;

struct Servo
{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
};

void Automat(void);
void ServoCallib(void);
void ServoCallib12(void);
void ServoInit(unsigned int uiServoFrequency);
void ServoGoTo(unsigned int uiPosition);